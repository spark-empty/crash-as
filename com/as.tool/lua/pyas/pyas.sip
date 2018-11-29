/* Define the SIP wrapper to the AS lua library. 
 * python version 3 -- sip 4.17  
 * python version 2 -- sip 4.16.4 
 * http://ftp.ics.uci.edu/pub/centos0/ics-custom-build/BUILD/sip-4.10/doc/html/c_api.html
 */  

%Module AS

class can {

%TypeHeaderCode
#include "pycan.h"
%End

public:
    /* example: can.open(0,'peak'.encode('utf-8'),0,1000000) */
    int open(unsigned long busid,const char* device,unsigned long port, unsigned long baudrate);
    int write(unsigned long busid,unsigned long canid,unsigned long dlc,unsigned char* data);
    int read(unsigned long busid,unsigned long canid,unsigned long* p_canid /Out/,unsigned long *dlc /Out/,unsigned char** data /Out/);
    %MethodCode
            PyObject * pyObj;
            sipRes = sipCpp->read(a0,a1,&a2,&a3,&a4);
            pyObj = sipBuildResult(0,"(immg)",sipRes,a2,a3,a4,(SIP_SSIZE_T)a3);
            if(NULL != a4) {
                free(a4);
            }
            return pyObj;
    %End
    int close(unsigned long busid);
    int reset(unsigned long busid);
};

class asdev {

%TypeHeaderCode
#include "pyasdev.h"
%End

public:
	int open(const char* device, const char* option);
	int write(int fd, unsigned char* data, unsigned long len);
	int read(int fd, unsigned char** data /Out/);
    %MethodCode
            PyObject * pyObj;
            sipRes = sipCpp->read(a0,&a1);
            pyObj = sipBuildResult(0,"(ig)",sipRes,a1,(SIP_SSIZE_T)sipRes);
            if(NULL != a1) {
                free(a1);
            }
            return pyObj;
    %End
    /* rdata out must be with type ascii */
	int ioctl(int fd, int type, unsigned char* data,unsigned long len, unsigned char** rdata /Out/);
    %MethodCode
            PyObject * pyObj;
            sipRes = sipCpp->ioctl(a0,a1,a2,a3,&a4);
            pyObj = sipBuildResult(0,"(is)",sipRes,a4);
            if(NULL != a4) {
                free(a4);
            }
            return pyObj;
    %End
	int close(int fd);
};


