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
#include "axi4fulltest.h"
//#include "xclk_wiz.h"
#include "xscugic.h"
#include "xil_types.h"
#include "xil_mmu.h"
#include "xdmaps.h"
//#include "AXI_CPWM.h"

u32 memread=0;
u32 gpio_reg0=0;
u32 pwm_reg0=0;
u32 pwm_reg1=0;
u32 pwm_reg2=0;
u32 pwm_reg3=0;
u32 pwm_reg4=0;
u32 pwm_reg5=0;
u32 pwm_reg6=0;
u32 pwm_reg7=0;
u32 pwm_reg8=0;
u32 pwm_reg9=0;
u32 pwm_reg10=0;
u32 pwm_reg11=0;
u32 pwm_reg12=0;
u32 pwm_reg13=0;
u32 pwm_reg14=0;
u32 pwm_reg15=0;
u32 pwm_reg16=0;
u32 pwm_reg17=0;
u32 pwm_reg18=0;
u32 pwm_reg19=0;
u32 pwm_reg20=0;
u32 pwm_reg21=0;
u16 pwm_period=2000;
u16 pwm_init=0;
u16 pwm_comp1=1000;
u16 pwm_comp2=1000;
u16 pwm_comp3=0;
u16 pwm_comp4=0;
u8 pwm_eventcount=0;
/*
AXI_CPWM_count_mode pwm_countmode=COUNT_UP_DOWN;
AXI_CPWM_mask_mode pwm_maskmode=MIN_MASK;
AXI_CPWM_onoff pwm_pwmonoff=REG_ON;
AXI_CPWM_onoff pwm_intonoff=REG_ON;
AXI_CPWM_onoff pwm_pwmclkdivonoff=REG_OFF;
AXI_CPWM_onoff pwm_dtclkdivonoff=REG_OFF;
*/
u8 pwm_dtimeA=0;
AXI_CPWM8C_onoff pwm_carronoff=REG_ON;
u8 pwm_dtimeB=0;
u8 pwm_carrclkdiv=0;
u8 pwm_dtclkdiv=0;
AXI_CPWM8C_count_mode pwm_countmode=COUNT_UP_DOWN;
AXI_CPWM8C_mask_mode pwm_maskmode=MIN_MASK;
AXI_CPWM8C_onoff pwm_dtonoff=REG_OFF;
AXI_CPWM8C_logic pwm_logicA=LOGIC_POS;
AXI_CPWM8C_logic pwm_logicB=LOGIC_POS;
AXI_CPWM8C_carrsel pwm_carrsel=CARR_MASTER1;
AXI_CPWM8C_onoff pwm_onoff=REG_ON;
u8 pwm_clksel=1;

//u8 pwm_logicA=0;
//u8 pwm_logicB=0;
u8 pwm_intmatrix=255;

#define INTC_INTERRUPT_ID_0 XPAR_FABRIC_AXI_CPWM8C_0_INTERRUPT_INTR
// instance of interrupt controller
static XScuGic intc;

int setup_interrupt_system();
void isr0 (void *intc_inst_ptr);
void cpwm8c_init();



int main()
{
	Xil_SetTlbAttributes(XPAR_AXI4FULLTEST_0_S00_AXI_BASEADDR,0xC02);
	mtcp(XREG_CP15_INVAL_UTLB_UNLOCKED, 0);
	dsb();
	int status = XST_SUCCESS;

	status = setup_interrupt_system();
	if (status != XST_SUCCESS)   {
	           return XST_FAILURE;
	    }
	cpwm8c_init();
	while (1){
	}

//    cleanup_platform();
    return 0;
}

