// Transimtter

#include <VirtualWire.h>  
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'#','0','*','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


 char *controller;  
 int buttonState1 = 0;  
 void setup()   
 {  
  // put your setup code here, to run once:  
 Serial.begin(9600);  
 pinMode(10,OUTPUT);  
 vw_set_ptt_inverted(true); //  
 vw_set_tx_pin(12);  
 vw_setup(4000);// speed of data transfer Kbps  
 delay(100);}  
 void loop()  
 {  
   char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
    buttonState1 = 1;
  } else {
    buttonState1 = 0;
  }
  // Serial.println(controller);  
  if (buttonState1 == 1)  
 {  
   vw_send((uint8_t *)key, strlen(key));  
   vw_wait_tx(); // Wait until the whole message is gone  
   digitalWrite(10,LOW);  
   }  
  else  
  {  
  controller="0" ;  
 vw_send((uint8_t *)controller, strlen(controller));  
 vw_wait_tx(); // Wait until the whole message is gone  
 digitalWrite(10, HIGH);  
  }  
 }  
