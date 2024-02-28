/**
 * @file xcpwm8c_sint.h
 * @addtogroup cpwm8c Overview
 * @{
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "xcpwm8c.h"


#ifndef SDT
XCpwm8c_Config *XCpwm8c_LookupConfig(u16 DeviceId)
{
	XCpwm8c_Config *CfgPtr = NULL;
	u32 Index;

	for (Index = 0U; Index < (u32)XPAR_XAXI_CPWM8C_NUM_INSTANCES; Index++) {
		if (XCpwm8c_ConfigTable[Index].DeviceId == DeviceId) {
			CfgPtr = &XCpwm8c_ConfigTable[Index];
			break;
		}
	}

	return CfgPtr;
}
#else
XCpwm8c_Config *XCpwm8c_LookupConfig(UINTPTR BaseAddress)
{
	XCpwm8c_Config *CfgPtr = NULL;
	u32 Index;

	for (Index = (u32)0x0; XCpwm8c_ConfigTable[Index].Name != NULL; Index++) {
		if ((XCpwm8c_ConfigTable[Index].BaseAddr == BaseAddress) || !BaseAddress) {
			CfgPtr = &XCpwm8c_ConfigTable[Index];
			break;
		}
	}

	return CfgPtr;
}
#endif

#ifndef SDT
int XCpwm8c_Initialize(XCpwm8c * InstancePtr, u16 DeviceId)
#else
int XCpwm8c_Initialize(XCpwm8c * InstancePtr, UINTPTR BaseAddress)
#endif
{
	XCpwm8c_Config *ConfigPtr;

	/*
	 * Assert arguments
	 */
	Xil_AssertNonvoid(InstancePtr != NULL);

	/*
	 * Lookup configuration data in the device configuration table.
	 * Use this configuration info down below when initializing this
	 * driver.
	 */
#ifndef SDT
	ConfigPtr = XCpwm8c_LookupConfig(DeviceId);
#else
	ConfigPtr = XCpwm8c_LookupConfig(BaseAddress);
#endif
	if (ConfigPtr == (XCpwm8c_Config *) NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XCpwm8c_CfgInitialize(InstancePtr, ConfigPtr,ConfigPtr->BaseAddr);
}

/** @} */