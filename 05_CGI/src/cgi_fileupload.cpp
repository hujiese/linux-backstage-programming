/*************************************************************************
	> File Name: cgi_fileupload.cpp
	> Author: hujie
	> Mail: jackster@163.com
	> Created Time: 2018年08月28日 星期二 17时34分17秒
 ************************************************************************/

#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 
 
#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>
 
using namespace std;
using namespace cgicc;
 
int main ()
{
   Cgicc cgi;
 
   cout << "Content-type:text/html\r\n\r\n";
   cout << "<html>\n";
   cout << "<head>\n";
   cout << "<title>CGI file upload</title>\n";
   cout << "</head>\n";
   cout << "<body>\n";
 
   // 获取要被上传的文件列表
   const_file_iterator file = cgi.getFile("userfile");
   if(file != cgi.getFiles().end()) {
      // 在 cout 中发送数据类型
      cout << HTTPContentHeader(file->getDataType());
      // 在 cout 中写入内容
      file->writeToStream(cout);
   }
   cout << "<file upload ok>\n";
   cout << "</body>\n";
   cout << "</html>\n";
   
   return 0;
}