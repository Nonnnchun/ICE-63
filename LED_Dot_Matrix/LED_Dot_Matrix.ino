#include "LedControl.h"


LedControl lc=LedControl(11,12,10);  // DIN,CLK,CS,Number of LED Module

unsigned long delaytime=50;  // time to updates of the display
unsigned long delayt=0.1;

void setup() {
  int devices=lc.getDeviceCount();  // find no of LED modules
  //we have to init all devices in a loop
  for(int address=0;address<devices;address++) {  // set up each device 
    lc.shutdown(address,false);
    lc.setIntensity(address,8);
    lc.clearDisplay(address);
  }
}

void loop() { 
  int devices=lc.getDeviceCount();  // find no of LED modules
  
  for(int row=0;row<1;row++) {
    for(int col=0;col<8;col++) {
      for(int address=0;address<devices;address++) {
        delay(delaytime);
        lc.setLed(address,row,col,true);
      }
    }
  }

  for(int col=7;col<8;col++) {
    for(int row=1;row<8;row++) {
      for(int address=0;address<devices;address++) {
        delay(delaytime);
        lc.setLed(address,row,col,true);
      }
    }
  }

  for(int row=7;row<8;row++) {
    for(int col=6;col>=0;col--) {
      for(int address=0;address<devices;address++) {
        delay(delaytime);
        lc.setLed(address,row,col,true);
      }
    }
  }

  for(int col=0;col<1;col++) {
    for(int row=6;row>0;row--) {
      for(int address=0;address<devices;address++) {
        delay(delaytime);
        lc.setLed(address,row,col,true);
      }
    }
  }
  for(int row=0;row<1;row++) {
    for(int col=0;col<8;col++) {
      for(int address=0;address<devices;address++) {
        delay(delayt);
        lc.setLed(address,row,col,false);
      }
    }
  }

  for(int col=7;col<8;col++) {
    for(int row=1;row<8;row++) {
      for(int address=0;address<devices;address++) {
        delay(delayt);
        lc.setLed(address,row,col,false);
      }
    }
  }

  for(int row=7;row<8;row++) {
    for(int col=6;col>=0;col--) {
      for(int address=0;address<devices;address++) {
        delay(delayt);
        lc.setLed(address,row,col,false);
      }
    }
  }

  for(int col=0;col<1;col++) {
    for(int row=6;row>0;row--) {
      for(int address=0;address<devices;address++) {
        delay(delayt);
        lc.setLed(address,row,col,false);
      }
    }
  }
}
