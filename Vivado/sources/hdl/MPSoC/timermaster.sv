`timescale 1ns/1ps

module timermaster 
(
	input clk, rst, ce,
	input begin_count,
	input [15:0] count_max,
	output reg syncout
);

reg [15:0] sync_carrier;
reg [15:0] count_max_aux;

always @(posedge clk or posedge rst or posedge begin_count) begin
	if(rst || begin_count==0) begin
		sync_carrier <= 0;
		count_max_aux <= count_max -1; // (-1 x4 para triangular, +1 x2 para diente de sierra)
		syncout <= 0;
	end
	else if ((sync_carrier >= count_max_aux) && (begin_count==1)) begin
		sync_carrier <= 0;
		syncout <= 0;
	end	
	else begin
		sync_carrier <= sync_carrier +1;
		if (sync_carrier == 0) begin
			syncout <= 1;
		end
		else begin
			syncout <= 0;
		end
	end
end

endmodule