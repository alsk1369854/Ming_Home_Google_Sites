# UML Realization 實現關係

<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/UML/images/UML_implements.jpg)
</center>

> ## Java code
```java
public interface Flyable {
    void fly();
}

public interface Runnable {
   void run();
}

public class Cat implements Flyable, Runnable {
    public fly(){ .... };
    public run(){ .... };
}

public class Dog implements Runnable {
    public run() { .... };
}
```

<br/>

> ## Realization Description
>
> 一個class實現interface介面（一個或者多個），表示類具備了某種能力
>
> __上方代碼展現了 Dog類 與 Cat類 都實現了跑的功能，而 Cat類 又在另外的實現了飛的功能__

<br/>

#### _END_