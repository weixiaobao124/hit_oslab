### 实验6 地址映射与共享

上一个实验实现了用信号量控制生产者-消费者程序，代码写在同一个.c文件中，共享一块空间。本次实验需要另外新增系统调用，shmat,shmget系统调用，使得不同进程能够共享同一物理地址空间。

通过**信号量**和**共享缓冲区**进行进程间的通信。



lab0.1：就是熟悉一些调试命令，对照实验指导书按部就班

lab0.2：实现shmat,shmget系统调用，使得不同进程能够共享同一物理地址空间。

- shmget()

```c
int shmget(key_t key, size_t size, int shmflg);
```

`shmget()` 会新建/打开一页内存，并返回该页共享内存的 shmid（该块共享内存在操作系统内部的 id）。

所有使用同一块共享内存的进程都要使用相同的 key 参数。

如果 key 所对应的共享内存已经建立，则直接返回 `shmid`。如果 size 超过一页内存的大小，返回 `-1`，并置 `errno` 为 `EINVAL`。如果系统无空闲内存，返回 -1，并置 `errno` 为 `ENOMEM`。

`shmflg` 参数可忽略。

- shmat()

```c
void *shmat(int shmid, const void *shmaddr, int shmflg);
```

`shmat()` 会将 `shmid` 指定的共享页面映射到当前进程的虚拟地址空间中，并将其首地址返回。

如果 `shmid` 非法，返回 `-1`，并置 `errno` 为 `EINVAL`。

`shmaddr` 和 `shmflg` 参数可忽略。



![在这里插入图片描述](https://img-blog.csdnimg.cn/9a4736a3c76f45c89bd236bcec303a6d.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM3ODU3MjI0,size_16,color_FFFFFF,t_70)




