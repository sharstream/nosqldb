/*____________________________________________
| Copyright (c) David Perez 2014-2015         |
| Child Graphyte Node js Process              |
| Graphyte Node js with NoSQL Global Scheme   |
| Apex Data Solutions, LLC                    | 
|____________________________________________*/

var events = require("event"),
    underscore = require(["underscore"]),
    changeHandler = new events.EventEmitter(),
    graphyte = {};

//var graphyteAdd = require('./lib/graphyte');
var graphyte_Addon = require('./build/Release/graphyte');
var connect_Addon = require('./build/Release/connect');

console.log(graphyteAdd.graphyte());

var init = function(db) {
  graphyte.Init = db;  
};

var deleteGlobal = function(globalName) {
  new Global(globalName)._delete();
  changeHandler.emit('del', globalName);
};

var prototype = function(globalName, register){

}

var deleteGlobalNode = function(globalName, subscripts) {
  new GlobalNode(globalName, subscripts)._delete();
};

var global = function(globalName) {
  return new GlobalNode(globalName,[]);
};

var redisGlobal = function(globalRedis, subscripts){
  graphyte.switchPrototype = redis;
  this._node = {global:globalRedis, subscripts:subscripts};
  this._globalname = globalRedis;
  this._subscripts = subscripts.slice(0);
  this.keys = Object.Keys(this).slice(0);
};

