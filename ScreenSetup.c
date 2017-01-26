#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lpc17xx_pinsel.h>
#include <lpc_types.h>
#include <lpc17xx_i2c.h>

I2C_M_SETUP_Type ScreenScreenTransferConfig;
uint8_t initScreen[12] = {0x00,0x34,0x0c,0x06,0x35,0x04,0x10,0x42,0x9f,0x34,0x02,0x20};


uint8_t writeBlank[33] = {0x40, 'h', 'e', 'l', 'l', 'o', 0xA0, 'w', 'o', 'r', 'l', 'd', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0,};


void main(void){
	
	//Pin Configuration    
	PINSEL_CFG_Type ScreenPinConfig;
	ScreenPinConfig.Funcnum = 3;
	ScreenPinConfig.OpenDrain = 0;
	ScreenPinConfig.Pinmode = 0;
	ScreenPinConfig.Portnum = 0;
	ScreenPinConfig.Pinnum = 0;

	    //Configure P0.0
	PINSEL_ConfigPin(&ScreenPinConfig);

	    //Configure P0.1
	ScreenPinConfig.Pinnum = 1;
	PINSEL_ConfigPin(&ScreenPinConfig);

	LPC_I2C_TypeDef *I2C = LPC_I2C1;
	I2C_Init(I2C, 100000);
	I2C_Cmd(I2C,ENABLE);

	ScreenTransferConfig.tx_length = 12;
	ScreenTransferConfig.sl_addr7bit = 59;
	ScreenTransferConfig.tx_data = initScreen;

	if(I2C_MasterTransferData(I2C, &ScreenTransferConfig, I2C_TRANSFER_POLLING) == SUCCESS){
		
			
			ScreenTransferConfig.tx_length = 33;
			ScreenTransferConfig.tx_data = writeBlank;
			I2C_MasterTransferData(I2C, &ScreenTransferConfig, I2C_TRANSFER_POLLING);
			ScreenTransferConfig.tx_length = 2;
			ScreenTransferConfig.tx_data = screenOn;
			I2C_MasterTransferData(I2C, &ScreenTransferConfig, I2C_TRANSFER_POLLING);
		
		
	}
	
	
	
	
}