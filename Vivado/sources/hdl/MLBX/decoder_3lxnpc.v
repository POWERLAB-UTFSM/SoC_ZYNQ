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

module decoder_3lxnpc(
	input	clk,ce,rst,
	input	[9:0]	t_short, t_off_on, t_on_offv0, t_offv0_on, t_off_oni0,
	input	[1:0]	v_lev,
	input	[1:0]	comm_type_anpc,
	input	[1:0]	npc_type,
	//output logic [5:0]  S_out
	output wire s_1,
	output wire s_2,
	output wire s_3,
	output wire s_4,
	output wire s_5,
	output wire s_6
	);

	localparam NOOUT=0;
	localparam NPC=1;
	localparam NPP=2;
	localparam ANPC=3;

	localparam TYPE_I=0;
	localparam TYPE_IU=1;
	localparam TYPE_II=2;
	localparam TYPE_III=3;

	wire [5:0]  S_out_ANPC;
	wire [5:0]  S_out_NPC;
	wire [5:0]  S_out_NPP;
	reg [5:0]  S_out;

	assign s_1 = S_out[5];
	assign s_2 = S_out[4];
	assign s_3 = S_out[3];
	assign s_4 = S_out[2];
	assign s_5 = S_out[1];
	assign s_6 = S_out[0];

//    always @* begin
//        s_1 = S_out[5];
//        s_2 = S_out[4];
//        s_3 = S_out[3];
//        s_4 = S_out[2];
//        s_5 = S_out[1];
//        s_6 = S_out[0];  
//    end
    

	fsm_3lanpc FSM3LANPC(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.t_short(t_short),
		.t_off_on(t_off_on),
		.t_on_offv0(t_on_offv0),
		.t_offv0_on(t_offv0_on),
		.t_off_oni0(t_off_oni0),
		.v_lev(v_lev),
		.comm_type(comm_type_anpc),
		.s_out(S_out_ANPC)
	);

//	fsm_3lnpc FSM3LNPC(
//		.clk(clk),
//		.rst(rst),
//		.t_short(t_short),
//		.t_off_on(t_off_on),
//		.v_lev(v_lev),
//		.S_out(S_out_NPC)
//	);

//	fsm_3lnpp FSM3LNPP(
//		.clk(clk),
//		.rst(rst),
//		.t_short(t_short),
//		.t_off_on(t_off_on),
//		.v_lev(v_lev),
//		.S_out(S_out_NPP)
//	);
    
	always @(posedge clk) begin
		case(npc_type)
			NOOUT: begin
				S_out <= 'b000_000;
			end
			NPC: begin
				S_out <= 'b000_000;
			end
			NPP: begin
				S_out <= 'b000_000;
			end
			ANPC: begin
				S_out <= S_out_ANPC;
			end
			default: begin
				S_out = 'b000_000;
			end
		endcase
	end
	
endmodule