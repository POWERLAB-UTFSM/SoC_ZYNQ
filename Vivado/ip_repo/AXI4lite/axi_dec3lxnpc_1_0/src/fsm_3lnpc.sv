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
import PKG_decoder_3lxnpc::*;

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


module fsm_3lnpc(
    input              clk,
    input              rst,
    input   [`TDELAY_WIDTH-1:0]  t_short, t_off_on,
    input   [1:0]   v_lev,
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
    
    _statesnpc_t   state, next_state, old_state, state_mem, next_state_mem;
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
            state     <= ZZ;
            old_state <= ZZ;
            //next_state <= Z_U2;
            v_lev_past <= 0;
            state_mem <= ZZ;
            next_state_mem <= ZZ;
            transition  <= 'd0;
            counter     <= 'd0;
            delay_timer <= 'd0;
            S_out <= 'b01_10_00;
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
                PP   :   begin
                            if(v_lev == 'd0) begin
                                next_state = ZZ;
                            end
                        end
                ZZ:   begin
                            if(v_lev == 'd1) 
                                next_state = PP;
                            else if(v_lev == 'd2)
                                next_state = NN;              
                        end
                NN   :   begin   
                            if(v_lev == 'd0) begin
                                next_state = ZZ;
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
                ZZ: begin // Z ->
                    //S_outcomb='b011_0XX;
                    if(transition) begin
                        case(next_state)
                            PP: begin // ZU2 -> P (type I)
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b01_00_00;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b11_00_00;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            NN: begin // Z -> N (type II)
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b00_10_00;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b00_11_00;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            default: begin // Z -> Z
                                S_outcomb='b01_10_00;
                                finish_transition=0;
                            end                     
                        endcase
                    end
                    else begin 
                        S_outcomb='b01_10_00;
                    end                  
                end
                PP: begin // P ->
                    //S_outcomb='b11_00_00;
                    if(transition) begin
                        case(next_state)
                            ZZ: begin // P -> Z
                                case(delay_timer)
                                    0: begin
                                        S_outcomb='b01_00_00;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin
                                        S_outcomb='b01_10_00;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            default: begin // P -> P
                                S_outcomb='b11_00_00;
                                finish_transition=0;
                            end                        
                        endcase
                    end
                    else begin 
                        S_outcomb='b11_00_00;
                    end                   
                end
                NN: begin // N ->
                    if(transition) begin
                        case(next_state)
                            ZZ: begin // N -> Z
                                case(delay_timer)
                                    0: begin // S_outcomb[4] = 0
                                        S_outcomb='b00_10_00;
                                        MAX_COUNTER=t_off_on;
                                        finish_transition=0;
                                    end
                                    1: begin // S_outcomb[2] = 1
                                        S_outcomb='b01_10_00;
                                        MAX_COUNTER=t_short;
                                        finish_transition=(counter==(MAX_COUNTER-1)) ? 1 : 0;
                                    end
                                endcase
                            end
                            default: begin // N -> N
                                S_outcomb='b00_11_00;
                                finish_transition=0;
                            end                        
                        endcase
                    end
                    else begin 
                        S_outcomb='b00_11_00;
                    end                   
                end
            endcase
    end
    
                            
 
endmodule