var docGlobal = function(globalDoc, subscripts){
  graphyte.switchPrototype = doc;
  // data-driven
  this._node = {global:globalDoc, subscripts:subscripts};
  this._globalname = globalDoc;
  this._subscripts = subscripts.slice(0);
  this.keys = Object.Keys(this).slice(0);

  this._delete = function() {
     changeHandler.emit('beforedelete', this._node);
     var node = this._node;
     var oldValue = graphyte.get(node).data;
     graphyte.del(node);
     node.oldValue = oldValue;
     changeHandler.emit('afterdelete', node);
  };

  Object.defineProperty(this, '_defined', {
    enumerable: true,
    configurable: false,
    get: function() {
      var def = graphyte.data().defined;
      if (typeof def === 'undefined') return 0;
      return def;
    }
  });

  Object.defineProperty(this, '_hasValue', {
    enumerable: true,
    configurable: false,
    get: function() {
      return ((this._defined === 1)||(this._defined === 11));
    }
  });

  Object.defineProperty(this, '_hasProperties', {
    enumerable: true,
    configurable: false,
    get: function() {
      return ((this._defined === 10)||(this._defined === 11));
    }
  });

  this._property = function(subscript) {
    // don't overwrite a global node's preset properties or methods
    if (subscript in this._reservedNames) return false;
    var subs = this._subscripts.slice(0);
    subs.push(subscript);
    if (typeof this[subscript] === 'undefined') this[subscript] = new GlobalNode(globalName,subs);
    return this[subscript];
  };

  this.$ = this._property;
  this._getProperty = this._property;

  this._getProperties = function() {
    var properties = [];
    this._forEach(function(key, subNode, node) {
      properties.push(key);
      node.$(key);
    });
    return properties;
  };

  this._setPropertyValue = function(subscript, value) {
    var subs = this._subscripts.slice(0);
    subs.push(subscript);
    var node = {global: globalName, subscripts: subs, data: value};
    graphyte.update({global: globalName, subscripts: subscript, data: value});
  };

  this._forEach = function(callback) {
    var result;
    var gnode;
    var direction = 'forwards';
    if (arguments.length > 1) {
      if (arguments[0].direction === 'reverse') direction = 'reverse';
      callback = arguments[1]; 
    }
    var subs = this._subscripts.slice(0);
    subs.push('');
    var node = {global: globalName, subscripts: subs};
    var quit = false;
    do {
      if (direction === 'forwards') {
        node = graphyte.order(node);
      }
      else {
        node = graphyte.previous(node);
      }
      result = node.result;
      if (result !== '') {
        gnode = this.$(result);
        quit = callback(result, gnode, this);
        if (quit) break;
      }
      console.log("Global Property: G: "+ this.$(result) + "S: "+ subs[keys] + "D: "+ node.data);
    }
    while (result !== '');
  };

  this._forRange = function(srcSubscript, destSubscript, callback) {
    var end = '';
    var result;
    var gnode;
    var subs;
    var node;
    var seed;
    var quit;
    var direction = 'forwards';
    if (arguments.length === 2) {
      var args = arguments[0];
      callback = arguments[1]; 
      if (args.direction === 'reverse') direction = 'reverse';
      srcSubscript = args.from;
      destSubscript = args.to;
    }
    if (direction === 'forwards') {
      if (destSubscript !== '') {
        subs = this._subscripts.slice(0);
        subs.push(destSubscript);
        node = {global: globalName, subscripts: subs};
        end = graphyte.factory.OrderGlobalbySubscript(node).result;
      }
      subs = this._subscripts.slice(0);
      subs.push(srcSubscript);
      node = {global: globalName, subscripts: subs};
      seed = graphyte.previous(node).result;
      quit = false;
      do {
        node = graphyte.order(node);
        result = node.result;
        if (result !== end) {
          gnode = this.$(result);
          quit = callback(result, gnode, this);
          if (quit) break;
        }
      }
      while (result !== end);
    }
    else {
      if (destSubscript !== '') {
        subs = this._subscripts.slice(0);
        subs.push(destSubscript);
        node = {global: globalName, subscripts: subs};
        end = graphyte.previous(node).result;
      }
      subs = this._subscripts.slice(0);
      subs.push(srcSubscript);
      node = {global: globalName, subscripts: subs};
      seed = graphyte.next(node).result;
      quit = false;
      do {
        node = graphyte.previous(node);
        result = node.result;
        if (result !== end) {
          gnode = this.$(result);
          quit = callback(result, gnode, this);
          if (quit) break;
        }
      }
      while (result !== end);
    }
  };

  this._getDocument = function(base, useArrays) {

    if (!base) base = 0;
    if (typeof useArrays === 'undefined') useArrays = true;

    var arrayOfSubscripts = function(globalNode) {
      var expected = base;
      var isArray = true;
      var subs = globalNode.subscripts.slice(0);
      subs.push("");
      var node = {global: globalName, subscripts: subs};
      var result;  
      do {
        node = graphyte.order(node);
        result = node.result;
        if (result !== '') {
          if (+result !== expected) {
            isArray = false;
            break;
          } 
          else {
            expected++;
          }
        }
      }
      while (result !== '');
      return isArray;
    };

    var getSubnodes = function(globalNode) {
      var isArray = false;
      if (useArrays) isArray = arrayOfSubscripts(globalNode);
      var document;
      if (isArray) {
        document = [];
      }
      else {
        document = {};
      }
      var result;
      var subs = globalNode.subscripts.slice(0);
      subs.push('');
      var defined;
      var node = {global: globalName, subscripts: subs};
      var index;
      do {
        node = graphyte.order(node);
        result = node.result;
        if (result !== '') {
          index = result;
          if (isArray) index = index - base;
          defined = graphyte.data(node).defined;
          if (defined === 1 || defined === 11) {
            document[index] = ewd.mumps.get(node).data;
            if (document[index] === 'true') document[index] = true;
            if (document[index] === 'false') document[index] = false;
          }
          if (defined === 10 || defined === 11) {
            //var subDocument = getSubnodes(node);
            //document[index] = subDocument;
            document[index] = getSubnodes(node);
          }
        }
      }
      while (result !== '');
      return document;
    };

    var fastGetDocument = function(node) {

      var addToJSON = function(obj, subscripts, value) {

        var append = function(obj, subscript) {
          if (typeof obj[subscript] !== 'object' || typeof obj[subscript] === 'undefined') {
             obj[subscript] = {};
          }
          return obj[subscript];
        };
  
        var build = function(obj) {
          i++;
          if (i === subscripts.length) {
            obj = value;
            return obj;
          }
          var obj2 = append(obj, subscripts[i]);
            obj[subscripts[i]] = build(obj2);
          return obj;
        };

        var i = -1;
        obj = build(obj);
        return obj;
      };

      var isSubNode = function(signature, currentArray) {
        var match = true;
        for (var i = 0; i < signature.length; i++) {
          if (signature[i] !== currentArray[i]) {
            match = false;
            break;
          }
        }
        return match;
      };

      var document = {};
      var signature = node.subscripts;
      var match = true;
      do {
        node = graphyte.next(node);
        match = false;
        if (node.defined !== 0) match = isSubNode(signature, node.subscripts);
        if (match) {
          document = addToJSON(document, node.subscripts, node.data);
        }  
      } while (match);
      return document;
    };

    if (!useArrays) {
      if (graphyte.next(this._node).ok) {
        return fastGetDocument(this._node);
      }
      else {
        return getSubnodes(this._node);
      }
    }
    else {
      return getSubnodes(this._node);
    }
  };

  this._setDocument = function(document, fast, offset) {

    if (!offset) offset = 0;

    var fixNumericString = function(value) {
      if (value === true || value === false) return value.toString();
      return value;
    };

    var setFast = function(obj, globalNode) {
      var subs;
      var i;
      var j;
      var value;
      for (i in obj){
        if (obj[i] === null) obj[i] = '';
        if (obj[i] instanceof Array) {
         if (obj[i].length !== 0) {
          for (j = 0; j < obj[i].length; j++) {
            if (typeof obj[i][j] === 'object') {
              subs = globalNode.subscripts.slice(0);
              subs.push(i);
              subs.push(j + offset);
              setFast(obj[i][j], {global: globalName, subscripts: subs});
            } 
            else {
              value = obj[i][j];
              if (value === null) value = '';
              subs = globalNode.subscripts.slice(0);
              subs.push(i);
              subs.push(j + offset);
              graphyte.update({global: globalName, subscripts: subs, data: value});
            }
          }
         }
        }
        if (typeof obj[i] !== 'object') {
          value = obj[i];
          if (value === null) value = '';
          subs = globalNode.subscripts.slice(0);
          subs.push(i);
          graphyte.update({global: globalName, subscripts: subs, data: value});
        }   
        if (obj[i] instanceof Object && !(obj[i] instanceof Array)) {
          subs = globalNode.subscripts.slice(0);
          subs.push(i);
          setFast(obj[i], {global: globalName, subscripts: subs});
        }
      }
    };

    var setProperties = function(obj, globalNode) {
      var i;
      var j;
      var value;
      var prop;
      for (i in obj){
        if (obj[i] === null) obj[i] = '';
        if (obj[i] instanceof Array) {
         if (obj[i].length !== 0) {
          for (j = 0; j < obj[i].length; j++) {
            if (typeof obj[i][j] === 'object') {
              prop = i;
              setProperties(obj[i][j], globalNode.$(prop).$(j + offset));
            } 
            else {
              value = obj[i][j];
              if (value === null) value = '';
              value = fixNumericString(value);
              globalNode.$(i).$(j + offset)._value = value;
            }
          }
         }
        }
        if (typeof obj[i] !== 'object') {
          value = obj[i];
          if (value === null) value = '';
          prop = i;
          value = fixNumericString(value);
          globalNode.$(prop)._value = value;
        }   
        if (obj[i] instanceof Object && !(obj[i] instanceof Array)) {
          setProperties(obj[i], globalNode.$(i));
        }
      }
    };

    if (fast) {
      //var subs = subscripts.slice(0);
      //var node = {global: globalName, subscripts: subs};
      setFast(document, {global: globalName, subscripts: subscripts.slice(0)});
    }
    else {
      setProperties(document, this);
    }
  };
};

