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
    logic [`PWMCOUNT_WIDTH*`PWM_WIDTH-1:0] period_x;
    logic [`PWMCOUNT_WIDTH*`PWM_WIDTH-1:0] initcarr_x;
    logic [`PWMCOUNT_WIDTH*`PWM_WIDTH-1:0] compare_x;
    logic [`PWMCOUNT_WIDTH-1:0] initcarr_c [`PWM_WIDTH-1:0];
    logic [`DTCOUNT_WIDTH*`PWM_WIDTH-1:0] dtime_A_x ;
    logic [`DTCOUNT_WIDTH*`PWM_WIDTH-1:0] dtime_B_x ;
    logic [`EVTCOUNT_WIDTH*`PWM_WIDTH-1:0] eventcount_x;
    logic [$bits(_count_mode)*`PWM_WIDTH-1:0] countmode_x;
    logic [$bits(_mask_mode)*`PWM_WIDTH-1:0] maskmode_x;
    logic [$bits(_carr_onoff)*`PWM_WIDTH-1:0] carr_onoff_x;
    logic [$bits(_dt_onoff)*`PWM_WIDTH-1:0] dt_onoff_x;
    logic [3*`PWM_WIDTH-1:0] carrsel_x;
    logic [`PWM_WIDTH-1:0] pwmout_A_x;
    logic [`PWM_WIDTH-1:0] pwmout_B_x;
    logic [`PWM_WIDTH-1:0] logic_A_x;
    logic [`PWM_WIDTH-1:0] logic_B_x;
    logic [1*`PWM_WIDTH-1:0] carrclkdiv_onoff_x;
    logic [1*`PWM_WIDTH-1:0] dtclkdiv_onoff_x;

    logic interrupt;
    logic [7:0] interrupt_matrix ;
    
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
    integer i;
    initial begin 
        
        pwm_onoff = PWM_OFF;
        int_onoff = INT_ON;
        interrupt_matrix[0]= 1'b1;
        interrupt_matrix[1]= 1'b0;
        

        carr_onoff_x[0] = 1'(CARR_ON);
        dt_onoff_x[0] = 1'(DT_ON);
        countmode_x[1:0] = 2'(COUNT_UPDOWN);
        maskmode_x[1:0] = 2'(MINMAX_MASK);
        carrsel_x[2:0] = 'd0;
        logic_A_x[0]=1;
        logic_B_x[0]=1;
        period_x[`PWMCOUNT_WIDTH-1:0] = 'd2000;
        initcarr_x[`PWMCOUNT_WIDTH-1:0] = 'd1000;
        compare_x[`PWMCOUNT_WIDTH-1:0] = 'd500;
        eventcount_x[`EVTCOUNT_WIDTH-1:0]='d0;
        dtime_A_x[`DTCOUNT_WIDTH-1:0] ='d0;
        dtime_B_x[`DTCOUNT_WIDTH-1:0] ='d0;
        carrclkdiv_onoff_x[0]=CLKDIV_OFF;
        dtclkdiv_onoff_x[0]=CLKDIV_OFF;
  
        
        repeat(1) @(posedge clk);
               //One free clock cycle for the reset signal
        repeat(1) @(posedge clk);
        pwm_onoff = PWM_ON;
            
        repeat(8040) @(posedge clk);
        period_x[`PWMCOUNT_WIDTH-1:0] = 'd0;
        
        repeat(8040) @(posedge clk);
        period_x[`PWMCOUNT_WIDTH-1:0] = 'd1000;
        
        repeat(8040) @(posedge clk);
        countmode_x[1:0] = 2'(COUNT_DOWN);
        
        repeat(8040) @(posedge clk);
        countmode_x[1:0] = 2'(COUNT_UP);
        
        repeat(8040) @(posedge clk);
        countmode_x[1:0] = 2'(COUNT_UP);
        
        repeat(8040) @(posedge clk);
        initcarr_x[`PWMCOUNT_WIDTH-1:0] = 'd5000;
        
        repeat(8040) @(posedge clk);
        initcarr_x[`PWMCOUNT_WIDTH-1:0] = 'd600;
        
        repeat(8040) @(posedge clk);
        pwm_onoff = PWM_OFF;
        
        repeat(8040) @(posedge clk);
        pwm_onoff = PWM_ON;
        
        repeat(8040) @(posedge clk);
        eventcount_x[`EVTCOUNT_WIDTH-1:0]='d1;
        
        repeat(8040) @(posedge clk);
        maskmode_x = 2'(NO_MASK);
        //period ='d1500;
        
        repeat(8040) @(posedge clk);
        dt_onoff_x[0] = 1'(DT_OFF);
        
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
    .interrupt_matrix(interrupt_matrix),
    .carrclkdiv_onoff_x(carrclkdiv_onoff_x),
    .dtclkdiv_onoff_x(dtclkdiv_onoff_x),
    .period_x(period_x),
    .eventcount_x(eventcount_x),
    .initcarr_x(initcarr_x),
    .compare_x(compare_x),
    .countmode_x(countmode_x),
    .carrsel_x(carrsel_x),
    .maskmode_x(maskmode_x),
    .carr_onoff_x(carr_onoff_x),
    .dt_onoff_x(dt_onoff_x),
    .dtime_A_x(dtime_A_x),
    .dtime_B_x(dtime_B_x),
    .logic_A_x(logic_A_x),
    .logic_B_x(logic_B_x),
    .pwmout_A_x(pwmout_A_x),
    .pwmout_B_x(pwmout_B_x),
    .interrupt(interrupt)
);
		
//=============================================================

endmodule