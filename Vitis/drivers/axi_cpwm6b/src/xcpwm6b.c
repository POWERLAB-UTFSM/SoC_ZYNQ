#include "xcpwm6b.h"

/*************** INTERNAL MACRO ***************/
#define WRITE_FIELD(BASE, OFFSET, MASK, SHIFT, VAL) \
    do { \
        u32 reg = Xil_In32((BASE) + (OFFSET)); \
        reg &= ~(MASK); \
        reg |= (((u32)(VAL) << (SHIFT)) & (MASK)); \
        Xil_Out32((BASE) + (OFFSET), reg); \
    } while(0)

/*************** INIT ***************/
int XCpwm6b_CfgInitialize(XCpwm6b *InstancePtr,const XCpwm6b_Config *Config, UINTPTR EffectiveAddr)
{
	/* Assert arguments */
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(Config != NULL);
	Xil_AssertNonvoid(EffectiveAddr != (u32)0);

    InstancePtr->BaseAddr = EffectiveAddr;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    /* Reset software mirror */
    InstancePtr->carrier_max = 0;
    InstancePtr->carrier_init = 0;

    InstancePtr->compare1 = 0;
    InstancePtr->compare2 = 0;

    InstancePtr->count_mode = NO_COUNT;
    InstancePtr->sync_mode = NO_EVENT;
    InstancePtr->event_count = 0;
    InstancePtr->clkdiv_carr = 0;

    InstancePtr->en_pwm = REG_OFF;
    InstancePtr->mask_on = REG_OFF;
    InstancePtr->ce = REG_OFF;

    InstancePtr->sig_pwm_1 = LOGIC_POS;
    InstancePtr->sig_pwm_2 = LOGIC_POS;

    InstancePtr->deadtime = 0;
    InstancePtr->dt_onoff = REG_OFF;
    InstancePtr->clkdiv_dtime = 0;

    InstancePtr->dt_logic_1a = LOGIC_POS;
    InstancePtr->dt_logic_1b = LOGIC_POS;
    InstancePtr->dt_logic_2a = LOGIC_POS;
    InstancePtr->dt_logic_2b = LOGIC_POS;

	XCpwm6b_WriteFullStatus(InstancePtr);
    return XST_SUCCESS;
}


