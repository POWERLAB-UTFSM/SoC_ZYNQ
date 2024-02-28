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

	return (XCpwm8c_Config *)CfgPtr;
}
#else
XCpwm8c_Config *XCpwm8c_LookupConfig(u32 BaseAddress)
{
	XCpwm8c_Config *CfgPtr = NULL;
	u32 Index;

	for (Index = (u32)0x0; XCpwm8c_ConfigTable[Index].Name != NULL; Index++) {
		if ((XCpwm8c_ConfigTable[Index].BaseAddr == BaseAddress) || !BaseAddress) {
			CfgPtr = &XCpwm8c_ConfigTable[Index];
			break;
		}
	}

	return (XCpwm8c_Config *)CfgPtr;
}
#endif

/** @} */