void isr0 (void *intc_inst_ptr) {
	//u32 IntIDFull;

	//AXI4FULLTEST_mWriteMemory(XPAR_AXI4FULLTEST_0_S00_AXI_BASEADDR, 1);
	//memread=AXI4FULLTEST_mReadMemory(XPAR_AXI4FULLTEST_0_S00_AXI_BASEADDR);
	//AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
	//-------------------------------------------------------------
	//Clear interrupt in PL (AXI_CPWM8C)
	//-------------------------------------------------------------
	AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG6_OFFSET,2);
	AXI_CPWM8C_IntAck(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR);
	//-------------------------------------------------------------
	//Clear interrupt in PS
	//-------------------------------------------------------------
	//IntIDFull = XScuGic_CPUReadReg(&intc, XSCUGIC_INT_ACK_OFFSET);
	//XScuGic_CPUWriteReg(&intc, XSCUGIC_EOI_OFFSET, IntIDFull);
}

// sets up the interrupt system and enables interrupts for IRQ_F2P[1:0]
int setup_interrupt_system() {

    int result;
    XScuGic *intc_instance_ptr = &intc;
    XScuGic_Config *intc_config;

    // get config for interrupt controller
    intc_config = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
    if (NULL == intc_config) {
        return XST_FAILURE;
    }

    // initialize the interrupt controller driver
    result = XScuGic_CfgInitialize(intc_instance_ptr, intc_config, intc_config->CpuBaseAddress);

    if (result != XST_SUCCESS) {
        return result;
    }

    // set the priority of IRQ_F2P[0:0] to 0xA0 (highest 0xF8, lowest 0x00) and a trigger for a active high trigger 0x3.
    XScuGic_SetPriorityTriggerType(intc_instance_ptr, INTC_INTERRUPT_ID_0, 0xA0, 0x3);

    // connect the interrupt service routine isr0 to the interrupt controller
    result = XScuGic_Connect(intc_instance_ptr, INTC_INTERRUPT_ID_0, (Xil_ExceptionHandler)isr0, (void *)&intc);

    if (result != XST_SUCCESS) {
        return result;
    }

    // enable interrupts for IRQ_F2P[0:0]
    XScuGic_Enable(intc_instance_ptr, INTC_INTERRUPT_ID_0);

    // initialize the exception table and register the interrupt controller handler with the exception table
    Xil_ExceptionInit();

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, intc_instance_ptr);

    // enable non-critical exceptions
    Xil_ExceptionEnable();

    return XST_SUCCESS;
}

