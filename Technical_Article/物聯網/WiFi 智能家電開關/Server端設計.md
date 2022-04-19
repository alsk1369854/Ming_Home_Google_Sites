# Server端設計

> CH340 ESP8266 引腳圖 
> 
> Server端電路圖
> 
> Server端程式

<br/>


> ## CH340 ESP8266 引腳圖


<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/物聯網/WiFi%20智能家電開關/images/CH340_ESP8266_IO_引角圖.jpg)
</center>

<br/>

> ## Server端電路圖

<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/物聯網/WiFi%20智能家電開關/images/電路圖.png)
</center>

### 繼電器接腳解說
#### 接開發版
+ `S` => 訊號線: 接收高電壓(開)或低電壓(關)
+ `VCC` => 供電電壓(正級): 這邊接開發版輸出的 3V 直流電壓
+ `GND` => 接地(負級): 這邊接開發版的 GND 接地

#### 接控制電器
+ `NO` => Open常開端: 未通電時與COM(公共端)形成迴路。
+ `NC` => Close常閉端: 通電時與COM(公共端)形成迴路。
+ `COM` => 公共端: 未通電時與NC(常開端)形成迴路，反之通電時與NO(常閉端)形成迴路。

<br/>

### 繼電器原理圖

<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/物聯網/WiFi%20智能家電開關/images/繼電器原理圖.jpg)
</center>

<br/>

> ## 


<br/>

