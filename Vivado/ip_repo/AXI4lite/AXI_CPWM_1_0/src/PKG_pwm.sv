`timescale 1ns / 1ps
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
    `ifndef DIVCLK_WIDTH
    `define DIVCLK_WIDTH 5
    `endif
    
    `ifndef DTCOUNT_WIDTH
    `define DTCOUNT_WIDTH 8
    `endif
    
    `ifndef PWMCOUNT_WIDTH
    `define PWMCOUNT_WIDTH 16
    `endif
    
    `ifndef INTCOUNT_WIDTH
    `define INTCOUNT_WIDTH 3
    `endif
    
    typedef enum logic [1:0] {COUNT_UP,COUNT_DOWN,COUNT_UPDOWN} _count_mode;
    typedef enum logic [1:0] {NO_MASK,MIN_MASK,MAX_MASK,MINMAX_MASK} _mask_mode;
    typedef enum logic {PWM_OFF,PWM_ON} _pwm_onoff;
	typedef enum logic {INT_OFF,INT_ON} _int_onoff;
endpackage