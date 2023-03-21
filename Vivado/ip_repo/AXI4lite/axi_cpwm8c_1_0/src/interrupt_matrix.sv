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
	input  [7:0] interrupt_in ,
    input  [7:0] matrix ,
	output wire interrupt_out
);
	
	assign interrupt_out = interrupt_in[7] & matrix[7] | interrupt_in[6] & matrix[6] | interrupt_in[5] & matrix[5] | interrupt_in[4] & matrix[4] | interrupt_in[3] & matrix[3] | interrupt_in[2] & matrix[2] | interrupt_in[1] & matrix[1] | interrupt_in[0] & matrix[0];
    
endmodule