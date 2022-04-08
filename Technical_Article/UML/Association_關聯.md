# UML Association 關聯關係

<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/UML/images/UML_Association.jpg)
</center>

> ## Java code
```java
public class Husband{
    Wife wife;
    ....
}

public class Wife{
    ....
}
```

<br/>

> ## Association Description
>
> &emsp;&emsp;表示類與類之間的連線，它使得一個類知道另外一個類的屬性和方法。
> 關聯可以使用單箭頭表示單向關聯，使用雙箭頭或者不適用箭頭表示雙向關聯，不建議使用雙向關聯
>
> + 0..1 表示可以有0個或者1個例項
>
> + 0..* 表示對例項的數目沒有限制
> 
> + 1     表示只能有一個例項
>
> + 1..* 表示至少有一個例項
>
>
> &emsp;&emsp;關聯關係體現的是兩個類，或者類與介面之間的強依賴關係，這種關係很強烈，比依賴更強，不是偶然性的，也不是臨時性的，而是一種長期性，相對平等的關係，表現在程式碼層面，為被關聯的類B以類屬性的形式出現在類A中，也可能是關聯類A引用了被關聯類B的全域性變數
>
> __上方展程式碼展現了，找到了丈夫類就能找到夫人類了。__

<br/>

#### _END_
