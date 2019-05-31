#include<ESP8266WiFi.h>

String readLine = ""; //서버에서 전송된 데이터 String저장
String wfEn = "<WfEn>";
String s = "";
String now = "";
String pubDate = "";

const char* ssid = "";
const char* password = "";
const char* host = "www.kma.go.kr";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
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
       if (readLine.indexOf("data seq") > -1){
        now = readLine;
       }
       if (now.indexOf("\"0\"") > -1 && readLine.indexOf("<wfEn>")>-1{
        s = readLine.substring(readLine.indexOf("<wfEn>")+wfEn.length(), readLine.indexOf("<\wfEn"));
        Serial.println(s);
       }
      }
     }
    }
