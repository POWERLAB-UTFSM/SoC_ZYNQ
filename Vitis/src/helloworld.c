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

#include <math.h>
#include <stdio.h>
//#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"
#include "sleep.h"
#include "xgpio.h"
#include "axi_cpwm8c.h"
#include "axi_dec3lxnpc.h"
#include "xgpiops.h"
//#include "axi4fulltest.h"
#include "xclk_wiz.h"
#include "xscugic.h"
#include "xil_types.h"
//#include "xil_mmu.h"
#include "xdmaps.h"

u16 globalpwm_period=2000;
u16 globalpwm_compare1=0;
u16 globalpwm_compare2=0;
u16 globalpwm_compare1_off=0;
u16 globalpwm_compare2_off=0;


float time_sin=0;
float theta_sin=0;
float pwm_time=0;
float osc_sin=0;
float ref_sinpos=0;
float ref_sinneg=0;
float m_A=0;
float f_1=50;

#define M_2PI 6.283185307179586476925286

u8 globaldec3lxnpc_tshort=1;
u8 globaldec3lxnpc_toffon=40;
u8 globaldec3lxnpc_toffV0on=50;
u8 globaldec3lxnpc_tonoffV0=35;
u8 globaldec3lxnpc_toffonI0=45;

u32 globalxgpio_pinenable=0;

AXI_DEC3LXNPC_convtype globaldec3lxnpc_convtype=ANPC;
AXI_DEC3LXNPC_commtype globaldec3lxnpc_commtype=type_I;

u64 pwmclkfreq=50;
u8 pwm_intmatrix=255;

#define INTC_INTERRUPT_ID_0 XPAR_FABRIC_AXI_CPWM8C_0_VEC_ID
// instance of interrupt controller
static XScuGic intc;

//Function declaration
int setup_interrupt_system(u16 DeviceId, u16 InterruptId);
void isr0 (void *intc_inst_ptr);
void fiq_handler (void *intc_inst_ptr);
void cpwm8c_init();
int setup_FIQ_interrupt_system(u16 DeviceId);
static inline void pwm_wireack(XGpioPs *InstancePtr,u32 pin_dir);

XGpioPs_Config *xgpiopsptr;
XGpioPs xgpiops;
XGpio_Config *xgpioptr;
XGpio xgpio;

#define XCLK_US_WIZ_RECONFIG_OFFSET	0x0000025C

XClk_Wiz_Config *xclkwizptr;
XClk_Wiz xclkwiz;

