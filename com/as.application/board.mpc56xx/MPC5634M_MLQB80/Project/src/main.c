#include "MPC5634M_MLQB80.h"

#pragma section RX ".flscode" code_mode=far_abs

void __declspec (section ".flscode") fls_test(void);
int main(void) {
	EcuM_Init();
	fls_test();
	while(1);
	return 0;
}



__declspec (section ".flscode") void fls_test(void)
{
	
}




