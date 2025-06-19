`timescale 10ns/1ps

module TESTBENCH_pwm16bits;
  
	localparam NO_COUNT	=2'b00;
	localparam COUNT_UP	=2'b01;
	localparam COUNT_DOWN	=2'b10;
	localparam COUNT_UPDOWN	=2'b11;

	localparam NO_EVENT=0;
	localparam MIN_EVENT=1;
	localparam MAX_EVENT=2;
	localparam MINMAX_EVENT=3;

	reg clk=0;
	reg ce=1;
	reg rst=1;
	reg [15:0] compare_1=16'h000A;
	reg [15:0] compare_2=16'h0008;
	reg sig_pwm_1=0;
	reg sig_pwm_2=0;
	reg [1:0] carrier_mode=COUNT_UPDOWN;
	reg carrier_initdir=0;
	reg [15:0] carrier_max=16'h000F;
	reg [15:0] carrier_init=16'h000A;
	//wire [15:0] carrier;
	reg [2:0] sync_mode=MIN_EVENT;
	reg [3:0] event_count=1;
	reg en_pwm=1;
	reg [15:0] sync_carrier_max=16'h003C;
	reg begin_count= 0;
	reg conf_sync_comp = 0;
	reg conf_sync_carr = 1;
	reg [15:0] wavemax = 16'h0E;
	reg [1:0] wave_conf= 3;
	reg [15:0] waveinit = 16'h05;
	reg dirinit=0;

	reg testv=1;

	wire pwm_1a;
	wire pwm_1b;
	wire pwm_2a;
	wire pwm_2b;
	wire sync;
	wire syncout;
	wire [15:0] wave;

	timermaster MASTER(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.begin_count(begin_count),
		.count_max(sync_carrier_max),
		.syncout(syncout)
	);
  
	pwm16bits DUT1(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.carrier_max(carrier_max),
		.carrier_init(carrier_init),
		.carrier_initdir(carrier_initdir),
		.carrier_mode(carrier_mode),
		.event_count(event_count),
		.sync_mode(sync_mode),
		.compare_1(compare_1),
		.compare_2(compare_2),
		.sig_pwm_1(sig_pwm_1),
		.sig_pwm_2(sig_pwm_2),
		.sync_ext(syncout),
		.conf_sync_comp(conf_sync_comp),
		.conf_sync_carr(conf_sync_carr),
		.en_pwm(en_pwm),
		//.carrier(carrier),
		.sync(sync),
		.pwm_1a(pwm_1a),
		.pwm_1b(pwm_1b),
		.pwm_2a(pwm_2a),
		.pwm_2b(pwm_2b)
	);
	
	/*triangularwave DUT3(
	   .clk(clk),
	   .reset(rst),
	   .wavemax(wavemax),
	   .waveinit(waveinit),
	   .dirinit(dirinit),
	   .wave_conf(wave_conf),
	   .wave(wave)
	   );*/
  
	initial begin
		$dumpfile("dump.vcd");
		$dumpvars(0);
	end
  
	initial begin
		#2
		rst=0;
		#304
		begin_count=1;
		/*#2031
		begin_count=0;
		carrier_max=16'h01FF;
		#2000
		//carrier_init=16'h0000;*/
		#200
		//wave_conf=3;
		#207
		carrier_init=16'h03;
		#4600
		testv<=0;
	end
  
	initial begin
		while(testv) begin
			#1 clk=~clk;
		end
  end
      
 endmodule