#include <stdio.h>
#include <connect.h>
#include <string.h>
#include <analysisHTTP.h>
#include <configure.h>

/**
 *题目描述设计一个小型单线程Web服务器程序，接收浏览器请求，并把结果返回给浏览器。
 *任务具体要求
 *1、通过Socket监听，接收浏览器HTTP请求。
 *2、分析HTTP请求内容，分离出请求的文件。
 *3、将相应的文件通过Socket发回给浏览器。
 *4、服务器相关配置信息，如端口号，根目录等，通过配置文件指定。
 *5、第个模块单独写在源代码单元中（包含一个.h文件和一个.c文件）。
 *6、每一项功能用一个函数实现，并设计好相应接口，将来可以方便改成多线程、数据库存储。
 *7、代码编写符合规范，注释完整。
 */

char ip_address[20] = "127.0.0.1"; //IP地址
int port = 12345; // 端口号
char root[50] = "/home/shuangli/CLionProjects/webserver/root"; //根目录 必须是绝对路径
const int max_bufferlen = 1500; // 缓冲区的最大空间

int main(void) {
    get_ip_address(ip_address);
    getRoot(root);
    getPort(&port);
    printf("Welcome to Webserver!\n");
    printf("开放的地址为: %s:%d\n",ip_address,port);
    printf("根目录为:%s\n",root);

    int client_browser = connection_in_server(port);
    char buffer[max_bufferlen];
    long dataLen = getMessage(client_browser,buffer,max_bufferlen);
    printf("收到的数据长度为%ld\n",dataLen);
    printf("%s",buffer);

    char fileRoute[50];
    strcpy(fileRoute,getRoute(buffer));
    printf("所需要的文件路径为%s\n",fileRoute);

    char filename[50];
    strcpy(filename,getFilename(buffer));
    printf("文件名为:%s\n",filename);

    sendFile(filename,fileRoute,client_browser);
    return 0;
}