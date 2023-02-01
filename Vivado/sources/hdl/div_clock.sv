`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 12:57:42 AM
// Design Name: 
// Module Name: div_pwm_clock
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

module div_clock(
    input clk,
    input reset,
    input logic [`DIVCLK_WIDTH-1:0] divider,
    input _pwm_onoff pwm_onoff,
	output logic div_clk
    );
	
	logic [`DIVCLK_WIDTH-1:0] counter;
    
	always_ff @(posedge clk,posedge reset) begin
		if(reset || (pwm_onoff==PWM_OFF)) begin
			counter <= 4'b0;
			div_clk <= 1'b0;
		end
		else begin
			if(counter == divider) begin
				counter <= 4'b0;
				div_clk <= ~div_clk;
			end
			else begin
				counter <= counter + 1'b1;
			end
		end
	end
    
endmodule
