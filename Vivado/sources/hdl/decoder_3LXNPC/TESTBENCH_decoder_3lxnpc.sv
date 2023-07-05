`timescale 10ns / 10ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/15/2022 03:48:41 PM
// Design Name: 
// Module Name: tb_state_machine
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

module TESTBENCH_decoder_3lxnpc();
//=============================================================
// Signal Definition
//=============================================================

	_commtypes_t    comm_type_anpc;
	logic [5:0]    S_out;
	logic[`TDELAY_WIDTH-1:0]            t_short, t_off_on, t_on_offV0, t_offV0_on, t_off_onI0;
	logic [1:0]    v_lev;
    logic change;
    logic[2:0] xstate,next_state,old_state;
    logic transition;
    logic finish_transition;
    logic[`TDELAY_WIDTH-1:0] MAX_COUNTER;
    logic[2:0] delay_timer;
    _npctypes_t npc_type;
	
//=============================================================
//  Clock & Reset generator
//=============================================================

	bit clk = 1'b0;
	bit rst = 1'b1;

	always #1 clk = ~clk;
	always_ff @(posedge clk) rst = 1'b0;
    
//=============================================================
//    Data Flow
//=============================================================
    initial begin 
        npc_type <= NPP;
        t_short <= 'd3;
        t_off_on <= 'd10;
        t_on_offV0 <= 'd7;
        t_offV0_on <= 'd6;
        t_off_onI0 <= 'd9;
        comm_type_anpc  <= type_I;
        v_lev <= 'b00;
        repeat(1) @(posedge clk);       //One free clock cycle for the reset signal

        repeat(100) @(posedge clk);
        v_lev  <= 'b01;
        repeat(50) @(posedge clk);
        v_lev  <= 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  <= 'b01 ;
        repeat(50) @(posedge clk);
        comm_type_anpc  <= type_II;
        repeat(50) @(posedge clk);
        v_lev <= 'b00;
        repeat(50) @(posedge clk);
        v_lev  <= 'b01 ;
        repeat(50) @(posedge clk);
        comm_type_anpc  <= type_III;
        repeat(50) @(posedge clk);
        v_lev  <= 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  <= 'b01 ;
        repeat(50) @(posedge clk);
        v_lev  <= 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  <= 'b10 ;
        repeat(50) @(posedge clk);
        comm_type_anpc  <= type_I;
        repeat(50) @(posedge clk);
        v_lev  <= 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  <= 'b10 ;
        repeat(50) @(posedge clk);
        comm_type_anpc  <= type_I;
        repeat(50) @(posedge clk);
        v_lev  <= 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  <= 'b10 ;
        repeat(50) @(posedge clk);
        comm_type_anpc  <= type_II;
        repeat(50) @(posedge clk);
        v_lev  <= 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  <= 'b10 ;
        repeat(50) @(posedge clk);
        comm_type_anpc  <= type_III;
        repeat(50) @(posedge clk);
        v_lev  <= 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  <= 'b10 ;
        repeat(50) @(posedge clk);
        v_lev  <= 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  <= 'b01 ;
        
        
    end 
//=============================================================
//    Design Under Test
//=============================================================


decoder_3lxnpc DUT(
        .clk,
        .rst(rst),
        .t_short,
        .t_off_on,
        .t_on_offV0,
        .t_offV0_on,
        .t_off_onI0,
        .v_lev(v_lev),
        .comm_type_anpc(comm_type_anpc),
        .npc_type(npc_type),
        .S_out(S_out)
        /*,
        .change(change),
        .state(xstate),
        .next_state(next_state),
        .old_state(old_state),
        .transition(transition),
        .finish_transition(finish_transition),
        .counter(counter),
        .MAX_COUNTER(MAX_COUNTER),
        .delay_timer(delay_timer)*/
    );

endmodule
		
		
//=============================================================
