`timescale 10ns / 100ps
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
    //input _mask_mode mask_mode,
    input _pwm_onoff pwm_onoff,
    input _carr_onoff carr_onoff,
    output logic [`PWMCOUNT_WIDTH-1:0] carrier
    //output logic maskevent
    );

    //------------------------------------
    //State definition
    typedef enum logic [2:0] {S_RESET0,S_UP,S_DOWN,S_RESETP,S_STOP,S_NEWCARR} _state_counter;
    _state_counter counter_state;
    _state_counter counter_state_next;
    logic stop_status;
    logic [`PWMCOUNT_WIDTH-1:0] init_carr_buffer;
    logic new_carrier;
    
    always_comb begin
        if(count_mode==NO_COUNT || period == 0 || pwm_onoff == PWM_OFF || carr_onoff==CARR_OFF) begin
            stop_status=1;
        end
        else begin
            stop_status=0;
        end
    end
    
    //always_comb begin
    /*always_ff @(posedge clk) begin
        if(init_carr !=init_carr_buffer) begin
            new_carrier=1;
        end
    end*/
    
    always_comb begin
    //always_ff @(posedge clk) begin
    //------------------------------------
    //Conditional state transition
        counter_state_next=counter_state;
        case(counter_state) 
            S_RESET0: begin
                if(stop_status==1) begin
                    counter_state_next = S_STOP;
                end
                else
                if (new_carrier==1) begin
                    counter_state_next = S_NEWCARR;
                end
                else  
                if(count_mode==COUNT_DOWN) begin
                    counter_state_next = S_RESETP;
                end
                else
                if((count_mode==COUNT_UP || count_mode==COUNT_UPDOWN) && carrier < (period-1)) begin
                    counter_state_next = S_UP;
                end
                
            end
            S_RESETP: begin
                if(stop_status==1) begin
                    counter_state_next = S_STOP;
                end
                else
                if (new_carrier==1) begin
                    counter_state_next = S_NEWCARR;
                end
                else
                if(count_mode==COUNT_DOWN && carrier > 1) begin
                    counter_state_next = S_DOWN;
                end
                else 
                if(count_mode==COUNT_UP || count_mode==COUNT_UPDOWN) begin
                    counter_state_next = S_UP;
                end
                
            end
            S_UP: begin
                if(stop_status==1) begin
                    counter_state_next = S_STOP;
                end
                else
                if (new_carrier==1) begin
                    counter_state_next = S_NEWCARR;
                end
                else 
                if((count_mode==COUNT_UPDOWN || count_mode==COUNT_DOWN) && carrier >= (period-1)) begin
                    counter_state_next = S_DOWN;
                end
                else 
                if(count_mode==COUNT_UP && carrier >= (period-1)) begin
                    counter_state_next = S_RESET0;
                end
                
            end
            S_DOWN: begin
                if(stop_status==1) begin
                    counter_state_next = S_STOP;
                end
                else
                if (new_carrier==1) begin
                    counter_state_next = S_NEWCARR;
                end
                else 
                if((count_mode==COUNT_UPDOWN || count_mode==COUNT_UP) && carrier <=1) begin
                    counter_state_next = S_UP;
                end
                else 
                if(count_mode==COUNT_DOWN && carrier <= 1) begin
                    counter_state_next = S_RESETP;
                end
                
            end
            S_STOP: begin
                if(stop_status==1) begin
                    counter_state_next = S_STOP;
                end
                else begin 
                    counter_state_next = S_NEWCARR;
                end
                /*if((count_mode==COUNT_UPDOWN || count_mode==COUNT_UP) && carrier < (period-1)) begin
                    counter_state_next = S_UP;
                end
                else 
                if((count_mode==COUNT_UPDOWN || count_mode==COUNT_DOWN ) && carrier > 1) begin
                    counter_state_next = S_DOWN;
                end
                else 
                if(carrier >= (period-1) && stop_status==0) begin
                    counter_state_next = S_RESETP;
                end
                else 
                if(carrier <= 1 && stop_status==0) begin
                    counter_state_next = S_RESET0;
                end*/
            end
            S_NEWCARR: begin
                if(stop_status==1) begin
                    counter_state_next = S_STOP;
                end
                else 
                if((count_mode==COUNT_UPDOWN || count_mode==COUNT_UP) && carrier < (period-1)) begin
                    counter_state_next = S_UP;
                end
                else 
                if((count_mode==COUNT_UPDOWN || count_mode==COUNT_DOWN ) && carrier > 0) begin
                    counter_state_next = S_DOWN;
                end
                else 
                if(carrier >= (period-1) && stop_status==0) begin
                    counter_state_next = S_RESETP;
                end
                else 
                if(carrier <= 1 && stop_status==0) begin
                    counter_state_next = S_RESET0;
                end
            end
        endcase
            
    end
    
    always_ff @(posedge clk or posedge reset) begin
        if (reset) begin
            counter_state <= S_NEWCARR;
            init_carr_buffer <=0;
        end
        else begin
            counter_state <= counter_state_next;
            init_carr_buffer <=init_carr;
        end
    end
    
    always_ff @(posedge clk) begin
        //------------------------------------
        //State actions
        if(init_carr !=init_carr_buffer) begin
            new_carrier=1;
        end
        case(counter_state) 
            S_RESET0: begin
                carrier = 0;
            end
            S_RESETP: begin
                carrier = (period) ;
            end
            S_UP: begin
                carrier = (carrier +1) ;
            end
            S_DOWN: begin
                carrier = (carrier -1) ;
            end
            S_STOP: begin
                carrier = 0;
            end
            S_NEWCARR: begin
                carrier = init_carr;
                new_carrier=0;
            end
        endcase
    end
    
endmodule