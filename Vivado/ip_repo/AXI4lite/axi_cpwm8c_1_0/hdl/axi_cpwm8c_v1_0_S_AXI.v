`default_nettype none
`timescale 1 ns / 1 ps

	module axi_cpwm8c_v1_0_S_AXI #
	(
		// {{{
		// Users to add parameters here
		parameter [0:0] OPT_READ_SIDEEFFECTS = 1,
		parameter [0:0]	OPT_SKIDBUFFER = 1'b0,
		parameter [0:0]	OPT_LOWPOWER = 0,
		parameter integer PWM_WIDTH = 8,
		// User parameters ends
		// Do not modify the parameters beyond this line
		// Width of S_AXI data bus
		parameter integer C_S_AXI_DATA_WIDTH	= 32,
		// Width of S_AXI address bus
		parameter integer C_S_AXI_ADDR_WIDTH	= 7
		// }}}
	) (
		// {{{
		// Users to add ports here
		input wire pwm_clk,
		input wire wire_ack,
        output wire [PWM_WIDTH-1:0] pwmout_A,
        output wire [PWM_WIDTH-1:0] pwmout_B,
        output wire trigger,
        output wire interrupt,
		// No user ports (yet) in this design
		// User ports ends

		// Do not modify the ports beyond this line
		// Global Clock Signal
		input wire  S_AXI_ACLK,
		// Global Reset Signal. This Signal is Active LOW
		input wire  S_AXI_ARESETN,
		// Write address (issued by master, acceped by Slave)
		input wire [C_S_AXI_ADDR_WIDTH-1 : 0] S_AXI_AWADDR,
		// Write channel Protection type. This signal indicates the
    		// privilege and security level of the transaction, and whether
    		// the transaction is a data access or an instruction access.
		input wire [2 : 0] S_AXI_AWPROT,
		// Write address valid. This signal indicates that the master
		// signaling valid write address and control information.
		input wire  S_AXI_AWVALID,
		// Write address ready. This signal indicates that the slave
		// is ready to accept an address and associated control signals.
		output wire  S_AXI_AWREADY,
		// Write data (issued by master, acceped by Slave)
		input wire [C_S_AXI_DATA_WIDTH-1 : 0] S_AXI_WDATA,
		// Write strobes. This signal indicates which byte lanes hold
    		// valid data. There is one write strobe bit for each eight
    		// bits of the write data bus.
		input wire [(C_S_AXI_DATA_WIDTH/8)-1 : 0] S_AXI_WSTRB,
		// Write valid. This signal indicates that valid write
    		// data and strobes are available.
		input wire  S_AXI_WVALID,
		// Write ready. This signal indicates that the slave
    		// can accept the write data.
		output wire  S_AXI_WREADY,
		// Write response. This signal indicates the status
    		// of the write transaction.
		output wire [1 : 0] S_AXI_BRESP,
		// Write response valid. This signal indicates that the channel
    		// is signaling a valid write response.
		output wire  S_AXI_BVALID,
		// Response ready. This signal indicates that the master
    		// can accept a write response.
		input wire  S_AXI_BREADY,
		// Read address (issued by master, acceped by Slave)
		input wire [C_S_AXI_ADDR_WIDTH-1 : 0] S_AXI_ARADDR,
		// Protection type. This signal indicates the privilege
    		// and security level of the transaction, and whether the
    		// transaction is a data access or an instruction access.
		input wire [2 : 0] S_AXI_ARPROT,
		// Read address valid. This signal indicates that the channel
    		// is signaling valid read address and control information.
		input wire  S_AXI_ARVALID,
		// Read address ready. This signal indicates that the slave is
    		// ready to accept an address and associated control signals.
		output wire  S_AXI_ARREADY,
		// Read data (issued by slave)
		output wire [C_S_AXI_DATA_WIDTH-1 : 0] S_AXI_RDATA,
		// Read response. This signal indicates the status of the
    		// read transfer.
		output wire [1 : 0] S_AXI_RRESP,
		// Read valid. This signal indicates that the channel is
    		// signaling the required read data.
		output wire  S_AXI_RVALID,
		// Read ready. This signal indicates that the master can
    		// accept the read data and response information.
		input wire  S_AXI_RREADY
		// }}}
	);

