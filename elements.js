src="https://unpkg.com/axios/dist/axios.min.js"
   
   var holdNavn1;
    var holdNavn2;
    var tid1;
    var tid2;
    var highscore = [];
    var serverArray = [];
    var uddannelse;
    var litres;
    var sw = 0;
    var st = 0;
    var e = 0;
    var ee = 0;
    var bt = 0;
    var m = 0;
    var kt = 0;

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

function sortData(holdNavn, tid) {
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
    
    //console.log(highscore);
    // send til server
}



function checkStudy()
{
    var beerElement = document.createElement("h1");
    beerElement.value = "Ølscore";
         if (document.getElementsByName('softwareteknologi') == true) 
            {
            sw +=1.32;
            } else if (document.getElementsByName('elektriskenergiteknologi') == true){
            ee +=1.32;
            } else if (document.getElementsByName('bioteknologi') == true){
            bt +=1.32;
            } else if (document.getElementsByName('kemiteknologi') == true){
            kt +=1.32;
            } else if (document.getElementsByName('maskinteknik') == true){
            m +=1.32;
            } else if (document.getElementsByName('sundhedsteknologi') == true){
            st +=1.32;
            } else if (document.getElementsByName('elektronik') == true){
            e +=1.32;
            }

            //send til server
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


function updateData()
{
    setInterval(() => {  }, 5000);
}


function sendData(holdNavn, tid)
{
    var gameResult = {name: holdNavn, time: Number(tid)};
    serverArray.push(gameResult);

    axios.post('http://localhost:8080/', serverArray)
    .then(response => {

    }).catch(error => alert('Error sending name & time to server'));

}


function clickEvent() {
    holdNavn1 = document.getElementById("hold1-navn").value;
    tid1 = document.getElementById("hold1-tid").value;
    holdNavn2 = document.getElementById("hold2-navn").value;
    tid2 = document.getElementById("hold2-tid").value;

    sendData(holdNavn1,tid1);
    sendData(holdNavn2, tid2);
    
    sortData(holdNavn1, tid1);
    sortData(holdNavn2, tid2);
    
    checkStudy();


    
}