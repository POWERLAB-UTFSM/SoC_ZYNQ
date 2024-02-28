/**
 * @file xcpwm8c.h
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

/****************** read/write register ********************/
#define HWREG(x)                                                          \
            (*((volatile u32 *)(x)))

#define AXI_CPWM8C_S_AXI_SLV_REG0_OFFSET 0
#define AXI_CPWM8C_S_AXI_SLV_REG1_OFFSET 4
#define AXI_CPWM8C_S_AXI_SLV_REG2_OFFSET 8
#define AXI_CPWM8C_S_AXI_SLV_REG3_OFFSET 12
#define AXI_CPWM8C_S_AXI_SLV_REG4_OFFSET 16
#define AXI_CPWM8C_S_AXI_SLV_REG5_OFFSET 20
#define AXI_CPWM8C_S_AXI_SLV_REG6_OFFSET 24
#define AXI_CPWM8C_S_AXI_SLV_REG7_OFFSET 28
#define AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET 32
#define AXI_CPWM8C_S_AXI_SLV_REG9_OFFSET 36
#define AXI_CPWM8C_S_AXI_SLV_REG10_OFFSET 40
#define AXI_CPWM8C_S_AXI_SLV_REG11_OFFSET 44
#define AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET 48
#define AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET 52
#define AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET 56
#define AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET 60
#define AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET 64
#define AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET 68
#define AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET 72
#define AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET 76

/************************** User defined functions/macros ****************************/
/**/
/**/
/**
 * This typedef contains configuration information for the device.
 */
/**
 * This typedef contains configuration information for a device.
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

typedef struct {
	UINTPTR BaseAddr;	/**< Device base address */
	u32 IsReady;			/**< Device is initialized and ready */
} XCpwm8c;


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

int XCpwm8c_CfgInitialize(XCpwm8c * InstancePtr, XCpwm8c_Config * Config, UINTPTR EffectiveAddr);


static INLINE void XCpwm8c_mWrite_Period_1(UINTPTR BaseAddress, u16 Value){
	//HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG0_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG0_OFFSET) & 0xFFFF0000) + (Value);
	Xil_Out16((BaseAddress) + (0), (u16)(Value));
	//XCpwm8c_mWriteReg16(BaseAddress,0,Value);
}
static INLINE void XCpwm8c_mWrite_Period_2(UINTPTR BaseAddress, u16 Value){
	//HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG0_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG0_OFFSET) & 0x0000FFFF) + (Value << 16);
	Xil_Out16((BaseAddress) + (2), (u16)(Value));
	//XCpwm8c_mWriteReg16(BaseAddress,2,Value);
}
static INLINE void XCpwm8c_mWrite_Period_3(UINTPTR BaseAddress, u16 Value){
	//HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG1_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG1_OFFSET) & 0xFFFF0000) + (Value);
	Xil_Out16((BaseAddress) + (4), (u16)(Value));
}
static INLINE void XCpwm8c_mWrite_Period_4(UINTPTR BaseAddress, u16 Value){
	//HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG1_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG1_OFFSET) & 0x0000FFFF) + (Value << 16);
	Xil_Out16((BaseAddress) + (6), (u16)(Value));
}
static INLINE void XCpwm8c_mWrite_Period_5(UINTPTR BaseAddress, u16 Value){
	//HWREG(BaseAddress + XCpwm8c_S_AXI_SLV_REG2_OFFSET) = (HWREG(BaseAddress + XCpwm8c_S_AXI_SLV_REG2_OFFSET) & 0xFFFF0000) + (Value);
	Xil_Out16((BaseAddress) + (8), (u16)(Value));
}
static INLINE void XCpwm8c_mWrite_Period_6(UINTPTR BaseAddress, u16 Value){
	//HWREG(BaseAddress + XCpwm8c_S_AXI_SLV_REG2_OFFSET) = (HWREG(BaseAddress + XCpwm8c_S_AXI_SLV_REG2_OFFSET) & 0x0000FFFF) + (Value << 16);
	Xil_Out16((BaseAddress) + (10), (u16)(Value));
}
static INLINE void XCpwm8c_mWrite_Period_7(UINTPTR BaseAddress, u16 Value){
	//HWREG(BaseAddress + XCpwm8c_S_AXI_SLV_REG3_OFFSET) = (HWREG(BaseAddress + XCpwm8c_S_AXI_SLV_REG3_OFFSET) & 0xFFFF0000) + (Value);
	Xil_Out16((BaseAddress) + (12), (u16)(Value));
}
static INLINE void XCpwm8c_mWrite_Period_8(UINTPTR BaseAddress, u16 Value){
	//HWREG(BaseAddress + XCpwm8c_S_AXI_SLV_REG3_OFFSET) = (HWREG(BaseAddress + XCpwm8c_S_AXI_SLV_REG3_OFFSET) & 0x0000FFFF) + (Value << 16);
	Xil_Out16((BaseAddress) + (14), (u16)(Value));
}

