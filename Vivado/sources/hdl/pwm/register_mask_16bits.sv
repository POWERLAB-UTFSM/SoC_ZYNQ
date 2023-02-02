`timescale 10ns / 10ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 03:09:25 AM
// Design Name: 
// Module Name: register_mask_16bits
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

module register_mask_16bits(
    input clk,
    input reset,
    input logic mask_event,
    input _pwm_onoff pwm_onoff,
    input logic [`PWMCOUNT_WIDTH-1:0] reg_in,
    output logic [`PWMCOUNT_WIDTH-1:0] reg_out
    );
    
    logic refresh;
    
    always_ff @(posedge clk, posedge reset) begin

        if(mask_event==1'b1 || pwm_onoff==PWM_OFF) begin
            reg_out <= reg_in;
        end
        else if(reset) begin
            reg_out <= 0;
        end
    end
    
//    always_ff @(posedge reset) begin    
//        if(reset) begin
//            reg_out <= reg_in;
//        end
//    end
endmodule
