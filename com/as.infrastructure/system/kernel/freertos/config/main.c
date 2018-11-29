#include <stdio.h>
#include <assert.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void Task1( void * param)
{
	while(1)
	{
		printf("Task1 is running!\n");
		vTaskDelay(10);
	}
}
void Task2( void * param)
{
	while(1)
	{
		printf("Task2 is running!\n");
		vTaskDelay(10);
	}
}
int main( int argc, char* argv[] )
{
	/* Start the tasks and timer running. */
	xTaskCreate( Task1, "Tasl1", 1024, NULL, 1, NULL );
	xTaskCreate( Task2, "Tasl2", 1024, NULL, 1, NULL );
	vTaskStartScheduler();
	return 0;
}

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
	_assert(__FUNCTION__, pcFileName, ulLine);
}

unsigned long ulGetRunTimeCounterValue( void )
{
	return 0;
}

void vConfigureTimerForRunTimeStats( void )
{

}