int status = XST_SUCCESS;
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


	/*initialize PS XGPIO*/
	xgpiopsptr= XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
	status=XGpioPs_CfgInitialize(&xgpiops,xgpiopsptr,xgpiopsptr->BaseAddr);
	XGpioPs_SetDirection(&xgpiops,2,1);
	XGpioPs_SetOutputEnable(&xgpiops,2,1);

	/*initialize AXI XGPIO*/
	xgpioptr=XGpio_LookupConfig(XPAR_AXI_GPIO_0_DEVICE_ID);
	status=XGpio_CfgInitialize(&xgpio,xgpioptr,xgpioptr->BaseAddress);
	XGpio_SetDataDirection(&xgpio,1,0b11);
	/*XGpio_SetDataDirection(&xgpio,2,0);*/
	XGpio_DiscreteWrite(&xgpio,1,0);
	/*XGpio_DiscreteWrite(&xgpio,2,0);*/

	/*initialize XCLK_WIZ*/
	xclkwizptr=XClk_Wiz_LookupConfig(XPAR_CLK_WIZ_0_DEVICE_ID);
	status=XClk_Wiz_CfgInitialize(&xclkwiz, xclkwizptr,xclkwizptr->BaseAddr);
	XClk_Wiz_WriteReg(xclkwizptr->BaseAddr, XCLK_WIZ_REG25_OFFSET, 0);
	//status=XClk_Wiz_WaitForLock(&xclkwiz);
	status=XClk_Wiz_SetRate(&xclkwiz,pwmclkfreq);
	XClk_Wiz_WriteReg(xclkwizptr->BaseAddr, XCLK_US_WIZ_RECONFIG_OFFSET,(XCLK_WIZ_RECONFIG_LOAD | XCLK_WIZ_RECONFIG_SADDR));
	status=XClk_Wiz_WaitForLock(&xclkwiz);

	cpwm8c_init();

	/*Initialize interrupt*/
	//status = setup_interrupt_system(XPAR_PS7_SCUGIC_0_DEVICE_ID,INTC_INTERRUPT_ID_0);
	status = setup_FIQ_interrupt_system(XPAR_PS7_SCUGIC_0_DEVICE_ID); //initialize fast interrupt (FIQ) on channel "XPAR_PS7_SCUGIC_0_DEVICE_ID"

	/*status check*/
	if (status != XST_SUCCESS){
		return XST_FAILURE;
	}

	//xil_printf("holi :D");
	while (1){
		//AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_compare1);
		//AXI_CPWM8C_mWrite_Compare_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_compare2);
		AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_period);

		AXI_DEC3LXNPC_mWrite_tshort(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_tshort);
		AXI_DEC3LXNPC_mWrite_toffon(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_toffon);
		AXI_DEC3LXNPC_mWrite_toffV0on(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_toffV0on);
		AXI_DEC3LXNPC_mWrite_tonoffV0(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_tonoffV0);
		AXI_DEC3LXNPC_mWrite_toffonI0(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_toffonI0);

		AXI_DEC3LXNPC_mWrite_convtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, globaldec3lxnpc_convtype );
		AXI_DEC3LXNPC_mWrite_commtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, globaldec3lxnpc_commtype );

		XGpio_DiscreteWrite(&xgpio,1,globalxgpio_pinenable);

		status=XClk_Wiz_SetRate(&xclkwiz,pwmclkfreq);
		XClk_Wiz_WriteReg(xclkwizptr->BaseAddr, XCLK_US_WIZ_RECONFIG_OFFSET,(XCLK_WIZ_RECONFIG_LOAD | XCLK_WIZ_RECONFIG_SADDR));
		status=XClk_Wiz_WaitForLock(&xclkwiz);
		//XGpio_DiscreteWrite(&xgpio,2,globalxgpio_pinenable);
	}

//    cleanup_platform();
    return 0;
}

static inline void pwm_wireack(XGpioPs *InstancePtr,u32 pin_dir){
	XGpioPs_WritePin(InstancePtr, pin_dir, 1);
	XGpioPs_WritePin(InstancePtr, pin_dir, 0);
}

void isr0 (void *intc_inst_ptr) {
	//u32 IntIDFull;

	AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_compare1);
	AXI_CPWM8C_mWrite_Compare_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_compare2);
	AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_period);
	AXI_CPWM8C_mWrite_Period_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_period);
	//AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_period);
	//AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_compare1);
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
	XGpioPs_WritePin(&xgpiops, 54, 1);
	XGpioPs_WritePin(&xgpiops, 54, 0);

}

