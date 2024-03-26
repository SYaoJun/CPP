# 基础语法
- 移动构造和赋值
- 拷贝构造和赋值
- 条件变量
- 多线程
- promise和future
## 编译命令
```sh
./main -t=hello -n=yaojun
./main -tag=hello -name=yaojun
```
## jemalloc
- 是用来干嘛的？什么场景用得上？
```sh
echo /usr/local/lib >> /etc/ld.so.conf
ldconfig
gcc jemalloc.c -o jemalloc -ljemalloc
```
