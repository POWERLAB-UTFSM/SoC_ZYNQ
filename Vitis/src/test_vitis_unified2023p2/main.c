#include "hardware_func.h"
#include <xil_types.h>

#define XBUFFER_SIZE 8
#define BUFFER_BYTESIZE 1200

static volatile uint8_t* tx_buffer = (uint8_t*) 0x0010A768;
static volatile uint8_t* rx_buffer = (uint8_t*) 0x00F00000;

UINTPTR* txBufferAddr;
UINTPTR* rxBufferAddr;
//uint8_t tx_buffer[XBUFFER_SIZE];
//uint8_t rx_buffer[XBUFFER_SIZE];

//static volatile double gv_sinans[1]={3.141592};
//static volatile double gv_sinarg[1]={3.141592};
static volatile double gv_xbuffer[XBUFFER_SIZE] __attribute__((section (".data1"))) = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0};
//static volatile double gv_xarg[1]={3.141592};

//static volatile u8 SourBuffer[BUFFER_BYTESIZE] __attribute__ ((aligned (64)));
//static volatile u8 DestBuffer[BUFFER_BYTESIZE] __attribute__ ((aligned (64)));

/* Global driver intances*/
XGpio xgpio_my_inst;
XGpio_Config xgpio_my_config;

XGpioPs xgpiops_my_inst;
XGpioPs_Config xgpiops_my_config;

XClk_Wiz xclkwiz_my_inst;
XClk_Wiz_Config xclkwiz_my_config;

XScuGic xscugic_my_inst;
XScuGic_Config xscugic_my_config;

XCpwm8c xcpwm8c_my_inst;
XCpwm8c_Config xcpwm8c_my_config;

XAxiCdma xaxicdma_my_inst;
XAxiCdma_Config xaxicdma_my_config;


/* Global variables */
u16 my_comp1=1000;
u16 my_comp2=1000;
u16 my_cmax=2000;
u8 my_eventcount=0;
/*
XCpwm8c_onoff my_pwmonoff=REG_ON;
XCpwm8c_countmode my_countmode=COUNT_UP_DOWN;
XCpwm8c_maskmode my_maskmode=MIN_MASK;

UINTPTR data_addrstart;
UINTPTR data_addrend;
UINTPTR data_length;
UINTPTR data_addrout;
UINTPTR data_addrin;
*/
u64 i_cnt=0;
u32 status_int=XST_FAILURE;
u64 buff_size;

/* Interrupt handler declaration*/
void _My_IRQHandler();

