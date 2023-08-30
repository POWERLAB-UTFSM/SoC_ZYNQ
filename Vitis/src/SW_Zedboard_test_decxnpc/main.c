/*
--------------------
main.c
--------------------
*/
#include <math.h>
#include <stdio.h>

#include "hw_zedboard_test_decxnpc.h"

#define M_2PI 6.283185307179586476925286

/*
---------------------------------------------------------------------------------
Global variable definition
---------------------------------------------------------------------------------
*/
XGpioPs xgpiops_my_inst;
XGpioPs_Config xgpiops_my_config;
XGpio xgpio_my_inst;
XGpio_Config xgpio_my_config;
XClk_Wiz xclk_wiz_my_inst;
XClk_Wiz_Config xclk_wiz_my_config;
XScuGic xscugic_my_inst;
XScuGic_Config xscugic_my_config;

u16 globalpwm_period=2000;
u16 globalpwm_compare1=0;
u16 globalpwm_compare2=0;
u16 globalpwm_compare1_off=0;
u16 globalpwm_compare2_off=0;

float time_sin=0;
float theta_sin=0;
float pwm_time=0;
float osc_sin=0;
float ref_sinpos=0;
float ref_sinneg=0;
float m_A=0.0,m_A_masked=0.0;
float f_1=50;

u8 globaldec3lxnpc_tshort=5;
u8 globaldec3lxnpc_toffon=40;
u8 globaldec3lxnpc_toffV0on=50;
u8 globaldec3lxnpc_tonoffV0=35;
u8 globaldec3lxnpc_toffonI0=45;

u32 globalxgpio_pinenable=0;

AXI_DEC3LXNPC_convtype globaldec3lxnpc_convtype=ANPC;
AXI_DEC3LXNPC_commtype globaldec3lxnpc_commtype=type_I;

u64 pwmclkfreq=50;

int status= XST_SUCCESS;

/*
---------------------------------------------------------------------------------
Function declarations
---------------------------------------------------------------------------------
*/
/*fast interrupt handler*/
//void fiq_myhandler(void *intc_inst_ptr);
/*interrupt handler*/
void irq0_myhandler(void *intc_inst_ptr);


/*
---------------------------------------------------------------------------------
---------------------------------------------------------------------------------
main()
---------------------------------------------------------------------------------
---------------------------------------------------------------------------------
*/
int main()
{
	/*initialization routines*/
	status = xgpiops_myinit(&xgpiops_my_inst,&xgpiops_my_config,XPAR_XGPIOPS_0_DEVICE_ID);
	status = xgpio_myinit(&xgpio_my_inst,&xgpio_my_config,XPAR_AXI_GPIO_0_DEVICE_ID);
	status = xclk_wiz_myinit(&xclk_wiz_my_inst,&xclk_wiz_my_config,50,XPAR_CLK_WIZ_0_DEVICE_ID);
	//status = xscugic_fiq_interrupt_myinit(&xscugic_my_inst,&xscugic_my_config,(Xil_ExceptionHandler) fiq_myhandler,XPAR_PS7_SCUGIC_0_DEVICE_ID);
	status = xscugic_irq_interrupt_myinit(&xscugic_my_inst,&xscugic_my_config,(Xil_ExceptionHandler) irq0_myhandler,XPAR_PS7_SCUGIC_0_DEVICE_ID,XPAR_FABRIC_AXI_CPWM8C_0_VEC_ID);
	axi_cpwm8c_lspwm3l_dec3lxnpc_myinit(2000);
	axi_dec3lxnpc_myinit(globaldec3lxnpc_convtype,globaldec3lxnpc_commtype,globaldec3lxnpc_tshort,globaldec3lxnpc_toffon,globaldec3lxnpc_toffV0on,globaldec3lxnpc_tonoffV0,globaldec3lxnpc_toffonI0);
	
	/*status check*/
	if (status != XST_SUCCESS){
		return XST_FAILURE;
	}

	//xil_printf("holi :D");
	while (1){
		AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,globalpwm_period);

		AXI_DEC3LXNPC_mWrite_tshort(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_tshort);
		AXI_DEC3LXNPC_mWrite_toffon(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_toffon);
		AXI_DEC3LXNPC_mWrite_toffV0on(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_toffV0on);
		AXI_DEC3LXNPC_mWrite_tonoffV0(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_tonoffV0);
		AXI_DEC3LXNPC_mWrite_toffonI0(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,globaldec3lxnpc_toffonI0);

		AXI_DEC3LXNPC_mWrite_convtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, globaldec3lxnpc_convtype );
		AXI_DEC3LXNPC_mWrite_commtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, globaldec3lxnpc_commtype );

		XGpio_DiscreteWrite(&xgpio_my_inst,1,globalxgpio_pinenable);

		if(m_A>1.0){
			m_A_masked=1.0;
		} else if (m_A<0.0){
			m_A_masked=0.0;
		}
		else {
			m_A_masked=m_A;
		}
		
	}

	// cleanup_platform();
    return 0;
}

/*
---------------------------------------------------------------------------------
irq0_myhandler()
interupt service routine handler definition
---------------------------------------------------------------------------------
*/
void irq0_myhandler(void *intc_inst_ptr) {
	u32 IntIDFull;

	//time period calculation
	pwm_time=2*(float)(globalpwm_period)/((float)(pwmclkfreq)*1E6);

	//sine wave generator with modulation index
	osc_sin=m_A_masked*sinf(theta_sin);

	//LSPWM reference de-normalizer (two references)
	ref_sinpos=(float)(globalpwm_period)*(osc_sin)+globalpwm_compare1;
	ref_sinneg=(float)(globalpwm_period)*(osc_sin+1)-globalpwm_compare2+1;

	//reference compare write to AXI_CPWM8C
	AXI_CPWM8C_mWrite_Compare_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,ref_sinpos);
	AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,ref_sinneg);

	//sine angle update generator
	theta_sin=theta_sin+2*M_PI*f_1*pwm_time;

	//sine angle update reset
	if(theta_sin>M_2PI){
		theta_sin=theta_sin-M_2PI;
	}

	//Interrupt acknowledgment signal from xgpiops to AXI_CPWM8C
	xgpiops_pwm_wireack(&xgpiops_my_inst,54);
	//-------------------------------------------------------------
	//Clear interrupt in PS
	//-------------------------------------------------------------
	IntIDFull = XScuGic_CPUReadReg(&xscugic_my_inst, XSCUGIC_INT_ACK_OFFSET);
	XScuGic_CPUWriteReg(&xscugic_my_inst, XSCUGIC_EOI_OFFSET, IntIDFull);
}
