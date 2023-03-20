`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 12:57:42 AM
// Design Name: 
// Module Name: carrier_gen_16bits
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

module carrier_gen_16bits(
    input clk,
    input reset,
    input [`PWMCOUNT_WIDTH-1:0] period,
    input [`PWMCOUNT_WIDTH-1:0] init_carr,
    input _count_mode count_mode,
    input _mask_mode mask_mode,
    input _pwm_onoff pwm_onoff,
    input _carr_onoff carr_onoff,
    output logic [`PWMCOUNT_WIDTH-1:0] carrier,
    output logic maskevent
    );
    
    enum bit {UP, DOWN} state_carrier;
    logic carrier_mask;
    logic [`PWMCOUNT_WIDTH-1:0] init_carr_buff;
    wire pwmcarr_onoff;
    
    assign pwmcarr_onoff = (_pwm_onoff'(pwm_onoff)) || (_pwm_onoff'(carr_onoff));
    
    always_ff @(posedge clk or posedge reset) begin
        
        if(reset==1'b1) begin
            state_carrier <= UP;
            carrier <= 15'b0;
            carrier_mask <= 1'b0;
            maskevent <= 1'b0;
            //init_carr_buff <= 1'b0;
        end
        
        //PWM off
        else if (pwmcarr_onoff==PWM_OFF || period==0) begin
            carrier <= 15'b0;
            carrier_mask <= 1'b0;
        end
        
        //PWM on
        else begin
            if(carrier_mask==0) begin
                carrier <= init_carr;
                carrier_mask <= 1'b1;
                init_carr_buff <= init_carr;
                //state_carrier <= UP;
            end

            else if(carrier_mask==1 && period>'d0) begin

                if(count_mode== COUNT_UP) begin
                    state_carrier <= UP;
                    if(carrier <(period)) begin
                        carrier <= carrier + 'd1;
                    end
                    else begin
                        carrier <= 'd0;
                    end
                end
                
                else if(count_mode== COUNT_DOWN) begin
                    state_carrier <= DOWN;
                    if(carrier >(0)) begin
                        carrier <= carrier - 'd1;
                    end
                    else begin
                        carrier <= period;
                    end
                end
                
                else if(count_mode ==COUNT_UPDOWN) begin
                    if(carrier <(period) && state_carrier == UP) begin
                        carrier <= carrier + 'd1;
                        state_carrier <= UP;
                    end
                    
                    else if ((carrier >(0) && state_carrier == DOWN) || carrier >period) begin        
                        carrier <= carrier - 'd1;
                        state_carrier <= DOWN;
                    end
                    
                    else if(carrier==period) begin
                        state_carrier <= DOWN;
                    end
                    
                    else if(carrier=='d0) begin
                        state_carrier <= UP;
                    end
                end
                
                if(init_carr_buff!=init_carr) begin
                    carrier_mask <= 1'b0;
                end
            end
            
            if (mask_mode==NO_MASK) begin
                maskevent <= 1'b1;
            end
            else if(carrier == 1'b0 && (mask_mode==MIN_MASK || mask_mode==MINMAX_MASK)) begin
                maskevent <= 1'b1;
            end
            else if(carrier == period && (mask_mode==MAX_MASK || mask_mode==MINMAX_MASK)) begin
                maskevent <= 1'b1;
            end
            else begin
                maskevent  <= 1'b0;
            end
        end 
    end 
    
endmodule