#ifndef HARDWARE_FUNC_H /* prevent circular inclusions */
#define HARDWARE_FUNC_H /* by using protection macros */

#include "xparameters.h"
#include "xcommon_drv_config.h"
#include "xplatform_info.h"
#include "xgpio.h"
#include "xgpiops.h"
#include "xstatus.h"
#include "xclk_wiz.h"
#include "xscugic.h"
#include "xcpwm8c.h"
//#include "xdec3lxnpc.h"
#include "xinterrupt_wrap.h"

#define MY_GPIO_0_BASEADDR XPAR_XGPIO_0_BASEADDR
#define MY_GPIOPS_0_BASEADDR XPAR_XGPIOPS_0_BASEADDR
#define MY_CLKWIZ_0_BASEADDR XPAR_XCLK_WIZ_0_BASEADDR
#define MY_CPWM8C_0_BASEADDR XPAR_AXI_CPWM8C_0_BASEADDR

void XGpiops_My_PwmWireack(XGpioPs *InstancePtr,u32 pin_dir);

int XGpio_My_Init(XGpio *InstancePtr,XGpio_Config *InstanceCfg, UINTPTR BaseAddr);

void XGpio_My_Ch1enable(XGpio *InstancePtr, u32 input);

int XCpwm8c_My_Init(XCpwm8c *InstancePtr,XCpwm8c_Config *InstanceCfg,UINTPTR BaseAddr);

void XCpwm8c_My_initlow(UINTPTR BaseAddress);

int XScugic_My_InitInterrupt(u32 IntrId,UINTPTR BaseAddress,XScuGic *IntInstance,XScuGic_Config *IntConfig,Xil_ExceptionHandler IntHandler,u32 Priority,u32 Trigger);

//int my_XSetupInterruptSystem(void *DriverInstance, void *IntrHandler, u32 IntrId,  UINTPTR IntcParent, u16 Priority);

/*
int XGpio_myinit(XGpio *InstancePtr, XGpio_Config *InstanceConfigPtr, UINTPTR BaseAddr);

int XGpiops_myinit(XGpioPs *InstancePtr, XGpioPs_Config *InstanceConfigPtr, UINTPTR BaseAddr);

int XClk_wiz_myinit(XClk_Wiz *InstancePtr, XClk_Wiz_Config *InstanceConfigPtr, u64 xclk_wiz_freqinit, UINTPTR BaseAddr);

int XScugic_fiq_interrupt_myinit(XScuGic *intc_inst_ptr, XScuGic_Config *intc_config, Xil_ExceptionHandler fiq_handler, UINTPTR BaseAddr);

int XScugic_irq_interrupt_myinit(XScuGic *intc_instance_ptr, XScuGic_Config *intc_config, Xil_ExceptionHandler irq_handler, UINTPTR BaseAddr, u16 InterruptId);

void XCpwm8c_lspwm3l_dec3lxnpc_myinit(u16 pwm_period, UINTPTR BaseAddr);

void XGpiops_pwm_wireack(XGpioPs *InstancePtr,u32 pin_dir);
*/

#endif /* end of inclusion protection macro */