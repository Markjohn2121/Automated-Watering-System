  #include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

SoftwareSerial NodeMCU(D7,D6);

ESP8266WebServer server;
WebSocketsServer webSocket = WebSocketsServer(81);



unsigned long prevMillis = 0;
long intervalOn = 1000;
long intervalOff = 2000;
long ledOff = 2000;
String state = "OFF";

// SEND TO ARDUINO SERIAL COM VARIABLES this also use recieve from web
long schedOnePotValue = 0,
     schedpump,
     schedValue = 0,
     manualState,
     Mode =1; // 1 = auto, 2 = sched, 3 = manual






// RECIEVE TO ARDUINO SERIAL COM VARIABLES this also use SENF TO CLIENT
String soilMoisture1VALUE,
       soilMoisture2VALUE,
       schedStatus,
       manualStatus,
       autoActivate,
       schedActivate,
       manualActivate,
       currentMode,
       schedOnePotStatus = "stopped",
       schedTwoPotStatus = "stopped",
       manualOneStatus = "off",
       manualTwoStatus = "off",
       temperature,
       humidity, schedDone = "";





const int temp = D1;
const int onlineBtn = D0;
const int onlineLed = D2;
const int wifiLed = D3;




//====================WEBPAGE========================
char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <link rel="stylesheet" href="./">
    <title>Document</title>

     <style>
     * {
  font-family: "Gill Sans", "Gill Sans MT", Calibri, "Trebuchet MS", sans-serif;
}

body {
  background-color: aqua;
}

