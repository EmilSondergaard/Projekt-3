
    var holdNavn1;
    var holdNavn2;
    var tid1;
    var tid2;
    var highscore = [];
    var beerCount = [];
    var uddannelse;
    var litres;
    var sw = 0;
    var st = 0;
    var e = 0;
    var ee = 0;
    var bt = 0;
    var m = 0;
    var kf = 0;

function beerScore (studieretning, liter){
    // var highscoreElement = document.createElement("h1");
    // highscoreElement.value = "Ølscore";
 

    // litres = litres + 1.32

    // var count = {study: uddannelse, liter: Number(litres)};
    // beerCount.push(count);
    // beerCount.sort((a,b)=> b.time - a.time);
    // const container2 = document.getElementById("beercount-container");
    // container.innerHTML="";
    // for (let index = 0; index < 5; index++) {
    //     if(highscore[index]){
    //         let item = document.createElement("h2");
    //         item.innerHTML = `studieretning: ${beerCount[index].study} - : ${highscore[index].time}`;
    //         container2.appendChild(item);
    //     }
    // }
}

function Highscore(holdNavn, tid) {
    var highscoreElement = document.createElement("h1");
    highscoreElement.value = "Highscore";

    var gameResult = {name: holdNavn, time: Number(tid)};
    highscore.push(gameResult);
    highscore.sort((a,b)=> a.time - b.time);
    const container1 = document.getElementById("highscore-container");
    container1.innerHTML="";
    for (let index = 0; index < 5; index++) {
        if(highscore[index]){
            let item = document.createElement("h2");
            item.innerHTML = `navn: ${highscore[index].name} - time: ${highscore[index].time}`;
            container1.appendChild(item);
        }
    }
    
    console.log(highscore);
}



function checkStudy()
{

    var beerElement = document.createElement("h1");
    beerElement.value = "Ølscore";
    var methods = document.getElementsByName('softwareteknologi');
    for (var i=0; i<methods.length; i++) {
         if (methods[i].checked == true) {
             sw +=1.32;
             alert(sw);
            }
}

//    if (document.getElementById('softwareteknologi').checked == true) 
//    {
//      sw = sw + 1.32;
//    }
//     else 
//     {
    
//    }



// if (document.getElementById("softwareteknologi") == 1) {
//     sw = sw + 1.32;
//     let item1 = document.createElement("h2");
//             item1.innerHTML = `softwareteknologi: - ${sw} L`;
            
// } 
// else if (document.getElementById("elektriskenergiteknologi") == 1) 
// {
//     ee = ee + 1.32;
//     let item2 = document.createElement("h2");
//             item2.innerHTML = `elektriskenergiteknologi: - ${ee} L`;
// }
// container1.appendChild(sw); 
// container1.appendChild(ee);




}

function clickEvent() {
    holdNavn1 = document.getElementById("hold1-navn").value;
    tid1 = document.getElementById("hold1-tid").value;
    holdNavn2 = document.getElementById("hold2-navn").value;
    tid2 = document.getElementById("hold2-tid").value;

    console.log("holdnavn: " +holdNavn1);
    console.log("tid: " + tid1);
    Highscore(holdNavn1, tid1);
    Highscore(holdNavn2, tid2);
    checkStudy();
}