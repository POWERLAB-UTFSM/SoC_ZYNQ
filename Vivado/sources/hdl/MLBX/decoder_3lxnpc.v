module decoder_3lxnpc(
	input              clk,ce,rst,
	input   [7:0]	t_short, t_off_on, t_on_offV0, t_offV0_on, t_off_onI0,
	input   [1:0]	v_lev,
	input   [1:0]	comm_type_anpc,
	input 	[1:0]	npc_type,
	//output logic [5:0]  S_out
	output wire S_1,
	output wire S_2,
	output wire S_3,
	output wire S_4,
	output wire S_5,
	output wire S_6
	);


		localparam NOOUT=0;
		localparam NPC=1;
		localparam NPP=2;
		localparam ANPC=3;

		localparam TYPE_I=0;
		localparam TYPE_IU=1;
		localparam TYPE_II=2;
		localparam TYPE_III=3;

    reg [5:0]  S_out_ANPC;
    reg [5:0]  S_out_NPC;
    reg [5:0]  S_out_NPP;
    reg [5:0]  S_out;

    assign S_1 = S_out[5];
    assign S_2 = S_out[4];
    assign S_3 = S_out[3];
    assign S_4 = S_out[2];
    assign S_5 = S_out[1];
    assign S_6 = S_out[0];

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