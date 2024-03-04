#include <math.h>
#include <sys/_types.h>
#include <xcpwm8c.h>
#include <xcpwm8c_l.h>
#include <xgpiops.h>
#include <xinterrupt_wrap.h>

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
XGpioPs_Config* xgpiops_my_config = NULL;

XClk_Wiz xclkwiz_my_inst;
XClk_Wiz_Config* xclkwiz_my_config = NULL;

XScuGic xscugic_my_inst;
XScuGic_Config xscugic_my_config;

XCpwm8c xcpwm8c_my_inst;
XCpwm8c_Config xcpwm8c_my_config;


/* Global variables */
u16 my_comp=1000;
u16 my_cmax=2000;
u8 my_eventcount=0;
XCpwm8c_onoff my_pwmonoff=REG_ON;
XCpwm8c_countmode my_countmode=COUNT_UP_DOWN;
XCpwm8c_maskmode my_maskmode=MIN_MASK;

/* Interrupt handler declaration*/
void _My_IRQHandler();

/* Function declaration*/
int Interrupt_My_Init(void);

int \
main(){
    
    u32 status= XST_SUCCESS;
    //asdf = &__data_start;
    /*
    xgpio_my_config = XGpio_LookupConfig(MY_GPIO_0_BASEADDR);
    status = XGpio_CfgInitialize(&xgpio_my_inst,xgpio_my_config,xgpio_my_config->BaseAddress);*/
    status = XGpio_My_Init(\
        &xgpio_my_inst,\
        &xgpio_my_config,\
        MY_GPIO_0_BASEADDR\
        );

    xgpiops_my_config = XGpioPs_LookupConfig(MY_GPIOPS_0_BASEADDR);
    status = XGpioPs_CfgInitialize(&xgpiops_my_inst,xgpiops_my_config,xgpiops_my_config->BaseAddr);
    XGpioPs_SetDirection(&xgpiops_my_inst,2,1);
	XGpioPs_SetOutputEnable(&xgpiops_my_inst,2,1);

    xclkwiz_my_config = XClk_Wiz_LookupConfig(MY_CLKWIZ_0_BASEADDR);
    status = XClk_Wiz_CfgInitialize(&xclkwiz_my_inst,xclkwiz_my_config,xclkwiz_my_config->BaseAddr);

    /*
    xcpwm8c_my_config = * XCpwm8c_LookupConfig(MY_CPWM8C_0_BASEADDR);
    status = XCpwm8c_CfgInitialize(&xcpwm8c_my_inst,&xcpwm8c_my_config,xcpwm8c_my_config.BaseAddr);
    */

    status = XCpwm8c_My_Init(\
        &xcpwm8c_my_inst,\
        &xcpwm8c_my_config,\
        MY_CPWM8C_0_BASEADDR\
        );

    status = XScugic_My_InitInterrupt(\
        xcpwm8c_my_config.IntrId,
        XPAR_XSCUGIC_0_BASEADDR,\
        &xscugic_my_inst,
        &xscugic_my_config,\
        &_My_IRQHandler,\
        XINTERRUPT_DEFAULT_PRIORITY,\
        XINTR_IS_EDGE_TRIGGERED\
        );

    if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}
    
    while(1){

    }

    return status;
}

void \
_My_IRQHandler(){
    // XCpwm8c_WriteCompare(&xcpwm8c_my_inst, 0, my_comp);
    // XCpwm8c_WriteCountMax(&xcpwm8c_my_inst, 0, my_cmax);
    // XCpwm8c_WritePwmOnOff(&xcpwm8c_my_inst,my_pwmonoff);
    // XCpwm8c_WriteEventCount(&xcpwm8c_my_inst,0,my_eventcount);
    
    // XCpwm8c_WriteMaskMode(&xcpwm8c_my_inst, 0, my_maskmode);
    // XCpwm8c_mWrite_MaskMode_1(MY_CPWM8C_0_BASEADDR, my_maskmode);
    // XCpwm8c_mWrite_Compare_1(MY_CPWM8C_0_BASEADDR,my_comp);
	XGpiops_My_PwmWireack(&xgpiops_my_inst,54);
}