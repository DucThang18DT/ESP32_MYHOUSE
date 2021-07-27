#include "LoginPage.h"

void LoginPage::setLoginPage(){
*_loginPage = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>My House</title>
</head>
<body>
  <header><h1 id="ESP8266-WEBSERVER">ESP32-WEBSERVER</h1></header>
  <main>
    <div class="login-form" id="login-form">
          <form method="post" action="">
              <h1 id="Welcome">Welcome !</h1>
              <div class="input-box">
                  <input id="User" type="text" placeholder="User name">
              </div>
              <div class="input-box">
                  <input id="Pass" type="password" placeholder="Password">
              </div>
              <div class="submit-box">
          <input type="button" id="btSubmit" value="Log In" onClick="Validation()"/>
              </div>
          </form>
      </div>    
  </main>
</body>
</html>
<style type="text/css">
  html {
      background-color: #333333;
  }

  #ESP8266-WEBSERVER{
    color: #e0dfdc; 
    text-align: center;
    text-shadow: 0 -1px 0 #fff, 0 1px 0 #2e2e2e, 0 2px 0 #2c2c2c, 0 3px 0 #2a2a2a, 0 4px 0 #282828, 0 5px 0 #262626, 0 6px 0 #242424, 0 7px 0 #222, 0 8px 0 #202020, 0 9px 0 #1e1e1e, 0 10px 0 #1c1c1c, 0 11px 0 #1a1a1a, 0 12px 0 #181818, 0 13px 0 #161616, 0 14px 0 #141414, 0 15px 0 #121212, 0 22px 30px rgba(0, 0, 0, 0.9);
  }

  #ESP {
    color: #99FFFF; 
    text-align: center;
    text-shadow: 3px 2px 1px black;
  }

  #login-form{
    display: block;
  }
  .login-form{
      width: 100%;
      max-width: 400px;
      margin: 10% auto;
      background-color: #EEEEEE;
      border: 5px dotted #00CCFF;
      padding: 15px;
      border-radius: 10px;
  }

  #Welcome{
    color: #009999;
      font-size: 40px;
      margin-bottom: 30px;
      margin-top: 20px;
      margin-left: 30px;
  }

  .input-box{
      margin-bottom: 10px;
      margin-left: 45px;
  }
  .input-box input{
      padding: 7.5px 10px;
      width: 80%;
      border: 1px solid #cccccc;
      outline: none;
  }
  .submit-box{
      text-align: right;
      margin-bottom: 20px;
      margin-top: 15px;
      margin-right: 40px;
  }
  #btSubmit{
      padding: 7.5px 15px;
      border-radius: 2px;
      background-color: #009999;
      color: #ffffff;
      border: none;
      outline: none;
  }
</style>
<script type="text/javascript">
  function Validation() {
    var User_name = document.getElementById("User");
    var PassWord = document.getElementById("Pass");
    var url = "Valid?User=" + User_name + "&Pass=" + PassWord;
    Getdata(url);
  }

    function Creat_Obj(){
      Browser = navigator.appName;
      if(Browser == "Microsoft Internet Explorer")
          Obj = new ActiveXObject("Microsoft.XMLHTTP");
      else
          Obj = new XMLHttpRequest();
    return Obj;
    }
    var xhttp = Creat_Obj();
    function Getdata(url){
      xhttp.open("GET","/"+url,true);
      xhttp.onreadystatechange = Process;
      xhttp.send();
    }
    function Process(){
      if(xhttp.readyState == 4 && xhttp.status == 200){
          var Response_JSON = xhttp.responseText;
            var Object_Json = JSON.parse(Response_JSON);
        }
    }
</script>
)=====";}

const char* LoginPage::buildLoginPage(){
  setLoginPage();
  return *_loginPage;
}
