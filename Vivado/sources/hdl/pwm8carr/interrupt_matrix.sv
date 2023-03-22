`timescale 10ns / 100ps
// Company: 
// Engineer: 
// 
// Create Date: 01/24/2023 12:57:42 AM
// Design Name: 
// Module Name: interrupt_matrix
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

import PKG_pwm::*;

module interrupt_matrix(
    input reset,
	input  [`PWM_WIDTH-1:0] interrupt_in ,
    input  [`PWM_WIDTH-1:0] matrix ,
	output interrupt_out
);

    logic [`PWM_WIDTH-1:0] matrix_aux;
    
    always_comb begin
        if (reset) begin
            matrix_aux <= 0;
        end
        else begin
            matrix_aux <= matrix;
        end
    end
	
	assign interrupt_out=interrupt_in & matrix_aux;
	/*genvar i;
    generate
        for (i=0; i<`PWM_WIDTH; i=i+1) begin
            
        end 
    endgenerate*/
	//assign interrupt_out = interrupt_in[7] & matrix_aux[7] | interrupt_in[6] & matrix_aux[6] | interrupt_in[5] & matrix_aux[5] | interrupt_in[4] & matrix_aux[4] | interrupt_in[3] & matrix_aux[3] | interrupt_in[2] & matrix_aux[2] | interrupt_in[1] & matrix_aux[1] | interrupt_in[0] & matrix_aux[0];
    
endmodule