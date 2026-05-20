#ifndef HDFCPWM_H
#define HDFCPWM_H

#include "xparameters.h"
#include "xstatus.h"
#include "xil_types.h"
#include "xintc.h"
#include "xil_exception.h"

#include "xcpwm6b.h"


#include "xcommon_drv_config.h"
#include "xplatform_info.h"
#include "xscugic.h"
#include "xinterrupt_wrap.h"

/*************** BASE ADDR ***************/
#define MY_CPWM6B_0_BASEADDR XPAR_AXI_CPWM_6B_0_BASEADDR
#define MY_SCUGIC_DEVICE_ID  XPAR_SCUGIC_SINGLE_DEVICE_ID
#define INTC_IRQ_ID XPAR_FABRIC_AXI_INTC_0_INTR


/*************** INSTANCES ***************/
extern XCpwm6b xcpwm6b_my_inst;
extern XScuGic xscugic_my_inst;
extern XIntc   xintc_my_inst;

/*************** FUNCTIONS ***************/
int _HW_My_Init(void);

int XCpwm6b_My_Init(XCpwm6b *InstancePtr, UINTPTR BaseAddr);
int GIC_Init(XScuGic *GicInstancePtr);
int INTC_Init(XIntc *IntcInstancePtr);
void CPWM6B_InterruptHandler(void *CallbackRef);

#endif