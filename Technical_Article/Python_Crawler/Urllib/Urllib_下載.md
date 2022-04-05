# Urllib Download

> 網頁下載
> 
> 圖片下載 
> 
> 影片下載

<br/>

> ### _下載前置作業_

```python
# 導入 urllib 庫
import urllib.request

# 必要時可使用忽略 ssl 驗證
import ssl
ssl._create_default_https_context = ssl._create_unverified_context

# url => 下載路徑
# filename => 下載後的文件命名
url = 'http://xxx.xxx'
filename = 'download_filename.html'
urllib.request.urlretrieve(url, filename)

# 下載後的當案會出現在專案的目錄內
```

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/Python_Crawler/Urllib/images/download_file_storage_location.png)

<br/><br/>

> ## 網頁下載

```python
# 設定網頁地址
url_web_page = 'https://sites.google.com/view/chiamingliang/about-ming'

# 下載網頁
urllib.request.urlretrieve(url_web_page, 'about_ming.html')
```

<br/><br/>

> ## 圖片下載

```python
# 設定圖片來源地址
url_demo_img = 'https://lh4.googleusercontent.com/VlEG9nDlEsojAvqYvgU9C2ajETFSX76cMY1Gt4ynw9glmzFJ90EP1uv6oFUyuLPbfOJnTkaPHMCxIQOJgcXMFokKZyf43WQWNrxVabQewvR9kYwdwNhbjGXsGVRxng7OfA=w1280'

# 下載圖片 
urllib.request.urlretrieve(url=url_demo_img, filename='demo_img.png')
```

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/Python_Crawler/Urllib/images/download_image_demo.png)

<br/><br/>

> ## 影片下載

```python
# 設定影片來源地址
url_demo_video = 'https://vd4.bdstatic.com/mda-nc9641cs73ae8isf/sc/cae_h264_delogo/1646886893879862123/mda-nc9641cs73ae8isf.mp4?v_from_s=hkapp-haokan-nanjing&auth_key=1649067774-0-0-c583d9124b7e9ca8f420ff5376fede13&bcevod_channel=searchbox_feed&cd=0&pd=1&pt=3&logid=3174775469&vid=13845466462917644178&abtest=100815_2-101454_3-17451_1&klogid=3174775469'

# 下載影片
urllib.request.urlretrieve(url_demo_video, 'demo_video.mp4')
```

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/Python_Crawler/Urllib/images/download_video_demo.png)

<br/><br/>

### **End**
