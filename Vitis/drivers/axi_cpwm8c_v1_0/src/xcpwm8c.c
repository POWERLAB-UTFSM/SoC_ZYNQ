

/***************************** Include Files *******************************/
#include "xcpwm8c.h"
#include "xstatus.h"



/************************** Function Definitions ***************************/

int XCpwm8c_CfgInitialize(XCpwm8c * InstancePtr, XCpwm8c_Config * Config, UINTPTR EffectiveAddr)
{
	/* Assert arguments */
	Xil_AssertNonvoid(InstancePtr != NULL);

	/* Set some default values. */
	InstancePtr->BaseAddr = EffectiveAddr;

	/*
	 * Indicate the instance is now ready to use, initialized without error
	 */
	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;
	return (XST_SUCCESS);
}
