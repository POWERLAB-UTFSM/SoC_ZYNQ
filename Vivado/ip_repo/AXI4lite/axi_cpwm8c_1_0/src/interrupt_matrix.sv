`timescale 10ns / 100ps
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 12:57:42 AM
// Design Name: 
// Module Name: interrupt_matrix
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



module interrupt_matrix(
    input clk,
    input reset,
	input  [`PWM_WIDTH-1:0] interrupt_in ,
    input  [`PWM_WIDTH-1:0] matrix ,
    input logic int_ack,
    input logic wire_ack,
	output trigger_out,
	output logic interrupt_out
);

    logic [`PWM_WIDTH-1:0] matrix_aux;
    logic [`PWM_WIDTH-1:0] result;
    logic [3:0] cnt;
    typedef enum {
        S_ack,
        S_int,
        S_wait
    } State_int;
    
    State_int state,state_next;
    
    always_comb begin
        if (reset) begin
            matrix_aux <= 0;
        end
        else begin
            matrix_aux <= matrix;
        end
    end
	
	//assign interrupt_out=interrupt_in & matrix_aux;
	genvar i;
    generate
        for (i=0; i<`PWM_WIDTH; i=i+1) begin
            assign result[i]=interrupt_in[i] & matrix_aux[i];
        end 
    endgenerate
    assign trigger_out = | result;

    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= S_ack;
            cnt=0;
        end
        else begin
            state <= state_next;
            if(state==S_int) begin
                cnt=cnt+1;
            end
            else begin
                cnt=0;
            end
        end
    end
    

    always_comb begin
        state_next = state;
        case (state)
            S_ack: begin
                interrupt_out = trigger_out;
                state_next = trigger_out ? S_int : S_ack;
            end
            S_int: begin
                interrupt_out = 1'b1;
                state_next = (cnt==4'b1111) ? S_wait : ((int_ack==1 || wire_ack==1) ? S_ack: S_int);
            end
            S_wait: begin
                interrupt_out = 1'b0;
                state_next = (int_ack==1 || wire_ack==1) ? S_ack : S_wait;
            end
            default: begin
                interrupt_out = 1'b0;
                state_next = S_wait;
            end
        endcase
  end
    
endmodule