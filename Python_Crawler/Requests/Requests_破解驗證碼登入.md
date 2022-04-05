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


<br/>

獲取並分析提交登入攜帶的數據

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

<br/>

在網頁中找到驗證碼請求地址


<br/><br/>

> ## 製作 session 物件，將我們的的請求變成同一個物件
```python
# 製作一個 session 物件
session = requests.session()

# 獲取網頁數據源碼
request_login_page = session.get(url=login_page_url, headers=headers)

# 獲取字串型式的 html 源碼
login_page_text = request_login_page.text
```

<br/><br/>

> ## 

