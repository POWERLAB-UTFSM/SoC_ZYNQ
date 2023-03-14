
#ifndef AXI_CPWM_H
#define AXI_CPWM_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"

#define AXI_CPWM_S_AXI_SLV_REG0_OFFSET 0
#define AXI_CPWM_S_AXI_SLV_REG1_OFFSET 4
#define AXI_CPWM_S_AXI_SLV_REG2_OFFSET 8
#define AXI_CPWM_S_AXI_SLV_REG3_OFFSET 12
#define AXI_CPWM_S_AXI_SLV_REG4_OFFSET 16

/****************** read/write register ********************/
#define HWREG(x)                                                          \
            (*((volatile u32 *)(x)))

typedef enum
{
   COUNT_UP = 0,
   COUNT_DOWN = 1,
   COUNT_UP_DOWN = 2,
} AXI_CPWM_count_mode;

typedef enum
{
   NO_MASK = 0,
   MIN_MASK = 1,
   MAX_MASK = 2,
   MINMAX_MASK = 3,
} AXI_CPWM_mask_mode;

typedef enum
{
   REG_OFF = 0,
   REG_ON = 1,
} AXI_CPWM_onoff;


     
/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a AXI_CPWM register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the AXI_CPWMdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void AXI_CPWM_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define AXI_CPWM_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a AXI_CPWM register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the AXI_CPWM device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 AXI_CPWM_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define AXI_CPWM_mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

/************************** Function Prototypes ****************************/
/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the AXI_CPWM instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus AXI_CPWM_Reg_SelfTest(void * baseaddr_p);

/************************** User defined functions/macros ****************************/
/**/
/**/
static inline void AXI_CPWM_mWrite_Period(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG0_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG0_OFFSET) & 0x0000FFFF) + (Value << 16);
}

static inline void AXI_CPWM_mWrite_InitCarrier(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG0_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG0_OFFSET) & 0xFFFF0000) + (Value);
}

static inline void AXI_CPWM_mWrite_Comp1(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG1_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG1_OFFSET) & 0x0000FFFF) + (Value << 16);
}

static inline void AXI_CPWM_mWrite_Comp2(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG1_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG1_OFFSET) & 0xFFFF0000) + (Value);
}

static inline void AXI_CPWM_mWrite_Comp3(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG2_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG2_OFFSET) & 0x0000FFFF) + (Value << 16);
}

static inline void AXI_CPWM_mWrite_Comp4(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG2_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG2_OFFSET) & 0xFFFF0000) + (Value);
}

static inline void AXI_CPWM_mWrite_DeadTimeA(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG3_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG3_OFFSET) & 0x00FFFFFF) + (Value << 24);
}

static inline void AXI_CPWM_mWrite_DeadTimeB(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG3_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG3_OFFSET) & 0xFF00FFFF) + (Value << 16);
}

static inline void AXI_CPWM_mWrite_CarrClkDiv(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG3_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG3_OFFSET) & 0b11111111111111110000011111111111) + (Value << 11);
}

static inline void AXI_CPWM_mWrite_DtimeClkDiv(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG3_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG3_OFFSET) & 0b11111111111111111111100000111111) + (Value << 6);
}

static inline void AXI_CPWM_mWrite_EventCount(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG3_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG3_OFFSET) & 0b11111111111111111111111111000111) + (Value << 3);
}

static inline void AXI_CPWM_mWrite_CountMode(UINTPTR BaseAddress, AXI_CPWM_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) & 0b11111111111111111111111111111100) + ((u8)Value);
}

static inline void AXI_CPWM_mWrite_MaskMode(UINTPTR BaseAddress, AXI_CPWM_mask_mode Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) & 0b11111111111111111111111111110011) + ((u8)Value << 2);
}

static inline void AXI_CPWM_mWrite_PWMOnOff(UINTPTR BaseAddress, AXI_CPWM_onoff Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) & 0b11111111111111111111111111101111) + ((u8)Value << 4);
}

static inline void AXI_CPWM_mWrite_IntOnOff(UINTPTR BaseAddress, AXI_CPWM_onoff Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) & 0b11111111111111111111111111011111) + ((u8)Value << 5);
}

static inline void AXI_CPWM_mWrite_PWMClkDivOnOff(UINTPTR BaseAddress, AXI_CPWM_onoff Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) & 0b11111111111111111111111110111111) + ((u8)Value << 6);
}

static inline void AXI_CPWM_mWrite_DTClkDivOnOff(UINTPTR BaseAddress, AXI_CPWM_onoff Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) & 0b11111111111111111111111101111111) + ((u8)Value << 7);
}

static inline void AXI_CPWM_mWrite_LogicOutA(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) & 0b11111111111111111111111011111111) + ((u8)Value << 8);
}

static inline void AXI_CPWM_mWrite_LogicOutB(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM_S_AXI_SLV_REG4_OFFSET) & 0b11111111111111111111110111111111) + ((u8)Value << 9);
}



#endif // AXI_CPWM_H
