# UML Class
> General Class (一般類)
> 
> Abstract Class (抽象類)
>

<br/>

> ## _General Class_ 
<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/UML/images/UML_Class.jpg)
</center>

> ### Java code
```java
class Student{
    // Attribute
    private int final STUDENT_ID;
    private String name;
    private int age;
    public static int nextID = 1;

    // Constructor
    public Student(name String, age int) { .... }

    // Operation
    public String getName() { .... }
    public void setName(newName String) { .... }
    public int getAge() { .... }
    protected setAge(newAge int) { .... }
    void fallInLove() { .... }
}
```
> ### Description
#### 類名、屬性、方法宣告位置
+ `類的名稱` => 最上層(三樓) 
+ `類的屬性` => 第二層(二樓) 
+ `類的方法` => 第一層(一樓) 

#### 能見度符號
+ `+` => public: 所有人都可以訪問
+ `-` => private: 唯獨自己可以訪問
+ `#` => protected: 同一個工作包下可訪問
+ `~` => [default]: 唯獨繼承者可訪問

#### Static and Final
+ `static` => 使用底線對 <u>static</u> 標示
+ `final` => 在結尾添加 {readOnly} 標示


<br/>

> ## _Abstract Class_

<center>

![](https://raw.githubusercontent.com/alsk1369854/Ming_Home_Google_Sites/master/Technical_Article/UML/images/UML_Abstract_Class.jpg)
</center>

> ### Java code
```java
abstract class Employess{
    // Attribute
    private String name;

    // Constructor
    public Employee(name String) {...}

    // Operation
    public String getName() {...}
    public void setName(newName String) {...}

    // Abstract Operation
    public abstract void work();
}
```
> ### Description
#### 抽象類、抽象方法宣告
+ `abstract` = > 使用斜體對  _抽象類與抽象方法_ 標示

<br/>

#### _END_