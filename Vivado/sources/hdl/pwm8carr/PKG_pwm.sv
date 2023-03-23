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
    
    typedef enum logic [1:0] {NO_COUNT,COUNT_UP,COUNT_DOWN,COUNT_UPDOWN} _count_mode;
    typedef enum logic [1:0] {NO_MASK,MIN_MASK,MAX_MASK,MINMAX_MASK} _mask_mode;
    typedef enum logic {PWM_OFF,PWM_ON} _pwm_onoff;
	typedef enum logic {INT_OFF,INT_ON} _int_onoff;
	typedef enum logic {DT_OFF,DT_ON} _dt_onoff;
	typedef enum logic {CLKDIV_OFF,CLKDIV_ON} _clkdiv_onoff;
	typedef enum logic {CARR_OFF,CARR_ON} _carr_onoff;
	
	//typedef _count_mode [`PWM_WIDTH-1:0] _count_mode_t;
	//typedef _mask_mode [`PWM_WIDTH-1:0] _mask_mode_t;
	//typedef _pwm_onoff [`PWM_WIDTH-1:0] _pwm_onoff_t;
endpackage