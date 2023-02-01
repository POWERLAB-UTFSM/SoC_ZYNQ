`timescale 1ns / 1ps
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


module compare_16bits (
    input [`PWMCOUNT_WIDTH-1:0] carrier,
    input [`PWMCOUNT_WIDTH-1:0] compare,
    input _pwm_onoff pwm_onoff,
    output logic pwm
    );
    
    
    always_latch begin
        if(carrier >= compare) begin
            pwm = 'd0 && pwm_onoff;  
        end
        else begin
            pwm = 'd1 && pwm_onoff; 
        end
    end
    
endmodule
