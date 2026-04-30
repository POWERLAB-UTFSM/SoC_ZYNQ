#include "hdfcpwm.h"

/*************** INSTANCES ***************/
XCpwm6b xcpwm6b_my_inst;
XScuGic xscugic_my_inst;

/*************** INTERRUPT HANDLER ***************/
void CPWM6B_InterruptHandler(void *CallbackRef)
{
    XCpwm6b *InstancePtr = (XCpwm6b *)CallbackRef;

    /* 👉 ici tu traites ton event */
    /* ex: toggle flag, lire statut, etc */

    /* ⚠️ si ton IP a un registre d’ACK → à appeler ici */
}

/*************** GIC INIT ***************/
int GIC_Init(XScuGic *GicInstancePtr)
{
    int status;
    XScuGic_Config *Config;

    Config = XScuGic_LookupConfig(MY_SCUGIC_DEVICE_ID);
    if (Config == NULL)
        return XST_FAILURE;

    status = XScuGic_CfgInitialize(GicInstancePtr, Config, Config->CpuBaseAddress);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    /* connecter interruption */
    status = XScuGic_Connect(GicInstancePtr,
                            MY_CPWM6B_INTR_ID,
                            (Xil_InterruptHandler)CPWM6B_InterruptHandler,
                            (void *)&xcpwm6b_my_inst);

    if (status != XST_SUCCESS)
        return XST_FAILURE;

    XScuGic_Enable(GicInstancePtr, MY_CPWM6B_INTR_ID);

    /* init exceptions ARM */
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
                                 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
                                 GicInstancePtr);
    Xil_ExceptionEnable();

    return XST_SUCCESS;
}

/*************** CPWM INIT ***************/
int XCpwm6b_My_Init(XCpwm6b *InstancePtr, UINTPTR BaseAddr)
{
    int status;
    XCpwm6b_Config *CfgPtr;

#ifndef SDT
    CfgPtr = XCpwm6b_LookupConfig(BaseAddr);
#else
    CfgPtr = XCpwm6b_LookupConfig(BaseAddr);
#endif

    if (CfgPtr == NULL)
        return XST_FAILURE;

    status = XCpwm6b_CfgInitialize(InstancePtr, CfgPtr, BaseAddr);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    /* -------- CONFIG -------- */
    XCpwm6b_WriteCarrierMax(InstancePtr, 2000);
    XCpwm6b_WriteCarrierInit(InstancePtr, 0);

    XCpwm6b_WriteCompare1(InstancePtr, 1000);
    XCpwm6b_WriteCompare2(InstancePtr, 1000);

    XCpwm6b_WriteCountMode(InstancePtr, COUNT_UP_DOWN);
    XCpwm6b_WriteSyncMode(InstancePtr, MIN_EVENT);
    XCpwm6b_WriteEventCount(InstancePtr, 0);
    XCpwm6b_WriteClkDivCarr(InstancePtr, 0);

    XCpwm6b_WriteMaskOn(InstancePtr, REG_OFF);
    XCpwm6b_WriteCE(InstancePtr, REG_ON);

    XCpwm6b_WriteLogicA(InstancePtr, LOGIC_NEG);
    XCpwm6b_WriteLogicB(InstancePtr, LOGIC_POS);

    XCpwm6b_WriteDeadTime(InstancePtr, 0);
    XCpwm6b_WriteDeadTimeOnOff(InstancePtr, REG_OFF);
    XCpwm6b_WriteClkDivDTime(InstancePtr, 0);

    XCpwm6b_WriteDtLogic1A(InstancePtr, LOGIC_NEG);
    XCpwm6b_WriteDtLogic1B(InstancePtr, LOGIC_NEG);
    XCpwm6b_WriteDtLogic2A(InstancePtr, LOGIC_POS);
    XCpwm6b_WriteDtLogic2B(InstancePtr, LOGIC_POS);

    /* ⚠️ activer PWM EN DERNIER */
    XCpwm6b_WritePwmOnOff(InstancePtr, REG_ON);

    return XST_SUCCESS;
}

/*************** GLOBAL INIT ***************/
int _HW_My_Init(void)
{
    int status;

    /* init PWM */
    status = XCpwm6b_My_Init(&xcpwm6b_my_inst, MY_CPWM6B_0_BASEADDR);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    /* init interruptions */
    status = GIC_Init(&xscugic_my_inst);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    return XST_SUCCESS;
}
