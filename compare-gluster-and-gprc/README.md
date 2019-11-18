
util 是一些工具：
1. profiler.h	计时
2. file_system.h	文件读写
3. exception.h	异常
4. string_util.h 随机字符串生成

## how to run
修改 gluster 读写文件的目录。
```
	mkdir build
	cd build
	cmake ../
	make
```
or 
```
	mkdir build
	cd build
	make
```
在 build 下生成对应的多个文件夹，每个文件夹下有对应的可执行文件。
