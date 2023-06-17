//<html>
//<head>
//  <script>
//    var Socket;
//    function init() {
//      Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
//      Socket.onmessage = function(event){
//         var obj = JSON.parse(event.data)
//       
//        document.getElementById("rxConsole").value += obj.device;
//         document.getElementById("ran").innerHTML = obj.temp;
//          document.getElementById("led").innerHTML = obj.hum;
//        console.log(obj.temp);
//          console.log(obj);
//       
//       //const js = JSON.parse()
//   
//         
//      }
//    }
//    function sendText(){
//      Socket.send(document.getElementById("txBar").value);
//      document.getElementById("txBar").value = "";
//    }
//    function sendon(){
//      Socket.send("#"+document.getElementById("on").value);
//    }    
//       function  sendoff(){
//      Socket.send("$"+document.getElementById("off").value);
//    }
//  </script>
//</head>
//<body onload="javascript:init()">
//  <div>
//    <textarea id="rxConsole"></textarea>
//    <p id="ran" ></p>
//    <p id="led"></p>
//  </div>
//  <hr/>
//  <div>
//    <input type="text" id="txBar" onkeydown="if(event.keyCode == 13) sendText();" />
//  </div>
//  <hr/>
//  <div>
//    <input type="number" min="0" max="60000" value="2000" id="on" oninput="sendon()" />
//     <input type="number" min="0" max="60000" value="2000" id="off" oninput="sendoff()" />
//  </div>  
//</body>
//</html>
