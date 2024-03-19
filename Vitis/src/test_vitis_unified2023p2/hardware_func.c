#include "hardware_func.h"

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


/* Buffer variables */
volatile uint8_t* ___tx_buffer = (uint8_t*) 0x00100000;
volatile uint8_t* ___rx_buffer = (uint8_t*) 0x00100000;

UINTPTR* ___txBufferAddr;
UINTPTR* ___rxBufferAddr;

u32 ___buff_size;
u32 ___i_cnt  __attribute__((section (".data1"))) = 0;
u32 ___k_samp __attribute__((section (".data1"))) = 3;

void \
_Buffer_My_Init(\
  void\
)
{
  ___tx_buffer = (uint8_t*) &__data1_start;
  ___buff_size = (u64)(&__data1_end)-(u64)(&__data1_start);
  ___rx_buffer = (uint8_t*) (&__data1_end + 0x00010000);

  for(u32 i=0;i<___buff_size;i++)
  {
    //tx_buffer[i]=i;    
    ___rx_buffer[i]=0x00;
  }

  ___txBufferAddr = (UINTPTR*)&___tx_buffer[0];
  ___rxBufferAddr = (UINTPTR*)&___rx_buffer[0];
}

u32 _Buffer_My_SimpleTransfer(\
  void\
)
{
  u32 status = XST_FAILURE;

  if(___buff_size<=0)
    return XST_SUCCESS;

  Xil_DCacheFlushRange( (UINTPTR)___txBufferAddr,(u32)___buff_size);
  Xil_DCacheFlushRange( (UINTPTR)((u64)___rxBufferAddr+(u64)(___buff_size*___i_cnt)),(u32)___buff_size);
  status = XAxiCdma_SimpleTransfer(&xaxicdma_my_inst, (UINTPTR) ___txBufferAddr, (UINTPTR)((u64)___rxBufferAddr+(u64)(___buff_size*___i_cnt)),(u32)___buff_size, NULL, NULL);

  // while(XAxiCdma_IsBusy(&xaxicdma_my_inst)) {};
  // Xil_DCacheInvalidateRange( (UINTPTR)___txBufferAddr,(u32)___buff_size);
  // XAxiCdma_Reset(&xaxicdma_my_inst);
  ___i_cnt=(___i_cnt+1)%___k_samp;

  return status;
}

u32 _Buffer_My_Reset(\
  void\
)
{
  u32 status = XST_FAILURE;

  if(___buff_size<=0)
    return XST_SUCCESS;

  while(XAxiCdma_IsBusy(&xaxicdma_my_inst)) {};
  Xil_DCacheInvalidateRange( (UINTPTR)___txBufferAddr,(u32)___buff_size);
  XAxiCdma_Reset(&xaxicdma_my_inst);
  // ___i_cnt=(___i_cnt+1)%___k_samp;

  return status;
}


int _HW_My_Init(void)
{
  u32 status = XST_FAILURE;

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

  status = XScuGic_My_Init(\
		&xscugic_my_inst,\
		&xscugic_my_config,\
		MY_SCUGIC_0_BASEADDR\
		);

  return status;
}

int \
XScuGic_My_Init(\
  XScuGic *InstancePtr,\
  XScuGic_Config *InstanceCfg,\
  UINTPTR BaseAddr\
)
{
  int status = XST_FAILURE;
	XScuGic_Config * ICfg = NULL;

  ICfg  = XScuGic_LookupConfig(BaseAddr);
	if (NULL == ICfg) {
		return XST_FAILURE;
	}
	status = XScuGic_CfgInitialize(InstancePtr,ICfg,ICfg->CpuBaseAddress);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

  *InstanceCfg=*ICfg;

  return status;
}


int \
XScugic_My_InitInterrupt(\
	u32 IntrId,\
	XScuGic *IntInstance,\
	Xil_ExceptionHandler IntHandler,\
	u32 Priority,\
	u32 Trigger\
)
{
	int status = XST_FAILURE;

  XScuGic_InterruptMaptoCpu(IntInstance,1,XGet_IntrId(IntrId)+XGet_IntrOffset(IntrId));

	// set the priority of IRQ_F2P[0:0] to 0xA0 (highest 0xF8, lowest 0x00) and a trigger for a rising edge trigger 0x3.
	XScuGic_SetPriorityTriggerType(\
		IntInstance,\
		XGet_IntrId(IntrId)+XGet_IntrOffset(IntrId),\
		Priority,\
		Trigger);

	// connect the interrupt service routine isr0 to the interrupt controller
	status = XScuGic_Connect(\
		IntInstance,\
		XGet_IntrId(IntrId)+XGet_IntrOffset(IntrId), \
		IntHandler, \
		(void *)IntInstance);

	// Perform a self-test to ensure that the hardware was built correctly
	status = XScuGic_SelfTest(IntInstance);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

  

	// enable interrupts for IRQ_F2P[0:0]
	XScuGic_Enable(IntInstance,XGet_IntrId(IntrId)+XGet_IntrOffset(IntrId));

	// initialize the exception table and register the interrupt controller handler with the exception table
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, IntInstance);

	// enable non-critical exceptions
	Xil_ExceptionEnable();

	return status;
}

