
#ifndef AXI_CPWM8C_H
#define AXI_CPWM8C_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"

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
#define AXI_CPWM8C_S_AXI_SLV_REG20_OFFSET 80
#define AXI_CPWM8C_S_AXI_SLV_REG21_OFFSET 84

/************************** User defined functions/macros ****************************/
/**/
/**/
typedef enum
{
   NO_COUNT = 0,
   COUNT_UP = 1,
   COUNT_DOWN = 2,
   COUNT_UP_DOWN = 3,
} AXI_CPWM8C_count_mode;

typedef enum
{
   NO_MASK = 0,
   MIN_MASK = 1,
   MAX_MASK = 2,
   MINMAX_MASK = 3,
} AXI_CPWM8C_mask_mode;

typedef enum
{
   REG_OFF = 0,
   REG_ON = 1,
} AXI_CPWM8C_onoff;

typedef enum
{
   LOGIC_POS = 0,
   LOGIC_NEG = 1,
} AXI_CPWM8C_logic;

typedef enum
{
   CARR_MASTER1 = 0,
   CARR_LOCAL = 1,
} AXI_CPWM8C_carrsel;

static inline void AXI_CPWM8C_mWrite_Period_1(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG0_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG0_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_Period_2(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG0_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG0_OFFSET) & 0xFFFF0000) + (Value);
}
static inline void AXI_CPWM8C_mWrite_Period_3(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG1_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG1_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_Period_4(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG1_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG1_OFFSET) & 0xFFFF0000) + (Value);
}
static inline void AXI_CPWM8C_mWrite_Period_5(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG2_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG2_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_Period_6(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG2_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG2_OFFSET) & 0xFFFF0000) + (Value);
}
static inline void AXI_CPWM8C_mWrite_Period_7(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG3_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG3_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_Period_8(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG3_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG3_OFFSET) & 0xFFFF0000) + (Value);
}

static inline void AXI_CPWM8C_mWrite_InitCarrier_1(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG4_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_InitCarrier_2(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG4_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG4_OFFSET) & 0xFFFF0000) + (Value);
}
static inline void AXI_CPWM8C_mWrite_InitCarrier_3(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG5_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG5_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_InitCarrier_4(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG5_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG5_OFFSET) & 0xFFFF0000) + (Value);
}
static inline void AXI_CPWM8C_mWrite_InitCarrier_5(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG6_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG6_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_InitCarrier_6(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG6_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG6_OFFSET) & 0xFFFF0000) + (Value);
}
static inline void AXI_CPWM8C_mWrite_InitCarrier_7(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG7_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG7_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_InitCarrier_8(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG7_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG7_OFFSET) & 0xFFFF0000) + (Value);
}

static inline void AXI_CPWM8C_mWrite_Compare_1(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_Compare_2(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG8_OFFSET) & 0xFFFF0000) + (Value);
}
static inline void AXI_CPWM8C_mWrite_Compare_3(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG9_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG9_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_Compare_4(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG9_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG9_OFFSET) & 0xFFFF0000) + (Value);
}
static inline void AXI_CPWM8C_mWrite_Compare_5(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG10_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG10_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_Compare_6(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG10_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG10_OFFSET) & 0xFFFF0000) + (Value);
}
static inline void AXI_CPWM8C_mWrite_Compare_7(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG11_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG11_OFFSET) & 0x0000FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_Compare_8(UINTPTR BaseAddress, u16 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG11_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG11_OFFSET) & 0xFFFF0000) + (Value);
}

static inline void AXI_CPWM8C_mWrite_DeadTimeA_1(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) & 0x00FFFFFF) + (Value << 24);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeA_2(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) & 0xFF00FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeA_3(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) & 0xFFFF00FF) + (Value << 8);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeA_4(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG12_OFFSET) & 0xFFFFFF00) + (Value);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeA_5(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) & 0x00FFFFFF) + (Value << 24);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeA_6(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) & 0xFF00FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeA_7(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) & 0xFFFF00FF) + (Value << 8);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeA_8(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG13_OFFSET) & 0xFFFFFF00) + (Value);
}

static inline void AXI_CPWM8C_mWrite_DeadTimeB_1(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) & 0x00FFFFFF) + (Value << 24);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeB_2(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) & 0xFF00FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeB_3(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) & 0xFFFF00FF) + (Value << 8);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeB_4(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG14_OFFSET) & 0xFFFFFF00) + (Value);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeB_5(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) & 0x00FFFFFF) + (Value << 24);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeB_6(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) & 0xFF00FFFF) + (Value << 16);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeB_7(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) & 0xFFFF00FF) + (Value << 8);
}
static inline void AXI_CPWM8C_mWrite_DeadTimeB_8(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG15_OFFSET) & 0xFFFFFF00) + (Value);
}

