`timescale 10ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 01:18:08 AM
// Design Name: 
// Module Name: carrier_16bits_1carr
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
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// IMPORTED PACKAGES
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
import PKG_pwm::*;

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// MODULE INITIALIZATION
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 
 module carrier_16bits_1carr (
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // Signal INPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// ------------------------------------------------
	// common clock and reset
	// ------------------------------------------------
    input clk,
    input reset,
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // Register INPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    input [`PWMCOUNT_WIDTH-1:0] period,
    input [`PWMCOUNT_WIDTH-1:0] initcarr,
    input [`EVTCOUNT_WIDTH-1:0] eventcount,
    input _carr_sel carrsel,
    input _count_mode countmode,
    input _mask_mode maskmode,
    input _pwm_onoff pwm_onoff,
    input _carr_onoff carrier_onoff,
    //input _int_onoff int_onoff,
    //input _carr_onoff carr_onoff,
    //input _clkdiv_onoff carrclkdiv_onoff,
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // OUTPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    output wire [`PWMCOUNT_WIDTH-1:0] carrier,
    output _carr_sel carrsel_out,
    output wire maskevent
    
 );
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // DEFINITION OF INTERNAL VARIABLES
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    
    wire [`PWMCOUNT_WIDTH-1:0] period__masked;
    wire [`PWMCOUNT_WIDTH-1:0] initcarr__masked;
    wire [`EVTCOUNT_WIDTH-1:0] eventcount__masked;
    //wire [`DIVCLK_WIDTH-1:0] carrclkdivider__masked;
    wire maskevent_single;
    //wire carrsel__masked;
    _count_mode countmode__masked;
    _mask_mode maskmode__masked;
    _pwm_onoff pwm_onoff__masked;
    _carr_onoff carr_onoff__masked;
    //_int_onoff int_onoff__masked;
    //_clkdiv_onoff carrclkdiv_onoff__masked;
    
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // ASSIGN VARIABLES
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    
    //assign countmode__masked = countmode;
    //assign maskmode__masked = maskmode;
    //assign pwm_onoff__masked = pwm_onoff;
    //assign carr_onoff__masked = carr_onoff;
    //assign int_onoff__masked = int_onoff;
    //assign eventcount__masked = eventcount;
    
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // SUBMODULES
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    carrier_gen_16bits CARR(
        //.clk(pwm_clk),
        .clk(clk),
        .reset(reset),
        .period(period__masked),
        .init_carr(initcarr__masked),
        .count_mode(countmode__masked),
        //.mask_mode(maskmode__masked),
        .pwm_onoff(pwm_onoff),
        .carr_onoff(carrier_onoff),
        .carrier(carrier)
        //.maskevent(maskevent_single)
    );
    
    maskevent_carrier MASKEVT(
        .clk,
        .reset,
        .mask_mode(maskmode__masked),
	    .carrier(carrier),
	    .period(period__masked),
	    .maskevent(maskevent_single)
    );
    
    /*div_clock DIVCLK_PWM(
        .clk,
        .reset,
        .divider(carrclkdivider__masked),
        .pwm_onoff(pwm_onoff),
        .clkdiv_onoff(carrclkdiv_onoff__masked),
        .div_clk(pwm_clk)
    );*/
    
    event_counter EVTCOUNT(
        .clk(clk),
        .reset(reset),
        .maskevent_input(maskevent_single),
        .event_count(eventcount__masked),
        .pwm_onoff(pwm_onoff),
        //.pwm_onoff(pwm_onoff),
        .carr_onoff(carrier_onoff),
        .countmode(countmode__masked),
        .maskmode(maskmode__masked),
        .maskevent_output(maskevent)
    );
    
    register_mask_16bits REGMASK_PERIOD(
        .clk(clk),
        .reset(reset),
        .maskevent(maskevent),
        .pwm_onoff(pwm_onoff),
        //.pwm_onoff(pwm_onoff),
        .reg_in(period),
        .reg_out(period__masked)        
    );
    
    register_mask_16bits REGMASK_INITCARR(
        .clk(clk),
        .reset(reset),
        .maskevent(maskevent),
        .pwm_onoff(pwm_onoff),
        //.pwm_onoff(pwm_onoff),
        .reg_in(initcarr),
        .reg_out(initcarr__masked)        
    );
    
    register_mask_16bits REGMASK_CONF(
        .clk(clk),
        .reset(reset),
        .maskevent(maskevent),
        .pwm_onoff(pwm_onoff),
        .reg_in({countmode,maskmode,eventcount,carrsel}),
        .reg_out({countmode__masked,maskmode__masked,eventcount__masked,carrsel_out})        
    );
    
endmodule