this._increment = function(){
  
};

var tabGlobal = function(GlobalTabular, subscripts) {
  graphyte.switchPrototype = tab;
  
  this._node = {global:GlobalTabular, subscripts:subscripts};
  this._globalname = GlobalTabular;
  this._subscripts = subscripts.slice(0);
  this.keys = Object.Keys(this).slice(0);
};

var graphGlobal = function(GlobalGraph, subscripts) {
  graphyte.switchPrototype = graph;

  this._node = {global:GlobalGraph, subscripts:subscripts};
  this._globalname = GlobalGraph;
  this._subscripts = subscripts.slice(0);
  this.keys = Object.Keys(this).slice(0);
};

changeHandler.emit('message', 'Global prototype loaded');

changeHandler.on('message', function(Prototype){
  console.log(Prototype);
});

var gbldir = function(range) {
  if (typeof range === 'undefined') range = {};
  return graphyte.getDirectory(range);
};

function to_array(args) {
    var len = args.length,
        arr = new Array(len), i;
    for (i = 0; i < len; i += 1) {
        arr[i] = args[i];
    }
    return arr;
}

Object.defineProperty(this, 'key', {
  __proto__:Prototype(),
  value: 'static'
});

module.exports = {
  init: Init,
  register: typeGlobal,
  prototype: getPrototype,
  version: version,
  Global: Global,
  GlobalNode: GlobalNode,
  deleteGlobal: deleteGlobal,
  deleteGlobalNode: deleteGlobalNode,
  directory: gbldir,
  FactoryFn: GlobalFactoryFn,
  function: fn,
  array: to_array,
  changeHandler: changeHandler
};
