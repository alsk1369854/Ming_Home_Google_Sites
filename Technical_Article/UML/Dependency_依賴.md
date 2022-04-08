# UML Dependency 依賴關係 

<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/UML/images/UML_Dependency.jpg)
</center>

> ## Java code
```java
public class Human {
    // 依賴1
    public void crossRiver() {
        // 局部變數
        Ship ship = new Ship();
        ....
    }

    //  依賴2
    public void crossRiver(ship Ship) {
        ....
    }
}

public class Ship {
    ....
}
```

<br/>

> ## Dependency Description
> 
> &emsp;&emsp;是表示類與類之間的連線，表示一個類依賴於另外一個類的定義，依賴關係時是單向的。簡單理解就是類A使用到了類B，這種依賴具有偶然性、臨時性，是非常弱的關係。但是類B的變化會影響到類A。
>
> 在程式碼層面，為類B作為引數被類A在某個方法中使用。
>
> __上方程式碼展現了，某人要過河，則人與船的關係就是依賴，人過河之後，與船的關係就解除了，因此是一種弱的連線。__

<br/>

#### _END_

