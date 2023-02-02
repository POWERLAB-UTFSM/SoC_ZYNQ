`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/15/2022 03:48:06 PM
// Design Name: 
// Module Name: state_machine
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
state_machine inst_1
    (
    .clk(),                 // Coprocessor clock
    .reset(),               // Global Reset
    .v_lev(),               // Voltage level (0 -> 00  /  1 -> 01   /  -1 -> 10)  
    .z_type(),              // Type of transition defined by thermal decision block
    .S_out()                // Powe electronics transistor signals
    );
*/


module fsm3lanpc(
    input   logic           clk,
    input   logic           reset,
    input   logic[`TDELAY_WIDTH-1:0]  t_short, t_off_on, t_on_offV0, t_offV0_on, t_off_onI0,
    input   logic   [1:0]   v_lev,
    input   logic   [1:0]   z_type,
    output  logic   [5:0]   S_out
    );
    
    //enum{P, Z_U2, Z_U1, Z_L1, Z_L2, N} state = Z_U2, next_state, old_state; 
    states_t state = Z_U2, next_state, old_state;
    
    logic [5:0] comb_S_out;
    logic       transition = 'd0, finish_transition = 'd0;
    logic[`TDELAY_WIDTH-1:0] counter = 'd0;
    logic [1:0] delay_timer;
    
    logic[`TDELAY_WIDTH-1:0] MAX_COUNTER;
    
    // When the state changes 
    // 1 - update old_state
    //     set transition to 1 
    //     counter     = 0
    //     delay_timer = 0
    // 2 - keep old_state
    //     keep transition in 1
    //     counter     = 1
    //     delay_timer = 0
    // 3 - keep old_state
    //     keep transition in 1 
    //     counter     = 2
    //     delay_timer = delay_timer
    
    always_ff @(posedge clk) begin
        state       <= next_state;
        S_out       <= comb_S_out;
        old_state   <= (state != next_state)? state: old_state;
        transition  <= (state != next_state)? 'd1: (finish_transition)? 'd0: transition;
        counter     <= (counter == MAX_COUNTER - 1)?                                     'd0: (transition)? counter + 'd1: 'd0;
        delay_timer <= (!finish_transition && counter == MAX_COUNTER - 1)? delay_timer + 'd1: (transition)? delay_timer:   'd0;
    
        if (reset) begin
            state       <= Z_U2;
            S_out       <= 'b010_010;
            transition  <= 'd0;
            counter     <= 'd0;
            delay_timer <= 'd0;
        end
    end
    
    
    // COMBINATIONAL LOGIC FOR STATES
    always_comb begin
        next_state = state;
        if(!transition) begin
            case(state)
                P   :   begin
                            if(!v_lev) begin
                                case(z_type)
                                'd1: next_state = Z_U2;
                                'd2: next_state = Z_L2;
                                'd3: next_state = Z_L1;
                                default: next_state = Z_U2;
                                endcase
                            end
                        end
                Z_U2:   begin
                            if(v_lev == 'd1) 
                                next_state = P;
                            else if(v_lev == 'd2)
                                next_state = N;              
                        end
                Z_U1:   begin     
                            if(v_lev == 'd1)
                                next_state = P;
                            else if(v_lev == 'd2)
                                next_state = N;             
                        end
                Z_L1:   begin   
                            if(v_lev == 'd1)
                                next_state = P;
                            else if(v_lev == 'd2)
                                next_state = N;               
                        end
                Z_L2:   begin     
                            if(v_lev == 'd1)
                                next_state = P;
                            else if(v_lev == 'd2)
                                next_state = N;             
                        end
                N   :   begin   
                            if(!v_lev) begin
                                case(z_type)
                                'd1: next_state = Z_L2;
                                'd2: next_state = Z_U2;
                                'd3: next_state = Z_U1;
                                default: next_state = Z_L2;
                                endcase
                            end               
                        end
            endcase
        end
    end
    
    // TRANSITIONS
    transitions TRAN1
        (
        .t_short(t_short),
        .t_off_on(t_off_on),
        .t_on_offV0(t_on_offV0),
        .t_offV0_on(t_offV0_on),
        .t_off_onI0(t_off_onI0),
        .delay_timer(delay_timer),              // Timer for delay between clk
        .counter(counter),                      // Cycle counter when it is in transition clk 
        .state(state),                          // Actual state
        .old_state(old_state),                  // Old state
        .transition(transition),                // 1 -> Transition in process / 0 -> Transition finished
        .S_out(S_out),                          // Synchronized S_out
        .MAX_COUNTER(MAX_COUNTER),              // MAX_COUNTER
        .finish_transition(finish_transition),  // Flag to finish transition 
        .comb_S_out(comb_S_out)                 // Combination S_out
        );
    

endmodule
