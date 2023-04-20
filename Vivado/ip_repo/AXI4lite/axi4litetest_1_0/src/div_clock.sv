`timescale 10ns / 100ps
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
    input [`DIVCLK_WIDTH-1:0] divider,
    input _pwm_onoff pwm_onoff,
    input _clkdiv_onoff clkdiv_onoff,
	output logic div_clk
    );
    
    logic div_clkaux;
	logic [`DIVCLK_WIDTH-1:0] counter;
    
	always_ff @(posedge clk,posedge reset) begin
		if(reset || (pwm_onoff==PWM_OFF)) begin
			counter <= 4'b0;
			div_clkaux <= 1'b0;
		end
		else begin
			if(counter == divider) begin
				counter <= 4'b0;
				div_clkaux <= ~div_clkaux;
			end
			else begin
				counter <= counter + 1'b1;
			end
		end
	end
	
	always_comb begin  
	   if(clkdiv_onoff == CLKDIV_ON) begin
	       div_clk=div_clkaux;
	   end
	   else begin
	       div_clk=clk;
	   end	
	end
    
endmodule
