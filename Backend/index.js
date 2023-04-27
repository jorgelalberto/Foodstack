const { prototype } = require('events');
const greetModule = require('./build/Debug/greet.node');
var splayTreeAddon = require('./build/Debug/SPLAYTREE.node');
var hashmapAddon = require('./build/Debug/HASHMAP.node');
var splayTree = new splayTreeAddon.SplayTree();
var hashMap = new hashmapAddon.HashMap();

/* SplayTree Functions */
// Returns 5 specfied values of Ingredient
console.log('Func : ', splayTree.searchnapi('BUTTER,WITH SALT'));
// Returns all partial matches of Typed Information
console.log('Func : ', splayTree.searchpartialmatchesnapi('BUTTER,WITH SALT'));
// Returns time of last search operation
console.log('Func : ', splayTree.gettimenapi());
// FIXME: implement bmr function
/* HashMap Functions */
// Returns 5 specfied values of Ingredient
console.log('Func : ', hashMap.searchnapi('BUTTER,WITH SALT'));
console.log('Func : ', hashMap.gettimenapi());

// Imports & Const Vars
const express = require('express')
const app = express()
const port = 3000
const path = require('path');
// Changable Vars
// meals aray will contain maps of meals as such: const meal = new Set();, where each meal contains ingredients n its set
// updatemealslist
let numIngr = 0
let mealNum = 1
// 2d array of meals[meal#][ingredient#]
let meal1 = []
let meal2 = []
let meal3 = []
let meal4 = []
let meal5 = []
let meal6 = []

// times in nanoseconds and performance is all shared uses
let avg_ST_performance = 0
let avg_HM_performance = 0
let numSearchCalls = 0

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
    // page exit leads to reinitialize vars
    numIngr = 0
    mealNum = 1
    avg_ST_performance = 0
    avg_HM_performance = 0
    numSearchCalls = 0
    meal1 = []
    meal2 = []
    meal3 = []
    meal4 = []
    meal5 = []
    meal6 = []
});
app.get('/homePage', function (req, res) {
    res.sendFile(frontendPath + '/homePage.html');
    // page refresh leads to reinitialize vars
    numIngr = 0
    mealNum = 1
    avg_ST_performance = 0
    avg_HM_performance = 0
    numSearchCalls = 0
    meal1 = []
    meal2 = []
    meal3 = []
    meal4 = []
    meal5 = []
    meal6 = []});
app.get('/aboutUs', function (req, res) {
    res.sendFile(frontendPath + '/aboutUs.html');
    // page exit leads to reinitialize vars
    numIngr = 0
    mealNum = 1
    avg_ST_performance = 0
    avg_HM_performance = 0
    numSearchCalls = 0
    meal1 = []
    meal2 = []
    meal3 = []
    meal4 = []
    meal5 = []
    meal6 = []
});

app.post('/homePage/search', async (req, res) => {
    let payload = req.body.payload.trim();
    let id = "ingredient" + mealNum
    let search = splayTree.searchpartialmatchesnapi(payload)
    // FIXME: change searchpartialmatches to update time (currently does not)
    let time = splayTree.gettimenapi();
    //limit search results to 10
    search = search.slice(0,10);
    res.send({payload: search, "timeST": time, "passID":id, "avgtimeST": avg_ST_performance, "avgtimeHM": avg_HM_performance});
});
app.post('/homePage/ingredientValues', async (req, res) => {
    let ingredient = req.body.ingredient.trim();
    let id = "ingredientList" + mealNum;
    let macrosST = splayTree.searchnapi(ingredient);
    let macrosHM = hashMap.searchnapi(ingredient);
    let time1 = splayTree.gettimenapi();
    let time2 = hashMap.gettimenapi();

    numSearchCalls += 1;
    avg_ST_performance = parseFloat(((avg_ST_performance*(numSearchCalls-1)) + time1)/numSearchCalls).toFixed(2);
    avg_HM_performance = parseFloat(((avg_HM_performance*(numSearchCalls-1)) + time2)/numSearchCalls).toFixed(2);


    res.send({"ingredientValues": macrosST, "timeST": time1, "timeHM": time2, "writetoID": id, "avgtimeST": avg_ST_performance, "avgtimeHM": avg_HM_performance});
    if (mealNum == 0) meal1[numIngr] = ingredient;
    else if (mealNum == 1) meal2[numIngr] = ingredient;
    else if (mealNum == 2) meal3[numIngr] = ingredient;
    else if (mealNum == 3) meal4[numIngr] = ingredient;
    else if (mealNum == 4) meal5[numIngr] = ingredient;
    else if (mealNum == 5) meal6[numIngr] = ingredient;

    numIngr += 1;
    if (numIngr % 5 == 0) mealNum = mealNum + 1;
});
/*
app.post('/homePage/mealValues', async (req, res) => {
    let sentMealNum = req.body.sentMealNum.trim();
    let totatlMacrosST = 0;

    if (sentMealNum == 0) {
        for (let i=0; i<Meal1.length; i++)
        let macrosST = splayTree.searchnapi(ingredient);
        let macrosHM = hashMap.searchnapi(ingredient);
        let time1 = splayTree.gettimenapi();
        let time2 = hashMap.gettimenapi();
    
        numSearchCalls += 1;
        avg_ST_performance = parseFloat(((avg_ST_performance*(numSearchCalls-1)) + time1)/numSearchCalls).toFixed(2);
        avg_HM_performance = parseFloat(((avg_HM_performance*(numSearchCalls-1)) + time2)/numSearchCalls).toFixed(2);

    }meal1[numIngr] = ingredient;
    else if (sentMealNum == 1) meal2[numIngr] = ingredient;
    else if (sentMealNum == 2) meal3[numIngr] = ingredient;
    else if (sentMealNum == 3) meal4[numIngr] = ingredient;
    else if (sentMealNum == 4) meal5[numIngr] = ingredient;
    else if (sentMealNum == 5) meal6[numIngr] = ingredient;

    res.send({"ingredientValues": macrosST, "timeST": time1, "timeHM": time2, "writetoID": id, "avgtimeST": avg_ST_performance, "avgtimeHM": avg_HM_performance});
});
*/


//Listen on port 3000
app.listen(port, function (err) {
    // error check
    if (err) console.log(err);
    // notify server active
    console.log("Server listening on PORT", port);
});