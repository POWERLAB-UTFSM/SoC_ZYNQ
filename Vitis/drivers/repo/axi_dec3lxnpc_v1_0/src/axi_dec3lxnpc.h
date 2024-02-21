
#ifndef AXI_DEC3LXNPC_H
#define AXI_DEC3LXNPC_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"

/****************** read/write register ********************/
#define HWREG(x)                                                          \
            (*((volatile u32 *)(x)))

#define AXI_DEC3LXNPC_S00_AXI_SLV_REG0_OFFSET 0
#define AXI_DEC3LXNPC_S00_AXI_SLV_REG1_OFFSET 4
#define AXI_DEC3LXNPC_S00_AXI_SLV_REG2_OFFSET 8
#define AXI_DEC3LXNPC_S00_AXI_SLV_REG3_OFFSET 12

/************************** User defined functions/macros ****************************/
/**/
/**/

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
} AXI_DEC3LXNPC_Config;

typedef enum
{
   NoConv = 0,
   NPC = 1,
   NPP = 2,
   ANPC = 3,
} AXI_DEC3LXNPC_convtype;

typedef enum
{
   type_I = 0,
   type_IU = 1,
   type_II = 2,
   type_III = 3,
} AXI_DEC3LXNPC_commtype;

static INLINE void AXI_DEC3LXNPC_mWrite_tshort(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG0_OFFSET) = (HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG0_OFFSET) & 0xFFFFFF00) + (Value);
}

static INLINE void AXI_DEC3LXNPC_mWrite_toffon(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG1_OFFSET) = (HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG1_OFFSET) & 0x00FFFFFF) + (Value << 24);
}

static INLINE void AXI_DEC3LXNPC_mWrite_tonoffV0(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG1_OFFSET) = (HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG1_OFFSET) & 0xFF00FFFF) + (Value << 16);
}

static INLINE void AXI_DEC3LXNPC_mWrite_toffV0on(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG1_OFFSET) = (HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG1_OFFSET) & 0xFFFF00FF) + (Value << 8);
}

static INLINE void AXI_DEC3LXNPC_mWrite_toffonI0(UINTPTR BaseAddress, u8 Value){
	HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG1_OFFSET) = (HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG1_OFFSET) & 0xFFFFFF00) + (Value);
}

static INLINE void AXI_DEC3LXNPC_mWrite_commtype(UINTPTR BaseAddress, AXI_DEC3LXNPC_commtype Value){
	HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG2_OFFSET) = (HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG2_OFFSET) & 0b11111111111111111111111111110011) + (((u8)(Value) & 0b0000011) << 2);
}

static INLINE void AXI_DEC3LXNPC_mWrite_convtype(UINTPTR BaseAddress, AXI_DEC3LXNPC_convtype Value){
	HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG2_OFFSET) = (HWREG(BaseAddress + AXI_DEC3LXNPC_S00_AXI_SLV_REG2_OFFSET) & 0b11111111111111111111111111111100) + (((u8)(Value) & 0b0000011));
}


/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a AXI_DEC3LXNPC register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the AXI_DEC3LXNPCdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void AXI_DEC3LXNPC_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define AXI_DEC3LXNPC_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a AXI_DEC3LXNPC register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the AXI_DEC3LXNPC device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 AXI_DEC3LXNPC_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define AXI_DEC3LXNPC_mReadReg(BaseAddress, RegOffset) \
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
 * @param   baseaddr_p is the base address of the AXI_DEC3LXNPC instance to be worked on.
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
XStatus AXI_DEC3LXNPC_Reg_SelfTest(void * baseaddr_p);

#endif // AXI_DEC3LXNPC_H
