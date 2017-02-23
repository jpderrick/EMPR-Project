I2C_M_SETUP_Type ScreenTransferConfig;

void ScreenController(int screenUID);
int filterParams[10][3];

void screenPause(void){
	
	int i = 0;
	for(i=0;i<=10000000;i++){
	}
	GPIO_SetDir(1, 0x40000, 1);
	GPIO_SetValue(1, 0x40000);
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

void clearScreen(void) {
	uint8_t writeBlank[33] = {0x00, 0x01};
	ScreenTransferConfig.tx_length = 2; //Length is always 33 (since 32 items of data, plus the write bit)
	ScreenTransferConfig.tx_data = writeBlank;
	I2C_MasterTransferData(I2C, &ScreenTransferConfig, I2C_TRANSFER_POLLING);
	
}
int showScreen(uint8_t screenData[]){
	clearScreen();
	screenPause();
	ScreenTransferConfig.tx_length = 33; //Length is always 33 (since 32 items of data, plus the write bit)
	ScreenTransferConfig.tx_data = screenData;
	I2C_MasterTransferData(I2C, &ScreenTransferConfig, I2C_TRANSFER_POLLING);

	if(I2C_MasterTransferData(I2C, &ScreenTransferConfig, I2C_TRANSFER_POLLING) == SUCCESS){
		return 1;
	}else {
		return 0;
	}
	
}

void gatherScreenData(int screenUID){
	//Collect all of the data needed for the screen that's static
	return;
}


void lowPassParams(void){

		

}

void mainScreen(void){
	//show the main screen
	//uint8_t nextScreenID[4] = {1,70,70,70};
	uint8_t writeBlank[33] = {0x40, 'a', 'd', 'd', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 'c', 'o', 'n', 'f', 'i', 'g', 'v', 'g', 'u', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 'c', 'l', 'e', 'a', 'r'};
	showScreen(writeBlank);
	screenPause();
	int menuChoice = listenForMenu("A","*","*","*");
	if(menuChoice == 1){
		ScreenController(1);
	}
}

void chooseModeScreen(void){
	
	//choose whether this module shall be serial or parallel
	uint8_t nextScreenID[4] = {100,100,100,4};
	uint8_t writeBlank[33] = {0x40, 'v', 'u', 'u', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 'c', 'l', 'e', 'e', 'r','a', 'd', 'd', 0xA0, 'a', 0xA0, 'f', 0xA0, 0xA0, 0xA0, 'c', 'o', 'b', 'f', 'i', 'g'};
	showScreen(writeBlank);
	screenPause();
	int menuChoice = listenForMenu("A","*","C","*");
	if(menuChoice == 1){
		ScreenController(0);
	}else if(menuChoice == 3){
		ScreenController(2);	
	}
}


void filterParams(int filterID){
	uint8_t filters[4][33] = {
		{}, //give each filter an ID
		{0x40, 'h','e','l','l','o', 0xA0,'w','o','r','l','d', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 'a','n','o','t','h','e','r',0xA0,'f','i','l','t','e','r',0xA0},
		{0x40, 'b','e','l','l','o', 0xA0,'w','o','r','l','d', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 'a','n','o','t','h','e','r',0xA0,'f','i','l','t','e','r',0xA0}
	};
	
}
void chooseFilter(int filterPage){

	/* Each filter has its own ID

		1: Low Pass
		2: High Pass
		3: Flanging
		4: Echo

	*/
	//We'll store all of the filters with their UID in an array which output the right page requested
	uint8_t filters[4][33] = {{1,2,3,4},{0x40, 'h','e','l','l','o', 0xA0,'w','o','r','l','d', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 'a','n','o','t','h','e','r',0xA0,'f','i','l','t','e','r',0xA0},{0x40, 'b','e','l','l','o', 0xA0,'w','o','r','l','d', 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 'a','n','o','t','h','e','r',0xA0,'f','i','l','t','e','r',0xA0}};
	int selectedFilter = 1000;
	int pages = 2;
	screenPause();
	showScreen(filters[filterPage]);
	int menuChoice = listenForMenu("A","B","*","D");
	setLastKey("X");
	GPIO_ClearValue(1, 0x40000);
	if(menuChoice == 1){
		selectedFilter = filters[0][filterPage*2 - 2];
		ScreenController(1);
	}else if(menuChoice == 2){
		selectedFilter = filters[0][filterPage*2 - 1];
	}else if(menuChoice == 4){
		//Change Page
		if(filterPage < pages){
			chooseFilter(filterPage+1);
		}else {
			chooseFilter(1);
		}
	}
		

	

}



void ScreenController(int screenUID){
	//Take the screenUID requested, and run the correct function
	setLastKey("X");
	GPIO_ClearValue(1, 0x40000);
	switch(screenUID){
		case 0:
			mainScreen();
			break;
		case 1:
			chooseModeScreen();
			break;
		case 2:
			chooseFilter(1);
			break;

	}
	
}
	
	
	
