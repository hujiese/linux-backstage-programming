## C++常用编程技术扩充 ##

### 1.共用体 ###

共用体,用关键词union来定义,它是一种特殊的类.在一个共用体里可以定义多种不同的数据类型,这些数据类型共享一段内存,在不同的时间里保存不同的数据类型和长度的变量,以达到节省空间的目的.但是同一时间只能存储其中一个成员变量的值.其用法和结构体类似.

考虑一个16位整数,它由2个字节组成.内存中存储这两个字节有两种方法:一种是将低序字节存储在起始地址,这称为小端字节序;还一种是将高地址字节存储在起始地址,这称为大端字节序.

目前,几乎所有的网络协议都是采用big endian的方式来传输数据的,当两台采用不同字节序的主机通信时,在发送数据之前都必须经过字节序的转换成为网络字节序后再进行传播.

可以使用union来判断系统是大端还是小端字节序:

```cpp
#include<iostream>
using namespace std;
union TEST{
    short a;
    char b[sizeof(short)];
};
int main(){
    TEST test;
    test.a=0x0102;// 不能引用共用体变量，只能引用共用体变量中的成员。
    if(test.b[0]==0x01&&test.b[1]==0x02){
        cout<<"big endian."<<endl;
    }
    else if(test.b[0]==0x02&&test.b[1]==0x01){
        cout<<"small endian."<<endl;
    }
    else{
        cout<<"unknown"<<endl;
    }
    return 0;
}
```

编译运行结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter01$ g++ 0112.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter01$ ./a.out
    small endian.

### 2.结构体、共用体在内存单元占用字节数的计算 ###

#### (1) union ####

```cpp
#include<iostream>
using namespace std; 
union A{
   int a[5];
   char b;
   double c;
};
int main(){
   cout<<sizeof(A)<<endl;
   return 0;
}
```

运行结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter01$ g++ 0114.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter01$ ./a.out
    24

union中变量共用内存应以最长的为准,上面程序执行结果却不是预想的20 (int a[5],5*4 =20Byte),这是因为在共用体内变量的默认内存对齐方式,必须以最长的 double(8Byte)对齐,也就是说应该是 sizeof(A)=24 。所以将共用体中的 int a[5]修改成 int a[6]后,结果仍然不变;但如果将 int a[5]修改成 int a[7],结果就将变成32。

#### (2) struct ####

计算struct有两个原则：

1）各成员变量存放的起始地址相对于结构的起始地址的偏移量必须为该变量的类型所占用的字节数的倍数.

2）为了确保结构的大小为结构的字节边界数（即该结构中占用最大空间的类型所占用的字节数）的倍数,所以在为最后一个成员变量申请空间后，还会根据需要自动填充空缺的字节。

例如:

```cpp
#include<iostream>
using namespace std; 
struct B{
  char a;
  double b;
  int c;
}test_struct_b;
int main(){
   cout<<sizeof(test_struct_b)<<endl;
   return 0;
}

```

结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter01$ g++ 0115.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter01$ ./a.out
    24

第一个成员变量a是char类型,占用了1byte,第二个变量b是doulbe类型的,占用了8byte,但是根据第一条准则,b变量相对于该结构体起始位置应该是double的整数倍,也就是说前面还需要填充一定空间,然后让b变量地址减去结构体地址(这里就是变量a的起始地址)要是8的倍数,所以前面还需要填充7个字节.至于变量c,距离结构体首地址偏移为16,是4的整数倍,所以不用填充.至此,一共占用了1+7+8+4=20byte,但是根据第二条准则,整个结构体大小要是8的倍数,所以距离20最近且大于20的8的倍数是24,所以最后计算得到结构体大小为24byte.

### 3.extern "C" 块 ###

经常能在C与C++混编的程序中看到这样的语句:

```cpp
#ifdef _cplusplus
	extern ” C ”(
#endif
	...
#ifdef _cplusplus
}
#endif
```
其中,_cplusplus是C++的预定义宏,表示当前开发环境是C++。在C++语言中,为了支持重载机制,在编译生成的汇编代码中,会对函数名字进行一些处理(通常称为函数名字改编),如加入函数的参数类型或返回类型等,而在C语言 ,只是简单的函数名字而已,并不加入其他信息,如下所示 :

```cpp
int func(int demo);
int func(double demo) ;
```

C语言无法区分上面两个函数的不同,因为C编译器产生的函数名都是_func ,而C++编译器产生的名字则可能是 _func_Fi 和 _func_Fd ,这样就很好地把函数区别开了 。

所以,在C/C\++ 混合编程的环境下,extern ”C”块的作用就是告诉C\++编译器这段代码要按 C 标准编译,以尽可能地保持 C++与 C 的兼容性。下面这个例子说明__cplusplus 的使用方法:

```cpp
#include<stdio.h>
int main() {
    #define TO_LITERAL(text) TO_LITERAL_(text)
    #define TO_LITERAL_(text) #text
    #ifndef __cplusplus
    /* this translation unit is being treated as a C one */
        printf("a C program\n");
    #else
       /*this translation unit is being treated as a C++ one*/
        printf("a C++ program\n__cplusplus expands to \""
          TO_LITERAL(__cplusplus) "\"\n");
    #endif
    return 0;
}
```

运行结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter01$ g++ 0118.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter01$ ./a.out
    8

程序的意思是:如果没有定义_cplusplus ,那么当前源代码就会被当作C源代码处理;如果定义了\__cplusplus ,那么当前源代码会被当中C++源代码处理,并且输出__cplusplus宏被展开后的字符串 。