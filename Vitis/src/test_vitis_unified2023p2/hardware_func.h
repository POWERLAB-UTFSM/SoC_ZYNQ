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
#include "xdec3lxnpc.h"
#include "xinterrupt_wrap.h"
#include "xaxicdma.h"

#define MY_GPIO_0_BASEADDR XPAR_XGPIO_0_BASEADDR
#define MY_GPIOPS_0_BASEADDR XPAR_XGPIOPS_0_BASEADDR
#define MY_CLKWIZ_0_BASEADDR XPAR_XCLK_WIZ_0_BASEADDR
#define MY_CPWM8C_0_BASEADDR XPAR_AXI_CPWM8C_0_BASEADDR
#define MY_SCUGIC_0_BASEADDR XPAR_XSCUGIC_0_BASEADDR
#define MY_AXICDMA_0_BASEADDR XPAR_XAXICDMA_0_BASEADDR

/**
 * @brief 
 * 
 * @param InstancePtr 
 * @param InstanceCfg 
 * @param BaseAddr 
 * @return int 
 */
int XGpioPs_My_Init(XGpioPs *InstancePtr,XGpioPs_Config *InstanceCfg, UINTPTR BaseAddr);

/**
 * @brief 
 * 
 * @param InstancePtr 
 * @param pin_dir 
 */
void XGpioPs_My_PwmWireack(XGpioPs *InstancePtr,u32 pin_dir);

/**
 * @brief 
 * 
 * @param InstancePtr 
 * @param InstanceCfg 
 * @param BaseAddr 
 * @return int 
 */
int XGpio_My_Init(XGpio *InstancePtr,XGpio_Config *InstanceCfg, UINTPTR BaseAddr);

/**
 * @brief 
 * 
 * @param InstancePtr 
 * @param input 
 */
void XGpio_My_Ch1Enable(XGpio *InstancePtr, u32 input);

/**
 * @brief 
 * 
 * @param InstancePtr 
 * @param InstanceCfg 
 * @param BaseAddr 
 * @return int 
 */
int XAxiCdma_My_Init(XAxiCdma *InstancePtr,XAxiCdma_Config *InstanceCfg,UINTPTR BaseAddr);

/**
 * @brief 
 * 
 * @param InstancePtr 
 * @param InstanceCfg 
 * @param BaseAddr 
 * @return int 
 */
int XCpwm8c_My_Init(XCpwm8c *InstancePtr,XCpwm8c_Config *InstanceCfg,UINTPTR BaseAddr);

/**
 * @brief 
 * 
 * @param BaseAddress 
 */
void XCpwm8c_My_InitLow(UINTPTR BaseAddress);

/**
 * @brief 
 * 
 * @param InstancePtr 
 * @param InstanceCfg 
 * @param BaseAddr 
 * @return int 
 */
int XClk_Wiz_My_Init(XClk_Wiz *InstancePtr,XClk_Wiz_Config *InstanceCfg, UINTPTR BaseAddr);

/**
 * @brief 
 * 
 * @param IntrId 
 * @param BaseAddress 
 * @param IntInstance 
 * @param IntConfig 
 * @param IntHandler 
 * @param Priority 
 * @param Trigger 
 * @return int 
 */
int XScugic_My_InitInterrupt(u32 IntrId,UINTPTR BaseAddress,XScuGic *IntInstance,XScuGic_Config *IntConfig,Xil_ExceptionHandler IntHandler,u32 Priority,u32 Trigger);


#endif /* end of inclusion protection macro */