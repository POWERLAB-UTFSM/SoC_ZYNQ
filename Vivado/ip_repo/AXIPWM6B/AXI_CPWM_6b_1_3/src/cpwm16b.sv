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

module cpwm16b #(
	parameter PWMWIDTH = 16,
	parameter DTCOUNT_WIDTH = 8
	)
(
	input clk,
	input ce,
	input rst,
	//registers
	input [PWMWIDTH-1:0] carrier_max,
	input [PWMWIDTH-1:0] carrier_init,
	input [1:0] count_mode, //00=no_count; 01=up; 10=down; 11=up_down
	input [1:0] sync_mode,//00=no_count; 01=min_count; 10=max_count; 11=minmax_count
	input [3:0] event_count,
	input [PWMWIDTH-1:0] compare_1,
	input [PWMWIDTH-1:0] compare_2,
	input en_pwm,
	input sig_pwm_1,
	input sig_pwm_2,
	input [1:0] clkdiv_carr,
	input mask_on,
	input [DTCOUNT_WIDTH-1:0] deadtime,
	input dt_logic_1a,
	input dt_logic_1b,
	input dt_logic_2a,
	input dt_logic_2b,
	input dt_onoff,
	input [1:0] clkdiv_dtime,
	//outputs
	output wire sync,
	output wire pwm_1a,
	output wire pwm_1b,
	output wire pwm_2a,
	output wire pwm_2b
);

	wire [15:0] carrier;
	wire pwm_aux_1a;
	wire pwm_aux_1b;
	wire pwm_aux_2a;
	wire pwm_aux_2b;
	
	wire clk_carr;
	wire clk_dtime;

	wire [PWMWIDTH-1:0] mask_compare_1;
	wire [PWMWIDTH-1:0] mask_compare_2;
	wire [PWMWIDTH-1:0] mask_carrier_init;
	wire [PWMWIDTH-1:0] mask_carrier_max;

	cpwm16b_timer  TIMER1 
	(
		.clk(clk_carr),
		.ce(ce),
		.rst(rst),
		.carrier_max(mask_carrier_max),
		.carrier_init(mask_carrier_init),
		.enable(en_pwm),
		.count_mode(count_mode),
		.carrier(carrier)
	);

	cpwm16b_eventcount  EVTCNT1 
	(
		.clk(clk_carr),
		.ce(ce),
		.rst(rst),
		.carrier_max(mask_carrier_max),
		.carrier(carrier),
		.event_count(event_count),
		.eventcount_mode(sync_mode),
		.sync(sync)
	);
	
	cpwm16b_compare2ch  CMP1 
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.carrier(carrier),
		.compare_1(mask_compare_1),
		.compare_2(mask_compare_2),
		.en_pwm(en_pwm),
		.sig_pwm_1(sig_pwm_1),
		.sig_pwm_2(sig_pwm_2),
		.pwm_1a(pwm_aux_1a),
		.pwm_1b(pwm_aux_1b),
		.pwm_2a(pwm_aux_2a),
		.pwm_2b(pwm_aux_2b)
	);
	
	cpwm16b_deadtime DT1A
	(
		.clk(clk_dtime),
		.ce(ce),
		.rst(rst),
		.pwmin(pwm_aux_1a),
		.deadtime(deadtime),
		.dt_logic(dt_logic_1a),
		.pwm_onoff(en_pwm),
		.dt_onoff(dt_onoff),
		.pwmout(pwm_1a)
	);

	cpwm16b_deadtime DT1B
	(
		.clk(clk_dtime),
		.ce(ce),
		.rst(rst),
		.pwmin(pwm_aux_1b),
		.deadtime(deadtime),
		.dt_logic(dt_logic_1b),
		.pwm_onoff(en_pwm),
		.dt_onoff(dt_onoff),
		.pwmout(pwm_1b)
	);

	cpwm16b_deadtime DT2A
	(
		.clk(clk_dtime),
		.ce(ce),
		.rst(rst),
		.pwmin(pwm_aux_2a),
		.deadtime(deadtime),
		.dt_logic(dt_logic_2a),
		.pwm_onoff(en_pwm),
		.dt_onoff(dt_onoff),
		.pwmout(pwm_2a)
	);

	cpwm16b_deadtime DT2B
	(
		.clk(clk_dtime),
		.ce(ce),
		.rst(rst),
		.pwmin(pwm_aux_2b),
		.deadtime(deadtime),
		.dt_logic(dt_logic_2b),
		.pwm_onoff(en_pwm),
		.dt_onoff(dt_onoff),
		.pwmout(pwm_2b)
	);
	
	cpwm16b_clockdiv CD_CARR
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.div(clkdiv_carr),
		.clkout(clk_carr)
	);

	cpwm16b_clockdiv CD_DT
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.div(clkdiv_dtime),
		.clkout(clk_dtime)
	);

	cpwm16b_registerbuffer BUFF1
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.syncevent(sync),
		.mask_on(mask_on),
		.reg_in({compare_1,compare_2}),
		.reg_out({mask_compare_1,mask_compare_2})
	);

	cpwm16b_registerbuffer BUFF2
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.syncevent(sync),
		.mask_on(mask_on),
		.reg_in({carrier_max,carrier_init}),
		.reg_out({mask_carrier_max,mask_carrier_init})
	);

endmodule
