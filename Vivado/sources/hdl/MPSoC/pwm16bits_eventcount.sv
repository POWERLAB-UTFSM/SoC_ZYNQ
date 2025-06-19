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
	input [15:0] carrier_max,
	input [15:0] carrier,
	input [3:0] event_count,
	input [1:0] sync_mode,
	output reg sync
);
	
	//--------------------------------
	//Interrupt generator
	/*reg mask_ok_min;
	reg mask_ok_max;
	reg carrier_event_min;
	reg carrier_event_max;*/

	reg sync_buffer;
	reg [3:0] event_timer;

	localparam NO_EVENT=0;
	localparam MIN_EVENT=1;
	localparam MAX_EVENT=2;
	localparam MINMAX_EVENT=3;

	/*wire mask_ok_min;
	wire mask_ok_max;
	wire carrier_event_min;
	wire carrier_event_max;*/

	initial begin
		//sync_buffer <= 1'b0;
		event_timer <=0;
	end

	always@* begin 
	/*	assign mask_ok_min = sync_mode==MIN_EVENT || sync_mode==MINMAX_EVENT;
		assign mask_ok_max = sync_mode==MAX_EVENT || sync_mode==MINMAX_EVENT;
		assign carrier_event_min = (carrier == 0);
		assign carrier_event_max = (carrier == carrier_max);*/
		sync_buffer <= (((carrier_max!=0) && (carrier == 0) && (sync_mode==MIN_EVENT || sync_mode==MINMAX_EVENT)) || ((carrier == carrier_max) && (sync_mode==MAX_EVENT || sync_mode==MINMAX_EVENT)) || (sync_mode==NO_EVENT)) ? 1'b1 : 1'b0;
	end


	always @(posedge clk or posedge rst) begin
		if (rst) begin
				event_timer <= 3'b0000;
				sync <= 1;
		end
		else if (sync_buffer==1 ) begin
			if((event_timer < event_count) && sync_mode!=NO_EVENT && carrier_max!=0) begin
				event_timer <= event_timer +1;
				sync <= 0;
			end
			else begin
				event_timer <= 3'b0000;
				sync <= 1;
			end
		end
		else begin
			event_timer <= event_timer;
			sync <= 0;
		end
	end

endmodule