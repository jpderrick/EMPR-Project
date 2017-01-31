#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lpc17xx_uart.h>
#include <lpc17xx_pinsel.h>
#include <lpc_types.h>
#include <lpc17xx_i2c.h>

I2C_M_SETUP_Type KeypadTransferConfig;
char lastKeyPressed = "X";

int SetupKeypad(void){

	
}

int listenForKey(void){
	//Just poll the keyboard, waiting for a key to be pressed, 
	//return 1 if a key has been pressed
	while(getLastKeyPressed() == "X"){
		//Loop through each column
		for(int i = 1;i<=4;i++){
			KeypadTransferConfig.rx_length = 1;
			KeypadTransferConfig.rx_data = buffer;
			enableColumn(i);
			I2C_MasterTransferData(I2C, &TransferConfig, I2C_TRANSFER_POLLING);
		}
	}
}

char getKeyPressed(void){


}

int isKeyPressed(char key){

}

void setLastKeyPressed(void){

}

char getLastKeyPressed(void){
	return lastKeyPressed;
}
char bufferToChar(char buffer){

		if(buffer == 0xB7){
			return "2";
		}else if(buffer == 0xBB) {
			return "5";
		}else if(buffer == 0xBD){
			return "8";		
		}else if(buffer == 0xBE){
			return "0";		
		}else if(buffer == 0x77){
			return "1";
		}else if(buffer == 0x7B) {
			return "4";
		}else if(buffer == 0x7D){
			return "7";		
		}else if(buffer == 0x7E){
			return "*";
		}else if(buffer == 0xD7){
			return "3";
		}else if(buffer == 0xDB) {
			return "6";
		}else if(buffer == 0xDD){
			return "9";		
		}else if(buffer == 0xDE){
			return "#";
		}else if(buffer == 0xE7){
			return "A";
		}else if(buffer == 0xEB) {
			return "B";
		}else if(buffer == 0xED){
			return "C";		
		}else if(buffer == 0xEE){
			return "D";
		}
		else {
			return "X";
		}

}

void enableColumn(int column){
	uint8_t setHigh[1];
	switch(column){
		case 1:
			setHigh[0] = 0x7F; 
			break;
		case 2: 
			setHigh[0] = 0xBF;
			break;
		case 3:
			setHigh[0] = 0xDF;
			break;
		case 4:
			setHigh[0] = 0xEF;
			break; 
	}

	TransferConfig.tx_length = 1;
	TransferConfig.sl_addr7bit = 33;
	TransferConfig.tx_data = setHigh;
	I2C_MasterTransferData(I2C, &KeypadTransferConfig, I2C_TRANSFER_POLLING);
}

void main(void){
	setupI2C();

	if(SetupKeypad() == 0){
		//There's a problem witht he keypad setting up
	}else{

	}

}