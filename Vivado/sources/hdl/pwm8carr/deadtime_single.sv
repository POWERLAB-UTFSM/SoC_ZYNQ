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

import PKG_pwm::*;

module deadtime_single (
    input clk,
	input reset,
	input pwmin_X,
	input [`DTCOUNT_WIDTH-1:0] dtime_X,
	//input [`DTCOUNT_WIDTH-1:0] dtime_B,
	input logic_X,
	//input logic_B,
	input _pwm_onoff pwm_onoff,
	input _dt_onoff dt_onoff,
	output wire pwmout_X
	//output logic pwmout_B
    );
    
    typedef enum logic [1:0] {S_OFF,S_DTCOUNT,S_ON} _state_dtime;
    _state_dtime dtime_state;
    _state_dtime dtime_state_next;
    
    logic pwm_X;
    //wire pwmaux_X;
    logic [`DTCOUNT_WIDTH-1:0] dt_counter;
    
    always_comb begin
    //always_ff @(posedge clk) begin
    //------------------------------------
    //Conditional state transition
        dtime_state_next=dtime_state;
        case(dtime_state)
            S_OFF: begin
                if(pwmin_X==1) begin
                    dtime_state_next = S_DTCOUNT;
                end
                else begin
                    dtime_state_next = S_OFF;
                end
            end 
            S_DTCOUNT: begin
                if(dt_counter>=dtime_X) begin
                    dtime_state_next = S_ON;
                end
                else if(pwmin_X==0) begin
                    dtime_state_next = S_OFF;
                end
                else begin
                    dtime_state_next = S_DTCOUNT;
                end
            end
            S_ON: begin
                if(pwmin_X==0) begin
                    dtime_state_next = S_OFF;
                end
                else begin
                    dtime_state_next = S_ON;
                end
            end
        endcase
    end
    
    always_ff @(posedge clk) begin
        //------------------------------------
        //State actions
        case(dtime_state_next)
            S_OFF: begin
                pwm_X = 0;
                dt_counter = 0;
            end
            S_DTCOUNT: begin
                dt_counter = dt_counter + 1;
            end
            S_ON: begin
                pwm_X = 1;
            end
        endcase
    end
    
    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
            dtime_state = S_OFF;
        end
        else begin
            dtime_state = dtime_state_next;
        end 
    end
    
    assign pwmout_X = (dt_onoff==DT_ON) ?  (pwm_X ^ ~logic_X) & pwm_onoff: (pwmin_X ^ ~logic_X) & pwm_onoff;
    //always_ff @(posedge clk or posedge reset) begin

    /*always_comb begin
        if (dt_onoff == DT_ON) begin
            pwmout_X = pwm_X ^ ~logic_X;
        end
        else if (dt_onoff == DT_OFF) begin
            pwmout_X = pwmin_X ^ ~logic_X;
        end
    end*/
    
endmodule
