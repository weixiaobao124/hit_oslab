#include <asm/segment.h>
#include <errno.h>

#include <linux/kernel.h>

char str[23];
//do not want to check lenth
int sys_iam(const char * name)
{
    int i = 0;
    while (get_fs_byte(name + i) != 0)
    {
        str[i] = get_fs_byte(name + i);
        i ++;
    }
    str[i] = 0;
    return i;
}

int sys_whoami(char *name, unsigned int size)
{
    int i = 0;
    while (str[i] != 0)
    {
        put_fs_byte(str[i], name + i);
        i ++;
    }
    put_fs_byte(0, name + i);

    return i;
}
