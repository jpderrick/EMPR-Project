
I2C_M_SETUP_Type KeypadTransferConfig;
char *lastKeyPressed = "X";
char output[30];
uint8_t setHigh[] = {0x7F};

char *bufferToChar(char buffer){

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
	
	KeypadTransferConfig.tx_length = 1;
	KeypadTransferConfig.sl_addr7bit = 33;
	KeypadTransferConfig.tx_data = setHigh;
	I2C_MasterTransferData(I2C, &KeypadTransferConfig, I2C_TRANSFER_POLLING);
}

int listenForKey(void){
	int i =1;
	uint8_t buffer[1] = {};
	int keyPressed = 0;
	char* previousKeyPressed = lastKeyPressed;
	
	while(keyPressed == 0){
		lastKeyPressed = "X";
		for(i=1;i<=4;i++){

			KeypadTransferConfig.rx_length = 1;
			KeypadTransferConfig.rx_data = buffer;
			enableColumn(i);
			I2C_MasterTransferData(I2C,&KeypadTransferConfig,I2C_TRANSFER_POLLING);
			lastKeyPressed = bufferToChar(buffer[0]);
			
			if(lastKeyPressed != "X" || lastKeyPressed != previousKeyPressed){
				keyPressed = 1;
				sprintf(output,"Returned %s \n\r",lastKeyPressed);
				write_usb_serial_blocking(output,strlen(output));
				break;
			}
		

		}
	}
	return 1;
}
char *getKeyPressed(void){

	return lastKeyPressed;

}
	
int listenForMenu(char *L1, char *L2, char *R1, char *R2){

	while(strcmp(lastKeyPressed,L1) != 0 && strcmp(lastKeyPressed,L2) != 0 && strcmp(lastKeyPressed,R1) != 0 && strcmp(lastKeyPressed,R2) != 0){
		listenForKey();	
	}	
	
	if(lastKeyPressed == L1){
		write_usb_serial_blocking("Selected L1 \n\r",16);
		return 1;
	}else if(lastKeyPressed == L2){
		write_usb_serial_blocking("Selected L2 \n\r",16);
		return 2;
	}else if(lastKeyPressed  == R1){
		write_usb_serial_blocking("Selected R1 \n\r",16);
		return 3;
	}else if(lastKeyPressed == R2){
		write_usb_serial_blocking("Selected R2 \n\r",16);
		return 4;
	}
	
}

int isLastKeyPressed(char *key){

	if(strcmp(key,lastKeyPressed) == 0){
		return 1;
	}else {
		return 0;
	}
}


void main(void){
	serial_init();
	setupI2C();
	listenForMenu("A","B","C","D");
}

