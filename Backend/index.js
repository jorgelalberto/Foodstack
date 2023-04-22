// greet module in this case
//const addon = require('bindings')('greet'); // import 'greet.node'
//exports.hello = addon.greetHello;

const greetModule = require('./build/Release/greet.node');
console.log('exports : ', greetModule);
console.log();
console.log('greetModule.greetHello() : ', greetModule.greetHello("Hi"));
console.log()



// Imports
const express = require('express')
const app = express()
const port = 3000
const path = require('path');



app.use(express.static(path.join(__dirname, '../Frontend')));
app.use('/CSS', express.static(path.join(__dirname, '../Frontend/CSS')));
app.use('/JS', express.static(path.join(__dirname, '../Frontend/JS')));
app.use('/IMGS', express.static(path.join(__dirname, '../Frontend/IMGS')));
var frontendPath = path.join(__dirname, '../Frontend');



app.get("/", function (req, res) {
    res.sendFile(frontendPath + "/index.html");
});
app.get('/homePage', function (req, res) {
    res.sendFile(frontendPath + '/homePage.html');
});
app.get('/aboutUs', function (req, res) {
    res.sendFile(frontendPath + '/aboutUs.html');
});



//Listen on port 3000
app.listen(port, function (err) {
    if (err) console.log(err);
    console.log("Server listening on PORT", port);
});