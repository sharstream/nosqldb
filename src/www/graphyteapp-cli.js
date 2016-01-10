/*____________________________________________
| Copyright (c) David Perez 2014-2015         |
| Child Graphyte Node js Client               |
| Graphyte Node js with NoSQL Global Scheme   |
| Apex Data Solutions, LLC                    | 
|____________________________________________*/

var http = require('http');

var options = {
  host: 'shapeshed.com',
  port: 80,
  path: '/'
};

http.get(options, function(res) {
  if (res.statusCode  == 200) {
    console.log("The site is up!");
  }
  else {
    console.log("The site is down!");
  }
}).on('error', function(e) {
  console.log("There was an error: " + e.message);
});

process.send({message: 'Testing Child_cliProcess'});
