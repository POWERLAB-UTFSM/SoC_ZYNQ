`timescale 10ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 01:18:08 AM
// Design Name: 
// Module Name: compare_16bits
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

module comparator_16bits (
    // system clock
    input clk,
    // system reset
    //input reset,
    input [`PWMCOUNT_WIDTH-1:0] carrier,
    input [`PWMCOUNT_WIDTH-1:0] carrier_master,
    input [`PWMCOUNT_WIDTH-1:0] compare,
    input _carr_sel carrsel,
    input _pwm_onoff pwm_onoff,
    input _dt_onoff dt_onoff,
    output wire pwmout_A,
    output wire pwmout_B
    );
    
    logic pwm;
    logic [`PWMCOUNT_WIDTH-1:0] carrier_aux;
    
    assign carrier_aux = (carrsel==CARR_MASTER1) ? carrier_master : carrier;
    //-------------------
    // PWM
    //-------------------
    always_ff @(posedge clk) begin
        if(carrier_aux >= compare) begin
            pwm = 'd0 && pwm_onoff;  
        end
        else begin
            pwm = 'd1 && pwm_onoff; 
        end
    end
    
    //always_comb begin
        assign pwmout_A = pwm;
        assign pwmout_B = ~pwm && (dt_onoff ==DT_ON);
    //end
        
endmodule
