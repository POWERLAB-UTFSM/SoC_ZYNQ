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

module cpwm16b_compare2ch #(
	parameter PWMWIDTH = 16
)
(
	input clk,
	input ce,
	input rst,
	input [15:0] carrier,
	input [15:0] compare_1,
	input [15:0] compare_2,
	input en_pwm,
	input sig_pwm_1,
	input sig_pwm_2,
	output reg pwm_1a,
	output reg pwm_1b,
	output reg pwm_2a,
	output reg pwm_2b
);

	// reg pwm_1_buffer;
	// reg pwm_2_buffer;
	wire pwm_1_buffer;
	wire pwm_2_buffer;

	// initial begin
	// 	pwm_1_buffer=0;
	// 	pwm_2_buffer=0;
	// end

	assign pwm_1_buffer = (carrier>compare_1) ? 'd0 : 'd1 ;
	assign pwm_2_buffer = (carrier>compare_2) ? 'd0 : 'd1 ;

	// always @* begin
	// 	if(carrier>compare_1) begin
	// 		pwm_1_buffer='d0;
	// 	end
	// 	else begin
	// 		pwm_1_buffer='d1;
	// 	end
	// end

	// always @* begin
	// 	if(carrier>compare_2) begin
	// 		pwm_2_buffer='d0;
	// 	end
	// 	else begin
	// 		pwm_2_buffer='d1;
	// 	end
	// end

	always @(posedge clk or posedge rst) begin
		if(rst) begin
			pwm_1a <= 0;
			pwm_2a <= 0;
			pwm_1b <= 0;
			pwm_2b <= 0;
		end
		else if(ce==1) begin
			pwm_1a <= (pwm_1_buffer ^ sig_pwm_1)&en_pwm;	
			pwm_2a <= (pwm_2_buffer ^ sig_pwm_2)&en_pwm;
			pwm_1b <= (~pwm_1_buffer ^ sig_pwm_1)&en_pwm;	
			pwm_2b <= (~pwm_2_buffer ^ sig_pwm_2)&en_pwm;
		end
	end


endmodule