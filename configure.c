//
// Created by shuangli on 25-1-4.
//

#include "configure.h"

// 根据配置文件修改ip地址
void get_ip_address(char* ip_address) {
    FILE* fp = fopen("../configure.txt","rb");
    if (fp==NULL) return;
    char buffer[300] = {0};
    fread(buffer, 1, sizeof(buffer), fp);
    char *p = buffer+12;
    int k = 0;
    while (*(p+k)!='\n') k++;
    *(p+k) = '\0';
    strcpy(ip_address,p);
}

// 根据配置文件修改根目录
void getRoot(char* root) {
    FILE* fp = fopen("../configure.txt","rb");
    if (fp==NULL) return;
    char buffer[300] = {0};
    fread(buffer, 1, sizeof(buffer), fp);
    char *p = strstr(buffer,"root");
    p = p+7;
    int k = 0;
    while (*(p+k)!='\0') k++;
    *(p+k) = '\0';
    strcpy(root,p);
}

// 根据配置文件修改端口
void getPort(int* port) {
    FILE* fp = fopen("../configure.txt","rb");
    if (fp==NULL) return;
    char buffer[300] = {0};
    fread(buffer, 1, sizeof(buffer), fp);
    char *p = strstr(buffer,"port");
    p = p+7;
    int k = 0;
    while (*(p+k)!='\n') k++;
    *(p+k) = '\0';
    char *end = NULL;
    *port = strtol(p,&end,0);
}
