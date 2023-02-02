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
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"
#include "sleep.h"
#include "xgpio.h"
#include "AXI_CPWM.h"

u32 gpio_reg0=0;
u32 pwm_reg0=0;
u32 pwm_reg1=0;
u32 pwm_reg2=0;
u32 pwm_reg3=0;
u32 pwm_reg4=0;

int main()
{
    init_platform();

    print("Hello World\n\r");

    pwm_reg0 = 2000 << 16 | 0;
    pwm_reg1 = 1000 << 16 | 1000;
    pwm_reg2 = 1000 << 16 | 1000;
    pwm_reg3 = 0 << 24 | 0 << 16 | 0 << 11 | 0 << 6 | 0 << 3;
    pwm_reg4 = 0 << 7 | 0 << 6 | 1 << 5 | 1 << 4 | 1 << 2 | 1 ;

	while (1) {
		XGpio_WriteReg(XPAR_AXI_GPIO_0_BASEADDR, XGPIO_DATA_OFFSET, gpio_reg0);
		AXI_CPWM_mWriteReg(XPAR_AXI_CPWM_0_S_AXI_BASEADDR, AXI_CPWM_S_AXI_SLV_REG0_OFFSET, pwm_reg0);
		AXI_CPWM_mWriteReg(XPAR_AXI_CPWM_0_S_AXI_BASEADDR, AXI_CPWM_S_AXI_SLV_REG1_OFFSET, pwm_reg1);
		AXI_CPWM_mWriteReg(XPAR_AXI_CPWM_0_S_AXI_BASEADDR, AXI_CPWM_S_AXI_SLV_REG2_OFFSET, pwm_reg2);
		AXI_CPWM_mWriteReg(XPAR_AXI_CPWM_0_S_AXI_BASEADDR, AXI_CPWM_S_AXI_SLV_REG3_OFFSET, pwm_reg3);
		AXI_CPWM_mWriteReg(XPAR_AXI_CPWM_0_S_AXI_BASEADDR, AXI_CPWM_S_AXI_SLV_REG4_OFFSET, pwm_reg4);
	}

    cleanup_platform();
    return 0;
}