static INLINE void XCpwm8c_mWrite_InitCarrier_1(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG4_OFFSET) & 0xFFFF0000) + (Value);
}
static INLINE void XCpwm8c_mWrite_InitCarrier_2(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG4_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static INLINE void XCpwm8c_mWrite_InitCarrier_3(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG5_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG5_OFFSET) & 0xFFFF0000) + (Value);
}
static INLINE void XCpwm8c_mWrite_InitCarrier_4(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG5_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG5_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static INLINE void XCpwm8c_mWrite_InitCarrier_5(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG6_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG6_OFFSET) & 0xFFFF0000) + (Value);
}
static INLINE void XCpwm8c_mWrite_InitCarrier_6(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG6_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG6_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static INLINE void XCpwm8c_mWrite_InitCarrier_7(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG7_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG7_OFFSET) & 0xFFFF0000) + (Value);
}
static INLINE void XCpwm8c_mWrite_InitCarrier_8(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG7_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG7_OFFSET) & 0x0000FFFF) + (Value << 16);
}

static INLINE void XCpwm8c_mWrite_Compare_1(UINTPTR BaseAddress, u16 Value){
	//HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET) & 0xFFFF0000) + (Value);
	Xil_Out16((BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET) + (0), (u16)(Value));
}
static INLINE void XCpwm8c_mWrite_Compare_2(UINTPTR BaseAddress, u16 Value){
	//HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET) & 0x0000FFFF) + (Value << 16);
	Xil_Out16((BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET) + (2), (u16)(Value));
}
static INLINE void XCpwm8c_mWrite_Compare_3(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG9_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG9_OFFSET) & 0xFFFF0000) + (Value);
}
static INLINE void XCpwm8c_mWrite_Compare_4(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG9_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG9_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static INLINE void XCpwm8c_mWrite_Compare_5(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG10_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG10_OFFSET) & 0xFFFF0000) + (Value);
}
static INLINE void XCpwm8c_mWrite_Compare_6(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG10_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG10_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static INLINE void XCpwm8c_mWrite_Compare_7(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG11_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG11_OFFSET) & 0xFFFF0000) + (Value);
}
static INLINE void XCpwm8c_mWrite_Compare_8(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG11_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG11_OFFSET) & 0x0000FFFF) + (Value << 16);
}

static INLINE void XCpwm8c_mWrite_DeadTimeA_1(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) & 0xFFFFFF00) + (Value);
}
static INLINE void XCpwm8c_mWrite_DeadTimeA_2(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) & 0xFFFF00FF) + (Value << 8);
}
static INLINE void XCpwm8c_mWrite_DeadTimeA_3(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) & 0xFF00FFFF) + (Value << 16);
}
static INLINE void XCpwm8c_mWrite_DeadTimeA_4(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) & 0x00FFFFFF) + (Value << 24);
}
static INLINE void XCpwm8c_mWrite_DeadTimeA_5(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) & 0xFFFFFF00) + (Value);
}
static INLINE void XCpwm8c_mWrite_DeadTimeA_6(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) & 0xFFFF00FF) + (Value << 8);
}
static INLINE void XCpwm8c_mWrite_DeadTimeA_7(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) & 0xFF00FFFF) + (Value << 16);
}
static INLINE void XCpwm8c_mWrite_DeadTimeA_8(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) & 0x00FFFFFF) + (Value << 24);
}