> ## Server 端程式
```c++

#include <ESP8266WiFi.h>

// 設定提供連線的 WiFi 名稱和密碼
#ifndef STASSID
#define STASSID "Handsome_Boys_229" // WiFi 名稱
#define STAPSK "88888888"           // WiFi 密碼
#define Network_Adapter_Company "Espressif Inc"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

// 設定接腳
const int manualSwitchPin = 4; // 設定手動開關pin腳
const int relayPin = 5;        // 設定繼電器pin腳

// 設定初始設備狀態
bool mainLightState = false;
bool manualSwitchState = false;

// 後台服務器聆聽端口: 80 Port
WiFiServer server(80);

// 初始化設定
void setup()
{
    // 序列埠監控視窗的鮑率 115200 bit/s
    Serial.begin(115200);

    // 設定繼電器訊號輸出腳為
    pinMode(relayPin, OUTPUT);

    // 設定手動開關接收訊號腳位
    pinMode(manualSwitchPin, INPUT);

    // 開啟初始化設定提示燈
    digitalWrite(LED_BUILTIN, 1);

    // manualSwitchState = digitalRead(manualSwitchPin);

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
    while (WiFi.status() != WL_CONNECTED)
    {
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

    // 關閉初始化設定提示燈
    digitalWrite(LED_BUILTIN, 0);
}

// 運行階段
void loop()
{
    // 如果手動按紐按下
    if (manualSwitchState == 1)
    {   
        // 切換主燈狀態 開 => 關; 關 => 開
        mainLightState = !mainLightState
        digitalWrite(relayPin, mainLightState);
        delay(1000);
    }

    // 檢查是否有 Client 建立連線
    WiFiClient client = server.available();
    if (!client)
    {
        return;
    }
    Serial.println(F("new client"));

    client.setTimeout(1500); // default is 1000

    // 讀取收到的 get 請求數據的第一行
    String req = client.readStringUntil('\r');
    Serial.println(F("request: "));
    Serial.println(req);

    // 解析 get 請求中攜帶的數據，並匹配操作
    if (req.indexOf(F("/ajaxMainLight/0")) != -1)
    {
        // 切換主燈狀態 開 => 關; 關 => 開
        mainLightState = !mainLightState;
    }
    else // 沒有任何匹配
    {
        Serial.println(F("invalid request"));
        mainLightState = digitalRead(relayPin);
    }

    // 依照上面匹配的數據來設定測試燈
    digitalWrite(relayPin, mainLightState);

    // 將請求剩下的數據讀完，不在做任何操作
    while (client.available())
    {
        client.read();
    }

    // 回傳數據給使用者，這邊是回傳一個 html 頁面
    client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"));
    client.print(F("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><link rel='icon' href='data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCA1NzYgNTEyIj48IS0tIEZvbnQgQXdlc29tZSBQcm8gNS4xNS40IGJ5IEBmb250YXdlc29tZSAtIGh0dHBzOi8vZm9udGF3ZXNvbWUuY29tIExpY2Vuc2UgLSBodHRwczovL2ZvbnRhd2Vzb21lLmNvbS9saWNlbnNlIChDb21tZXJjaWFsIExpY2Vuc2UpIC0tPjxwYXRoIGQ9Ik0zODQgNjRIMTkyQzg2IDY0IDAgMTUwIDAgMjU2czg2IDE5MiAxOTIgMTkyaDE5MmMxMDYgMCAxOTItODYgMTkyLTE5MlM0OTAgNjQgMzg0IDY0em0wIDMyMGMtNzAuOCAwLTEyOC01Ny4zLTEyOC0xMjggMC03MC44IDU3LjMtMTI4IDEyOC0xMjggNzAuOCAwIDEyOCA1Ny4zIDEyOCAxMjggMCA3MC44LTU3LjMgMTI4LTEyOCAxMjh6Ii8+PC9zdmc+'><link rel='apple-touch-icon-precomposed' href='data:image/png;base64,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'><link rel='apple-touch-startup-image' href='data:image/png;base64,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'><meta name='apple-mobile-web-app-title' content='MING Controller'><meta name='apple-mobile-web-app-capable' content='yes'><meta name='apple-mobile-web-app-status-bar-style' content='black-translucent'><meta name='viewport' content='width=device-width,initial-scale=1'><script src='https://unpkg.com/react@17/umd/react.development.js' crossorigin></script><script src='https://unpkg.com/react-dom@17/umd/react-dom.development.js' crossorigin></script><script src='https://unpkg.com/@babel/standalone/babel.min.js'></script><script src='https://unpkg.com/classnames@2.3.1/index.js'></script><script src='https://kit.fontawesome.com/8d3fcba981.js'></script><script src='https://cdn.jsdelivr.net/npm/axios/dist/axios.min.js'></script><title>MING Controller</title><style>body{margin:0;padding:0;font-family:monospace;background-color:#897f83}.main{background-color:#eae1d9;height:100vh;width:100vw;overflow:auto}.line{background-color:#6667748e;height:2px;margin:0 45px;border-radius:30px}.SwitchExecute{color:#fff;background-color:#c0a38b}.onIconColor{color:#9dbd69}.head{position:sticky;display:flex;justify-content:space-between;top:0;background-color:#897f83;height:auto;width:100%;border-radius:0 0 30px 30px}.head>.headText{display:flex;align-items:flex-end;height:120px;margin-left:30px;font-size:75px;font-weight:700;color:#fff}.refresh{display:flex;align-items:flex-end;margin:0 30px 23px 0;color:#fff;font-size:40px}.rotate{animation:rotation 2s infinite linear}@keyframes rotation{from{transform:rotate(0)}to{transform:rotate(359deg)}}.item,.title{height:65px}.title{display:flex;align-items:flex-end;justify-content:space-between;margin:0 20px 2px 20px;font-weight:700;color:#6667748e;font-size:20px}.item{display:flex;justify-content:center;margin:1px 3px}.item>a{display:flex;align-items:center;justify-content:space-between;height:100%;width:100%;border-radius:45px;padding:0 33px 0 20px;text-decoration:none;font-size:30px;font-weight:700}.item>.itemTextColor{color:#676872}</style><body><div id='root'></div><script type='text/babel'>class App extends React.Component {constructor(props){super(props);let itemExecute={};for(const[key]of Object.entries(props.StateData)){itemExecute={...itemExecute,[key]:false}}this.state={data:props.StateData,itemExecute,doRefresh:false}}refreshFn=()=>{this.setState({doRefresh:true});let url='http://'+this.props.IP;let setStateFn=()=>{this.setState({doRefresh:false})};this.updateSateDateFn(url,setStateFn.bind(this))};executeSwitchFn=(switchName)=>{let newItemExecute={...this.state.itemExecute,[switchName]:true};this.setState({itemExecute:newItemExecute});let url='http://'+this.props.IP+'/'+switchName+'/0';let setStateFn=()=>{newItemExecute={...newItemExecute,[switchName]:false};this.setState({itemExecute:newItemExecute})};this.updateSateDateFn(url,setStateFn.bind(this))};updateSateDateFn=(url,setStateFn)=>{axios.get(url).then((red)=>{let responseData=red.data;let itemList=responseData.split('const StateData={')[2].split('}')[0].split(',');let newStateData={};itemList.map((item)=>{let temp=item.split(':');if(temp[1]=='true'){newStateData={...newStateData,[temp[0]]:true}}else{newStateData={...newStateData,[temp[0]]:false}}});this.setState({data:newStateData});setStateFn()}).catch((error)=>{console.error(error)}).finally(()=>{console.log(url)})};render(){let{data,itemExecute,doRefresh}=this.state;const refreshIconClassNames=classNames({'fas fa-sync color-white':true,'rotate':doRefresh});const ajaxMainLightClassNames=classNames({'itemTextColor':!itemExecute.ajaxMainLight,'SwitchExecute':itemExecute.ajaxMainLight});const ajaxMainLightIconClassNames=classNames({'fas fa-lightbulb':true,'onIconColor':data.ajaxMainLight});return(<div><div className='main'><div className='head'><div className='headText'>MING</div><div className='refresh'><a onClick={this.refreshFn}><i className={refreshIconClassNames}></i></a></div></div><div className='title'><div>Room 228</div><div>State</div></div><div className='line'></div><div className='item'><a className={ajaxMainLightClassNames}id='ajaxMainLight'onClick={()=>{this.executeSwitchFn('ajaxMainLight')}}><div>Main Light</div><i id='ajaxMainLightIcon'className={ajaxMainLightIconClassNames}></i></a></div><div className='line'></div>{}<div className='title'></div></div></div>)}}"));
    // 回傳 Server端 IP給 Clinet端
    client.print(F("const IP='"));
    client.print(WiFi.localIP());
    client.print(F("';"));

    // 回傳當前所控制的設備狀態給 Clinet端
    client.print(F("const StateData={"));
    client.print(F("ajaxMainLight:"));
    client.print((mainLightState) ? F("false") : F("true"));

    // 添加新設備
    /* next item
    client.print(F(",mainLightState2:"));
    client.print((mainLightState) ? F("true") : F("false"));
    */

    // 將剩下的頁面傳完
    client.print(F("};ReactDOM.render(<App IP={IP} StateData={StateData}/>, document.getElementById('root'));</script>"));

    // 已完成回傳訊息給 Client 端，並斷開與 Client 的連線
    // 在監控視窗中打印以和 Client 端開連線
    Serial.println(F("Disconnecting from client"));

    // 繼續回去監聽等待下一次 Client 做連線
} 
```

<br/>

#### _END_