int \
XAxiCdma_My_Init(\
  XAxiCdma *InstancePtr,\
  XAxiCdma_Config *InstanceCfg,\
  UINTPTR BaseAddr\
)
{
  int status = XST_FAILURE;
	XAxiCdma_Config * ICfg = NULL;

  ICfg  = XAxiCdma_LookupConfig(BaseAddr);
	if (NULL == ICfg) {
		return XST_FAILURE;
	}
	status = XAxiCdma_CfgInitialize(InstancePtr,ICfg,ICfg->BaseAddress);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

  XAxiCdma_IntrDisable(InstancePtr, XAXICDMA_XR_IRQ_ALL_MASK);

  *InstanceCfg=*ICfg;

  return status;
}

void \
_My_XCpwm8c_IntAckGpioPs(void)
{
	XGpioPs_WritePin(&xgpiops_my_inst, 54, 1);
	XGpioPs_WritePin(&xgpiops_my_inst, 54, 0);
}

void \
XGpio_My_Ch1Enable(\
XGpio *InstancePtr,\
u32 input){

    XGpio_DiscreteWrite(InstancePtr,1,input);

}

int \
XGpio_My_Init(XGpio *InstancePtr,XGpio_Config *InstanceCfg, UINTPTR BaseAddr)
{
	u32 status = XST_SUCCESS;

	//XCpwm8c *IPtr = NULL;
	XGpio_Config *ICfg = NULL;
	
	ICfg  = XGpio_LookupConfig(BaseAddr);
	if (NULL == ICfg) {
		return XST_FAILURE;
	}
	status = XGpio_CfgInitialize(InstancePtr,ICfg,ICfg->BaseAddress);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	*InstanceCfg=*ICfg;
	//*InstancePtr=*IPtr;

	return status;
}

int \
XClk_Wiz_My_Init(XClk_Wiz *InstancePtr,XClk_Wiz_Config *InstanceCfg, UINTPTR BaseAddr)
{
	u32 status = XST_SUCCESS;

	//XCpwm8c *IPtr = NULL;
	XClk_Wiz_Config *ICfg = NULL;
	
	ICfg  = XClk_Wiz_LookupConfig(BaseAddr);
	if (NULL == ICfg) {
		return XST_FAILURE;
	}
	status = XClk_Wiz_CfgInitialize(InstancePtr,ICfg,ICfg->BaseAddr);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	*InstanceCfg=*ICfg;
	//*InstancePtr=*IPtr;

	return status;
}

int \
XGpioPs_My_Init(XGpioPs *InstancePtr,XGpioPs_Config *InstanceCfg, UINTPTR BaseAddr)
{
	u32 status = XST_SUCCESS;

	//XCpwm8c *IPtr = NULL;
	XGpioPs_Config *ICfg = NULL;
	
	ICfg  = XGpioPs_LookupConfig(BaseAddr);
	if (NULL == ICfg) {
		return XST_FAILURE;
	}
	status = XGpioPs_CfgInitialize(InstancePtr,ICfg,ICfg->BaseAddr);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

  XGpioPs_SetDirection(InstancePtr,XGPIOPS_BANK2,1);
	XGpioPs_SetOutputEnable(InstancePtr,XGPIOPS_BANK2,1);

	*InstanceCfg=*ICfg;
	//*InstancePtr=*IPtr;

	return status;
}

int \
XCpwm8c_My_Init(XCpwm8c *InstancePtr,XCpwm8c_Config *InstanceCfg, UINTPTR BaseAddr)
{
	u32 status = XST_SUCCESS;

	XCpwm8c_Config *ICfg = NULL;
	
	ICfg  = XCpwm8c_LookupConfig(BaseAddr);
	if (NULL == ICfg) {
		return XST_FAILURE;
	}
	status = XCpwm8c_CfgInitialize(InstancePtr,ICfg,ICfg->BaseAddr);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}