main {
  display: flex;
  flex-wrap: wrap;
  margin-left: auto;
  margin-right: auto;
  /* Switch starts here */
  /* Keyboard Users */
}
main .soil-moisture-container,
main .main-temp-container,
main .main-controller-container {
  padding: 1em;
  display: flex;
  flex-direction: column;
  justify-content: center;
  justify-items: center;
  align-content: center;
  gap: 2em;
  width: 80%;
  margin-left: auto;
  margin-right: auto;
  position: relative;
  background-color: rgb(15, 182, 182);
}
main .soil-moisture-container .label-con {
  width: 70%;
  display: flex;
  flex-direction: row;
  justify-content: space-between;
}
main .soil-moisture-container .label-con label {
  font-weight: bolder;
  font-family: "Gill Sans", "Gill Sans MT", Calibri, "Trebuchet MS", sans-serif;
}
main .soil-moisture-container #smOne {
  position: relative;
  color: blue;
  background-color: rgb(10, 10, 108);
  width: 70%;
  font-weight: bolder;
  font-size: larger;
}
main .soil-moisture-container #smOne #smValueOne {
  position: relative;
  width: 33.33%;
  background-color: wheat;
}
main .soil-moisture-container #smTwo {
  position: relative;
  color: blue;
  background-color: rgb(10, 10, 108);
  width: 70%;
  font-weight: bolder;
  font-size: larger;
}
main .soil-moisture-container #smTwo #smValueTwo {
  position: relative;
  width: 90%;
  background-color: thistle;
}
main .main-temp-container .label-con {
  width: 70%;
  display: flex;
  flex-direction: row;
  justify-content: space-between;
}
main .main-temp-container .label-con label {
  font-weight: bolder;
  font-family: "Gill Sans", "Gill Sans MT", Calibri, "Trebuchet MS", sans-serif;
}
main .main-temp-container #temp {
  position: relative;
  color: blue;
  background-color: rgb(10, 10, 108);
  width: 50%;
  font-weight: bolder;
  font-size: larger;
}
main .main-temp-container #temp #tempValue {
  position: relative;
  width: 33.33%;
  background-color: wheat;
}
main .main-temp-container #humi {
  position: relative;
  color: blue;
  background-color: rgb(10, 10, 108);
  width: 50%;
  font-weight: bolder;
  font-size: larger;
}
main .main-temp-container #humi #humiValue {
  position: relative;
  width: 33.33%;
  background-color: wheat;
}
main .main-controller-container {
  background-color: #4c4949;
  align-items: center;
  position: relative;
}
main .main-controller-container .mode-inputs {
  position: relative;
  display: flex;
  flex-wrap: wrap;
  border-radius: 0.5rem;
  background-color: #EEE;
  box-sizing: border-box;
  box-shadow: 0 0 0px 1px rgba(0, 0, 0, 0.06);
  padding: 0.25rem;
  width: inherit;
  height: -moz-fit-content;
  height: fit-content;
  font-size: 14px;
}
main .main-controller-container .mode-inputs .mode {
  flex: 1 1 auto;
  text-align: center;
}
main .main-controller-container .mode-inputs .mode input {
  display: none;
}
main .main-controller-container .mode-inputs .mode .name {
  display: flex;
  cursor: pointer;
  align-items: center;
  justify-content: center;
  border-radius: 0.5rem;
  border: none;
  padding: 0.5rem 0;
  color: rgb(51, 65, 85);
  transition: all 0.15s ease-in-out;
}
main .main-controller-container .mode-inputs .mode input:checked + .name {
  background-color: #0e97d6;
  font-weight: 600;
}
main .main-controller-container .auto-wrap, main .main-controller-container .manual-wrap {
  margin-top: -2em;
  background-color: #333;
  display: flex;
  flex-direction: row;
  flex-wrap: wrap;
  padding: 1em;
  position: relative;
  gap: 3em;
  background-color: rgb(58, 66, 66);
}
main .main-controller-container .sched-wrap {
  display: flex;
  flex-direction: row;
  flex-wrap: wrap;
  padding: 1em;
  position: relative;
  gap: 3em;
  background-color: rgb(58, 66, 66);
}
main .main-controller-container .sched-wrap #scheduleOne,
main .main-controller-container .sched-wrap #scheduleTwo {
  border-radius: 0.7em;
  border: none;
  outline: none;
  width: 8em;
  height: 2em;
}
main .main-controller-container .sched-wrap #scheduleOne::-moz-selection, main .main-controller-container .sched-wrap #scheduleTwo::-moz-selection {
  background-color: #0084d0;
}
main .main-controller-container .sched-wrap #scheduleOne::selection,
main .main-controller-container .sched-wrap #scheduleTwo::selection {
  background-color: #0084d0;
}
main .main-controller-container .sched-wrap .pot-con {
  display: flex;
  flex-direction: row;
  flex-wrap: wrap;
  gap: 1em;
}
main .main-controller-container .sched-wrap .pot-con .schedstatus {
  padding: -1em;
  height: -moz-fit-content;
  height: fit-content;
  display: flex;
}
main .main-controller-container .sched-wrap .pot-con .schedstatus #scheduleOne-status,
main .main-controller-container .sched-wrap .pot-con .schedstatus #scheduleTwo-status {
  padding: 0;
  margin-top: -0.5em;
  color: red;
}
main .main-controller-container #schedule-tab {
  display: none;
}
main .main-controller-container .manual-wrap {
  background-color: blueviolet;
}
main .rocker {
  display: inline-block;
  position: relative;
  /*
              SIZE OF SWITCH
              ==============
              All sizes are in em - therefore
              changing the font-size here
              will change the size of the switch.
              See .rocker-small below as example.
              */
  font-size: 2em;
  font-weight: bold;
  text-align: center;
  text-transform: uppercase;
  color: #888;
  width: 7em;
  height: 4em;
  overflow: hidden;
  border-bottom: 0.5em solid #eee;
}
main .rocker-small {
  font-size: 0.5em;
  /* Sizes the switch */
  margin: -1em;
}
main .rocker::before {
  content: "";
  position: absolute;
  top: 0.5em;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #999;
  border: 0.5em solid #eee;
  border-bottom: 0;
}
main .rocker input {
  opacity: 0;
  width: 0;
  height: 0;
}
main .switch-left,
main .switch-right {
  cursor: pointer;
  position: absolute;
  display: flex;
  align-items: center;
  justify-content: center;
  height: 2.5em;
  width: 3em;
  transition: 0.2s;
  -webkit-user-select: none;
     -moz-user-select: none;
          user-select: none;
}
main .switch-left {
  height: 2.4em;
  width: 2.75em;
  left: 0.85em;
  bottom: 0.4em;
  background-color: #ddd;
  transform: rotate(15deg) skewX(15deg);
}
main .switch-right {
  right: 0.5em;
  bottom: 0;
  background-color: #bd5757;
  color: #fff;
}
main .switch-left::before,
main .switch-right::before {
  content: "";
  position: absolute;
  width: 0.4em;
  height: 2.45em;
  bottom: -0.45em;
  background-color: #ccc;
  transform: skewY(-65deg);
}
main .switch-left::before {
  left: -0.4em;
}
main .switch-right::before {
  right: -0.375em;
  background-color: transparent;
  transform: skewY(65deg);
}
main input:checked + .switch-left {
  background-color: #0084d0;
  color: #fff;
  bottom: 0px;
  left: 0.5em;
  height: 2.5em;
  width: 3em;
  transform: rotate(0deg) skewX(0deg);
}
main input:checked + .switch-left::before {
  background-color: transparent;
  width: 3.0833em;
}
main input:checked + .switch-left + .switch-right {
  background-color: #ddd;
  color: #888;
  bottom: 0.4em;
  right: 0.8em;
  height: 2.4em;
  width: 2.75em;
  transform: rotate(-15deg) skewX(-15deg);
}
main input:checked + .switch-left + .switch-right::before {
  background-color: #ccc;
}
main input:focus + .switch-left {
  color: #333;
}
main input:checked:focus + .switch-left {
  color: #fff;
}
main input:focus + .switch-left + .switch-right {
  color: #fff;
}
main input:checked:focus + .switch-left + .switch-right {
  color: #333;
}
main .disableSwitch {
  background-color: #3d3b3b;
  color: #888;
}

