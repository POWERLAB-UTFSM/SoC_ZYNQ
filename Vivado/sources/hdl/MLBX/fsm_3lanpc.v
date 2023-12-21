`timescale 10ns / 10ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/15/2022 03:48:06 PM
// Design Name: 
// Module Name: state_machine
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

module fsm_3lanpc(
	input	clk,ce,rst,
	input   [9:0]  t_short, t_off_on, t_on_offv0, t_offv0_on, t_off_oni0,
	input   [1:0]   v_lev,
	input   [1:0]   comm_type,
	output reg [5:0]  s_out
    /*,
    output logic change,
    output _states_t state,next_state,old_state,
    output logic transition,
    output logic finish_transition,
    output logic[`TDELAY_WIDTH-1:0] counter,
    output logic[`TDELAY_WIDTH-1:0] max_counter,
    output logic[2:0] delay_timer*/
	);

	localparam P=0;
	localparam Z_U2=1;
	localparam Z_U1=2;
	localparam Z_L1=3;
	localparam Z_L2=4;
	localparam N=5;
	//P, Z_U2, Z_U1, Z_L1, Z_L2, N
	
	localparam TYPE_I=0;
	localparam TYPE_IU=1;
	localparam TYPE_II=2;
	localparam TYPE_III=3;
    
	reg [2:0]  state, next_state, old_state, state_mem, next_state_mem;
	reg transition;
	reg [1:0] v_lev_past;
	reg  finish_transition;
	reg [9:0] counter;
	reg [2:0] delay_timer;
	reg [9:0] max_counter;
	reg change;
	reg [5:0] S_outcomb;

    initial begin
        state     <= Z_U2;
        old_state <= Z_U2;
        v_lev_past <= 0;
        state_mem <= Z_U2;
        next_state_mem <= Z_U2;
        transition  <= 'd0;
        counter     <= 'd0;
        delay_timer <= 'd0;
        s_out <= 'b010_010;
        //finish_transition <= 0;
        //max_counter <= 'd254;
        change<=0;
    end

	always @(posedge clk or posedge rst) begin     
		if (rst) begin
			state     <= Z_U2;
			old_state <= Z_U2;
			//next_state <= Z_U2;
			v_lev_past <= 0;
			state_mem <= Z_U2;
			next_state_mem <= Z_U2;
			transition  <= 'd0;
			counter     <= 'd0;
			delay_timer <= 'd0;
			s_out <= 'b010_010;
			//finish_transition <= 0;
			//max_counter <= 'd254;
			change<=0;
		end
        
		else begin
			v_lev_past <= v_lev;
			s_out <= S_outcomb;
			counter     <= (transition && (counter < max_counter - 1))? counter + 'd1: 'd0;
			delay_timer <= (transition && counter == max_counter - 1)? delay_timer + 'd1: (transition)? delay_timer:   'd0;
			//transition  <= ((state != next_state) && !finish_transition)? 'd1: 'd0;
			if(state!=next_state) begin
				transition<=1;
			end
			if(finish_transition) begin
				transition<=0;
				old_state <=state;
			end
			state       <= next_state;
		end 
	end
    
    
	// COMBINATIONAL LOGIC FOR STATES
	always @* begin
		next_state = state;
		//if(transition==0) begin
		case(state)
			P   :   begin
				if(v_lev == 'd0 && transition=='d0) begin
					case(comm_type)
						TYPE_I: next_state = Z_U2;
						TYPE_II: next_state = Z_L2;
						TYPE_III: next_state = Z_L1;
						default: next_state = Z_U2;
					endcase
				end
			end
			Z_U2:   begin
				if(v_lev == 'd1 && transition=='d0) 
					next_state = P;
				else if(v_lev == 'd2 && transition=='d0)
					next_state = N;              
				end
			Z_U1:   begin     
				if(v_lev == 'd1 && transition=='d0)
					next_state = P;
				else if(v_lev == 'd2 && transition=='d0)
					next_state = N;             
			end
			Z_L1:   begin   
				if(v_lev == 'd1 && transition=='d0)
					next_state = P;
				else if(v_lev == 'd2 && transition=='d0)
					next_state = N;               
			end
			Z_L2:   begin     
				if(v_lev == 'd1 && transition=='d0)
					next_state = P;
				else if(v_lev == 'd2 && transition=='d0)
					next_state = N;             
			end
			N   :   begin   
				if(v_lev == 'd0 && transition=='d0) begin
					case(comm_type)
						TYPE_I: next_state = Z_L2;
						TYPE_II: next_state = Z_U2;
						TYPE_III: next_state = Z_U1;
						default: next_state = Z_L2;
					endcase
				end               
			end
		endcase
        //end
	end
    
	// Logic for transitions
	always @* begin
		finish_transition=0;
		max_counter='d255;
		//if(transition) begin
		case(old_state)
			Z_U2: begin // ZU2 ->
				//S_outcomb='b010_010;
				if(transition) begin
					case(next_state)
						P: begin // ZU2 -> P (type I)
							case(delay_timer)
								0: begin
									S_outcomb='b010_000;
									max_counter=t_off_on;
									finish_transition=0;
								end
								1: begin
									S_outcomb='b110_000;
									max_counter=t_short;
									finish_transition=0;
								end
							2: begin
									S_outcomb='b110_001;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						N: begin // ZU2 -> N (type II)
							case(delay_timer)
								0: begin
									S_outcomb='b011_010;
									max_counter=t_short;
									finish_transition=0;
								end
								1: begin
									S_outcomb='b001_010;
									max_counter=t_off_on;
									finish_transition=0;
								end
								2: begin
									S_outcomb='b001_110;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						default: begin // ZU2 -> ZU2
								S_outcomb='b010_010;
								finish_transition=0;
						end                      
					endcase
				end
				else begin 
					S_outcomb='b010_010;
				end                  
			end
			Z_U1: begin // ZU1 ->
				//S_outcomb='b010_110; 
				if(transition) begin
					case(next_state)
						P: begin // ZU1 -> P (type IU)
							case(delay_timer)
								0: begin
									S_outcomb='b010_010;
									max_counter=t_off_oni0;
									finish_transition=0;
								end
								1: begin
									S_outcomb='b010_011;
									max_counter=t_short;
									finish_transition=0;
								end
								2: begin
									S_outcomb='b010_001;
									max_counter=t_off_on;
									finish_transition=0;
								end
								3: begin
									S_outcomb='b110_001;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						N: begin // ZU2 -> N (type III)
							case(delay_timer)
								0: begin
									S_outcomb='b000_110;
									max_counter=t_off_on;
									finish_transition=0;
								end
								1: begin
									S_outcomb='b001_110;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						default: begin // ZU1 -> ZU1
							S_outcomb='b010_110;
							finish_transition=0;
						end                      
					endcase
				end
				else begin
					S_outcomb='b010_110; 
				end                  
			end
			Z_L1: begin // ZL1 ->
				//S_outcomb='b101_001;
				if(transition) begin
					case(next_state)
						P: begin // ZL2 -> P (type III)
							case(delay_timer)
								0: begin
									S_outcomb='b100_001;
									max_counter=t_off_on;
									finish_transition=0;
								end
								1: begin
									S_outcomb='b110_001;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						N: begin // ZL2 -> N (type IU)
							case(delay_timer)
								0: begin
									S_outcomb='b001_001;
									max_counter=t_off_oni0;
									finish_transition=0;
								end
								1: begin
									S_outcomb='b001_011;
									max_counter=t_short;
									finish_transition=0;
								end
								2: begin
									S_outcomb='b001_010;
									max_counter=t_off_on;
									finish_transition=0;
								end
								3: begin
									S_outcomb='b001_110;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						default: begin // ZL2 -> ZL2
							S_outcomb='b101_001;
							finish_transition=0;
						end                      
					endcase
				end
				else begin
						S_outcomb='b101_001; 
				end                   
			end
			Z_L2: begin // ZL2 ->
				//S_outcomb='b001_001;
				if(transition) begin
					case(next_state)
						P: begin // ZL2 -> P (type II)
							case(delay_timer)
								0: begin
									S_outcomb='b011_001;
									max_counter=t_short;
									finish_transition=0;
								end
								1: begin
									S_outcomb='b010_001;
									max_counter=t_off_on;
									finish_transition=0;
								end
								2: begin
									S_outcomb='b110_001;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						N: begin // ZL2 -> N (type I)
							case(delay_timer)
								0: begin
									S_outcomb='b001_000;
									max_counter=t_off_on;
									finish_transition=0;
								end
								1: begin
									S_outcomb='b001_100;
									max_counter=t_short;
									finish_transition=0;
								end
								2: begin
									S_outcomb='b001_110;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						default: begin // ZL2 -> ZL2 
							S_outcomb='b001_001;
							finish_transition=0;
						end                      
					endcase
				end
				else begin
						S_outcomb='b001_001; 
				end                    
			end
			P: begin // P ->
				//S_outcomb='b110_001;
				if(transition) begin
					case(next_state)
						Z_U2: begin // P -> ZU2 (type I)
							case(delay_timer)
								0: begin
									S_outcomb='b110_000;
									max_counter=t_short;
									finish_transition=0;
								end
								1: begin
									S_outcomb='b010_000;
									max_counter=t_off_on;
									finish_transition=0;
								end
								2: begin
									S_outcomb='b010_010;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						Z_U1: begin // P -> ZU1 (type IU) [not used in normal operation]
							case(delay_timer)
								0: begin
									S_outcomb='b010_001;
									max_counter=t_short;
									finish_transition=0;
								end
								1: begin
									S_outcomb='b010_011;
									max_counter=t_off_on;
									finish_transition=0;
								end
								2: begin
									S_outcomb='b010_010;
									max_counter=t_short;
									finish_transition=0;
								end
								3: begin
									S_outcomb='b010_110;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						Z_L1: begin // P -> ZL1 (type III)
							case(delay_timer)
								0: begin // S_outcomb[2] = 0
									S_outcomb='b100_001; 
									max_counter=t_off_on;
									finish_transition=0;
								end
								1: begin // S_outcomb[3] = 1
									S_outcomb='b101_001;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						Z_L2: begin // P -> ZL2 (type II) b110_001 -> b001_001
							case(delay_timer)
								0: begin // S_outcomb[1] = 0
									S_outcomb='b010_001;
									max_counter=t_off_on;
									finish_transition=0;
								end
								1: begin // S_outcomb[3] = 1
									S_outcomb='b011_001;
									max_counter=t_short;
									finish_transition=0;
								end
								2: begin // S_outcomb[2] = 0
									S_outcomb='b001_001;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						default: begin // P -> P
							S_outcomb='b110_001;
							finish_transition=0;
						end                        
					endcase
				end
				else begin 
						S_outcomb='b110_001;
				end                   
			end
			N: begin // N ->
				if(transition) begin
					case(next_state)
						Z_U2: begin // N -> ZU2 (type II)
							case(delay_timer)
								0: begin // S_outcomb[4] = 0
									S_outcomb='b001_010;
									max_counter=t_off_on;
									finish_transition=0;
								end
								1: begin // S_outcomb[2] = 1
									S_outcomb='b011_010;
									max_counter=t_on_offv0;
									finish_transition=0;
								end
								2: begin // S_outcomb[3] = 0
									S_outcomb='b010_010;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						Z_U1: begin // N -> ZU1 (type III)
							case(delay_timer)
								0: begin // S_outcomb[3] = 0
									S_outcomb='b000_110;
									max_counter=t_off_on;
									finish_transition=0;
								end
								1: begin // S_outcomb[2] = 1
									S_outcomb='b010_110;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						Z_L1: begin // N -> ZL1 (type IU) [not used in normal operation]
							case(delay_timer)
								0: begin // S_outcomb[4] = 0
									S_outcomb='b001_010; 
									max_counter=t_off_on;
									finish_transition=0;
								end
								1: begin // S_outcomb[6] = 1
									S_outcomb='b001_011;
									max_counter=t_short;
									finish_transition=0;
								end
								2: begin // S_outcomb[5] = 0
									S_outcomb='b001_001;
									max_counter=t_short;
									finish_transition=0;
								end
								3: begin // S_outcomb[1] = 1
									S_outcomb='b101_001;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						Z_L2: begin // N -> ZL2 (type I)
							case(delay_timer)
								0: begin // S_outcomb[5] = 0
									S_outcomb='b001_100;
									max_counter=t_short;
									finish_transition=0;
								end
								1: begin // S_outcomb[4] = 0
									S_outcomb='b001_000;
									max_counter=t_off_on;
									finish_transition=0;
								end
								2: begin // S_outcomb[6] = 1
									S_outcomb='b001_001;
									max_counter=t_short;
									finish_transition=(counter==(max_counter-1)) ? 1 : 0;
								end
							endcase
						end
						default: begin // N -> N
							S_outcomb='b001_110;
							finish_transition=0;
						end                        
					endcase
				end
				else begin 
					S_outcomb='b001_110;
				end                   
			end
		endcase
	end
    
endmodule