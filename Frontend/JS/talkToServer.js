function searchIngredients(e){
  const searchResults = document.getElementById('searchResults');
  const algoResults = document.getElementById('algoInfo');
  fetch('search', {
      method: 'POST',
      headers: {'Content-Type': 'application/json'},
      body: JSON.stringify({payload: e.value})
    }).then(res => res.json()).then(data => {
        let payload = data.payload;
        let timeST = data.timeST;
        let avgtimeST = data.avgtimeST;
        let avgtimeHM = data.avgtimeHM;
        let root = data.root;
        searchResults.innerHTML = '';
        algoResults.innerHTML = '';

        algoResults.innerHTML += '<a id="timeST">' + "SplayTree: "+ timeST + '</a>';
        algoResults.innerHTML += '<a id="avgtimeST">' + "SplayTree Avg: " + avgtimeST + "ns" + '</a>';
        algoResults.innerHTML += '<a id="avgtimeHM">' + "HashMap Avg: " + avgtimeHM + "ns" +  '</a>';
        algoResults.innerHTML += '<a id="avgtimeHM">' + "SplayTree Root: " + root + '</a>';

        if (payload.length < 1) {
          searchResults.innerHTML = '<a>Sorry. Nothing Found.</a>'
          return;
        }
        payload.forEach((item, index) => {
          if (index > 0)
          searchResults.innerHTML += '<a id="ingredient" onclick="ingredientValues(this)" href="#">' + item + '</a>';
        }
        );
        return;
    });
}

function ingredientValues(e){
  const algoResults = document.getElementById('algoInfo');
  fetch('ingredientValues', {
      method: 'POST',
      headers: {'Content-Type': 'application/json'},
      body: JSON.stringify({ingredient: e.innerText})
    }).then(res => res.json()).then(data => {
      const ingredientInfo = document.getElementById('ingredientInfo');
        let ingredientValues = data.ingredientValues;
        let timeST = data.timeST;
        let timeHM = data.timeHM;
        let avgtimeST = data.avgtimeST;
        let avgtimeHM = data.avgtimeHM;
        let root = data.root;
        ingredientInfo.innerHTML = '';
        algoResults.innerHTML = '';

        // Display in espective ingredient list under meals
        const ingredientList = document.getElementById(data.writetoID);
        var arr = e.innerHTML.split(",");
        var fst = arr.splice(0,1).join("");
        ingredientList.innerHTML += '<a id="ingredient">' + fst + '</a>';
        ingredientList.title = e.innerText;

        // display algo info
        algoResults.innerHTML += '<a id="timeST">' + "SplayTree: " + timeST + "ns" + '</a>';
        algoResults.innerHTML += '<a id="timeHM">' + "HashMap: " + timeHM + "ns" +  '</a>';
        algoResults.innerHTML += '<a id="avgtimeST">' + "SplayTree Avg: " + avgtimeST + "ns" + '</a>';
        algoResults.innerHTML += '<a id="avgtimeHM">' + "HashMap Avg: " + avgtimeHM + "ns" +  '</a>';
        algoResults.innerHTML += '<a id="avgtimeHM">' + "SplayTree Root: " + root + '</a>';
        
        // display in macros
        ingredientValues.forEach((item, index) => {
          if (index == 0) ingredientInfo.innerHTML += '<a href="#">' + "Calories: " + item + '</a>';
          if (index == 1) ingredientInfo.innerHTML += '<a href="#">' + "Protein: " + item + '</a>';
          if (index == 2) ingredientInfo.innerHTML += '<a href="#">' + "Carbs: " + item + '</a>';
          if (index == 3) ingredientInfo.innerHTML += '<a href="#">' + "Fats: " + item + '</a>';
          if (index == 4) ingredientInfo.innerHTML += '<a href="#">' + "Sugars: " + item + '</a>';
        });
        return;
    });
}

function showMealMacros(e){
  let MealText = e.innerHTML;
  const myArray = MealText.split(" ");
  // will always be second element in array bc of format: "Meal #""
  let specifiedMealNum = myArray[1];
  fetch('mealValues', {
    method: 'POST',
    headers: {'Content-Type': 'application/json'},
    body: JSON.stringify({sentMealNum: specifiedMealNum})
  }).then(res => res.json()).then(data => {
    const ingredientInfo = document.getElementById('ingredientInfo');
      let mealTotal = data.mealTotal;
      ingredientInfo.innerHTML = '';

      // display in macros
      mealTotal.forEach((item, index) => {
        if (index == 0) ingredientInfo.innerHTML += '<a href="#">' + "Calories: " + item + '</a>';
        else if (index == 1) ingredientInfo.innerHTML += '<a href="#">' + "Protein: " + item + '</a>';
        else if (index == 2) ingredientInfo.innerHTML += '<a href="#">' + "Carbs: " + item + '</a>';
        else if (index == 3) ingredientInfo.innerHTML += '<a href="#">' + "Fats: " + item + '</a>';
        else if (index == 4) ingredientInfo.innerHTML += '<a href="#">' + "Sugars: " + item + '</a>';
      });
      return;
  });
}