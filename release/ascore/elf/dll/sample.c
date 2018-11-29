#include <stdio.h>
#ifdef USE_PTHREAD
#include <pthread.h>
#endif
#include <unistd.h>

void goodBye(void)
{
	printf("Good Bye!\n");
}

void* child(void* arg)
{
	int id = (int)arg;
	int counter = 0;

	while(1)
	{
		printf("child%d is running %d\n",counter++);
		sleep(1);
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	int i;
	FILE* fp;

	fp = fopen("hello.txt","w+");

	for(i=0; i<argc; i++)
	{
		if(fp != NULL)
		{
			fprintf(fp, "argv[%d] = %s\n", i, argv[i]);
		}
		else
		{
			printf("argv[%d] = %s\n", i, argv[i]);
		}
	}

	if(fp != NULL)
	{
		fclose(fp);
	}

	printf("Hello World!\n");
#ifdef USE_PTHREAD
	pthread_create(NULL,NULL, child, (void*)1);
	pthread_create(NULL,NULL, child, (void*)2);
	sleep(5);
#endif
	goodBye();
	return 0;
}
