`timescale 10ns/1ps

module pwm16bits_timernew (
	input wire clk, 
	input wire ce,          // Clock input
	input wire rst,         // Synchronous rst
	input wire [15:0] carrier_max,
	input wire [15:0] carrier_init,
	input wire carrier_initdir,
	input wire [1:0] carrier_mode,
	input wire sync_ext,
	output reg [15:0] carrier     // 8-bit triangular carrier output
);

	reg direction; // 0 = up, 1 = down
	reg [15:0] carrier_init_buff;
	reg [15:0] carrier_max_buff;

	wire new_carrier;

	localparam NO_COUNT	=2'b00;
	localparam COUNT_UP	=2'b01;
	localparam COUNT_DOWN	=2'b10;
	localparam COUNT_UPDOWN	=2'b11;

	assign new_carrier = (carrier_init !=carrier_init_buff) || (carrier_max != carrier_max_buff) || (sync_ext == 1) ? 1 : 0  ;
	//assign new_carrier = 0;

	always @(posedge clk or posedge rst) begin
		if (rst || carrier_mode == NO_COUNT || carrier_max_buff == 0) begin
			carrier <= 16'd0;
			direction <= 1'b0; // Start counting up
			carrier_init_buff <= 16'd0;
			carrier_max_buff <= carrier_max;
		end else begin
			case (carrier_mode) 
				COUNT_UP: begin
					if (new_carrier) begin
						carrier <= carrier_init ;
						carrier_init_buff <= carrier_init;
						carrier_max_buff <= carrier_max;
					end else begin
						if (carrier >= carrier_max_buff ) begin
							carrier <= 0;
						end else begin
							carrier <= carrier + 1;
						end
					end
				end
				COUNT_DOWN: begin
					if (new_carrier) begin
						carrier <= carrier_init;
						carrier_init_buff <= carrier_init;
						carrier_max_buff <= carrier_max;
					end else begin
						if (carrier <= 0 ) begin
							carrier <= carrier_max_buff;
						end else begin
							carrier <= carrier - 1;
						end
					end
				end
				COUNT_UPDOWN: begin
					if (new_carrier) begin
						carrier <= carrier_init ;
						carrier_init_buff <= carrier_init;
						direction <= carrier_initdir;
						carrier_max_buff <= carrier_max;
					end else begin
						if (!direction) begin //up
							if(carrier >= carrier_max_buff) begin
								direction <= 1; // Change to down
								carrier <= carrier - 1;
							end else begin
								carrier <= carrier + 1;
							end
						end else begin
							if(carrier <= 0) begin
								direction <= 0; // Change to up
								carrier <= carrier + 1;
							end else begin
								carrier <= carrier - 1;
							end
						end
					end
				end
			endcase
		end
	end

endmodule