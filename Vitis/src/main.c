#include "hdfcpwm.h"

/*------------------------------------------------------------------------------------------*/
/* main */
/*------------------------------------------------------------------------------------------*/
int main(void)
{
    
    int status;
    unsigned int i=1;

    /* -------- HW INIT -------- */
    status = _HW_My_Init();
    if (status != XST_SUCCESS)
        return XST_FAILURE;


    /* -------- LOOP -------- */
    while (1)
    {
        /* 
         * ton système est piloté :
         * - soit par interruption (sync_event)
         * - soit statique
         */
         XCpwm6b_WriteEventCount(&xcpwm6b_my_inst, i);
         i++;
         if(i==5)
         {
            i=0;
         }
         XCpwm6b_ClearInterrupt(&xcpwm6b_my_inst);
    }

    return XST_SUCCESS;
}

