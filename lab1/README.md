## task1

**BIOS** 中断号 **0x10**：输出字符串和字符

**msg1** 存储了字符串的信息

**cx** 是字符串长度

**0xAA55** 是校验位，最后必须是这个



## task2

在进入setup时输出

模仿task1的代码，要输出的信息存储在msg2



## task3

输出设备的信息

要输出的信息在 0x9000开始，段寄存器默认设置，因此为[0],[1]。。。。。

主要是函数调用问题，输出数字进制的转化，需要编写函数



因此需要设置ss,sp，即栈来存储

sp设置为0xFF00