static inline void AXI_CPWM8C_mWrite_EventCount_1(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b00011111111111111111111111111111) + ((Value & 0b00000111) << 29);
}
static inline void AXI_CPWM8C_mWrite_EventCount_2(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11100011111111111111111111111111) + ((Value & 0b00000111) << 26);
}
static inline void AXI_CPWM8C_mWrite_EventCount_3(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111100011111111111111111111111) + ((Value & 0b00000111) << 23);
}
static inline void AXI_CPWM8C_mWrite_EventCount_4(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111100011111111111111111111) + ((Value & 0b00000111) << 20);
}
static inline void AXI_CPWM8C_mWrite_EventCount_5(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111111100011111111111111111) + ((Value & 0b00000111) << 17);
}
static inline void AXI_CPWM8C_mWrite_EventCount_6(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111111111100011111111111111) + ((Value & 0b00000111) << 14);
}
static inline void AXI_CPWM8C_mWrite_EventCount_7(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111111111111100011111111111) + ((Value & 0b00000111) << 11);
}
static inline void AXI_CPWM8C_mWrite_EventCount_8(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111111111111111100011111111) + ((Value & 0b00000111) << 8);
}

static inline void AXI_CPWM8C_mWrite_InterruptMatrix(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG16_OFFSET) & 0b11111111111111111111111100000000) + (Value);
}

static inline void AXI_CPWM8C_mWrite_CountMode_1(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b00111111111111111111111111111111) + ((u8)Value << 30);
}
static inline void AXI_CPWM8C_mWrite_CountMode_2(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11001111111111111111111111111111) + ((u8)Value << 28);
}
static inline void AXI_CPWM8C_mWrite_CountMode_3(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11110011111111111111111111111111) + ((u8)Value << 26);
}
static inline void AXI_CPWM8C_mWrite_CountMode_4(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111100111111111111111111111111) + ((u8)Value << 24);
}
static inline void AXI_CPWM8C_mWrite_CountMode_5(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111001111111111111111111111) + ((u8)Value << 22);
}
static inline void AXI_CPWM8C_mWrite_CountMode_6(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111110011111111111111111111) + ((u8)Value << 20);
}
static inline void AXI_CPWM8C_mWrite_CountMode_7(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111100111111111111111111) + ((u8)Value << 18);
}
static inline void AXI_CPWM8C_mWrite_CountMode_8(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111001111111111111111) + ((u8)Value << 16);
}

static inline void AXI_CPWM8C_mWrite_MaskMode_1(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111110011111111111111) + ((u8)Value << 14);
}
static inline void AXI_CPWM8C_mWrite_MaskMode_2(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111100111111111111) + ((u8)Value << 12);
}
static inline void AXI_CPWM8C_mWrite_MaskMode_3(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111001111111111) + ((u8)Value << 10);
}
static inline void AXI_CPWM8C_mWrite_MaskMode_4(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111110011111111) + ((u8)Value << 8);
}
static inline void AXI_CPWM8C_mWrite_MaskMode_5(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111111100111111) + ((u8)Value << 6);
}
static inline void AXI_CPWM8C_mWrite_MaskMode_6(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111111111001111) + ((u8)Value << 4);
}
static inline void AXI_CPWM8C_mWrite_MaskMode_7(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111111111110011) + ((u8)Value << 2);
}
static inline void AXI_CPWM8C_mWrite_MaskMode_8(UINTPTR BaseAddress, AXI_CPWM8C_count_mode Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG17_OFFSET) & 0b11111111111111111111111111111100) + ((u8)Value);
}

static inline void AXI_CPWM8C_mWrite_DTimeOnOff_1(UINTPTR BaseAddress, AXI_CPWM8C_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b01111111111111111111111111111111) + ((u8)Value << 31);
}
static inline void AXI_CPWM8C_mWrite_DTimeOnOff_2(UINTPTR BaseAddress, AXI_CPWM8C_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b10111111111111111111111111111111) + ((u8)Value << 30);
}
static inline void AXI_CPWM8C_mWrite_DTimeOnOff_3(UINTPTR BaseAddress, AXI_CPWM8C_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11011111111111111111111111111111) + ((u8)Value << 29);
}
static inline void AXI_CPWM8C_mWrite_DTimeOnOff_4(UINTPTR BaseAddress, AXI_CPWM8C_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11101111111111111111111111111111) + ((u8)Value << 28);
}
static inline void AXI_CPWM8C_mWrite_DTimeOnOff_5(UINTPTR BaseAddress, AXI_CPWM8C_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11110111111111111111111111111111) + ((u8)Value << 27);
}
static inline void AXI_CPWM8C_mWrite_DTimeOnOff_6(UINTPTR BaseAddress, AXI_CPWM8C_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111011111111111111111111111111) + ((u8)Value << 26);
}
static inline void AXI_CPWM8C_mWrite_DTimeOnOff_7(UINTPTR BaseAddress, AXI_CPWM8C_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111101111111111111111111111111) + ((u8)Value << 25);
}
static inline void AXI_CPWM8C_mWrite_DTimeOnOff_8(UINTPTR BaseAddress, AXI_CPWM8C_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111110111111111111111111111111) + ((u8)Value << 24);
}

