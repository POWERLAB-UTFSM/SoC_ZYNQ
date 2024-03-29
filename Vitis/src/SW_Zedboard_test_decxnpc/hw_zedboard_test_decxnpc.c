#include "hw_zedboard_test_decxnpc.h"



/*static inline void xgpiops_pwm_wireack(XGpioPs *InstancePtr,u32 pin_dir){
	XGpioPs_WritePin(InstancePtr, pin_dir, 1);
	XGpioPs_WritePin(InstancePtr, pin_dir, 0);
}*/


int xgpiops_myinit(XGpioPs *InstancePtr, XGpioPs_Config *InstanceConfigPtr, u16 DeviceId){
	int status;
	InstanceConfigPtr= XGpioPs_LookupConfig(DeviceId);
	status=XGpioPs_CfgInitialize(InstancePtr,InstanceConfigPtr,InstanceConfigPtr->BaseAddr);
	XGpioPs_SetDirection(InstancePtr,2,1);
	XGpioPs_SetOutputEnable(InstancePtr,2,1);

	return status;
}

int xgpio_myinit(XGpio *InstancePtr, XGpio_Config *InstanceConfigPtr, u16 DeviceId){
	int status;
	InstanceConfigPtr=XGpio_LookupConfig(DeviceId);
	status=XGpio_CfgInitialize(InstancePtr,InstanceConfigPtr,InstanceConfigPtr->BaseAddress);
	XGpio_SetDataDirection(InstancePtr,1,0b11);
	/*XGpio_SetDataDirection(&xgpio,2,0);*/
	XGpio_DiscreteWrite(InstancePtr,1,0);
	/*XGpio_DiscreteWrite(&xgpio,2,0);*/

	return status;
}
int xclk_wiz_myinit(XClk_Wiz *InstancePtr, XClk_Wiz_Config *InstanceConfigPtr,u64 xclk_wiz_freqinit, u16 DeviceId){
	int status;
	InstanceConfigPtr=XClk_Wiz_LookupConfig(DeviceId);
	status=XClk_Wiz_CfgInitialize(InstancePtr, InstanceConfigPtr,InstanceConfigPtr->BaseAddr);
	XClk_Wiz_WriteReg(InstanceConfigPtr->BaseAddr, XCLK_WIZ_REG25_OFFSET, 0);
	//status=XClk_Wiz_WaitForLock(&xclkwiz);
	status=XClk_Wiz_SetRate(InstancePtr,xclk_wiz_freqinit);
	XClk_Wiz_WriteReg(InstanceConfigPtr->BaseAddr, XCLK_US_WIZ_RECONFIG_OFFSET,(XCLK_WIZ_RECONFIG_LOAD | XCLK_WIZ_RECONFIG_SADDR));
	status=XClk_Wiz_WaitForLock(InstancePtr);

	return status;
}

int xscugic_fiq_interrupt_myinit(XScuGic *intc_instance_ptr,XScuGic_Config *intc_config,Xil_ExceptionHandler fiq_handler,u16 DeviceId){
	int status;

	//Initialize the interrupt controller driver so that it is ready to use.
	intc_config = XScuGic_LookupConfig(DeviceId);
	if (NULL == intc_config) {
		return XST_FAILURE;
	}

	status = XScuGic_CfgInitialize(intc_instance_ptr, intc_config, intc_config->CpuBaseAddress);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	 //Perform a self-test to ensure that the hardware was built correctly
	status = XScuGic_SelfTest(intc_instance_ptr);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_FIQ_INT,(Xil_ExceptionHandler) fiq_handler,intc_instance_ptr);
	Xil_ExceptionEnableMask(XIL_EXCEPTION_FIQ);

	return XST_SUCCESS;
}

