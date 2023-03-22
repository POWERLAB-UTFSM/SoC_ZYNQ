`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 12:57:42 AM
// Design Name: 
// Module Name: carrier_gen_16bits
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

module maskevent_carrier(
	input clk,
	input reset,
	input _mask_mode mask_mode,
	input [`PWMCOUNT_WIDTH-1:0] carrier,
	input [`PWMCOUNT_WIDTH-1:0] period,
	output logic maskevent
);

	logic mask_ok_min;
	logic mask_ok_max;
	logic carrier_min;
	logic carrier_max;
	logic mask_decision;
	
	always_comb begin
		mask_ok_min = mask_mode==MIN_MASK || mask_mode==MINMAX_MASK;
		mask_ok_max = mask_mode==MAX_MASK || mask_mode==MINMAX_MASK;
	    carrier_min = (carrier == 0);
	    carrier_max = (carrier == period);
	end

	always_ff @(posedge clk or posedge reset) begin
        if(reset==1'b1) begin
            maskevent <= 1'b0;
        end
        else if((carrier_min & mask_ok_min) | (carrier_max & mask_ok_max) | mask_mode==NO_MASK) begin
            maskevent <= 1'b1;
        end
        else begin
            maskevent  <= 1'b0;
        end
    end

endmodule

