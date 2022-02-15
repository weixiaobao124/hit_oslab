#define __LIBRARY__
#include <unistd.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <errno.h>

shm shm_list[100];

int sys_shmget(unsigned int id, size_t size)
{
	int i;
	unsigned long page;
  	
    if(size>PAGE_SIZE){
      	return -EINVAL;
 	 }
  	for(i=0; i<100; i++){
      	if(shm_list[i].id == id)
          	return i;
  	}
	page = get_free_page();
	if(!page)
		return -ENOMEM;
  	
    for(i=0; i<100; i++){
      	if(shm_list[i].id==0) //not allocate
      	{
          	shm_list[i].id = id;
          	shm_list[i].size = size;
          	shm_list[i].page = page;
          	return i;
      	}	
  	}
	return -1;
}

void * sys_shmat(int shmid)
{
 	 unsigned long data_base, brk;
 	 if(shmid < 0 || 100 <= shmid || shm_list[shmid].id == 0)
      	return (void *)-EINVAL;

	/*data_base:data基址(虚拟)*/
    /*shmget已经找到了合适的物理地址空间，此处需要在进程的虚拟地址空间中找到一块空闲的分配*/
  	data_base = get_base(current->ldt[2]);
  	/*  当前进程的虚拟地址 + brk在虚拟内存中的偏移 = brk的虚拟地址*/
  	brk = data_base + current->brk;
    //紧接着brk的为一块空闲空间
  	current->brk += PAGE_SIZE;
  	if(put_page(shm_list[shmid].page, brk) == 0)
      	return (void *)-ENOMEM;

  	return (void *)(current->brk - PAGE_SIZE);
 }


