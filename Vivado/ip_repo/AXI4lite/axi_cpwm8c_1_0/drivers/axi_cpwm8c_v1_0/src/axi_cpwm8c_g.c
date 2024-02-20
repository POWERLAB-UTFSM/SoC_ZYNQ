/***************************** Include Files *********************************/

#include "axi_cpwm8c.h"
#include "xparameters.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/


/************************** Variable Prototypes ******************************/

/**
 * This table contains configuration information for each GPIO device
 * in the system.
 */
AXIcpwm8c_Config AXIcpwm8c_ConfigTable[] = {
	{
#ifdef XPAR_AXICPWM8C_NUM_INSTANCES
	 XPAR_AXICPWM8C_0_DEVICE_ID,
	 XPAR_AXICPWM8C_0_BASEADDR,
	 XPAR_AXICPWM8C_0_INTERRUPT_PRESENT,
	 XPAR_AXICPWM8C_0_IS_DUAL
#endif
	}
};
/** @} */
