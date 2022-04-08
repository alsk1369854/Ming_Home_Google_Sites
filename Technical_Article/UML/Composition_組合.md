# UML Composition 組合關係 

<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/UML/images/UML_Composition.jpg)
</center>

> ## Java code
```java
public class 人 {
    private List<肢體> hands;
}
 
public class 肢體 {
    private 人 body;
}
```

<br/>

> ## Composition Description
> 
> &emsp;&emsp;是關聯關係的一種特例，體現的是一種contain-a關係，比聚合更強，是一種強聚合關係。它同樣體現整體與部分的關係，但此時整體與部分是不可分的，整體生命週期的結束也意味著部分生命週期的結束，反之亦然。
>
> &emsp;&emsp;組合與聚合幾乎完全相同，唯一區別就是對於組合，“部分”不同脫離“整體”單獨存在，其生命週期應該是一致的。
>
> 體現在程式碼層面與關聯時一致的，只能從語義來區分。
>
> __上方程式碼展現了，人沒了肢體那人就沒存在的必要了，相對的若肢體沒有人也沒有存在的意義，兩者生命週期是並行的。__

<br/>

#### _END_

