# Urllib Post Request

> Post請求
> 
> 請求參數會包在請求的 Request 中
>
> 請求的參數必須經過編碼
>
> 下面示範透過發送 `Post請求` 獲得中文名的英文翻譯
>
> [英文名字翻譯|翻譯網](https://name.longwin.com.tw/name.php)

<br/>

> ## _前置準備工作_

```python
# import urllib lib, Python 原生就有
# 用於包裝 Request
import urllib.request
# 用於將參數編碼為 unicode
import urllib.pares

# 有時候我們需要不驗證網頁ssl認證才可運作
# 導入 ssl 庫, Python 原生就有
import ssl
# 全部請求不驗證 ssl
ssl._create_default_https_context = ssl._create_unverified_context

```

<br/>

> ## _分析查詢網站_
### 找到請求地址
![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/Python_Crawler/Urllib/images/find_post_request_url.png)

<br/>

> ## _開始寫程式_
```python
# 設定請求翻譯地址
translate_url = 'https://name.longwin.com.tw/name.php'

# 設定請求頭
headers = {
    'user-agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.60 Safari/537.36',
    # 大多數反爬可以透過傳 cookie 的方式解決
    'cookie': '_ga=GA1.4.24384683.1594388240; SEARCH_SAMESITE=CgQI-5MB; OTZ=6415391_24_24__24_; SID=IAic3DvLSl5seswjfLPmydhZTkobOWi-t8OzXh2cb5jaNt2Wr1G1LIYEvbcQD4_ZaTQEgA.; __Secure-1PSID=IAic3DvLSl5seswjfLPmydhZTkobOWi-t8OzXh2cb5jaNt2Wckz3OEpYcTz9Uzf6YWhaBQ.; __Secure-3PSID=IAic3DvLSl5seswjfLPmydhZTkobOWi-t8OzXh2cb5jaNt2WRYO3uQ5E8VF3p1AT0l1V0A.; HSID=AToS0P-FBtoQFZOXC; SSID=AnwAE10v6fIVQXJ4A; APISID=ONdrdpza65xa51_l/Akz2CZXOFyllz38V-; SAPISID=bQDGT9t7zGsyBSxX/ASvjbrEiW8Dv90sLj; __Secure-1PAPISID=bQDGT9t7zGsyBSxX/ASvjbrEiW8Dv90sLj; __Secure-3PAPISID=bQDGT9t7zGsyBSxX/ASvjbrEiW8Dv90sLj; _gid=GA1.4.1954128954.1649053448; NID=511=mFj2w-QAy2mX5dIrBGMF57PDyd-5jwkTkA1eOEoH_XVV8p21oETcy5rda3m6_FjNksaXNbo_pmX5ByNgCptGR8ljDZ6wq_YPRD6z1qtrqMKgB08xGKv9lJI2Pe-J8WwwexVV0lLitegs57rE1JTAQ1lLunauZhzToOcSbH76GVGZRRdgAeumOcegb-sRJ9mHIuptJ6IwANXC9hnyW6ATo6ypUW_jdUshKYHm8v6lvDj8rqu2lbYJBSsKoJ2CTWlNWKEMvFECX3Wjcdu9O-G_X-yzt717UuAsbp2ekJtx2vwYvX_ay1qTjKA1p1GWxAmSywefvlfcq6wynPhjrV1uyVFPfM7TYpt-kqWIQ0Nq6V9I51gPLVps'
}

# 設定攜帶參數並轉換成 Unicode 編碼型式
form_data = {
    'query': '梁家銘',
    'submit': '查詢'
}
form_data = urllib.parse.urlencode(form_data)
# 打印 Before encode form_data 數據
print('@Before encode form_data: ' + str(form_data))
# output
# @Before encode form_data: query=%E6%A2%81%E5%AE%B6%E9%8A%98&submit=%E6%9F%A5%E8%A9%A2

# 請求的參數需要經過編碼 
form_data = form_data.encode('utf-8')
# 打印 After encode form_data 數據
print('@After encode form_data: ' + str(form_data))
# output
# @After encode form_data: b'query=%E6%A2%81%E5%AE%B6%E9%8A%98&submit=%E6%9F%A5%E8%A9%A2'

# 定制_Request
request = urllib.request.Request(url=translate_url, data=form_data, headers=headers)

# 模擬瀏覽器發送請求
response = urllib.request.urlopen(request)

# 讀取並解碼回傳解果
content = response.read().decode('utf-8')

# 打印 content 數據
print(content)

```

<br/>

> ## Output
```html
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>英文名字翻譯|翻譯網</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta name="description" content="翻譯網, 英文名字翻譯,中文唸法,拼音翻譯,繁簡互轉,整句翻譯 的工具站">
<meta name="keywords" content="翻譯,英文名字,中文唸法,拼音,繁簡互轉,整句翻譯">
<meta name="robots" content="all">
<meta name="author" content="Tsung">
<meta name="referrer" content="origin">
<meta name="verify-v1" content="256ijhvnJ7WW17nF88xEOv7/bxd0MP5Lq88LmYGkdV8=">
<link rel="shortcut icon" href="//name.longwin.com.tw/images/favicon.ico">
<!-- <link rel="stylesheet" href="http://yui.yahooapis.com/2.8.2/build/reset-fonts-grids/reset-fonts-grids.css"> -->
<link rel="stylesheet" href="/A.reset-fonts-grids.css.pagespeed.cf.m69kQMrmqF.css" aysnc>
<link rel="stylesheet" href="/A.style.css.pagespeed.cf.2IjzucBftp.css" media="screen" aysnc>
<script>(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)})(window,document,'script','https://www.google-analytics.com/analytics.js','ga');ga('create','UA-101810-3','auto');ga('send','pageview');</script>
<script type="text/javascript">(function(){var ga=document.createElement('script');ga.type='text/javascript';ga.async=true;ga.src=('https:'==document.location.protocol?'https://':'http://')+'stats.g.doubleclick.net/dc.js';var s=document.getElementsByTagName('script')[0];s.parentNode.insertBefore(ga,s);})();</script>
<script type="text/javascript">window.google_analytics_uacct="UA-101810-3";</script>
<!-- 自動廣告 -->
<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
<script>(adsbygoogle=window.adsbygoogle||[]).push({google_ad_client:"ca-pub-2833110699572522",enable_page_level_ads:true});</script>
<!-- microsoft clarity -->
<script type="text/javascript">(function(c,l,a,r,i,t,y){c[a]=c[a]||function(){(c[a].q=c[a].q||[]).push(arguments)};t=l.createElement(r);t.async=1;t.src="https://www.clarity.ms/tag/"+i;y=l.getElementsByTagName(r)[0];y.parentNode.insertBefore(t,y);})(window,document,"clarity","script","3y4ohl8kgv");</script>
</head>
<body>
<div id="logo">
<h1><a accesskey="H" href="https://name.longwin.com.tw/" title="翻譯網首頁">翻譯網</a></h1>
<span>贊助: <a href="https://www.longwin.com.tw" title="隆瑩寢具精品">隆瑩寢飾精品</a></span>
<p>此站提供的服務隨時在增加，也不曉得會加什麼，總之如果有什麼需求，都可以跟我反應，能力範圍內，會想辦法做出來的。對本人有什麼興趣，歡迎參觀 <a href="http://blog.longwin.com.tw/" title="Tsung's Blog">Tsung's Blog</a></p>
</div>
<div id="nav">
<ul>
<li><a href="name.php" title="英文名字翻譯"><span>英文名字翻譯</span></a></li>
<li><a href="word.php" title="查中文字唸法, 拼音翻譯"><span>文字翻譯</span></a></li>
<li><a href="name2passport.php" title="護照英文名字翻譯"><span>護照英文名字翻譯</span></a></li>
<li><a href="twcn.php" title="正體中文轉簡體中文"><span>繁簡、簡繁轉換</span></a></li>
<li><a href="word2big.php" title="文字放大, 轉換"><span>文字放大</span></a></li>
<li><a href="porter.php" title="動詞原型轉換"><span>動詞原型轉換</span></a></li>
<li><a href="nos.php" title="文字筆劃數"><span>文字筆劃數(吉凶)</span></a></li>
<li><a href="nod.php" title="諸葛神算"><span>諸葛神算</span></a></li>
<li><a href="life_weight.php" title="命格重量"><span>命格重量</span></a></li>
</ul>
</div>
<blockquote id="desc">
<h2>英文名字翻譯</h2>
<span>功能說明: 此功能會將您輸入的中文名字, 轉換成英文名字的拼音, 依 <a href="http://www.merica.com.tw/phonetic_table.asp" title="國語羅馬拼音對照表">國語羅馬拼音對照表</a> 來製作.</span>
</blockquote>
<script type="text/javascript">google_ad_client="pub-2833110699572522";google_ad_width=728;google_ad_height=15;google_ad_format="728x15_0ads_al_s";google_ad_channel="";</script>
<script type="text/javascript" src="//pagead2.googlesyndication.com/pagead/show_ads.js"></script>
<div id="div_form">
<form method="post" action="name.php">
請輸入您的中文名字 <input type="text" name="query" value="梁家銘" tabindex="1" autofocus>(簡體, 繁體皆可輸入)
<input type="submit" name="submit" value="查詢" tabindex="2">
</form>
</div>
<div id="result">
正體中文: 梁家銘 <br/>您好, 您的英文名字是 Liang Gu Jia Ming , Liang Ku Chia Ming 挑一個喜歡的用吧!<br/><br/>PS: 請注意可能有破音字的狀況, 翻譯出來的字數會可能會多於自己的名字, 請自行移除<br/>若不知該移除哪字, 可用 <a href="word.php" title="字串詳細翻譯">字串詳細翻譯</a> 查詢</div>
<script type="text/javascript" src="//click.longwin.com.tw/js/click_min.js?hash=e3ecde2fc9406853a123abc4389e2590"></script>
<div class="fsapromo" id="fsapromo-float-d" model="300x250"></div>
<script defer src="https://ad.sitemaji.com/ysm_namelongwin.js"></script>
</body>
</html>
```

<br/>

### _End_
