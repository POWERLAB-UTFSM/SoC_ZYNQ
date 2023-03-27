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
    input [`PWMCOUNT_WIDTH-1:0] carrier_master,
    input [`PWMCOUNT_WIDTH-1:0] compare,
    input _carr_sel carrsel,
    input [`DTCOUNT_WIDTH-1:0] dtime_A,
    input [`DTCOUNT_WIDTH-1:0] dtime_B,
    //input [`DIVCLK_WIDTH-1:0] dtclkdivider,
    input logic_A,
	input logic_B,
    input _pwm_onoff pwm_onoff,
    input _dt_onoff dt_onoff,
    //input _clkdiv_onoff dtclkdiv_onoff,
    input maskevent,
    output wire pwmout_A,
    output wire pwmout_B
    //output [`PWM_WIDTH-1:0] carrsel_out
    );
    
    logic [`PWMCOUNT_WIDTH-1:0] compare__masked;
    logic [`DTCOUNT_WIDTH-1:0] dtime_A__masked;
    logic [`DTCOUNT_WIDTH-1:0] dtime_B__masked;
    //logic [`DIVCLK_WIDTH-1:0] dtclkdivider__masked;
    logic logic_A__masked;
    logic logic_B__masked;
    //_clkdiv_onoff dtclkdiv_onoff__masked;
    _pwm_onoff pwm_onoff__masked;
    _dt_onoff dt_onoff__masked;
    wire pwm;
    logic pwmin_A;
    logic pwmin_B;
    
    register_mask_16bits REGMASK_COMP(
        .clk(clk),
        .reset(reset),
        .maskevent(maskevent),
        .pwm_onoff(pwm_onoff),
        .reg_in(compare),
        .reg_out(compare__masked)        
    );
    
    register_mask_16bits REGMASK_DT(
        .clk(clk),
        .reset(reset),
        .maskevent(maskevent),
        .pwm_onoff(pwm_onoff),
        .reg_in({dtime_A,dtime_B}),
        .reg_out({dtime_A__masked,dtime_B__masked})        
    );
    
    register_mask_16bits REGMASK_CONF(
        .clk(clk),
        .reset(reset),
        .maskevent(maskevent),
        .pwm_onoff(pwm_onoff),
        .reg_in({logic_A,logic_B,dt_onoff}),
        .reg_out({logic_A__masked,logic_B__masked,dt_onoff__masked})        
    );
    
    comparator_16bits COMP1(
        .clk(clk),
        .carrier(carrier),
        .carrier_master(carrier_master),
        .carrsel(carrsel),
        .compare(compare__masked),
        .pwm_onoff(pwm_onoff),
        .dt_onoff(dt_onoff__masked),
        .pwmout_A(pwmin_A),
        .pwmout_B(pwmin_B)
    );
    
    deadtime_single DT_A(
        .clk,
        .reset,
        .pwmin_X(pwmin_A),
        .dtime_X(dtime_A__masked),
        .logic_X(logic_A__masked),
        .pwm_onoff(pwm_onoff),
        .dt_onoff(dt_onoff__masked),
        .pwmout_X(pwmout_A)
    );
    
    deadtime_single DT_B(
        .clk,
        .reset,
        .pwmin_X(pwmin_B),
        .dtime_X(dtime_B__masked),
        .logic_X(logic_B__masked),
        .pwm_onoff(pwm_onoff),
        .dt_onoff(dt_onoff__masked),
        .pwmout_X(pwmout_B)
    );
    
    /*dead_time DT(
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
    );*/
    
    
    
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
    /*always_comb begin
        if(carrier >= compare__masked) begin
            pwm = 'd0 && pwm_onoff;  
        end
        else begin
            pwm = 'd1 && pwm_onoff; 
        end
    end*/
        
endmodule
