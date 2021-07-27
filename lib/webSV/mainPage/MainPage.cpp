#include "MainPage.h"

void MainPage::setMainPage(){
  *_mainPage = R"=====(
<!DOCTYPE html>
<html>
<head>
  <title>My House Control</title>
</head>
<body>
  <div id="Head"><h1>MY HOUSE</h1></div>
  <div id="body" style="display: block;">
    <div class="row">
      <div class="button" style="float: left;">
        <b>Fan</br></b>
        <button id="Fan" onclick="Turn(1)"><b>--</b></button>
        <div>
          <button class="almBut" id="almFan" onclick="SH_SltHour(1)"><b>--:--</b></button>
        </div>
      </div>
      <div class="button" style="float: right;">
        <b>Lamp</br></b>
        <button id="Lamp" onclick="Turn(3)"><b>--</b></button>
        <div>
          <button class="almBut" id="almLamp" onclick="SH_SltHour(3)"><b>--:--</b></button>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="button" style="float: left;">
        <b>Door</br></b>
        <button id="Door" onclick="Turn(2)"><b>--</b></B></button>
        <div>
          <button class="almBut" id="almDoor" onclick="SH_SltHour(2)"><b>--:--</b></button>
        </div>
      </div>
      <div class="button" style="float: right;">
        <b>Push Lamp</br></b>
        <button id="PLamp" onclick="Turn(4)"><b>--</b></button>
        <div>
          <button class="almBut" id="almPLamp" onclick="SH_SltHour(4)"><b>--:--</b></button>
        </div>
      </div>
    </div>
    <div class="row" id="MainDiv">
      <b id="MaintText">Main</br></b>
      <button id="MainBut" onclick="Turn(0)"><b>--</b></button>
      <div>
        <button class="almBut" id="almMain" onclick="SH_SltHour(0)"><b>--:--</b></button>
      </div>
    </div>
    <div><b id="Note"></b></div>
  </div>
  <div id="Almfra" style="display: none;">
    <b>Alarm</br></b>
    <div id="Almslt"> 
      <b>HH:MM</br></b>
      <select id="HourSlt" size="5"></select>
      <b>:</b>
      <select id="MntSlt" size="5"></select>
      <div id="setfr">
        <button onclick="Set()"><b>OK</b></button>
        <button onclick="Cancel()"><b>X</b></button>
      </div>
    </div>
  </div>
</body>
</html>
<style type="text/css">
  #setfr{
    margin: 10px;
  }
  #HourSlt::-webkit-scrollbar { 
      display: none; 
  }
  #MntSlt::-webkit-scrollbar { 
      display: none; 
  }
  #Almslt{
    width: 200px;
    margin: auto;
  }
  #Almfra{
    margin: 50px auto;
    text-align: center;
    width: 200px;
  }
  .almBut{
    width: 100px;
    height: 50px;
    border-radius: 10px;
    margin-top: 10px;
  }

  #Head{
    margin: auto;
    text-align: center;
    height: : 50px;
    width: 300px;
  }
  #body {
    width: 300px;
    height: 300px;
    align-content: center;
    align-items: center;
    margin: auto;
  }
  button {
    border: 5px solid ;
    border-top-color: #81F781;
    border-left-color: #81F781;
    border-bottom-color: #088A08;
    border-right-color: #088A08;
    font-size: 25px;
    margin: auto;
    background-color: #00FF00;
    width: 75px;
    height: 75px;
    border-radius: 50%;
  }
  button:active{
    border-top-color: #088A08;
    border-left-color: #088A08;
    border-bottom-color: #81F781;
    border-right-color: #81F781;
    transform: translate(3px,3px);
  }
  .row{
    clear: left;
  }
  .button{  
    text-align: center;
    margin: 20px 10px;
  }
  #MainText{
    margin: auto;
  }
  #MainDiv{
    text-align: center;
    width: 300px;
    height: 180px;
  }
  #MainBut{
    clear: right;
    margin: auto;
    border-radius: 10px;
    height: 75px;
    width: 150px;
  }
