`timescale 10ns / 100ps
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
    //input clk,
    input reset,
    input logic maskevent,
    input _pwm_onoff pwm_onoff,
    input logic [`PWMCOUNT_WIDTH-1:0] reg_in,
    output logic [`PWMCOUNT_WIDTH-1:0] reg_out
    );
    
    //logic refresh;
    
    /*always_ff @(posedge maskevent, posedge reset) begin
      if (maskevent==1'b1 | pwm_onoff==PWM_ON) begin
         reg_out <= reg_in;
      end
      else if (reset) begin
        reg_out <= 0; 
      end
    end*/
    
    
    /*always_ff @(posedge clk, posedge reset) begin
        if(reset) begin
            reg_out <= 0;
        end
        else if(maskevent==1'b1 | pwm_onoff==PWM_OFF) begin
            reg_out <= reg_in;
        end
    endcase*/
    
    always_latch begin    
        if(reset==1'b1 || pwm_onoff==PWM_OFF || maskevent==1'b1) begin
            reg_out <= reg_in;
        end
    end
endmodule
