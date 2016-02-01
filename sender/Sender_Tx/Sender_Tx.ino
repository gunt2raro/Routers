/**
 * By Ramiro Gutierrez Alaniz
 * Date Sunday, January 31, 2016
 * Router arduino code
 */
 
#include <XBee.h>

/*
This example is for Series 1 XBee
Sends a TX16 or TX64 request with the value of analogRead(pin5) and checks the status response for success
Note: In my testing it took about 15 seconds for the XBee to start reporting success, so I've added a startup delay
*/

XBee xbee = XBee();

unsigned long start = millis();

// allocate two bytes for to hold a 10-bit analog reading
uint8_t payload[] = { 0, 0 };

// with Series 1 you can use either 16-bit or 64-bit addressing

// 16-bit addressing: Enter address of remote XBee, typically the coordinator
Tx16Request tx = Tx16Request(0x1874, payload, sizeof(payload));

// 64-bit addressing: This is the SH + SL address of remote XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x4008b490);
// unless you have MY on the receiving radio set to FFFF, this will be received as a RX16 packet
//Tx64Request tx = Tx64Request(addr64, payload, sizeof(payload));

TxStatusResponse txStatus = TxStatusResponse();

/*
 * setup function
 */
void setup() {
  // serial init on the monitor
  Serial.begin( 9600 );
  // Serial init on the xbee
  Serial1.begin( 9600 );
  xbee.setSerial(Serial1);
}// End of setup function

/*
 * Loop function
 */
void loop() {
   
    // start transmitting after a startup delay.  Note: this will rollover to 0 eventually so not best way to handle
    if (millis() - start > 15000) {
      // break down 10-bit reading into two bytes and place in payload
      pin5 = analogRead(5);
      payload[0] = pin5 >> 8 & 0xff;
      payload[1] = pin5 & 0xff;
      
      xbee.send(tx);
    }
  
    // after sending a tx request, we expect a status response
    // wait up to 5 seconds for the status response
    if (xbee.readPacket(5000)) {
      // got a response!
      // should be a znet tx status            	
    	if (xbee.getResponse().getApiId() == TX_STATUS_RESPONSE) {
    	   xbee.getResponse().getTxStatusResponse(txStatus);
    		
    	   // get the delivery status, the fifth byte
           if (txStatus.getStatus() == SUCCESS) {
            	// success.  time to celebrate
           } else {
            	// the remote XBee did not receive our packet. is it powered on?
             	flashLed(errorLed, 3, 500);
           }
        }      
    } else if (xbee.getResponse().isError()) {
      // nss.print("Error reading packet.  Error code: ");  
      // nss.println(xbee.getResponse().getErrorCode());
      // or flash error led
    }
    // Shitty delay
    delay(1000);
}// End of loop function
