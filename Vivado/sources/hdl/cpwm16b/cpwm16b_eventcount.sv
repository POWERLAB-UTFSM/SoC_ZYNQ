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

module cpwm16b_eventcount #(
	parameter PWMWIDTH = 16
)
(
	input clk,ce,rst,
	input [PWMWIDTH-1:0] carrier_max,
	input [PWMWIDTH-1:0] carrier,
	input [3:0] event_count,
	input [1:0] eventcount_mode,
	output wire sync
);

wire event_detected;
wire is_min;
wire is_max;

reg [3:0] current_count;

//typedef enum t_eventcount_mode [1:0] {
//    COUNT_MIN  = 2'b00, 
//    COUNT_MAX  = 2'b01, 
//    COUNT_MINMAX  = 2'b10,
//    COUNT_NONE = 2'b11
//    } e_eventcount_mode;

assign is_max = (carrier == carrier_max);
assign is_min = (carrier == 0);

assign event_detected = 
	(eventcount_mode == 1) ? is_min :
	(eventcount_mode == 2) ? is_max :
	(eventcount_mode == 3) ? (is_max | is_min) : (0);
    
always @(posedge clk or posedge rst) begin
	if (rst || sync==1) begin
		current_count <= 0;
		// sync <= 0;
	end 
	else if (event_detected==1 && ce==1) begin
		current_count <= current_count + 1;
	end
end

assign sync = (event_count == current_count) ? 1 : 0;
// always @(*) begin
// 	if (event_count == current_count) begin
// 		sync <= 1;
// 	end
// 	else begin
// 		sync <= 0;
// 	end
// end

endmodule