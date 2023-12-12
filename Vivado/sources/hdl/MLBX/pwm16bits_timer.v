`timescale 10ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 01:18:08 AM
// Design Name: 
// Module Name:
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

module pwm16bits_timer //#(parameter PWMWIDTH = 16)
(
	input clk,ce,rst,
	input [15:0] count_max,
	input [15:0] init_carr,
	input [1:0] count_mode, //00=no_count; 01=up; 10=down; 11=up_down
	output reg [15:0] carrier
);

	reg [2:0] counter_state;
	reg [2:0] counter_state_next;
	reg stop_status;
	reg [15:0] init_carr_buffer;
	reg new_carrier;

	localparam S_RESET0		=0;
	localparam S_UP  			=1;
	localparam S_DOWN			=2;
	localparam S_RESETP		=3;
	localparam S_STOP			=4;
	localparam S_NEWCARR	=5;
	
	localparam NO_COUNT	=2'b00;
	localparam COUNT_DOWN	=2'b01;
	localparam COUNT_UP	=2'b10;
	localparam COUNT_UPDOWN	=2'b11;

	initial begin
		counter_state <= S_NEWCARR;
		init_carr_buffer <=0;
	end

	always @* begin
		if(count_mode==2'b00 || count_max == 0) begin
			stop_status=1;
		end
		else begin
			stop_status=0;
		end
	end



	always @* begin
	//always_ff @(posedge clk) begin
	//------------------------------------
	//Conditional state transition (FSM)
	counter_state_next=counter_state;
	case(counter_state) 
		S_RESET0: begin
			if(stop_status==1) begin
				counter_state_next = S_STOP;
			end
			else
			if (new_carrier==1) begin
				counter_state_next = S_NEWCARR;
			end
			else  
			if(count_mode==COUNT_DOWN) begin
				counter_state_next = S_RESETP;
			end
			else
			if((count_mode==COUNT_UP || count_mode==COUNT_UPDOWN) && carrier < (count_max-1)) begin
				counter_state_next = S_UP;
			end
		end
		S_RESETP: begin
			if(stop_status==1) begin
				counter_state_next = S_STOP;
			end
			else
			if (new_carrier==1) begin
				counter_state_next = S_NEWCARR;
			end
			else
			if(count_mode==COUNT_DOWN && carrier > 1) begin
				counter_state_next = S_DOWN;
			end
			else 
			if(count_mode==COUNT_UP || count_mode==COUNT_UPDOWN) begin
				counter_state_next = S_UP;
			end
			
		end
		S_UP: begin
			if(stop_status==1) begin
				counter_state_next = S_STOP;
			end
			else
			if (new_carrier==1) begin
				counter_state_next = S_NEWCARR;
			end
			else 
			if((count_mode==COUNT_UPDOWN || count_mode==COUNT_DOWN) && carrier >= (count_max-1)) begin
				counter_state_next = S_DOWN;
			end
			else 
			if(count_mode==COUNT_UP && carrier >= (count_max-1)) begin
				counter_state_next = S_RESET0;
			end
		end
		S_DOWN: begin
			if(stop_status==1) begin
				counter_state_next = S_STOP;
			end
			else
			if (new_carrier==1) begin
				counter_state_next = S_NEWCARR;
			end
			else 
			if((count_mode==COUNT_UPDOWN || count_mode==COUNT_UP) && carrier <=1) begin
				counter_state_next = S_UP;
			end
			else 
			if(count_mode==COUNT_DOWN && carrier <= 1) begin
				counter_state_next = S_RESETP;
			end
		end
		S_STOP: begin
			if(stop_status==1) begin
				counter_state_next = S_STOP;
			end
			else begin 
				counter_state_next = S_NEWCARR;
			end
			/*if((count_mode==COUNT_UPDOWN || count_mode==COUNT_UP) && carrier < (count_max-1)) begin
					counter_state_next = S_UP;
			end
			else 
			if((count_mode==COUNT_UPDOWN || count_mode==COUNT_DOWN ) && carrier > 1) begin
					counter_state_next = S_DOWN;
			end
			else 
			if(carrier >= (count_max-1) && stop_status==0) begin
					counter_state_next = S_RESETP;
			end
			else 
			if(carrier <= 1 && stop_status==0) begin
					counter_state_next = S_RESET0;
			end*/
		end
		S_NEWCARR: begin
			if(stop_status==1) begin
				counter_state_next = S_STOP;
			end
			else 
			if((count_mode==COUNT_UPDOWN || count_mode==COUNT_UP) && carrier < (count_max-1)) begin
				counter_state_next = S_UP;
			end
			else 
			if((count_mode==COUNT_UPDOWN || count_mode==COUNT_DOWN ) && carrier > 0) begin
				counter_state_next = S_DOWN;
			end
			else 
			if(carrier >= (count_max-1) && stop_status==0) begin
				counter_state_next = S_RESETP;
			end
			else 
			if(carrier <= 1 && stop_status==0) begin
				counter_state_next = S_RESET0;
			end
		end
		endcase		
	end

    always @(posedge clk or posedge rst) begin
		if (rst) begin
			counter_state <= S_NEWCARR;
			init_carr_buffer <=0;
		end
		else begin
			counter_state <= counter_state_next;
			//init_carr_buffer <=init_carr;
			if(init_carr !=init_carr_buffer && (carrier == 0)) begin
				new_carrier=1;
			end
			case(counter_state) 
				S_RESET0: begin
					carrier <= 0;
				end
				S_RESETP: begin
					carrier <= (count_max) ;
				end
				S_UP: begin
					carrier <= (carrier +1) ;
				end
				S_DOWN: begin
					carrier <= (carrier -1) ;
				end
				S_STOP: begin
					carrier <= 0;
				end
				S_NEWCARR: begin
					carrier = init_carr;
					new_carrier=0;
					init_carr_buffer <=init_carr;
				end
			endcase
		end
	end

	// always @(posedge clk) begin
	// 	//------------------------------------
	// 	//State actions
	// 	if(init_carr !=init_carr_buffer && (carrier == 0)) begin
	// 		new_carrier=1;
	// 	end
	// 	case(counter_state) 
	// 		S_RESET0: begin
	// 			carrier <= 0;
	// 		end
	// 		S_RESETP: begin
	// 			carrier <= (count_max) ;
	// 		end
	// 		S_UP: begin
	// 			carrier <= (carrier +1) ;
	// 		end
	// 		S_DOWN: begin
	// 			carrier <= (carrier -1) ;
	// 		end
	// 		S_STOP: begin
	// 			carrier <= 0;
	// 		end
	// 		S_NEWCARR: begin
	// 			carrier = init_carr;
	// 			new_carrier=0;
	// 			init_carr_buffer <=init_carr;
	// 		end
	// 	endcase
	// end

	// //--------------------------------
	// //Interrupt generator
	// reg mask_ok_min;
	// reg mask_ok_max;
	// reg carrier_min;
	// reg carrier_max;

  // localparam NO_MASK=1;
	// localparam MIN_MASK=1;
	// localparam MAX_MASK=2;
	// localparam MINMAX_MASK=3;

	// always @* begin
	// 	mask_ok_min = sync_mode==MIN_MASK || sync_mode==MINMAX_MASK;
	// 	mask_ok_max = sync_mode==MAX_MASK || sync_mode==MINMAX_MASK;
	// 	carrier_min = (carrier == 0);
	// 	carrier_max = (carrier == count_max);
	// end

	// always @(posedge clk or posedge rst) begin
	// 	if(rst==1'b1) begin
	// 		sync <= 1'b0;
	// 	end
	// 	else if((carrier_min & mask_ok_min) | (carrier_max & mask_ok_max) | sync_mode==NO_MASK) begin
	// 		sync <= 1'b1;
	// 	end
	// 	else begin
	// 		sync  <= 1'b0;
	// 	end
	// end


endmodule