void cpwm8c_init()
{


		AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
//		AXI_CPWM8C_mWrite_Period_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
//		AXI_CPWM8C_mWrite_Period_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
//		AXI_CPWM8C_mWrite_Period_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
//		AXI_CPWM8C_mWrite_Period_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
//		AXI_CPWM8C_mWrite_Period_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
//		AXI_CPWM8C_mWrite_Period_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
//		AXI_CPWM8C_mWrite_Period_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);

		AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
//		AXI_CPWM8C_mWrite_Compare_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
//		AXI_CPWM8C_mWrite_Compare_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
//		AXI_CPWM8C_mWrite_Compare_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
//		AXI_CPWM8C_mWrite_Compare_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
//		AXI_CPWM8C_mWrite_Compare_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
//		AXI_CPWM8C_mWrite_Compare_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
//		AXI_CPWM8C_mWrite_Compare_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);

		AXI_CPWM8C_mWrite_DeadTimeA_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
//		AXI_CPWM8C_mWrite_DeadTimeA_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
//		AXI_CPWM8C_mWrite_DeadTimeA_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
//		AXI_CPWM8C_mWrite_DeadTimeA_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
//		AXI_CPWM8C_mWrite_DeadTimeA_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
//		AXI_CPWM8C_mWrite_DeadTimeA_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
//		AXI_CPWM8C_mWrite_DeadTimeA_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
//		AXI_CPWM8C_mWrite_DeadTimeA_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);

		AXI_CPWM8C_mWrite_DeadTimeB_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
//		AXI_CPWM8C_mWrite_DeadTimeB_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
//		AXI_CPWM8C_mWrite_DeadTimeB_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
//		AXI_CPWM8C_mWrite_DeadTimeB_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
//		AXI_CPWM8C_mWrite_DeadTimeB_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
//		AXI_CPWM8C_mWrite_DeadTimeB_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
//		AXI_CPWM8C_mWrite_DeadTimeB_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
//		AXI_CPWM8C_mWrite_DeadTimeB_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);

		AXI_CPWM8C_mWrite_EventCount_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
//		AXI_CPWM8C_mWrite_EventCount_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
//		AXI_CPWM8C_mWrite_EventCount_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
//		AXI_CPWM8C_mWrite_EventCount_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
//		AXI_CPWM8C_mWrite_EventCount_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
//		AXI_CPWM8C_mWrite_EventCount_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
//		AXI_CPWM8C_mWrite_EventCount_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
//		AXI_CPWM8C_mWrite_EventCount_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);

		AXI_CPWM8C_mWrite_InterruptMatrix(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_intmatrix);

		AXI_CPWM8C_mWrite_CountMode_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
//		AXI_CPWM8C_mWrite_CountMode_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
//		AXI_CPWM8C_mWrite_CountMode_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
//		AXI_CPWM8C_mWrite_CountMode_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
//		AXI_CPWM8C_mWrite_CountMode_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
//		AXI_CPWM8C_mWrite_CountMode_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
//		AXI_CPWM8C_mWrite_CountMode_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
//		AXI_CPWM8C_mWrite_CountMode_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);

		AXI_CPWM8C_mWrite_MaskMode_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
//		AXI_CPWM8C_mWrite_MaskMode_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
//		AXI_CPWM8C_mWrite_MaskMode_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
//		AXI_CPWM8C_mWrite_MaskMode_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
//		AXI_CPWM8C_mWrite_MaskMode_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
//		AXI_CPWM8C_mWrite_MaskMode_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
//		AXI_CPWM8C_mWrite_MaskMode_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
//		AXI_CPWM8C_mWrite_MaskMode_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);

		AXI_CPWM8C_mWrite_DTimeOnOff_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
//		AXI_CPWM8C_mWrite_DTimeOnOff_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
//		AXI_CPWM8C_mWrite_DTimeOnOff_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
//		AXI_CPWM8C_mWrite_DTimeOnOff_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
//		AXI_CPWM8C_mWrite_DTimeOnOff_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
//		AXI_CPWM8C_mWrite_DTimeOnOff_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
//		AXI_CPWM8C_mWrite_DTimeOnOff_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
//		AXI_CPWM8C_mWrite_DTimeOnOff_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);

		AXI_CPWM8C_mWrite_LogicA_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
//		AXI_CPWM8C_mWrite_LogicA_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
//		AXI_CPWM8C_mWrite_LogicA_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
//		AXI_CPWM8C_mWrite_LogicA_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
//		AXI_CPWM8C_mWrite_LogicA_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
//		AXI_CPWM8C_mWrite_LogicA_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
//		AXI_CPWM8C_mWrite_LogicA_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
//		AXI_CPWM8C_mWrite_LogicA_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);

		AXI_CPWM8C_mWrite_LogicB_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
//		AXI_CPWM8C_mWrite_LogicB_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
//		AXI_CPWM8C_mWrite_LogicB_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
//		AXI_CPWM8C_mWrite_LogicB_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
//		AXI_CPWM8C_mWrite_LogicB_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
//		AXI_CPWM8C_mWrite_LogicB_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
//		AXI_CPWM8C_mWrite_LogicB_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
//		AXI_CPWM8C_mWrite_LogicB_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);

		AXI_CPWM8C_mWrite_CarrSel_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrSel_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrSel_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrSel_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrSel_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrSel_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrSel_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrSel_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);

		AXI_CPWM8C_mWrite_CarrOnOff_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carronoff);
//		AXI_CPWM8C_mWrite_CarrOnOff_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrOnOff_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrOnOff_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrOnOff_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrOnOff_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrOnOff_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
//		AXI_CPWM8C_mWrite_CarrOnOff_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);


//		XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR, XGPIO_DATA_OFFSET, gpio_reg0);
		AXI_CPWM8C_mWrite_PWMOnOff(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_onoff);

		AXI_CPWM8C_IntAck(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR);
}
