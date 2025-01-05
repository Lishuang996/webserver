# webserver
webserver是一个小型单线程Web服务器程序，提供根目录下从服务器到浏览器的文件下载功能。
## 快速上手
1. 首先`git clone`下来这个项目
```
git clone https://github.com/Lishuang996/webserver.git
cd webserver
```
2. 修改你的配置文件`configure.txt`
```
ipAddress = 127.0.0.1
port = 27546
root = /home/shuangli/CLionProjects/webserver/root
```
- ipAddress是你的IP地址
- port是你的端口号
- root是需要传输文件的根目录

3. 构建整个项目
```
cmake --build ./cmake-build-debug --target webserver -j 14
```

4. 开始运行
```
./cmake-build-debug/webserver
```
