#include<ESP8266WiFi.h>

const char* ssid = "LG Q7_2795";
const char* password = "seon1az7h";
const char* host = "www.kma.go.kr";
String s;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("Connecting to");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status()!=WL_CONNECTED){
  delay(500);
  Serial.print(".");
}

Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address:");
Serial.println(WiFi.localIP());
}


void loop() {
  // put your main code here, to run repeatedly:
    WiFiClient client;
    if(client.connect(host,80)){
      client.print(String("GET")+"/wid/queryDFSRSS/jsp?zone=1123066000"
      + "HTTP/1.1\r\n" + "Host: " + host +"\r\n" +
      "Connection : close\r\n\r\n");
      while(!client.available()); //연결완료 될때까지 반복문 돌고  
      while(client.available()) {
      s= client.readStringUntil('\n'); //enter는 한 줄 하고 있음. 나올때까지 계속 읽는 것. 한 줄씩 계속 읽음
      //시리얼 모니터 창에 한 줄 씩 적어주겠다
      
      Serial.println(s);
      
    }
  delay(60000); //매번 받아 올 필요 없으니, (3시간~1시간마다 새로고침) 그냥 많이 딜레이 줌. 길게 줄 필요 x
  }
}
