module pwm16bits_syncsel //#(parameter PWMWIDTH = 16)
(
	input clk,ce,rst,
	input sync_in_ext,
	input sync_in_int,
	input conf_sync,
	output sync_out
);

assign sync_out = conf_sync ? sync_in_ext : sync_in_in;

endmodule