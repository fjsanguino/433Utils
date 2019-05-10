/*
  RFSniffer

  Usage: ./RFSniffer [<pulseLength>]
  [] = optional

  Hacked from http://code.google.com/p/rc-switch/
  by @justy to provide a handy RF code sniffer
*/

#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
     
     
RCSwitch mySwitch;
 


int main(int argc, char *argv[]) {
  
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     
     
     if (argc == 1){
	printf("Usage: %s PIN [pulselength]\n", argv[0]);
	printf("PIN: As in wiringPi\n");
    }
    int PIN = atoi(argv[1]);
    int pulseLength = 0;
    if (argc >= 3) pulseLength = atoi(argv[2]);
	
     if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }


     mySwitch = RCSwitch();
     if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
     mySwitch.enableReceive(PIN);  // Receiver on interrupt 0 => that is pin #2
     
    
  
      while (!mySwitch.available()) {
	 
	}
    
        int value = mySwitch.getReceivedValue();
    
        if (value == 0) {
          printf("Unknown encoding\n");
        } else {    
   
          printf("%i\n", value );
        }
    
        fflush(stdout);
        mySwitch.resetAvailable();
 
      usleep(100); 

    return value;


}

