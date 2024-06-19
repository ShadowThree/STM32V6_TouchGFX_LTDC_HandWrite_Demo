#ifndef __ATK_NCR_H
#define __ATK_NCR_H
#include "stdint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//本数字字母识别程序由ALIENTEK提供,我们提供2个LIB,供大家使用
//ATKNCR_M_Vx.x.lib和ATKNCR_N_Vx.x.lib的唯一区别是是否使用动态内存分配.
//其中:M,代表需要用到malloc的版本,必须实现alientek_ncr_malloc和alientek_ncr_free两个函数
//     N,代表普通版本,不需要实现alientek_ncr_malloc和alientek_ncr_free两个函数
//     Vx.x,代表当前识别程序的版本.		 	  
//功能:支持数字/小写字母/大写字母/混合四种识别模式.		  
//本识别程序使用起来相当简单.					   
//第一步:调用alientek_ncr_init函数,初始化识别程序
//第二步:获取输入的点阵数据(必须有2个及以上的不同点阵数据输入)
//第三步:调用alientek_ncr函数,得到识别结果.
//第四步:如果不需要再识别,则调用alientek_ncr_stop函数,终止识别.如果还需要继续,则重复2,3步即可.		   
//版本:V2.0
//正点原子@ALIENTEK
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved													    								  
//版权所有，盗版必究。
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//当使用ATKNCR_M_Vx.x.lib的时候,不需要理会ATK_NCR_TRACEBUF1_SIZE和ATK_NCR_TRACEBUF2_SIZE
//当使用ATKNCR_N_Vx.x.lib的时候,如果出现识别死机,请适当增加ATK_NCR_TRACEBUF1_SIZE和ATK_NCR_TRACEBUF2_SIZE的值
#define ATK_NCR_TRACEBUF1_SIZE	500*4  	//定义第一个tracebuf大小(单位为字节),如果出现死机,请把该数组适当改大
#define ATK_NCR_TRACEBUF2_SIZE	250*4	//定义第二个tracebuf大小(单位为字节),如果出现死机,请把该数组适当改大

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//输入轨迹坐标类型
//__packed typedef struct _atk_ncr_point		// ARM_compiler_v5
typedef struct __attribute__((packed)) _atk_ncr_point		// ARM_compiler_v6
{
	short x; 	//x轴坐标
	short y;	//y轴坐标
}atk_ncr_point;		

// recognize mode
#define RECOGNIZE_123		1
#define RECOGNIZE_ABC		2
#define RECOGNIZE_abc		3
#define RECOGNIZE_Aa1		4
// output number
#define CHAR_NUM	6
// max point to record
#define MAX_POINT		1000
// alientek_ncr_init() malloc HEAP size for ATKNCR_M_V2.0.lib
//#define ATK_INIT_HEAP_SIZE	(512+512+512+160+64+64+496)		// 2320Bytes; info source: LOG from alientek_ncr_malloc()
extern atk_ncr_point draw_coor[MAX_POINT];
extern volatile uint16_t point_num;
extern char result[CHAR_NUM+1];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//外部调用函数
//初始化识别器
//返回值:0,初始化成功
//       1,初始化失败
unsigned char alientek_ncr_init(void);
//停止识别器
void alientek_ncr_stop(void);

//识别器识别
//track:输入点阵集合 
//potnum:输入点阵的点数,就是track的大小
//charnum:期望输出的结果数,就是你希望输出多少个匹配结果
//mode:识别模式
//1,仅识别数字
//2,仅识别大写字母
//3,仅识别小写字母
//4,混合识别(全部识别)
//result:结果缓存区(至少为:charnum+1个字节)	
/** @note: the track will be changed! */
void alientek_ncr(atk_ncr_point * track,int potnum,int charnum,unsigned char mode,char*result);

//内存设置函数 
void alientek_ncr_memset(char *p,char c,unsigned long len);	
//动态申请内存,当使用ATKNCR_M_Vx.x.lib时,必须实现.
void *alientek_ncr_malloc(unsigned int size);			 
//动态释放内存,当使用ATKNCR_M_Vx.x.lib时,必须实现.
void alientek_ncr_free(void *ptr);						 	    
#endif



