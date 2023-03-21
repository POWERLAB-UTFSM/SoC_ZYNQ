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
    // PWM period  carrier x
    input [`PWM_WIDTH-1:0][`PWMCOUNT_WIDTH-1:0] period_c,
	// ------------------------------------------------
	// initial carrier values (8 x 16 bits)
	// ------------------------------------------------
	// PWM initial value carrier 1
    input [`PWM_WIDTH-1:0][`PWMCOUNT_WIDTH-1:0] initcarr_c,
	// ------------------------------------------------
	// compare registers 1 (8 x 16 bits)
	// ------------------------------------------------
	// PWM compare register 1 carrier 1
    input [`PWM_WIDTH-1:0][`PWMCOUNT_WIDTH-1:0] compare_c,
	// ------------------------------------------------
	// dead time register A (8 x 8 bits)
	// ------------------------------------------------
	// dead time value for pulse A compare 1
    input [`PWM_WIDTH-1:0][`DTCOUNT_WIDTH-1:0] dtime_A_c,
	// ------------------------------------------------
	// dead time register B (8 x 8 bits)
	// ------------------------------------------------
	// dead time value for pulse A compare 1
    input [`PWM_WIDTH-1:0][`DTCOUNT_WIDTH-1:0] dtime_B_c,
	// ------------------------------------------------
	// PWM carrier clock dividers (8 x 4 bits)
	// ------------------------------------------------
	// clock divider for PWM carrier 1
    input [`PWM_WIDTH-1:0][`DIVCLK_WIDTH-1:0] carrclkdivider_c,
    // ------------------------------------------------
	// Dead time clock dividers (8 x 4 bits)
	// ------------------------------------------------
	// clock driver for the dead time generator compare 1
    input [`PWM_WIDTH-1:0][`DIVCLK_WIDTH-1:0] dtclkdivider_c,
	// ------------------------------------------------
	// Carrier on-off clock divider (8 x 1 bits)
	// ------------------------------------------------
	// pwm carrier clock divider ON-OFF state bit carrier 1
    input  _clkdiv_onoff [`PWM_WIDTH-1:0] carrclkdiv_onoff_c,
    // ------------------------------------------------
	// Dead time on-off clock divider (8 x 1 bits)
	// ------------------------------------------------
	// dead time clock divider ON-OFF state configuration bit
    input _clkdiv_onoff [`PWM_WIDTH-1:0] dtclkdiv_onoff_c,
	// ------------------------------------------------
	// event counters (8 x 3 bits)
	// ------------------------------------------------
	// event counter carrier 1
    input [`PWM_WIDTH-1:0][`EVTCOUNT_WIDTH-1:0] eventcount_c,
	// ------------------------------------------------
	// count mode configuration (8 x 2 bits)
	// ------------------------------------------------
	// count mode carrier 1
    input _count_mode [`PWM_WIDTH-1:0] countmode_c,
	// ------------------------------------------------
	// mask mode configuration (8 x 2 bits)
	// ------------------------------------------------
	// event mask mode carrier 1
    input _mask_mode [`PWM_WIDTH-1:0] maskmode_c,
	// ------------------------------------------------
	// on-off counter carrier (8 x 1 bits)
	// ------------------------------------------------
	// Carrier count ON-OFF state carrier 1
    input _carr_onoff [`PWM_WIDTH-1:0] carr_onoff_c,
    // ------------------------------------------------
	// on-off dead time (8 x 1 bits)
	// ------------------------------------------------
	// Carrier count ON-OFF state carrier 1
    input _dt_onoff [`PWM_WIDTH-1:0] dt_onoff_c,
    // ------------------------------------------------
	// carrier selector (8 x 3 bits)
	// ------------------------------------------------
	// Carrier selector compare 1
    input [`PWM_WIDTH-1:0][2:0] carrsel_c,
    // ------------------------------------------------
    // PWM ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    // ------------------------------------------------
	// on-off general registers (2 x 2 bits)
	// ------------------------------------------------
    input _pwm_onoff pwm_onoff,
    // Interrupt ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    input _int_onoff int_onoff,
    // ------------------------------------------------
	// interrupt matrix (1 x 8 bits)
	// ------------------------------------------------
	input [7:0] interrupt_matrix,
    // ------------------------------------------------
	// logic value of output A (8 x 1 bits)
	// ------------------------------------------------
	// logic value of PWM output A carrier 1
    input [`PWM_WIDTH-1:0] logic_A_c,
    // ------------------------------------------------
	// logic value of output B (8 x 1 bits)
	// ------------------------------------------------
	// logic value of PWM output A carrier 1
    input [`PWM_WIDTH-1:0] logic_B_c,
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // OUTPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // ------------------------------------------------
	// PWM output signal A (8 x 1 bits)
	// ------------------------------------------------ 
	// PWM output signal A compare 1
    output logic [`PWM_WIDTH-1:0] pwmout_A_c,
    // ------------------------------------------------
	// PWM output signal B (8 x 1 bits)
	// ------------------------------------------------
    // PWM output signal B compare 1
    output logic [`PWM_WIDTH-1:0] pwmout_B_c,
    // ------------------------------------------------
	// main interrupt signal (1 bit)
	// ------------------------------------------------
    output wire interrupt
    );
    
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // INTERNAL signal definitions
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    
    logic pwm_clk;
    
    logic [`PWM_WIDTH-1:0][`PWMCOUNT_WIDTH-1:0] carrier_c;
    logic [`PWM_WIDTH-1:0][`PWMCOUNT_WIDTH-1:0] carriercomp_c;
    logic [`PWM_WIDTH-1:0] maskeventcomp_c;
    logic [`PWM_WIDTH-1:0] maskevent_c;
    logic [`PWM_WIDTH-1:0] [2:0] carrsel_c__masked;
    
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // auxilliary assign (comment if necessary)
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    //assign carrsel_c1__masked = carrsel_c1;
    //assign interrupt = maskevent_c1;

    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // MODULES
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    
    genvar i;
        generate
            for (i=0; i<`PWM_WIDTH; i=i+1) begin : PWMX // <-- example block name
            carrier_16bits_1carr  CARR(
                .clk,
                .reset,
                .pwm_onoff(pwm_onoff),
                .int_onoff(int_onoff),
                .period(period_c[i]),
                .initcarr(initcarr_c[i]),
                .eventcount(eventcount_c[i]),
                .carrclkdivider(carrclkdivider_c[i]),
                .carrclkdiv_onoff(carrclkdiv_onoff_c[i]),
                .countmode(countmode_c[i]),
                .maskmode(maskmode_c[i]),
                .carr_onoff(carr_onoff_c[i]),
                .carrier(carrier_c[i]),
                .maskevent(maskevent_c[i])
            );
            
            compare_16bits COMP(
                .clk,
                .reset,
                .carrier(carriercomp_c[i]),
                .carrsel(carrsel_c[i]),
                .compare(compare_c[i]),
                .dtclkdivider(dtclkdivider_c[i]),
                .dt_onoff(dt_onoff_c[i]),
                .dtime_A(dtime_A_c[i]),
                .dtime_B(dtime_B_c[i]),
                .logic_A(logic_A_c[i]),
                .logic_B(logic_B_c[i]),
                .pwm_onoff(pwm_onoff),
                .dtclkdiv_onoff(dtclkdiv_onoff_c[i]),
                .maskevent(maskeventcomp_c[i]),
                .pwmout_A(pwmout_A_c[i]),
                .pwmout_B(pwmout_B_c[i]),
                .carrsel_out(carrsel_c__masked[i])
            );
            
            mux_16bits_8x1 MUX_COMP(
                .in_0(carrier_c[0]),
                .in_1(carrier_c[1]),
                .in_2(carrier_c[2]),
                .in_3(carrier_c[3]),
                .in_4(carrier_c[4]),
                .in_5(carrier_c[5]),
                .in_6(carrier_c[6]),
                .in_7(carrier_c[7]),
                .sel_0(carrsel_c__masked[i]),
                .out_0(carriercomp_c[i])
            );
            
            mux_1bit_8x1 MUX_EVENT(
                .in_0(maskevent_c[0]),
                .in_1(maskevent_c[1]),
                .in_2(maskevent_c[2]),
                .in_3(maskevent_c[3]),
                .in_4(maskevent_c[4]),
                .in_5(maskevent_c[5]),
                .in_6(maskevent_c[6]),
                .in_7(maskevent_c[7]),
                .sel_0(carrsel_c__masked[i]),
                .out_0(maskeventcomp_c[i])
            );
        end 
    endgenerate
    
    interrupt_matrix INTMAT(
        .interrupt_in(maskevent_c),
        .matrix(interrupt_matrix),
        .interrupt_out(interrupt)
    );
    
    
endmodule