static INLINE void XCpwm8c_mWrite_DeadTimeB_1(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) & 0xFFFFFF00) + (Value);
}
static INLINE void XCpwm8c_mWrite_DeadTimeB_2(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) & 0xFFFF00FF) + (Value << 8);
}
static INLINE void XCpwm8c_mWrite_DeadTimeB_3(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) & 0xFF00FFFF) + (Value << 16);
}
static INLINE void XCpwm8c_mWrite_DeadTimeB_4(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) & 0x00FFFFFF) + (Value << 24);
}
static INLINE void XCpwm8c_mWrite_DeadTimeB_5(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) & 0xFFFFFF00) + (Value);
}
static INLINE void XCpwm8c_mWrite_DeadTimeB_6(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) & 0xFFFF00FF) + (Value << 8);
}
static INLINE void XCpwm8c_mWrite_DeadTimeB_7(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) & 0xFF00FFFF) + (Value << 16);
}
static INLINE void XCpwm8c_mWrite_DeadTimeB_8(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) & 0x00FFFFFF) + (Value << 24);
}

static INLINE void XCpwm8c_mWrite_EventCount_8(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b00011111111111111111111111111111) + ((Value & 0b00000111) << 29);
}
static INLINE void XCpwm8c_mWrite_EventCount_7(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11100011111111111111111111111111) + ((Value & 0b00000111) << 26);
}
static INLINE void XCpwm8c_mWrite_EventCount_6(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111100011111111111111111111111) + ((Value & 0b00000111) << 23);
}
static INLINE void XCpwm8c_mWrite_EventCount_5(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111100011111111111111111111) + ((Value & 0b00000111) << 20);
}
static INLINE void XCpwm8c_mWrite_EventCount_4(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111111100011111111111111111) + ((Value & 0b00000111) << 17);
}
static INLINE void XCpwm8c_mWrite_EventCount_3(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111111111100011111111111111) + ((Value & 0b00000111) << 14);
}
static INLINE void XCpwm8c_mWrite_EventCount_2(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111111111111100011111111111) + ((Value & 0b00000111) << 11);
}
static INLINE void XCpwm8c_mWrite_EventCount_1(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111111111111111100011111111) + ((Value & 0b00000111) << 8);
}

static INLINE void XCpwm8c_mWrite_InterruptMatrix(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111111111111111111100000000) + (Value);
}

static INLINE void XCpwm8c_mWrite_CountMode_8(UINTPTR BaseAddress, XCpwm8c_countmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b00111111111111111111111111111111) + ((u8)Value << 30);
}
static INLINE void XCpwm8c_mWrite_CountMode_7(UINTPTR BaseAddress, XCpwm8c_countmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11001111111111111111111111111111) + ((u8)Value << 28);
}
static INLINE void XCpwm8c_mWrite_CountMode_6(UINTPTR BaseAddress, XCpwm8c_countmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11110011111111111111111111111111) + ((u8)Value << 26);
}
static INLINE void XCpwm8c_mWrite_CountMode_5(UINTPTR BaseAddress, XCpwm8c_countmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111100111111111111111111111111) + ((u8)Value << 24);
}
static INLINE void XCpwm8c_mWrite_CountMode_4(UINTPTR BaseAddress, XCpwm8c_countmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111001111111111111111111111) + ((u8)Value << 22);
}
static INLINE void XCpwm8c_mWrite_CountMode_3(UINTPTR BaseAddress, XCpwm8c_countmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111110011111111111111111111) + ((u8)Value << 20);
}
static INLINE void XCpwm8c_mWrite_CountMode_2(UINTPTR BaseAddress, XCpwm8c_countmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111100111111111111111111) + ((u8)Value << 18);
}
static INLINE void XCpwm8c_mWrite_CountMode_1(UINTPTR BaseAddress, XCpwm8c_countmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111001111111111111111) + ((u8)Value << 16);
}

