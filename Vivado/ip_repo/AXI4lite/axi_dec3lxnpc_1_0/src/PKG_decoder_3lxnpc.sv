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

package PKG_decoder_3lxnpc; // package name
    `ifndef TDELAY_WIDTH
    `define TDELAY_WIDTH 8
    `endif

    typedef enum logic [2:0] {P, Z_U2, Z_U1, Z_L1, Z_L2, N} _statesanpc_t;  // State definitions for 3L-ANPC
    typedef enum logic [1:0] {PP, ZZ, NN} _statesnpc_t;  // State definitions for 3L-NPC/NPP
    typedef enum logic [1:0] {type_I, type_IU, type_II, type_III} _commtypes_t;  // commutation type definitions for 3L-ANPC
    typedef enum logic [1:0] {NoOut,NPC,NPP,ANPC} _npctypes_t;

    //parameter t_short 		= cycles(500,10);
    //parameter t_off_on 		= cycles(500,10);
    //parameter t_on_offV0	= cycles(500,10);
    //parameter t_offV0_on 	= cycles(500,10);
    //parameter t_off_onI0    = cycles(500,10);
endpackage