void XCpwm6b_WriteFullStatus(XCpwm6b *InstancePtr)
{
    /* -------- CARRIER -------- */
    XCpwm6b_WriteCarrierMax(InstancePtr, 0);
    XCpwm6b_WriteCarrierInit(InstancePtr, 0);

    /* -------- COMPARE -------- */
    XCpwm6b_WriteCompare1(InstancePtr, 0);
    XCpwm6b_WriteCompare2(InstancePtr, 0);

    /* -------- MODE -------- */
    XCpwm6b_WriteCountMode(InstancePtr, NO_COUNT);
    XCpwm6b_WriteSyncMode(InstancePtr, NO_EVENT);
    XCpwm6b_WriteEventCount(InstancePtr, 0);
    XCpwm6b_WriteClkDivCarr(InstancePtr, 0);

    XCpwm6b_WritePwmOnOff(InstancePtr, REG_OFF);
    XCpwm6b_WriteMaskOn(InstancePtr, REG_OFF);
    XCpwm6b_WriteCE(InstancePtr, REG_OFF);

    /* -------- LOGIC -------- */
    XCpwm6b_WriteLogicA(InstancePtr, LOGIC_POS);
    XCpwm6b_WriteLogicB(InstancePtr, LOGIC_POS);

    /* -------- DEADTIME -------- */
    XCpwm6b_WriteDeadTime(InstancePtr, 0);
    XCpwm6b_WriteDeadTimeOnOff(InstancePtr, REG_OFF);
    XCpwm6b_WriteClkDivDTime(InstancePtr, 0);

    /* -------- DEADTIME LOGIC -------- */
    XCpwm6b_WriteDtLogic1A(InstancePtr, LOGIC_POS);
    XCpwm6b_WriteDtLogic1B(InstancePtr, LOGIC_POS);
    XCpwm6b_WriteDtLogic2A(InstancePtr, LOGIC_POS);
    XCpwm6b_WriteDtLogic2B(InstancePtr, LOGIC_POS);
}
```


/*************** CARRIER ***************/
void XCpwm6b_WriteCarrierMax(XCpwm6b *InstancePtr, u16 carrier_max)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    u32 reg = Xil_In32(InstancePtr->BaseAddr + XCPWM6B_OFFSET_CARRIER);
    reg &= 0x0000FFFF;
    reg |= ((u32)carrier_max << 16);
    Xil_Out32(InstancePtr->BaseAddr + XCPWM6B_OFFSET_CARRIER, reg);

    InstancePtr->carrier_max = carrier_max;
}

void XCpwm6b_WriteCarrierInit(XCpwm6b *InstancePtr, u16 carrier_init)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    u32 reg = Xil_In32(InstancePtr->BaseAddr + XCPWM6B_OFFSET_CARRIER);
    reg &= 0xFFFF0000;
    reg |= carrier_init;
    Xil_Out32(InstancePtr->BaseAddr + XCPWM6B_OFFSET_CARRIER, reg);

    InstancePtr->carrier_init = carrier_init;
}

/*************** MODE ***************/
void XCpwm6b_WriteCountMode(XCpwm6b *InstancePtr, XCpwm6b_countmode count_mode)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_MODE,
                XCPWM6B_MASK_COUNT_MODE,
                XCPWM6B_SHIFT_COUNT_MODE, count_mode);

    InstancePtr->count_mode = count_mode;
}

void XCpwm6b_WriteSyncMode(XCpwm6b *InstancePtr, XCpwm6b_syncmode sync_mode)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_MODE,
                XCPWM6B_MASK_SYNC_MODE,
                XCPWM6B_SHIFT_SYNC_MODE, sync_mode);

    InstancePtr->sync_mode = sync_mode;
}

void XCpwm6b_WriteEventCount(XCpwm6b *InstancePtr, u8 event_count)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_MODE,
                XCPWM6B_MASK_EVENT_COUNT,
                XCPWM6B_SHIFT_EVENT_COUNT, event_count);

    InstancePtr->event_count = event_count;
}

void XCpwm6b_WriteClkDivCarr(XCpwm6b *InstancePtr, u8 clkdiv_carr)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_MODE,
                XCPWM6B_MASK_CLKDIV_CARR,
                XCPWM6B_SHIFT_CLKDIV_CARR, clkdiv_carr);

    InstancePtr->clkdiv_carr = clkdiv_carr;
}

void XCpwm6b_WritePwmOnOff(XCpwm6b *InstancePtr, XCpwm6b_onoff en_pwm)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_MODE,
                XCPWM6B_MASK_EN_PWM,
                XCPWM6B_SHIFT_EN_PWM, en_pwm);

    InstancePtr->en_pwm = en_pwm;
}

void XCpwm6b_WriteMaskOn(XCpwm6b *InstancePtr, XCpwm6b_onoff mask_on)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_MODE,
                XCPWM6B_MASK_MASK_ON,
                XCPWM6B_SHIFT_MASK_ON, mask_on);

    InstancePtr->mask_on = mask_on;
}

void XCpwm6b_WriteCE(XCpwm6b *InstancePtr, XCpwm6b_onoff ce)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_MODE,
                XCPWM6B_MASK_CE,
                XCPWM6B_SHIFT_CE, ce);

    InstancePtr->ce = ce;
}

/*************** LOGIC ***************/
void XCpwm6b_WriteLogicA(XCpwm6b *InstancePtr, XCpwm6b_onoff sig_pwm_1)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_MODE,
                XCPWM6B_MASK_SIG_PWM1,
                XCPWM6B_SHIFT_SIG_PWM1, sig_pwm_1);

    InstancePtr->sig_pwm_1 = sig_pwm_1;
}

void XCpwm6b_WriteLogicB(XCpwm6b *InstancePtr, XCpwm6b_onoff sig_pwm_2)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_MODE,
                XCPWM6B_MASK_SIG_PWM2,
                XCPWM6B_SHIFT_SIG_PWM2, sig_pwm_2);

    InstancePtr->sig_pwm_2 = sig_pwm_2;
}

/*************** COMPARE ***************/
void XCpwm6b_WriteCompare1(XCpwm6b *InstancePtr, u16 compare1)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    u32 reg = Xil_In32(InstancePtr->BaseAddr + XCPWM6B_OFFSET_COMPARE);
    reg &= 0xFFFF0000;
    reg |= compare1;
    Xil_Out32(InstancePtr->BaseAddr + XCPWM6B_OFFSET_COMPARE, reg);

    InstancePtr->compare1 = compare1;
}

void XCpwm6b_WriteCompare2(XCpwm6b *InstancePtr, u16 compare2)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    u32 reg = Xil_In32(InstancePtr->BaseAddr + XCPWM6B_OFFSET_COMPARE);
    reg &= 0x0000FFFF;
    reg |= ((u32)compare2 << 16);
    Xil_Out32(InstancePtr->BaseAddr + XCPWM6B_OFFSET_COMPARE, reg);

    InstancePtr->compare2 = compare2;
}

/*************** DEADTIME ***************/
void XCpwm6b_WriteDeadTime(XCpwm6b *InstancePtr, u8 deadtime)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_DEADTIME,
                XCPWM6B_MASK_DEADTIME,
                XCPWM6B_SHIFT_DEADTIME, deadtime);

    InstancePtr->deadtime = deadtime;
}

void XCpwm6b_WriteDeadTimeOnOff(XCpwm6b *InstancePtr, XCpwm6b_onoff dt_onoff)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_DEADTIME,
                XCPWM6B_MASK_DTONOFF,
                XCPWM6B_SHIFT_DTONOFF, dt_onoff);

    InstancePtr->dt_onoff = dt_onoff;
}

void XCpwm6b_WriteClkDivDTime(XCpwm6b *InstancePtr, u8 clkdiv_dtime)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_DEADTIME,
                XCPWM6B_MASK_CLKDIV_DTIME,
                XCPWM6B_SHIFT_CLKDIV_DTIME, clkdiv_dtime);

    InstancePtr->clkdiv_dtime = clkdiv_dtime;
}

/*************** DEADTIME LOGIC ***************/
void XCpwm6b_WriteDtLogic1A(XCpwm6b *InstancePtr, XCpwm6b_onoff dt_logic_1a)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_DEADTIME,
                XCPWM6B_MASK_DT_LOGIC_1A,
                XCPWM6B_SHIFT_DT_LOGIC_1A, dt_logic_1a);

    InstancePtr->dt_logic_1a = dt_logic_1a;
}

void XCpwm6b_WriteDtLogic1B(XCpwm6b *InstancePtr, XCpwm6b_onoff dt_logic_1b)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_DEADTIME,
                XCPWM6B_MASK_DT_LOGIC_1B,
                XCPWM6B_SHIFT_DT_LOGIC_1B, dt_logic_1b);

    InstancePtr->dt_logic_1b = dt_logic_1b;
}

void XCpwm6b_WriteDtLogic2A(XCpwm6b *InstancePtr, XCpwm6b_onoff dt_logic_2a)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_DEADTIME,
                XCPWM6B_MASK_DT_LOGIC_2A,
                XCPWM6B_SHIFT_DT_LOGIC_2A, dt_logic_2a);

    InstancePtr->dt_logic_2a = dt_logic_2a;
}

void XCpwm6b_WriteDtLogic2B(XCpwm6b *InstancePtr, XCpwm6b_onoff dt_logic_2b)
{
	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
    
    WRITE_FIELD(InstancePtr->BaseAddr, XCPWM6B_OFFSET_DEADTIME,
                XCPWM6B_MASK_DT_LOGIC_2B,
                XCPWM6B_SHIFT_DT_LOGIC_2B, dt_logic_2b);

    InstancePtr->dt_logic_2b = dt_logic_2b;
}
```
