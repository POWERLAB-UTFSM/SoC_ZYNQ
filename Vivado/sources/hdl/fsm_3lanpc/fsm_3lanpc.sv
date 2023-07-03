`timescale 10ns / 10ps
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
import PKG_fsm_3lanpc::*;

/*
fsm_3lanpc INST_1
    (
    .clk(),                     // Coprocessor clock
    .reset(),                   // Global Reset
    .t_short(),                 // commutation delay times
    .t_off_on(),
    .t_on_offV0(),
    .t_offV0_on(),
    .t_off_onI0(),
    .v_lev(),                   // Voltage level (0 -> 00  /  1 -> 01   /  -1 -> 10)  
    .comm_type(),               // Type of transition defined by thermal decision block
    .S_out()                    // Power electronics transistor signals
    );
*/


module fsm_3lanpc(
    input              clk,
    input              rst,
    input   [`TDELAY_WIDTH-1:0]  t_short, t_off_on, t_on_offV0, t_offV0_on, t_off_onI0,
    input   [1:0]   v_lev,
    input   _commtypes_t   comm_type,
    output logic [5:0]  S_out
    /*,
    output logic change,
    output _states_t state,next_state,old_state,
    output logic transition,
    output logic finish_transition,
    output logic[`TDELAY_WIDTH-1:0] counter,
    output logic[`TDELAY_WIDTH-1:0] MAX_COUNTER,
    output logic[2:0] delay_timer*/
    );
    
    _states_t   state, next_state, old_state, state_mem, next_state_mem;
    logic transition;
    logic [1:0] v_lev_past;
    logic  finish_transition;
    logic[`TDELAY_WIDTH-1:0] counter;
    logic [2:0] delay_timer;
    logic[`TDELAY_WIDTH-1:0] MAX_COUNTER;
    logic change;
    logic [5:0] S_outcomb;

    always_ff @(posedge clk or posedge rst) begin

          
        if (rst) begin
            state     <= Z_U2;
            old_state <= Z_U2;
            //next_state <= Z_U2;
            v_lev_past <= 0;
            state_mem <= Z_U2;
            next_state_mem <= Z_U2;
            transition  <= 'd0;
            counter     <= 'd0;
            delay_timer <= 'd0;
            S_out <= 'b010_010;
            //finish_transition <= 0;
            //MAX_COUNTER <= 'd254;
            change<=0;
        end
        
        else begin
            v_lev_past <= v_lev;
            S_out <= S_outcomb;
            counter     <= (transition && (counter < MAX_COUNTER - 1))? counter + 'd1: 'd0;
            delay_timer <= (transition && counter == MAX_COUNTER - 1)? delay_timer + 'd1: (transition)? delay_timer:   'd0;
            transition  <= ((v_lev != v_lev_past || state != next_state) && !finish_transition)? 'd1: 'd0;
            old_state   <= (state!=next_state)? state: old_state;
            
            if(finish_transition==1) begin
                state       <= next_state;
            end
            
            
        end 
    end
    
    
    // COMBINATIONAL LOGIC FOR STATES
    always_comb begin
        next_state = state;
        //if(change) begin
            case(state)
                P   :   begin
                            if(v_lev == 'd0) begin
                                case(comm_type)
                                type_I: next_state = Z_U2;
                                type_II: next_state = Z_L2;
                                type_III: next_state = Z_L1;
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
                            if(v_lev == 'd0) begin
                                case(comm_type)
                                type_I: next_state = Z_L2;
                                type_II: next_state = Z_U2;
                                type_III: next_state = Z_U1;
                                default: next_state = Z_L2;
                                endcase
                            end               
                        end
            endcase
    end
    
    // Logic for transitions
    always_comb begin
        finish_transition=0;
        MAX_COUNTER='d255;
        //if(transition) begin
            case(state)
                Z_U2: begin // ZU2 ->
                    //S_outcomb='b010_010;
                    if(transition) begin
                        case(next_state)
                            P: begin // ZU2 -> P (type I)
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b010_000;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b110_000;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    2: begin
                                        S_outcomb='b110_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            N: begin // ZU2 -> N (type II)
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b011_010;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b001_010;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    2: begin
                                        S_outcomb='b001_110;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            //default: begin // ZU2 -> ZU2
                            //    S_outcomb='b001_110;
                            //    finish_transition=0;
                            //end                      
                        endcase
                    end
                    else begin 
                        S_outcomb='b010_010;
                    end                  
                end
                Z_U1: begin // ZU1 ->
                    //S_outcomb='b010_110; 
                    if(transition) begin
                        case(next_state)
                            P: begin // ZU1 -> P (type IU)
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b010_010;
                                        MAX_COUNTER=t_off_onI0;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b010_011;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    2: begin
                                        S_outcomb='b010_001;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    3: begin
                                        S_outcomb='b110_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            N: begin // ZU2 -> N (type III)
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b000_110;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b001_110;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            //default: begin // ZU1 -> ZU1
                            //    S_outcomb='b010_110;
                            //    finish_transition=0;
                            //end                      
                        endcase
                    end
                    else begin
                        S_outcomb='b010_110; 
                    end                  
                end
                Z_L1: begin // ZL2 ->
                    //S_outcomb='b101_001;
                    if(transition) begin
                        case(next_state)
                            P: begin // ZL2 -> P (type III)
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b100_001;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b110_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            N: begin // ZL2 -> N (type IU)
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b001_001;
                                        MAX_COUNTER=t_off_onI0;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b001_011;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    2: begin
                                        S_outcomb='b001_010;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    3: begin
                                        S_outcomb='b001_110;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                        //default: begin // ZL2 -> ZL2
                        //    S_outcomb='b001_110;
                        //    finish_transition=0;
                        //end                      
                        endcase
                    end
                    else begin
                        S_outcomb='b101_001; 
                    end                   
                end
                Z_L2: begin // ZL2 ->
                    //S_outcomb='b101_001;
                    if(transition) begin
                        case(next_state)
                            P: begin // ZL2 -> P (type II)
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b011_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b010_001;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    2: begin
                                        S_outcomb='b110_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            N: begin // ZL2 -> N (type I)
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b001_000;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b001_100;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    2: begin
                                        S_outcomb='b001_110;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            //default: begin // ZL2 -> ZL2 
                            //    S_outcomb='b001_110;
                            //    finish_transition=0;
                            //end                      
                        endcase
                    end
                    else begin
                        S_outcomb='b001_001; 
                    end                    
                end
                P: begin // P ->
                    //S_outcomb='b110_001;
                    if(transition) begin
                        case(next_state)
                            Z_U2: begin // P -> ZU2 (type I)
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b110_000;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b010_000;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    2: begin
                                        S_outcomb='b010_010;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            Z_U1: begin // P -> ZU1 (type IU) [not used in normal operation]
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b010_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b010_011;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    2: begin
                                        S_outcomb='b010_010;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    3: begin
                                        S_outcomb='b010_110;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            Z_L1: begin // P -> ZL1 (type III)
                                case(delay_timer)
                                    0: begin // S_outcomb[2] = 0
                                        S_outcomb='b100_001; 
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin // S_outcomb[3] = 1
                                        S_outcomb='b101_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            Z_L2: begin // P -> ZL2 (type II)
                                case(delay_timer)
                                    0: begin // S_outcomb[1] = 0
                                        S_outcomb='b010_001;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin // S_outcomb[3] = 1
                                        S_outcomb='b011_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    2: begin // S_outcomb[2] = 0
                                        S_outcomb='b001_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            default: begin // P -> P
                                S_outcomb='b110_001;
                                finish_transition=0;
                            end                        
                        endcase
                    end
                    else begin 
                        S_outcomb='b110_001;
                    end                   
                end
                N: begin // N ->
                    if(transition) begin
                        case(next_state)
                            Z_U2: begin // N -> ZU2 (type II)
                                case(delay_timer)
                                    0: begin // S_outcomb[4] = 0
                                        S_outcomb='b001_010;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin // S_outcomb[2] = 1
                                        S_outcomb='b011_010;
                                        MAX_COUNTER=t_on_offV0;
                                        finish_transition=0;
                                    end
                                    2: begin // S_outcomb[3] = 0
                                        S_outcomb='b010_010;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            Z_U1: begin // N -> ZU1 (type III)
                                case(delay_timer)
                                    0: begin // S_outcomb[3] = 0
                                        S_outcomb='b000_110;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    1: begin // S_outcomb[2] = 1
                                        S_outcomb='b010_110;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            Z_L1: begin // N -> ZL1 (type IU) [not used in normal operation]
                                case(delay_timer)
                                    0: begin // S_outcomb[4] = 0
                                        S_outcomb='b001_010; 
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin // S_outcomb[6] = 1
                                        S_outcomb='b001_011;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    2: begin // S_outcomb[5] = 0
                                        S_outcomb='b001_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    3: begin // S_outcomb[1] = 1
                                        S_outcomb='b101_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            Z_L2: begin // N -> ZL2 (type I)
                                case(delay_timer)
                                    0: begin // S_outcomb[5] = 0
                                        S_outcomb='b001_100;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin // S_outcomb[4] = 0
                                        S_outcomb='b001_000;
                                        MAX_COUNTER=t_short;
                                        finish_transition=0;
                                    end
                                    2: begin // S_outcomb[6] = 1
                                        S_outcomb='b001_001;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            //default: begin // N -> N
                            //    S_outcomb='b001_110;
                            //    finish_transition=0;
                            //end                        
                        endcase
                    end
                    else begin 
                        S_outcomb='b001_110;
                    end                   
                end
            endcase
//        end
//        //steady state firing signals
//        else begin
//            case(next_state)
//                P: begin
//                    S_outcomb='b110_001;
//                end
//                Z_U2: begin
//                    S_outcomb='b010_010;
//                end
//                Z_U1: begin
//                    S_outcomb='b010_110;
//                end
//                Z_L1: begin
//                    S_outcomb='b101_001;
//                end
//                Z_L2: begin
//                    S_outcomb='b001_001;
//                end
//                N: begin
//                    S_outcomb='b001_110;
//                end
//            endcase          
//        end
    end
    
                            
 
endmodule