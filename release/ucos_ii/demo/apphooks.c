#include "includes.h"

void App_TaskCreateHook (OS_TCB *ptcb) {}
void App_TaskDelHook (OS_TCB *ptcb) {}
void App_TaskIdleHook (void) {}
void App_TaskReturnHook(OS_TCB *ptcb) {}
void App_TaskSwHook (void) {}
void App_TaskStatHook (void) {}
void App_TimeTickHook (void) {}
void App_TCBInitHook (OS_TCB* ptcb) {}


int puts(const char* str) { return 0; }
