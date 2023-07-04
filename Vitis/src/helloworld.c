/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
//#include "platform.h"
//#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"
#include "sleep.h"
//#include "xgpio.h"
#include "axi_cpwm8c.h"
#include "xgpiops.h"
//#include "axi4fulltest.h"
//#include "xclk_wiz.h"
#include "xscugic.h"
#include "xil_types.h"
#include "xil_mmu.h"
#include "xdmaps.h"

u16 globalpwm_period=2000;
u16 globalpwm_compare=1000;


u8 pwm_intmatrix=255;

#define INTC_INTERRUPT_ID_0 XPAR_FABRIC_AXI_CPWM8C_0_VEC_ID
// instance of interrupt controller
static XScuGic intc;

int setup_interrupt_system(u16 DeviceId, u16 InterruptId);
void isr0 (void *intc_inst_ptr);
void fiq_handler (void *intc_inst_ptr);
void cpwm8c_init();
int setup_FIQ_interrupt_system(u16 DeviceId);

XGpioPs_Config *xgpioptr;
XGpioPs xgpio;

float ans=5.2e4;
float k[4]={5.2e4,2.5,-3.2,1.05e2};
float con[100];

u32 count=0;
u32 j=0;



int main()
{
	//Xil_SetTlbAttributes(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,0xC02);
	//mtcp(XREG_CP15_INVAL_UTLB_UNLOCKED, 0);
	//dsb();
	int status = XST_SUCCESS;

	xgpioptr= XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
	status=XGpioPs_CfgInitialize(&xgpio,xgpioptr,xgpioptr->BaseAddr);
	XGpioPs_SetDirection(&xgpio,2,1);
	XGpioPs_SetOutputEnable(&xgpio,2,1);

	cpwm8c_init();

	//status = setup_interrupt_system(XPAR_PS7_SCUGIC_0_DEVICE_ID,INTC_INTERRUPT_ID_0);
	status = setup_FIQ_interrupt_system(XPAR_PS7_SCUGIC_0_DEVICE_ID); //initialize fast interrupt (FIQ) on channel "XPAR_PS7_SCUGIC_0_DEVICE_ID"
	if (status != XST_SUCCESS)   {
	           return XST_FAILURE;
	    }
	while (1){
	}

//    cleanup_platform();
    return 0;
}

void isr0 (void *intc_inst_ptr) {
	//u32 IntIDFull;

	//AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_period);
	AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_compare);
	//AXI_CPWM8C_mWrite_Period_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
	//AXI_CPWM8C_mWrite_Period_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
	//AXI_CPWM8C_mWrite_Period_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);


	/*for(j=0;j<100;j++){
		(j!=0) ? (ans=con[j-1]) : (ans=0);
		con[j]=ans+k[0]+k[1]+k[2]+k[3];
	}*/
	//AXI4LITETEST_mWriteReg(XPAR_AXI4LITETEST_0_S00_AXI_BASEADDR, 4, pwm_comp1);
	//-------------------------------------------------------------
	//Clear interrupt in PS
	//-------------------------------------------------------------
	//IntIDFull = XScuGic_CPUReadReg(&intc, XSCUGIC_INT_ACK_OFFSET);
	//XScuGic_CPUWriteReg(&intc, XSCUGIC_EOI_OFFSET, IntIDFull);
	//-------------------------------------------------------------
	//Clear interrupt in PL (AXI_CPWM8C)
	//-------------------------------------------------------------
	//AXI4LITETEST_mWriteReg(XPAR_AXI4LITETEST_0_S_AXI_BASEADDR, AXI4LITETEST_S_AXI_SLV_REG6_OFFSET,2);
	//AXI_CPWM8C_IntAck(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR);
	XGpioPs_WritePin(&xgpio, 54, 1);
	XGpioPs_WritePin(&xgpio, 54, 0);

}

void fiq_handler (void *intc_inst_ptr) {
	//u32 IntIDFull;

	//AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
	AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_compare);
	//AXI_CPWM8C_mWrite_Period_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
	//AXI_CPWM8C_mWrite_Period_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);


	/*for(j=0;j<100;j++){
		(j!=0) ? (ans=con[j-1]) : (ans=0);
		con[j]=ans+k[0]+k[1]+k[2]+k[3];
	}*/
	//AXI4LITETEST_mWriteReg(XPAR_AXI4LITETEST_0_S00_AXI_BASEADDR, 4, pwm_comp1);
	//-------------------------------------------------------------
	//Clear interrupt in PS
	//-------------------------------------------------------------
	//IntIDFull = XScuGic_CPUReadReg(&intc, XSCUGIC_INT_ACK_OFFSET);
	//XScuGic_CPUWriteReg(&intc, XSCUGIC_EOI_OFFSET, IntIDFull);
	//-------------------------------------------------------------
	//Clear interrupt in PL (AXI_CPWM8C)
	//-------------------------------------------------------------
	//AXI4LITETEST_mWriteReg(XPAR_AXI4LITETEST_0_S_AXI_BASEADDR, AXI4LITETEST_S_AXI_SLV_REG6_OFFSET,2);
	//AXI_CPWM8C_IntAck(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR);
	XGpioPs_WritePin(&xgpio, 54, 1);
	XGpioPs_WritePin(&xgpio, 54, 0);

}

