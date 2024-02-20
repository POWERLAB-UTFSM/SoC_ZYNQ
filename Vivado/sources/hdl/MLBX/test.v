module test (
    input clk, ce, 
    input sig_in,
    input conf,
    output wire sig_out
);

//assign sig_out = sig_in;

//always @* begin
//    if (conf==1) begin
//        sig_out <= !sig_in;
//    end
//    else begin
//        sig_out <= 0;
//    end
// end

test_sv TESTin(
    .clk(clk),
    .ce(ce),
    .sig_in(sig_in),
    .conf(conf),
    .sig_out(sig_out)
);

endmodule