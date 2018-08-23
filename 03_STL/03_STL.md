## STL补充 ##

### string ###

#### 1.C++字符串和C字符串的转换 ####

C\++提供的由C\++字符串转换成对应的C字符串的方法是使用data()、c_str()和copy()来实现。其中, data()以字符数组的形式返回字符串内容,但并不添'\0'; c_str()返回一个以'\0'结尾的字符数组;而 copy()则把字符串的内容复制或写入既有的 c_string或字符数组内。需要注意的是,C++字符串并不以'\0'结尾。

c_str()语句可以生成一个const char *指针,并指向空字符的数组。这个数组的数据是临时的,当有一个改变这些数据的成员函数被调用后,其中的数据就会失效。因此要么现用现转换,要么把它的数据复制到用户自己可以管理的内存中后再转换。

##### (1) c_str()使用方法举例 #####

```cpp
#include<iostream>
#include<string>
using namespace std;
int main(){
    string str="Hello world.";
    const char * cstr=str.c_str();
    cout<<cstr<<endl;
    str="Abcd.";
    cout<<cstr<<endl;
    return 0;
}
```

运行结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter03$ g++ 0303.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter03$ ./a.out
    Hello world.
    Abcd.

如上例所示,改变了str的内容, cstr的内容也会随着改变。所以上面如果继续使用C指针的话,导致的错误将是不可想象的。既然C指针指向的内容容易失效,就可以考虑把数据复制出来解决问题:

```cpp
#include<iostream>
#include<string>
#include<string.h>
using namespace std;
int main(){
	char * cstr=new char[20];
	string str="Hello world.";
    strncpy(cstr,str.c_str(),str.size());
    cout<<cstr<<endl;
    str="Abcd.";
    cout<<cstr<<endl;
    return 0;
}
```

运行结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter03$ g++ 0304.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter03$ ./a.out
    Hello world.
    Hello world.

上例中用strcpy函数将str.c_str()的内容复制到cstr里了,这样就能保证cstr里的内容不随着str的内容改变而改变了。

copy(p,n,size_type _Off= 0)这句表明从string类型对象中至多复制n个字符到字符指针p指向的空间中,并且默认从首字符开始,也可以指定开始的位置(从0开始计数),返回真正从对象中复制的字符。不过用户要确保p指向的空间足够来保存n个字符。

##### (2) string.copy用法的详细举例 #####

```cpp
#include<iostream>
#include<string>
using namespace std;
 
int main (){
    size_t length;
    char buffer[8];
    string str("Test string......");
	cout<<"str:"<<str<<endl;
       
    length=str.copy(buffer,7,5);
    buffer[length]='\0';
    cout<<"str.copy(buffer,7,5),buffer contains: "<<buffer<<endl; 
	
    length=str.copy(buffer,str.size(),5); 
    buffer[length]='\0';  
    cout<<"str.copy(buffer,str.size(),5),buffer contains:"<<buffer<<endl;
 
    length=str.copy(buffer,7,0); 
    buffer[length]='\0'; 
    cout<< "str.copy(buffer,7,0),buffer contains:"<<buffer<<endl;
 
    length=str.copy(buffer,7); //缺省参数pos，默认pos=0；
    buffer[length]='\0';
    cout<<"str.copy(buffer,7),buffer contains:"<<buffer<<endl;
	
    length=str.copy(buffer,string::npos,5); 
    buffer[length]='\0';
    cout<<"string::npos:"<<(int)(string::npos)<<endl;
    cout<<"buffer[string::npos]:"<<buffer[string::npos]<<endl;
    cout<<"buffer[length-1]:"<<buffer[length-1]<<endl;
    cout<<"str.copy(buffer,string::npos,5),buffer contains:"<<buffer<<endl;
	
    length=str.copy(buffer,string::npos);
    buffer[length]='\0';
    cout<<"str.copy(buffer,string::npos),buffer contains:"<<buffer<<endl; 
    cout<<"buffer[string::npos]:"<<buffer[string::npos]<<endl;
    cout<<"buffer[length-1]:"<<buffer[length-1]<<endl; 
    return 0;
 }
```

运行结果如下;

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter03$ g++ 0305.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter03$ ./a.out
    str:Test string......
    str.copy(buffer,7,5),buffer contains: string.
    str.copy(buffer,str.size(),5),buffer contains:string......
    str.copy(buffer,7,0),buffer contains:Test st
    str.copy(buffer,7),buffer contains:Test st
    string::npos:-1
    buffer[string::npos]:
    buffer[length-1]:.
    str.copy(buffer,string::npos,5),buffer contains:string......
    str.copy(buffer,string::npos),buffer contains:Test string......
    buffer[string::npos]:
    buffer[length-1]:.

例子中展示了通过不同的方法用string的copy方法进行字符串的复制,常见的api的参数一般是把起始点信息放在前面,长度信息放在后面,如string的构造函数string s(char *str,int stridx,int strlen);而copy方法却是把长度放在起始点前面,这个是需要小心使用的。另外,copy函数的第二个参数,除了可以是长度,也可以是一个位置,如string::npos。

string::npos是一个机器最大的正整数,不同机器不一样,如64位机器是18446744073709551615,而32位机器则是4294967295,类型是std::container_ type::size_ type。可以将其强制转换成 int,就是-1,这样就不会存在移植的问题。一般用npos表示string的结束位置。

