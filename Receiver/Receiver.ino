/*
* By Ramiro Guiterrez Alaniz
* Date Sunday, January 31, 2016
* This is the Receiver Router code
* Will be connected to the desktop software
*/

/*
* Set up function
*/
void setup() {
	// initialize serial communication 1
	// This is for the system connection
	Serial.begin(9600);
  // initialize serila communication 2
	// This is the serial for the xbee
  Serial1.begin(9600);
}// End of setup function

/*
* Loop function
*/
void loop() {
  // see if there's incoming serial data:
  if (Serial1.available() > 0) {
    byte tag[10];
    int i = 0;
    Serial.println( "" );
    Serial.println( "Tag : " );
    while( i < 10 ){
      incomingByte = Serial1.read();
      tag[i] = incomingByte;
      i++;
    }
    int j = 0;
    while( j<10 ) {
      Serial.print( tag[j] );
      Serial.print( "-" );  
      j++;
    }
  }// End of serial validation
  // the fucken delay
  delay(100);
}// End of loop function
