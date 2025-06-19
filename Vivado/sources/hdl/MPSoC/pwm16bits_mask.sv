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

module pwm16bits_mask //#(parameter PWMWIDTH = 16)
(
	input wire clk,ce,rst,
	input wire [31:0] mask_in,
	input wire conf_sync,
	input wire intmask_int,
	input wire intmask_ext,
	output reg [31:0] mask_out
);

	wire intmask;

	assign intmask = (conf_sync) ? intmask_ext : intmask_int;
	//assign intmask = intmask_int;

	initial begin
    mask_out<=0;
	end

	always @(posedge clk or posedge rst) begin
		if(rst) begin
			mask_out<=0;
		end
		else begin
			if(intmask==1) begin
				mask_out<=mask_in;
			end
		end
	end

	


endmodule