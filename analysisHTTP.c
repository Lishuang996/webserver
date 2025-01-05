//
// Created by shuangli on 25-1-4.
//

#include "include/analysisHTTP.h"
#include <stdio.h>
#include <stdlib.h>
extern char ip_address[50];
extern int port; // 端口号
extern char root[50]; //根目录 必须是绝对路径

// 解析出所需文件的路径
char* getRoute(char *buffer) {
    char *from = strstr(buffer,"GET");
    from += 4;
    char *to = strstr(buffer,"HTTP/");
    to--;
    *to = '\0';
    static char route[50] = {0};
    strcpy(route,root);
    strcat(route,from);
    return route;
}

// 解析出所需文件的文件名
char* getFilename(char *buffer) {
    char *from = strstr(buffer,"GET");
    char *p = NULL;
    for (int i = 0;from[i]!='\0';i++) {
        if (from[i]=='/') p = from+i;
    }
    from = p+1;
    if (from==NULL) {
        printf("无法获取\n");
        exit(1);
    }
    static char name[50] = {0};
    strcpy(name,from);
    return name;
}
