`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 12:23:04 PM
// Design Name: 
// Module Name: TESTBENCH_pwm_16bits
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

module TESTBENCH_pwm_16bits();
//=============================================================
// Signal Definition
//=============================================================
    logic [`PWMCOUNT_WIDTH-1:0] period;
    logic [`PWMCOUNT_WIDTH-1:0] init_carr;
    logic [`PWMCOUNT_WIDTH-1:0] compare_1;
    logic [`PWMCOUNT_WIDTH-1:0] compare_2;
    logic [`PWMCOUNT_WIDTH-1:0] compare_3;
    logic [`PWMCOUNT_WIDTH-1:0] compare_4;
    logic [`DIVCLK_WIDTH-1:0] pwmclk_divider;
    logic [`DIVCLK_WIDTH-1:0] dtclk_divider;
    logic [`PWMCOUNT_WIDTH-1:0] carrier;
    logic [`INTCOUNT_WIDTH-1:0] event_count;
    _count_mode count_mode;
    _mask_mode mask_mode;
    _pwm_onoff pwm_onoff;
    _int_onoff int_onoff;
    _clkdiv_onoff pwmclkdiv_onoff;
    _clkdiv_onoff dtclkdiv_onoff;
    logic pwmout_1_A;
    logic pwmout_1_B;
    logic pwmout_2_A;
    logic pwmout_2_B;
    logic pwmout_3_A;
    logic pwmout_3_B;
    logic pwmout_4_A;
    logic pwmout_4_B;
    logic [`DTCOUNT_WIDTH-1:0] dtime_A;
    logic [`DTCOUNT_WIDTH-1:0] dtime_B;
    logic [`DTCOUNT_WIDTH-1:0] logic_A;
    logic [`DTCOUNT_WIDTH-1:0] logic_B;
    logic interrupt;

//=============================================================
//  Clock & Reset generator
//=============================================================

	bit clk = 1'b0;
	bit rst = 1'b1;

	always #1 clk = ~clk;
	always_ff @(posedge clk) rst <= 1'b0;
    
//=============================================================
//    Data Flow
//=============================================================
    initial begin 
        period ='d2000;
        init_carr ='d500;
        compare_1 ='d1000; 
        compare_2 ='d1000; 
        compare_3 ='d1000; 
        compare_4 ='d1000; 
        pwmclkdiv_onoff = CLKDIV_OFF;
        dtclkdiv_onoff = CLKDIV_OFF;
        pwmclk_divider ='d0;
        dtclk_divider ='d0;
        event_count ='d0;
        count_mode = COUNT_UPDOWN;
        mask_mode = MAX_MASK;
        pwm_onoff = PWM_OFF;
        int_onoff = INT_ON;
        
        dtime_A = 100;
        dtime_B = 100;
        logic_A = 0;
        logic_B = 0;
        
        repeat(1) @(posedge clk);       //One free clock cycle for the reset signal
        
        
        repeat(1250) @(posedge clk);
        pwm_onoff = PWM_ON;
        
        repeat(50000) @(posedge clk);
        compare_1 ='d667;
        
        repeat(16500) @(posedge clk);
        period ='d1500;
        
        repeat(18000) @(posedge clk);
        init_carr ='d600;
        
        repeat(18000) @(posedge clk);
        event_count ='d2;
        
        repeat(23000) @(posedge clk);
        pwmclkdiv_onoff = CLKDIV_ON;
        
    end 
//=============================================================
//    Design Under Test
//=============================================================


pwm_16bits DUT1(
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // INPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 
    // system clock
    .clk,
    // system reset
    .reset(rst),
    // PWM carrier period
    .period,
    // PWM initial carrier value
    .init_carr,
    // PWM compare register 1
    .compare_1,
    // PWM compare register 2
    .compare_2,
    // PWM compare register 3
    .compare_3,
    // PWM compare register 4
    .compare_4,
    // dead time value for pulse A
    .dtime_A,
    // dead time value for pulse B
    .dtime_B,
    // clock divider for PWM
    .pwmclk_divider,
    // clock driver for the dead time generator
    .dtclk_divider,
    // clock driver for the dead time generator
    .event_count,
    // count mode configuration bits
    .count_mode,
    // event mask mode configuration bits (defined and packaged in PKG_pwm.sv)
    .mask_mode,
    // ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    .pwm_onoff,
    // ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    .int_onoff,
    // pwm clock divider ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    .pwmclkdiv_onoff,
    // dead time clock divider ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    .dtclkdiv_onoff,
    // logic value of PWM output A
    .logic_A,
    // logic value of PWM output B
    .logic_B,
    // logic value of PWM output A
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // OUTPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 
    // PWM output signal 1 A
    .pwmout_1_A,
    // PWM output signal 1 B
    .pwmout_1_B,
    // PWM output signal 2 A
    .pwmout_2_A,
    // PWM output signal 2 B
    .pwmout_2_B,
    // PWM output signal 3 A
    .pwmout_3_A,
    // PWM output signal 3 B
    .pwmout_3_B,
    // PWM output signal 4 A
    .pwmout_4_A,
    // PWM output signal 4 B
    .pwmout_4_B,
    // interrupt output signal
    .interrupt
    );	
		
//=============================================================

endmodule