`timescale 10ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/07/2026 11:08:08 AM
// Design Name: 
// Module Name: interrupt
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

module cpwm16b_interrupt
(
    input clk,
    input ce,
    input rst,

    /* event source */
    input sync_event,

    /* cpu control */
    input irq_enable,
    input irq_clear,

    /* status */
    output wire irq_status,

    /* interrupt line */
    output wire interrupt
);

    reg irq_status_reg;
    reg sync_event_d;
    wire sync_rise;
    reg irq_clear_sync1;
    reg irq_clear_sync2;
    
    
    /*Rising edge sync*/
    always @(posedge clk or posedge rst)
    begin
        if(rst)
            sync_event_d <= 0;
    
        else
            sync_event_d <= sync_event;
    end
    
    assign sync_rise = sync_event & ~sync_event_d;
    
    
    /*Synchroniseur CDC*/
    always @(posedge clk or posedge rst)
    begin
        if(rst)
        begin
            irq_clear_sync1 <= 0;
            irq_clear_sync2 <= 0;
        end
        else
        begin
            irq_clear_sync1 <= irq_clear;
            irq_clear_sync2 <= irq_clear_sync1;
        end
    end
    /*
     * IRQ latch
     */
    always @(posedge clk or posedge rst)
    begin
        if(rst)
        begin
            irq_status_reg <= 0;
        end
        
        /* priorité absolue CPU */
        else if(irq_clear_sync2)
        begin
            irq_status_reg <= 0;
        end
        
        else if (ce)
        begin
            if(sync_rise && irq_enable)
            begin
                irq_status_reg <= 1;
            end
    
        end
    end

    /*
     * outputs
     */
    assign irq_status = irq_status_reg;

    assign interrupt =
        irq_status_reg &
        irq_enable;

endmodule