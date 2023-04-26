const greetModule = require('./build/Release/greet.node');
console.log('exports : ', greetModule);
console.log();
console.log('greetModule.greetHello() : ', greetModule.greetHello(""));
console.log()

// var addon = require('bindings')('addon')
// var splayTree = addon.SplayTree(filename)



// Imports & Const Vars
const express = require('express')
const app = express()
const port = 3000
const path = require('path');



// Express Available Use Files
app.use(express.json());
app.use(express.urlencoded({extended: true}));
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

app.post('/homePage/search', function (req, res) {
    let payload = req.body.payload.trim();
    //let search = await splayTree.NarrowDownSearch(payload)
    console.log(payload);
    //res.send({payload: search});
});



//Listen on port 3000
app.listen(port, function (err) {
    if (err) console.log(err);
    console.log("Server listening on PORT", port);
});