static INLINE void XCpwm8c_mWrite_MaskMode_8(UINTPTR BaseAddress, XCpwm8c_maskmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111110011111111111111) + ((u8)Value << 14);
}
static INLINE void XCpwm8c_mWrite_MaskMode_7(UINTPTR BaseAddress, XCpwm8c_maskmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111100111111111111) + ((u8)Value << 12);
}
static INLINE void XCpwm8c_mWrite_MaskMode_6(UINTPTR BaseAddress, XCpwm8c_maskmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111001111111111) + ((u8)Value << 10);
}
static INLINE void XCpwm8c_mWrite_MaskMode_5(UINTPTR BaseAddress, XCpwm8c_maskmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111110011111111) + ((u8)Value << 8);
}
static INLINE void XCpwm8c_mWrite_MaskMode_4(UINTPTR BaseAddress, XCpwm8c_maskmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111111100111111) + ((u8)Value << 6);
}
static INLINE void XCpwm8c_mWrite_MaskMode_3(UINTPTR BaseAddress, XCpwm8c_maskmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111111111001111) + ((u8)Value << 4);
}
static INLINE void XCpwm8c_mWrite_MaskMode_2(UINTPTR BaseAddress, XCpwm8c_maskmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111111111110011) + ((u8)Value << 2);
}
static INLINE void XCpwm8c_mWrite_MaskMode_1(UINTPTR BaseAddress, XCpwm8c_maskmode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111111111111100) + ((u8)Value);
}

static INLINE void XCpwm8c_mWrite_DTimeOnOff_8(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b01111111111111111111111111111111) + ((u8)Value << 31);
}
static INLINE void XCpwm8c_mWrite_DTimeOnOff_7(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b10111111111111111111111111111111) + ((u8)Value << 30);
}
static INLINE void XCpwm8c_mWrite_DTimeOnOff_6(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11011111111111111111111111111111) + ((u8)Value << 29);
}
static INLINE void XCpwm8c_mWrite_DTimeOnOff_5(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11101111111111111111111111111111) + ((u8)Value << 28);
}
static INLINE void XCpwm8c_mWrite_DTimeOnOff_4(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11110111111111111111111111111111) + ((u8)Value << 27);
}
static INLINE void XCpwm8c_mWrite_DTimeOnOff_3(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111011111111111111111111111111) + ((u8)Value << 26);
}
static INLINE void XCpwm8c_mWrite_DTimeOnOff_2(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111101111111111111111111111111) + ((u8)Value << 25);
}
static INLINE void XCpwm8c_mWrite_DTimeOnOff_1(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111110111111111111111111111111) + ((u8)Value << 24);
}

static INLINE void XCpwm8c_mWrite_LogicA_8(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111011111111111111111111111) + ((u8)Value << 23);
}
static INLINE void XCpwm8c_mWrite_LogicA_7(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111101111111111111111111111) + ((u8)Value << 22);
}
static INLINE void XCpwm8c_mWrite_LogicA_6(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111110111111111111111111111) + ((u8)Value << 21);
}
static INLINE void XCpwm8c_mWrite_LogicA_5(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111011111111111111111111) + ((u8)Value << 20);
}
static INLINE void XCpwm8c_mWrite_LogicA_4(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111101111111111111111111) + ((u8)Value << 19);
}
static INLINE void XCpwm8c_mWrite_LogicA_3(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111110111111111111111111) + ((u8)Value << 18);
}
static INLINE void XCpwm8c_mWrite_LogicA_2(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111011111111111111111) + ((u8)Value << 17);
}
static INLINE void XCpwm8c_mWrite_LogicA_1(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111101111111111111111) + ((u8)Value << 16);
}

static INLINE void XCpwm8c_mWrite_LogicB_8(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111110111111111111111) + ((u8)Value << 15);
}
static INLINE void XCpwm8c_mWrite_LogicB_7(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111011111111111111) + ((u8)Value << 14);
}
static INLINE void XCpwm8c_mWrite_LogicB_6(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111101111111111111) + ((u8)Value << 13);
}
static INLINE void XCpwm8c_mWrite_LogicB_5(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111110111111111111) + ((u8)Value << 12);
}
static INLINE void XCpwm8c_mWrite_LogicB_4(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111011111111111) + ((u8)Value << 11);
}
static INLINE void XCpwm8c_mWrite_LogicB_3(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111101111111111) + ((u8)Value << 10);
}
static INLINE void XCpwm8c_mWrite_LogicB_2(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111110111111111) + ((u8)Value << 9);
}
static INLINE void XCpwm8c_mWrite_LogicB_1(UINTPTR BaseAddress, XCpwm8c_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111011111111) + ((u8)Value << 8);
}

