`timescale 10ns/1ps

module pwm16bits_timernew (
	input wire clk,           // Clock input
	input wire reset,         // Synchronous reset
	input wire [15:0] wavemax,
	input wire [15:0] waveinit,
	input wire dirinit,
	input wire [1:0] wave_conf,
	output reg [15:0] wave     // 8-bit triangular wave output
);

	reg direction; // 0 = up, 1 = down
	reg [15:0] waveinit_buff;

	localparam NO_COUNT	=2'b00;
	localparam COUNT_UP	=2'b01;
	localparam COUNT_DOWN	=2'b10;
	localparam COUNT_UPDOWN	=2'b11;

	always @(posedge clk or posedge reset) begin
		if (reset || wave_conf == NO_COUNT) begin
			wave <= 16'd1;
			direction <= 1'b0; // Start counting up
			waveinit_buff <= 0;
		end else begin
			case (wave_conf) 
				COUNT_UP: begin
					if (wave >= wavemax) begin
						wave <= 0;
					end else begin
						if (waveinit_buff != waveinit) begin
							wave <= waveinit;
							waveinit_buff <= waveinit;
						end else begin
							wave <= wave + 1;
						end
					end
				end
				COUNT_DOWN: begin
					if (wave == 0) begin
						wave <= wavemax;
					end else begin
						if (waveinit_buff != waveinit) begin
							wave <= waveinit;
							waveinit_buff <= waveinit;
						end else begin
							wave <= wave - 1;
						end
					end
				end
				COUNT_UPDOWN: begin
					if (!direction) begin
						if (wave >= wavemax) begin
							//direction <= 1'b1; // Change to down
							if (waveinit_buff != waveinit) begin
								wave <= waveinit;
								waveinit_buff <= waveinit;
								direction <= dirinit;
							end else begin
								wave <= wave - 1;
								direction <= 1'b1; // Change to down
							end
						end else begin
							if (waveinit_buff != waveinit) begin
								wave <= waveinit;
								waveinit_buff <= waveinit;
								direction <= dirinit;
							end else begin
								wave <= wave + 1;
							end
						end
					end else begin
						if (wave == 16'd0) begin
							//direction <= 1'b0; // Change to up
							if (waveinit_buff != waveinit) begin
								wave <= waveinit;
								waveinit_buff <= waveinit;
								direction <= dirinit;
							end else begin
								wave <= wave + 1;
								direction <= 1'b0; // Change to up
							end
						end else begin
							if (waveinit_buff != waveinit) begin
								wave <= waveinit;
								waveinit_buff <= waveinit;
								direction <= dirinit;
							end else begin
								wave <= wave - 1;
							end
						end
					end
				end
			endcase
		end
	end

endmodule