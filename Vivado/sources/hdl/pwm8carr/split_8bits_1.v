module split_8bits_1 (
    input [7:0] in_0,
    output out_7,
    output out_6,
    output out_5,
    output out_4,
    output out_3,
    output out_2,
    output out_1,
    output out_0
);
    assign out_1=in_0[7];
endmodule