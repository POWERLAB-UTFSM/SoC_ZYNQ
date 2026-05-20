`timescale 1ns / 10ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/31/2026 11:08:38 PM
// Design Name: 
// Module Name: _TESTBENCH_cpwm16b
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


module _TESTBENCH_cpwm16b#(
	parameter PWMWIDTH = 16,
	parameter DTCOUNT_WIDTH = 8
)
(
);
    
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
	reg rst=0;
	reg [PWMWIDTH-1:0] carrier_max=0;
	reg [PWMWIDTH-1:0] carrier_init=0;
	reg [1:0] count_mode=0;
	reg [1:0] sync_mode=0;
	reg [3:0] event_count=0;
	reg [PWMWIDTH-1:0] compare_1=0;
	reg [PWMWIDTH-1:0] compare_2=0;
	reg en_pwm=0;
	reg sig_pwm_1=0;
	reg sig_pwm_2=0;
	reg [DTCOUNT_WIDTH-1:0] deadtime=0;
	reg dt_logic_1a=0;
	reg dt_logic_1b=0;
	reg dt_logic_2a=0;
	reg dt_logic_2b=0;
	reg dt_onoff=0;
	reg irq_clear=0;
	reg irq_enable=0;
	reg [1:0] clkdiv_carr=0;
	reg [1:0] clkdiv_dtime=0;
	reg mask_on=0;
	
	reg testv=1;

	initial begin
		clk=0;
		en_pwm=1;
		rst=1;
		ce=1;
		count_mode=COUNT_UPDOWN;
		sync_mode=MIN_EVENT;
		carrier_max=16'h00FF;
		carrier_init=0;
		event_count=5;
		compare_1=16'h006F;
		compare_2=16'h006F;
		sig_pwm_1=0;
		sig_pwm_2=0;
		deadtime=7'b0000000;
		dt_logic_1a=0;
		dt_logic_1b=0;
		dt_logic_2a=0;
		dt_logic_2b=0;
		dt_onoff=1;
		irq_clear=0;
		irq_enable=1;
		clkdiv_carr=0;
		clkdiv_dtime=0;
		mask_on=0;
		
		#1
		rst<=0;
		clkdiv_carr=2;
        begin
            irq_clear = 0;
        
            while(testv)
            begin
                @(posedge interrupt);
        
                // laisser vivre l'IRQ un peu
                @(posedge clk);
        
                irq_clear = 1;
        
                @(posedge clk);
        
                irq_clear = 0;
            end
        end
        		
		#35000
		//count_mode<=COUNT_UPDOWN;
		event_count=1;

		#55000
		//count_mode<=COUNT_UPDOWN;
		clkdiv_carr=1;
		deadtime=7'b0100000;
		
		#70000
		compare_1=16'h006F;
		mask_on = 1;


		
		#90000
		clkdiv_dtime=10;
        
		
		#150000
		testv<=0;
	end
  
	initial begin
		while(testv) begin
			#1 clk=~clk;
		end
	end
  
  cpwm16b CPWM16B
	(
		.clk(clk),
		.ce(ce),
		.rst(rst),
		.carrier_max(carrier_max),
		.carrier_init(carrier_init),
		.clkdiv_carr(clkdiv_carr),
		.count_mode(count_mode), //00=no_count; 01=up; 10=down; 11=up_down
		.sync_mode(sync_mode),//00=no_count; 01=min_count; 10=max_count; 11=minmax_count
		.event_count(event_count),
		.compare_1(compare_1),
		.compare_2(compare_2),
		.en_pwm(en_pwm),
		.sig_pwm_1(sig_pwm_1),
		.sig_pwm_2(sig_pwm_2),
		.deadtime(deadtime),
		.mask_on(mask_on),
		.dt_logic_1a(dt_logic_1a),
		.dt_logic_1b(dt_logic_1b),
		.dt_logic_2a(dt_logic_2a),
		.dt_logic_2b(dt_logic_2b),
		.dt_onoff(dt_onoff),
		.irq_enable(irq_enable),
		.irq_clear(irq_clear),
		.clkdiv_dtime(clkdiv_dtime),
		.sync(sync),
		.pwm_1a(pwm_1a),
		.pwm_1b(pwm_1b),
		.pwm_2a(pwm_2a),
		.pwm_2b(pwm_2b),
		.irq_status(irq_status),
		.interrupt(interrupt)
	);
	
    
endmodule
