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

### 2.派生类的构造函数与析构函数的调用顺序 ###

构造函数的调用顺序规则如下所述:

1)基类构造函数。如果有多个基类,则构造函数的调用顺序是某类在类派生表中出现的顺序,而不是它们在成员初始化表中的顺序。

2)成员类对象构造函数。如果有多个成员类对象,则构造函数的调用顺序是对象在类中被声明的顺序,而不是它们出现在成员初始化表中的顺序。

3)派生类构造函数。而析构函数的调用顺序与构造函数的调用顺序正好相反,将上面3点内容中的顺序反过
来用就可以了,即:首先调用派生类的析构函数;其次再调用成员类对象的析构函数;最后调用基类的析构函数。析构函数在下面3种情况时被调用。

- 对象生命周期结束被销毁时(一般类成员的指针变量与引用都不自动调用析构函数)。
- delete指向对象的指针时,或delete指向对象的基类类型指针,而其基类虚构函数是虚函数时。
- 对象i是对象o的成员,o的析构函数被调用时,对象i的析构函数也被调用。

下面用例将说明构造函数的调用顺序:

```cpp
#include<iostream>
using namespace std;
class CBase{
public:
    CBase (){ std::cout<<"CBase::CBase()"<<std::endl; }
    ~ CBase (){ std::cout<<"CBase::~CBase()"<<std::endl; }
};

class CBase1:public CBase {
public:
    CBase1 (){ std::cout<<"CBase::Base1()"<<std::endl; }
    ~ CBase1 (){ std::cout<<"CBase::~Base1()"<<std::endl; }
};

class CDerive{
public:
    CDerive (){ std::cout<<"CDerive::CDerive()"<<std::endl; }
    ~ CDerive (){ std::cout<<"CDerive::~CDerive()"<<std::endl; }
};

class CDerive1:public CBase1{
private:
    CDerive m_derive;
public:
    CDerive1(){ std::cout<<"CDerive1::CDerive1()"<<std::endl; }
    ~CDerive1(){ std::cout<<"CDerive1::~CDerive1()"<<std::endl; }
};

int main(){
    CDerive1 derive;
    return 0;
}
```

结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ g++ 0227.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ ./a.out
    CBase::CBase()
    CBase::Base1()
    CDerive::CDerive()
    CDerive1::CDerive1()
    CDerive1::~CDerive1()
    CDerive::~CDerive()
    CBase::~Base1()
    CBase::~CBase()

上面例子中声明了4个类,CBasel继承于CBase、CDerivel继承于CBasel、CDerivel中有CDerive的成员变量,最后定义一个CDerivel对象,用来确定各种基类、派生类的构造函数和析构函数的执行顺序。 执行结果与上文中描述的调用顺序相符。

总的来说,构造函数的调用顺序是:1如果存在基类,那么先调用基类的构造函数,如果基类的构造函数中仍然存在基类,那么程序会继续进行向上查找,直到找到它最早的基类进行初始化(如上例中类Derivel,继承于类Base与Basel);2如果所调用的类中定义的时候存在对象被声明,那么在基类的构造函数调用完成以后,再调用对象的构造函数(如上例在类Derivel中声明的对象Derive m_derive);3调用派生类的构造函数(如上例最后调用的是Derivel类的构造函数)。

### 3.虚析构函数 ###

在C\++中,构造函数不能声明时为虚函数,这是因为编译器在构造对象时,必须知道确切类型,才能正确地生成对象;其次,在构造函数执行之前,对象并不存在,无法使用指向此对象的指针来调用构造函数。然而,析构函数可以声明为虚函数;C++明确指出,当derived class对象经由一个base class指针被删除、而base class带着一个non-virtual析构函数,会导致对象的derived成分没被销毁掉,下面例子所示:

```cpp
#include<iostream>
using namespace std;
class Base{
public:
    Base(){ std::cout<<"Base::Base()"<<std::endl; }
    ~Base(){ std::cout<<"Base::~Base()"<<std::endl; }
};
class Derive:public Base{
public:
    Derive(){ std::cout<<"Derive::Derive()"<<std::endl; }
    ~Derive(){ std::cout<<"Derive::~Derive()"<<std::endl; }
};
int main(){
    Base* pBase = new Derive(); 
    /*这种base classed的设计目的是为了用来"通过base class接口处理derived class对象"*/
    delete pBase;
    return 0;
}
```

运行结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ g++ 0231.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ ./a.out
    Base::Base()
    Derive::Derive()
    Base::~Base()

上面例子中声明了类Base和类Derive,类Derive继承于类Base,两个类各自有构造函数和析构函数,并且基类和派生类的析构函数都是非虚函数。从上面的执行结果可以看出,析构函数的调用结果是存在问题的,也就是说析构函数只做了局部销毁工作,这可能形成资源泄漏、损坏数据结构等问题。而解决此问题的方法很简单,只要给基类一个virtual构函数即可,下面例子所示:

```cpp
#include<iostream>
using namespace std;
class Base{
public:
    Base(){ std::cout<<"Base::Base()"<<std::endl; }
    virtual ~Base(){ std::cout<<"Base::~Base()"<<std::endl; }
};

class Derive:public Base{
public:
    Derive(){ std::cout<<"Derive::Derive()"<<std::endl; }
    ~Derive(){ std::cout<<"Derive::~Derive()"<<std::endl; }
};

int main(){
    Base* pBase = new Derive();
    delete pBase;
    return 0;
}
```

运行结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ g++ 0232.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter02$ ./a.out
    Base::Base()
    Derive::Derive()
    Derive::~Derive()
    Base::~Base()

