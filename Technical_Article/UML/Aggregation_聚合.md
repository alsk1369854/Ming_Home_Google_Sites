# UML Aggregation 聚合關係 

<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/UML/images/UML_Aggregation.jpg)
</center>

> ## Java code
```java
public class ClassRoom {
    private List<Student> students;
}
 
public class Student {
    private ClassRoom classRoom;
}
```

<br/>

> ## Aggregation Description
> 
> &emsp;&emsp;是關聯關係的特例，是強的關聯關係，聚合是整個與個體的關係，即has-a關係，此時整體和部分是可以分離的，他們具有各自的生命週期，部分可以屬於多個物件，也可以被多個物件共享。
>
> 在程式碼層面聚合與關聯是一致的，只能從語義上來區分。
>
> __上方程式碼展現了，教室沒了但是學生還有存在的必要__

<br/>

#### _END_

