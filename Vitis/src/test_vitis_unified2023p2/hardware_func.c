#include "hardware_func.h"


//---------------------------------------------------------------
// gpio

int \
XGpio_myinit(\
XGpio *InstancePtr, \
XGpio_Config *InstanceConfigPtr, \
UINTPTR BaseAddr){
	int status=XST_SUCCESS;

	InstanceConfigPtr = XGpio_LookupConfig(BaseAddr);
    status = XGpio_CfgInitialize(InstancePtr, InstanceConfigPtr, BaseAddr);
    if(status != XST_SUCCESS){
        return XST_FAILURE;
    }
    XGpio_SetDataDirection(InstancePtr, 1, 0b11);
    XGpio_DiscreteWrite(InstancePtr,1,0);

	return status;
}

void \
XGpio_mych1enable(\
XGpio *InstancePtr,\
u32 input){

    XGpio_DiscreteWrite(InstancePtr,1,input);

}


//---------------------------------------------------------------
// gpiops

int \
XGpiops_myinit(\
XGpioPs *InstancePtr,\
XGpioPs_Config *InstanceConfigPtr,\
UINTPTR BaseAddr){
	int status=XST_SUCCESS;

	InstanceConfigPtr = XGpioPs_LookupConfig(BaseAddr);
    status = XGpioPs_CfgInitialize(InstancePtr, InstanceConfigPtr, BaseAddr);

    if(status != XST_SUCCESS){
        return XST_FAILURE;
    }

    XGpioPs_SetDirection(InstancePtr, 2, 1);
    XGpioPs_SetOutputEnable(InstancePtr,2,1);

	return status;
}

void \
XGpiops_pwm_wireack(XGpioPs *InstancePtr,u32 pin_dir){
	XGpioPs_WritePin(InstancePtr, pin_dir, 1);
	XGpioPs_WritePin(InstancePtr, pin_dir, 0);
}

//---------------------------------------------------------------
// clk_wiz
int \
XClk_wiz_myinit(\
XClk_Wiz *InstancePtr, \
XClk_Wiz_Config *InstanceConfigPtr, \
u64 xclk_wiz_freqinit, \
UINTPTR BaseAddr){

	int status=XST_SUCCESS;

	InstanceConfigPtr=XClk_Wiz_LookupConfig(BaseAddr);
	status=XClk_Wiz_CfgInitialize(InstancePtr, InstanceConfigPtr,InstanceConfigPtr->BaseAddr);
	XClk_Wiz_WriteReg(InstanceConfigPtr->BaseAddr, XCLK_WIZ_REG25_OFFSET, 0);

    status=XClk_Wiz_WaitForLock(InstancePtr);
	status=XClk_Wiz_SetRate(InstancePtr,xclk_wiz_freqinit);
	XClk_Wiz_WriteReg(InstanceConfigPtr->BaseAddr, XCLK_WIZ_RECONFIG_OFFSET,(XCLK_WIZ_RECONFIG_LOAD | XCLK_WIZ_RECONFIG_SADDR));
	status=XClk_Wiz_WaitForLock(InstancePtr);

	return status;
}

int \
XScugic_fiq_interrupt_myinit(\
XScuGic *intc_inst_ptr, \
XScuGic_Config *intc_config, \
Xil_ExceptionHandler fiq_handler, \
UINTPTR BaseAddr){

	int status=XST_SUCCESS;

	//Initialize the interrupt controller driver so that it is ready to use.
	intc_config = XScuGic_LookupConfig(BaseAddr);
	if (NULL == intc_config) {
		return XST_FAILURE;
	}

	status = XScuGic_CfgInitialize(intc_inst_ptr, intc_config, intc_config->CpuBaseAddress);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	 //Perform a self-test to ensure that the hardware was built correctly
	status = XScuGic_SelfTest(intc_inst_ptr);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_FIQ_INT,(Xil_ExceptionHandler) fiq_handler,intc_inst_ptr);
	Xil_ExceptionEnableMask(XIL_EXCEPTION_FIQ);

	return XST_SUCCESS;
}

int \
XScugic_irq_interrupt_myinit(\
XScuGic *intc_instance_ptr, \
XScuGic_Config *intc_config, \
Xil_ExceptionHandler irq_handler, \
UINTPTR BaseAddr, \
u16 InterruptId){
	int status;

	//Initialize the interrupt controller driver so that it is ready to use.
	intc_config = XScuGic_LookupConfig(BaseAddr);
	if (NULL == intc_config) {
		return XST_FAILURE;
	}

	status = XScuGic_CfgInitialize(intc_instance_ptr, intc_config, intc_config->CpuBaseAddress);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// set the priority of IRQ_F2P[0:0] to 0xA0 (highest 0xF8, lowest 0x00) and a trigger for a rising edge trigger 0x3.
    XScuGic_SetPriorityTriggerType(intc_instance_ptr,InterruptId, 0xA0, 0x3);

	// connect the interrupt service routine isr0 to the interrupt controller
    status = XScuGic_Connect(intc_instance_ptr,InterruptId, irq_handler, (void *)intc_instance_ptr);

	 //Perform a self-test to ensure that the hardware was built correctly
	status = XScuGic_SelfTest(intc_instance_ptr);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// enable interrupts for IRQ_F2P[0:0]
    XScuGic_Enable(intc_instance_ptr,InterruptId);

	// initialize the exception table and register the interrupt controller handler with the exception table
    Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, intc_instance_ptr);

	// enable non-critical exceptions
    Xil_ExceptionEnable();

	return XST_SUCCESS;
}

