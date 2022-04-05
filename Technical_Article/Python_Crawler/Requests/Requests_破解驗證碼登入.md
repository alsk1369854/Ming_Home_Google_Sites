# Requests 破解驗證碼登入

> 這裡我們將使用 requests 中的 session() 方法將我們的的請求變成同一個物件
>
> 目的是為了讓驗證碼作用領域與我們提交的領域相對應
> 
> 下面將演示在爬蟲中如何破解驗證碼進行登入
>

<br/>
<br/>

> ### _前置作業_
安裝 requests 與 bs4
```shell
# 用於發送請求
pip install requests

# 用於解析 html 標籤
pip install bs4 
```

Python 準備作業
```python
# 導入 requests 庫
import requests

# 導入 BeautifulSoup
from bs4 import BeautifulSoup

# 設定我們登入的頁面網址
login_page_url = 'https://sso.nknu.edu.tw/userLogin/login.aspx?cUrl=/default.aspx'

# 製作請求頭
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.60 Safari/537.36'
}

```

<br/><br/>

## 分析登入網頁

利用登入失敗獲取登入請求

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/Python_Crawler/Requests/images/find_login_submit_url.png)

<br/>

獲取並分析提交登入攜帶的數據

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/Python_Crawler/Requests/images/find_login_form_data.png)

```python
form_data = {
    '__EVENTTARGET': '',
    '__EVENTARGUMENT': '',
    '__VIEWSTATEENCRYPTED': '',

    # 頁面上找看不到: 通常就存放在網頁源碼裡
    # 動態的變數 => 找網頁源碼
    '__VIEWSTATE': "?",

    # 動態的變數 => 找網頁源碼
    '__VIEWSTATEGENERATOR': "?",

    # 學號
    'uLoginID': '學號',

    # 密碼
    'uPassword': '密碼',

    # 驗證碼
    'uAuthorizationCodeInput': '驗證碼',

    'uLogin': '登入',
    'Hidden1': '',
    'uGoogleToken': '',
    'uLoginID2': '',
}
```

<br/>

在網頁中找到 __VIEWSTATE __VIEWSTATEGENERATOR 數據

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/Python_Crawler/Requests/images/find_form_data_value.png)

<br/>

在網頁中找到驗證碼請求地址
在網頁中找到 __VIEWSTATE __VIEWSTATEGENERATOR 數據

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/Python_Crawler/Requests/images/find_login_imgCode_url.png)

<br/><br/>

> ## 開始寫程式

<br/><br/>

> ### 製作 session 物件，將我們的的請求變成同一個物件
```python
# 製作一個 session 物件
session = requests.session()

# 獲取網頁數據源碼
request_login_page = session.get(url=login_page_url, headers=headers)

# 獲取字串型式的 html 源碼
login_page_text = request_login_page.text
```

<br/><br/>

> ### 利用 BeautifulSoup 解析出我們需要的數據

