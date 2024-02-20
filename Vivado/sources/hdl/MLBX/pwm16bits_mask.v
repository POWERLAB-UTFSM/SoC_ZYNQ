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
	input clk,ce,rst,
	input [31:0] mask_in,
    input intmask,
	output reg [31:0] mask_out
	
);

	reg write=0;
	reg pwm_2_buffer;

	initial begin
		write<=0;
        mask_out<=0;
	end

	always @(posedge clk or posedge rst) begin
		if(rst==1) begin
            write<=0;
            mask_out<=0;
        end
        else begin
            if(intmask==1 || write==0) begin
                write<=1;
                mask_out<=mask_in;
            end
        end
	end

	


endmodule