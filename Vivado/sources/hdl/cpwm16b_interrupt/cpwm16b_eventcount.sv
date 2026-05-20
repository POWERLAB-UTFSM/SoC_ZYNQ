`timescale 10ns / 100ps

module cpwm16b_eventcount #
(
    parameter PWMWIDTH = 16
)
(
    input wire clk,
    input wire tick,
    input wire ce,
    input wire rst,

    input wire [PWMWIDTH-1:0] carrier_max,
    input wire [PWMWIDTH-1:0] carrier,

    input wire [3:0] event_count,
    input wire [1:0] eventcount_mode,

    output reg sync
);

    /* ------------------------------------------------ */
    /* INTERNAL SIGNALS                                 */
    /* ------------------------------------------------ */

    reg [3:0] current_count;

    // sync pulse stretcher
    reg [PWMWIDTH-1:0] sync_cnt;

    wire is_max;
    wire is_min;

    reg is_max_d;
    reg is_min_d;

    wire max_pulse;
    wire min_pulse;

    wire event_detected;

    /* ------------------------------------------------ */
    /* MIN / MAX DETECTION                              */
    /* ------------------------------------------------ */

    assign is_max = (carrier == carrier_max);
    assign is_min = (carrier == 0);

    /* ------------------------------------------------ */
    /* EDGE DETECTION                                   */
    /* ------------------------------------------------ */

    always @(posedge clk or posedge rst)
    begin
        if(rst)
        begin
            is_max_d <= 0;
            is_min_d <= 0;
        end
        else if (ce && tick)
        begin
            is_max_d <= is_max;
            is_min_d <= is_min;
        end
    end

    assign max_pulse = is_max & ~is_max_d;
    assign min_pulse = is_min & ~is_min_d;

    /* ------------------------------------------------ */
    /* EVENT SELECTION                                  */
    /* ------------------------------------------------ */

    assign event_detected =
        (eventcount_mode == 2'b01) ? min_pulse :
        (eventcount_mode == 2'b10) ? max_pulse :
        (eventcount_mode == 2'b11) ? (max_pulse | min_pulse) :
                                     1'b0;


    /* ------------------------------------------------ */
    /* SYNC OUTPUT                                      */
    /* ------------------------------------------------ */

    //assign sync = (sync_cnt != 0);

    /* ------------------------------------------------ */
    /* EVENT COUNTER + SYNC GENERATION                  */
    /* ------------------------------------------------ */

    always @(posedge clk or posedge rst)
    begin
        if(rst)
        begin
            current_count <= 0;
            sync_cnt <= 0;
            sync <= 0;
        end
        else if (ce && tick)
        begin

            /* décrémentation pulse sync */
            if(sync_cnt != 0)
            begin
                sync_cnt <= sync_cnt - 1;
                sync <= 1;
            end
            else
            begin
                sync <= 0;
            end

            if(event_detected)
            begin
                /* protection event_count = 0 */
                if(event_count == 0)
                begin
                    current_count <= 0;
                end
                else
                begin
                    if(current_count == (event_count - 1))
                    begin
                        current_count <= 0;

                        // pulse sync = 1/4 période carrier
                        sync_cnt <= (carrier_max >> 2);
                    end
                    else
                    begin
                        current_count <= current_count + 1;
                    end
                end
            end
        end
    end

endmodule