void fiq_handler (void *intc_inst_ptr) {
	//u32 IntIDFull;

	// PWM_period [s] = PWM_count*(1/PWM_clock [MHz] )*2   ----triangular wave

	pwm_time=2*(float)(globalpwm_period)/((float)(pwmclkfreq)*1E6);

	theta_sin=2*M_PI*f_1*time_sin;

	if(theta_sin>M_2PI){
		theta_sin=theta_sin-M_2PI;
	}

	osc_sin=m_A*sinf(theta_sin);
	ref_sinpos=(float)(globalpwm_period)*(osc_sin);
	ref_sinneg=(float)(globalpwm_period)*(osc_sin+1);

	AXI_CPWM8C_mWrite_Compare_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,ref_sinpos);
	AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,ref_sinneg);

	//t[k+1]=t[k]+PWM_period
	time_sin=time_sin+pwm_time;

	//AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_compare1);
	//AXI_CPWM8C_mWrite_Compare_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_compare2);
	//AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_period);
	//AXI_CPWM8C_mWrite_Period_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_period);
	//XClk_Wiz_SetRateHz(&xclkwiz,pwmclkfreq);
	//AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_compare1);
	//AXI_CPWM8C_mWrite_Compare_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_compare2);
	//AXI_DEC3LXNPC_mWrite_convtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, globaldec3lxnpc_convtype );
	//AXI_DEC3LXNPC_mWrite_commtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, globaldec3lxnpc_commtype );
	//AXI_DEC3LXNPC_mWrite_tshort(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_tshort);
	//AXI_DEC3LXNPC_mWrite_toffon(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_toffon);
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
	pwm_wireack(&xgpiops,54);
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
	u16 pwm_comp1=0;
	u8 pwm_eventcount=0;
	u8 pwm_dtimeA=0;
	u8 pwm_dtimeB=0;
	AXI_CPWM8C_count_mode pwm_countmode=COUNT_UP_DOWN;
	AXI_CPWM8C_mask_mode pwm_maskmode=MIN_MASK;
	AXI_CPWM8C_onoff pwm_dtonoff=REG_OFF;
	AXI_CPWM8C_logic pwm_logicA1=LOGIC_NEG;
	AXI_CPWM8C_logic pwm_logicB1=LOGIC_NEG;
	AXI_CPWM8C_logic pwm_logicA2=LOGIC_POS;
	AXI_CPWM8C_logic pwm_logicB2=LOGIC_POS;
	AXI_CPWM8C_carrsel pwm_carrsel=CARR_MASTER1;
	AXI_CPWM8C_onoff pwm_onoff=REG_ON;
	AXI_CPWM8C_onoff pwm_carronoff=REG_ON;

	AXI_DEC3LXNPC_convtype dec3lxnpc_convtype=ANPC;
	AXI_DEC3LXNPC_commtype dec3lxnpc_commtype=type_I;

	AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
	AXI_CPWM8C_mWrite_Period_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
	AXI_CPWM8C_mWrite_InitCarrier_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_init);
	AXI_CPWM8C_mWrite_InitCarrier_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_init);
	AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
	AXI_CPWM8C_mWrite_Compare_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
	AXI_CPWM8C_mWrite_DeadTimeA_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
	AXI_CPWM8C_mWrite_DeadTimeB_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
	AXI_CPWM8C_mWrite_DeadTimeA_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
	AXI_CPWM8C_mWrite_DeadTimeB_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
	AXI_CPWM8C_mWrite_EventCount_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
	AXI_CPWM8C_mWrite_EventCount_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
	AXI_CPWM8C_mWrite_InterruptMatrix(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_intmatrix);
	AXI_CPWM8C_mWrite_CountMode_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
	AXI_CPWM8C_mWrite_CountMode_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
	AXI_CPWM8C_mWrite_MaskMode_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
	AXI_CPWM8C_mWrite_MaskMode_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
	AXI_CPWM8C_mWrite_DTimeOnOff_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
	AXI_CPWM8C_mWrite_DTimeOnOff_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
	AXI_CPWM8C_mWrite_LogicA_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA1);
	AXI_CPWM8C_mWrite_LogicB_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB1);
	AXI_CPWM8C_mWrite_LogicA_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA2);
	AXI_CPWM8C_mWrite_LogicB_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB2);
	AXI_CPWM8C_mWrite_CarrSel_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
	AXI_CPWM8C_mWrite_CarrSel_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
	AXI_CPWM8C_mWrite_CarrOnOff_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carronoff);
	AXI_CPWM8C_mWrite_CarrOnOff_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carronoff);
	AXI_CPWM8C_mWrite_PWMOnOff(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_onoff);
	AXI_CPWM8C_IntAck(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR);

	AXI_DEC3LXNPC_mWrite_tshort(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,10);
	AXI_DEC3LXNPC_mWrite_toffon(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,20);
	AXI_DEC3LXNPC_mWrite_toffV0on(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,30);
	AXI_DEC3LXNPC_mWrite_tonoffV0(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,25);
	AXI_DEC3LXNPC_mWrite_toffonI0(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,15);

	AXI_DEC3LXNPC_mWrite_convtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, dec3lxnpc_convtype );
	AXI_DEC3LXNPC_mWrite_commtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, dec3lxnpc_commtype );
}
