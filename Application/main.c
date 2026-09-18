#define F_CPU 16000000UL

#include <util/delay.h>

#include "Dio.h"
#include "Dio_cfg.h"


int main()
{
    Dio_Init(DioConfig, CFGS);

    DIO_ReturnPinState_t previousInputState = DIO_HIGH;
    DIO_PinState_t ledState = LOW;

    while(1)
    {
        DIO_ReturnPinState_t inputState = Dio_ReadPin(DIO_PORT_C, 1);

        if ((previousInputState == DIO_HIGH) && (inputState == DIO_LOW))
        {
            ledState = (ledState == HIGH) ? LOW : HIGH;
            Dio_WritePin(DIO_PORT_D, 6, ledState);
            _delay_ms(25);
        }

        previousInputState = inputState;
        _delay_ms(10);
    }

}