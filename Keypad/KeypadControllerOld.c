#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lpc17xx_pinsel.h>
#include <lpc_types.h>
#include <lpc17xx_i2c.h>
#include "serial.h"

LPC_I2C_TypeDef *I2C = LPC_I2C1;
I2C_M_SETUP_Type ScreenTransferConfig;
char lastKeyPressed = "X";

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
int listenForKey(void){
	//Just poll the keyboard, waiting for a key to be pressed, 
	//return 1 if a key has been pressed
	while(lastKeyPressed == "X"){
		//Loop through each column
		for(int i = 1;i<=4;i++){
			KeypadTransferConfig.rx_length = 1;
			uint8_t buffer[1] = {};
			KeypadTransferConfig.rx_data = buffer;
			enableColumn(i);
			I2C_MasterTransferData(I2C, &TransferConfig, I2C_TRANSFER_POLLING);
			lastKeyPressed = bufferToChar(buffer[0]);
		}
	}
	return 1;
}	
char getKeyPressed(void){

	return lastKeyPressed;

}

int listenForMenu(char L1, char L2, char R1, char R2){

	while(lastKeyPressed != L1 && lastKeyPressed != L2 && lastKeyPressed != R1 && lastKeyPressed != R2){
		listenForKey()	
	}	
	
	if(lastKeyPressed == L1){
		return 1;
	}else if(lastKeyPressed == L2){
		return 2;
	}else if(lastKeyPressed  == R1){
		return 3;
	}else if(lastKeyPressed == R2){
		return 4;
	}
	
}

int isLastKeyPressed(char key){

	if(key == lastKeyPressed){
		return 1;
	}else {
		return 0;
	}
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
	serial_init();
	if(SetupKeypad() == 0){
		//There's a problem witht he keypad setting up
		write_usb_serial_blocking("Keypad Problem",14);
	}else{
		write_usb_serial_blocking("Keypad Setup",12);
		listenForKey();
	}

}

// Read options
int read_usb_serial_none_blocking(char *buf,int length)
{
	return(UART_Receive((LPC_UART_TypeDef *)LPC_UART0, (uint8_t *)buf, length, NONE_BLOCKING));
}

// Write options
int write_usb_serial_blocking(char *buf,int length)
{
	return(UART_Send((LPC_UART_TypeDef *)LPC_UART0,(uint8_t *)buf,length, BLOCKING));
}
// init code for the USB serial line
void serial_init(void)
{
	UART_CFG_Type UARTConfigStruct;			// UART Configuration structure variable
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;	// UART FIFO configuration Struct variable
	PINSEL_CFG_Type PinCfg;				// Pin configuration for UART
	/*
	 * Initialize UART pin connect
	 */
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	// USB serial first
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 3;
	PINSEL_ConfigPin(&PinCfg);
		
	/* Initialize UART Configuration parameter structure to default state:
	 * - Baudrate = 9600bps
	 * - 8 data bit
	 * - 1 Stop bit
	 * - None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);
	/* Initialize FIFOConfigStruct to default state:
	 * - FIFO_DMAMode = DISABLE
	 * - FIFO_Level = UART_FIFO_TRGLEV0
	 * - FIFO_ResetRxBuf = ENABLE
	 * - FIFO_ResetTxBuf = ENABLE
	 * - FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	// Built the basic structures, lets start the devices/
	// USB serial
	UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UARTConfigStruct);		// Initialize UART0 peripheral with given to corresponding parameter
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &UARTFIFOConfigStruct);	// Initialize FIFO for UART0 peripheral
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);			// Enable UART Transmit
	
}
