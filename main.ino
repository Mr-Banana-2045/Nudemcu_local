#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
char *name = "moz";
char *pass = "12345678";

bool ledState = HIGH;

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<html lang='en'><title>LED Control</title><meta name='viewport' content='width=device-width, initial-scale=1'><meta charset='UTF-8'><body><style>body{background:black; text-align:center;} h1{color:white; margin-top:10px; font-weight:900;} button{background:white; padding:10px; font-size:25px; border:none; margin-top:5px; font-weight:300;} button:hover{background: #AAAAAA} hr{margin-left: 30px; margin-right:30px;} p,li{color:white; font-size:20px;} .st{text-align: left; margin-left: 20px;}</style><code><h1>LED Control</h1><hr><form action=\'/on' method=\'get\'><button onclick='ledon()' style='margin-right:5px;'>ON LED</button></form><form action=\'/off' method=\'get\'><button onclick='ledoff()'>OFF LED</button></form><br><div class='st'><p>online Client :</p><li style='margin-left:30px;'>IP Address : <a id='address' style='color:white; font-size:20px; font-weight:900;'></a></li><br><li style='color:white; font-size:20px; font-weight:500; margin-left:30px;'>LED : <a id='led' style='color:white; font-size:20px; font-weight:900;'></a></li><li style='color:white; margin-top: 20px; font-size:20px; font-weight:500; margin-left:30px;'>Client information : <a id='info' style='color:white; font-size:20px; font-weight:900;'></a></li></div></code><script>function ledon() {document.getElementById('led').innerText = 'ON';} function ledoff() {document.getElementById('led').innerText = 'OFF';} document.getElementById('info').innerText = navigator.userAgent; document.getElementById('address').innerText = window.location.href; </script></body></html>");
}
void handon() {
  digitalWrite(LED_BUILTIN, LOW);
  server.send(200, "text/html", "<html lang='en'><title>LED Control</title><meta name='viewport' content='width=device-width, initial-scale=1'><meta charset='UTF-8'><body><style>body{background:black; text-align:center;} h1{color:white; margin-top:10px; font-weight:900;} button{background:white; padding:10px; font-size:25px; border:none; margin-top:5px; font-weight:300;} button:hover{background: #AAAAAA} hr{margin-left: 30px; margin-right:30px;} p,li{color:white; font-size:20px;} .st{text-align: left; margin-left: 20px;}</style><code><h1>LED Control</h1><form action=\'/on' method=\'get\'><button onclick='ledon()' style='margin-right:5px;'>ON LED</button></form><form action=\'/off' method=\'get\'><button onclick='ledoff()'>OFF LED</button></form><br><div class='st'><p>online Client :</p><li style='margin-left:30px;'>IP Address : <a id='address' style='color:white; font-size:20px; font-weight:900;'></a></li><br><li style='color:white; font-size:20px; font-weight:500; margin-left:30px;'>LED : <a id='led' style='color:white; font-size:20px; font-weight:900;'>ON</a></li><li style='color:white; margin-top: 20px; font-size:20px; font-weight:500; margin-left:30px;'>Client information : <a id='info' style='color:white; font-size:20px; font-weight:900;'></a></li></div></code><script>function ledon() {document.getElementById('led').innerText = 'ON';} function ledoff() {document.getElementById('led').innerText = 'OFF';} document.getElementById('info').innerText = navigator.userAgent; document.getElementById('address').innerText = window.location.href; </script></body></html>");
}
void handoff() {
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, "text/html", "<html lang='en'><title>LED Control</title><meta name='viewport' content='width=device-width, initial-scale=1'><meta charset='UTF-8'><body><style>body{background:black; text-align:center;} h1{color:white; margin-top:10px; font-weight:900;} button{background:white; padding:10px; font-size:25px; border:none; margin-top:5px; font-weight:300;} button:hover{background: #AAAAAA} hr{margin-left: 30px; margin-right:30px;} p,li{color:white; font-size:20px;} .st{text-align: left; margin-left: 20px;}</style><code><h1>LED Control</h1><form action=\'/on' method=\'get\'><button onclick='ledon()' style='margin-right:5px;'>ON LED</button></form><form action=\'/off' method=\'get\'><button onclick='ledoff()'>OFF LED</button></form><div class='st'><br><p>online Client :</p><li style='margin-left:30px;'>IP Address : <a id='address' style='color:white; font-size:20px; font-weight:900;'></a></li><br><li style='color:white; font-size:20px; font-weight:500; margin-left:30px;'>LED : <a id='led' style='color:white; font-size:20px; font-weight:900;'>OFF</a></li><li style='color:white; margin-top: 20px; font-size:20px; font-weight:500; margin-left:30px;'>Client information : <a id='info' style='color:white; font-size:20px; font-weight:900;'></a></li</div></code><script>function ledon() {document.getElementById('led').innerText = 'ON';} function ledoff() {document.getElementById('led').innerText = 'OFF';} document.getElementById('info').innerText = navigator.userAgent; document.getElementById('address').innerText = window.location.href; </script></body></html>");
}
void handleLED() {
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
  server.send(200, "text/plain", ledState ? "LED ON" : "LED OFF");
}
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledState);
  WiFi.softAP(name, pass);
  IPAddress ip = WiFi.softAPIP();
  Serial.print(ip);
  server.on("/", HTTP_GET, handleRoot);
  server.on("/led", handleLED);
  server.on("/on", HTTP_GET, handon);
  server.on("/off", HTTP_GET, handoff);
  server.begin();
  Serial.print("Started Server :D");
}

void loop() {
  server.handleClient();
}