.manual_con {
  background-color: #0e97d6;
  display: flex;
  flex-wrap: wrap;
  gap: 1em;
}
.manual_con .manual1 {
  position: relative;
  width: 100%;
  background-color: aqua;
  padding: 2em;
}
.manual_con .manual2 {
  position: relative;
  background-color: #3d3b3b;
  width: 100%;
}
     </style>
</head>

<body onload="javascript:init()">


    <center>
        <h1>AWT System</h1>

    </center>
    <main>

        <div class="soil-moisture-container">
            <!-- Soil Moisture ONE -->
            <div> <label>Soil moisture <span style="color: red; font-weight: bolder;">One</span> Value:
                    <div class="label-con">
                        <label for="">Wet</label>
                        <label for="">|</label>
                        <label for="">Dry</label>
                    </div>

                    <div id="smOne">
                        <div id="smValueOne">500</div>
                    </div>
                </label>
            </div>


            <!-- devide the value 100/19   1000/10 if higher to 1000 makeit 100% -->
            <div>
                <!--  Soil Moisture TWO-->

                <div> <label>Soil moisture <span style="color: red; font-weight: bolder;">Two</span> Value:
                        <div class="label-con">
                            <label for="">Wet</label>
                            <label for="">|</label>
                            <label for="">Dry</label>
                        </div>

                        <div id="smTwo">
                            <div id="smValueTwo">900</div>
                        </div>
                    </label>
                </div>
            </div>
        </div>


        <!-- TEMPERATURE/HUMIDITY -->

        <br>
        <div class="main-temp-container">

            <!-- TEMP -->
            <div> <label>TEMPERATURE \ HUMIDITY

                    <div class="label-con">

                        <label for="">Temperature</label>

                    </div>

                    <div id="temp">
                        <div id="tempValue">500</div>
                    </div>
                </label>
            </div>

            <!-- HUMI -->
            <div>
                <div class="label-con">
                    <label for="">Humidity</label>

                </div>

                <div id="humi">
                    <div id="humiValue">500</div>
                </div>
            </div>


        </div>


        <!-- TEMPERATURE/HUMIDITY -->

        <!-- MAIN CONTROLLER -->

        <br>





        <div class="main-controller-container">

            <div class="mode-inputs">
                <label class="mode">
                    <input type="radio" name="mode" checked="" id="mode-auto">
                    <span class="name">Auto</span>
                </label>
                <label class="mode">
                    <input type="radio" name="mode" id="mode-schedule">
                    <span class="name">Schedule</span>
                </label>

                <label class="mode">
                    <input type="radio" name="mode" id="mode-manual">
                    <span class="name">Manual</span>
                </label>



            </div>



            <div class="auto-wrap" id="auto-tab">
                <!-- Activate button -->

                <div class="auto-con-wrap" style="background-color: aqua;width:max-content;padding: 1em;">

                    <div><label for="" id="auto-activate"
                            style="background-color: green;padding: 5px;border-radius: 1em;">Activated</label></div>

                    <label class="rocker rocker-small" style="margin-top: 5px;margin-bottom: 5px; margin-left: auto;">
                        <input type="checkbox" id="auto-activate-btn" name="activate">
                        <span class="switch-left">Yes</span>
                        <span class="switch-right">No</span>
                    </label>
                </div>




            </div>



            <!-- POT SCHEDULE -->
            <div class="sched-wrap" id="schedule-tab">

                <div class="wrap">
                    <h3 style="margin-bottom: 5px;margin-top: -5px;">POT SCHEDULE</h3>


                    <div><label for="" id="sched-activate"
                            style="background-color: red;padding: 5px;border-radius: 1em;">Activate</label></div>
                    <!-- Activate button -->
                    <label class="rocker rocker-small" style="margin-top: 5px;margin-bottom: 5px;">
                        <input type="checkbox" id="sched-activate-btn" name="activate">
                        <span class="switch-left">Yes</span>
                        <span class="switch-right">No</span>
                    </label>
                    <br>

                    <label for="scheduleOne">Schedule Time </label>
                    <div class="pot-con">


                        <select name="scheduleOne" id="scheduleOne">
                            <option value="60000" selected>1 mins</option>
                            <option value="150000">15 mins</option>
                            <option value="1800000">30 mins</option>
                            <option value="3600000">1 hrs</option>
                            <option value="7200000">2 hrs</option>
                            <option value="10800000">3 hrs</option>
                            <option value="14400000">4 hrs</option>
                        </select>
                        <div style="display:inline ;margin-left: 1em;">
                            <label class="rocker rocker-small">
                                <input type="checkbox" id="schedOneSwitch" disabled>
                                <span class="switch-left disableSwitch" id="schedOne-On">On</span>
                                <span class="switch-right disableSwitch " id="schedOne-Off">Off</span>
                            </label>



                        </div>
                        <!-- <div class="schedstatus">
                            <p id="scheduleOne-status">Stopped</p>
                        </div> -->


                    </div>

                    <br>
                    <label for="scheduleTwo">Pump duration </label>
                    <div class="pot-con">



                        <select name="scheduleTwo" id="scheduleTwo">
                            
                            <option value="120000" selected>2 mins</option>
                            <option value="300000">5 mins</option>
                            <option value="600000">10 mins</option>
                            
                        </select>

