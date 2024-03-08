

/***************************** Include Files *******************************/
#include "xcpwm8c.h"
#include "xstatus.h"



/************************** Function Definitions ***************************/

int XCpwm8c_CfgInitialize(XCpwm8c * InstancePtr,const  XCpwm8c_Config * Config, UINTPTR EffectiveAddr)
{
	/* Assert arguments */
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(Config != NULL);
	Xil_AssertNonvoid(EffectiveAddr != (u32)0);

	/* Set some default values. */
	InstancePtr->BaseAddr = EffectiveAddr;
	InstancePtr->IntMatrix = 0;
	InstancePtr->PwmOnOff = REG_OFF;
	
	for(u16 i_ch=0; i_ch < CPWM8C_N_CHANNEL;i_ch++){
		InstancePtr->ChParam[i_ch].CountMaxim=0;
		InstancePtr->ChParam[i_ch].InitCarr=0;
		InstancePtr->ChParam[i_ch].Compare=0;
		InstancePtr->ChParam[i_ch].DeadTimeA=0;
		InstancePtr->ChParam[i_ch].DeadTimeB=0;
		InstancePtr->ChParam[i_ch].EventCount=0;
		InstancePtr->ChParam[i_ch].CountMode=NO_COUNT;
		InstancePtr->ChParam[i_ch].MaskMode=NO_MASK;
		InstancePtr->ChParam[i_ch].DTimeOnOff=REG_OFF;
		InstancePtr->ChParam[i_ch].LogicA=LOGIC_POS;
		InstancePtr->ChParam[i_ch].LogicB=LOGIC_POS;
		InstancePtr->ChParam[i_ch].CarrSel=CARR_MASTER1;
		InstancePtr->ChParam[i_ch].CarrOnOff=REG_OFF;
	}

	/*
	 * Indicate the instance is now ready to use, initialized without error
	 */
	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;
	XCpwm8c_WriteFullStatus(InstancePtr);
	return (XST_SUCCESS);
}

void XCpwm8c_WriteFullStatus(const XCpwm8c * InstancePtr)
{
	for(u16 i_ch=0; i_ch < CPWM8C_N_CHANNEL;i_ch++){
		XCpwm8c_WriteCountMax(InstancePtr, i_ch, 0);
		XCpwm8c_WriteCountInit(InstancePtr, i_ch, 0);
		XCpwm8c_WriteCompare(InstancePtr, i_ch, 0);
		XCpwm8c_WriteDeadTimeA(InstancePtr, i_ch, 0);
		XCpwm8c_WriteDeadTimeB(InstancePtr, i_ch, 0);
		XCpwm8c_WriteEventCount(InstancePtr, i_ch, 0);
		XCpwm8c_WriteCountMode(InstancePtr, i_ch, NO_COUNT);
		XCpwm8c_WriteMaskMode(InstancePtr, i_ch, NO_MASK);
		XCpwm8c_WriteDTimeOnOff(InstancePtr, i_ch, REG_OFF);
		XCpwm8c_WriteLogicA(InstancePtr, i_ch, LOGIC_POS);
		XCpwm8c_WriteLogicB(InstancePtr, i_ch, LOGIC_POS);
		XCpwm8c_WriteCarrSel(InstancePtr, i_ch, CARR_MASTER1);
		XCpwm8c_WriteCarrOnOff(InstancePtr, i_ch,REG_OFF);
	}
	XCpwm8c_WritePwmOnOff(InstancePtr,REG_OFF);
	XCpwm8c_WriteIntMatrix(InstancePtr,0);
}

void XCpwm8c_WriteCountMax(const XCpwm8c *InstancePtr, u16 Channel, u16 CountMaxim)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].CountMaxim=CountMaxim;
		Xil_Out16((InstancePtr->BaseAddr) + (UINTPTR)((Channel)<<1), (u16)(CountMaxim));
	}
}

