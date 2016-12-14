//wifi
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "bananahunter";
const char* password = "lightning";

ESP8266WebServer server(80);

char rBuf[50];
String webSite;


//website
void buildWeb(){
  webSite += "<html>";
  webSite+="<head>\n";
  webSite+="<meta charset='UTF-8'/>\n";
  webSite+="<title>Form Control RGB_LED</title>\n";
  webSite+="<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>";
  webSite+="<script>";
  webSite+="$(document).ready(function(){";
  webSite+="$(\"[type = range]\").change(function(){";
  webSite+="var redval = $(\"#red\").val();";
  webSite+="$(\"#red-text\").text(redval);";
  webSite+="});";
  webSite+="});";
  webSite+="</script>";
  webSite+="</head>\n";
  webSite += "<body>";
  webSite += "<h1>RGB LED Control form</h1>";
  webSite += "<form action=\"/form1\">";
  webSite += "<p>Red Color : <span id = \"red-text\">0</span></p>";
  webSite += "<input type=\"range\" id=\"red\" name=\"R-led\" min=\"0\" max=\"255\" value=\"0\">";
  webSite += "<input type=\"submit\" value=\"submit\"></form>";
  webSite += "</body></html>";
}

void handleRoot(){
  server.send(200,"text/html",webSite);
}

void handleLEDStatus(){
  int red_color = server.arg("R-led").toInt();
  Wire.beginTransmission(8);
//  analogWrite(LEDR,red_color);
  Wire.write(red_color);
  Wire.endTransmission();

  server.send(200,"text/html",webSite);
}

void handleNotFound(){
  server.send(404,"text/html","404 Error!");
}

void setup()
{  
  Serial.begin(115200);
  // put your setup code here, to run once:
  buildWeb();
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.on("/",handleRoot);
  server.on("/form1",handleLEDStatus);
  server.onNotFound(handleNotFound);
  Wire.begin(4,5);
  
  server.begin();
  Serial.println(WiFi.localIP());  
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();               //website
}
