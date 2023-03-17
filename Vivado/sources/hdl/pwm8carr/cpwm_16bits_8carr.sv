`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Dr.-Ing. Alan Wilson
// 
// Create Date: 01/23/2023 11:33:04 PM
// Design Name: 
// Module Name: pwm_16bits_8carr
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

module pwm_16bits_8carr (
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // Signal INPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// ------------------------------------------------
	// common clock and reset
	// ------------------------------------------------
    // system clock
    input clk,
    // system reset
    input reset,
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // Register INPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// ------------------------------------------------
	// periods (8 x 16 bits)
	// ------------------------------------------------
    // PWM period  carrier 1
    input [`PWMCOUNT_WIDTH-1:0] period_c1,
	// PWM period  carrier 2
    input [`PWMCOUNT_WIDTH-1:0] period_c2,
	// PWM period  carrier 3
    input [`PWMCOUNT_WIDTH-1:0] period_c3,
	// PWM period  carrier 4
    input [`PWMCOUNT_WIDTH-1:0] period_c4,
	// PWM period  carrier 5
    input [`PWMCOUNT_WIDTH-1:0] period_c5,
	// PWM period  carrier 6
    input [`PWMCOUNT_WIDTH-1:0] period_c6,
	// PWM period  carrier 7
    input [`PWMCOUNT_WIDTH-1:0] period_c7,
	// PWM period  carrier 8
    input [`PWMCOUNT_WIDTH-1:0] period_c8,
	// ------------------------------------------------
	// initial carrier values (8 x 16 bits)
	// ------------------------------------------------
    // PWM initial value carrier 1
    input [`PWMCOUNT_WIDTH-1:0] initcarr_c1,
	// PWM initial value carrier 2
    input [`PWMCOUNT_WIDTH-1:0] initcarr_c2,
	// PWM initial value carrier 3
    input [`PWMCOUNT_WIDTH-1:0] initcarr_c3,
	// PWM initial value carrier 4
    input [`PWMCOUNT_WIDTH-1:0] initcarr_c4,
	// PWM initial value carrier 5
    input [`PWMCOUNT_WIDTH-1:0] initcarr_c5,
	// PWM initial value carrier 6
    input [`PWMCOUNT_WIDTH-1:0] initcarr_c6,
	// PWM initial value carrier 7
    input [`PWMCOUNT_WIDTH-1:0] initcarr_c7,
	// PWM initial value carrier 8
    input [`PWMCOUNT_WIDTH-1:0] initcarr_c8,
	// ------------------------------------------------
	// compare registers 1 (8 x 16 bits)
	// ------------------------------------------------
    // PWM compare register 1 carrier 1
    input [`PWMCOUNT_WIDTH-1:0] compare_c1,
	// PWM compare register 1 carrier 1
    input [`PWMCOUNT_WIDTH-1:0] compare_c2,
	// PWM compare register 1 carrier 1
    input [`PWMCOUNT_WIDTH-1:0] compare_c3,
	// PWM compare register 1 carrier 1
    input [`PWMCOUNT_WIDTH-1:0] compare_c4,
	// PWM compare register 1 carrier 1
    input [`PWMCOUNT_WIDTH-1:0] compare_c5,
	// PWM compare register 1 carrier 1
    input [`PWMCOUNT_WIDTH-1:0] compare_c6,
	// PWM compare register 1 carrier 1
    input [`PWMCOUNT_WIDTH-1:0] compare_c7,
	// PWM compare register 1 carrier 1
    input [`PWMCOUNT_WIDTH-1:0] compare_c8,
	// ------------------------------------------------
	// dead time register A (8 x 8 bits)
	// ------------------------------------------------
    // dead time value for pulse A compare 1
    input [`DTCOUNT_WIDTH-1:0] dtime_A_c1,
	// dead time value for pulse A compare 2
    input [`DTCOUNT_WIDTH-1:0] dtime_A_c2,
	// dead time value for pulse A compare 3
    input [`DTCOUNT_WIDTH-1:0] dtime_A_c3,
	// dead time value for pulse A compare 4
    input [`DTCOUNT_WIDTH-1:0] dtime_A_c4,
	// dead time value for pulse A compare 5
    input [`DTCOUNT_WIDTH-1:0] dtime_A_c5,
	// dead time value for pulse A compare 6
    input [`DTCOUNT_WIDTH-1:0] dtime_A_c6,
	// dead time value for pulse A compare 7
    input [`DTCOUNT_WIDTH-1:0] dtime_A_c7,
	// dead time value for pulse A compare 8
    input [`DTCOUNT_WIDTH-1:0] dtime_A_c8,
	// ------------------------------------------------
	// dead time register B (8 x 8 bits)
	// ------------------------------------------------
    // dead time value for pulse B compare 1
    input [`DTCOUNT_WIDTH-1:0] dtime_B_c1,
	// dead time value for pulse B compare 2
    input [`DTCOUNT_WIDTH-1:0] dtime_B_c2,
	// dead time value for pulse B compare 3
    input [`DTCOUNT_WIDTH-1:0] dtime_B_c3,
	// dead time value for pulse B compare 4
    input [`DTCOUNT_WIDTH-1:0] dtime_B_c4,
	// dead time value for pulse B compare 5
    input [`DTCOUNT_WIDTH-1:0] dtime_B_c5,
	// dead time value for pulse B compare 6
    input [`DTCOUNT_WIDTH-1:0] dtime_B_c6,
	// dead time value for pulse B compare 7
    input [`DTCOUNT_WIDTH-1:0] dtime_B_c7,
	// dead time value for pulse B compare 8
    input [`DTCOUNT_WIDTH-1:0] dtime_B_c8,
	// ------------------------------------------------
	// GENERAL module clock dividers (2 x 5 bits)
	// ------------------------------------------------
    // clock divider for PWM
    input [`DIVCLK_WIDTH-1:0] pwmclk_divider,
    // clock driver for the dead time generator
    input [`DIVCLK_WIDTH-1:0] dtclk_divider,
	// ------------------------------------------------
	// on-off clock dividers (2 x 1 bits)
	// ------------------------------------------------
	// pwm clock divider ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    input _clkdiv_onoff pwmclkdiv_onoff,
    // dead time clock divider ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    input _clkdiv_onoff dtclkdiv_onoff,
	// ------------------------------------------------
	// event counters (8 x 3 bits)
	// ------------------------------------------------
    // event counter carrier 1
    input [`INTCOUNT_WIDTH-1:0] eventcount_c1,
	// event counter carrier 2
    input [`INTCOUNT_WIDTH-1:0] eventcount_c2,
	// event counter carrier 3
    input [`INTCOUNT_WIDTH-1:0] eventcount_c3,
	// event counter carrier 4
    input [`INTCOUNT_WIDTH-1:0] eventcount_c4,
	// event counter carrier 5
    input [`INTCOUNT_WIDTH-1:0] eventcount_c5,
	// event counter carrier 6
    input [`INTCOUNT_WIDTH-1:0] eventcount_c6,
	// event counter carrier 7
    input [`INTCOUNT_WIDTH-1:0] eventcount_c7,
	// event counter carrier 8
    input [`INTCOUNT_WIDTH-1:0] eventcount_c8,
	// ------------------------------------------------
	// count mode configuration (8 x 2 bits)
	// ------------------------------------------------
    // count mode carrier 1
    input _count_mode countmode_c1,
	// count mode carrier 2
    input _count_mode countmode_c2,
	// count mode carrier 3
    input _count_mode countmode_c3,
	// count mode carrier 4
    input _count_mode countmode_c4,
	// count mode carrier 5
    input _count_mode countmode_c5,
	// count mode carrier 6
    input _count_mode countmode_c6,
	// count mode carrier 7
    input _count_mode countmode_c7,
	// count mode carrier 8
    input _count_mode countmode_c8,
	// ------------------------------------------------
	// mask mode configuration (8 x 2 bits)
	// ------------------------------------------------
    // event mask mode carrier 1
    input _mask_mode maskmode_c1,
	// event mask mode carrier 2
    input _mask_mode maskmode_c2,
	// event mask mode carrier 3
    input _mask_mode maskmode_c3,
	// event mask mode carrier 4
    input _mask_mode maskmode_c4,
	// event mask mode carrier 5
    input _mask_mode maskmode_c5,
	// event mask mode carrier 6
    input _mask_mode maskmode_c6,
	// event mask mode carrier 7
    input _mask_mode maskmode_c7,
	// event mask mode carrier 8
    input _mask_mode maskmode_c8,
	// ------------------------------------------------
	// on-off counter carrier (8 x 2 bits)
	// ------------------------------------------------
	// Carrier count ON-OFF state carrier 1
    input _carr_onoff carr_onoff_c1,
	// Carrier count ON-OFF state carrier 2
    input _carr_onoff carr_onoff_c2,
	// Carrier count ON-OFF state carrier 3
    input _carr_onoff carr_onoff_c3,
	// Carrier count ON-OFF state carrier 4
    input _carr_onoff carr_onoff_c4,
	// Carrier count ON-OFF state carrier 5
    input _carr_onoff carr_onoff_c5,
	// Carrier count ON-OFF state carrier 6
    input _carr_onoff carr_onoff_c6,
	// Carrier count ON-OFF state carrier 7
    input _carr_onoff carr_onoff_c7,
	// Carrier count ON-OFF state carrier 8
    input _carr_onoff carr_onoff_c8,
    // PWM ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    input _pwm_onoff pwm_onoff,
    // Interrupt ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    input _int_onoff int_onoff,
    // ------------------------------------------------
	// logic value of output A (8 x 1 bits)
	// ------------------------------------------------
    // logic value of PWM output A carrier 1
    input logic_A_c1,
    // logic value of PWM output A carrier 1
    input logic_A_c2,
    // logic value of PWM output A carrier 1
    input logic_A_c3,
    // logic value of PWM output A carrier 1
    input logic_A_c4,
    // logic value of PWM output A carrier 1
    input logic_A_c5,
    // logic value of PWM output A carrier 1
    input logic_A_c6,
    // logic value of PWM output A carrier 1
    input logic_A_c7,
    // logic value of PWM output A carrier 1
    input logic_A_c8,
    // ------------------------------------------------
	// logic value of output B (8 x 1 bits)
	// ------------------------------------------------
    // logic value of PWM output B carrier 1
    input logic_B_c1,
    // logic value of PWM output B carrier 2
    input logic_B_c2,
    // logic value of PWM output B carrier 3
    input logic_B_c3,
    // logic value of PWM output B carrier 4
    input logic_B_c4,
    // logic value of PWM output B carrier 5
    input logic_B_c5,
    // logic value of PWM output B carrier 6
    input logic_B_c6,
    // logic value of PWM output B carrier 7
    input logic_B_c7,
    // logic value of PWM output B carrier 8
    input logic_B_c8,
    // logic value of PWM output A
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // OUTPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // ------------------------------------------------
	// PWM output signal A (8 x 1 bits)
	// ------------------------------------------------ 
    // PWM output signal A compare 1
    output logic pwmout_A_c1,
    // PWM output signal A compare 2
    output logic pwmout_A_c2,
    // PWM output signal A compare 3
    output logic pwmout_A_c3,
    // PWM output signal A compare 4
    output logic pwmout_A_c4,
    // PWM output signal A compare 5
    output logic pwmout_A_c5,
    // PWM output signal A compare 6
    output logic pwmout_A_c6,
    // PWM output signal A compare 7
    output logic pwmout_A_c7,
    // PWM output signal A compare 8
    output logic pwmout_A_c8,
    // ------------------------------------------------
	// PWM output signal B (8 x 1 bits)
	// ------------------------------------------------
    // PWM output signal B compare 1
    output logic pwmout_B_c1,
    // PWM output signal B compare 2
    output logic pwmout_B_c2,
    // PWM output signal B compare 3
    output logic pwmout_B_c3,
    // PWM output signal B compare 4
    output logic pwmout_B_c4,
    // PWM output signal B compare 5
    output logic pwmout_B_c5,
    // PWM output signal B compare 6
    output logic pwmout_B_c6,
    // PWM output signal B compare 7
    output logic pwmout_B_c7,
    // PWM output signal B compare 8
    output logic pwmout_B_c8,
    // ------------------------------------------------
	// main interrupt signal (1 bit)
	// ------------------------------------------------
    output wire interrupt
    );
    
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // INTERNAL signal definitions
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    
    


    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // MODULES
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    configregpwm_concatenate CONCAT(
        .pwm_onoff,
        .int_onoff,
        .pwmclkdiv_onoff,
        .dtclkdiv_onoff,
        .mask_mode,
        .count_mode,
        .logic_A,
        .logic_B,
	    .register_concat
    );
    
    configregpwm_split SPLIT(
        .register_concat(register_concat__masked),
        .pwm_onoff(pwm_onoff__masked),
        .int_onoff(int_onoff__masked),
        .pwmclkdiv_onoff(pwmclkdiv_onoff__masked),
        .dtclkdiv_onoff(dtclkdiv_onoff__masked),
        .mask_mode(mask_mode__masked),
        .count_mode(count_mode__masked),
        .logic_A(logic_A__masked),
        .logic_B(logic_B__masked)
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
        .clkdiv_onoff(pwmclkdiv_onoff__masked),
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
        .compare(compare_c1__masked),
        .pwm_onoff(pwm_onoff__masked),
        .pwm(pwm_out_c1)
    );
    
    div_clock DTCLK(
        .clk,
        .reset,
        .divider(dtclk_divider),
        .pwm_onoff(pwm_onoff__masked),
        .clkdiv_onoff(dtclkdiv_onoff__masked),
        .div_clk(dt_clk)
    );
    
    dead_time DT1(
       .clk(dt_clk),
	   .reset,
	   .pwm(pwm_1),
	   .dtime_A,
	   .dtime_B,
	   .logic_A(logic_A__masked),
	   .logic_B(logic_B__masked),
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
	   .logic_A(logic_A__masked),
	   .logic_B(logic_B__masked),
	   .pwm_onoff(pwm_onoff__masked),
	   .pwmout_A(pwmout_2_A),
	   .pwmout_B(pwmout_2_B)
    );
    
/*    dead_time DT3(
       .clk(dt_clk),
	   .reset,
	   .pwm(pwm_3),
	   .dtime_A,
	   .dtime_B,
	   .logic_A(logic_A__masked),
	   .logic_B(logic_B__masked),
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
	   .logic_A(logic_A__masked),
	   .logic_B(logic_B__masked),
	   .pwm_onoff(pwm_onoff__masked),
	   .pwmout_A(pwmout_4_A),
	   .pwmout_B(pwmout_4_B)
    );*/
    
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