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

module cpwm16b_clockdiv
(
    input clk,
    input ce,
    input rst,
    input [1:0] div,

    output reg tick
);

reg [2:0] counter;

always @(posedge clk or posedge rst)
begin
    if(rst)
    begin
        counter <= 0;
        tick <= 0;
    end
    else
    begin
        tick <= 0;

        if(ce)
        begin
            counter <= counter + 1;

            case(div)

                2'b00:
                    tick <= 1;

                2'b01:
                    tick <= counter[0];

                2'b10:
                    tick <= &counter[1:0];

                2'b11:
                    tick <= &counter[2:0];

            endcase
        end
    end
end

endmodule