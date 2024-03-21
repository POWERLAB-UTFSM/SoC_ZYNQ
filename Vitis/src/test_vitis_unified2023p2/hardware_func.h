#ifndef HARDWARE_FUNC_H /* prevent circular inclusions */
#define HARDWARE_FUNC_H /* by using protection macros */

/* Library headers*/
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
#include "xil_types.h"
#include <math.h>

/* Rx Buffer memory base address */
#define MY_RX_BUFFER_OFFSET 0x00F00000

/* Hardware Memory Address Aliases (from "xparameters.h") */
#define MY_GPIO_0_BASEADDR XPAR_XGPIO_0_BASEADDR
#define MY_GPIOPS_0_BASEADDR XPAR_XGPIOPS_0_BASEADDR
#define MY_CLKWIZ_0_BASEADDR XPAR_XCLK_WIZ_0_BASEADDR
#define MY_CPWM8C_0_BASEADDR XPAR_AXI_CPWM8C_0_BASEADDR
#define MY_SCUGIC_0_BASEADDR XPAR_XSCUGIC_0_BASEADDR
#define MY_AXICDMA_0_BASEADDR XPAR_XAXICDMA_0_BASEADDR

/* Memory section definitions from linker */
extern UINTPTR __data_start;
extern UINTPTR __data_end;
extern UINTPTR __data1_start;
extern UINTPTR __data1_end;
extern UINTPTR _vector_table;
extern UINTPTR __eh_framehdr_start;
extern UINTPTR __eh_framehdr_end;

/* Global driver intances */
extern XGpio xgpio_my_inst;
extern XGpio_Config xgpio_my_config;
extern XGpioPs xgpiops_my_inst;
extern XGpioPs_Config xgpiops_my_config;
extern XClk_Wiz xclkwiz_my_inst;
extern XClk_Wiz_Config xclkwiz_my_config;
extern XScuGic xscugic_my_inst;
extern XScuGic_Config xscugic_my_config;
extern XCpwm8c xcpwm8c_my_inst;
extern XCpwm8c_Config xcpwm8c_my_config;
extern XAxiCdma xaxicdma_my_inst;
extern XAxiCdma_Config xaxicdma_my_config;

// /* Buffer variables */
// extern volatile uint8_t* ___tx_buffer;
// extern volatile uint8_t* ___rx_buffer;

// extern UINTPTR* ___txBufferAddr;
// extern UINTPTR* ___rxBufferAddr;
// extern u32 ___buff_size;
// extern u32 ___i_cnt;
// extern u32 ___k_samp;

/* Function declarations */

int _HW_My_Init(void);

// void _Buffer_My_Init(void);

// u32 _Buffer_My_SimpleTransfer(void);

// u32 _Buffer_My_Reset(void);

void _My_XCpwm8c_IntAckGpioPs(void);

int XScuGic_My_Init(XScuGic *InstancePtr,XScuGic_Config *InstanceCfg,UINTPTR BaseAddr);

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
int XScugic_My_InitInterrupt(u32 IntrId,XScuGic *IntInstance,Xil_ExceptionHandler IntHandler,u32 Priority,u32 Trigger);


#endif /* end of inclusion protection macro */