<!-- 
                        <div style="display:inline ;margin-left: 1em;">
                            <label class="rocker rocker-small">
                                <input type="checkbox" id="schedTwoSwitch">
                                <span class="switch-left disableSwitch" id="schedTwo-On">On</span>
                                <span class="switch-right disableSwitch" id="schedTwo-Off">Off</span>
                            </label>

                        </div> -->

                        <div class="schedstatus">
                            <p id="scheduleTwo-status">Stopped</p>
                        </div>
                    </div>
                    <!-- POT STATUS -->


                </div>
                <!--END POT SCHEDULE -->








            </div >

            <!-- MANUAL -->
            <div class="manual-wrap" id="manual-tab" style="display: none;">
                <div><label for="" id="manual-activate"
                    style="background-color: red;padding: 5px;border-radius: 1em;">Deactivated</label></div>

            <label class="rocker rocker-small" style="margin-top: 5px;margin-bottom: 5px; margin-left: auto;">
                <input type="checkbox" id="manual-activate-btn" name="activate">
                <span class="switch-left">Yes</span>
                <span class="switch-right">No</span>
            </label>

            <div class="manual_con">

<div class="manual1">
<p>Manual Mode</p>

<label class="rocker rocker-small" style="margin-top: 5px;margin-bottom: 5px; margin-left: auto;">
  <input type="checkbox" id="manual-1-btn" name="activate" disabled>
  <span class="switch-left disableSwitch" id="manual1_On">On</span>
  <span class="switch-right disableSwitch" id="manual_off">off</span>
