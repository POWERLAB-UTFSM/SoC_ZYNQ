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
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"
#include "sleep.h"
#include "xgpio.h"
#include "axi_cpwm8c.h"
//#include "AXI_CPWM.h"

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
u8 pwm_dtimeB=0;
u8 pwm_carrclkdiv=0;
u8 pwm_dtclkdiv=0;
AXI_CPWM8C_count_mode pwm_countmode=COUNT_UP_DOWN;
AXI_CPWM8C_mask_mode pwm_maskmode=MINMAX_MASK;
AXI_CPWM8C_onoff pwm_dtonoff=REG_ON;
AXI_CPWM8C_logic pwm_logicA=LOGIC_NEG;
AXI_CPWM8C_logic pwm_logicB=LOGIC_NEG;
AXI_CPWM8C_carrsel pwm_carrsel=CARR_MASTER1;
AXI_CPWM8C_onoff pwm_onoff=REG_ON;
u8 pwm_clksel=1;

//u8 pwm_logicA=0;
//u8 pwm_logicB=0;
u8 pwm_intmatrix=255;

int main()
{
//    init_platform();

//    print("Hello World\n\r");

//    pwm_reg0 = 2000 << 16 | 0;
//    pwm_reg1 = 1000 << 16 | 1000;
//    pwm_reg2 = 1000 << 16 | 1000;
//    pwm_reg3 = 0 << 24 | 0 << 16 | 0 << 11 | 0 << 6 | 0 << 3;
//    pwm_reg4 = 0 << 9 | 0 << 8 | 0 << 7 | 0 << 6 | 1 << 5 | 1 << 4 | 1 << 2 | 1 ;
//    pwm_period = 2000;
//    pwm_init = 2000;
//    pwm_comp1 = 1000;
//	pwm_comp2 = 1000;
//	pwm_comp3 = 1000;
//	pwm_comp4 = 1000;
//	pwm_dtimeA = 0;
//	pwm_dtimeB = 0;
//	pwm_eventcount=0;

	while (1) {


		AXI_CPWM8C_mWrite_PWMOnOff(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_onoff);

		AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
		/*AXI_CPWM8C_mWrite_Period_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
		AXI_CPWM8C_mWrite_Period_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
		AXI_CPWM8C_mWrite_Period_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
		AXI_CPWM8C_mWrite_Period_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
		AXI_CPWM8C_mWrite_Period_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
		AXI_CPWM8C_mWrite_Period_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
		AXI_CPWM8C_mWrite_Period_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);*/

		AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
		/*AXI_CPWM8C_mWrite_Compare_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
		AXI_CPWM8C_mWrite_Compare_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
		AXI_CPWM8C_mWrite_Compare_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
		AXI_CPWM8C_mWrite_Compare_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
		AXI_CPWM8C_mWrite_Compare_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
		AXI_CPWM8C_mWrite_Compare_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
		AXI_CPWM8C_mWrite_Compare_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);*/

		AXI_CPWM8C_mWrite_DeadTimeA_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
		/*AXI_CPWM8C_mWrite_DeadTimeA_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
		AXI_CPWM8C_mWrite_DeadTimeA_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
		AXI_CPWM8C_mWrite_DeadTimeA_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
		AXI_CPWM8C_mWrite_DeadTimeA_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
		AXI_CPWM8C_mWrite_DeadTimeA_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
		AXI_CPWM8C_mWrite_DeadTimeA_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
		AXI_CPWM8C_mWrite_DeadTimeA_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);*/

		AXI_CPWM8C_mWrite_DeadTimeB_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
		/*AXI_CPWM8C_mWrite_DeadTimeB_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
		AXI_CPWM8C_mWrite_DeadTimeB_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
		AXI_CPWM8C_mWrite_DeadTimeB_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
		AXI_CPWM8C_mWrite_DeadTimeB_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
		AXI_CPWM8C_mWrite_DeadTimeB_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
		AXI_CPWM8C_mWrite_DeadTimeB_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
		AXI_CPWM8C_mWrite_DeadTimeB_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);*/

		AXI_CPWM8C_mWrite_EventCount_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
		/*AXI_CPWM8C_mWrite_EventCount_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
		AXI_CPWM8C_mWrite_EventCount_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
		AXI_CPWM8C_mWrite_EventCount_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
		AXI_CPWM8C_mWrite_EventCount_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
		AXI_CPWM8C_mWrite_EventCount_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
		AXI_CPWM8C_mWrite_EventCount_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
		AXI_CPWM8C_mWrite_EventCount_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);*/

		AXI_CPWM8C_mWrite_InterruptMatrix(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_intmatrix);

		AXI_CPWM8C_mWrite_CountMode_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
		/*AXI_CPWM8C_mWrite_CountMode_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
		AXI_CPWM8C_mWrite_CountMode_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
		AXI_CPWM8C_mWrite_CountMode_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
		AXI_CPWM8C_mWrite_CountMode_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
		AXI_CPWM8C_mWrite_CountMode_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
		AXI_CPWM8C_mWrite_CountMode_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
		AXI_CPWM8C_mWrite_CountMode_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);*/

		AXI_CPWM8C_mWrite_MaskMode_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
		/*AXI_CPWM8C_mWrite_MaskMode_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
		AXI_CPWM8C_mWrite_MaskMode_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
		AXI_CPWM8C_mWrite_MaskMode_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
		AXI_CPWM8C_mWrite_MaskMode_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
		AXI_CPWM8C_mWrite_MaskMode_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
		AXI_CPWM8C_mWrite_MaskMode_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
		AXI_CPWM8C_mWrite_MaskMode_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);*/

		AXI_CPWM8C_mWrite_DTimeOnOff_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
		/*AXI_CPWM8C_mWrite_DTimeOnOff_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
		AXI_CPWM8C_mWrite_DTimeOnOff_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
		AXI_CPWM8C_mWrite_DTimeOnOff_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
		AXI_CPWM8C_mWrite_DTimeOnOff_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
		AXI_CPWM8C_mWrite_DTimeOnOff_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
		AXI_CPWM8C_mWrite_DTimeOnOff_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
		AXI_CPWM8C_mWrite_DTimeOnOff_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);*/

		AXI_CPWM8C_mWrite_LogicA_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
		/*AXI_CPWM8C_mWrite_LogicA_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
		AXI_CPWM8C_mWrite_LogicA_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
		AXI_CPWM8C_mWrite_LogicA_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
		AXI_CPWM8C_mWrite_LogicA_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
		AXI_CPWM8C_mWrite_LogicA_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
		AXI_CPWM8C_mWrite_LogicA_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);
		AXI_CPWM8C_mWrite_LogicA_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA);*/

		AXI_CPWM8C_mWrite_LogicB_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
		/*AXI_CPWM8C_mWrite_LogicB_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
		AXI_CPWM8C_mWrite_LogicB_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
		AXI_CPWM8C_mWrite_LogicB_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
		AXI_CPWM8C_mWrite_LogicB_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
		AXI_CPWM8C_mWrite_LogicB_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
		AXI_CPWM8C_mWrite_LogicB_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);
		AXI_CPWM8C_mWrite_LogicB_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB);*/

		AXI_CPWM8C_mWrite_CarrSel_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
		/*AXI_CPWM8C_mWrite_CarrSel_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
		AXI_CPWM8C_mWrite_CarrSel_3(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
		AXI_CPWM8C_mWrite_CarrSel_4(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
		AXI_CPWM8C_mWrite_CarrSel_5(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
		AXI_CPWM8C_mWrite_CarrSel_6(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
		AXI_CPWM8C_mWrite_CarrSel_7(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
		AXI_CPWM8C_mWrite_CarrSel_8(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);*/

		AXI_CPWM8C_mWrite_ClkSel(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_clksel);

		XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR, XGPIO_DATA_OFFSET, gpio_reg0);
		/*
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG0_OFFSET, pwm_reg0);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG1_OFFSET, pwm_reg1);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG2_OFFSET, pwm_reg2);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG3_OFFSET, pwm_reg3);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG4_OFFSET, pwm_reg4);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG5_OFFSET, pwm_reg5);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG6_OFFSET, pwm_reg6);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG7_OFFSET, pwm_reg7);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET, pwm_reg8);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG9_OFFSET, pwm_reg9);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG10_OFFSET, pwm_reg10);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG11_OFFSET, pwm_reg11);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET, pwm_reg12);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET, pwm_reg13);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET, pwm_reg14);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET, pwm_reg15);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET, pwm_reg16);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET, pwm_reg17);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET, pwm_reg18);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET, pwm_reg19);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG20_OFFSET, pwm_reg20);
		AXI_CPWM8C_mWriteReg(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR, AXI_CPWM8C_S_AXI_SLV_REG21_OFFSET, pwm_reg21);
		*/


/*
		AXI_CPWM_mWrite_Period(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_period);
		AXI_CPWM_mWrite_InitCarrier(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_init);
		AXI_CPWM_mWrite_Comp1(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_comp1);
		AXI_CPWM_mWrite_Comp2(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_comp2);
		AXI_CPWM_mWrite_Comp3(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_comp3);
		AXI_CPWM_mWrite_Comp4(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_comp4);
		AXI_CPWM_mWrite_DeadTimeA(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_dtimeA);
		AXI_CPWM_mWrite_DeadTimeB(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_dtimeB);
		AXI_CPWM_mWrite_EventCount(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_eventcount);
		AXI_CPWM_mWrite_CarrClkDiv(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_carrclkdiv);
		AXI_CPWM_mWrite_DtimeClkDiv(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_dtclkdiv);
		AXI_CPWM_mWrite_CountMode(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_countmode);
		AXI_CPWM_mWrite_MaskMode(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_maskmode);
		AXI_CPWM_mWrite_PWMOnOff(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_pwmonoff);
		AXI_CPWM_mWrite_IntOnOff(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_intonoff);
		AXI_CPWM_mWrite_PWMClkDivOnOff(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_pwmclkdivonoff);
		AXI_CPWM_mWrite_DTClkDivOnOff(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_dtclkdivonoff);
		AXI_CPWM_mWrite_LogicOutA(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_logicA);
		AXI_CPWM_mWrite_LogicOutB(XPAR_AXI_CPWM_0_S_AXI_BASEADDR,pwm_logicB);
*/
		//AXI_CPWM_mWriteReg(XPAR_AXI_CPWM_0_S_AXI_BASEADDR, AXI_CPWM_S_AXI_SLV_REG0_OFFSET, pwm_reg0);
		//AXI_CPWM_mWriteReg(XPAR_AXI_CPWM_0_S_AXI_BASEADDR, AXI_CPWM_S_AXI_SLV_REG1_OFFSET, pwm_reg1);
		//AXI_CPWM_mWriteReg(XPAR_AXI_CPWM_0_S_AXI_BASEADDR, AXI_CPWM_S_AXI_SLV_REG2_OFFSET, pwm_reg2);
		//AXI_CPWM_mWriteReg(XPAR_AXI_CPWM_0_S_AXI_BASEADDR, AXI_CPWM_S_AXI_SLV_REG3_OFFSET, pwm_reg3);
		//AXI_CPWM_mWriteReg(XPAR_AXI_CPWM_0_S_AXI_BASEADDR, AXI_CPWM_S_AXI_SLV_REG4_OFFSET, pwm_reg4);

	}

//    cleanup_platform();
    return 0;
}
