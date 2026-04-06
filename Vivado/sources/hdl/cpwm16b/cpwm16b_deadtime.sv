`timescale 10ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 01:18:08 AM
// Design Name: 
// Module Name: dead_time
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

module cpwm16b_deadtime #(
	parameter DTCOUNT_WIDTH = 8
)
(
	input clk,
	input rst,
	input ce,
	input pwmin,
	input [DTCOUNT_WIDTH-1:0] deadtime,
	input dt_logic,
	input  pwm_onoff,
	input  dt_onoff, //0=off, 1=on
	output wire pwmout
);
    
	reg [DTCOUNT_WIDTH-1:0] dtcounter;
	reg  pwmaux;

	assign pwmout=(dt_onoff==1) ? ((pwmaux ^ dt_logic) & pwm_onoff) : (pwmin);

	always  @(posedge clk, posedge rst) begin
		if(rst) begin
			pwmaux <= 0;
			dtcounter <= 0;
		end
		else if (dt_onoff==1 && ce==1) begin
			if (pwmin==1 && dtcounter < deadtime && pwmaux==0) begin
				dtcounter <= dtcounter + 1;
				pwmaux <= 0;        
			end
			else if (pwmin==1 && dtcounter >= deadtime && pwmaux==0) begin
				dtcounter <= 0;
				pwmaux <= 1;
			end
			else begin
				pwmaux <= pwmin;
			end
		end
	end
    
endmodule