/*
	XCpwm8c_WriteCountMax(InstancePtr,0,2000);
	XCpwm8c_WriteCountMax(InstancePtr,1,2000);
	XCpwm8c_WriteCompare(InstancePtr,0,1000);
	XCpwm8c_WriteCompare(InstancePtr,1,1000);
	XCpwm8c_WriteCountMode(InstancePtr,0,COUNT_UP_DOWN);
	XCpwm8c_WriteCountMode(InstancePtr,1,COUNT_UP_DOWN);
	XCpwm8c_WriteMaskMode(InstancePtr,0,MIN_MASK);
	XCpwm8c_WriteMaskMode(InstancePtr,1,MIN_MASK);
	XCpwm8c_WriteCarrOnOff(InstancePtr,0,REG_ON);
	XCpwm8c_WriteCarrOnOff(InstancePtr,1,REG_ON);
	XCpwm8c_WriteCarrSel(InstancePtr,0,CARR_MASTER1);
	XCpwm8c_WriteCarrSel(InstancePtr,1,CARR_MASTER1);
	XCpwm8c_WriteDTimeOnOff(InstancePtr,0,REG_OFF);
	XCpwm8c_WriteDTimeOnOff(InstancePtr,1,REG_OFF);
	XCpwm8c_WriteLogicA(InstancePtr,0,LOGIC_NEG);
	XCpwm8c_WriteLogicA(InstancePtr,1,LOGIC_POS);
	XCpwm8c_WriteLogicA(InstancePtr,0,LOGIC_NEG);
	XCpwm8c_WriteLogicA(InstancePtr,1,LOGIC_POS);
	XCpwm8c_WriteIntMatrix(InstancePtr,1);
	XCpwm8c_WritePwmOnOff(InstancePtr,REG_ON);
	XCpwm8c_WriteIntAck(InstancePtr);
*/
	*InstanceCfg=*ICfg;
	//*InstancePtr=*IPtr;

	return status;
}

void XCpwm8c_My_InitLow(UINTPTR BaseAddress)
{
	u16 pwm_period=2000;
	u16 pwm_init=0;
	u16 pwm_comp1=1000;
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

	XCpwm8c_mWrite_Period_1(BaseAddress,pwm_period);
	XCpwm8c_mWrite_Period_2(BaseAddress,pwm_period);
	XCpwm8c_mWrite_InitCarrier_1(BaseAddress,pwm_init);
	XCpwm8c_mWrite_InitCarrier_2(BaseAddress,pwm_init);
	XCpwm8c_mWrite_Compare_1(BaseAddress,pwm_comp1);
	XCpwm8c_mWrite_Compare_2(BaseAddress,pwm_comp1);
	XCpwm8c_mWrite_DeadTimeA_1(BaseAddress,pwm_dtimeA);
	XCpwm8c_mWrite_DeadTimeB_1(BaseAddress,pwm_dtimeB);
	XCpwm8c_mWrite_DeadTimeA_2(BaseAddress,pwm_dtimeA);
	XCpwm8c_mWrite_DeadTimeB_2(BaseAddress,pwm_dtimeB);
	XCpwm8c_mWrite_EventCount_1(BaseAddress,pwm_eventcount);
	XCpwm8c_mWrite_EventCount_2(BaseAddress,pwm_eventcount);
	XCpwm8c_mWrite_InterruptMatrix(BaseAddress,pwm_intmatrix);
	XCpwm8c_mWrite_CountMode_1(BaseAddress,pwm_countmode);
	XCpwm8c_mWrite_CountMode_2(BaseAddress,pwm_countmode);
	XCpwm8c_mWrite_MaskMode_1(BaseAddress,pwm_maskmode);
	XCpwm8c_mWrite_MaskMode_2(BaseAddress,pwm_maskmode);
	XCpwm8c_mWrite_DTimeOnOff_1(BaseAddress,pwm_dtonoff);
	XCpwm8c_mWrite_DTimeOnOff_2(BaseAddress,pwm_dtonoff);
	XCpwm8c_mWrite_LogicA_1(BaseAddress,pwm_logicA1);
	XCpwm8c_mWrite_LogicB_1(BaseAddress,pwm_logicB1);
	XCpwm8c_mWrite_LogicA_2(BaseAddress,pwm_logicA2);
	XCpwm8c_mWrite_LogicB_2(BaseAddress,pwm_logicB2);
	XCpwm8c_mWrite_CarrSel_1(BaseAddress,pwm_carrsel);
	XCpwm8c_mWrite_CarrSel_2(BaseAddress,pwm_carrsel);
	XCpwm8c_mWrite_CarrOnOff_1(BaseAddress,pwm_carronoff);
	XCpwm8c_mWrite_CarrOnOff_2(BaseAddress,pwm_carronoff);
	XCpwm8c_mWrite_PWMOnOff(BaseAddress,pwm_onoff);
	XCpwm8c_mWrite_IntAck(BaseAddress);
}