////////////////////////////////////////////////////////////////////////
	//
	// Register/wire signal declarations
	// {{{
	////////////////////////////////////////////////////////////////////////
	//
	localparam	ADDRLSB = $clog2(C_S_AXI_DATA_WIDTH)-3;

	wire	i_reset = !S_AXI_ARESETN;

	wire				axil_write_ready;
	wire	[C_S_AXI_ADDR_WIDTH-ADDRLSB-1:0]	awskd_addr;
	//
	wire	[C_S_AXI_DATA_WIDTH-1:0]	wskd_data;
	wire [C_S_AXI_DATA_WIDTH/8-1:0]	wskd_strb;
	reg				axil_bvalid;
	//
	wire				axil_read_ready;
	wire	[C_S_AXI_ADDR_WIDTH-ADDRLSB-1:0]	arskd_addr;
	reg	[C_S_AXI_DATA_WIDTH-1:0]	axil_read_data;
	reg				axil_read_valid;

	reg	[C_S_AXI_DATA_WIDTH-1:0]	r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19;
	wire	[C_S_AXI_DATA_WIDTH-1:0]	wskd_r0, wskd_r1, wskd_r2, wskd_r3, wskd_r4, wskd_r5, wskd_r6, wskd_r7, wskd_r8, wskd_r9, wskd_r10, wskd_r11, wskd_r12, wskd_r13, wskd_r14, wskd_r15, wskd_r16, wskd_r17, wskd_r18, wskd_r19;
	// }}}
	////////////////////////////////////////////////////////////////////////
	//
	// AXI-lite signaling
	//
	////////////////////////////////////////////////////////////////////////
	//
	// {{{

	//
	// Write signaling
	//
	// {{{

	generate if (OPT_SKIDBUFFER)
	begin : SKIDBUFFER_WRITE
		// {{{
		wire	awskd_valid, wskd_valid;

		skidbuffer #(.OPT_OUTREG(0),
				.OPT_LOWPOWER(OPT_LOWPOWER),
				.DW(C_S_AXI_ADDR_WIDTH-ADDRLSB))
		axilawskid(//
			.i_clk(S_AXI_ACLK), .i_reset(i_reset),
			.i_valid(S_AXI_AWVALID), .o_ready(S_AXI_AWREADY),
			.i_data(S_AXI_AWADDR[C_S_AXI_ADDR_WIDTH-1:ADDRLSB]),
			.o_valid(awskd_valid), .i_ready(axil_write_ready),
			.o_data(awskd_addr));

		skidbuffer #(.OPT_OUTREG(0),
				.OPT_LOWPOWER(OPT_LOWPOWER),
				.DW(C_S_AXI_DATA_WIDTH+C_S_AXI_DATA_WIDTH/8))
		axilwskid(//
			.i_clk(S_AXI_ACLK), .i_reset(i_reset),
			.i_valid(S_AXI_WVALID), .o_ready(S_AXI_WREADY),
			.i_data({ S_AXI_WDATA, S_AXI_WSTRB }),
			.o_valid(wskd_valid), .i_ready(axil_write_ready),
			.o_data({ wskd_data, wskd_strb }));

		assign	axil_write_ready = awskd_valid && wskd_valid
				&& (!S_AXI_BVALID || S_AXI_BREADY);
		// }}}
	end else begin : SIMPLE_WRITES
		// {{{
		reg	axil_awready;

		initial	axil_awready = 1'b0;
		always @(posedge S_AXI_ACLK)
		if (!S_AXI_ARESETN)
			axil_awready <= 1'b0;
		else
			axil_awready <= !axil_awready
				&& (S_AXI_AWVALID && S_AXI_WVALID)
				&& (!S_AXI_BVALID || S_AXI_BREADY);

		assign	S_AXI_AWREADY = axil_awready;
		assign	S_AXI_WREADY  = axil_awready;

		assign 	awskd_addr = S_AXI_AWADDR[C_S_AXI_ADDR_WIDTH-1:ADDRLSB];
		assign	wskd_data  = S_AXI_WDATA;
		assign	wskd_strb  = S_AXI_WSTRB;

		assign	axil_write_ready = axil_awready;
		// }}}
	end endgenerate

	initial	axil_bvalid = 0;
	always @(posedge S_AXI_ACLK)
	if (i_reset)
		axil_bvalid <= 0;
	else if (axil_write_ready)
		axil_bvalid <= 1;
	else if (S_AXI_BREADY)
		axil_bvalid <= 0;

	assign	S_AXI_BVALID = axil_bvalid;
	assign	S_AXI_BRESP = 2'b00;
	// }}}

	//
	// Read signaling
	//
	// {{{

	generate if (OPT_SKIDBUFFER)
	begin : SKIDBUFFER_READ
		// {{{
		wire	arskd_valid;

		skidbuffer #(.OPT_OUTREG(0),
				.OPT_LOWPOWER(OPT_LOWPOWER),
				.DW(C_S_AXI_ADDR_WIDTH-ADDRLSB))
		axilarskid(//
			.i_clk(S_AXI_ACLK), .i_reset(i_reset),
			.i_valid(S_AXI_ARVALID), .o_ready(S_AXI_ARREADY),
			.i_data(S_AXI_ARADDR[C_S_AXI_ADDR_WIDTH-1:ADDRLSB]),
			.o_valid(arskd_valid), .i_ready(axil_read_ready),
			.o_data(arskd_addr));

		assign	axil_read_ready = arskd_valid
				&& (!axil_read_valid || S_AXI_RREADY);
		// }}}
	end else begin : SIMPLE_READS
		// {{{
		reg	axil_arready;

		always @(*)
			axil_arready = !S_AXI_RVALID;

		assign	arskd_addr = S_AXI_ARADDR[C_S_AXI_ADDR_WIDTH-1:ADDRLSB];
		assign	S_AXI_ARREADY = axil_arready;
		assign	axil_read_ready = (S_AXI_ARVALID && S_AXI_ARREADY);
		// }}}
	end endgenerate

	initial	axil_read_valid = 1'b0;
	always @(posedge S_AXI_ACLK)
	if (i_reset)
		axil_read_valid <= 1'b0;
	else if (axil_read_ready)
		axil_read_valid <= 1'b1;
	else if (S_AXI_RREADY)
		axil_read_valid <= 1'b0;

	assign	S_AXI_RVALID = axil_read_valid;
	assign	S_AXI_RDATA  = axil_read_data;
	assign	S_AXI_RRESP = 2'b00;
	// }}}

	// }}}
	////////////////////////////////////////////////////////////////////////
	//
	// AXI-lite register logic
	//
	////////////////////////////////////////////////////////////////////////
	//
	// {{{

	// apply_wstrb(old_data, new_data, write_strobes)
	assign	wskd_r0 = apply_wstrb(r0, wskd_data, wskd_strb);
	assign	wskd_r1 = apply_wstrb(r1, wskd_data, wskd_strb);
	assign	wskd_r2 = apply_wstrb(r2, wskd_data, wskd_strb);
	assign	wskd_r3 = apply_wstrb(r3, wskd_data, wskd_strb);
	assign	wskd_r4 = apply_wstrb(r4, wskd_data, wskd_strb);
	assign	wskd_r5 = apply_wstrb(r5, wskd_data, wskd_strb);
	assign	wskd_r6 = apply_wstrb(r6, wskd_data, wskd_strb);
	assign	wskd_r7 = apply_wstrb(r7, wskd_data, wskd_strb);
	assign	wskd_r8 = apply_wstrb(r8, wskd_data, wskd_strb);
	assign	wskd_r9 = apply_wstrb(r9, wskd_data, wskd_strb);
	assign	wskd_r10 = apply_wstrb(r10, wskd_data, wskd_strb);
	assign	wskd_r11 = apply_wstrb(r11, wskd_data, wskd_strb);
	assign	wskd_r12 = apply_wstrb(r12, wskd_data, wskd_strb);
	assign	wskd_r13 = apply_wstrb(r13, wskd_data, wskd_strb);
	assign	wskd_r14 = apply_wstrb(r14, wskd_data, wskd_strb);
	assign	wskd_r15 = apply_wstrb(r15, wskd_data, wskd_strb);
	assign	wskd_r16 = apply_wstrb(r16, wskd_data, wskd_strb);
	assign	wskd_r17 = apply_wstrb(r17, wskd_data, wskd_strb);
	assign	wskd_r18 = apply_wstrb(r18, wskd_data, wskd_strb);
	assign	wskd_r19 = apply_wstrb(r19, wskd_data, wskd_strb);

	initial	r0 = 0;
	initial	r1 = 0;
	initial	r2 = 0;
	initial	r3 = 0;
	initial	r4 = 0;
	initial	r5 = 0;
	initial	r6 = 0;
	initial	r7 = 0;
	initial	r8 = 0;
	initial	r9 = 0;
	initial	r10 = 0;
	initial	r11 = 0;
	initial	r12 = 0;
	initial	r13 = 0;
	initial	r14 = 0;
	initial	r15 = 0;
	initial	r16 = 0;
	initial	r17 = 0;
	initial	r18 = 0;
	initial	r19 = 0;
	always @(posedge S_AXI_ACLK)
	if (i_reset)
	begin
		r0 <= 0;
		r1 <= 0;
		r2 <= 0;
		r3 <= 0;
		r4 <= 0;
		r5 <= 0;
		r6 <= 0;
		r7 <= 0;
		r8 <= 0;
		r9 <= 0;
		r10 <= 0;
		r11 <= 0;
		r12 <= 0;
		r13 <= 0;
		r14 <= 0;
		r15 <= 0;
		r16 <= 0;
		r17 <= 0;
		r18 <= 0;
		r19 <= 0;
	end else if (axil_write_ready)
	begin
		case(awskd_addr)
		'h00:	r0 <= wskd_r0;
		'h01:	r1 <= wskd_r1;
		'h02:	r2 <= wskd_r2;
		'h03:	r3 <= wskd_r3;
		'h04:	r4 <= wskd_r4;
		'h05:	r5 <= wskd_r5;
		'h06:	r6 <= wskd_r6;
		'h07:	r7 <= wskd_r7;
		'h08:	r8 <= wskd_r8;
		'h09:	r9 <= wskd_r9;
		'h0A:	r10 <= wskd_r10;
		'h0B:	r11 <= wskd_r11;
		'h0C:	r12 <= wskd_r12;
		'h0D:	r13 <= wskd_r13;
		'h0E:	r14 <= wskd_r14;
		'h0F:	r15 <= wskd_r15;
		'h10:	r16 <= wskd_r16;
		'h11:	r17 <= wskd_r17;
		'h12:	r18 <= wskd_r18;
		'h13:	r19 <= wskd_r19;
		endcase
	end

	initial	axil_read_data = 0;
	always @(posedge S_AXI_ACLK)
	if (OPT_LOWPOWER && !S_AXI_ARESETN)
		axil_read_data <= 0;
	else if (!S_AXI_RVALID || S_AXI_RREADY)
	begin
		case(arskd_addr)
		'h00:	axil_read_data	<= r0;
		'h01:	axil_read_data	<= r1;
		'h02:	axil_read_data	<= r2;
		'h03:	axil_read_data	<= r3;
		'h04:	axil_read_data	<= r4;
		'h05:	axil_read_data	<= r5;
		'h06:	axil_read_data	<= r6;
		'h07:	axil_read_data	<= r7;
		'h08:	axil_read_data	<= r8;
		'h09:	axil_read_data	<= r9;
		'h0A:	axil_read_data	<= r10;
		'h0B:	axil_read_data	<= r11;
		'h0C:	axil_read_data	<= r12;
		'h0D:	axil_read_data	<= r13;
		'h0E:	axil_read_data	<= r14;
		'h0F:	axil_read_data	<= r15;
		'h10:	axil_read_data	<= r16;
		'h11:	axil_read_data	<= r17;
		'h12:	axil_read_data	<= r18;
		'h13:	axil_read_data	<= r19;
		endcase

		if (OPT_LOWPOWER && !axil_read_ready)
			axil_read_data <= 0;
	end

	function [C_S_AXI_DATA_WIDTH-1:0]	apply_wstrb;
		input	[C_S_AXI_DATA_WIDTH-1:0]		prior_data;
		input	[C_S_AXI_DATA_WIDTH-1:0]		new_data;
		input	[C_S_AXI_DATA_WIDTH/8-1:0]	wstrb;

		integer	k;
		for(k=0; k<C_S_AXI_DATA_WIDTH/8; k=k+1)
		begin
			apply_wstrb[k*8 +: 8]
				= wstrb[k] ? new_data[k*8 +: 8] : prior_data[k*8 +: 8];
		end
	endfunction
	// }}}

	// Make Verilator happy
	// {{{
	// Verilator lint_off UNUSED
	wire	unused;
	assign	unused = &{ 1'b0, S_AXI_AWPROT, S_AXI_ARPROT,
			S_AXI_ARADDR[ADDRLSB-1:0],
			S_AXI_AWADDR[ADDRLSB-1:0] };
	// Verilator lint_on  UNUSED
	
	// Add user logic here
   cpwm_16bits_8carr CPWM8C(
        //.pwm0_clk(S_AXI_ACLK)
        //,
        //.pwm1_clk(pwm1_clk)
        //,
        //.pwm2_clk(pwm2_clk)
        //,
        //.pwm3_clk(pwm3_clk)
        //,
        .clk(pwm_clk)
        ,
        .reset(~S_AXI_ARESETN)
        ,
        .period_x({r3,r2,r1,r0})
        ,
        .initcarr_x({r7,r6,r5,r4})
        ,
        .compare_x({r11,r10,r9,r8})
        ,
        .dtime_A_x({r13,r12})
        ,
        .dtime_B_x({r15,r14})
        ,
        .eventcount_x(r16[31:8])
        ,
        .interrupt_matrix(r16[7:0])
        ,
        .countmode_x(r17[31:16])
        ,
        .maskmode_x(r17[15:0])
        ,
        .dt_onoff_x(r18[31:24])
        ,
        .logic_A_x(r18[23:16])
        ,
        .logic_B_x(r18[15:8])
        ,
        .carrsel_x(r18[7:0])
        ,
        .pwm_onoff(r19[0])
        ,
        .carrier_onoff_x(r19[8:1])
        ,
        .int_ack(r19[9])
        ,
        .wire_ack(wire_ack)
        //,
        //.clk_sel(slv_reg19[2:1])
        //--------------------------------
        //Outputs
        //--------------------------------
        ,
        .pwmout_A_x(pwmout_A)
        ,
        .pwmout_B_x(pwmout_B)
        ,
        .trigger(trigger)
        ,
        .interrupt(interrupt)
   );
	// User logic ends

	// }}}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Formal properties
