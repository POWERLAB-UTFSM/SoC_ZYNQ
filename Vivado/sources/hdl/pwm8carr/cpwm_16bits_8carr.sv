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

module cpwm_16bits_8carr (
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
    input [`EVTCOUNT_WIDTH-1:0] eventcount_c1,
	// event counter carrier 2
    input [`EVTCOUNT_WIDTH-1:0] eventcount_c2,
	// event counter carrier 3
    input [`EVTCOUNT_WIDTH-1:0] eventcount_c3,
	// event counter carrier 4
    input [`EVTCOUNT_WIDTH-1:0] eventcount_c4,
	// event counter carrier 5
    input [`EVTCOUNT_WIDTH-1:0] eventcount_c5,
	// event counter carrier 6
    input [`EVTCOUNT_WIDTH-1:0] eventcount_c6,
	// event counter carrier 7
    input [`EVTCOUNT_WIDTH-1:0] eventcount_c7,
	// event counter carrier 8
    input [`EVTCOUNT_WIDTH-1:0] eventcount_c8,
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
    // ------------------------------------------------
	// carrier selector (8 x 3 bits)
	// ------------------------------------------------
	// Carrier selector compare 1
    input [2:0] carrsel_c1,
	// Carrier selector compare 2
    input [2:0] carrsel_c2,
	// Carrier selector compare 3
    input [2:0] carrsel_c3,
	// Carrier selector compare 4
    input [2:0] carrsel_c4,
	// Carrier selector compare 5
    input [2:0] carrsel_c5,
	// Carrier selector compare 6
    input [2:0] carrsel_c6,
	// Carrier selector compare 7
    input [2:0] carrsel_c7,
	// Carrier selector compare 8
    input [2:0] carrsel_c8,
    // ------------------------------------------------
    // PWM ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    // ------------------------------------------------
	// on-off general registers (2 x 2 bits)
	// ------------------------------------------------
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
    
    logic [`PWMCOUNT_WIDTH-1:0] carrier_c1;
    logic [`PWMCOUNT_WIDTH-1:0] carrier_c2;
    logic [`PWMCOUNT_WIDTH-1:0] carrier_c3;
    logic [`PWMCOUNT_WIDTH-1:0] carrier_c4;
    logic [`PWMCOUNT_WIDTH-1:0] carrier_c5;
    logic [`PWMCOUNT_WIDTH-1:0] carrier_c6;
    logic [`PWMCOUNT_WIDTH-1:0] carrier_c7;
    logic [`PWMCOUNT_WIDTH-1:0] carrier_c8;
    
    logic [`PWMCOUNT_WIDTH-1:0] carriercomp_c1;
    logic [`PWMCOUNT_WIDTH-1:0] carriercomp_c2;
    logic [`PWMCOUNT_WIDTH-1:0] carriercomp_c3;
    logic [`PWMCOUNT_WIDTH-1:0] carriercomp_c4;
    logic [`PWMCOUNT_WIDTH-1:0] carriercomp_c5;
    logic [`PWMCOUNT_WIDTH-1:0] carriercomp_c6;
    logic [`PWMCOUNT_WIDTH-1:0] carriercomp_c7;
    logic [`PWMCOUNT_WIDTH-1:0] carriercomp_c8;
    
    logic pwm_c1;
    logic pwm_c2;
    logic pwm_c3;
    logic pwm_c4;
    logic pwm_c5;
    logic pwm_c6;
    logic pwm_c7;
    logic pwm_c8;
    
    logic maskeventcomp_c1;
    logic maskeventcomp_c2;
    logic maskeventcomp_c3;
    logic maskeventcomp_c4;
    logic maskeventcomp_c5;
    logic maskeventcomp_c6;
    logic maskeventcomp_c7;
    logic maskeventcomp_c8;
    
    logic maskevent_c1;
    logic maskevent_c2;
    logic maskevent_c3;
    logic maskevent_c4;
    logic maskevent_c5;
    logic maskevent_c6;
    logic maskevent_c7;
    logic maskevent_c8;
    
    logic [2:0] carrsel_c1__masked;
    
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // auxilliary assign (comment if necessary)
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    //assign carrsel_c1__masked = carrsel_c1;
    assign interrupt = maskevent_c1;

    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // MODULES
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    
    carrier_16bits_1carr CARR_C1(
        .clk,
        .reset,
        .pwm_onoff(pwm_onoff),
        .int_onoff(int_onoff),
        .period(period_c1),
        .initcarr(initcarr_c1),
        .eventcount(eventcount_c1),
        .countmode(countmode_c1),
        .maskmode(maskmode_c1),
        .carr_onoff(carr_onoff_c1),
        .carrier(carrier_c1),
        .maskevent(maskevent_c1)
    );
    
    mux_16bits_8x1 MUX_COMP_C1(
        .in_0(carrier_c1),
        .in_1(carrier_c2),
        .in_2(carrier_c3),
        .in_3(carrier_c4),
        .in_4(carrier_c5),
        .in_5(carrier_c6),
        .in_6(carrier_c7),
        .in_7(carrier_c8),
        .sel_0(carrsel_c1__masked),
        .out_0(carriercomp_c1)
    );
    
    mux_1bit_8x1 MUX_EVENT_C1(
        .in_0(maskevent_c1),
        .in_1(maskevent_c2),
        .in_2(maskevent_c3),
        .in_3(maskevent_c4),
        .in_4(maskevent_c5),
        .in_5(maskevent_c6),
        .in_6(maskevent_c7),
        .in_7(maskevent_c8),
        .sel_0(carrsel_c1__masked),
        .out_0(maskeventcomp_c1)
    );
    
    compare_16bits COMP1(
        .clk,
        .reset,
        .carrier(carriercomp_c1),
        .carrsel(carrsel_c1),
        .compare(compare_c1),
        .dtime_A(dtime_A_c1),
        .dtime_B(dtime_B_c1),
        .logic_A(logic_A_c1),
        .logic_B(logic_B_c1),
        .pwm_onoff(pwm_onoff),
        .maskevent(maskeventcomp_c1),
        .pwmout_A(pwmout_A_c1),
        .pwmout_B(pwmout_B_c1),
        .carrsel_out(carrsel_c1__masked)
    );
    
endmodule