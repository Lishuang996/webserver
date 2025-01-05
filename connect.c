//
// Created by shuangli on 24-12-30.
//

#include "connect.h"



/**connect.c
 * 封装socket的相关操作 包括建立连接并监听 获取请求头 发送文件
 */

// 创建socket并连接，出现错误返回-1
int connection_in_server(int port) {
    // 创建socket
    int tcp_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct sockaddr_in address;

    // 判断是否创建成功
    if (tcp_socket==-1) {
        printf("socket creation failed");
        close(tcp_socket);
        exit(1);
    }

    // 设置服务器地址信息
    address.sin_family = AF_INET; // 设置为ipv4
    address.sin_addr.s_addr = INADDR_ANY; // 接收任意网卡发来的请求
    address.sin_port = htons(port); // 设置端口
    int addrlen = sizeof(address);

    // 绑定套接字到指定IP 和 端口
    if (bind(tcp_socket,(struct sockaddr *)&address,addrlen)<0) {
        printf("bind failed");
        close(tcp_socket);
        exit(1);
    }

    // 开始监听 最大连接数为5
    if (listen(tcp_socket,5) == -1) {
        printf("listen failed");
        close(tcp_socket);
        exit(1);
    }

    // listen() 只是让套接字进入监听状态，并没有真正接收客户端请求，listen() 后面的代码会继续执行，
    // 直到遇到 accept()。accept() 会阻塞程序执行（后面代码不能被执行），直到有新的请求到来。
    const int new_socket = accept(tcp_socket, (struct sockaddr *) &address, (socklen_t *) &addrlen);
    if (new_socket==-1) {
        printf("accept failed");
        exit(1);
    }

    printf("连接成功\n");
    close(tcp_socket);
    return new_socket;
}

// 获取HTTP请求 new_socket是从收到的socket文件 buffer是接收的缓存区域 max_bufferlen是最大缓存大小
long getMessage(int new_socket,char *buffer,int max_bufferlen) {
    buffer[0] = '\0';
    long dataNum = recv(new_socket,buffer,max_bufferlen-1,0);
    if (dataNum==-1) {
        printf("Read Error");
        exit(1);
    }
    buffer[dataNum] = '\0';
    return dataNum;
}

// 发送文件 filename是文件名 fileRoute是文件路径 client_browser是浏览器socket文件
void sendFile(char* filename,char* fileRoute,int client_browser) {
    char buffer[1500];
    FILE* fp = fopen(fileRoute,"rb");
    if (fp == NULL) {
        perror("File opening failed");
        exit(1);
    }

    char header[1024];
    snprintf(header, sizeof(header),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: application/octet-stream\r\n"
                 "Content-Disposition: attachment; filename=\"%s\"\r\n"
                 "Connection: close\r\n"
                 "\r\n", filename);

    if (write(client_browser,header,strlen(header))==-1) {
        printf("发送请求头失败");
        exit(1);
    }
    printf("发送请求头成功\n ");

    unsigned long bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        if (write(client_browser, buffer, bytes_read) < 0) {
            perror("Write error to socket");
            break;
        }
    }
    printf("文件发送成功");
    fclose(fp);
    close(client_browser);
}

