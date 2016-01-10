/*____________________________________________
| Copyright (c) David Perez 2014-2015         |
| Child Graphyte Node js Process              |
| GraphyteCLI 								  |
| Apex Data Solutions, LLC    				  |	
|____________________________________________*/

var spawn = require('child_process').spawn;
var ping = spawn('ping', ['bbc.co.uk']);
var fs = require('fs');
var os = require('os');
var events = require('events');
var crypto = require('crypto');
var util = require('util');
var uuid = require('node-uuid');
var se = require('speakeasy');
var ntp = require('ntp-client');

var graphytedb;
var database;
var mongoShell;
var mongoDB;
var gtm;
var cache;
var globaldb;

ping.stdout.setEncoding('utf8');
ping.stdout.on('data', function(data){
	console.log(data);
	ping.kill('SIGINT');
});

process.stdin.resume();
//process.send({message: 'Testing Child_frontProcess'});

ping.on('exit', function(code, signal){
	console.log('Push [Ctl + C] to exit the process:' + process.pid + ' with the signal ' + signal);
});

process.on('SIGINT', function(){
console.log('Got a SIGINT. Exiting');
process.exit(0);
});

process.on('SIGTERM', function(){
console.log('Got a SIGTERM. Exiting');
process.exit(0);
});

setInterval(function(){
// This keeps the process running
}, 10000);

console.log('Run `kill ' + process.pid +' ` to send a SIGTERM');
console.log('Run `kill -s SIGINT ' + process.pid + '` to send a SIGINT');
console.log('Requesting from http://bbc.co.uk');