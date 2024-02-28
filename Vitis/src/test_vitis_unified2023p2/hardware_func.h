//#ifndef HARDWARE_FUNC /* prevent circular inclusions */
//#define HARDWARE_FUNC /* by using protection macros */

#include "xparameters.h"
#include "xcommon_drv_config.h"
#include "xplatform_info.h"
#include "xgpio.h"
#include "xgpiops.h"
#include "xstatus.h"
#include "xclk_wiz.h"
#include "xscugic.h"
#include "xcpwm8c.h"
#include "xdec3lxnpc.h"
#include "xinterrupt_wrap.h"

#define MY_GPIO_0_BASEADDR XPAR_XGPIO_0_BASEADDR
#define MY_GPIOPS_0_BASEADDR XPAR_XGPIOPS_0_BASEADDR
#define MY_CLKWIZ_0_BASEADDR XPAR_XCLK_WIZ_0_BASEADDR
#define MY_CPWM8C_0_BASEADDR XPAR_AXI_CPWM8C_0_BASEADDR


int xgpio_myinit(XGpio *InstancePtr, UINTPTR BaseAddr);

/**
 * @brief 
 * 
 * @param InstancePtr 
 * @param input 
 */
void xgpio_mych1enable(XGpio *InstancePtr, u32 input);

int xgpiops_myinit(XGpioPs *InstancePtr, XGpioPs_Config *InstanceConfigPtr, UINTPTR BaseAddr);

int xclk_wiz_myinit(XClk_Wiz *InstancePtr, XClk_Wiz_Config *InstanceConfigPtr, u64 xclk_wiz_freqinit, UINTPTR BaseAddr);

int xscugic_fiq_interrupt_myinit(XScuGic *intc_inst_ptr, XScuGic_Config *intc_config, Xil_ExceptionHandler fiq_handler, UINTPTR BaseAddr);

int xscugic_irq_interrupt_myinit(XScuGic *intc_instance_ptr, XScuGic_Config *intc_config, Xil_ExceptionHandler irq_handler, UINTPTR BaseAddr, u16 InterruptId);

void axi_cpwm8c_lspwm3l_dec3lxnpc_myinit(u16 pwm_period, UINTPTR BaseAddr);

void xgpiops_pwm_wireack(XGpioPs *InstancePtr,u32 pin_dir);


//#endif /* end of inclusion protection macro */