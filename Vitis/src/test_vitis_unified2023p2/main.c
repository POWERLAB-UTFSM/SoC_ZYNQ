
/*------------------------------------------------------------------------------------------*/
/* Libraries */
/*------------------------------------------------------------------------------------------*/
#include "hardware_func.h"

/*------------------------------------------------------------------------------------------*/
/* Local definitions */
/*------------------------------------------------------------------------------------------*/
#define XBUFFER_SIZE 50

/*------------------------------------------------------------------------------------------*/
/* Sampled (Tx-Rx Buffer) variables (must be stored in memory section ".data1") */
/*------------------------------------------------------------------------------------------*/
double gv_xbuffer[XBUFFER_SIZE] __attribute__((section (".data1"))) = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0};
//double gv_xbufferb[XBUFFER_SIZE] __attribute__((section (".data1")));
/*------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------*/
/* Global variables */
/*------------------------------------------------------------------------------------------*/
u16 my_comp1=1000;
u16 my_comp2=1000;
u16 my_cmax=2000;
u8 my_eventcount=0;
u32 status_int=XST_FAILURE;

/*------------------------------------------------------------------------------------------*/
/* Interrupt handler declaratios */
/*------------------------------------------------------------------------------------------*/
void _My_IRQHandler();

void _My_FIQHandler();

/*------------------------------------------------------------------------------------------*/
/* Local function declarations */
/*------------------------------------------------------------------------------------------*/
/**
 * @brief Configures the "XCpwm8c" hardware with a level-shifted PWM for 3X-NPC converters at a fixed frequency
 * 
 * @param InstancePtr XCpwm8c instance variable
 */
void XCpwm8c_3lxnpc_My_Init(const XCpwm8c *InstancePtr);

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*------------------------------------------------------------------------------------------*/
/*  main  */
/*------------------------------------------------------------------------------------------*/
int \
main(){
	u32 status= XST_FAILURE;

  //gv_xbuffer[0]=0;

  status = _HW_My_Init();
  //_Buffer_My_Init();

	/*status = XScugic_My_InitInterrupt(\
		xcpwm8c_my_config.IntrId,\
		&xscugic_my_inst,
		&_My_IRQHandler,\
		0xF0U,\
		XINTR_IS_LEVEL_TRIGGERED\
		);*/

	status = XScugic_My_InitFIQInterrupt(\
		&xscugic_my_inst,
		&_My_FIQHandler\
	);


	XCpwm8c_3lxnpc_My_Init(&xcpwm8c_my_inst);

	// _My_XCpwm8c_IntAckGpioPs();
	// XCpwm8c_WriteIntAck(&xcpwm8c_my_inst);

	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Xil_SetTlbAttributes(MY_CPWM8C_0_BASEADDR,0xC02);
	// mtcp(XREG_CP15_INVAL_UTLB_UNLOCKED, 0);
	// dsb();

	while(1){
		// usleep(10);
		// _My_XCpwm8c_IntAckGpioPs();
	}

	return status;
}

/*------------------------------------------------------------------------------------------*/
/*  Interrupt  */
/* _My_IRQHandler() */
/*------------------------------------------------------------------------------------------*/
void \
_My_IRQHandler(){
	//XScuGic_CPUWriteReg(&xscugic_my_inst, XSCUGIC_EOI_OFFSET, XScuGic_CPUReadReg(&xscugic_my_inst, XSCUGIC_INT_ACK_OFFSET));
	// _Buffer_My_Reset();
	/*
	switch(i_cnt){
		case 0:
			XCpwm8c_WriteCompare(&xcpwm8c_my_inst, 0, my_comp1);
			break;
		case 1:
			XCpwm8c_WriteCompare(&xcpwm8c_my_inst, 1, my_comp2);
			break;
		case 2:
			XCpwm8c_WriteCountMax(&xcpwm8c_my_inst, 0, my_cmax);
			break;
	}*/

	// status_int = _Buffer_My_SimpleTransfer();
	_My_XCpwm8c_IntAckGpioPs();
	XScuGic_CPUWriteReg(&xscugic_my_inst, XSCUGIC_EOI_OFFSET, XScuGic_CPUReadReg(&xscugic_my_inst, XSCUGIC_INT_ACK_OFFSET));
	//XCpwm8c_WriteIntAck(&xcpwm8c_my_inst);
}

/*------------------------------------------------------------------------------------------*/
/*  Interrupt  */
/* _My_IRQHandler() */
/*------------------------------------------------------------------------------------------*/
void \
_My_FIQHandler(){
	//_Buffer_My_Reset();
	/*
	switch(i_cnt){
		case 0:
			XCpwm8c_WriteCompare(&xcpwm8c_my_inst, 0, my_comp1);
			break;
		case 1:
			XCpwm8c_WriteCompare(&xcpwm8c_my_inst, 1, my_comp2);
			break;
		case 2:
			XCpwm8c_WriteCountMax(&xcpwm8c_my_inst, 0, my_cmax);
			break;
	}*/

	//status_int = _Buffer_My_SimpleTransfer();
	_My_XCpwm8c_IntAckGpioPs();
	XScuGic_CPUWriteReg(&xscugic_my_inst, XSCUGIC_EOI_OFFSET, XScuGic_CPUReadReg(&xscugic_my_inst, XSCUGIC_INT_ACK_OFFSET));
	//XCpwm8c_WriteIntAck(&xcpwm8c_my_inst);
}

/*------------------------------------------------------------------------------------------*/
/* Local function  */
/* XCpwm8c_3lxnpc_My_Init() */
/*------------------------------------------------------------------------------------------*/
void \
XCpwm8c_3lxnpc_My_Init(\
	const XCpwm8c *InstancePtr\
)
{
	XCpwm8c_WriteCountMax(InstancePtr,0,2000);
	XCpwm8c_WriteCountMax(InstancePtr,1,2000);
	XCpwm8c_WriteCompare(InstancePtr,0,1000);
	XCpwm8c_WriteCompare(InstancePtr,1,1000);
	XCpwm8c_WriteCountMode(InstancePtr,0,COUNT_UP_DOWN);
	XCpwm8c_WriteCountMode(InstancePtr,1,COUNT_UP_DOWN);
	XCpwm8c_WriteEventCount(InstancePtr, 0, 0);
	XCpwm8c_WriteEventCount(InstancePtr, 1, 0);
	XCpwm8c_WriteMaskMode(InstancePtr,0,MIN_MASK);
	XCpwm8c_WriteMaskMode(InstancePtr,1,MIN_MASK);
	XCpwm8c_WriteCarrOnOff(InstancePtr,0,REG_ON);
	XCpwm8c_WriteCarrOnOff(InstancePtr,1,REG_ON);
	XCpwm8c_WriteCarrSel(InstancePtr,0,CARR_MASTER1);
	XCpwm8c_WriteCarrSel(InstancePtr,1,CARR_MASTER1);
	XCpwm8c_WriteDTimeOnOff(InstancePtr,0,REG_OFF);
	XCpwm8c_WriteDTimeOnOff(InstancePtr,1,REG_OFF);
	XCpwm8c_WriteLogicA(InstancePtr,0,LOGIC_NEG);
	XCpwm8c_WriteLogicA(InstancePtr,1,LOGIC_POS);
	XCpwm8c_WriteLogicA(InstancePtr,0,LOGIC_NEG);
	XCpwm8c_WriteLogicA(InstancePtr,1,LOGIC_POS);
	XCpwm8c_WriteIntMatrix(InstancePtr,1);
	XCpwm8c_WritePwmOnOff(InstancePtr,REG_ON);
	XCpwm8c_WriteIntAck(InstancePtr);
}