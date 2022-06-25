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
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
char target[2] = {'*', '*'};
char *controller;  
bool numberInput = false;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


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
    if(numberInput == false && target[0] == '*' && key != 'D') {
      target[0] = key;
      Serial.print("[0][");
      Serial.print(key);
      Serial.println("]");
      numberInput = true;
    }
    if(numberInput == false && target[1] == '*' && key != 'D') {
      target[1] = key;
      Serial.print("[1][");
      Serial.print(key);
      Serial.println("]");
      numberInput = true;
    }
    Serial.println("------------");
    Serial.println(numberInput);
    Serial.println(target[0]);
    Serial.println(target[1]);
    Serial.println(key);
    Serial.println("------------");
    if (target[0] != '*' && target[1] != '*' && key == 'D') {
      Serial.print("Llamando #");
      Serial.print(target[0]);
      Serial.println(target[1]);
      
      vw_send((uint8_t *)target, strlen(target)+1);  
   vw_wait_tx(); // Wait until the whole message is gone 
   digitalWrite(10,HIGH);  
   delay(500);
   controller=0 ;  
            vw_send((uint8_t *)controller, strlen(controller)+1);  
    vw_wait_tx(); // Wait until the whole message is gone  
    digitalWrite(10, LOW);  
   digitalWrite(10, LOW);  
      target[0] =  '*';
      target[1] =  '*';
      numberInput = true;
      } else {
        controller=0 ;  
            vw_send((uint8_t *)controller, strlen(controller));  
    vw_wait_tx(); // Wait until the whole message is gone  
    digitalWrite(10, LOW);  
      }
    
    numberInput = false;
  }
  // Serial.println(controller);  
  
 }  
