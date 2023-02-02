`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 03:09:25 AM
// Design Name: 
// Module Name: configregpwm_split
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

module configregpwm_split(
    input [`PWMCOUNT_WIDTH-1:0] register_concat,
	output _pwm_onoff pwm_onoff,
	output _int_onoff int_onoff,
	output _clkdiv_onoff pwmclkdiv_onoff,
	output _clkdiv_onoff dtclkdiv_onoff,
	output _mask_mode mask_mode,
	output _count_mode count_mode
    );

    assign count_mode = _count_mode'(register_concat[1:0]);
	assign mask_mode = _mask_mode'(register_concat[3:2]);
	assign pwmclkdiv_onoff = _clkdiv_onoff'(register_concat[4]);
    assign dtclkdiv_onoff = _clkdiv_onoff'(register_concat[5]);
    assign int_onoff = _int_onoff'(register_concat[6]);
    assign pwm_onoff = _pwm_onoff'(register_concat[7]);

endmodule
