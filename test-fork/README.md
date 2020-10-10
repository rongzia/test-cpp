### 子进程相关内容
参考：  
- [linux中fork（）函数详解](https://www.cnblogs.com/dongguolei/p/8086346.html)
- [孤儿进程与僵尸进程[总结]](https://www.cnblogs.com/lushilin/p/9401494.html)

需要注意的是，尽管 fork 出来的进程 copy 了附父进程的数据，包括指针，但是两个指针并不是同一个，尽管打印出来的指针地址是一样的。  
具体原因是，指针在进程内只是一个偏移量，fork 出的子进程也具有相同的偏移量，并不是实际物理地址。详见 `fork.cpp`。