#include "hw_zedboard.h"


int xgpio_myinit(XGpio *InstancePtr, UINTPTR BaseAddr){
	int status=XST_SUCCESS;

	status = XGpio_Initialize(InstancePtr,BaseAddr);
    if(status != XST_SUCCESS){
        return XST_FAILURE;
    }
    XGpio_SetDataDirection(InstancePtr, 1, 0b11);
    XGpio_DiscreteWrite(InstancePtr,1,0);

	return status;
}