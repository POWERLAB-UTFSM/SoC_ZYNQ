#include <math.h>

#include "hw_zedboard.h"

int main(){
    
    int status= XST_SUCCESS;
    XGpio xgpio_my_inst;
    
    u32 my_write=0;
    double my_sinans=0.0;
    double my_sinarg=1.57079;

    status = xgpio_myinit(&xgpio_my_inst,MY_GPIO0_BASEADDR);

    while(1){
        my_sinans=sin(my_sinarg);  
        XGpio_DiscreteWrite(&xgpio_my_inst,1,my_write);
    }

    return status;
}