#include "hdfcpwm.h"

/*------------------------------------------------------------------------------------------*/
/* main */
/*------------------------------------------------------------------------------------------*/
int main(void)
{
    int status;

    /* -------- HW INIT -------- */
    status = _HW_My_Init();
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    /* -------- PWM CONFIG -------- */
    XCpwm6b_3lxnpc_My_Init(&xcpwm6b_my_inst);

    /* -------- LOOP -------- */
    while (1)
    {
        /* 
         * ton système est piloté :
         * - soit par interruption (sync_event)
         * - soit statique
         */
    }

    return XST_SUCCESS;
}

