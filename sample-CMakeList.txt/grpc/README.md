grpc 编译、在项目中使用 grpc 是一个比较复杂的问题，在 Makefile 连接 grpc 库还好，`-I` 指定头文件绝对路径，`-L`、`-l` 指定库文件的目录和库名，比如：  
`gcc -I/home/rrzhang/local/grpc/include -L/home/rrzhang/local/grpc/lib64 -lgrpc`。

但是在 CmakeLists.txt 中并不是这么简单，尤其是系统里存在多个版本的 grpc 时，寻找指定的库尤为困难。比如系统里一般在 `/usr/local/include /usr/bin /usr/lib /usr/lib64` 几个目录下，cmake 中 find_package 也会默认从这里寻找库。

这个文件夹主要示例 cmake 如何寻找 grpc。

> [编译安装 grpc 参考](http://note.youdao.com/noteshare?id=f8d0d50294dffbbf7b731336fd4d9ded&sub=WEBe53dd9ea5523bd2834c37fc4e5634f62)

> [cmake() - 寻找头文件和lib](http://note.youdao.com/noteshare?id=79d29d8a99d65bc30b04538d083313b8&sub=FF0334B7D1CC4ED79C5A122F91B9BB1C)