/*------------------------------------------------------------------------------------------*/
/*  main  */
/*------------------------------------------------------------------------------------------*/
int \
main(){

   
	u32 status= XST_SUCCESS;

  tx_buffer = (uint8_t*) &__data1_start;
  buff_size = (u64)(&__data1_end)-(u64)(&__data1_start);
/*
  data_addrstart = &__data_start;
  data_addrend = &__data_end;
  data_length = 32;
  data_addrin = SourBuffer;
  data_addrout = DestBuffer;*/

  for(u32 i=0;i<buff_size;i++)
  {
    //tx_buffer[i]=i;    
    rx_buffer[i]=0x00;
  }

  txBufferAddr = (UINTPTR*)&tx_buffer[0];
  rxBufferAddr = (UINTPTR*)&rx_buffer[0];

	status = XGpio_My_Init(\
		&xgpio_my_inst,\
		&xgpio_my_config,\
		MY_GPIO_0_BASEADDR\
		);

	status = XAxiCdma_My_Init(\
		&xaxicdma_my_inst,\
		&xaxicdma_my_config,\
		MY_AXICDMA_0_BASEADDR\
		);

  // xaxicdma_my_config  = *XAxiCdma_LookupConfig(MY_AXICDMA_0_BASEADDR);
	// status = XAxiCdma_CfgInitialize(&xaxicdma_my_inst,&xaxicdma_my_config,xaxicdma_my_config.BaseAddress);
  // if (status != XST_SUCCESS) {
	// 	return XST_FAILURE;
	// }
  XAxiCdma_IntrDisable(&xaxicdma_my_inst, XAXICDMA_XR_IRQ_ALL_MASK);
/*
  Xil_DCacheFlushRange( (UINTPTR)txBufferAddr,XBUFFER_SIZE);
  Xil_DCacheFlushRange( (UINTPTR)rxBufferAddr,XBUFFER_SIZE);

  status_int = XAxiCdma_SimpleTransfer(&xaxicdma_my_inst, (UINTPTR) txBufferAddr, (UINTPTR) rxBufferAddr,XBUFFER_SIZE, NULL, NULL);
   
  usleep(10);
  XAxiCdma_Reset(&xaxicdma_my_inst);  
  usleep(10); 
  Xil_DCacheInvalidateRange( (UINTPTR)txBufferAddr,XBUFFER_SIZE);*/

	status = XClk_Wiz_My_Init(\
		&xclkwiz_my_inst,\
		&xclkwiz_my_config,\
		MY_CLKWIZ_0_BASEADDR\
		);

	status = XGpioPs_My_Init(\
		&xgpiops_my_inst,\
		&xgpiops_my_config,\
		MY_GPIOPS_0_BASEADDR\
		);

	status = XCpwm8c_My_Init(\
		&xcpwm8c_my_inst,\
		&xcpwm8c_my_config,\
		MY_CPWM8C_0_BASEADDR\
		);

	status = XScugic_My_InitInterrupt(\
		xcpwm8c_my_config.IntrId,\
		MY_SCUGIC_0_BASEADDR,\
		&xscugic_my_inst,
		&xscugic_my_config,\
		&_My_IRQHandler,\
		XINTERRUPT_DEFAULT_PRIORITY,\
		XINTR_IS_EDGE_TRIGGERED\
		);

  /*for(u32 i=0;i<XBUFFER_SIZE;i++)
  {
    gv_xbuffer[i]=(double)(i*i);
  }*/

	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Xil_SetTlbAttributes(MY_CPWM8C_0_BASEADDR,0xC02);
	// mtcp(XREG_CP15_INVAL_UTLB_UNLOCKED, 0);
	// dsb();
   
	while(1){

	}

	return status;
}

/*------------------------------------------------------------------------------------------*/
/*  Interrupt  */
/* _My_IRQHandler() */
/*------------------------------------------------------------------------------------------*/
void \
_My_IRQHandler(){
  /*
	switch(i_cnt){
		case 0:
			XCpwm8c_WriteCompare(&xcpwm8c_my_inst, 0, my_comp1);
			break;
		case 1:
			XCpwm8c_WriteCompare(&xcpwm8c_my_inst, 1, my_comp2);
			break;
		case 2:
			XCpwm8c_WriteCountMax(&xcpwm8c_my_inst, 0, my_cmax);
			break;
	}*/
/*
  status_int=XAxiCdma_SimpleTransfer(&xaxicdma_my_inst, 0x0010a720,0x00110880, data_length, NULL, NULL);
  usleep(4);
  XAxiCdma_Reset(&xaxicdma_my_inst);*/
	
  gv_xbuffer[0]=10.0*(double)i_cnt;
  Xil_DCacheFlushRange( (UINTPTR)txBufferAddr,(u32)buff_size);
  Xil_DCacheFlushRange( (UINTPTR)((u64)rxBufferAddr+(buff_size*i_cnt)),(u32)buff_size);
  status_int = XAxiCdma_SimpleTransfer(&xaxicdma_my_inst, (UINTPTR) txBufferAddr, (UINTPTR)((u64)rxBufferAddr+(buff_size*i_cnt)),(u32)buff_size, NULL, NULL);
  while(XAxiCdma_IsBusy(&xaxicdma_my_inst)) {};
  Xil_DCacheInvalidateRange( (UINTPTR)txBufferAddr,(u32)buff_size);
  XAxiCdma_Reset(&xaxicdma_my_inst);
  i_cnt=(i_cnt+1)%3;
	XGpioPs_My_PwmWireack(&xgpiops_my_inst,54);
}