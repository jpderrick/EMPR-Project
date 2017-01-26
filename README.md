# EMPR-Project
Code for the EMPR Group Project

A useful list of screen IDs:
	0: Main Screen  - 'homepage'
	1: Parallel or Serial Mode
	2: Select Filter
	3: Add Mixer
	4: 
	70: VUU
	70: Config Screen
	70: Reset
	100: No Screen for this Button


Break everything down into 'modules':
	- Two Parallel Filters
	- Mixer (can select original signal input)
	- Serial Filter

Initial Screen:
	- CONFIG Button - shows the current setup of the filters etc.
	- ADD Button - allows them to add a new module
	- AVG SIGNAL INPUT LEVEL - in real time


Possible input methods for values of filter variables:
	- potentiometer
	- keypad => shown in segment display
	- keypad => shown directly on keypad - probably too much updating of the screen to do

Screens to show:
	- Main Screen
	- A

To ADD a filter(s);
								
									User Presses ADD
											|
											|
								   Parallel or Serial?
								   			|
								   		 ___|___________
								   		|  				|
								   		|				|
								   		P				S
								   		|				|
								   	  __|__         	|
								   	 |	   |		   Filter 
								Filter A   Filter B    + Params
								+ Params   + Params     |
									 |	   |			|
									 |_____|			|
									 	|				|
									Mix + Params 	Mix w/ Source?
										|				+ Params
										|				|
									   FIN.			   FIN.
									   				  