</label>

</div>

<!-- <div class="manual2">
  <p>POT 2</p>
  
  <label class="rocker rocker-small" style="margin-top: 5px;margin-bottom: 5px; margin-left: auto;">
    <input type="checkbox" id="manual-2-btn" name="activate" disabled>
    <span class="switch-left disableSwitch" id="manual2_On">On</span>
    <span class="switch-right disableSwitch" id="manual2_off">Off</span>
</label>
  
  </div> -->

            </div>



            </div>

    </main>



    <script>
    let schedPotOneValue = document.getElementById("scheduleOne");
let schedPotTwoValue = document.getElementById("scheduleTwo");

let schedOneSwitch = document.getElementById("schedOneSwitch");
let schedOne_On = document.getElementById("schedOne-On");
let schedOne_Off = document.getElementById("schedOne-Off");
let schedOne_status = document.getElementById("scheduleOne-status");

let schedTwoSwitch = document.getElementById("schedTwoSwitch");
let schedTwo_On = document.getElementById("schedTwo-On");
let schedTwo_Off = document.getElementById("schedTwo-Off");
let schedTwo_status = document.getElementById("scheduleTwo-status");

//radio btn
let mode_state = true;
let mode_auto = document.getElementById("mode-auto");
let mode_schedule = document.getElementById("mode-schedule");
let mode_manual = document.getElementById("mode-manual");

// tab
let schedule_tab = document.getElementById("schedule-tab");
let auto_tab = document.getElementById("auto-tab");
let manual_tab = document.getElementById("manual-tab");
let auto_activate = document.getElementById("auto-activate");
let auto_activate_btn = document.getElementById("auto-activate-btn");
let sched_activate = document.getElementById("sched-activate");
let sched_activate_btn = document.getElementById("sched-activate-btn");

let manual_activate = document.getElementById("manual-activate");
let manual_activate_btn = document.getElementById("manual-activate-btn");

let manual1_On = document.getElementById("manual1_On");
let manual_off = document.getElementById("manual_off");

// let manual2_On = document.getElementById("manual2_On");
// let manua2_off = document.getElementById("manual2_off");
var num;

let manual_1_btn = document.getElementById("manual-1-btn");
let manual_2_btn = document.getElementById("manual-2-btn");
// From ESP VARIABLE
let soilMoisture1VALUE = "0";
let soilMoisture2VALUE = "0";
let currentMode,currentStatus = "";
let schedStatus = "stopped";
let manualStatus = "stopped";
let autoActivate = "deactivate";
let schedActivate = "deactivate";
let manualActivate = "deactivate";

setActivateIndicator(autoActivate,schedActivate,manualActivate);

// sched_activate_btn.click();

function setActivateIndicator(autoActivate,schedActivate,manualActivate){

// for auto
if(autoActivate == "activated"){
auto_activate.innerText = "activated"
auto_activate.style.backgroundColor = "green";
}else{
auto_activate.innerText = "Deactivate"
auto_activate.style.backgroundColor = "red";
}

// for sched
if(schedActivate == "activated"){
sched_activate.innerText = "activated"
sched_activate.style.backgroundColor = "green";
schedOneSwitch.removeAttribute("disabled"); 
      schedOne_Off.classList.remove("disableSwitch");
      schedOne_On.classList.remove("disableSwitch");
}else{
sched_activate.innerText = "Deactivate"
sched_activate.style.backgroundColor = "red";


}

// for manual
if(manualActivate == "activated"){
manual_activate.innerText = "activated"
manual_activate.style.backgroundColor = "green";
manual_1_btn.removeAttribute("disabled"); 
      manual1_On.classList.remove("disableSwitch");
      manual_off.classList.remove("disableSwitch");
}else{
manual_activate.innerText = "Deactivate"
manual_activate.style.backgroundColor = "red";
manual_1_btn.setAttribute("disabled",true); 
manual1_On.classList.add("disableSwitch");
      manual_off.classList.add("disableSwitch");
}


}



