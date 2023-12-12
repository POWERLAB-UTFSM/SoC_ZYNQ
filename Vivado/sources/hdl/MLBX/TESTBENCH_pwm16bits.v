`timescale 10ns / 100ps

module TESTBENCH_pwm16bits();

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
	reg [15:0] compare_1=16'h001F;
	reg [15:0] compare_2=16'h002F;
	reg sig_pwm_1=0;
	reg sig_pwm_2=0;
	reg [1:0] count_mode=COUNT_DOWN;
	reg [15:0] count_max=16'h00FF;
	reg [15:0] init_carr=0;
	//wire [15:0] carrier;
	reg [2:0] sync_mode=MIN_EVENT;
	reg [3:0] event_count=2;
	
	

	always #1 clk = ~clk;
	always @(posedge clk) rst <= 1'b0;

	initial begin
		count_mode=COUNT_DOWN;
		init_carr=0;
		event_count=0;
		compare_1=16'h001F;
		compare_2=16'h002F;
		
		repeat(2000) @(posedge clk);
		count_mode=COUNT_UPDOWN;
		
		repeat(3000) @(posedge clk);
		init_carr=16'h05FF;
	end

	pwm16bits DUT1(
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

endmodule