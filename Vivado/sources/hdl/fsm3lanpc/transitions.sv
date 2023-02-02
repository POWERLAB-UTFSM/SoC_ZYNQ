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
import PKG_fsm3lanpc::*;

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

module transitions(
    input  logic[`TDELAY_WIDTH-1:0]          t_short, t_off_on, t_on_offV0, t_offV0_on, t_off_onI0,
    input  logic [1:0]  delay_timer,
    input  logic[`TDELAY_WIDTH-1:0]          counter,
    input  states_t     state,      
                        old_state,
    input  logic        transition,
    input  logic [5:0]  S_out,
    output logic[`TDELAY_WIDTH-1:0]          MAX_COUNTER,
    output logic        finish_transition,
    output logic [5:0]  comb_S_out
    );
    
    // Logic for transitions
    always_comb begin
        finish_transition = 'd0;
        comb_S_out = S_out;
        MAX_COUNTER = 100;
        
        case(state)
            P   :   begin
                        comb_S_out = 'b110_001;
                        if(transition) begin
                            case(old_state)
                                Z_U2:   begin // 'd010_010
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
                                Z_U1:   begin // 'd010_110
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
                                Z_L1:   begin // 'd101_001
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
                                Z_L2:   begin // 'd001_001
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
                            case(old_state)
                                P:    begin // 'd110_001
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
                                N:    begin // 'd001_110
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
                            case(old_state)
                                N:    begin // 'd001_110
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
                            case(old_state)
                                P:    begin // 'd110_001
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
                            case(old_state)
                                P:    begin // 'd110_001
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
                                N:    begin // 'd001_110
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
                            case(old_state)
                                Z_U2:   begin // 'd010_010
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
                                Z_U1:   begin // 'd010_110
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
                                Z_L1:   begin // 'd101_001
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
                                Z_L2:   begin // 'd001_001
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

