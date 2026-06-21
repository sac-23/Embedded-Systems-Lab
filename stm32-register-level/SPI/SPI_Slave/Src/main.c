#include "gpio.h"
#include "spi.h"

uint8_t ucData;

int main(void)
{


    vGPIO_Init();
    vSPI_Init();

    while(1)
    {
        ucData = ucSPI_Receive();

        if(ucData == 'A')
        {
            vGPIO_TogglePin();
        }
    }
}