static inline void AXI_CPWM8C_mWrite_LogicA_1(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111011111111111111111111111) + ((u8)Value << 23);
}
static inline void AXI_CPWM8C_mWrite_LogicA_2(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111101111111111111111111111) + ((u8)Value << 22);
}
static inline void AXI_CPWM8C_mWrite_LogicA_3(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111110111111111111111111111) + ((u8)Value << 21);
}
static inline void AXI_CPWM8C_mWrite_LogicA_4(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111011111111111111111111) + ((u8)Value << 20);
}
static inline void AXI_CPWM8C_mWrite_LogicA_5(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111101111111111111111111) + ((u8)Value << 19);
}
static inline void AXI_CPWM8C_mWrite_LogicA_6(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111110111111111111111111) + ((u8)Value << 18);
}
static inline void AXI_CPWM8C_mWrite_LogicA_7(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111011111111111111111) + ((u8)Value << 17);
}
static inline void AXI_CPWM8C_mWrite_LogicA_8(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111101111111111111111) + ((u8)Value << 16);
}

static inline void AXI_CPWM8C_mWrite_LogicB_1(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111110111111111111111) + ((u8)Value << 15);
}
static inline void AXI_CPWM8C_mWrite_LogicB_2(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111011111111111111) + ((u8)Value << 14);
}
static inline void AXI_CPWM8C_mWrite_LogicB_3(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111101111111111111) + ((u8)Value << 13);
}
static inline void AXI_CPWM8C_mWrite_LogicB_4(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111110111111111111) + ((u8)Value << 12);
}
static inline void AXI_CPWM8C_mWrite_LogicB_5(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111011111111111) + ((u8)Value << 11);
}
static inline void AXI_CPWM8C_mWrite_LogicB_6(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111101111111111) + ((u8)Value << 10);
}
static inline void AXI_CPWM8C_mWrite_LogicB_7(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111110111111111) + ((u8)Value << 9);
}
static inline void AXI_CPWM8C_mWrite_LogicB_8(UINTPTR BaseAddress, AXI_CPWM8C_logic Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111011111111) + ((u8)Value << 8);
}

static inline void AXI_CPWM8C_mWrite_CarrSel_1(UINTPTR BaseAddress, AXI_CPWM8C_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111101111111) + ((u8)Value << 7);
}
static inline void AXI_CPWM8C_mWrite_CarrSel_2(UINTPTR BaseAddress, AXI_CPWM8C_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111110111111) + ((u8)Value << 6);
}
static inline void AXI_CPWM8C_mWrite_CarrSel_3(UINTPTR BaseAddress, AXI_CPWM8C_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111111011111) + ((u8)Value << 5);
}
static inline void AXI_CPWM8C_mWrite_CarrSel_4(UINTPTR BaseAddress, AXI_CPWM8C_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111111101111) + ((u8)Value << 4);
}
static inline void AXI_CPWM8C_mWrite_CarrSel_5(UINTPTR BaseAddress, AXI_CPWM8C_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111110111111111110111) + ((u8)Value << 3);
}
static inline void AXI_CPWM8C_mWrite_CarrSel_6(UINTPTR BaseAddress, AXI_CPWM8C_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111110111111111111011) + ((u8)Value << 2);
}
static inline void AXI_CPWM8C_mWrite_CarrSel_7(UINTPTR BaseAddress, AXI_CPWM8C_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111111111101) + ((u8)Value << 1);
}
static inline void AXI_CPWM8C_mWrite_CarrSel_8(UINTPTR BaseAddress, AXI_CPWM8C_carrsel Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG18_OFFSET) & 0b11111111111111111111111111111110) + ((u8)Value);
}

static inline void AXI_CPWM8C_mWrite_PWMOnOff(UINTPTR BaseAddress, AXI_CPWM8C_onoff Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111111111111110) + ((u8)Value);
}

static inline void AXI_CPWM8C_mWrite_CarrSel(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) = (HWREG(BaseAddress + AXI_CPWM8C_S_AXI_SLV_REG19_OFFSET) & 0b11111111111111111111111111111001) + ((Value & 0b00000011) << 1);
}

/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a AXI_CPWM8C register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the AXI_CPWM8Cdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void AXI_CPWM8C_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define AXI_CPWM8C_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a AXI_CPWM8C register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the AXI_CPWM8C device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 AXI_CPWM8C_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define AXI_CPWM8C_mReadReg(BaseAddress, RegOffset) \
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
 * @param   baseaddr_p is the base address of the AXI_CPWM8C instance to be worked on.
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
XStatus AXI_CPWM8C_Reg_SelfTest(void * baseaddr_p);

#endif // AXI_CPWM8C_H