void \
XCpwm8c_lspwm3l_dec3lxnpc_myinit(\
u16 pwm_period, \
UINTPTR BaseAddr){
	//u16 pwm_period=2000;
	u16 pwm_init=0;
	u16 pwm_comp1=0;
	u8 pwm_eventcount=0;
	u8 pwm_dtimeA=0;
	u8 pwm_dtimeB=0;
	u8 pwm_intmatrix=1;

	XCpwm8c_countmode pwm_countmode=COUNT_UP_DOWN;
	XCpwm8c_maskmode pwm_maskmode=MIN_MASK;
	XCpwm8c_onoff pwm_dtonoff=REG_OFF;
	XCpwm8c_logic pwm_logicA1=LOGIC_NEG;
	XCpwm8c_logic pwm_logicB1=LOGIC_NEG;
	XCpwm8c_logic pwm_logicA2=LOGIC_POS;
	XCpwm8c_logic pwm_logicB2=LOGIC_POS;
	XCpwm8c_carrsel pwm_carrsel=CARR_MASTER1;
	XCpwm8c_onoff pwm_onoff=REG_ON;
	XCpwm8c_onoff pwm_carronoff=REG_ON;

	XCpwm8c_mWrite_Period_1(BaseAddr,pwm_period);
	XCpwm8c_mWrite_Period_2(BaseAddr,pwm_period);
	XCpwm8c_mWrite_InitCarrier_1(BaseAddr,pwm_init);
	XCpwm8c_mWrite_InitCarrier_2(BaseAddr,pwm_init);
	XCpwm8c_mWrite_Compare_1(BaseAddr,pwm_comp1);
	XCpwm8c_mWrite_Compare_2(BaseAddr,pwm_comp1);
	XCpwm8c_mWrite_DeadTimeA_1(BaseAddr,pwm_dtimeA);
	XCpwm8c_mWrite_DeadTimeB_1(BaseAddr,pwm_dtimeB);
	XCpwm8c_mWrite_DeadTimeA_2(BaseAddr,pwm_dtimeA);
	XCpwm8c_mWrite_DeadTimeB_2(BaseAddr,pwm_dtimeB);
	XCpwm8c_mWrite_EventCount_1(BaseAddr,pwm_eventcount);
	XCpwm8c_mWrite_EventCount_2(BaseAddr,pwm_eventcount);
	XCpwm8c_mWrite_InterruptMatrix(BaseAddr,pwm_intmatrix);
	XCpwm8c_mWrite_CountMode_1(BaseAddr,pwm_countmode);
	XCpwm8c_mWrite_CountMode_2(BaseAddr,pwm_countmode);
	XCpwm8c_mWrite_MaskMode_1(BaseAddr,pwm_maskmode);
	XCpwm8c_mWrite_MaskMode_2(BaseAddr,pwm_maskmode);
	XCpwm8c_mWrite_DTimeOnOff_1(BaseAddr,pwm_dtonoff);
	XCpwm8c_mWrite_DTimeOnOff_2(BaseAddr,pwm_dtonoff);
	XCpwm8c_mWrite_LogicA_1(BaseAddr,pwm_logicA1);
	XCpwm8c_mWrite_LogicB_1(BaseAddr,pwm_logicB1);
	XCpwm8c_mWrite_LogicA_2(BaseAddr,pwm_logicA2);
	XCpwm8c_mWrite_LogicB_2(BaseAddr,pwm_logicB2);
	XCpwm8c_mWrite_CarrSel_1(BaseAddr,pwm_carrsel);
	XCpwm8c_mWrite_CarrSel_2(BaseAddr,pwm_carrsel);
	XCpwm8c_mWrite_CarrOnOff_1(BaseAddr,pwm_carronoff);
	XCpwm8c_mWrite_CarrOnOff_2(BaseAddr,pwm_carronoff);
	XCpwm8c_mWrite_PWMOnOff(BaseAddr,pwm_onoff);
	XCpwm8c_mWrite_IntAck(BaseAddr);
}

/*
void axi_dec3lxnpc_myinit(AXI_DEC3LXNPC_convtype dec3lxnpc_convtype,AXI_DEC3LXNPC_commtype dec3lxnpc_commtype,u8 axi_dec3lxnpc_tshort,u8 axi_dec3lxnpc_toffon,u8 axi_dec3lxnpc_toffV0on,u8 axi_dec3lxnpc_tonoffV0,u8 axi_dec3lxnpc_toffonI0){
	AXI_DEC3LXNPC_mWrite_tshort(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,axi_dec3lxnpc_tshort);
	AXI_DEC3LXNPC_mWrite_toffon(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,axi_dec3lxnpc_toffon);
	AXI_DEC3LXNPC_mWrite_toffV0on(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,axi_dec3lxnpc_toffV0on);
	AXI_DEC3LXNPC_mWrite_tonoffV0(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,axi_dec3lxnpc_tonoffV0);
	AXI_DEC3LXNPC_mWrite_toffonI0(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,axi_dec3lxnpc_toffonI0);

	AXI_DEC3LXNPC_mWrite_convtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, dec3lxnpc_convtype );
	AXI_DEC3LXNPC_mWrite_commtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, dec3lxnpc_commtype );
}
*/