void XCpwm8c_WriteCountInit(const XCpwm8c *InstancePtr, u16 Channel, u16 CountInit)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].InitCarr=CountInit;
		Xil_Out16(InstancePtr->BaseAddr + CPWM8C_OFFSET_COUNTINIT + (UINTPTR)((Channel)<<1), (u16)(CountInit));
	}
}

void XCpwm8c_WriteCompare(const XCpwm8c *InstancePtr, u16 Channel, u16 Compare)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].Compare=Compare;
		Xil_Out16(InstancePtr->BaseAddr + CPWM8C_OFFSET_COMPARE + (UINTPTR)((Channel)<<1), (u16)(Compare));
	}
}

void XCpwm8c_WriteDeadTimeA(const XCpwm8c *InstancePtr, u16 Channel, u8 DeadTime)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].DeadTimeA=DeadTime;
		Xil_Out8(InstancePtr->BaseAddr + CPWM8C_OFFSET_DEADTIMEA + (Channel), (u8)(DeadTime));
	}
}

void XCpwm8c_WriteDeadTimeB(const XCpwm8c *InstancePtr, u16 Channel, u8 DeadTime)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].DeadTimeB=DeadTime;
		Xil_Out8(InstancePtr->BaseAddr + CPWM8C_OFFSET_DEADTIMEB + (Channel), (u8)(DeadTime));
	}
}

void XCpwm8c_WriteEventCount(const XCpwm8c *InstancePtr, u16 Channel, u8 EventCount)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].EventCount=EventCount;
		XCpwm8c_Out32MaskedShiftedUp(InstancePtr->BaseAddr,CPWM8C_OFFSET_EVENTCOUNT,CPWM8C_MULTCH_EVENTCOUNT*(Channel),CPWM8C_MASK_REG_EVENTCOUNT,CPWM8C_MASK_VAL_EVENTCOUNT,CPWM8C_MASK_SHIFT_EVENTCOUNT,EventCount);
	}
}

void XCpwm8c_WriteCountMode(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_countmode CountMode)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].CountMode=CountMode;
		XCpwm8c_Out32MaskedShiftedUp(InstancePtr->BaseAddr,CPWM8C_OFFSET_COUNTMODE,CPWM8C_MULTCH_COUNTMODE*(Channel),CPWM8C_MASK_REG_COUNTMODE,CPWM8C_MASK_VAL_COUNTMODE,CPWM8C_MASK_SHIFT_COUNTMODE,(u8)(CountMode));
	}
}

void XCpwm8c_WriteMaskMode(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_maskmode MaskMode)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].MaskMode=MaskMode;
		XCpwm8c_Out32MaskedShiftedUp(InstancePtr->BaseAddr,CPWM8C_OFFSET_MASKMODE,CPWM8C_MULTCH_MASKMODE*(Channel),CPWM8C_MASK_REG_MASKMODE,CPWM8C_MASK_VAL_MASKMODE,CPWM8C_MASK_SHIFT_MASKMODE,(u8)(MaskMode));
	}
}

void XCpwm8c_WriteDTimeOnOff(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_onoff DTimeOnOff)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].DTimeOnOff=DTimeOnOff;
		XCpwm8c_Out32MaskedShifted(InstancePtr->BaseAddr,CPWM8C_OFFSET_DTONOFF,CPWM8C_MULTCH_DTONOFF*(CPWM8C_N_CHANNEL-1-Channel),CPWM8C_MASK_REG_DTONOFF,CPWM8C_MASK_VAL_DTONOFF,CPWM8C_MASK_SHIFT_DTONOFF,(u8)(DTimeOnOff));
	}
}

void XCpwm8c_WriteLogicA(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_logic LogicA)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].LogicA=LogicA;
		XCpwm8c_Out32MaskedShifted(InstancePtr->BaseAddr,CPWM8C_OFFSET_LOGICA,CPWM8C_MULTCH_LOGICA*(CPWM8C_N_CHANNEL-1-Channel),CPWM8C_MASK_REG_LOGICA,CPWM8C_MASK_VAL_LOGICA,CPWM8C_MASK_SHIFT_LOGICA,(u8)(LogicA));
	}
}

