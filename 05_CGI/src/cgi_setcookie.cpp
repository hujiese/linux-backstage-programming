/*************************************************************************
	> File Name: cgi_setcookie.cpp
	> Author: hujie
	> Mail: jackster@163.com
	> Created Time: 2018年08月28日 星期二 17时13分15秒
 ************************************************************************/

#include <iostream>
using namespace std;
 
int main ()
{
 
   cout << "Set-Cookie:UserID=jackster;\r\n";
   cout << "Set-Cookie:Password=jackster123456;\r\n";
   cout << "Set-Cookie:Domain=http://localhost;\r\n";
   cout << "Set-Cookie:Path=/cgi;\n";
   cout << "Content-type:text/html\r\n\r\n";
 
   cout << "<html>\n";
   cout << "<head>\n";
   cout << "<title>Cookies in CGI</title>\n";
   cout << "</head>\n";
   cout << "<body>\n";
 
   cout << "set cookies ok ..." << endl;  
  
   cout << "<br/>\n";
   cout << "</body>\n";
   cout << "</html>\n";
   
   return 0;
}