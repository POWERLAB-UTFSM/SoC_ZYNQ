`timescale 10ns / 100ps
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
    input [`PWMCOUNT_WIDTH*`PWM_WIDTH-1:0]  period_x,
    //input [`PWMCOUNT_WIDTH-1:0]  period_c [`PWM_WIDTH-1:0] ,
	// ------------------------------------------------
	// initial carrier values (8 x 16 bits)
	// ------------------------------------------------
	// PWM initial value carrier 1
	input [`PWMCOUNT_WIDTH*`PWM_WIDTH-1:0]  initcarr_x,
    //input [`PWMCOUNT_WIDTH-1:0] initcarr_c [`PWM_WIDTH-1:0],
	// ------------------------------------------------
	// compare registers 1 (8 x 16 bits)
	// ------------------------------------------------
	// PWM compare register 1 carrier 1
	input [`PWMCOUNT_WIDTH*`PWM_WIDTH-1:0]  compare_x,
    //input [`PWMCOUNT_WIDTH-1:0] compare_c [`PWM_WIDTH-1:0],
	// ------------------------------------------------
	// dead time register A (8 x 8 bits)
	// ------------------------------------------------
	// dead time value for pulse A compare 1
	input [`DTCOUNT_WIDTH*`PWM_WIDTH-1:0]  dtime_A_x,
    //input [`DTCOUNT_WIDTH-1:0] dtime_A_c [`PWM_WIDTH-1:0],
	// ------------------------------------------------
	// dead time register B (8 x 8 bits)
	// ------------------------------------------------
	// dead time value for pulse A compare 1
	input [`DTCOUNT_WIDTH*`PWM_WIDTH-1:0]  dtime_B_x,
    //input [`DTCOUNT_WIDTH-1:0] dtime_B_c [`PWM_WIDTH-1:0],
	// ------------------------------------------------
	// PWM carrier clock dividers (8 x 4 bits)
	// ------------------------------------------------
	// clock divider for PWM carrier 1
	input [`DIVCLK_WIDTH*`PWM_WIDTH-1:0] carrclkdivider_x,
    //input [`DIVCLK_WIDTH-1:0] carrclkdivider_c [`PWM_WIDTH-1:0],
    // ------------------------------------------------
	// Dead time clock dividers (8 x 4 bits)
	// ------------------------------------------------
	// clock driver for the dead time generator compare 1
	input [`DIVCLK_WIDTH*`PWM_WIDTH-1:0] dtclkdivider_x,
    //input [`DIVCLK_WIDTH-1:0] dtclkdivider_c [`PWM_WIDTH-1:0],
	// ------------------------------------------------
	// Carrier on-off clock divider (8 x 1 bits)
	// ------------------------------------------------
	// pwm carrier clock divider ON-OFF state bit carrier 1
    input [$bits(_clkdiv_onoff)*`PWM_WIDTH-1:0] carrclkdiv_onoff_x,
    //input  _clkdiv_onoff  carrclkdiv_onoff_c [`PWM_WIDTH-1:0],
    // ------------------------------------------------
	// Dead time on-off clock divider (8 x 1 bits)
	// ------------------------------------------------
	// dead time clock divider ON-OFF state configuration bit
    input [$bits(_clkdiv_onoff)*`PWM_WIDTH-1:0] dtclkdiv_onoff_x,
    //input _clkdiv_onoff  dtclkdiv_onoff_c [`PWM_WIDTH-1:0],
	// ------------------------------------------------
	// event counters (8 x 3 bits)
	// ------------------------------------------------
	// event counter carrier 1
    input [`EVTCOUNT_WIDTH*`PWM_WIDTH-1:0] eventcount_x,
    //input [`EVTCOUNT_WIDTH-1:0] eventcount_c [`PWM_WIDTH-1:0],
	// ------------------------------------------------
	// count mode configuration (8 x 2 bits)
	// ------------------------------------------------
	// count mode carrier 1
	input [$bits(_count_mode)*`PWM_WIDTH-1:0] countmode_x,
    //input _count_mode  countmode_c [`PWM_WIDTH-1:0],
	// ------------------------------------------------
	// mask mode configuration (8 x 2 bits)
	// ------------------------------------------------
	// event mask mode carrier 1
	input [$bits(_mask_mode)*`PWM_WIDTH-1:0] maskmode_x,
    //input _mask_mode  maskmode_c [`PWM_WIDTH-1:0],
	// ------------------------------------------------
	// on-off counter carrier (8 x 1 bits)
	// ------------------------------------------------
	// Carrier count ON-OFF state carrier 1
	input [$bits(_carr_onoff)*`PWM_WIDTH-1:0] carr_onoff_x,
    //input _carr_onoff  carr_onoff_c [`PWM_WIDTH-1:0],
    // ------------------------------------------------
	// on-off dead time (8 x 1 bits)
	// ------------------------------------------------
	// Carrier count ON-OFF state carrier 1
	input [$bits(_dt_onoff)*`PWM_WIDTH-1:0] dt_onoff_x,
    //input _dt_onoff  dt_onoff_c [`PWM_WIDTH-1:0],
    // ------------------------------------------------
	// carrier selector (8 x 3 bits)
	// ------------------------------------------------
	// Carrier selector compare 1
	input [`PWM_WIDTH*`PWM_WIDTH-1:0] carrsel_x,
    //input [2:0] carrsel_c [`PWM_WIDTH-1:0],
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
	input [`PWM_WIDTH-1:0] interrupt_matrix,
    // ------------------------------------------------
	// logic value of output A (8 x 1 bits)
	// ------------------------------------------------
	// logic value of PWM output A carrier 1
    input [`PWM_WIDTH-1:0] logic_A_x,
    //input  logic_A_c [`PWM_WIDTH-1:0],
    // ------------------------------------------------
	// logic value of output B (8 x 1 bits)
	// ------------------------------------------------
	// logic value of PWM output A carrier 1
    input [`PWM_WIDTH-1:0] logic_B_x,
    //input  logic_B_c [`PWM_WIDTH-1:0],
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // OUTPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // ------------------------------------------------
	// PWM output signal A (8 x 1 bits)
	// ------------------------------------------------ 
	// PWM output signal A compare 1
	output wire  [`PWM_WIDTH-1:0] pwmout_A_x,
    //output logic  pwmout_A_c [`PWM_WIDTH-1:0],
    // ------------------------------------------------
	// PWM output signal B (8 x 1 bits)
	// ------------------------------------------------
    // PWM output signal B compare 1
    output wire  [`PWM_WIDTH-1:0] pwmout_B_x,
    //output logic  pwmout_B_c [`PWM_WIDTH-1:0],
    // ------------------------------------------------
	// main interrupt signal (1 bit)
	// ------------------------------------------------
    output interrupt
    );
    
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // INTERNAL signal definitions
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    
    logic [`PWMCOUNT_WIDTH*`PWM_WIDTH-1:0]  carrier_x;
    logic [`PWM_WIDTH-1:0] maskevent_x;
    
    //logic pwm_clk;
    
    wire [`PWMCOUNT_WIDTH-1:0] carrier_c [`PWM_WIDTH-1:0];
    wire [`PWMCOUNT_WIDTH-1:0] carriercomp_c [`PWM_WIDTH-1:0];
    wire  [`PWM_WIDTH-1:0] maskeventcomp_c ;
    wire  [`PWM_WIDTH-1:0] maskevent_c ;
    wire  [`PWM_WIDTH-1:0] carrsel_c__masked [`PWM_WIDTH-1:0];
    
    wire [`PWMCOUNT_WIDTH-1:0] period_c [`PWM_WIDTH-1:0];
    wire [`PWMCOUNT_WIDTH-1:0] initcarr_c [`PWM_WIDTH-1:0];
    wire [`PWMCOUNT_WIDTH-1:0] compare_c [`PWM_WIDTH-1:0];
    wire [`DTCOUNT_WIDTH-1:0] dtime_A_c [`PWM_WIDTH-1:0];
    wire [`DTCOUNT_WIDTH-1:0] dtime_B_c [`PWM_WIDTH-1:0];
    wire [`DIVCLK_WIDTH-1:0] carrclkdivider_c [`PWM_WIDTH-1:0];
    wire [`DIVCLK_WIDTH-1:0] dtclkdivider_c [`PWM_WIDTH-1:0];
    _clkdiv_onoff  carrclkdiv_onoff_c [`PWM_WIDTH-1:0];
    _clkdiv_onoff  dtclkdiv_onoff_c [`PWM_WIDTH-1:0];
    wire [`EVTCOUNT_WIDTH-1:0] eventcount_c [`PWM_WIDTH-1:0];
    _count_mode  countmode_c [`PWM_WIDTH-1:0];
    _mask_mode  maskmode_c [`PWM_WIDTH-1:0];
    _carr_onoff  carr_onoff_c [`PWM_WIDTH-1:0];
    _dt_onoff  dt_onoff_c [`PWM_WIDTH-1:0];
    wire [`PWM_WIDTH-1:0] carrsel_c [`PWM_WIDTH-1:0];
    wire logic_A_c [`PWM_WIDTH-1:0];
    wire logic_B_c [`PWM_WIDTH-1:0];
    wire  pwmout_A_c [`PWM_WIDTH-1:0];
    wire  pwmout_B_c [`PWM_WIDTH-1:0];
    
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // auxilliary assign (comment if necessary)
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    //assign carrsel_c1__masked = carrsel_c1;
    //assign interrupt = maskevent_c1;
    genvar j;
        generate
        for (j=0; j<`PWM_WIDTH; j=j+1) begin
           assign period_c[j]=period_x[`PWMCOUNT_WIDTH*(j+1)-1:`PWMCOUNT_WIDTH*j];
           assign initcarr_c[j]=initcarr_x[`PWMCOUNT_WIDTH*(j+1)-1:`PWMCOUNT_WIDTH*j];
           assign compare_c[j]=compare_x[`PWMCOUNT_WIDTH*(j+1)-1:`PWMCOUNT_WIDTH*j];
           assign dtime_A_c[j]=dtime_A_x[`DTCOUNT_WIDTH*(j+1)-1:`DTCOUNT_WIDTH*j];
           assign dtime_B_c[j]=dtime_B_x[`DTCOUNT_WIDTH*(j+1)-1:`DTCOUNT_WIDTH*j];
           assign carrclkdivider_c[j]=carrclkdivider_x[`DIVCLK_WIDTH*(j+1)-1:`DIVCLK_WIDTH*j];
           assign dtclkdivider_c[j]=dtclkdivider_x[`DIVCLK_WIDTH*(j+1)-1:`DIVCLK_WIDTH*j];
           assign carrclkdiv_onoff_c[j]=_clkdiv_onoff'(carrclkdiv_onoff_x[$bits(_clkdiv_onoff)*(j+1)-1:$bits(_clkdiv_onoff)*j]);
           assign dtclkdiv_onoff_c[j]=_clkdiv_onoff'(dtclkdiv_onoff_x[$bits(_clkdiv_onoff)*(j+1)-1:$bits(_clkdiv_onoff)*j]);
           assign eventcount_c[j] = eventcount_x[`EVTCOUNT_WIDTH*(j+1)-1:`EVTCOUNT_WIDTH*j];
           assign countmode_c[j]=_count_mode'(countmode_x[$bits(_count_mode)*(j+1)-1:$bits(_count_mode)*j]);
           assign maskmode_c[j]=_mask_mode'(maskmode_x[$bits(_mask_mode)*(j+1)-1:$bits(_mask_mode)*j]);
           assign carr_onoff_c[j]=_carr_onoff'(carr_onoff_x[$bits(_carr_onoff)*(j+1)-1:$bits(_carr_onoff)*j]);
           assign dt_onoff_c[j]=_dt_onoff'(dt_onoff_x[$bits(_dt_onoff)*(j+1)-1:$bits(_dt_onoff)*j]);
           assign carrsel_c[j]=carrsel_x[`PWM_WIDTH*(j+1)-1:`PWM_WIDTH*j];
           assign logic_A_c[j]=logic_A_x[j];
           assign logic_B_c[j]=logic_B_x[j];
           assign pwmout_A_x[j]=pwmout_A_c[j];
           assign pwmout_B_x[j]=pwmout_B_c[j];
           assign carrier_x[`PWMCOUNT_WIDTH*(j+1)-1:`PWMCOUNT_WIDTH*j] = carrier_c[j];
           assign maskevent_x[j]=maskevent_c[j];
        end
    endgenerate

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
            
            mux_variable MUXVAR(
                .in_carr(carrier_x),
                .in_mask(maskevent_x),
                .sel_0(carrsel_c__masked[i]),
                .out_carr(carriercomp_c[i]),
                .out_mask(maskeventcomp_c[i])
            );
            
            /*mux_16bits_8x1 MUX_COMP(
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
            );*/
        end 
    endgenerate
    
    interrupt_matrix INTMAT(
        .reset,
        .interrupt_in(maskevent_c),
        .matrix(interrupt_matrix),
        .interrupt_out(interrupt)
    );
    
    
endmodule