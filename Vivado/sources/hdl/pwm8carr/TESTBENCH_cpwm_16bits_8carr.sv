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

module TESTBENCH_cpwm_16bits_8carr();
//=============================================================
// Signal Definition
//=============================================================
    logic [`PWMCOUNT_WIDTH-1:0] period_c1;
    logic [`PWMCOUNT_WIDTH-1:0] compare_c1;
    logic [`PWMCOUNT_WIDTH-1:0] initcarr_c1;
    logic [`DTCOUNT_WIDTH-1:0] dtime_A_c1;
    logic [`DTCOUNT_WIDTH-1:0] dtime_B_c1;
    logic [`EVTCOUNT_WIDTH-1:0] eventcount_c1;
    _count_mode countmode_c1;
    _mask_mode maskmode_c1;
    _carr_onoff carr_onoff_c1;
    logic [2:0] carrsel_c1;
    logic pwmout_A_c1;
    logic pwmout_B_c1;
    logic logic_A_c1;
    logic logic_B_c1;


    logic interrupt;
    _pwm_onoff pwm_onoff;
    _int_onoff int_onoff;
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
        period_c1 ='d2000;
        eventcount_c1='d0;
        compare_c1 ='d500;
        initcarr_c1 ='d0;
        dtime_A_c1 ='d0;
        pwm_onoff = PWM_OFF;
        int_onoff = INT_ON;
        carr_onoff_c1 = CARR_ON;
        countmode_c1 = COUNT_UPDOWN;
        maskmode_c1 = MIN_MASK;
        carrsel_c1 = 'd0;
        logic_A_c1=1;
        logic_B_c1=1;
        
        repeat(1) @(posedge clk);
               //One free clock cycle for the reset signal
        repeat(1) @(posedge clk);
        pwm_onoff = PWM_ON;
            
        repeat(8040) @(posedge clk);
        period_c1 = 'd0;
        
        repeat(8040) @(posedge clk);
        period_c1 = 'd1000;
        
        repeat(8040) @(posedge clk);
        countmode_c1 = COUNT_DOWN;
        
        repeat(8040) @(posedge clk);
        countmode_c1 = COUNT_UP;
        
        repeat(8040) @(posedge clk);
        countmode_c1 = COUNT_UP;
        
        repeat(8040) @(posedge clk);
        initcarr_c1 = 'd5000;
        
        repeat(8040) @(posedge clk);
        initcarr_c1 = 'd600;
        
        repeat(8040) @(posedge clk);
        pwm_onoff = PWM_OFF;
        
        repeat(8040) @(posedge clk);
        pwm_onoff = PWM_ON;
        
        repeat(8040) @(posedge clk);
        eventcount_c1 = 1;
        
        repeat(8040) @(posedge clk);
        maskmode_c1 = NO_MASK;
        //period ='d1500;
        
        repeat(18000) @(posedge clk);
        //init_carr ='d600;
        
        repeat(18000) @(posedge clk);
        //event_count ='d2;
        
        repeat(23000) @(posedge clk);
        //pwmclkdiv_onoff = CLKDIV_ON;
        
        repeat(18000) @(posedge clk);
        //period = 'd0;
        
        repeat(18000) @(posedge clk);
        //period = 'd2000;
        
    end 
//=============================================================
//    Design Under Test
//=============================================================
cpwm_16bits_8carr DUT1 (
    .clk,
    .reset(rst),
    .pwm_onoff(pwm_onoff),
    .int_onoff(int_onoff),
    .period_c1(period_c1),
    .eventcount_c1(eventcount_c1),
    .initcarr_c1(initcarr_c1),
    .compare_c1(compare_c1),
    .countmode_c1(countmode_c1),
    .carrsel_c1(carrsel_c1),
    .maskmode_c1(maskmode_c1),
    .carr_onoff_c1(carr_onoff_c1),
    .dtime_A_c1(dtime_A_c1),
    .dtime_B_c1(dtime_A_c1),
    .logic_A_c1(logic_A_c1),
    .logic_B_c1(logic_B_c1),
    .pwmout_A_c1(pwmout_A_c1),
    .pwmout_B_c1(pwmout_B_c1),
    .interrupt(interrupt)
);
		
//=============================================================

endmodule