```python
# 使用 BeautifulSoup 解析獲取到的網頁 html 源碼
soup = BeautifulSoup(login_page_text, 'lxml')

# 獲取 __VIEWSTATE 值
viewstate = soup.select('#__VIEWSTATE')[0].attrs.get('value')
# 打印 __VIEWSTATE 值
print('@__VIEWSTATE: ' + viewstate)
# output
# @__VIEWSTATE: 9BFVm/9yljVz4M5yKl6iKBgLeuFG3maa9WAjvX/iqUmUsSPIQgS80nskPqwYoHYtgtWNSPLyfBG1QtuF2tj5LrKcf6/l2WKY79hY0fHa4js+VVKlJCFau+FUlg9LHx2NLysamKcDM4KZyoPzqIzfMAYkUxU6doeQpsjvZ6FVN8pa4Qs5IZtmcX88CCaBipLMCjZrNrw6Un362Iy+6njc6PMfCktKnvruoQXB4+VEPMKi22lRiDKxAuVKbQxd8f1hTzW0oqoyKjBUQDAz6ASnFfg7J0uDq+8PvcqYaOIxQN/Rs9xC6ZqLzYKnDeV7mwO5og5xH9+gFVUhgm8r+m/qKTZLTchp5mZiAByTFGOQ05lp9H4CwgLy43nlJ/gCGOwNNLsPpcF6FS3W3+rVrGsRM8b6hZmp9NbDfq/VYpNroSrH7zMnFXxYGWfhBZY+QIwG1+kFYWQXuLVxHJQkm0CoJagPe5cLHPZ/gqUufRx2utWgCqaVntA5awopLyGlF7vFxQrxHen9PlWKeY9wdR3ZrpDnYO/0Gdd3gBuBSUySULbEckBwZrTbgH/fuQpIRqefP+PyQoMowxHqiUp2Oq4dGmexcQ0spZi3OI9uAlOX2VUc/rH7jAifAAjls4KElBMh4QRK9spMVuSloiHW+W38LDHoQfUIwKi8eyf8s+ja2gU8rwCVYCxDh2FAnDit+QukLni2UJD2N6ZYfaTlRy/35i1KL17wnrcsovpaBHb6AT2fM3itvMtPJr1wgfG7+JEecoUPvXA+KNPvXEMcZE3U3IhgJbn2uppKVRbu2G8pQIK8MhdLQPNmD9TEmxCdu4hHnn7meGSQxP2HuAmWZYHq7MkTgVZXgaCP/z3tSETu2YHskGvZz758ihz8acjNf0pNc2o0zi6zcRbpbR6n5kFFGIOwaze09bWWcPyA1rrjzpXiAjkzxn9S/2sxBGCZFUHIMuP1jVZdWcyO3pnWc50bHzpxthI30/aD//OXIoZdiN/VHuftb+OQJh7CfqDnURllLW0rl5YCTE0gzZDyD3MXYabNjOqiMegNKuS0EnLNytCPXk8dvfKPOZPwBfJxF9MtHwTzTw==


# 獲取 __VIEWSTATEGENERATOR
viewstategenerator = soup.select('#__VIEWSTATEGENERATOR')[0].attrs.get('value')
# 打印 __VIEWSTATEGENERATOR 值
print('@__VIEWSTATEGENERATOR: ' + viewstategenerator)
# output
# @__VIEWSTATEGENERATOR: D84C7206


# 獲取 驗證碼圖片 (此時的地址值有後半段) /userLogin/login.aspx?cSec=31&cFunction=img
login_img_code = soup.find(attrs={"title": "*"}).get('src')
# 組合上地址頭，使其成為完整地址
login_img_code_url = 'https://sso.nknu.edu.tw' + login_img_code
# 打印 驗證碼 請求地址
print('@login_img_code_url: ' + login_img_code_url)
# output
# @login_img_code_url: https://sso.nknu.edu.tw/userLogin/login.aspx?cSec=31&cFunction=img

```

<br/><br/>

> ### 下載驗證碼圖片到本地並輸入驗證碼

```python
# ** 注意 ** 
# 這邊要使用前面創建的 session 做請求發送
# 發送獲取驗證碼圖片請求
response_login_img_code = session.get(login_img_code_url, headers=headers)

# ** 注意 **
# 此時要使用 .content 二進制數據， 因為我們要下載圖片
login_img_code_content = response_login_img_code.content

# 下載驗證碼圖片到本地
with open('login_img_code.jpg', 'wb')as fp:
    fp.write(login_img_code_content)

# 查看下載的驗證碼圖片並輸入驗證碼 (有時IDE顯示比較慢，可以去實體目錄中查看)
input_login_img_code = input('輸入驗證碼: ')

```

> ### 發送登入請求
```python
# 設定我們上面找到的登入提交請求地址
login_submit_url = 'https://sso.nknu.edu.tw/userLogin/login.aspx?cUrl=%2fdefault.aspx'

# 定制登入的攜帶參數
login_form_data = {
    '__EVENTTARGET': '',
    '__EVENTARGUMENT': '',
    '__VIEWSTATEENCRYPTED': '',
    '__VIEWSTATE': viewstate,
    '__VIEWSTATEGENERATOR': viewstategenerator,
    'uLoginID': '410877033',
    'uPassword': '********',
    'uAuthorizationCodeInput': input_login_img_code,
    'uLogin': '登入',
    'Hidden1': '',
    'uGoogleToken': '',
    'uLoginID2': '',
}

# ** 注意 ** 
# 這邊要使用前面創建的 session 做請求發送
# 發送登入請求
response_login_submit = session.post(login_submit_url, data=login_form_data, headers=headers)

# 將登入後的畫面使用字串型式讀出
content = response_login_submit.text

# 將數據寫入 student.html 中以便確認是否登入成功
with open('student.html', 'w', encoding='utf-8')as fp:
    fp.write(content)
```

<br/><br/>

> ## 最後下載的 student.html 畫面

### **End**


