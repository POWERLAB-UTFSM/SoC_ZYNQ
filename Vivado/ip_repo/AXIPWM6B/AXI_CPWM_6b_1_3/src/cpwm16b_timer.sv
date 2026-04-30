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

module cpwm16b_timer #(
	parameter PWMWIDTH = 16
)
(
	input clk,
	input ce,
	input rst,
	input [PWMWIDTH-1:0] carrier_max,
	input [PWMWIDTH-1:0] carrier_init,
	input enable,
	input [1:0] count_mode, //00=no_count; 01=up; 10=down; 11=up_down
	output reg [PWMWIDTH-1:0] carrier
);

	reg [2:0] counter_state;
	reg [2:0] counter_state_next;
	reg [PWMWIDTH-1:0] carrier_init_buffer;
	reg new_carrier;

	wire stop_status;

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
		carrier_init_buffer <=0;
	end

	// always @* begin
	// 	if(count_mode==2'b00 || carrier_max == 0 || enable==0) begin
	// 		stop_status=1;
	// 	end
	// 	else begin
	// 		stop_status=0;
	// 	end
	// end

	assign stop_status = (count_mode==NO_COUNT || carrier_max == 0 || enable==0) ? 1 : 0;



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
			if((count_mode==COUNT_UP || count_mode==COUNT_UPDOWN) && carrier < (carrier_max-1)) begin
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
			if((count_mode==COUNT_UPDOWN || count_mode==COUNT_DOWN) && carrier >= (carrier_max-1)) begin
				counter_state_next = S_DOWN;
			end
			else 
			if(count_mode==COUNT_UP && carrier >= (carrier_max-1)) begin
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
			/*if((count_mode==COUNT_UPDOWN || count_mode==COUNT_UP) && carrier < (carrier_max-1)) begin
					counter_state_next = S_UP;
			end
			else 
			if((count_mode==COUNT_UPDOWN || count_mode==COUNT_DOWN ) && carrier > 1) begin
					counter_state_next = S_DOWN;
			end
			else 
			if(carrier >= (carrier_max-1) && stop_status==0) begin
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
			if((count_mode==COUNT_UPDOWN || count_mode==COUNT_UP) && carrier < (carrier_max-1)) begin
				counter_state_next = S_UP;
			end
			else 
			if((count_mode==COUNT_UPDOWN || count_mode==COUNT_DOWN ) && carrier > 0) begin
				counter_state_next = S_DOWN;
			end
			else 
			if(carrier >= (carrier_max-1) && stop_status==0) begin
				counter_state_next = S_RESETP;
			end
			else 
			if(carrier <= 1 && stop_status==0) begin
				counter_state_next = S_RESET0;
			end
		end
		default: begin
			if(stop_status==1) begin
				counter_state_next = S_STOP;
			end
			else begin 
				counter_state_next = S_NEWCARR;
			end
		end
		endcase		
	end

	always @(posedge clk or posedge rst) begin
		if (rst) begin
			counter_state <= S_NEWCARR;
			carrier_init_buffer <=0;
			carrier <= 0;
			new_carrier <= 0;
		end
		else if (ce==1) begin
			counter_state <= counter_state_next;
			//carrier_init_buffer <=carrier_init;

			case(counter_state) 
				S_RESET0: begin
					carrier <= 0;
					if(carrier_init !=carrier_init_buffer && (carrier == 0)) begin
						new_carrier <= 1;
					end
				end
				S_RESETP: begin
					carrier <= (carrier_max) ;
					if(carrier_init !=carrier_init_buffer && (carrier == 0)) begin
						new_carrier <= 1;
					end
				end
				S_UP: begin
					carrier <= (carrier +1) ;
					if(carrier_init !=carrier_init_buffer && (carrier == 0)) begin
						new_carrier <= 1;
					end
				end
				S_DOWN: begin
					carrier <= (carrier -1) ;
					if(carrier_init !=carrier_init_buffer && (carrier == 0)) begin
						new_carrier <= 1;
					end
				end
				S_STOP: begin
					carrier <= 0;
					if(carrier_init !=carrier_init_buffer && (carrier == 0)) begin
						new_carrier <= 1;
					end
				end
				S_NEWCARR: begin
					carrier <= carrier_init;
					new_carrier <=0;
					carrier_init_buffer <=carrier_init;
				end
				default: begin
					carrier <= 0;
					if(carrier_init !=carrier_init_buffer && (carrier == 0)) begin
						new_carrier <= 1;
					end
				end
			endcase
		end
	end


endmodule