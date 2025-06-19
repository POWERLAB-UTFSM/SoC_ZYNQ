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
	input [15:0] carrier_max,
	input [15:0] carrier_init,
	input carrier_initdir, //0=up, 1=down
	input [1:0] carrier_mode, //00=no_count; 01=up; 10=down; 11=up_down
	input [1:0] sync_mode,	//00=no_count; 01=min_count; 10=max_count; 11=minmax_count
	input [3:0] event_count,
	input [15:0] compare_1,
	input [15:0] compare_2,
	input en_pwm,
	input sig_pwm_1,
	input sig_pwm_2,
	input sync_ext,
	input conf_sync_comp,
	input conf_sync_carr,
	//output wire [15:0] carrier,
	output wire sync,
	output wire pwm_1a,
	output wire pwm_1b,
	output wire pwm_2a,
	output wire pwm_2b
);

	wire [15:0] carrier;
	wire [15:0] compare_1_masked;
	wire [15:0] compare_2_masked;
	wire [15:0] carrier_init_masked;
	wire [15:0] carrier_max_masked;

	pwm16bits_timernew TIMER1(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.carrier_max(carrier_max_masked),
		.carrier_init(carrier_init_masked),
		.carrier_initdir(carrier_initdir),
		.carrier_mode(carrier_mode),
		.sync_ext(sync_ext),
		.carrier(carrier)
		);

	pwm16bits_eventcount  EVTCNT1 
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.carrier_max(carrier_max_masked),
		.carrier(carrier),
		.event_count(event_count),
		.sync_mode(sync_mode),
		.sync(sync)
	);
	
	pwm16bits_mask  MASK1 
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.mask_in({compare_1,compare_2}),
		.conf_sync(conf_sync_comp),
		.intmask_int(sync),
		.intmask_ext(sync_ext),
		.mask_out({compare_1_masked,compare_2_masked})
	);
	
	pwm16bits_mask  MASK2 
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.mask_in({carrier_init,carrier_max}),
		.conf_sync(conf_sync_carr),
		.intmask_int(sync),
		.intmask_ext(sync_ext),
		.mask_out({carrier_init_masked,carrier_max_masked})
	);
	
	pwm16bits_compare2ch  CMP1 
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.carrier(carrier),
		.compare_1(compare_1_masked),
		.compare_2(compare_2_masked),
		.en_pwm(en_pwm),
		.sig_pwm_1(sig_pwm_1),
		.sig_pwm_2(sig_pwm_2),
		.pwm_1a(pwm_1a),
		.pwm_2a(pwm_2a),
		.pwm_1b(pwm_1b),
		.pwm_2b(pwm_2b)
	);

endmodule