/* Define the SIP wrapper to the Can library. 
 * python version 3 */  
%Module(name=Can, language="C")  

typedef unsigned char       		uint8;
typedef unsigned short      		uint16;
typedef unsigned long       		uint32;
typedef uint8                       Std_ReturnType;
struct CanPduType {
    /* the CAN ID, 29 or 11-bit */
	uint32   	id;
	uint8		length;
	uint8 		sdu
	{
		%GetCode
			sipPy = PyList_New(8);
			for(int i=0;i<8;i++)
			{
				PyList_SetItem(sipPy,i,PyLong_FromLong(sipCpp->sdu[i]));
			}
		%End
		
		%SetCode
			unsigned int length = PyList_Size(sipPy);
			if(length > 8)
			{
				PyErr_SetString(PyExc_ValueError,"the sdu must be < 8 bytes");
				sipErr = 1;
			}
			else
			{
				for(int i=0;i<length;i++)
				{
					sipCpp->sdu[i] = PyLong_AsLong(PyList_GetItem(sipPy,i));
				}
				
				sipCpp->length = length;
			}
		%End
	};
};
typedef CanPduType Can_PduType;

Std_ReturnType Can_Init(uint32 port,uint32 baudrate);
Std_ReturnType Can_DeInit(uint32 port);
Std_ReturnType Can_Receive(uint32 port,char** message);
Std_ReturnType Can_Write(uint32  port, Can_PduType *pduInfo /In/);