// sets up the interrupt system and enables interrupts for IRQ_F2P[1:0]
int setup_interrupt_system(u16 DeviceId, u16 InterruptId) {

    int result;
    XScuGic *intc_instance_ptr = &intc;
    XScuGic_Config *intc_config;

    // get config for interrupt controller
    intc_config = XScuGic_LookupConfig(DeviceId);
    if (NULL == intc_config) {
        return XST_FAILURE;
    }

    // initialize the interrupt controller driver
    result = XScuGic_CfgInitialize(intc_instance_ptr, intc_config, intc_config->CpuBaseAddress);

    if (result != XST_SUCCESS) {
        return result;
    }

    // set the priority of IRQ_F2P[0:0] to 0xA0 (highest 0xF8, lowest 0x00) and a trigger for a rising edge trigger 0x3.
    XScuGic_SetPriorityTriggerType(intc_instance_ptr,InterruptId, 0xA0, 0x3);

    // connect the interrupt service routine isr0 to the interrupt controller
    result = XScuGic_Connect(intc_instance_ptr,InterruptId, (Xil_ExceptionHandler)isr0, (void *)&intc);

    if (result != XST_SUCCESS) {
        return result;
    }

    // enable interrupts for IRQ_F2P[0:0]
    XScuGic_Enable(intc_instance_ptr,InterruptId);

    // initialize the exception table and register the interrupt controller handler with the exception table
    Xil_ExceptionInit();

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, intc_instance_ptr);

    // enable non-critical exceptions
    Xil_ExceptionEnable();

    return XST_SUCCESS;
}

// sets up the interrupt system and enables interrupts for FIQ
int setup_FIQ_interrupt_system(u16 DeviceId)
{
	int result;
	XScuGic *intc_instance_ptr = &intc;
	XScuGic_Config *intc_config;


	//Initialize the interrupt controller driver so that it is ready to use.

	intc_config = XScuGic_LookupConfig(DeviceId);
	if (NULL == intc_config) {
		return XST_FAILURE;
	}

	result = XScuGic_CfgInitialize(intc_instance_ptr, intc_config, intc_config->CpuBaseAddress);
	if (result != XST_SUCCESS) {
		return XST_FAILURE;
	}

	 //Perform a self-test to ensure that the hardware was built correctly

	result = XScuGic_SelfTest(intc_instance_ptr);
	if (result != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_FIQ_INT,(Xil_ExceptionHandler) fiq_handler,intc_instance_ptr);

	Xil_ExceptionEnableMask(XIL_EXCEPTION_FIQ);

	return XST_SUCCESS;
}

void cpwm8c_init()
{
	u16 pwm_period=2000;
	u16 pwm_init=0;
	u16 pwm_comp1=1000;
	u8 pwm_eventcount=0;
	u8 pwm_dtimeA=0;
	u8 pwm_dtimeB=0;
	AXI_CPWM8C_count_mode pwm_countmode=COUNT_UP_DOWN;
	AXI_CPWM8C_mask_mode pwm_maskmode=MIN_MASK;
	AXI_CPWM8C_onoff pwm_dtonoff=REG_OFF;
	AXI_CPWM8C_logic pwm_logicA=LOGIC_POS;
	AXI_CPWM8C_logic pwm_logicB=LOGIC_POS;
	AXI_CPWM8C_carrsel pwm_carrsel=CARR_MASTER1;
	AXI_CPWM8C_onoff pwm_onoff=REG_ON;
	AXI_CPWM8C_onoff pwm_carronoff=REG_ON;

	AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
	AXI_CPWM8C_mWrite_InitCarrier_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_init);
	AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
	AXI_CPWM8C_mWrite_DeadTimeA_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
	AXI_CPWM8C_mWrite_DeadTimeB_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
	AXI_CPWM8C_mWrite_EventCount_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
	AXI_CPWM8C_mWrite_InterruptMatrix(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_intmatrix);
	AXI_CPWM8C_mWrite_CountMode_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
	AXI_CPWM8C_mWrite_MaskMode_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
	AXI_CPWM8C_mWrite_DTimeOnOff_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
	AXI_CPWM8C_mWrite_LogicA_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
	AXI_CPWM8C_mWrite_LogicB_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
	AXI_CPWM8C_mWrite_CarrSel_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
	AXI_CPWM8C_mWrite_CarrOnOff_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carronoff);
	AXI_CPWM8C_mWrite_PWMOnOff(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_onoff);
	AXI_CPWM8C_IntAck(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR);
}
