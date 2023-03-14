`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 03:09:25 AM
// Design Name: 
// Module Name: configregpwm_concatenate
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

import PKG_pwm::*;

module configregpwm_concatenate(
    input _pwm_onoff pwm_onoff, //1 bit
    input _int_onoff int_onoff, //1 bit
    input _clkdiv_onoff pwmclkdiv_onoff, //1 bit
    input _clkdiv_onoff dtclkdiv_onoff, //1 bit
    input _mask_mode mask_mode, //1 bit
	input _count_mode count_mode,
	input logic_A,
	input logic_B,
	output[`PWMCOUNT_WIDTH-1:0] register_concat
    );
    
    assign register_concat = {logic_B,logic_A,pwm_onoff,int_onoff,pwmclkdiv_onoff,dtclkdiv_onoff,mask_mode,count_mode};
    

endmodule
