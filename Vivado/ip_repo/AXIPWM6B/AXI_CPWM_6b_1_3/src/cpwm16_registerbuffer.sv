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

module cpwm16b_registerbuffer #(
	parameter REGISTER_WIDTH = 32
)
(
	input clk,
	input rst,
	input ce,
	input syncevent,
	input mask_on,
	input [REGISTER_WIDTH-1:0] reg_in,
	output wire [REGISTER_WIDTH-1:0] reg_out
);

	reg [REGISTER_WIDTH-1:0] reg_aux;
	reg first_reg;

	assign reg_out = (~mask_on) ? (reg_aux) : (reg_in);
    
	always @(posedge clk or posedge rst) begin
		if(rst) begin
			reg_aux <= 0;
			first_reg <= 0;
			//reg_out <= 0;
		end
		else 
		if ((syncevent==1 || first_reg==0)&& ce==1) begin
			reg_aux <= reg_in;
			first_reg <= 1;
			//reg_out <= reg_in;
		end
	end
    
endmodule