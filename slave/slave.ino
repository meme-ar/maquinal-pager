 #include <VirtualWire.h>

 bool active = false;
 int greenTime = 0;
 int statusLed = 11;
 bool blink = false;
 
 int timePassed (int time) {
  int diff = 0;

  if (millis() <= time) {
    diff = (69666 - time) + millis();
  } else {
    diff = millis() - time;
  }

  return diff;
}

 void setup()  
 {  
 vw_set_ptt_inverted(true); // Required for DR3100  
 vw_set_rx_pin(12);  
 vw_setup(4000); // Bits per sec  
 Serial.begin(9600);  
 pinMode(LED_BUILTIN, OUTPUT);  
 pinMode(statusLed, OUTPUT); 
 vw_rx_start(); // Start the receiver PLL running  
 }  
 
 void loop()  
 {  
 uint8_t buf[VW_MAX_MESSAGE_LEN];  
 uint8_t buflen = 2;  
    
 if (vw_get_message(buf, &buflen)) // Non-blocking  
 {  
  String str = (char*)buf;
  Serial.println(str); 
  String new_str = str.substring(0, 2);
  Serial.println(new_str); 
   if(new_str=="08")  
   {  
    active = true;
   }    
 }
 if (active) {
    if (timePassed (greenTime) >= 500) {
    switchGreen();
    }
 } else {
    digitalWrite(LED_BUILTIN, LOW);  
 }
}

void switchGreen () {
  blink = !blink;
  if (blink) {
    digitalWrite(LED_BUILTIN, HIGH);  
  } else {
    digitalWrite(LED_BUILTIN,LOW); 
  }
  greenTime = millis();
}
