#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"

#define MY_GPIO0_BASEADDR XPAR_XGPIO_0_BASEADDR


int xgpio_myinit(XGpio *InstancePtr, UINTPTR BaseAddr);