#include "adxl345.h"
#include "i2c.h"
#include "gpio.h"

ADXL345_Data_t accel;

void vdelay(uint32_t count) {

	while (count--) ;
}

uint8_t id;

int main(void)
{
    vGPIO_Init();

    vI2C1_Init();

    id = uADXL345_ReadRegister(ADXL345_DEVID);

    if (id == 0xE5)
    {
    	vADXL345_Init();
    	while(1)
    	{
    	    vADXL345_ReadXYZ(&accel);
    	    vGPIO_TogglePin();
    	    vdelay(50000);
    	}
    }
    else
    {
    	vGPIO_SetPin();
    }
}
