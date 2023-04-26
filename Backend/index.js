const { prototype } = require('events');
const greetModule = require('./build/Debug/greet.node');
console.log()
console.log('exports : ', greetModule);
console.log('greetModule.greetHello() : ', greetModule.greetHello(""));
console.log()

var splayTreeAddon = require('./build/Debug/SPLAYTREE.node');
var splayTree = new splayTreeAddon.SplayTree();
//var tester1 = splayTree.[[Prototype]];

console.log('Object : ', splayTreeAddon);
console.log('Object : ', splayTree);
//console.log('Func : ', splayTree.searchnapi('BUTTER,WITH SALT'));
console.log('Func : ', splayTree.searchpartialmatchesnapi('BUTTER,WITH SALT'));
console.log('Func : ', splayTree.dummynapi());

//console.log('Object : ', splayTree.searchnapi("BUTTER,WITH SALT"));
console.log()



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
    let search = splayTree.searchpartialmatchesnapi(payload)
    console.log(search);
    //res.send({payload: search});
});



//Listen on port 3000
app.listen(port, function (err) {
    if (err) console.log(err);
    console.log("Server listening on PORT", port);
});