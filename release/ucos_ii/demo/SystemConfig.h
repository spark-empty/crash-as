#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#define _CRT_SECURE_NO_WARNINGS	

#include <stdio.h>
#include <assert.h>
#include <includes.h>		
/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define MainTask_Prio 5
#define App1Task_Prio 7
#define App2Task_Prio 9

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/
#ifdef __9S12__
#define MainTask_StkSize 256
#define App1Task_StkSize 256
#define App2Task_StkSize 256
#else
#ifdef __arch_dos__
#define MainTask_StkSize 4096
#define App1Task_StkSize 4096
#define App2Task_StkSize 4096
#else
#define MainTask_StkSize 1024
#define App1Task_StkSize 1024
#define App2Task_StkSize 1024
#endif
#endif
#define OS_IDLE_PRIO OS_TASK_IDLE_PRIO
#define OS_STAT_PRIO OS_TASK_STAT_PRIO


extern void MainTask(void *p_arg);
extern void App1Task(void *p_arg);
extern void App2Task(void *p_arg);

#endif
