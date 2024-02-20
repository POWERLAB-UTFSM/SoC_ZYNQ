`timescale 10ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 01:18:08 AM
// Design Name: 
// Module Name:
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

module pwm16bits //#(parameter PWMWIDTH = 16)
(
	input clk,ce,rst,
	input [15:0] count_max,
	input [15:0] init_carr,
	input [1:0] count_mode, //00=no_count; 01=up; 10=down; 11=up_down
	input [1:0] sync_mode,//00=no_count; 01=min_count; 10=max_count; 11=minmax_count
	input [3:0] event_count,
	input [15:0] compare_1,
	input [15:0] compare_2,
    input en_pwm,
	input sig_pwm_1,
	input sig_pwm_2,
	//output wire [15:0] carrier,
	output wire sync,
	output wire pwm_1a,
	output wire pwm_1b,
	output wire pwm_2a,
	output wire pwm_2b
);

    wire [15:0] carrier;

	pwm16bits_timer  TIMER1 
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.count_max(count_max),
		.init_carr(init_carr),
		.count_mode(count_mode),
		.carrier(carrier)
	);

	pwm16bits_eventcount  EVTCNT1 
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.count_max(count_max),
		.carrier(carrier),
		.event_count(event_count),
		.sync_mode(sync_mode),
		.sync(sync)
	);
	
	pwm16bits_compare2ch  CMP1 
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.carrier(carrier),
		.compare_1(compare_1),
		.compare_2(compare_2),
        .en_pwm(en_pwm),
		.sig_pwm_1(sig_pwm_1),
		.sig_pwm_2(sig_pwm_2),
		.pwm_1a(pwm_1a),
		.pwm_2a(pwm_2a),
		.pwm_1b(pwm_1b),
		.pwm_2b(pwm_2b)
	);

endmodule