int xscugic_irq_interrupt_myinit(XScuGic *intc_instance_ptr,XScuGic_Config *intc_config,Xil_ExceptionHandler irq_handler,u16 DeviceId,u16 InterruptId){
	int status;

	//Initialize the interrupt controller driver so that it is ready to use.
	intc_config = XScuGic_LookupConfig(DeviceId);
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

void axi_cpwm8c_lspwm3l_dec3lxnpc_myinit(u16 pwm_period){
	//u16 pwm_period=2000;
	u16 pwm_init=0;
	u16 pwm_comp1=0;
	u8 pwm_eventcount=0;
	u8 pwm_dtimeA=0;
	u8 pwm_dtimeB=0;
	u8 pwm_intmatrix=1;

	AXI_CPWM8C_count_mode pwm_countmode=COUNT_UP_DOWN;
	AXI_CPWM8C_mask_mode pwm_maskmode=MIN_MASK;
	AXI_CPWM8C_onoff pwm_dtonoff=REG_OFF;
	AXI_CPWM8C_logic pwm_logicA1=LOGIC_NEG;
	AXI_CPWM8C_logic pwm_logicB1=LOGIC_NEG;
	AXI_CPWM8C_logic pwm_logicA2=LOGIC_POS;
	AXI_CPWM8C_logic pwm_logicB2=LOGIC_POS;
	AXI_CPWM8C_carrsel pwm_carrsel=CARR_MASTER1;
	AXI_CPWM8C_onoff pwm_onoff=REG_ON;
	AXI_CPWM8C_onoff pwm_carronoff=REG_ON;

	AXI_CPWM8C_mWrite_Period_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
	AXI_CPWM8C_mWrite_Period_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_period);
	AXI_CPWM8C_mWrite_InitCarrier_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_init);
	AXI_CPWM8C_mWrite_InitCarrier_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_init);
	AXI_CPWM8C_mWrite_Compare_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
	AXI_CPWM8C_mWrite_Compare_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_comp1);
	AXI_CPWM8C_mWrite_DeadTimeA_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
	AXI_CPWM8C_mWrite_DeadTimeB_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
	AXI_CPWM8C_mWrite_DeadTimeA_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeA);
	AXI_CPWM8C_mWrite_DeadTimeB_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtimeB);
	AXI_CPWM8C_mWrite_EventCount_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
	AXI_CPWM8C_mWrite_EventCount_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_eventcount);
	AXI_CPWM8C_mWrite_InterruptMatrix(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_intmatrix);
	AXI_CPWM8C_mWrite_CountMode_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
	AXI_CPWM8C_mWrite_CountMode_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_countmode);
	AXI_CPWM8C_mWrite_MaskMode_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
	AXI_CPWM8C_mWrite_MaskMode_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_maskmode);
	AXI_CPWM8C_mWrite_DTimeOnOff_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
	AXI_CPWM8C_mWrite_DTimeOnOff_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_dtonoff);
	AXI_CPWM8C_mWrite_LogicA_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA1);
	AXI_CPWM8C_mWrite_LogicB_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB1);
	AXI_CPWM8C_mWrite_LogicA_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicA2);
	AXI_CPWM8C_mWrite_LogicB_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_logicB2);
	AXI_CPWM8C_mWrite_CarrSel_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
	AXI_CPWM8C_mWrite_CarrSel_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carrsel);
	AXI_CPWM8C_mWrite_CarrOnOff_1(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carronoff);
	AXI_CPWM8C_mWrite_CarrOnOff_2(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_carronoff);
	AXI_CPWM8C_mWrite_PWMOnOff(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR,pwm_onoff);
	AXI_CPWM8C_IntAck(XPAR_AXI_CPWM8C_0_S_AXI_BASEADDR);
}

void axi_dec3lxnpc_myinit(AXI_DEC3LXNPC_convtype dec3lxnpc_convtype,AXI_DEC3LXNPC_commtype dec3lxnpc_commtype,u8 axi_dec3lxnpc_tshort,u8 axi_dec3lxnpc_toffon,u8 axi_dec3lxnpc_toffV0on,u8 axi_dec3lxnpc_tonoffV0,u8 axi_dec3lxnpc_toffonI0){
	AXI_DEC3LXNPC_mWrite_tshort(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,axi_dec3lxnpc_tshort);
	AXI_DEC3LXNPC_mWrite_toffon(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,axi_dec3lxnpc_toffon);
	AXI_DEC3LXNPC_mWrite_toffV0on(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,axi_dec3lxnpc_toffV0on);
	AXI_DEC3LXNPC_mWrite_tonoffV0(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,axi_dec3lxnpc_tonoffV0);
	AXI_DEC3LXNPC_mWrite_toffonI0(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR,axi_dec3lxnpc_toffonI0);

	AXI_DEC3LXNPC_mWrite_convtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, dec3lxnpc_convtype );
	AXI_DEC3LXNPC_mWrite_commtype(XPAR_AXI_DEC3LXNPC_0_S00_AXI_BASEADDR, dec3lxnpc_commtype );
}
