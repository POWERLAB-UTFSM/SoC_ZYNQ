#include <math.h>
#include <sys/_types.h>
#include <xcpwm8c.h>
#include <xcpwm8c_l.h>
#include <xgpiops.h>
#include "xinterrupt_wrap.h"

#include "hardware_func.h"

#define XBUFFER_SIZE 300

/* Memory section definitions from linker*/
extern UINTPTR __data_start;
extern UINTPTR __data_end;

static volatile double gv_sinans[1]={3.141592};
static volatile double gv_sinarg[1]={3.141592};
static volatile double gv_xbuffer[XBUFFER_SIZE]  = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
static volatile double gv_xarg[1]={3.141592};

// void fiq_myhandler(void *intc_inst_ptr);
//void irq0_myhandler(void *intc_inst_ptr);


/* Global driver intances*/
XGpio xgpio_my_inst;
XGpio_Config* xgpio_my_config = 0;

XGpioPs xgpiops_my_inst;
XGpioPs_Config* xgpiops_my_config = 0;

XClk_Wiz xclkwiz_my_inst;
XClk_Wiz_Config* xclkwiz_my_config = 0;

XScuGic xscugic_my_inst;
XScuGic_Config* xscugic_my_config = 0;

XCpwm8c xcpwm8c_my_inst;
XCpwm8c_Config* xcpwm8c_my_config = 0;

u16 my_comp=1000;
u16 my_cmax=2000;
u8 my_eventcount=0;
XCpwm8c_onoff my_pwmonoff=REG_ON;
XCpwm8c_countmode my_countmode=COUNT_UP_DOWN;
XCpwm8c_maskmode my_maskmode=MIN_MASK;

/* Interrupt handler*/
void Interrupt_My_FIQHandler();

int \
main(){
    
    unsigned long status= XST_SUCCESS;

    volatile UINTPTR asdf;
    volatile int wohl=-1;

    u32 my_write=0;

    

    asdf = &__data_start;
    

    xgpio_my_config = XGpio_LookupConfig(MY_GPIO_0_BASEADDR);
    status = XGpio_CfgInitialize(&xgpio_my_inst,xgpio_my_config,xgpio_my_config->BaseAddress);

    xgpiops_my_config = XGpioPs_LookupConfig(MY_GPIOPS_0_BASEADDR);
    status = XGpioPs_CfgInitialize(&xgpiops_my_inst,xgpiops_my_config,xgpiops_my_config->BaseAddr);
    XGpioPs_SetDirection(&xgpiops_my_inst,2,1);
	XGpioPs_SetOutputEnable(&xgpiops_my_inst,2,1);

    xclkwiz_my_config = XClk_Wiz_LookupConfig(MY_CLKWIZ_0_BASEADDR);
    status = XClk_Wiz_CfgInitialize(&xclkwiz_my_inst,xclkwiz_my_config,xclkwiz_my_config->BaseAddr);

    xcpwm8c_my_config = XCpwm8c_LookupConfig(MY_CPWM8C_0_BASEADDR);
    status = XCpwm8c_CfgInitialize(&xcpwm8c_my_inst,xcpwm8c_my_config,xcpwm8c_my_config->BaseAddr);

    XCpwm8c_my_init(&xcpwm8c_my_inst);
    //XCpwm8c_my_initlow(MY_CPWM8C_0_BASEADDR);

    status = XSetupInterruptSystem(&xcpwm8c_my_inst,&Interrupt_My_FIQHandler,xcpwm8c_my_config->IntrId,xcpwm8c_my_config->IntrParent,XINTERRUPT_DEFAULT_PRIORITY);

    
    //axi_cpwm8c_lspwm3l_dec3lxnpc_myinit(2000,MY_CPWM8C_0_BASEADDR);

    //status = XConfigInterruptCntrl(XPAR_AXI_CPWM8C_0_INTERRUPT_PARENT);
    //status = xscugic_fiq_interrupt_myinit(&xscugic_my_inst,&xscugic_my_config,(Xil_ExceptionHandler) fiq_myhandler,XPAR_XSCUGIC_0_BASEADDR);
    //status = xscugic_irq_interrupt_myinit(&xscugic_my_inst,&xscugic_my_config,(Xil_ExceptionHandler) irq0_myhandler,XPAR_PS7_SCUGIC_0_BASEADDR,XPAR_FABRIC_AXI_CPWM8C_0_VEC_ID);

   
    while(1){
        gv_sinans[0]=sin(gv_sinarg[0]);  
        XCpwm8c_mWrite_EventCount_1(MY_CPWM8C_0_BASEADDR,my_eventcount);
        XGpio_mych1enable(&xgpio_my_inst,my_write);
    //     for (u32 i=0;i < XBUFFER_SIZE; i++){
    //         gv_xbuffer[i]=gv_sinans[0]*(double)(i);
    //         gv_xarg[0]=gv_sinans[0]/3.0;
    //     }
    }

    return status;
}

void \
Interrupt_My_FIQHandler(){
    //Interrupt acknowledgment signal from xgpiops to AXI_CPWM8C
    XCpwm8c_WriteCompare(&xcpwm8c_my_inst, 0, my_comp);
    XCpwm8c_WriteCountMax(&xcpwm8c_my_inst, 0, my_cmax);
    XCpwm8c_WritePwmOnOff(&xcpwm8c_my_inst,my_pwmonoff);
    //XCpwm8c_WriteEventCount(&xcpwm8c_my_inst,0,my_eventcount);
    
    //XCpwm8c_WriteMaskMode(&xcpwm8c_my_inst, 0, my_maskmode);
 //   XCpwm8c_mWrite_MaskMode_1(MY_CPWM8C_0_BASEADDR, my_maskmode);
    //XCpwm8c_mWrite_Compare_1(MY_CPWM8C_0_BASEADDR,my_comp);
	XGpiops_My_PwmWireack(&xgpiops_my_inst,54);
}

/*
void \
irq0_myhandler(\
void *intc_inst_ptr) {

	//xgpiops_pwm_wireack(,54);
    XGpioPs_WritePin(InstancePtr, pin_dir, 1)
}*/