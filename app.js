var addon = require('./build/Release/graphyteAPI');
//console.log('this should be:', addon.add(2,6));
addon(function (msg) {
    console.log(msg);
});