manual_1_btn.onclick = () =>{
  
if(!manual_1_btn.checked){
  startManual(false);
}else{

  startManual(true);

}



}

// Manual mode btn

function startManual(stat){
if(stat){
  Socket.send("%"+ 1 );

}else{
  Socket.send("%"+ 0 );

}



}


function setStatus(currentMode,schedStatus,manualStatus){

 if(currentMode == "auto"){
  // setMode("auto");
  

  
  schedule_tab.style.display = "none";
    auto_tab.style.display = "block";
    manual_tab.style.display = "none";
    
    mode_auto.removeAttribute("disabled");
      mode_schedule.removeAttribute("disabled");
      mode_manual.removeAttribute("disabled");
auto_tab.click();
   
  mode_auto.setAttribute("disabled", true);
  mode_schedule.setAttribute("disabled", true);
  mode_manual.setAttribute("disabled", true);
  currentStatus = "auto";
 }else if(currentMode == "schedule"){
  // setMode("schedule");

  
  schedule_tab.style.display = "block";
    auto_tab.style.display = "none";
    manual_tab.style.display = "none";

    
    mode_auto.removeAttribute("disabled");
      mode_schedule.removeAttribute("disabled");
      mode_manual.removeAttribute("disabled");
      mode_schedule.click();
  mode_auto.setAttribute("disabled", true);
  mode_schedule.setAttribute("disabled", true);
  mode_manual.setAttribute("disabled", true);
  currentStatus = "schedule";
  sched_activate_btn.click();
 }else if(currentMode == "manual"){
  // setMode("manual");

  
  
  schedule_tab.style.display = "none";
    auto_tab.style.display = "none";
    manual_tab.style.display = "block";

    mode_auto.removeAttribute("disabled");
      mode_schedule.removeAttribute("disabled");
      mode_manual.removeAttribute("disabled");
      mode_manual.click();
  mode_auto.setAttribute("disabled", true);
  mode_schedule.setAttribute("disabled", true);
  mode_manual.setAttribute("disabled", true);
  currentStatus = "manual";
  manual_activate_btn.click();
 }else{
  // setMode("auto");
  // auto_activate_btn.click();
  // mode_auto.click();
  // mode_auto.setAttribute("disabled", true);
  // mode_schedule.setAttribute("disabled", true);
  // mode_manual.setAttribute("disabled", true);
 }

}





let smValueTwo = document.getElementById("smValueTwo");
let smTwo = document.getElementById("smTwo");

auto_activate_btn.click();

mode_auto.setAttribute("disabled", true);
mode_schedule.setAttribute("disabled", true);
mode_manual.setAttribute("disabled", true);

// activate buttons
auto_activate_btn.onchange = () => {
  activateButton("auto");
};

sched_activate_btn.onchange = () => {
  activateButton("schedule");
};
manual_activate_btn.onchange = () => {
  activateButton("manual");
};

// END OF ACTIVATE BUTTONS




  //===========================================


// INITIALIZE WEBSOCKET =====
    var Socket;
    function init() {
     Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
     Socket.onmessage = function(event){
        var obj = JSON.parse(event.data)

//if(obj.schedDone == "done" && obj.schedStatus == "run"){
//  Socket.send("$"+ 0 );
//}else{
//  
//}
//        
if(obj.schedStatus == "run"){
  schedTwo_status.innerText = "Running";
  schedTwo_status.style.color = "green";

}else{
  schedTwo_status.innerText = "Stopped";
  schedTwo_status.style.color = "red";
}
       setSensorReading(obj.soilMoisture1VALUE,obj.soilMoisture2VALUE,20,29);
        setActivateIndicator(obj.autoActivate,obj.schedActivate,obj.manualActivate);
     currentMode = obj.currentMode;
//        if(currentMode != currentStatus){
//    setStatus(currentMode,schedStatus,manualStatus);
//  }
//       
         console.log(obj);
      
      //const js = JSON.parse()
  
        
     }
    }

