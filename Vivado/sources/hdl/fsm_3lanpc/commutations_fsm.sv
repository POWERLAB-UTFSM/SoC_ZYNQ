`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/20/2022 08:13:06 PM
// Design Name: 
// Module Name: transitions
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
import PKG_fsm_3lanpc::*;

/*
transitions inst_1
    (
    .t_short(),
    .t_off_on(),
    .t_on_offV0(),
    .t_offV0_on(),
    .t_off_onI0(),
    .delay_timer(),         // Timer for delay between transitions
    .counter(counter),      // Cycle counter when it is in transition mode
    .state(),               // Actual state
    .old_state(),           // Old state
    .transition(),          // 1 -> Transition in process / 0 -> Transition finished
    .S_out(),               // Synchronized S_out
    .MAX_COUNTER(),         // MAX_COUNTER
    .finish_transition(),   // Flag to finish transition 
    .comb_S_out()           // Combination S_out
    );
*/

module commutations_fsm(
    input clk,
    input rst,
    input  logic[`TDELAY_WIDTH-1:0]          t_short, t_off_on, t_on_offV0, t_offV0_on, t_off_onI0,
    input  _states_t                         state, old_state, next_state,  
    output logic transition,      
    output logic [0:5]  S_out_rev
    );
    
    logic  finish_transition = 'd0;
    logic[`TDELAY_WIDTH-1:0] counter = 'd0;
    logic [1:0] delay_timer;
    logic[`TDELAY_WIDTH-1:0] MAX_COUNTER;
    logic [5:0]  comb_S_out;
    logic [5:0] S_out;
    
    assign S_out_rev=S_out;
    
    always_ff @(posedge clk or posedge rst) begin
        S_out <= comb_S_out;
        transition  <= (state != next_state)? 'd1: (finish_transition)? 'd0: transition;
        counter     <= (counter == MAX_COUNTER - 1)?                                     'd0: (transition)? counter + 'd1: 'd0;
        delay_timer <= (!finish_transition && counter == MAX_COUNTER - 1)? delay_timer + 'd1: (transition)? delay_timer:   'd0;
    
        if (rst) begin
            transition  <= 'd0;
            counter     <= 'd0;
            delay_timer <= 'd0;
            S_out <= 'b010_010;
        end
    end
    
    // Logic for transitions
    always_comb begin
        finish_transition = 'd0;
        comb_S_out = S_out;
        MAX_COUNTER = 100;
        
        case(next_state)
            P   :   begin
                        comb_S_out = 'b110_001;
                        if(transition) begin
                            case(state)
                                Z_U2:   begin // 'b010_010
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out  = 'b010_000;  //S(1) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd1: begin
                                                        comb_S_out = 'b110_000;  //S(5) = 1;
                                                        MAX_COUNTER = t_short;
                                                     end
                                                'd2: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == (MAX_COUNTER - 1))? 'd1: 'd0; //S(0) = 1;
                                                     end
                                            endcase
                                        end
                                Z_U1:   begin // 'b010_110
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b010_010;  //S(2) = 0;
                                                        MAX_COUNTER = t_off_onI0;
                                                     end
                                                'd1: begin
                                                        comb_S_out = 'b010_011;  //S(0) = 1;
                                                        MAX_COUNTER = t_short;
                                                     end
                                                'd2: begin
                                                        comb_S_out = 'b010_001;  //S(1) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd3: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(5) = 1;
                                                     end
                                            endcase
                                        end
                                Z_L1:   begin // 'b101_001
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b100_001;  //S(3) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd1: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(4) = 1;
                                                     end
                                            endcase
                                        end
                                Z_L2:   begin // 'b001_001
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b011_001;  //S(4) = 1;
                                                        MAX_COUNTER = t_short;
                                                     end
                                                'd1: begin
                                                        comb_S_out = 'b010_001;  //S(3) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd2: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(5) = 1;
                                                     end
                                            endcase
                                        end
                            endcase
                        end
                    end
            Z_U2:   begin
                        comb_S_out = 'b010_010;
                        if(transition) begin
                            case(state)
                                P:    begin // 'b110_001
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b110_000;  //S(0) = 0;
                                                        MAX_COUNTER = t_short;
                                                     end
                                                'd1: begin
                                                        comb_S_out = 'b010_000;  //S(5) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd2: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(2) = 1;                                                        
                                                     end
                                            endcase
                                        end
                                N:    begin // 'b001_110
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b001_010;  //S(2) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd1: begin
                                                        comb_S_out = 'b011_010;  //S(4) = 1;
                                                        MAX_COUNTER = t_on_offV0;
                                                     end
                                                'd2: begin
                                                        MAX_COUNTER = t_on_offV0;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(3) = 0;
                                                     end
                                            endcase
                                        end
                            endcase
                        end            
                    end
            Z_U1:   begin     
                        comb_S_out = 'b010_110;
                        if(transition) begin
                            case(state)
                                N:    begin // 'b001_110
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b000_110;  //S(3) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd1: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(4) = 1;
                                                     end
                                            endcase
                                        end
                            endcase
                        end            
                    end
            Z_L1:   begin   
                        comb_S_out = 'b101_001;
                        if(transition) begin
                            case(state)
                                P:    begin // 'b110_001
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b100_001;  //S(4) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd1: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(3) = 1;
                                                     end
                                            endcase
                                        end
                            endcase
                        end                      
                    end
            Z_L2:   begin     
                        comb_S_out = 'b001_001;
                        if(transition) begin
                            case(state)
                                P:    begin // 'b110_001
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b010_001;  //S(5) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd1: begin
                                                        comb_S_out = 'b011_001;  //S(3) = 1;
                                                        MAX_COUNTER = t_on_offV0;
                                                     end
                                                'd2: begin
                                                        MAX_COUNTER = t_offV0_on;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(4) = 0;
                                                     end
                                            endcase
                                        end
                                N:    begin // 'b001_110
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b001_100;  //S(1) = 0;
                                                        MAX_COUNTER = t_short;
                                                     end
                                                'd1: begin
                                                        comb_S_out = 'b001_000;  //S(2) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd2: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(0) = 1;
                                                     end
                                            endcase
                                        end
                            endcase
                        end            
                    end
            N   :   begin   
                        comb_S_out = 'b001_110;
                        if(transition) begin
                            case(state)
                                Z_U2:   begin // 'b010_010
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b011_010;  //S(3) = 1;
                                                        MAX_COUNTER = t_short;
                                                     end
                                                'd1: begin
                                                        comb_S_out = 'b001_010;  //S(4) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd2: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(2) = 1;
                                                     end
                                            endcase
                                        end
                                Z_U1:   begin // 'b010_110
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b000_110;  //S(4) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd1: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(3) = 1;
                                                     end
                                            endcase
                                        end
                                Z_L1:   begin // 'b101_001
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b001_001;  //S(5) = 0;
                                                        MAX_COUNTER = t_off_onI0;
                                                     end
                                                'd1: begin
                                                        comb_S_out = 'b001_011;  //S(1) = 1;
                                                        MAX_COUNTER = t_short;
                                                     end
                                                'd2: begin
                                                        comb_S_out = 'b001_010;  //S(0) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd3: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(2) = 1;
                                                     end
                                            endcase
                                        end
                                Z_L2:   begin // 'b001_001
                                            case(delay_timer)
                                                'd0: begin
                                                        comb_S_out = 'b001_000;  //S(0) = 0;
                                                        MAX_COUNTER = t_off_on;
                                                     end
                                                'd1: begin
                                                        comb_S_out = 'b001_100;  //S(2) = 1;
                                                        MAX_COUNTER = t_short;
                                                     end
                                                'd2: begin
                                                        MAX_COUNTER = t_short;
                                                        finish_transition = (counter == MAX_COUNTER - 1)? 'd1: 'd0; //S(1) = 1;
                                                     end
                                            endcase
                                        end
                            endcase
                        end            
                    end
        endcase
    end
endmodule
