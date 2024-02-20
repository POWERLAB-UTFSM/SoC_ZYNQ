`timescale 10ns / 100ps

module TESTBENCH_cpwm_16bits_8carr();

    localparam NO_COUNT	=2'b00;
	localparam COUNT_DOWN	=2'b01;
	localparam COUNT_UP	=2'b10;
	localparam COUNT_UPDOWN	=2'b11;
	
	localparam NO_MASK=1;
	localparam MIN_MASK=1;
	localparam MAX_MASK=2;
	localparam MINMAX_MASK=3;
	
	reg clk=0;
	reg ce=1;
	reg rst=1;
	reg [1:0] count_mode=COUNT_DOWN;
	reg [15:0] countmax=16'h00FF;
	reg [15:0] init_carr=0;
	wire [15:0] carrier;
	reg [2:0] syncmode=MINMAX_MASK;
	
	

	always #1 clk = ~clk;
	always @(posedge clk) rst <= 1'b0;

	initial begin
		count_mode=COUNT_DOWN;
		init_carr=0;
		
		repeat(2000) @(posedge clk);
		count_mode=COUNT_UPDOWN;
		
		repeat(3000) @(posedge clk);
		init_carr=16'h000C;
	end

	pwmtimer_16bits DUT1(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.countmax(countmax),
		.init_carr(init_carr),
		.count_mode(count_mode),
		.syncmode(syncmode),
		.carrier(carrier),
		.sync(sync)
	);

endmodule