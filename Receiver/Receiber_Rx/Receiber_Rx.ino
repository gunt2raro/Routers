/**
 * By Ramiro Gutierrez Alaniz
 * Date Sunday, January 31, 2016
 * Router Master receiver arduino code
 */

// include the library
#include <XBee.h>

// Init all the xbee use variables
XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();

uint8_t option = 0;
uint8_t data = 0;

/*
 * Setup function
 */
void setup() {
  // start serial
  Serial.begin(9600);
  // Serial of the xbee
  Serial1.begin( 9600 );
  xbee.setSerial(Serial1);
}// End of setup function

/*
 * Loop function
 * It will countinously look for packages
 */
void loop() {
    // Start the packe reading
    xbee.readPacket();
    // Verify if it is available on the network
    if (xbee.getResponse().isAvailable()) {
      // Check if there ir a tx package
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE || xbee.getResponse().getApiId() == RX_64_RESPONSE) {
        
        if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
          xbee.getResponse().getRx16Response(rx16);
        	option = rx16.getOption();
        	data = rx16.getData(0);
        } else {
          xbee.getResponse().getRx64Response(rx64);
        	option = rx64.getOption();
        	data = rx64.getData(0);
        }
        
      } else {
      	// not something we were expecting
        flashLed(errorLed, 1, 25);    
      }
    } else if (xbee.getResponse().isError()) {
      // If there is an error, show it
    } 
}// End of loop function