static INLINE void XCpwm8c_mWrite_CarrSel_8(UINTPTR BaseAddress, XCpwm8c_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111101111111) + ((u8)Value << 7);
}
static INLINE void XCpwm8c_mWrite_CarrSel_7(UINTPTR BaseAddress, XCpwm8c_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111110111111) + ((u8)Value << 6);
}
static INLINE void XCpwm8c_mWrite_CarrSel_6(UINTPTR BaseAddress, XCpwm8c_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111111011111) + ((u8)Value << 5);
}
static INLINE void XCpwm8c_mWrite_CarrSel_5(UINTPTR BaseAddress, XCpwm8c_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111111101111) + ((u8)Value << 4);
}
static INLINE void XCpwm8c_mWrite_CarrSel_4(UINTPTR BaseAddress, XCpwm8c_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111111110111) + ((u8)Value << 3);
}
static INLINE void XCpwm8c_mWrite_CarrSel_3(UINTPTR BaseAddress, XCpwm8c_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111111111011) + ((u8)Value << 2);
}
static INLINE void XCpwm8c_mWrite_CarrSel_2(UINTPTR BaseAddress, XCpwm8c_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111111111101) + ((u8)Value << 1);
}
static INLINE void XCpwm8c_mWrite_CarrSel_1(UINTPTR BaseAddress, XCpwm8c_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111111111110) + ((u8)Value);
}

static INLINE void XCpwm8c_mWrite_PWMOnOff(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111111111111110) + ((u8)Value);
}

static INLINE void XCpwm8c_mWrite_CarrOnOff_8(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111111011111111) + ((u8)Value << 8);
}
static INLINE void XCpwm8c_mWrite_CarrOnOff_7(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111111101111111) + ((u8)Value << 7);
}
static INLINE void XCpwm8c_mWrite_CarrOnOff_6(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111111110111111) + ((u8)Value << 6);
}
static INLINE void XCpwm8c_mWrite_CarrOnOff_5(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111111111011111) + ((u8)Value << 5);
}
static INLINE void XCpwm8c_mWrite_CarrOnOff_4(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111111111101111) + ((u8)Value << 4);
}
static INLINE void XCpwm8c_mWrite_CarrOnOff_3(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111111111110111) + ((u8)Value << 3);
}
static INLINE void XCpwm8c_mWrite_CarrOnOff_2(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111111111111011) + ((u8)Value << 2);
}
static INLINE void XCpwm8c_mWrite_CarrOnOff_1(UINTPTR BaseAddress, XCpwm8c_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111111111111101) + ((u8)Value << 1);
}

static INLINE void XCpwm8c_mWrite_IntAck(UINTPTR BaseAddress){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111110111111111) + (1 << 9);
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111110111111111) + (0 << 9);
}

#define XCpwm8c_In32  Xil_In32	/**< Input Operations */
#define XCpwm8c_Out32 Xil_Out32	/**< Output Operations */
#define XCpwm8c_In16  Xil_In16	/**< Input Operations */
#define XCpwm8c_Out16 Xil_Out16	/**< Output Operations */


/**************************** Type Definitions *****************************/

#define XCpwm8c_mWriteReg32(BaseAddress, RegOffset, Data) \
  	XCpwm8c_Out32((BaseAddress) + (RegOffset), (u32)(Data))

#define XCpwm8c_mReadReg32(BaseAddress, RegOffset) \
    XCpwm8c_In32((BaseAddress) + (RegOffset))

#define XCpwm8c_mWriteReg16(BaseAddress, RegOffset, Data) \
  	XCpwm8c_Out16((BaseAddress) + (RegOffset), (u16)(Data))

#define XCpwm8c_mReadReg16(BaseAddress, RegOffset) \
    XCpwm8c_In16((BaseAddress) + (RegOffset))


XStatus XCpwm8c_Reg_SelfTest(void * baseaddr_p);

#endif // XCPWM8C_H
