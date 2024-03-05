#include <math.h>
#include <xaxicdma.h>

#include "hardware_func.h"

#define XBUFFER_SIZE 300

/* Memory section definitions from linker*/
extern UINTPTR __data_start;
extern UINTPTR __data_end;

static volatile double gv_sinans[1]={3.141592};
static volatile double gv_sinarg[1]={3.141592};
static volatile double gv_xbuffer[XBUFFER_SIZE]  = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
static volatile double gv_xarg[1]={3.141592};

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
XCpwm8c_onoff my_pwmonoff=REG_ON;
XCpwm8c_countmode my_countmode=COUNT_UP_DOWN;
XCpwm8c_maskmode my_maskmode=MIN_MASK;

u32 i_cnt=0;

/* Interrupt handler declaration*/
void _My_IRQHandler();

/*------------------------------------------------------------------------------------------*/
/*  main  */
/*------------------------------------------------------------------------------------------*/
int \
main(){
   
	u32 status= XST_SUCCESS;

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

	i_cnt=(i_cnt+1)%3;
	
	XGpiops_My_PwmWireack(&xgpiops_my_inst,54);
}