// END INITIALIZE WEBSOCKET ====




// Set sensors Reading Function ====
function setSensorReading(soilsnr1,soilsnr2,temp,humidity) {
  smValueOne.style.width = soilsnr1 / 10 + "%";
  smValueOne.innerText = soilsnr1;

  smValueTwo.style.width = soilsnr2 / 10 + "%";
  smValueTwo.innerText = soilsnr2;
  
}
// END Set sensors Reading Function ====

//===========================================

// MODE  =======
mode_auto.onclick = () => {
  setMode("auto");
};
mode_schedule.onclick = () => {
  setMode("schedule");
};
mode_manual.onclick = () => {
  setMode("manual");
};
// END OF MODE TAB ========

function setMode(mode) {
  if (mode == "auto") {
    schedule_tab.style.display = "none";
    auto_tab.style.display = "block";
    manual_tab.style.display = "none";
  } else if (mode == "schedule") {
    schedule_tab.style.display = "block";
    auto_tab.style.display = "none";
    manual_tab.style.display = "none";
  } else if (mode == "manual") {
    schedule_tab.style.display = "none";
    auto_tab.style.display = "none";
    manual_tab.style.display = "block";
  }
}

// save data to local storage
let saveData = () => {};

// start();

// SCHEDULE  ====

// schedPotOneValue.onchange = () => {
//   schedOneSwitch.checked = false;
//   potScheduleConfig(1, schedPotOneValue.value);
// };
// schedPotTwoValue.onchange = () => {
//   schedTwoSwitch.checked
//   potScheduleConfig(2, schedPotTwoValue.value);
// };
schedOneSwitch.onchange = () => {
    if (!schedOneSwitch.checked) {
    schedPotOneValue.removeAttribute("disabled");
      schedPotTwoValue.removeAttribute("disabled");
    Socket.send("$"+0);
}else{
//  Socket.send("%"+"ongoing" );
 Socket.send("$"+ schedPotOneValue.value );
  Socket.send("&"+ schedPotTwoValue.value);
  schedPotOneValue.setAttribute("disabled",true);
  schedPotTwoValue.setAttribute("disabled",true);
//  Socket.send("$"+schedPotOneValue.value );
// Socket.send("&"+ schedPotTwoValue.value);
//  alert(schedPotTwoValue.value);
// Send data to esp


}
};

// schedTwoSwitch.onchange = () => {
//   if (!schedTwoSwitch.checked) {
//     schedPotTwoValue.selectedIndex = 0;
//   }else{
//     // Send data to esp

//     Socket.send("&"+schedPotTwoValue.value );
      
//   }
// };
// END OF SCHEDULE EVENTS ====

// function for pot schedule on change
// function potScheduleConfig(pot, potValue) {
//   // schedOne_On.setAttribute

//   if (pot == 1) {
//     if (potValue != 0) {
//       schedOneSwitch.removeAttribute("disabled");

//       schedOne_Off.classList.remove("disableSwitch");
//       schedOne_On.classList.remove("disableSwitch");
//     } else {
//       schedOneSwitch.setAttribute("disabled", "true");
//       schedOneSwitch.checked = false;

//       schedOne_Off.classList.add("disableSwitch");
//       schedOne_On.classList.add("disableSwitch");
//   Socket.send("$"+schedPotOneValue.value );
//     }
//   }

//   if (pot == 2) {
//     if (potValue != 0) {
//       schedTwoSwitch.removeAttribute("disabled");

//       schedTwo_Off.classList.remove("disableSwitch");
//       schedTwo_On.classList.remove("disableSwitch");
//     } else {
//       schedTwoSwitch.setAttribute("disabled", "true");
//       schedTwoSwitch.checked = false;

