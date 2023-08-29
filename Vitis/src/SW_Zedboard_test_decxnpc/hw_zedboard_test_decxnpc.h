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

#define XCLK_US_WIZ_RECONFIG_OFFSET	0x0000025C



/*
---------------------------------------------------------------------------------
Function definition
---------------------------------------------------------------------------------
*/

static inline void xgpiops_pwm_wireack(XGpioPs *InstancePtr,u32 pin_dir){
	XGpioPs_WritePin(InstancePtr, pin_dir, 1);
	XGpioPs_WritePin(InstancePtr, pin_dir, 0);
}

int xgpiops_myinit(XGpioPs *InstancePtr, XGpioPs_Config *InstanceConfigPtr, u16 DeviceId);
int xgpio_myinit(XGpio *InstancePtr, XGpio_Config *InstanceConfigPtr, u16 DeviceId);
int xclk_wiz_myinit(XClk_Wiz *InstancePtr, XClk_Wiz_Config *InstanceConfigPtr,u64 xclk_wiz_freqinit, u16 DeviceId);
int xscugic_fiq_interrupt_myinit(XScuGic *intc_instance_ptr,XScuGic_Config *intc_config,Xil_ExceptionHandler fiq_handler,u16 DeviceId);

void axi_cpwm8c_lspwm3l_dec3lxnpc_myinit(u16 pwm_period);
void axi_dec3lxnpc_myinit(AXI_DEC3LXNPC_convtype dec3lxnpc_convtype,AXI_DEC3LXNPC_commtype dec3lxnpc_commtype,u8 axi_dec3lxnpc_tshort,u8 axi_dec3lxnpc_toffon,u8 axi_dec3lxnpc_toffV0on,u8 axi_dec3lxnpc_tonoffV0,u8 axi_dec3lxnpc_toffonI0);
