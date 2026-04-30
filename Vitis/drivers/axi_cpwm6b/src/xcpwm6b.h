#ifndef XCPWM6B_H
#define XCPWM6B_H

#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"

/*************** OFFSETS (en bytes) ***************/
#define XCPWM6B_OFFSET_CARRIER     0x00
#define XCPWM6B_OFFSET_MODE        0x04
#define XCPWM6B_OFFSET_COMPARE     0x08
#define XCPWM6B_OFFSET_DEADTIME    0x14

/*************** MODE REGISTER (bits) ***************/
#define XCPWM6B_MASK_COUNT_MODE    0x00000003  //position ou l'on ecrit dana le registre (valeur du bit)
#define XCPWM6B_SHIFT_COUNT_MODE   0 // nombre de bits dont on se decale

#define XCPWM6B_MASK_SYNC_MODE     0x0000000C
#define XCPWM6B_SHIFT_SYNC_MODE    2

#define XCPWM6B_MASK_EVENT_COUNT   0x000000F0
#define XCPWM6B_SHIFT_EVENT_COUNT  4
 
#define XCPWM6B_MASK_CLKDIV_CARR   0x00000300
#define XCPWM6B_SHIFT_CLKDIV_CARR  8

#define XCPWM6B_MASK_EN_PWM        0x00000400
#define XCPWM6B_SHIFT_EN_PWM       10

#define XCPWM6B_MASK_SIG_PWM1      0x00000800
#define XCPWM6B_SHIFT_SIG_PWM1     11

#define XCPWM6B_MASK_SIG_PWM2      0x00001000
#define XCPWM6B_SHIFT_SIG_PWM2     12

#define XCPWM6B_MASK_MASK_ON       0x00002000
#define XCPWM6B_SHIFT_MASK_ON      13

#define XCPWM6B_MASK_CE            0x00004000
#define XCPWM6B_SHIFT_CE           14

/*************** DEADTIME REGISTER ***************/
#define XCPWM6B_MASK_DEADTIME      0x000000FF
#define XCPWM6B_SHIFT_DEADTIME     0

#define XCPWM6B_MASK_DTONOFF       0x00000100
#define XCPWM6B_SHIFT_DTONOFF      8

#define XCPWM6B_MASK_DT_LOGIC_1A   0x00000200
#define XCPWM6B_SHIFT_DT_LOGIC_1A  9

#define XCPWM6B_MASK_DT_LOGIC_1B   0x00000400
#define XCPWM6B_SHIFT_DT_LOGIC_1B  10

#define XCPWM6B_MASK_DT_LOGIC_2A   0x00000800
#define XCPWM6B_SHIFT_DT_LOGIC_2A  11

#define XCPWM6B_MASK_DT_LOGIC_2B   0x00001000
#define XCPWM6B_SHIFT_DT_LOGIC_2B  12

#define XCPWM6B_MASK_CLKDIV_DTIME  0x00006000
#define XCPWM6B_SHIFT_CLKDIV_DTIME 13

/*************** TYPES ***************/
typedef enum {
    NO_COUNT = 0,
    COUNT_UP = 1,
    COUNT_DOWN = 2,
    COUNT_UP_DOWN = 3
} XCpwm6b_countmode;

typedef enum {
    NO_EVENT = 0,
    MIN_EVENT = 1,
    MAX_EVENT = 2,
    MINMAX_EVENT = 3
} XCpwm6b_syncmode;

typedef enum {
    REG_OFF = 0,
    REG_ON = 1
} XCpwm6b_onoff;

/**
 * @brief Output polarity
 */
typedef enum {
	LOGIC_POS = 0, /**< Active high */
	LOGIC_NEG = 1, /**< Active low */
} XCpwm6b_logic;

/*************** EXHAUSTIVE STRUCT ***************/
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
} XCpwm6b_Config;


typedef struct {

    /* HW access */
    UINTPTR BaseAddr;
    u32 IsReady;

    /* -------- CARRIER -------- */
    u16 carrier_max;
    u16 carrier_init;

    /* -------- COMPARE -------- */
    u16 compare1;
    u16 compare2;

    /* -------- MODE -------- */
    XCpwm6b_countmode count_mode;
    XCpwm6b_syncmode sync_mode;
    u8 event_count;
    u8 clkdiv_carr;

    XCpwm6b_onoff en_pwm;
    XCpwm6b_onoff mask_on;
    XCpwm6b_onoff ce;

    XCpwm6b_logic sig_pwm_1;
    XCpwm6b_logic sig_pwm_2;

    /* -------- DEADTIME -------- */
    u8 deadtime;
    XCpwm6b_onoff dt_onoff;
    u8 clkdiv_dtime;

    XCpwm6b_logic dt_logic_1a;
    XCpwm6b_logic dt_logic_1b;
    XCpwm6b_logic dt_logic_2a;
    XCpwm6b_logic dt_logic_2b;

} XCpwm6b;

extern XCpwm6b_Config XCpwm6b_ConfigTable[];

/*************** FUNCTIONS ***************/
#ifndef SDT
int XCpwm6b_Initialize(XCpwm6b *InstancePtr, u16 DeviceId);
XCpwm6b_Config *XCpwm6b_LookupConfig(u16 DeviceId);
#else
int XCpwm6b_Initialize(XCpwm6b *InstancePtr, UINTPTR BaseAddress);
XCpwm6b_Config *XCpwm6b_LookupConfig(UINTPTR BaseAddress);
#endif

int XCpwm6b_CfgInitialize(XCpwm6b *InstancePtr,const XCpwm6b_Config *Config, UINTPTR BaseAddr);
void XCpwm6b_WriteFullStatus(XCpwm6b *InstancePtr);


/* Carrier */
void XCpwm6b_WriteCarrierMax(XCpwm6b*, u16);
void XCpwm6b_WriteCarrierInit(XCpwm6b*, u16);

/* Mode */
void XCpwm6b_WriteCountMode(XCpwm6b*, XCpwm6b_countmode);
void XCpwm6b_WriteSyncMode(XCpwm6b*, XCpwm6b_syncmode);
void XCpwm6b_WriteEventCount(XCpwm6b*, u8);
void XCpwm6b_WriteClkDivCarr(XCpwm6b*, u8);
void XCpwm6b_WritePwmOnOff(XCpwm6b*, XCpwm6b_onoff);
void XCpwm6b_WriteMaskOn(XCpwm6b*, XCpwm6b_onoff);
void XCpwm6b_WriteCE(XCpwm6b*, XCpwm6b_onoff);

/* Logic */
void XCpwm6b_WriteLogicA(XCpwm6b*, XCpwm6b_logic);
void XCpwm6b_WriteLogicB(XCpwm6b*, XCpwm6b_logic);

/* Compare */
void XCpwm6b_WriteCompare1(XCpwm6b*, u16);
void XCpwm6b_WriteCompare2(XCpwm6b*, u16);

/* Deadtime */
void XCpwm6b_WriteDeadTime(XCpwm6b*, u8);
void XCpwm6b_WriteDeadTimeOnOff(XCpwm6b*, XCpwm6b_onoff);
void XCpwm6b_WriteClkDivDTime(XCpwm6b*, u8);

/* Deadtime Logic */
void XCpwm6b_WriteDtLogic1A(XCpwm6b*, XCpwm6b_logic);
void XCpwm6b_WriteDtLogic1B(XCpwm6b*, XCpwm6b_logic);
void XCpwm6b_WriteDtLogic2A(XCpwm6b*, XCpwm6b_logic);
void XCpwm6b_WriteDtLogic2B(XCpwm6b*, XCpwm6b_logic);

#endif
```
