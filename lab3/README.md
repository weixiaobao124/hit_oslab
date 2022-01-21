需要在==内核==中写文件，`write`是提供给用户的api，因此在内核中需要用`sys_write`



`fprintk`是内核中函数，调用了sys_write()

fprintk(3, "%ld\t%c\t%ld\n", current->pid, 'R', jiffies);



jiffies 在每次中断(int 0x20)的处理函数中+1



关键是找到：**进程状态切换点**



fork->sys_fork(汇编)->调用copy_process完成进程创建

copy_process在`kernerl/fork.c`中



其中就绪与运行间的状态转移是通过 `schedule()`（它亦是调度算法所在）完成的；运行到睡眠依靠的是 `sleep_on()` 和 `interruptible_sleep_on()`，还有进程主动睡觉的系统调用 `sys_pause()` 和 `sys_waitpid()`；睡眠到就绪的转移依靠的是 `wake_up()`。




