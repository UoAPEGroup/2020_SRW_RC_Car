#include <SoftwareSerial.h>
SoftwareSerial HM10(0, 1); // RX = 0, TX = 1

char appData;  
String inData = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
  //pinMode(13, OUTPUT); // onboard LED
  //digitalWrite(13, LOW); // switch OFF LED

}  

  
void loop() {
  HM10.listen();  // listen the HM10 port
  while (HM10.available() > 0) {   // if HM10 sends something then read
    appData = HM10.read();
    inData = String(appData);  // save the data in string format
    Serial.write(appData);
  }
  
  if (Serial.available()) {           // Read user input if available.
    delay(10);
    HM10.write(Serial.read());
  }
}
