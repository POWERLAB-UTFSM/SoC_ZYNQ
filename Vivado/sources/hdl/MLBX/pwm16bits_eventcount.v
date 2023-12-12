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

module pwm16bits_eventcount //#(parameter PWMWIDTH = 16)
(
	input clk,ce,rst,
	input [15:0] count_max,
	input [15:0] carrier,
	input [3:0] event_count,
	input [1:0] sync_mode,
	output reg sync
);
	
	//--------------------------------
	//Interrupt generator
	reg mask_ok_min;
	reg mask_ok_max;
	reg carrier_min;
	reg carrier_max;

	reg sync_buffer;
	reg [3:0] event_timer;

	localparam NO_EVENT=0;
	localparam MIN_EVENT=1;
	localparam MAX_EVENT=2;
	localparam MINMAX_EVENT=3;

	initial begin
		sync_buffer <= 1'b0;
		event_timer <=0;
	end

	always @* begin
		mask_ok_min = sync_mode==MIN_EVENT || sync_mode==MINMAX_EVENT;
		mask_ok_max = sync_mode==MAX_EVENT || sync_mode==MINMAX_EVENT;
		carrier_min = (carrier == 0);
		carrier_max = (carrier == count_max);
	end

	always @(posedge clk or posedge rst) begin
		if(rst==1'b1) begin
			sync_buffer <= 1'b0;
		end
		else if((carrier_min & mask_ok_min) | (carrier_max & mask_ok_max) | sync_mode==NO_EVENT) begin
			sync_buffer <= 1'b1;
		end
		else begin
			sync_buffer <= 1'b0;
		end
	end

	 always @(posedge sync_buffer or posedge rst) begin
		if (rst) begin
				event_timer <= 0;
		end
		else if(event_timer < (event_count)) begin
				event_timer <= event_timer +1;
		end
		else begin
				event_timer <= 0;
		end
	end

	always @(posedge clk) begin
	   if(event_timer == event_count) begin
			sync <= sync_buffer;
	   end
	   else begin
			sync <= 0;
	   end
	end

endmodule