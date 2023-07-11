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

module decoder_3lxnpc(
    input              clk,
    input              rst,
    input   [`TDELAY_WIDTH-1:0]  t_short, t_off_on, t_on_offV0, t_offV0_on, t_off_onI0,
    input   [1:0]   v_lev,
    input   _commtypes_t   comm_type_anpc,
    input _npctypes_t npc_type,
    output logic [5:0]  S_out
    );

    logic [5:0]  S_out_ANPC;
    logic [5:0]  S_out_NPC;
    logic [5:0]  S_out_NPP;

    fsm_3lanpc FSM3LANPC(
        .clk(clk),
        .rst(rst),
        .t_short(t_short),
        .t_off_on(t_off_on),
        .t_on_offV0(t_on_offV0),
        .t_offV0_on(t_offV0_on),
        .t_off_onI0(t_off_onI0),
        .v_lev(v_lev),
        .comm_type(comm_type_anpc),
        .S_out(S_out_ANPC)
    );

    fsm_3lnpc FSM3LNPC(
        .clk(clk),
        .rst(rst),
        .t_short(t_short),
        .t_off_on(t_off_on),
        .v_lev(v_lev),
        .S_out(S_out_NPC)
    );

    fsm_3lnpp FSM3LNPP(
        .clk(clk),
        .rst(rst),
        .t_short(t_short),
        .t_off_on(t_off_on),
        .v_lev(v_lev),
        .S_out(S_out_NPP)
    );
    
    always_comb begin
        case(npc_type)
            NoOut: begin
                S_out <= 'b000_000;
            end
            NPC: begin
                S_out <= S_out_NPC;
            end
            NPP: begin
                S_out <= S_out_NPP;
            end
            ANPC: begin
                S_out <= S_out_ANPC;
            end
            default: begin
                S_out <= 'b000_000;
            end
        endcase
    end
endmodule