//       schedTwo_Off.classList.add("disableSwitch");
//       schedTwo_On.classList.add("disableSwitch");
     
//     Socket.send("&"+schedPotTwoValue.value );
//     }
//   }
// }
// activate buttons function ====
function activateButton(mode) {
  let activated = "Activated";
  let Deactivate = "Deactivated";
  if (mode == "auto") {
    if (auto_activate_btn.checked) {
      alert("switching to Auto mode");
      mode_auto.setAttribute("disabled", true);
      mode_schedule.setAttribute("disabled", true);
      mode_manual.setAttribute("disabled", true);
//      auto_activate.innerText = activated;
//      auto_activate.style.backgroundColor = "green";
       currentStatus = "auto";
 Socket.send("#"+ 1);
      
    } else {
      // auto_activate_btn.checked =false;
      
//      auto_activate.innerText = Deactivate;
//      auto_activate.style.backgroundColor = "red";

      mode_auto.removeAttribute("disabled");
      mode_schedule.removeAttribute("disabled");
      mode_manual.removeAttribute("disabled");
       Socket.send("#"+ 0);
    }
  } else if (mode == "schedule") {
    if (sched_activate_btn.checked) {
      alert("switching to schedule mode");
      mode_auto.setAttribute("disabled", true);
      mode_schedule.setAttribute("disabled", true);
      mode_manual.setAttribute("disabled", true);
      
//      sched_activate.innerText = activated;
//      sched_activate.style.backgroundColor = "green";
       currentStatus = "schedule";
     Socket.send("#"+ 2);
//     Socket.send("$"+schedPotOneValue.value );
//        Socket.send("&"+schedPotTwoValue.value );
    } else {
      // auto_activate_btn.checked =false;
      
//      sched_activate.innerText = Deactivate;
//      sched_activate.style.backgroundColor = "red";
      mode_auto.removeAttribute("disabled");
      mode_schedule.removeAttribute("disabled");
      mode_manual.removeAttribute("disabled");
       Socket.send("#"+ 0);
    }
  } else if (mode == "manual") {
    if (manual_activate_btn.checked) {
      alert("switching to manual mode");
      mode_auto.setAttribute("disabled", true);
      mode_schedule.setAttribute("disabled", true);
      mode_manual.setAttribute("disabled", true);
//      manual_activate.innerText = activated;
//      manual_activate.style.backgroundColor = "green";
       currentStatus = "manual"; 
      Socket.send("#"+ 3);
    } else {
      // auto_activate_btn.checked =false;
     
//      manual_activate.innerText = Deactivate;
//      manual_activate.style.backgroundColor = "red";
      mode_auto.removeAttribute("disabled");
      mode_schedule.removeAttribute("disabled");
      mode_manual.removeAttribute("disabled");
       Socket.send("#"+ 0);
    }
  }
}

// function start() {
//   potScheduleConfig(1, schedPotOneValue.value);
//   potScheduleConfig(2, schedPotTwoValue.value);
// }






    </script>
</body>

</html>





)=====";








//====================WEBPAGE========================




void setup()
{
  pinMode(onlineLed,OUTPUT);
   pinMode(wifiLed,OUTPUT);
  
 pinMode(onlineBtn,INPUT_PULLUP);
 Serial.begin(115200);
    digitalWrite(onlineLed,LOW);
       digitalWrite(wifiLed,LOW);
    settingWifi(); // set wifi


if(MDNS.begin("esp8266")){
  Serial.println("MDNS reponse access using: esp8266.local");
}

  server.on("/",[](){
    server.send_P(200, "text/html", webpage);  
  });
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);


NodeMCU.begin(9600);
pinMode(D7,INPUT);
pinMode(D8,OUTPUT);
  
}


void loop()
{
  webSocket.loop();
  server.handleClient();
  MDNS.update();
  RecieveSerialCom();
//Serial.println(Mode);

    unsigned long currerntMillis = millis();
      if((currerntMillis - prevMillis) >=  intervalOff){

     
      
      
    
//      Serial.println(intervalOff);
              prevMillis = currerntMillis;
         
      } 
 

//delay(1000);
      
}