</style>
<script type="text/javascript">
  function Creat_Obj(){
      Browser = navigator.appName;
      if(Browser == "Microsoft Internet Explorer")
          Obj = new ActiveXObject("Microsoft.XMLHTTP");
      else
          Obj = new XMLHttpRequest();
    return Obj;
    }
  var xhttp = Creat_Obj();
  var Object_Json;
    function Getdata(url){
      xhttp.open("GET","/"+url,true);
      xhttp.onreadystatechange = Process_Json;
      xhttp.send();
        console.log(Object_Json);
    }

    function Process_Json(){
      if(xhttp.readyState == 4 && xhttp.status == 200){
        var Response_JSON = xhttp.responseText;
          Object_Json = JSON.parse(Response_JSON);
      }
      console.log(Object_Json);
    };

  function Turn(num) {
    switch (num){
      case 0:
        Getdata("Main");
        document.getElementById("MainBut").innerHTML = Object_Json.Main;
        break;
      case 1:
        Getdata("Fan");
        document.getElementById("Fan").innerHTML = Object_Json.Fan;
        break;
      case 2:
        Getdata("Door");
        document.getElementById("Door").innerHTML = Object_Json.Door;
        break;
      case 3:
        Getdata("Lamp");
        document.getElementById("Lamp").innerHTML = Object_Json.Lamp;
        break;
      case 4:
        Getdata("PLamp");
        document.getElementById("PLamp").innerHTML = Object_Json.PLamp;
        break;
    }
    console.log(Object_Json);
  }

  var xhttp3 = Creat_Obj();
  var Object_Json3;
    function UpdtStt(url){
      xhttp3.open("GET","/"+url,true);
      xhttp3.onreadystatechange = function(){
        if(xhttp3.readyState == 4 && xhttp3.status == 200){
          var Response_JSON = xhttp3.responseText;
            Object_Json3 = JSON.parse(Response_JSON);
        }
      }
      xhttp3.send();
        console.log(Object_Json3);
    }
  var Update = setInterval(UpdateStt, 600);
  function UpdateStt() {
    UpdtStt("Updt");
    document.getElementById("MainBut").innerHTML = Object_Json3.Main;
    document.getElementById("Fan").innerHTML = Object_Json3.Fan;
    document.getElementById("Door").innerHTML = Object_Json3.Door;
    document.getElementById("Lamp").innerHTML = Object_Json3.Lamp;
    document.getElementById("PLamp").innerHTML = Object_Json3.PLamp;
  }

  var xhttp2 = Creat_Obj();
  var Object_Json2;
  function Updatedata(url){
    xhttp2.open("GET","/"+url,true);
    xhttp2.onreadystatechange = function(){
      if(xhttp2.readyState == 4 && xhttp2.status == 200){
        var Response_JSON = xhttp2.responseText;
          Object_Json2 = JSON.parse(Response_JSON);
      }
    }
    xhttp2.send();
      console.log(Object_Json2);
  }
  var UpdateAlm = setInterval(UpdtAlm, 1000);
  function UpdtAlm(){
    Updatedata("UpdtALm");
    document.getElementById("almMain").innerHTML = Object_Json2.almMain;
    document.getElementById("almFan").innerHTML = Object_Json2.almFan;
    document.getElementById("almDoor").innerHTML = Object_Json2.almDoor;
    document.getElementById("almLamp").innerHTML = Object_Json2.almLamp;
    document.getElementById("almPLamp").innerHTML = Object_Json2.almPLamp;
  }

  var butAlm;
  function SH_SltHour(ButNum){
    butAlm = ButNum;
    document.getElementById("body").style.display = "none";
    document.getElementById("Almfra").style.display = "block";
    for (var count = 0 ; count <= 23; count++) {
      document.getElementById("HourSlt").innerHTML = document.getElementById("HourSlt").innerHTML + "<option>" + count + "</option>"
    }
    for (var count = 0 ; count <= 59; count++) {
      document.getElementById("MntSlt").innerHTML = document.getElementById("MntSlt").innerHTML + "<option>" + count + "</option>"
    }
  }
  function Cancel(){
    document.getElementById("body").style.display = "block";
    document.getElementById("Almfra").style.display = "none";
  }
  function Set(){
    switch (butAlm){
      case 0:
        var ID = "almMain";
        break;
      case 1:
        var ID = "almFan";
        break;
      case 2:
        var ID = "almDoor";
        break;
      case 3:
        var ID = "almLamp";
        break;
      case 4:
        var ID = "almPLamp";
        break;
    }
    var Hour = 0;
    Hour = document.getElementById("HourSlt").value;
    var Minute = 0;
    Minute =  document.getElementById("MntSlt").value;
    if (!Hour) Hour = 0;
    if (!Minute) Minute = 0;
    var Alarm = Hour*3600 + Minute*60;
    url = "Alm?butAlm=" + butAlm + "&Time=" + Alarm; 
    xhttp.open("GET","/"+url,true);
    xhttp.send();
    if (Hour < 10) Hour = "0" + Hour;
    if (Minute < 10) Minute = "0" + Minute;
    document.getElementById(ID).innerHTML = Hour + ":" + Minute;
    Cancel();
  }
</script>
)=====";
}

const char* MainPage::buildMainPage(){
  setMainPage();
  return *_mainPage;
}