// {{{
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
`ifdef	FORMAL
	////////////////////////////////////////////////////////////////////////
	//
	// The AXI-lite control interface
	//
	////////////////////////////////////////////////////////////////////////
	//
	// {{{
	localparam	F_AXIL_LGDEPTH = 4;
	wire	[F_AXIL_LGDEPTH-1:0]	faxil_rd_outstanding,
					faxil_wr_outstanding,
					faxil_awr_outstanding;

	faxil_slave #(
		// {{{
		.C_AXI_DATA_WIDTH(C_AXI_DATA_WIDTH),
		.C_AXI_ADDR_WIDTH(C_AXI_ADDR_WIDTH),
		.F_LGDEPTH(F_AXIL_LGDEPTH),
		.F_AXI_MAXWAIT(3),
		.F_AXI_MAXDELAY(3),
		.F_AXI_MAXRSTALL(5),
		.F_OPT_COVER_BURST(4)
		// }}}
	) faxil(
		// {{{
		.i_clk(S_AXI_ACLK), .i_axi_reset_n(S_AXI_ARESETN),
		//
		.i_axi_awvalid(S_AXI_AWVALID),
		.i_axi_awready(S_AXI_AWREADY),
		.i_axi_awaddr( S_AXI_AWADDR),
		.i_axi_awprot( S_AXI_AWPROT),
		//
		.i_axi_wvalid(S_AXI_WVALID),
		.i_axi_wready(S_AXI_WREADY),
		.i_axi_wdata( S_AXI_WDATA),
		.i_axi_wstrb( S_AXI_WSTRB),
		//
		.i_axi_bvalid(S_AXI_BVALID),
		.i_axi_bready(S_AXI_BREADY),
		.i_axi_bresp( S_AXI_BRESP),
		//
		.i_axi_arvalid(S_AXI_ARVALID),
		.i_axi_arready(S_AXI_ARREADY),
		.i_axi_araddr( S_AXI_ARADDR),
		.i_axi_arprot( S_AXI_ARPROT),
		//
		.i_axi_rvalid(S_AXI_RVALID),
		.i_axi_rready(S_AXI_RREADY),
		.i_axi_rdata( S_AXI_RDATA),
		.i_axi_rresp( S_AXI_RRESP),
		//
		.f_axi_rd_outstanding(faxil_rd_outstanding),
		.f_axi_wr_outstanding(faxil_wr_outstanding),
		.f_axi_awr_outstanding(faxil_awr_outstanding)
		// }}}
		);

	always @(*)
	if (OPT_SKIDBUFFER)
	begin
		assert(faxil_awr_outstanding== (S_AXI_BVALID ? 1:0)
			+(S_AXI_AWREADY ? 0:1));
		assert(faxil_wr_outstanding == (S_AXI_BVALID ? 1:0)
			+(S_AXI_WREADY ? 0:1));

		assert(faxil_rd_outstanding == (S_AXI_RVALID ? 1:0)
			+(S_AXI_ARREADY ? 0:1));
	end else begin
		assert(faxil_wr_outstanding == (S_AXI_BVALID ? 1:0));
		assert(faxil_awr_outstanding == faxil_wr_outstanding);

		assert(faxil_rd_outstanding == (S_AXI_RVALID ? 1:0));
	end

	//
	// Check that our low-power only logic works by verifying that anytime
	// S_AXI_RVALID is inactive, then the outgoing data is also zero.
	//
	always @(*)
	if (OPT_LOWPOWER && !S_AXI_RVALID)
		assert(S_AXI_RDATA == 0);
	// }}}
	////////////////////////////////////////////////////////////////////////
	//
	// Register return checking
	// {{{
	////////////////////////////////////////////////////////////////////////
	//
	//
`define	CHECK_REGISTERS
`ifdef	CHECK_REGISTERS
	faxil_register #(
		// {{{
		.AW(C_AXI_ADDR_WIDTH),
		.DW(C_AXI_DATA_WIDTH),
		.ADDR(0)
		// }}}
	) fr0 (
		// {{{
		.S_AXI_ACLK(S_AXI_ACLK),
		.S_AXI_ARESETN(S_AXI_ARESETN),
		.S_AXIL_AWW(axil_write_ready),
		.S_AXIL_AWADDR({ awskd_addr, {(ADDRLSB){1'b0}} }),
		.S_AXIL_WDATA(wskd_data),
		.S_AXIL_WSTRB(wskd_strb),
		.S_AXIL_BVALID(S_AXI_BVALID),
		.S_AXIL_AR(axil_read_ready),
		.S_AXIL_ARADDR({ arskd_addr, {(ADDRLSB){1'b0}} }),
		.S_AXIL_RVALID(S_AXI_RVALID),
		.S_AXIL_RDATA(S_AXI_RDATA),
		.i_register(r0)
		// }}}
	);

	faxil_register #(
		// {{{
		.AW(C_AXI_ADDR_WIDTH),
		.DW(C_AXI_DATA_WIDTH),
		.ADDR(4)
		// }}}
	) fr1 (
		// {{{
		.S_AXI_ACLK(S_AXI_ACLK),
		.S_AXI_ARESETN(S_AXI_ARESETN),
		.S_AXIL_AWW(axil_write_ready),
		.S_AXIL_AWADDR({ awskd_addr, {(ADDRLSB){1'b0}} }),
		.S_AXIL_WDATA(wskd_data),
		.S_AXIL_WSTRB(wskd_strb),
		.S_AXIL_BVALID(S_AXI_BVALID),
		.S_AXIL_AR(axil_read_ready),
		.S_AXIL_ARADDR({ arskd_addr, {(ADDRLSB){1'b0}} }),
		.S_AXIL_RVALID(S_AXI_RVALID),
		.S_AXIL_RDATA(S_AXI_RDATA),
		.i_register(r1)
		// }}}
	);

	faxil_register #(
		// {{{
		.AW(C_AXI_ADDR_WIDTH),
		.DW(C_AXI_DATA_WIDTH),
		.ADDR(8)
		// }}}
	) fr2 (
		// {{{
		.S_AXI_ACLK(S_AXI_ACLK),
		.S_AXI_ARESETN(S_AXI_ARESETN),
		.S_AXIL_AWW(axil_write_ready),
		.S_AXIL_AWADDR({ awskd_addr, {(ADDRLSB){1'b0}} }),
		.S_AXIL_WDATA(wskd_data),
		.S_AXIL_WSTRB(wskd_strb),
		.S_AXIL_BVALID(S_AXI_BVALID),
		.S_AXIL_AR(axil_read_ready),
		.S_AXIL_ARADDR({ arskd_addr, {(ADDRLSB){1'b0}} }),
		.S_AXIL_RVALID(S_AXI_RVALID),
		.S_AXIL_RDATA(S_AXI_RDATA),
		.i_register(r2)
		// }}}
	);

	faxil_register #(
		// {{{
		.AW(C_AXI_ADDR_WIDTH),
		.DW(C_AXI_DATA_WIDTH),
		.ADDR(12)
		// }}}
	) fr3 (
		// {{{
		.S_AXI_ACLK(S_AXI_ACLK),
		.S_AXI_ARESETN(S_AXI_ARESETN),
		.S_AXIL_AWW(axil_write_ready),
		.S_AXIL_AWADDR({ awskd_addr, {(ADDRLSB){1'b0}} }),
		.S_AXIL_WDATA(wskd_data),
		.S_AXIL_WSTRB(wskd_strb),
		.S_AXIL_BVALID(S_AXI_BVALID),
		.S_AXIL_AR(axil_read_ready),
		.S_AXIL_ARADDR({ arskd_addr, {(ADDRLSB){1'b0}} }),
		.S_AXIL_RVALID(S_AXI_RVALID),
		.S_AXIL_RDATA(S_AXI_RDATA),
		.i_register(r3)
		// }}}
	);
`endif
	// }}}
	////////////////////////////////////////////////////////////////////////
	//
	// Cover checks
	//
	////////////////////////////////////////////////////////////////////////
	//
	// {{{

	// While there are already cover properties in the formal property
	// set above, you'll probably still want to cover something
	// application specific here

	// }}}
`endif
// }}}
endmodule