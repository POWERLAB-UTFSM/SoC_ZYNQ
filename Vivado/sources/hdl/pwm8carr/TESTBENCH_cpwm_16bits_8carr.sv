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
    logic [`PWM_WIDTH-1:0][`PWMCOUNT_WIDTH-1:0] period_c;
    logic [`PWM_WIDTH-1:0][`PWMCOUNT_WIDTH-1:0] compare_c;
    logic [`PWM_WIDTH-1:0][`PWMCOUNT_WIDTH-1:0] initcarr_c;
    logic [`PWM_WIDTH-1:0][`DTCOUNT_WIDTH-1:0] dtime_A_c;
    logic [`PWM_WIDTH-1:0][`DTCOUNT_WIDTH-1:0] dtime_B_c;
    logic [`PWM_WIDTH-1:0][`EVTCOUNT_WIDTH-1:0] eventcount_c;
    _count_mode [`PWM_WIDTH-1:0] countmode_c;
    _mask_mode  [`PWM_WIDTH-1:0] maskmode_c;
    _carr_onoff [`PWM_WIDTH-1:0] carr_onoff_c;
    _dt_onoff  [`PWM_WIDTH-1:0] dt_onoff_c;
    logic [`PWM_WIDTH-1:0] [2:0] carrsel_c;
    logic [`PWM_WIDTH-1:0] pwmout_A_c;
    logic [`PWM_WIDTH-1:0] pwmout_B_c;
    logic [`PWM_WIDTH-1:0] logic_A_c;
    logic [`PWM_WIDTH-1:0] logic_B_c;
    _clkdiv_onoff [`PWM_WIDTH-1:0] carrclkdiv_onoff_c;
    _clkdiv_onoff [`PWM_WIDTH-1:0] dtclkdiv_onoff_c;

    logic interrupt;
    logic [7:0] interrupt_matrix;
    
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
        interrupt_matrix= 8'b00000001;
        
        for (i=0;i<8;i=i+1) begin
            carr_onoff_c[i] = CARR_ON;
            dt_onoff_c[i] = DT_ON;
            countmode_c[i] = COUNT_UPDOWN;
            maskmode_c[i] = MIN_MASK;
            carrsel_c[i] = 'd0;
            logic_A_c[i]=1;
            logic_B_c[i]=1;
            period_c ='d2000;
            eventcount_c[i]='d0;
            compare_c[i] ='d500;
            initcarr_c[i] ='d0;
            dtime_A_c[i] ='d0;
            dtime_B_c[i] ='d0;
            carrclkdiv_onoff_c[i]=CLKDIV_OFF;
            dtclkdiv_onoff_c[i]=CLKDIV_OFF;
        end
        
        repeat(1) @(posedge clk);
               //One free clock cycle for the reset signal
        repeat(1) @(posedge clk);
        pwm_onoff = PWM_ON;
            
        repeat(8040) @(posedge clk);
        period_c[0] = 'd0;
        
        repeat(8040) @(posedge clk);
        period_c[0] = 'd1000;
        
        repeat(8040) @(posedge clk);
        countmode_c[0] = COUNT_DOWN;
        
        repeat(8040) @(posedge clk);
        countmode_c[0] = COUNT_UP;
        
        repeat(8040) @(posedge clk);
        countmode_c[0] = COUNT_UP;
        
        repeat(8040) @(posedge clk);
        initcarr_c[0] = 'd5000;
        
        repeat(8040) @(posedge clk);
        initcarr_c[0] = 'd600;
        
        repeat(8040) @(posedge clk);
        pwm_onoff = PWM_OFF;
        
        repeat(8040) @(posedge clk);
        pwm_onoff = PWM_ON;
        
        repeat(8040) @(posedge clk);
        eventcount_c[0] = 1;
        
        repeat(8040) @(posedge clk);
        maskmode_c[0] = NO_MASK;
        //period ='d1500;
        
        repeat(8040) @(posedge clk);
        dt_onoff_c[0] = DT_OFF;
        
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
    .carrclkdiv_onoff_c(carrclkdiv_onoff_c),
    .dtclkdiv_onoff_c(dtclkdiv_onoff_c),
    .period_c(period_c),
    .eventcount_c(eventcount_c),
    .initcarr_c(initcarr_c),
    .compare_c(compare_c),
    .countmode_c(countmode_c),
    .carrsel_c(carrsel_c),
    .maskmode_c(maskmode_c),
    .carr_onoff_c(carr_onoff_c),
    .dt_onoff_c(dt_onoff_c),
    .dtime_A_c(dtime_A_c),
    .dtime_B_c(dtime_A_c),
    .logic_A_c(logic_A_c),
    .logic_B_c(logic_B_c),
    .pwmout_A_c(pwmout_A_c),
    .pwmout_B_c(pwmout_B_c),
    .interrupt(interrupt)
);
		
//=============================================================

endmodule