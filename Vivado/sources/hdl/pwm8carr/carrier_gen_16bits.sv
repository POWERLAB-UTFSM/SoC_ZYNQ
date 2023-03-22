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
    logic init_carr_change;
    //_pwm_onoff pwmcarr_onoff;
    
    //assign pwmcarr_onoff = _pwm_onoff'(_pwm_onoff'(pwm_onoff)) || (_carr_onoff'(carr_onoff));
    
    always_ff @(posedge clk or posedge reset) begin
        if(reset==1'b1) begin
            maskevent <= 1'b0;
        end
        else if (mask_mode==NO_MASK) begin
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
    
    always_ff @(posedge clk or posedge reset) begin
        if(reset==1'b1) begin
            //state_carrier <= UP;
            //carrier <= 'd0;
            carrier_mask <= 1'b0;
            init_carr_change <= 0;
            init_carr_buff <= init_carr;
            //state_carrier <=UP;
            //maskevent <= 1'b0;
            //init_carr_buff <= 1'b0;
        end
        
        //PWM off
        else if (pwm_onoff==PWM_OFF || carr_onoff==CARR_OFF || period=='d0) begin
            //carrier <= 'd0;
            carrier_mask <= 1'b0;
        end
        
        else if(init_carr_buff!=init_carr) begin
            carrier_mask <= 1'b0;
            init_carr_change <= 1;
            init_carr_buff <= init_carr;
        end
        
        else begin
            carrier_mask <= 1'b1;
            init_carr_change <= 0;
        end
    end
    
    always_ff @(posedge clk or posedge reset) begin
        if(reset) begin
            carrier <=0;
            state_carrier<=UP;
        end
        else if(carrier_mask==1'b0) begin
            if(init_carr_change==1) begin
                carrier <= init_carr;
            end
            /*else if(reset==1'b1) begin 
                carrier <= 0;
                state_carrier<=UP;
            end*/
            else begin
                carrier <= 0;
            end
            //state_carrier <= UP;
        end
        
        else if(carrier_mask==1'b1) begin
            if(carrier<period && state_carrier==UP) begin
                carrier <= carrier + 'd1;
            end
            else if(carrier>0 && state_carrier==DOWN) begin
                carrier <= carrier - 'd1;
            end
            
            else if(carrier>=period) begin
                if(count_mode==COUNT_UP) begin
                    carrier <= 0;
                    state_carrier<=UP;
                end
                if(count_mode==COUNT_DOWN || count_mode==COUNT_UPDOWN) begin
                    state_carrier<=DOWN;
                end
            end
            else if(carrier<=0) begin
                if(count_mode==COUNT_DOWN) begin
                    carrier <= period;
                    state_carrier<=DOWN;
                end
                if(count_mode==COUNT_UP || count_mode==COUNT_UPDOWN) begin
                    state_carrier<=UP;
                end
            end
            /*if(count_mode== COUNT_UP) begin
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
            
            else if(count_mode == COUNT_UPDOWN) begin
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
            end*/
        end
    end 
    
endmodule