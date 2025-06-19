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
	input init_slope, //0=up, 1=down
	input [1:0] count_mode, //00=no_count; 01=up; 10=down; 11=up_down
	input sync_ext,
	output reg [15:0] carrier
);

	//reg [2:0] counter_state;
	//reg [2:0] counter_state_next;

	//typedef enum logic [2:0] {S_NEWCARR,S_RESET0,S_UP,S_DOWN,S_RESETP,S_STOP} _state_counter;
	typedef enum logic [2:0] {S_STOP,S_RESET0,S_RESETP,S_UP,S_DOWN} _state_counter;
	_state_counter state_counter;
	_state_counter state_next_counter;

	wire stop_status;
	
	wire new_carrier;
	reg [15:0] init_carr_buffer;
	reg [15:0] count_max_buffer;

	/*

    localparam S_NEWCARR	=0;
	localparam S_RESET0		=1;
	localparam S_UP  			=2;
	localparam S_DOWN			=3;
	localparam S_RESETP		=4;
	localparam S_STOP			=5;
	*/

	
	
	
	localparam NO_COUNT	=2'b00;
	localparam COUNT_DOWN	=2'b01;
	localparam COUNT_UP	=2'b10;
	localparam COUNT_UPDOWN	=2'b11;

	initial begin
		state_counter <= S_STOP;
		//new_carrier <= 0;
		init_carr_buffer <=0;
        count_max_buffer <=0;
	end

	/*always @* begin
		if(count_mode== NO_COUNT || count_max == 0) begin
			stop_status=1;
		end
		else begin
			stop_status=0;
		end
	end*/
	assign stop_status = count_mode== (NO_COUNT) || (count_max == 0) ? 1 : 0;


	always @* begin
	//always_ff @(posedge clk) begin
	//------------------------------------
	//Conditional state transition (FSM)
	state_next_counter=state_counter;
	case(state_counter) 
	   S_STOP: begin
			if(stop_status==1) begin
				state_next_counter = S_STOP;
			end
			else
			if((carrier >= count_max || init_carr >= count_max) && (count_mode==COUNT_UP || count_mode==COUNT_UPDOWN )) begin
				state_next_counter = S_RESET0;
			end
			if(count_mode==COUNT_DOWN && (carrier == 0 || init_carr >= count_max)) begin
				state_next_counter = S_RESETP;
			end
			else 
			if(((count_mode==COUNT_UP) && (carrier<count_max) && (init_carr<count_max)) || (new_carrier == 1 && init_slope==0)) begin
				state_next_counter = S_UP;
			end
			if(((count_mode==COUNT_DOWN) && (carrier<count_max) && (init_carr<count_max)) || (new_carrier == 1 && init_slope==1)) begin
				state_next_counter = S_DOWN;
			end
			else 
			if((count_mode==COUNT_UPDOWN) && (init_slope == 0 ) && (carrier<count_max) && (init_carr<count_max)) begin
				state_next_counter = S_UP;
			end
			else 
			if((count_mode==COUNT_UPDOWN ) && (init_slope == 1 ) && (carrier<count_max) && (init_carr<count_max)) begin
				state_next_counter = S_DOWN;
			end
		end
		S_RESET0: begin
			if(stop_status==1) begin
				state_next_counter = S_STOP;
			end
			else
			/*if (new_carrier==1) begin
				state_next_counter = S_NEWCARR;
			end
			else*/  
			if(count_mode==COUNT_DOWN) begin
				state_next_counter = S_RESETP;
			end
			else
			begin
				state_next_counter = S_UP;
			end
		end
		S_RESETP: begin
			if(stop_status==1) begin
				state_next_counter = S_STOP;
			end
			else
			/*if (new_carrier==1) begin
				state_next_counter = S_NEWCARR;
			end
			else*/
			if(count_mode==COUNT_DOWN) begin
				state_next_counter = S_DOWN;
			end
			else 
			if(count_mode==COUNT_UP || count_mode==COUNT_UPDOWN) begin
				state_next_counter = S_UP;
			end
			
		end
		S_UP: begin
			if(stop_status==1) begin
				state_next_counter = S_STOP;
			end
			else
			/*if (new_carrier==1) begin
				state_next_counter = S_NEWCARR;
			end
			else*/ 
			if((count_mode==COUNT_UPDOWN || count_mode==COUNT_DOWN) && carrier >= (count_max-1)) begin
				state_next_counter = S_DOWN;
			end
			else 
			if((new_carrier == 1 && init_slope==1)) begin
				state_next_counter = S_DOWN;
			end
			else 
			if((new_carrier == 1 && (init_slope==0))) begin
				state_next_counter = S_UP;
			end
			else
			if(count_mode==COUNT_UP && carrier >= (count_max-1)) begin
				state_next_counter = S_RESET0;
			end
		end
		S_DOWN: begin
			if(stop_status==1) begin
				state_next_counter = S_STOP;
			end
			else
			/*if (new_carrier==1) begin
				state_next_counter = S_NEWCARR;
			end
			else*/ 
			if((count_mode==COUNT_UPDOWN || count_mode==COUNT_UP) && carrier <=1) begin
				state_next_counter = S_UP;
			end
			else 
			if((new_carrier == 1 && (init_slope==1 || count_mode==COUNT_DOWN))) begin
				state_next_counter = S_DOWN;
			end
			else 
			if(new_carrier == 1 && (init_slope==0 && (count_mode==COUNT_UP || count_mode==COUNT_UPDOWN))) begin
				state_next_counter = S_UP;
			end
			else 
			if(count_mode==COUNT_DOWN && carrier <= 1) begin
				state_next_counter = S_RESETP;
			end
		end
		/*S_STOP: begin
			if(stop_status==1) begin
				state_next_counter = S_STOP;
			end
			else begin 
				state_next_counter = S_NEWCARR;
			end
		end*/
		
		endcase		
	end
	
	assign new_carrier = (init_carr !=init_carr_buffer) || (count_max != count_max_buffer) || (sync_ext == 1) ? 1 : 0  ;
	

	always @(posedge clk or posedge rst) begin
		if (rst) begin
			state_counter <= S_STOP;
			carrier <= 0;
			//new_carrier <=0;
			init_carr_buffer <=0;
            count_max_buffer <=0;
		end
		else begin
			state_counter <= state_next_counter;
			//init_carr_buffer <=init_carr;
			//if((init_carr !=init_carr_buffer) || (count_max != count_max_buffer) || (sync_ext == 1)) begin
				//new_carrier <=1;
			//end
			case(state_counter) 
				S_RESET0: begin
				    if(new_carrier == 1) begin
				        carrier <= init_carr > count_max ? count_max : init_carr ;
				        //new_carrier <= 0;
                        init_carr_buffer <=init_carr;
				        count_max_buffer <=count_max;
				    end
				    else begin
					   carrier <= 0;
					end
				end
				S_RESETP: begin
				    if(new_carrier == 1) begin
				        carrier <= init_carr > count_max ? count_max : init_carr ;
				        //new_carrier <= 0;
				        init_carr_buffer <=init_carr;
				        count_max_buffer <=count_max;
				    end
				    else begin
					   carrier <= (count_max);
					end
				end
				S_UP: begin
				    if(new_carrier == 1) begin
				        carrier <= init_carr > count_max ? count_max : init_carr ;
				        //new_carrier <= 0;
				        init_carr_buffer <=init_carr;
				        count_max_buffer <=count_max;
				    end
				    else begin
					   carrier <= (carrier +1) ;
					end
				end
				S_DOWN: begin
				    if(new_carrier == 1) begin
				        carrier <= init_carr > count_max ? count_max : init_carr + 1 ;
				        //new_carrier <= 0;
				        init_carr_buffer <=init_carr;
				        count_max_buffer <=count_max;
				    end
				    else begin
					   carrier <= (carrier -1) ;
					end
				end
				S_STOP: begin
				    if(new_carrier == 1) begin
				        carrier <= init_carr > count_max ? count_max : init_carr ;
				        //new_carrier <= 0;
				        init_carr_buffer <=init_carr;
				        count_max_buffer <=count_max;
				    end
				    else begin
					   carrier <= 0;
					end
				end
			endcase
		end
	end


endmodule