/**
 * @file xcpwm8c.h
 * @addtogroup xcpwm8c Overview
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef XCPWM8C_H /* prevent circular inclusions */
#define XCPWM8C_H /* by using protection macros */

/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"
#include "xcpwm8c_l.h"

/****************** Definitions ********************/
#define CPWM8C_N_CHANNEL 8
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


/************************** User defined functions/macros ****************************/

/**
 * This typedef contains configuration information for the device.
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

typedef enum
{
	NO_COUNT = 0,
	COUNT_UP = 1,
	COUNT_DOWN = 2,
	COUNT_UP_DOWN = 3,
} XCpwm8c_countmode;

typedef enum
{
	NO_MASK = 0,
	MIN_MASK = 1,
	MAX_MASK = 2,
	MINMAX_MASK = 3,
} XCpwm8c_maskmode;

typedef enum
{
	REG_OFF = 0,
	REG_ON = 1,
} XCpwm8c_onoff;

typedef enum
{
	LOGIC_POS = 0,
	LOGIC_NEG = 1,
} XCpwm8c_logic;

typedef enum
{
	CARR_MASTER1 = 0,
	CARR_LOCAL = 1,
} XCpwm8c_carrsel;

typedef struct {
	u16 CountMaxim;
	u16 InitCarr;
	u16 Compare;
	u8 DeadTimeA;
	u8 DeadTimeB;
	u8 EventCount;
	XCpwm8c_countmode CountMode;
	XCpwm8c_maskmode MaskMode;
	XCpwm8c_onoff DTimeOnOff;
	XCpwm8c_logic LogicA;
	XCpwm8c_logic LogicB;
	XCpwm8c_carrsel CarrSel;
	XCpwm8c_onoff CarrOnOff;
} XCpwm8c_ChParam;

typedef struct {
	UINTPTR BaseAddr;	/**< Device base address */
	u32 IsReady;			/**< Device is initialized and ready */
	XCpwm8c_ChParam ChParam[CPWM8C_N_CHANNEL]; /**Channel parameter */
	XCpwm8c_onoff PwmOnOff;
	u8 IntMatrix;
} XCpwm8c;


/************************** Variable Definitions *****************************/
extern XCpwm8c_Config XCpwm8c_ConfigTable[];

/************************** Function Prototypes ******************************/

#ifndef SDT
int XCpwm8c_Initialize(XCpwm8c *InstancePtr, u16 DeviceId);
XCpwm8c_Config *XCpwm8c_LookupConfig(u16 DeviceId);
#else
int XCpwm8c_Initialize(XCpwm8c *InstancePtr, UINTPTR BaseAddress);
XCpwm8c_Config *XCpwm8c_LookupConfig(UINTPTR BaseAddress);
#endif

int XCpwm8c_CfgInitialize(XCpwm8c * InstancePtr,const  XCpwm8c_Config * Config, UINTPTR EffectiveAddr);

void XCpwm8c_WriteFullStatus(const XCpwm8c *InstancePtr);

void XCpwm8c_WriteCountMax(const XCpwm8c *InstancePtr, u16 Channel, u16 CountMaxim);

void XCpwm8c_WriteCompare(const XCpwm8c *InstancePtr, u16 Channel, u16 Compare);

void XCpwm8c_WriteDeadTimeA(const XCpwm8c *InstancePtr, u16 Channel, u8 DeadTime);

void XCpwm8c_WriteDeadTimeB(const XCpwm8c *InstancePtr, u16 Channel, u8 DeadTime);

void XCpwm8c_WriteEventCount(const XCpwm8c *InstancePtr, u16 Channel, u8 EventCount);

void XCpwm8c_WriteCountMode(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_countmode CountMode);

void XCpwm8c_WriteMaskMode(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_maskmode MaskMode);

void XCpwm8c_WriteDTimeOnOff(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_onoff DTimeOnOff);

void XCpwm8c_WriteLogicA(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_logic LogicA);

void XCpwm8c_WriteLogicB(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_logic LogicB);

void XCpwm8c_WriteCarrSel(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_carrsel CarrSel);

void XCpwm8c_WriteCarrOnOff(const XCpwm8c *InstancePtr, u16 Channel, XCpwm8c_onoff CarrOnOff);

void XCpwm8c_WritePwmOnOff(const XCpwm8c *InstancePtr, XCpwm8c_onoff PwmOnOff);

void XCpwm8c_WriteIntMatrix(const XCpwm8c *InstancePtr, u8 IntMatrix);

void XCpwm8c_WriteIntAck(const XCpwm8c *InstancePtr);

#endif // XCPWM8C_H
