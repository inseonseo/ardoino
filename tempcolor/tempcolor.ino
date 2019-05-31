#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

#define PIN D5
#define NUMPIXELS 144

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

String readLine="";
String temp = "<temp>";
String s = "";
String now = "";
String pubDate = "";

int tp;

const char* ssid = "";
const char* password ="";
const char* host = "www.kma.go.kr";

void setup() {
  
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() !=WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  pixels.begin();
}


void loop() {
  WiFiClient client;
  if(client.connect(host,80)){
    client.print(String("GET")+"/wid/queryDFSRSS/jsp?zone=1123066000"
    + "HTTP/1.1\r\n" + "Host: " + host +"\r\n" +
    "Connection : close\r\n\r\n");
    while(!client.available());
    while(client.available()) {
      readLine = client.readStringUntil('\n');
      if (readLine.indexOf("pubDate") > -1) {
        if (pubDate != readLine) {
          pubDate = readLine;
        }
        else{
          Serial.println("Not Updated");
          delay(180000);
          break;
        }
      }
      if (readLine.indexOf("data seq") > -1) {
        now = readLine;
      }
      if (now.indexOf("\"0\"")>-1 && readLine.indexOf("<temp>") > -1){
        s = readLine.substring(readLine.indexOf("<temp>") + temp.length(), readLine.indexOf("</temp>"));
        tp = s.toInt();
        if ( tp<=15){
          for (int i=0; i<NUMPIXELS; ++i) {
            pixels.setPixelColor(i, pixels.Color(0,60,80));
          }
          pixels.show();
        }
        else if (tp<=24){
          for ( int i=0; i<NUMPIXELS; ++i){
            pixels.setPixelColor(i, pixels.Color(60,80,40));
          }
          pixels.show();
          }
           else {
            for ( int i=0; i<NUMPIXELS; ++i){
              pixels.setPixelColor(i, pixels.Color(80,20,0));
            }
            pixels.show();
          }
         }
        }
      }
    }
