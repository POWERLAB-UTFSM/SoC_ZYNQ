`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Dr.-Ing. Alan Wilson
// 
// Create Date: 01/23/2023 11:33:04 PM
// Design Name: 
// Module Name: pwm_16bits
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// SystemVerilog module for a Pulse Width Modulation (PWM) generator for power electronic converters using 16 bits timer registers. Includes dead time, multiple event triggers and masked input register from events
// 
// Dependencies: 
//      Package definition:
//                          'PKG_pwm.sv'
//      Submodules:
//                          'carrier_gen_16bits.sv'
//                          'compare_16bits.sv'
//                          'dead_time.sv'
//                          'div_clock.sv'
//                          'register_mask_16bits.sv'
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// IMPORTED PACKAGES
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
import PKG_pwm::*;

module pwm_16bits  (
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // INPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 
    // system clock
    input clk,
    // system reset
    input reset,
    // PWM carrier period
    input [`PWMCOUNT_WIDTH-1:0] period,
    // PWM initial carrier value
    input [`PWMCOUNT_WIDTH-1:0] init_carr,
    // PWM compare register 1
    input [`PWMCOUNT_WIDTH-1:0] compare_1,
    // PWM compare register 2
    input [`PWMCOUNT_WIDTH-1:0] compare_2,
    // PWM compare register 3
    input [`PWMCOUNT_WIDTH-1:0] compare_3,
    // PWM compare register 4
    input [`PWMCOUNT_WIDTH-1:0] compare_4,
    // dead time value for pulse A
    input [`DTCOUNT_WIDTH-1:0] dtime_A,
    // dead time value for pulse B
    input [`DTCOUNT_WIDTH-1:0] dtime_B,
    // clock divider for PWM
    input [`DIVCLK_WIDTH-1:0] pwmclk_divider,
    // clock driver for the dead time generator
    input [`DIVCLK_WIDTH-1:0] dtclk_divider,
    // clock driver for the dead time generator
    input [`INTCOUNT_WIDTH-1:0] event_count,
    // count mode configuration bits
    input _count_mode count_mode,
    // event mask mode configuration bits (defined and packaged in PKG_pwm.sv)
    input _mask_mode mask_mode,
    // PWM ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    input _pwm_onoff pwm_onoff,
    // Interrupt ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    input _int_onoff int_onoff,
    // pwm clock divider ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    input _clkdiv_onoff pwmclkdiv_onoff,
    // dead time clock divider ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    input _clkdiv_onoff dtclkdiv_onoff,
    // logic value of PWM output A
    input logic_A,
    // logic value of PWM output B
    input logic_B,
    // logic value of PWM output A
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // OUTPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 
    // PWM output signal 1 A
    output logic pwmout_1_A,
    // PWM output signal 1 B
    output logic pwmout_1_B,
    // PWM output signal 2 A
    output logic pwmout_2_A,
    // PWM output signal 2 B
    output logic pwmout_2_B,
    // PWM output signal 3 A
    output logic pwmout_3_A,
    // PWM output signal 3 B
    output logic pwmout_3_B,
    // PWM output signal 4 A
    output logic pwmout_4_A,
    // PWM output signal 4 B
    output logic pwmout_4_B,
    // interrupt output signal
    output wire interrupt
    );
    
    //
    // Internal Signal definition
    //
    
    // masked period register from event mask handler (register_mask_16bits.sv) 
    logic [`PWMCOUNT_WIDTH-1:0] period__masked;
    // masked period register from event mask handler (register_mask_16bits.sv) 
    logic [`PWMCOUNT_WIDTH-1:0] register_concat__masked;
    // masked compare_1 register from event mask handler (register_mask_16bits.sv) 
    logic [`PWMCOUNT_WIDTH-1:0] compare_1__masked;
    // masked compare_1 register from event mask handler (register_mask_16bits.sv) 
    logic [`PWMCOUNT_WIDTH-1:0] compare_2__masked;
    // masked compare_1 register from event mask handler (register_mask_16bits.sv) 
    logic [`PWMCOUNT_WIDTH-1:0] compare_3__masked;
    // masked compare_1 register from event mask handler (register_mask_16bits.sv) 
    logic [`PWMCOUNT_WIDTH-1:0] compare_4__masked;
    // masked carrier initial value from event mask handler (register_mask_16bits.sv) 
    logic [`PWMCOUNT_WIDTH-1:0] init_carr__masked;
    //mask event trigger
    logic mask_event;
    //dead time clock
    logic dt_clk;
    //PWM carrier signal
    logic[`PWMCOUNT_WIDTH-1:0] carrier;
    //PWM master signal
    logic pwm_1;
    //PWM master signal
    logic pwm_2;
    //PWM master signal
    logic pwm_3;
    //PWM master signal
    logic pwm_4;
    //PWM clock
    logic pwm_clk;
    
    _pwm_onoff pwm_onoff__masked;
    _int_onoff int_onoff__masked;
    _mask_mode mask_mode__masked;
    _count_mode count_mode__masked;
    _clkdiv_onoff pwmclkdiv_onoff__masked;
    _clkdiv_onoff dtclkdiv_onoff__masked;
    logic[`PWMCOUNT_WIDTH-1:0] register_concat;

    //
    // Modules
    //
    
    configregpwm_concatenate CONCAT(
        .pwm_onoff,
        .int_onoff,
        .pwmclkdiv_onoff,
        .dtclkdiv_onoff,
        .mask_mode,
        .count_mode,
	    .register_concat
    );
    
    configregpwm_split SPLIT(
        .register_concat(register_concat__masked),
        .pwm_onoff(pwm_onoff__masked),
        .int_onoff(int_onoff__masked),
        .pwmclkdiv_onoff(pwmclkdiv_onoff__masked),
        .dtclkdiv_onoff(dtclkdiv_onoff__masked),
        .mask_mode(mask_mode__masked),
        .count_mode(count_mode__masked)
    );
    
    register_mask_16bits REG_CONFIG(
        .clk(clk),
        .reset,
        .mask_event,
        .pwm_onoff(pwm_onoff__masked),
        .reg_in(register_concat),
        .reg_out(register_concat__masked)        
    );
    
    register_mask_16bits REG_PERIOD(
        .clk(clk),
        .reset,
        .mask_event,
        .pwm_onoff(pwm_onoff__masked),
        .reg_in(period),
        .reg_out(period__masked)        
    );
    
    register_mask_16bits REG_COMP1(
        .clk(clk),
        .reset,
        .mask_event,
        .pwm_onoff(pwm_onoff__masked),
        .reg_in(compare_1),
        .reg_out(compare_1__masked)       
    );
    
    register_mask_16bits REG_COMP2(
        .clk(clk),
        .reset,
        .mask_event,
        .pwm_onoff(pwm_onoff__masked),
        .reg_in(compare_2),
        .reg_out(compare_2__masked)       
    );
    
    register_mask_16bits REG_COMP3(
        .clk(clk),
        .reset,
        .mask_event,
        .pwm_onoff(pwm_onoff__masked),
        .reg_in(compare_3),
        .reg_out(compare_3__masked)       
    );
    
    register_mask_16bits REG_COMP4(
        .clk(clk),
        .reset,
        .mask_event,
        .pwm_onoff(pwm_onoff__masked),
        .reg_in(compare_4),
        .reg_out(compare_4__masked)       
    );
    
    register_mask_16bits REG_CARR(
        .clk(clk),
        .reset,
        .mask_event,
        .pwm_onoff(pwm_onoff__masked),
        .reg_in(init_carr),
        .reg_out(init_carr__masked)       
    );
    
    div_clock PWMCLK(
        .clk,
        .reset,
        .divider(pwmclk_divider),
        .pwm_onoff(pwm_onoff__masked),
        .clkdiv_onoff(pwmclkdiv_onoff),
        .div_clk(pwm_clk)
    );
    
    carrier_gen_16bits CARR1(
        .clk(pwm_clk),
        .reset,
        .period(period__masked),
        .init_carr(init_carr__masked),
        .count_mode(count_mode__masked),
        .mask_mode(mask_mode__masked),
        .pwm_onoff(pwm_onoff__masked),
        .carrier,
        .mask_event
    );
    
    compare_16bits COMP1(
        .carrier,
        .compare(compare_1__masked),
        .pwm_onoff(pwm_onoff__masked),
        .pwm(pwm_1)
    );
    
    compare_16bits COMP2(
        .carrier,
        .compare(compare_2__masked),
        .pwm_onoff(pwm_onoff__masked),
        .pwm(pwm_2)
    );
    
    compare_16bits COMP3(
        .carrier,
        .compare(compare_3__masked),
        .pwm_onoff(pwm_onoff__masked),
        .pwm(pwm_3)
    );
    
    compare_16bits COMP4(
        .carrier,
        .compare(compare_4__masked),
        .pwm_onoff(pwm_onoff__masked),
        .pwm(pwm_4)
    );
    
    div_clock DTCLK(
        .clk,
        .reset,
        .divider(dtclk_divider),
        .pwm_onoff(pwm_onoff__masked),
        .clkdiv_onoff(dtclkdiv_onoff),
        .div_clk(dt_clk)
    );
    
    dead_time DT1(
       .clk(dt_clk),
	   .reset,
	   .pwm(pwm_1),
	   .dtime_A,
	   .dtime_B,
	   .logic_A,
	   .logic_B,
	   .pwm_onoff(pwm_onoff__masked),
	   .pwmout_A(pwmout_1_A),
	   .pwmout_B(pwmout_1_B)
    );
    
    dead_time DT2(
       .clk(dt_clk),
	   .reset,
	   .pwm(pwm_2),
	   .dtime_A,
	   .dtime_B,
	   .logic_A,
	   .logic_B,
	   .pwm_onoff(pwm_onoff__masked),
	   .pwmout_A(pwmout_2_A),
	   .pwmout_B(pwmout_2_B)
    );
    
    dead_time DT3(
       .clk(dt_clk),
	   .reset,
	   .pwm(pwm_3),
	   .dtime_A,
	   .dtime_B,
	   .logic_A,
	   .logic_B,
	   .pwm_onoff(pwm_onoff__masked),
	   .pwmout_A(pwmout_3_A),
	   .pwmout_B(pwmout_3_B)
    );
    
    dead_time DT4(
       .clk(dt_clk),
	   .reset,
	   .pwm(pwm_4),
	   .dtime_A,
	   .dtime_B,
	   .logic_A,
	   .logic_B,
	   .pwm_onoff(pwm_onoff__masked),
	   .pwmout_A(pwmout_4_A),
	   .pwmout_B(pwmout_4_B)
    );
    
    interrupt_counter INT1(
       .clk,
	   .reset,
	   .mask_event,
	   .pwm_onoff(pwm_onoff__masked),
	   .int_onoff(int_onoff__masked),
	   .event_count,
	   .interrupt
    );
    

endmodule
