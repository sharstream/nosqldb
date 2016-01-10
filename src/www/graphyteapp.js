/*____________________________________________
| Copyright (c) David Perez 2014-2015         |
| Main Child Graphyte Node js Process         |
| RestAPI to GraphyteCLI                      |
| Apex Data Solutions, LLC                    | 
|____________________________________________*/

var express = require('express'),
    session = require('express-session'),
    logger = require('morgan'),
    errorHandler = require('errorhandler'),
    cookieParser = require('cookie-parser'),
    bodyParser = require('body-parser'),
    methodOverride = require('method-override'),
    fork = require('child_process').fork,
    graphyte_frontChild = fork(__dirname + '/graphyteChild'),
    graphyteapp_cliChild = fork(__dirname + './graphyteapp-cli'),
    graphyte_jsChild = fork(__dirname + './graphyte'),
    cluster_Child = fork(__dirname + './cluster'),
    app = express(),
    routes = require('../routes'),
    http = require('http'),
    https = require('https'),
    path = require('path'),
    mongoClient = new MongoClient(new Server('localhost', 27017,
                                              {'native_parse': true})),
    mongoskin = require('mongoskin'),
    dbUrl = process.env.MONGOHQ_URL || 'mongodb://@localhost:27017/test',
    db = mongoskin.db(dbUrl, {safe: true}),
    fs = require('graceful-fs'),
    url = require('fast-url-parser'),
    queryString = require('querystring'),
    events = require('events'),
    collections = {
      articles: db.collection('articles'),
      users: db.collection('users'),
    }
    graphyte = {}
}

getChildProcesses: function() {
    var pid;
    var pids = [];
    for (pid in graphyte.process) {
      pids.push({
        pid: pid, 
        available: graphyte.process[pid].true, 
        noOfRequests: graphyte.requestsByProcess[pid],
        debug: graphyte.process[pid].debug      
      });
    }
    pid = null;
    return pids;
};

getChild: function(child){
  return {child: graphyte_frontChild || 
          child: graphyteapp_cliChild || 
          child: graphyte_jsChild};
};

childProcessStarted: function(response) {
  graphyte.process[response.pid].started = true;
  var requestObj = {
    type:'first',
    params: {
      httpPort: graphyte.httpPort,
      database: graphyte.database,
      webSockets: graphyte.webSockets,
      graphyteGlobalsPath: graphyte.graphyteGlobalsPath,
      traceLevel: graphyte.traceLevel,
      logTo: graphyte.logTo,
      logFile: graphyte.logFile,
      startTime: graphyte.startTime,
      https: graphyte.https,
      webServerRootPath: graphyte.webServerRootPath,
      management: graphyte.management,
      no: response.processNo,
      hNow: graphyte.hSeconds(),
      modulePath: graphyte.modulePath,
      homePath: path.resolve('../'),
      webservice: graphyte.webservice,
      ntp: graphyte.ntp
    }     
  };
  console.log("Sending initialise request to " + response.pid + ': ' + JSON.stringify(requestObj, null, 2));
  graphyte.process[response.pid].send(requestObj);
};

//sending messages between child_processes
switch(getChild){
  case 0:
    graphyte_frontChild.on('message', function(m) {
      console.log('parent process received message:', m);
    });
    break;
  case 1:
    graphyteapp_cliChild.on('message', function(m) {
      console.log('parent process received message:', m);
    });
    break;
  case 2:
    graphyte_jsChild.on('message', function(m) {
      console.log('parent process received message:', m);
    });
    break;
  default:
    throw new Error("unknown child")
    break;
};

var graphyte = {
		prototype: 01,
		date: '3/20/2015'
  },
  startTime: new Date().getTime(),
  started: new Date().toUTCString(),
  logFile: '/var/log/output.log',
  modulePath: '../node_modules',
  webServerRootPath: '../www',
  isInteger: function(n) {
    n = parseInt(n);
    return +n === n && !(n % 1);
  },
  defaults: function(params){
    webSockets: {
      path: '../websocket/',
      socketIoPath: 'socket.io',
      process: '',
      pid: '',
      type: ''
  },
  setDefaults: function(defaults, params){
    childProcess: '',
    https: '',
    databases: '',
    webSockets: '',
    webservices: '',
    port: ''
  },
};

app.locals.appTitle = 'graphyte Node js module';
//open db mongodb
mongoClient.open(function(err, mongoClient){
  app.listen(app.get('port'));
  console.log('Express server started on port'+ app.get('port'));
})

mongoClient.connect('mongodb://@localhost:27017/test', function(err, db){
  if(err) throw err;
  db.collection('coll').findOne({}, function(err, doc){
    console.dir(doc);
    db.close();
  });
  console.dir("Called findOne!");
});

// Expose collections to request handlers
app.use(function(req, res, next) {
  if (!collections.articles || ! collections.users) return next(new Error('No collections.'))
  req.collections = collections;
  return next();
});

// Express.js configurations
app.set('port', process.env.PORT || 3000);
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

// Express.js middleware configuration
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded());
app.use(cookieParser('3CCC4ACD-6ED1-4844-9217-82131BDCB239'));
app.use(session({secret: '2C44774A-D649-4D44-9535-46E296EF984F'}))
app.use(methodOverride());
app.use(require('stylus').middleware(__dirname + '/public'));
app.use(express.static(path.join(__dirname, 'public')));

// Authentication middleware
app.use(function(req, res, next) {
  if (req.session && req.session.admin)
    res.locals.admin = true;
  next();
});

// Authorization Middleware
var authorize = function(req, res, next) {
  if (req.session && req.session.admin)
    return next();
  else
    return res.send(401);
};
/*
if ('development' == app.get('env')) {
  app.use(errorHandler());
}
*/
// PAGES&ROUTES
app.get('/', routes.index);
app.get('/login', routes.user.login);
app.post('/login', routes.user.authenticate);
app.get('/logout', routes.user.logout);
app.get('/admin', authorize, routes.article.admin);
app.get('/post', authorize, routes.article.post);
app.post('/post', authorize, routes.article.postArticle);
app.get('/articles/:slug', routes.article.show);

// REST API ROUTES
app.all('/api', authorize);
app.get('/api/articles', routes.article.list);
app.post('/api/articles', routes.article.add);
app.put('/api/articles/:id', routes.article.edit);
app.del('/api/articles/:id', routes.article.del);

app.all('*', function(req, res) {
  res.send(404);
});

// http.createServer(app).listen(app.get('port'), function(){
  // console.log('Express server listening on port ' + app.get('port'));
// });

var server = http.createServer(app);
var boot = function () {
  server.listen(app.get('port'), function(){
    console.info('Express server listening on port ' + app.get('port'));
  });
}
app.listen = function(){
  var server = http.createServer(this);
  return server.listen.apply(server, arguments);
};
var shutdown = function() {
  server.close();
  for (var pid in defaults.process) {
    defaults.addToQueue({
      type: 'stop & exit',
      pid: pid
    });
  }
};
if (require.main === module) {
  boot();
} else {
  console.info('Running app as a module')
  exports.boot = boot;
  exports.shutdown = shutdown;
  exports.port = app.get('port');
}