copy函数的第三个参数不填时则默认为0,即从第一个字符开始。综上,可以使用string的 c_str()、 data()、copy(p, n),时,从一个string类型得到一个C类型的字符数组。

#### 2.string和int类型的转换 ####

##### (1) int转string #####

这里需要用到snprintf(),函数原型为:

	int snprintf(char *str , size_t size ,const char * format, ... )

它的功能主要是将可变个参数(...)按照format格式化成字符串,然后将其复制到由中,具体如下所述:

- 如果格式化后的字符串长度小于size,则将此字符串全部复制到str中,并给其后添加一个字符串结束符('\n') 。
- 如果格式化后的字符串长度不小于size,则只将其中的(size-1)个字符复制到str中,并给其后添加一个字符串结束符('\n'),返回值为欲写人的字符串长度。
- 函数的返回值是若成功,则返回欲写入的字符串长度,若出错则返回负值。
- 如果原始参数为“...”,那么这是个可变参数。

下面这个例子演示了snprintf的用法:

```cpp
#include<stdio.h>
int main (){
    char a[20];
    int i = snprintf(a, 9, "%012d", 12345);
    printf("i = %d, a = %s\n", i, a);
    return 0;
 }
```

运行结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter03$ g++ 0306.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter03$ ./a.out
    i = 12, a = 00000001

例子中, %012d的格式是指使输出的int型的数值以12位的固定位宽输出,如果不足12位,则在前面补O;如果超过12位,则按实际位数输出。如果输出的数值不是int型,则进行强制类型转换为int,之后按前面的格式输出。那就是先得到了000000012345,再取前面(9-1)位,即8位,则是00000001。

与此类似的,将int转换为string,代码通常可以这么写:

```cpp
static inline std::string i64tostr(long long a) {
    char buf[32] ;
    snprintf(buf, sizeof(buf ) ,"%lld", a);
    return std::string(buf) ;
}
```

##### (2) string转int #####

这里需要用到 strtol, strtoll, strtoul或strtoull函数,它们的函数原型分别如下所示:

```cpp
    long int strtol (const char *nptr, char **endp tr, int base);
    long long int strtoll(const char *nptr, char **endp tr, int base);
    unsigned long int strtoul(const char *nptr, char **endptr, int base);
    unsigned long long int strtoull(const char *nptr, char **endptr, int base);
```

下面这个例子演示了strtol的使用方法:

```cpp
#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;
int main(){
    char *endptr;
    char nptr[]="123abc";
    int ret = strtol(nptr, &endptr, 10 );
    cout<<"ret:"<<ret<<endl;
    cout<<"endptr:"<<endptr<<endl;

    char *endptr2;
    char nptr2[]=" \n\t    abc";
    ret = strtol(nptr2, &endptr2, 10 ); 
    cout<<"ret:"<<ret<<endl;
    cout<<"endptr2:"<<endptr2<<endl;

    char *endptr8;
    char nptr8[]="0123";
    ret = strtol(nptr8, &endptr8,0); 
    cout<<"ret:"<<ret<<endl;
    cout<<"endptr8:"<<endptr8<<endl;   

    char *endptr16;
    char nptr16[]="0x123";
    ret = strtol(nptr16, &endptr16,0); 
    cout<<"ret:"<<ret<<endl;
    cout<<"endptr16:"<<endptr16<<endl;  

    return 0;
}
```

运行结果如下:

    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter03$ g++ 0307.cpp
    jack@jack-Ubuntu:~/workspace/UNIX_ENV/CORE_BACKWEB/charpter03$ ./a.out
    ret:123
    endptr:abc
    ret:0
    endptr2:
            abc
    ret:83
    endptr8:
    ret:291
    endptr16:

例子中主要是使用strtol函数对不同的字符串取出整数。

```cpp
char nptr[] = ”123abc";
int ret = strtol(nptr, &endptr, 10);
```

十进制里没有“数字” a ,所以扫描到 就结束,因此ret值是123,即ependptr是abc。

```cpp
char *endptr2;
char nptr2[]=" \n\t    abc";
ret = strtol(nptr2, &endptr2, 10 );
```
由于函数会忽略nptr往前面的空格,所以从字符a开始扫描,但是遇见的“第一个”即是不合法字符,所以函数结束,此时ret=O;endp位= nptr;

```cpp
    char *endptr8;
    char nptr8[]="0123";
    ret = strtol(nptr8, &endptr8,0);

    char *endptr16;
    char nptr16[]="0x123";
    ret = strtol(nptr16, &endptr16,0);
```

当第三个参数为0时,则分以下3种情况:
- 如果nptr以Ox开头,则把nptr成16进制处理。
- 如果npstr以0开头,则把np位当成8进制处理。
- 否则,把nptr当成10进制。

nptr8是以0开头的,所以将nptr8当成8进制处理,再将8进制的0123转换为10进制的,得到了 1*8"2+2*8+3=83。ptrl6是以Ox开头的,将叩tr16当成16进制处理,再将16进制的Oxl23转换为10进制的得到了1*16"2+2*16+3=291。因此,将字符串转换为10进制的数字,可以这么写:

```cpp
static inline int64_t strtoint(const std::string& s ) {
	return strtoll(s.c_str(), 0 , 10);
}
```