#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lpc17xx_pinsel.h>
#include <lpc_types.h>
#include <lpc17xx_i2c.h>

LPC_I2C_TypeDef *I2C = LPC_I2C1;
I2C_M_SETUP_Type ScreenTransferConfig;

void setupI2C(void){

	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 3;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 0;

	    //Configure P0.0
	PINSEL_ConfigPin(&PinCfg);

	    //Configure P0.1
	PinCfg.Pinnum = 1;
	PINSEL_ConfigPin(&PinCfg);


	I2C_Init(I2C, 100000);
	I2C_Cmd(I2C,ENABLE);

}
int SetupScreen(void){

	//The Data to send
	uint8_t initScreen[12] = {0x00,0x34,0x0c,0x06,0x35,0x04,0x10,0x42,0x9f,0x34,0x02,0x20};

	ScreenTransferConfig.tx_length = 12;
	ScreenTransferConfig.sl_addr7bit = 59;
	ScreenTransferConfig.tx_data = initScreen;

	if(I2C_MasterTransferData(I2C, &ScreenTransferConfig, I2C_TRANSFER_POLLING) == SUCCESS){
		return 1;
	}else {
		return 0;
	}

}

void ScreenController(int screenUID=0){
	//Take the screenUID requested, and run the correct function
	switch(screenUID){
		case 0:
			mainScreen();
			break;
		case 1:
			chooseModeScreen();
			break;

	}
	return;
}

void gatherScreenData(int screenUID){
	//Collect all of the data needed for the screen that's static
	return;
}

void mainScreen(void){
	//show the main screen
	uint8_t nextScreenID[4] = [1,70,70,70];
	uint8_t writeBlank[33] = {0x40, 'A', 'D', 'D', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 'C', 'O', 'N', 'F', 'I', 'G', 'V', 'U', 'U', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 'C', 'L', 'E', 'A', 'R'};
	showScreen(writeBlank);
	//while (no valid keyboard input detected){

	//}
	//ScreenController(nextScreenID[X]);
}

void chooseModeScreen(void){
	//choose whether this module shall be serial or parallel
	uint8_t nextScreenID[4] = [100,100,,4];
	uint8_t writeBlank[33] = {0x40, 'A', 'D', 'D', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 'C', 'O', 'N', 'F', 'I', 'G', 'V', 'U', 'U', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 'C', 'L', 'E', 'A', 'R'};
	showScreen(writeBlank);
	//while (no valid keyboard input detected){

	//}
	//ScreenController(nextScreenID[X]);
}

int showScreen(uint8_t screenData[]){

	ScreenTransferConfig.tx_length = 33; //Length is always 33 (since 32 items of data, plus the write bit)
	ScreenTransferConfig.tx_data = screenData;
	I2C_MasterTransferData(I2C, &ScreenTransferConfig, I2C_TRANSFER_POLLING);

	if(I2C_MasterTransferData(I2C, &ScreenTransferConfig, I2C_TRANSFER_POLLING) == SUCCESS){
		return 1;
	}else {
		return 0;
	}
	
}

void main(void){
		setupI2C();
		if(SetupScreen() == 0){
			//Screen hasn't been set up correctly, get rekt
		}else {
			//Run the Screen
			ScreenController(); //Start the screen off at controlller 1
		}
			
		
		
}
	
	
	