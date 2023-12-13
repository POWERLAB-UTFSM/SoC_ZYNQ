`timescale 10ns / 100ps

module TESTBENCH_decoder_3lxnpc();

	localparam NO_COUNT	=2'b00;
	localparam COUNT_DOWN	=2'b01;
	localparam COUNT_UP	=2'b10;
	localparam COUNT_UPDOWN	=2'b11;

	localparam NO_EVENT=0;
	localparam MIN_EVENT=1;
	localparam MAX_EVENT=2;
	localparam MINMAX_EVENT=3;

	reg clk=0;
	reg ce=1;
	reg rst=1;
	reg [15:0] compare_1=16'h005F;
	reg [15:0] compare_2=16'h004F;
	reg sig_pwm_1=0;
	reg sig_pwm_2=0;
	reg [1:0] count_mode=COUNT_DOWN;
	reg [15:0] count_max=16'h00FF;
	reg [15:0] init_carr=0;
	//wire [15:0] carrier;
	reg [2:0] sync_mode=MIN_EVENT;
	reg [3:0] event_count=2;

	localparam TYPE_I=0;
	localparam TYPE_IU=1;
	localparam TYPE_II=2;
	localparam TYPE_III=3;

	localparam P=0;
	localparam Z_U2=1;
	localparam Z_U1=2;
	localparam Z_L1=3;
	localparam Z_L2=4;
	localparam N=5;
	//P, Z_U2, Z_U1, Z_L1, Z_L2, N

	localparam NOOUT=0;
	localparam NPC=1;
	localparam NPP=2;
	localparam ANPC=3;

	reg [7:0] t_short=1;
	reg [7:0] t_off_on=10;
	reg [7:0] t_off_oni0=8;
	reg [7:0] t_offv0_on=7;
	reg [7:0] t_on_offv0=6;

	reg [1:0] comm_type_anpc=TYPE_I;
	reg [1:0] npc_type=ANPC;
	
	reg [1:0] v_lev_x=2'b00;
	
	

	always #1 clk = ~clk;
	always @(posedge clk) rst <= 1'b0;

	initial begin
		count_mode=COUNT_DOWN;
		init_carr=0;
		event_count=0;
		compare_1=16'h004F;
		compare_2=16'h005F;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b01;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b01;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b10;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b10;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(50) @(posedge clk);
		comm_type_anpc=TYPE_II;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b01;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b01;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b10;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b10;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(50) @(posedge clk);
		comm_type_anpc=TYPE_III;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b01;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b01;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b10;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b10;
		
		repeat(50) @(posedge clk);
		v_lev_x=2'b00;
		
		repeat(2000) @(posedge clk);
		count_mode=COUNT_UPDOWN;
		
		repeat(3000) @(posedge clk);
		init_carr=16'h01FF;
	end

	pwm16bits PWM1(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.count_max(count_max),
		.init_carr(init_carr),
		.count_mode(count_mode),
		.event_count(event_count),
		.sync_mode(sync_mode),
		.compare_1(compare_1),
		.compare_2(compare_2),
		.sig_pwm_1(sig_pwm_1),
		.sig_pwm_2(sig_pwm_2),
		//.carrier(carrier),
		.sync(sync),
		.pwm_1a(pwm_1a),
		.pwm_1b(pwm_1b),
		.pwm_2a(pwm_2a),
		.pwm_2b(pwm_2b)
	);

	decoder_3lxnpc DUT1(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.t_short(t_short), 
		.t_off_on(t_off_on), 
		.t_on_offv0(t_on_offv0),
		.t_offv0_on(t_offv0_on),
		.t_off_oni0(t_off_oni0),
		.v_lev(v_lev_x),
		.comm_type_anpc(comm_type_anpc),
		.npc_type(npc_type),
		.s_1(s_1),
		.s_2(s_2),
		.s_3(s_3),
		.s_4(s_4),
		.s_5(s_5),
		.s_6(s_6)
	);

endmodule