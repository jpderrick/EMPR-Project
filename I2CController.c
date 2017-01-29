#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lpc17xx_pinsel.h>
#include <lpc_types.h>
#include <lpc17xx_i2c.h>

LPC_I2C_TypeDef *I2C = LPC_I2C1;

void setupI2C(void){

	I2C_Init(I2C, 100000);
	I2C_Cmd(I2C,ENABLE);

}