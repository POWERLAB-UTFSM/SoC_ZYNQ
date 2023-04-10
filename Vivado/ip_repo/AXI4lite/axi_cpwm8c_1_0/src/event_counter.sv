`timescale 10ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 01:18:08 AM
// Design Name: 
// Module Name: event_counter
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


module event_counter (
    input clk,
	input reset,
	input maskevent_input,
	input _pwm_onoff pwm_onoff,
	input _carr_onoff carr_onoff,
	input _count_mode countmode,
	input _mask_mode maskmode,
	input[`EVTCOUNT_WIDTH-1:0] event_count,
	output logic maskevent_output
    );
    
	logic[`EVTCOUNT_WIDTH-1:0] event_timer;
	logic maskevent_buffer;
    
    //always_latch begin
    always_ff @(posedge maskevent_input, posedge reset) begin
        if (reset) begin
            event_timer <= 0;
        end
        else if(event_timer < event_count) begin
            event_timer <= event_timer +1;
        end
        else begin
            event_timer <= 0;
        end
	end
	
	always_comb begin
	   if(maskmode==NO_MASK) begin
		   maskevent_output = 1 & (pwm_onoff) & (carr_onoff);
	   end
	   else if(event_timer == event_count) begin
	       maskevent_output = (maskevent_input)  & (pwm_onoff) & (carr_onoff) & (countmode!=NO_COUNT);
	   end
	   else begin
	       maskevent_output = 0;
	   end
	end
    
endmodule
