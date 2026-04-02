/**
 * @file xcpwm8c.h
 * @brief Public API for the CPWM8C 8-channel PWM driver
 *
 * @defgroup xcpwm8c CPWM8C Driver
 * @{
 *
 * @section description Description
 *
 * The CPWM8C is an 8-channel PWM generator peripheral. Each channel can be
 * independently configured with timing, duty cycle, polarity, dead-time,
 * and carrier modulation.
 *
 * This file defines:
 * - Driver structures
 * - Enumerations
 * - Hardware register mapping
 * - Function prototypes
 *
 * The implementation is provided in xcpwm8c.c.
 */

#ifndef XCPWM8C_H 
/** @brief Prevent circular inclusions by using protection macros */
#define XCPWM8C_H 

/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"
#include "xcpwm8c_l.h"

/****************** Definitions ********************/
/** @brief Number of PWM channels (0–7) */
#define CPWM8C_N_CHANNEL 8 

/** @defgroup adresses Hardware adresses
 * 
 * @brief OFFSETs to write PWM sates and values at the right adresses in the hardware 
 * @{
 */
#define CPWM8C_OFFSET_COUNTINIT 16

#define CPWM8C_OFFSET_COMPARE 32

#define CPWM8C_OFFSET_DEADTIMEA 48

#define CPWM8C_OFFSET_DEADTIMEB 56

#define CPWM8C_OFFSET_EVENTCOUNT 64
#define CPWM8C_MASK_REG_EVENTCOUNT 0x00000700
#define CPWM8C_MASK_VAL_EVENTCOUNT 0b00000111
#define CPWM8C_MASK_SHIFT_EVENTCOUNT 8
#define CPWM8C_MULTCH_EVENTCOUNT 3

#define CPWM8C_OFFSET_COUNTMODE 68
#define CPWM8C_MASK_REG_COUNTMODE 0x00030000
#define CPWM8C_MASK_VAL_COUNTMODE 0b11111111
#define CPWM8C_MASK_SHIFT_COUNTMODE 16
#define CPWM8C_MULTCH_COUNTMODE 2

#define CPWM8C_OFFSET_MASKMODE 68
#define CPWM8C_MASK_REG_MASKMODE 0x00000003
#define CPWM8C_MASK_VAL_MASKMODE 0b11111111
#define CPWM8C_MASK_SHIFT_MASKMODE 0
#define CPWM8C_MULTCH_MASKMODE 2

#define CPWM8C_OFFSET_DTONOFF 72
#define CPWM8C_MASK_REG_DTONOFF 0x80000000
#define CPWM8C_MASK_VAL_DTONOFF 0b11111111
#define CPWM8C_MASK_SHIFT_DTONOFF 31
#define CPWM8C_MULTCH_DTONOFF 1

#define CPWM8C_OFFSET_LOGICA 72
#define CPWM8C_MASK_REG_LOGICA 0x00800000
#define CPWM8C_MASK_VAL_LOGICA 0b11111111
#define CPWM8C_MASK_SHIFT_LOGICA 23
#define CPWM8C_MULTCH_LOGICA 1

#define CPWM8C_OFFSET_LOGICB 72
#define CPWM8C_MASK_REG_LOGICB 0x00008000
#define CPWM8C_MASK_VAL_LOGICB 0b11111111
#define CPWM8C_MASK_SHIFT_LOGICB 15
#define CPWM8C_MULTCH_LOGICB 1

#define CPWM8C_OFFSET_CARRSEL 72
#define CPWM8C_MASK_REG_CARRSEL 0x00000080
#define CPWM8C_MASK_VAL_CARRSEL 0b11111111
#define CPWM8C_MASK_SHIFT_CARRSEL 15
#define CPWM8C_MULTCH_CARRSEL 1

#define CPWM8C_OFFSET_CARRONOFF 76
#define CPWM8C_MASK_REG_CARRONOFF 0x00000100
#define CPWM8C_MASK_VAL_CARRONOFF 0b11111111
#define CPWM8C_MASK_SHIFT_CARRONOFF 8
#define CPWM8C_MULTCH_CARRONOFF 1

#define CPWM8C_OFFSET_PWMONOFF 76
#define CPWM8C_MASK_REG_PWMONOFF 0x00000001
#define CPWM8C_MASK_VAL_PWMONOFF 0b11111111
#define CPWM8C_MASK_SHIFT_PWMONOFF 0
#define CPWM8C_MULTCH_PWMONOFF 0

#define CPWM8C_OFFSET_INTMATRIX 64
#define CPWM8C_MASK_REG_INTMATRIX 0x000000FF
#define CPWM8C_MASK_VAL_INTMATRIX 0b11111111
#define CPWM8C_MASK_SHIFT_INTMATRIX 0
#define CPWM8C_MULTCH_INTMATRIX 0

