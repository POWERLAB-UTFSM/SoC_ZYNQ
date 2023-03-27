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
//                          'clk_sel.sv'
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

module clk_sel (
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // Signal INPUTS
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// ------------------------------------------------
	// common clock and reset
	// ------------------------------------------------
    // system clock
    //input clk,
    // system pwm clock
    input pwm0_clk,
    // system pwm clock
    input pwm1_clk,
    // system pwm clock
    input pwm2_clk,
    // system pwm clock
    input pwm3_clk,
    // system reset
    input reset,
    // ------------------------------------------------
    // PWM ON-OFF state configuration bit (defined and packaged in PKG_pwm.sv)
    // ------------------------------------------------
	// on-off general registers (2 x 2 bits)
	// ------------------------------------------------
    input _pwm_onoff pwm_onoff,
    input clk_sel,
    output logic clk_out
    );
    
    logic [1:0] clk_sel_aux;
    
    always_latch begin
        if(reset || pwm_onoff==PWM_OFF) begin
            //clk_out <= pwm0_clk;
            clk_sel_aux=clk_sel;
        end
    end
    
    always_comb begin
        case (clk_sel_aux) 
            0: begin
                clk_out = pwm0_clk;
            end
            1: begin
                clk_out = pwm1_clk;
            end
            2: begin
                clk_out = pwm2_clk;
            end
            3: begin
                clk_out = pwm3_clk;
            end
            default: begin
                clk_out = pwm0_clk;
            end
        endcase
    end

   
    
endmodule