void XCpwm8c_WriteLogicB(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_logic LogicB)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].LogicB=LogicB;
		XCpwm8c_Out32MaskedShifted(InstancePtr->BaseAddr,CPWM8C_OFFSET_LOGICB,CPWM8C_MULTCH_LOGICB*(CPWM8C_N_CHANNEL-1-Channel),CPWM8C_MASK_REG_LOGICB,CPWM8C_MASK_VAL_LOGICB,CPWM8C_MASK_SHIFT_LOGICB,(u8)(LogicB));
	}
}

void XCpwm8c_WriteCarrSel(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_carrsel CarrSel)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].CarrSel=CarrSel;
		XCpwm8c_Out32MaskedShifted(InstancePtr->BaseAddr,CPWM8C_OFFSET_CARRSEL,CPWM8C_MULTCH_CARRSEL*(CPWM8C_N_CHANNEL-1-Channel),CPWM8C_MASK_REG_CARRSEL,CPWM8C_MASK_VAL_CARRSEL,CPWM8C_MASK_SHIFT_CARRSEL,(u8)(CarrSel));
	}
}

void XCpwm8c_WriteCarrOnOff(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_onoff CarrOnOff)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	if(Channel < CPWM8C_N_CHANNEL){
		//InstancePtr->ChParam[Channel].CarrOnOff=CarrOnOff;
		XCpwm8c_Out32MaskedShifted(InstancePtr->BaseAddr,CPWM8C_OFFSET_CARRONOFF,CPWM8C_MULTCH_CARRONOFF*(CPWM8C_N_CHANNEL-1-Channel),CPWM8C_MASK_REG_CARRONOFF,CPWM8C_MASK_VAL_CARRONOFF,CPWM8C_MASK_SHIFT_CARRONOFF,(u8)(CarrOnOff));
	}
}

void XCpwm8c_WritePwmOnOff(const XCpwm8c *InstancePtr, XCpwm8c_onoff PwmOnOff)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	//InstancePtr->PwmOnOff=PwmOnOff;
	XCpwm8c_Out32MaskedShifted(InstancePtr->BaseAddr,CPWM8C_OFFSET_PWMONOFF,0,CPWM8C_MASK_REG_PWMONOFF,CPWM8C_MASK_VAL_PWMONOFF,CPWM8C_MASK_SHIFT_PWMONOFF,(u8)(PwmOnOff));

}

void XCpwm8c_WriteIntMatrix(const XCpwm8c *InstancePtr, u8 IntMatrix)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	//InstancePtr->IntMatrix=IntMatrix;
	XCpwm8c_Out32MaskedShifted(InstancePtr->BaseAddr,CPWM8C_OFFSET_INTMATRIX,0,CPWM8C_MASK_REG_INTMATRIX,CPWM8C_MASK_VAL_INTMATRIX,CPWM8C_MASK_SHIFT_INTMATRIX,(u8)(IntMatrix));

}

void XCpwm8c_WriteIntAck(const XCpwm8c *InstancePtr)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	XCpwm8c_Out32MaskedShifted(InstancePtr->BaseAddr,CPWM8C_OFFSET_INTACK,0,CPWM8C_MASK_REG_INTACK,CPWM8C_MASK_VAL_INTACK,CPWM8C_MASK_SHIFT_INTACK,(u8)(1));
	XCpwm8c_Out32MaskedShifted(InstancePtr->BaseAddr,CPWM8C_OFFSET_INTACK,0,CPWM8C_MASK_REG_INTACK,CPWM8C_MASK_VAL_INTACK,CPWM8C_MASK_SHIFT_INTACK,(u8)(0));
}