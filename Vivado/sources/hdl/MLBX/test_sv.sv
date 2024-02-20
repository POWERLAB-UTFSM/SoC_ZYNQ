module test_sv (
    input clk, ce, 
    input sig_in,
    input conf,
    output logic sig_out
);

always_comb begin
    if (conf==1) begin
        sig_out <= !sig_in;
    end
    else begin
        sig_out <= 0;
    end
end

// assign sig_out = sig_in;

endmodule