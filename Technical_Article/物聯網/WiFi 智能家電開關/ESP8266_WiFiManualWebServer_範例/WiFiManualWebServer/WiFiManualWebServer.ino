/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

// 導入 ESP8266WiFi 庫
#include <ESP8266WiFi.h>

// 設定提供連線的 WiFi 名稱和密碼
#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

// 後台服務器聆聽端口: 80 Port
WiFiServer server(80);

// 初始化設定
void setup() {
  // 序列埠監控視窗的鮑率 115200 bit/s
  Serial.begin(115200);

  // 設定測試燈 13 PIN，為輸出裝置
  pinMode(LED_BUILTIN, OUTPUT);
  // 給測試燈低電壓 (燈暗)
  digitalWrite(LED_BUILTIN, 0);

  // 打印連接到的 WiFi 名稱
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  // 設定 WiFi的模式為 STA(Station)，共有 WIFI_AP、WIFI_STA、WIFI_AP_STA、WIFI_OFF
  WiFi.mode(WIFI_STA);
  // 連線 WiFi
  WiFi.begin(ssid, password);

  // 等待 WiFi連線成功
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // 開啟 Server
  server.begin();
  Serial.println(F("Server started"));

  // 在監控視窗中打印出自己的 IP 位置
  Serial.println(WiFi.localIP());
}

// 運行階段
void loop() {
  // 檢查是否有 Client 建立連線
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println(F("new client"));

  client.setTimeout(5000); // default is 1000

  // 讀取收到的 get 請求數據的第一行
  String req = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(req);

  // 解析 get 請求中攜帶的數據，並匹配操作
  int val;
  if (req.indexOf(F("/gpio/0")) != -1) {
    // 給低電壓 (燈暗)
    val = 0;
  } else if (req.indexOf(F("/gpio/1")) != -1) {
    // 給高電壓 (燈亮)
    val = 1;
  } else {
    // 沒有任何匹配
    Serial.println(F("invalid request"));
    val = digitalRead(LED_BUILTIN);
  }

  // 依照上面匹配的數據來設定測試燈 
  digitalWrite(LED_BUILTIN, val);

  // 將請求剩下的數據讀完，不在做任何操作
  while (client.available()) {
    client.read();
  }

  // 回傳數據給使用者，這邊是回傳一個 html 頁面
  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now "));
  client.print((val) ? F("high") : F("low"));
  client.print(F("<br><br>Click <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/1'>here</a> to switch LED GPIO on, or <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/0'>here</a> to switch LED GPIO off.</html>"));

  // 已完成回傳訊息給 Client 端，並斷開與 Client 的連線
  // 在監控視窗中打印以和 Client 端開連線
  Serial.println(F("Disconnecting from client"));
  
  // 繼續回去監聽等待下一次 Client 做連線
}
