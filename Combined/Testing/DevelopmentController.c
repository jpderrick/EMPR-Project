//A File to let us test various controllers
//Through development
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lpc17xx_pinsel.h>
#include <lpc_types.h>
#include <lpc17xx_i2c.h>
#include <lpc17xx_gpio.h>
#include "serial.h"
//Include the controllers
#include "I2CController.c"
#include "KeypadController.c"
#include "ScreenController.c"



void main(void){
	setupI2C();
	SetupScreen();

	ScreenController(0);
}

