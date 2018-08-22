## C++ 面向对象编程补充 ##

### 1.对象的存储空间 ###

很多C++书籍中都介绍过一个对象需要占用多大的内存空 间,最权威的结论是:非静态成员变量总和加上编译器为了CPU计算做出的数据对齐处理和支持虚函数所产生的负担的总和。下面分别看看数据成员、成员函数、构造函数、析构函数、虚函数的空间占用情况 。

#### (1) 空类的存储空间 ####

```cpp
#include<iostream>
using namespace std;
class CBox{
};
int main(){
    CBox boxobj;
    cout<<sizeof(boxobj)<<endl;//输出1
    return 0;
}
```

编译运行结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ g++ 0214.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ ./a.out 
    1

上例定义了一个空类CBox,里面既没有数据成员,也没有成员函数.程序执行结果显示它的大小为1。空类型对象中不包含任何信息,应该大小为 0。电 但是当 声 明该类型 的对象的时候,它必须在内存中占有一定的空间,否则无法使用这些对象。 至于占用多少内存,由编译器决定。C++中每个空类型的实例占 lByte 空间 。

#### (2) 只有成员变量的类的存储空间计算 ####

```cpp
#include<iostream>
using namespace std;
class CBox{
    int length,width,height;
};
int main(){
    CBox boxobj;
    cout<<sizeof(boxobj)<<endl;
    return 0;
}
```

结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ g++ 0215.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ ./a.out 
    12

类CBox中只有3个成员变量,由于整型变量占4Byte,所以对象所占的空间就是12Byte。

#### (3) 有成员变量和静态成员变量的类的存储空间计算 ####

```cpp
#include<iostream>
using namespace std;
class CBox{
    int length,width,height;
    static int count;
};
int main(){
    CBox boxobj;
    cout<<sizeof(boxobj)<<endl;
    return 0;
}
```

结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ g++ 0216.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ ./a.out 
    12

类CBox中有3个普通数据成员和1个静态数据成员,,但是程序的执行结果还是12,也就证明了静态数据成员是不占对象的内存空间的 。

#### (4) 类中只有1个成员函数的存储空间计算 ####

```cpp
#include<iostream>
using namespace std;
class CBox{
    int foo();
};
int main(){
    CBox boxobj;
    cout<<sizeof(boxobj)<<endl;
    return 0;
}
```

结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ g++ 0217.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ ./a.out 
    1

类CBox中只有一个成员函数,类CBox的对象boxobj的大小却只有lByte,和空类对象是一样的,所以可以得出,成员函数是不占空间的 。

#### (5) 类中构造函数、析构函数的空间占用情况 ####

```cpp
#include<iostream>
using namespace std;
class CBox{
public:
    CBox(){};
    ~CBox(){};
};
int main(){
    CBox boxobj;
    cout<<sizeof(boxobj)<<endl;
    return 0;
}
```

结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ g++ 0218.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ ./a.out 
    1

类CBox中只有构造函数和析构函数,类CBox的对象boxobj的大小也只有1Byte,和空类对象是一样的,所以可以得出,构造函数和析构函数也是不占空间的。

#### (6) 类中有虚的析构函数的空间计算 ####

```cpp
#include<iostream>
using namespace std;
class CBox{
public:
    CBox(){};
    virtual ~CBox(){};
};
int main(){
    CBox boxobj;
    cout<<sizeof(boxobj)<<endl;//输出4
    return 0;
}
```
结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ g++ 0219.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ ./a.out 
    8

类CBox中有1个构造函数和1个虚的析构函数,程序的执行结果是8。事实上,编译器为了支持虚函数,会产生额外的负担,这正是指向虚函数表 的指针的大小 。(指针变量在64位的机器上占8Byte)如果一个类中有一个或者多个虚函数,没有成员变量,那么类相当于含有一个指向虚函数表的指针,占8Byte 。

#### (7) 继承空类和多重继承空类存储空间的计算 ####

```cpp
#include<iostream>
using namespace std;
class A{
};
class B{
};
class C:public A{
};
class D:public virtual B{
};
class E:public A,public B{
};
int main(){
    A a;
    B b;
    C c;
    D d;
    E e;
    cout<<"sizeof(a):"<<sizeof(a)<<endl;
    cout<<"sizeof(b):"<<sizeof(b)<<endl;
    cout<<"sizeof(c):"<<sizeof(c)<<endl;
    cout<<"sizeof(d):"<<sizeof(d)<<endl;
    cout<<"sizeof(e):"<<sizeof(e)<<endl;
    return 0;
}
```

结果如下;

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ g++ 0220.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ ./a.out
    sizeof(a):1
    sizeof(b):1
    sizeof(c):1
    sizeof(d):8
    sizeof(e):1

上例定义了一个空类A和B ,类C继承了类A,类D继承了虚基类B,类E继承了类A和类B。这些类的对象所占的 空间都是lByte。由此可见,单一继承的空类空间也是l,多重继承的空类空间还是1,但是虚继承涉及虚表(虚指针),所以sizeof(d)=8。

综上所述,每个对象所占用的存储空间只是该对象的非静态数据成员的总和,其他都不占用存储空间,包括成员 函数和静态数据成员。函数代码是存储在对象空间之外的,而且,函数代码段是公用的,即如果对同一个类定义了10个对象,这些对象的成员函数对应的是同一个函数代码段,而不是10个不同的函数代码段。