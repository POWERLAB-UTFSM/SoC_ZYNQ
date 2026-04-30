#ifndef HDFCPWM_H
#define HDFCPWM_H

#include "xparameters.h"
#include "xstatus.h"
#include "xil_types.h"

#include "xscugic.h"
#include "xil_exception.h"

#include "xcpwm6b.h"

/*************** BASE ADDR ***************/
#define MY_CPWM6B_0_BASEADDR XPAR_AXI_CPWM_6B_0_BASEADDR
#define MY_SCUGIC_DEVICE_ID  XPAR_SCUGIC_0_DEVICE_ID

/* ⚠️ à vérifier dans xparameters.h */
#define MY_CPWM6B_INTR_ID    XPAR_FABRIC_AXI_CPWM_6B_0_SYNC_EVENT_INTR

/*************** INSTANCES ***************/
extern XCpwm6b xcpwm6b_my_inst;
extern XScuGic xscugic_my_inst;

/*************** FUNCTIONS ***************/
int _HW_My_Init(void);

int XCpwm6b_My_Init(XCpwm6b *InstancePtr, UINTPTR BaseAddr);
int GIC_Init(XScuGic *GicInstancePtr);

void CPWM6B_InterruptHandler(void *CallbackRef);

#endif