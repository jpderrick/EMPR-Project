# EMPR-Project
Code for the EMPR Group Project


#ScreenController
A useful list of screen IDs:<br/>
	0: Main Screen  - 'homepage'<br/>
	1: Parallel or Serial Mode<br/>
	2: Select Filter<br/>
	3: Add Mixer<br/>
	4: <br/>
	70: VUU<br/>
	70: Config Screen<br/>
	70: Reset<br/>
	100: No Screen for this Button<br/>
<br/>
<hr/>

Break everything down into 'modules':<br/>
	- Two Parallel Filters<br/>
	- Mixer (can select original signal input)<br/>
	- Serial Filter<br/>
<br/>
<hr/>

Initial Screen:<br/>
	- CONFIG Button - shows the current setup of the filters etc.<br/>
	- ADD Button - allows them to add a new module<br/>
	- AVG SIGNAL INPUT LEVEL - in real time<br/>

<br/>
<hr/>

Possible input methods for values of filter variables:<br/>
	- potentiometer<br/>
	- keypad => shown in segment display<br/>
	- keypad => shown directly on keypad - probably too much updating of the screen to do<br/>
<br/>
Screens to show:<br/>
	- Main Screen<br/>
	- A<br/>
<br/>
<hr/>

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
									   				  
