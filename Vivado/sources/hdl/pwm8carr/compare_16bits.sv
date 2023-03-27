`timescale 10ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 01:18:08 AM
// Design Name: 
// Module Name: compare_16bits
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

module compare_16bits (
    // system clock
    input clk,
    // system reset
    input reset,
    input [`PWMCOUNT_WIDTH-1:0] carrier,
    input [`PWMCOUNT_WIDTH-1:0] compare,
    input [`PWM_WIDTH-1:0] carrsel,
    input [`DTCOUNT_WIDTH-1:0] dtime_A,
    input [`DTCOUNT_WIDTH-1:0] dtime_B,
    input [`DIVCLK_WIDTH-1:0] dtclkdivider,
    input logic_A,
	input logic_B,
    input _pwm_onoff pwm_onoff,
    input _dt_onoff dt_onoff,
    input _clkdiv_onoff dtclkdiv_onoff,
    input maskevent,
    output pwmout_A,
    output pwmout_B,
    output [`PWM_WIDTH-1:0] carrsel_out
    );
    
    logic [`PWMCOUNT_WIDTH-1:0] compare__masked;
    logic [`DTCOUNT_WIDTH-1:0] dtime_A__masked;
    logic [`DTCOUNT_WIDTH-1:0] dtime_B__masked;
    logic [`DIVCLK_WIDTH-1:0] dtclkdivider__masked;
    logic logic_A__masked;
    logic logic_B__masked;
    _clkdiv_onoff dtclkdiv_onoff__masked;
    _pwm_onoff pwm_onoff__masked;
    _dt_onoff dt_onoff__masked;
    logic pwm;
    
    register_mask_16bits REGMASK_COMP(
        //.clk(clk),
        .reset(reset),
        .maskevent(maskevent),
        .pwm_onoff(pwm_onoff),
        .reg_in(compare),
        .reg_out(compare__masked)        
    );
    
    register_mask_16bits REGMASK_DT(
        //.clk(clk),
        .reset(reset),
        .maskevent(maskevent),
        .pwm_onoff(pwm_onoff),
        .reg_in({dtime_A,dtime_B}),
        .reg_out({dtime_A__masked,dtime_B__masked})        
    );
    
    register_mask_16bits REGMASK_CONF(
        //.clk(clk),
        .reset(reset),
        .maskevent(maskevent),
        .pwm_onoff(pwm_onoff),
        .reg_in({logic_A,logic_B,dtclkdiv_onoff,dtclkdivider,dt_onoff,carrsel}),
        .reg_out({logic_A__masked,logic_B__masked,dtclkdiv_onoff__masked,dtclkdivider__masked,dt_onoff__masked,carrsel_out})        
    );
    
    dead_time DT(
        //.clk(dt_clk),
        .clk(clk),
        .reset(reset),
        .pwm(pwm),
        .dtime_A(dtime_A__masked),
        .dtime_B(dtime_B__masked),
        .logic_A(logic_A__masked),
        .logic_B(logic_B__masked),
        .dt_onoff(dt_onoff__masked),
        .pwm_onoff(pwm_onoff),
        .pwmout_A(pwmout_A),
        .pwmout_B(pwmout_B)
    );
    
    /*div_clock DIVCLK_PWM(
        .clk,
        .reset,
        .divider(dtclkdivider__masked),
        .pwm_onoff(pwm_onoff),
        .clkdiv_onoff(dtclkdiv_onoff__masked),
        .div_clk(dt_clk)
    );*/
    
    //-------------------
    // PWM
    //-------------------
    always_latch begin
        if(carrier >= compare__masked) begin
            pwm = 'd0 && pwm_onoff;  
        end
        else begin
            pwm = 'd1 && pwm_onoff; 
        end
    end
        
endmodule
