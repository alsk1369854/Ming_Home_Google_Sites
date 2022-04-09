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
+ `S` => 訊號線: 接收高電壓(開)或低電壓(關)
+ `VCC` => 供電電壓(正級): 這邊接開發版輸出的 3V 直流電壓
+ `GND` => 接地(負級): 這邊接開發版的 GND 接地

+ `NO` => Open常開端: 未通電時與COM(公共端)形成迴路。
+ `NC` => Close常閉端: 通電時與COM(公共端)形成迴路。
+ `COM` => 公共端: 未通電時與NC(常開端)形成迴路，反之通電時與NO(常閉端)形成迴路。

### 繼電器原理圖

<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/物聯網/WiFi%20智能家電開關/images/電路圖.png)
</center>