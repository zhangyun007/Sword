/* 
作者：chenyu...... 
来源：CSDN 
原文：https://blog.csdn.net/u011068702/article/details/82532482 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
 
 /* 结构体里放函数指针，类似于C++里的class*/
typedef struct key_info 
{
	int (*init)(struct key_info *info);
	int (*set_name)(struct key_info *info, const char *name);
	int (*get_name)(struct key_info *info, char name[], int size);
	pthread_mutex_t lock;	
	char name[128];
	int (*fun)(struct key_info *info, int x, int y);
}KeyInfo;
 
static int init(KeyInfo *info);
static int set_name(KeyInfo *info, const char *name);
static int get_name(KeyInfo *info, char name[], int size);
static int add(int x, int y);
 
static int add(KeyInfo *info, int x, int y)
{
	return x + y;	
}
static int init(KeyInfo *info)
{
	assert(info != NULL);
	memset(info->name, 0, sizeof(info->name));
	info->init = init;
	info->set_name = set_name;
	info->get_name = get_name;
	return pthread_mutex_init(&info->lock, NULL);
}
 
static int set_name(KeyInfo *info, const char *name)
{
	assert(name != NULL);
	pthread_mutex_lock(&info->lock);
	strncpy(info->name, name, sizeof(info->name) - 1);
	pthread_mutex_unlock(&info->lock);
}
 
static int get_name(KeyInfo *info, char name[], int size)
{
	assert(name != NULL);
	pthread_mutex_lock(&info->lock);
    strncpy(name, info->name, size - 1);	
	*(name + size - 1) = 0;
	pthread_mutex_unlock(&info->lock);
}
 
 
int main()
{
/**	KeyInfo info;
	info.fun = add;
	printf("add(1 + 8) is %d\n", info.fun(&info, 1, 8));
	info.set_name = set_name;
	info.get_name = get_name;
	info.set_name(&info, "chenyu");
	char name[100];
	info.get_name(&info, name, sizeof(name));
	printf("info.get_name is %s\n", name);
**/
	KeyInfo info = {init};
	info.init(&info);
	const char *name = "chenyu";
	info.set_name(&info, name);
	char name_buf[100];
	printf("sizeof(name_buf[100]) is %d\n", sizeof(name_buf));
	info.get_name(&info, name_buf, sizeof(name_buf));
	printf("info.get_name is %s\n", name_buf);
	return 0;
}