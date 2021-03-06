#include <ESP8266WiFi.h>

int vapor = D7;

String readLine="";
String sky = "<sky>";
String s = "";
String now = "";
String pubDate = "";

const char* ssid = "LG Q7_2795";
const char* password ="seon1az7h";
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
  pinMode(vapor, INPUT);
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
          delay(180000);
          break;
        }
      }
      if (readLine.indexOf("data seq") > -1) {
        now = readLine;
      }
      if (now.indexOf("\"0\"")>-1 && readLine.indexOf("<sky>") > -1){
        s = readLine.substring(readLine.indexOf("<sky>") + sky.length(),readLine.indexOf("</sky>"));
        if ( s.toInt()>1){
        pinMode(vapor, OUTPUT);
        digitalWrite(vapor,1);
          }
           else {
            pinMode(vapor, INPUT);
         }
        }
      }
    }
  }
