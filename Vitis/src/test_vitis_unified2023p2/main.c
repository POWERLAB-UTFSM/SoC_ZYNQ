#include <math.h>

#include "hardware_func.h"

volatile XGpio xgpio_my_inst;
volatile XGpio_Config xgpio_my_config;

volatile XGpioPs xgpiops_my_inst;
volatile XGpioPs_Config xgpiops_my_config;

volatile XClk_Wiz xclkwiz_my_inst;
volatile XClk_Wiz_Config xclkwiz_my_config;

volatile XScuGic xscugic_my_inst;
volatile XScuGic_Config xscugic_my_config;

// void fiq_myhandler(void *intc_inst_ptr);
//void irq0_myhandler(void *intc_inst_ptr);

int \
main(){
    
    int status= XST_SUCCESS;

    int asd=SDT;

    u32 my_write=0;
    double my_sinans=0.0;
    double my_sinarg=3.141592;

    status = xgpio_myinit(&xgpio_my_inst,MY_GPIO_0_BASEADDR);
    status = xgpiops_myinit(&xgpiops_my_inst,&xgpiops_my_config,MY_GPIOPS_0_BASEADDR);
    status = xclk_wiz_myinit(&xclkwiz_my_inst,&xclkwiz_my_config,50,MY_CLKWIZ_0_BASEADDR);
    axi_cpwm8c_lspwm3l_dec3lxnpc_myinit(2000,MY_CPWM8C_0_BASEADDR);

    status = XConfigInterruptCntrl(XPAR_AXI_CPWM8C_0_INTERRUPT_PARENT);
    //status = xscugic_fiq_interrupt_myinit(&xscugic_my_inst,&xscugic_my_config,(Xil_ExceptionHandler) fiq_myhandler,XPAR_XSCUGIC_0_BASEADDR);
    //status = xscugic_irq_interrupt_myinit(&xscugic_my_inst,&xscugic_my_config,(Xil_ExceptionHandler) irq0_myhandler,XPAR_PS7_SCUGIC_0_BASEADDR,XPAR_FABRIC_AXI_CPWM8C_0_VEC_ID);
   

    while(1){
        //my_sinans=sin(my_sinarg);  
        //xgpio_mych1enable(&xgpio_my_inst,my_write);
    }

    return status;
}

/*
void \
irq0_myhandler(\
void *intc_inst_ptr) {

	//xgpiops_pwm_wireack(,54);
    XGpioPs_WritePin(InstancePtr, pin_dir, 1)
}*/