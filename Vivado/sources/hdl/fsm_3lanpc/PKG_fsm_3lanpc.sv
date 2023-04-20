`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/20/2022 08:20:34 PM
// Design Name: 
// Module Name: states_pkg
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


	

// states_pkg.sv

package PKG_fsm_3lanpc; // package name
    `ifndef TDELAY_WIDTH
    `define TDELAY_WIDTH 8
    `endif

    typedef enum logic [2:0] {P, Z_U2, Z_U1, Z_L1, Z_L2, N} _states_t;  // State definitions
    typedef enum logic [1:0] {type_I, type_IU, type_II, type_III} _commtypes_t;  // State definitions

    //parameter t_short 		= cycles(500,10);
    //parameter t_off_on 		= cycles(500,10);
    //parameter t_on_offV0	= cycles(500,10);
    //parameter t_offV0_on 	= cycles(500,10);
    //parameter t_off_onI0    = cycles(500,10);
endpackage
