`timescale 10ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 01:18:08 AM
// Design Name: 
// Module Name: mux_16bits_8x1
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

module mux_16bits_8x1 (
    input wire [`PWMCOUNT_WIDTH-1:0] in_0,
	input wire [`PWMCOUNT_WIDTH-1:0] in_1,
	input wire [`PWMCOUNT_WIDTH-1:0] in_2,
	input wire [`PWMCOUNT_WIDTH-1:0] in_3,
	input wire [`PWMCOUNT_WIDTH-1:0] in_4,
	input wire [`PWMCOUNT_WIDTH-1:0] in_5,
	input wire [`PWMCOUNT_WIDTH-1:0] in_6,
	input wire [`PWMCOUNT_WIDTH-1:0] in_7,
	input wire [2:0] sel_0,
	output logic [`PWMCOUNT_WIDTH-1:0] out_0 
);

always_comb begin
	case (sel_0)
		'd0 : out_0 <= in_0;
		'd1 : out_0 <= in_1;
		'd2 : out_0 <= in_2;
		'd3 : out_0 <= in_3;
		'd4 : out_0 <= in_4;
		'd5 : out_0 <= in_5;
		'd6 : out_0 <= in_6;
		'd7 : out_0 <= in_7;
		default : out_0 <= in_0;
	endcase
end
	
endmodule