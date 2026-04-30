`timescale 10ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 01:18:08 AM
// Design Name: 
// Module Name:
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

module cpwm16b_clockdiv //#(parameter PWMWIDTH = 16)
(
	input clk,ce,rst,
	input [1:0] div,
	output reg clkout
);

reg [2:0] counter;

always @(posedge clk or posedge rst) begin
	if(rst) begin
		counter <= 0;
	end
	else if(ce==1) begin
		counter <= counter + 1;
	end
end

// assign clkout = 
// 	(div==2'b00) ? clk :
// 	(div==2'b01) ? counter[0] :
// 	(div==2'b10) ? counter[1] :
// 	counter[2];

always @(*) begin
	case (div)
		(2'b00) : begin
			clkout <= clk;
		end
		(2'b01) : begin
			clkout <= counter[0];
		end
		(2'b10) : begin
			clkout <= counter[1];
		end
		default : begin
			clkout <= clk;
		end
	endcase
end

endmodule