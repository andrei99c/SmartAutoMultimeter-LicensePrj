#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* mySsid = "AMP Meter";
IPAddress ip(10,10,10,10);
IPAddress gateway(10,10,10,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
String text = "";
//double data;
String data; 



void setup(void){
// pinMode(A0, INPUT);
 Serial.begin(9600);
 WiFi.softAPConfig(ip, gateway, subnet);
 WiFi.softAP(mySsid);
 delay(1500);

 server.on("/data.txt", [](){
   text = (String)data;
   server.send(200, "text/html", text);
 });
 server.on("/", [](){
   page = "<h1>Web Server for read current from sensor</h1><br/><br/><h1>Current:</h1> <h1 id=\"data\">""</h1>\r\n";
   page += "<script>\r\n";
   page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 800);\r\n";
   page += "function loadData(url, callback){\r\n";
   page += "var xhttp = new XMLHttpRequest();\r\n";
   page += "xhttp.onreadystatechange = function(){\r\n";
   page += " if(this.readyState == 4 && this.status == 200){\r\n";
   page += " callback.apply(xhttp);\r\n";
   page += " }\r\n";
   page += "};\r\n";
   page += "xhttp.open(\"GET\", url, true);\r\n";
   page += "xhttp.send();\r\n";
   page += "}\r\n";
   page += "function updateData(){\r\n";
   page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
   page += "}\r\n";
   page += "</script>\r\n";
   server.send(200, "text/html", page);
});
 
 server.begin();
 Serial.println("Web server started!");
}
 
void loop(void){
 //data = analogRead(A0);
 //Serial.print(data);
// int datafromarduino = Serial.read();
// data = Serial.println(datafromarduino);
 //data = Serial.readStringUntil('\n');
 
 data = Serial.readStringUntil('\n');
 Serial.println(data);
// delay(100);
 server.handleClient();
}