#define CPWM8C_OFFSET_INTACK 76
#define CPWM8C_MASK_REG_INTACK 0x00000200
#define CPWM8C_MASK_VAL_INTACK 0b11111111
#define CPWM8C_MASK_SHIFT_INTACK 9
#define CPWM8C_MULTCH_INTACK 0

#define XCpwm8c_Out32MaskedShifted(Address,Offset,Shift,RegMask,ValMask,ShiftMask,Value) \
*((volatile u32 *)((Address) + (Offset))) = \
(*((volatile u32 *)((Address) + (Offset))) & ~((RegMask) >> Shift)) + (((Value) & (ValMask)) << (ShiftMask-Shift)); 

#define XCpwm8c_Out32MaskedShiftedUp(Address,Offset,Shift,RegMask,ValMask,ShiftMask,Value) \
*((volatile u32 *)((Address) + (Offset))) = \
(*((volatile u32 *)((Address) + (Offset))) & ~((RegMask) << Shift)) + (((Value) & (ValMask)) << (ShiftMask+Shift)); 

/** @} */

/************************** User defined functions/macros ****************************/
/** @defgroup Structures
 * @brief Enumerations and structures that describe the PWM at software level
 * @{
  */
/**
 * @brief This typedef contains configuration information for the device.
 */
typedef struct {
#ifndef SDT
	u16 DeviceId;		/**< Unique ID of device */
#else
	char *Name;
#endif
	UINTPTR BaseAddr;		/**< Register base address */
#ifdef SDT
	u16 IntrId;		/** Bits[11:0] Interrupt-id Bits[15:12]
				 * trigger type and level flags */
	UINTPTR IntrParent; 	/** Bit[0] Interrupt parent type Bit[64/32:1]
				 * Parent base address */
#endif
} XCpwm8c_Config;

/**
 * @brief PWM counter modes
 */
typedef enum {
	NO_COUNT = 0,      /**< Counter disabled */
	COUNT_UP = 1,      /**< Up-counting mode */
	COUNT_DOWN = 2,    /**< Down-counting mode */
	COUNT_UP_DOWN = 3  /**< Up-down (center-aligned) mode */
} XCpwm8c_countmode;

/**
 * @brief Output masking modes
 */
typedef enum {
	NO_MASK = 0,
	MIN_MASK = 1,
	MAX_MASK = 2,
	MINMAX_MASK = 3,
} XCpwm8c_maskmode;

/**
 * @brief Generic ON/OFF control
 */
typedef enum {
	REG_OFF = 0, /**< Disabled */
	REG_ON = 1,  /**< Enabled */
} XCpwm8c_onoff;

/**
 * @brief Output polarity
 */
typedef enum {
	LOGIC_POS = 0, /**< Active high */
	LOGIC_NEG = 1, /**< Active low */
} XCpwm8c_logic;

/**
 * @brief Carrier source selection
 */
typedef enum {
	CARR_MASTER1 = 0, /**< Global/master carrier */
	CARR_LOCAL = 1,   /**< Local carrier */
} XCpwm8c_carrsel;

/**
 * @brief PWM channel configuration structure
 */
typedef struct {
	u16 CountMaxim;              /**< Maximum counter value */
	u16 InitCarr;               /**< Initial counter value */
	u16 Compare;                /**< Compare value (duty cycle) */
	u8 DeadTimeA;               /**< Dead-time for output A */
	u8 DeadTimeB;               /**< Dead-time for output B */
	u8 EventCount;              /**< Event counter */
	XCpwm8c_countmode CountMode; /**< Count mode selection */
	XCpwm8c_maskmode MaskMode; /**< Mask mode selection */
	XCpwm8c_onoff DTimeOnOff; /**< Dead-time ON/OFF */
	XCpwm8c_logic LogicA; /**< Polarity for output A */
	XCpwm8c_logic LogicB; /**< Polarity for output B */
	XCpwm8c_carrsel CarrSel; /**< Carrier selection */
	XCpwm8c_onoff CarrOnOff; /**< Carrier ON/OFF */
} XCpwm8c_ChParam;

/**
 * @brief Main driver instance structure
 */
typedef struct {
	UINTPTR BaseAddr;                          /**< Base address of the peripheral */
	u32 IsReady;                               /**< Initialization status */
	XCpwm8c_ChParam ChParam[CPWM8C_N_CHANNEL]; /**< Per-channel configuration */
	XCpwm8c_onoff PwmOnOff;                   /**< Global PWM enable */
	u8 IntMatrix;                              /**< Interrupt configuration */
} XCpwm8c;


/************************** Variable Definitions *****************************/
/** @brief Define the driver config from extern output */
extern XCpwm8c_Config XCpwm8c_ConfigTable[];
/** @} */
/************************** Function Prototypes ******************************/

