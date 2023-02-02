`timescale 1ns / 1ps
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
import PKG_fsm3lanpc::*;

module TESTBENCH_fsm3lanpc();
//=============================================================
// Signal Definition
//=============================================================

	logic [2:0]    z_type;
	logic [5:0]    S_out;
	logic[`TDELAY_WIDTH-1:0]            t_short, t_off_on, t_on_offV0, t_offV0_on, t_off_onI0;
	logic [2:0]    v_lev;
	
//=============================================================
//  Clock & Reset generator
//=============================================================

	bit clk = 1'b0;
	bit rst = 1'b1;

	always #1 clk = ~clk;
	always_ff @(posedge clk) rst <= 1'b0;
    
//=============================================================
//    Data Flow
//=============================================================
    initial begin 
        t_short = 'd3;
        t_off_on = 'd10;
        t_on_offV0 = 'd7;
        t_offV0_on = 'd6;
        t_off_onI0 = 'd9;
        z_type  = 'd1;
        v_lev = 'b00;
        repeat(1) @(posedge clk);       //One free clock cycle for the reset signal

        repeat(100) @(posedge clk);
        v_lev  = 'b01;
        repeat(50) @(posedge clk);
        v_lev  = 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  = 'b01 ;
        repeat(50) @(posedge clk);
        z_type  = 'd2;
        repeat(50) @(posedge clk);
        v_lev  = 'b00;
        repeat(50) @(posedge clk);
        v_lev  = 'b01 ;
        repeat(50) @(posedge clk);
        z_type  = 'd3;
        repeat(50) @(posedge clk);
        v_lev  = 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  = 'b01 ;
        repeat(50) @(posedge clk);
        v_lev  = 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  = 'b10 ;
        repeat(50) @(posedge clk);
        z_type  = 'd1;
        repeat(50) @(posedge clk);
        v_lev  = 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  = 'b10 ;
        repeat(50) @(posedge clk);
        z_type  = 'd1;
        repeat(50) @(posedge clk);
        v_lev  = 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  = 'b10 ;
        repeat(50) @(posedge clk);
        z_type  = 'd2;
        repeat(50) @(posedge clk);
        v_lev  = 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  = 'b10 ;
        repeat(50) @(posedge clk);
        z_type  = 'd3;
        repeat(50) @(posedge clk);
        v_lev  = 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  = 'b10 ;
        repeat(50) @(posedge clk);
        v_lev  = 'b00 ;
        repeat(50) @(posedge clk);
        v_lev  = 'b01 ;
        
        
    end 
//=============================================================
//    Design Under Test
//=============================================================


fsm3lanpc FSM1(
        .clk,
        .reset(rst),
        .t_short,
        .t_off_on,
        .t_on_offV0,
        .t_offV0_on,
        .t_off_onI0,
        .v_lev,
        .z_type,
        .S_out
    );

endmodule
		
		
//=============================================================
