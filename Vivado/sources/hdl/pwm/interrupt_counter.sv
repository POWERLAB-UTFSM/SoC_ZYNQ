`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 01:18:08 AM
// Design Name: 
// Module Name: interrupt_counter
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


module interrupt_counter (
    input clk,
	input reset,
	input mask_event,
	input _pwm_onoff pwm_onoff,
	input _int_onoff int_onoff,
	input[`INTCOUNT_WIDTH-1:0] event_count,
	output logic interrupt
    );
    
	logic[`INTCOUNT_WIDTH-1:0] int_counter;
	logic int_buffer;
    
    always_ff @(posedge mask_event, posedge reset) begin
        if (reset) begin
            int_counter <= 0;
        end
        else if(int_counter < event_count) begin
            int_counter <= int_counter +1;
        end
        else begin
            int_counter <= 0;
        end
	end
	
	always_comb begin
	   if(int_counter == event_count) begin
	       interrupt = mask_event & int_onoff & pwm_onoff;
	   end
	   else begin
	       interrupt = 0;
	   end
	end
    
endmodule
