module pwm_timer (
    input clk, ce, 
    input [15:0] cntmax,
    output reg [15:0] cntout
);

reg [15:0] cnt;
reg cnt_mode;


initial cnt=16'b0000000000000000;
initial cnt_mode=1

always @(posedge clk) begin
    
cnt=cnt+1;
end

endmodule