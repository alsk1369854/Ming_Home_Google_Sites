# UML Generalization 泛化(繼承)關係

<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/UML/images/UML_Generalization.jpg)
</center>

> ## Java code
```java
public class Student {
    private String name;    
    ...
}

public class MiddleSchoolStudent extends Student {
    ...
}

public class CollegeStudent extends Student {
    ...
}
```

<br/>

> ## Generalization Description
>
> 一個類（子類、子介面）繼承另外一個類（稱為父類、父介面）的功能，並可以增加它自己新功能的能力。
>
> 上方代碼使現了 MiddleSchoolStudent類 與 CollegeStudent類 都繼承了 Student類 的屬性與方法

<br/>

### _END_