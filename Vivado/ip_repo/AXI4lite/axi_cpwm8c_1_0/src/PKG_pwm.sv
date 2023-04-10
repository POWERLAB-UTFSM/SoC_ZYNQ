`timescale 10ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 02:52:10 AM
// Design Name: 
// Module Name: PKG_pwm
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


package PKG_pwm;
    `ifndef PWM_WIDTH
    `define PWM_WIDTH 8
    `endif

    `ifndef DIVCLK_WIDTH
    `define DIVCLK_WIDTH 4
    `endif
    
    `ifndef DTCOUNT_WIDTH
    `define DTCOUNT_WIDTH 8
    `endif
    
    `ifndef PWMCOUNT_WIDTH
    `define PWMCOUNT_WIDTH 16
    `endif
    
    `ifndef EVTCOUNT_WIDTH
    `define EVTCOUNT_WIDTH 3
    `endif
    
    typedef enum logic [1:0] {NO_COUNT=0,COUNT_UP=1,COUNT_DOWN=2,COUNT_UPDOWN=3} _count_mode;
    typedef enum logic [1:0] {NO_MASK=0,MIN_MASK=1,MAX_MASK=2,MINMAX_MASK=3} _mask_mode;
    typedef enum logic {PWM_OFF,PWM_ON} _pwm_onoff;
	typedef enum logic {INT_OFF,INT_ON} _int_onoff;
	typedef enum logic {DT_OFF,DT_ON} _dt_onoff;
	typedef enum logic {CLKDIV_OFF,CLKDIV_ON} _clkdiv_onoff;
	typedef enum logic {CARR_OFF,CARR_ON} _carr_onoff;
	typedef enum logic {CARR_MASTER1=0,CARR_LOCAL=1} _carr_sel;
	typedef enum logic {LOGIC_POS=0,LOGIC_NEG=1} _logic_pwm;
	
	//typedef _count_mode [`PWM_WIDTH-1:0] _count_mode_t;
	//typedef _mask_mode [`PWM_WIDTH-1:0] _mask_mode_t;
	//typedef _pwm_onoff [`PWM_WIDTH-1:0] _pwm_onoff_t;
endpackage