/**
 * @defgroup functions Functions
 * @{
 * @brief The following functions write directly in hardware register. No modifications are made to the GPU memory in order to speed up the program.
 */

#ifndef SDT
int XCpwm8c_Initialize(XCpwm8c *InstancePtr, u16 DeviceId);
XCpwm8c_Config *XCpwm8c_LookupConfig(u16 DeviceId);
#else
int XCpwm8c_Initialize(XCpwm8c *InstancePtr, UINTPTR BaseAddress);
XCpwm8c_Config *XCpwm8c_LookupConfig(UINTPTR BaseAddress);
#endif



/**
 * @brief Initialize the PWM driver instance
 *
 * This function initializes the driver structure and resets
 * the hardware registers to default values (calling XCpwm8c_WriteFullStatus).
 *
 * @param InstancePtr Pointer to the driver instance
 * @param Config Pointer to the configuration structure
 * @param EffectiveAddr Base address of the device
 * @return XST_SUCCESS if successful
 */
int XCpwm8c_CfgInitialize(XCpwm8c *InstancePtr,
                         const XCpwm8c_Config *Config,
                         UINTPTR EffectiveAddr);

/**
 * @brief Reset all hardware registers to default values
 *
 * @param InstancePtr Pointer to the driver instance
 */
void XCpwm8c_WriteFullStatus(const XCpwm8c *InstancePtr);

/* ===== Channel configuration ===== */

/**
 * @brief Set maximum counter value 
 */
void XCpwm8c_WriteCountMax(const XCpwm8c *InstancePtr,
                           u16 Channel,
                           u16 CountMaxim);

/**
 * @brief Set initial counter value 
 */
void XCpwm8c_WriteCountInit(const XCpwm8c *InstancePtr,
                            u16 Channel,
                            u16 CountInit);

/**
 * @brief Set compare value (duty cycle) 
 */
void XCpwm8c_WriteCompare(const XCpwm8c *InstancePtr,
                          u16 Channel,
                          u16 Compare);

/**
 * @brief Set dead-time for output A 
 */
void XCpwm8c_WriteDeadTimeA(const XCpwm8c *InstancePtr,
                            u16 Channel,
                            u8 DeadTime);

/**
 * @brief Set dead-time for output B 
 */
void XCpwm8c_WriteDeadTimeB(const XCpwm8c *InstancePtr,
                            u16 Channel,
                            u8 DeadTime);

/**
 * @brief Set event count
 */
void XCpwm8c_WriteEventCount(const XCpwm8c *InstancePtr,
                             u16 Channel,
                             u8 EventCount);

/**
 * @brief Set counter mode
 */
void XCpwm8c_WriteCountMode(const XCpwm8c *InstancePtr,
                            u16 Channel,
                            XCpwm8c_countmode CountMode);

/**
 * @brief Set masking mode
 */
void XCpwm8c_WriteMaskMode(const XCpwm8c *InstancePtr,
                           u16 Channel,
                           XCpwm8c_maskmode MaskMode);

/**
 * @brief Enable or disable dead-time insertion
 */
void XCpwm8c_WriteDTimeOnOff(const XCpwm8c *InstancePtr,
                             u16 Channel,
                             XCpwm8c_onoff DTimeOnOff);

/**
 * @brief Set output logic for channel A (either low or high)
 */
void XCpwm8c_WriteLogicA(const XCpwm8c *InstancePtr,
                         u16 Channel,
                         XCpwm8c_logic LogicA);

/**
 * @brief Set output logic for channel B (either low or high)
 */
void XCpwm8c_WriteLogicB(const XCpwm8c *InstancePtr,
                         u16 Channel,
                         XCpwm8c_logic LogicB);

/**
 * @brief Select carrier source
 */
void XCpwm8c_WriteCarrSel(const XCpwm8c *InstancePtr,
                          u16 Channel,
                          XCpwm8c_carrsel CarrSel);

/**
 * @brief Enable or disable carrier 
 */
void XCpwm8c_WriteCarrOnOff(const XCpwm8c *InstancePtr,
                            u16 Channel,
                            XCpwm8c_onoff CarrOnOff);

/* ===== Global control ===== */

/**
 * @brief Enable or disable PWM globally
 */
void XCpwm8c_WritePwmOnOff(const XCpwm8c *InstancePtr,
                           XCpwm8c_onoff PwmOnOff);

/**
 * @brief Set interrupt matrix
 */
void XCpwm8c_WriteIntMatrix(const XCpwm8c *InstancePtr,
                            u8 IntMatrix);

/**
 * @brief Acknowledge interrupt
 */
void XCpwm8c_WriteIntAck(const XCpwm8c *InstancePtr);
/** @} */
#endif // XCPWM8C_H
/** @} */