  #include <Servo.h>
    
  //SERVO 1
  //-------------------------
    Servo servo1;
    const byte datapin1 = 3;
    byte position_S1;
  

void setup() {
  
  //SERVO 1
  //-------------------------
    servo1.attach(datapin1);      // verknüpft den Servomotor mit Pin 3 mit dem Servo-Objekt
    position_S1 = 63;
    servo1.write(position_S1);    // Ausgangsposition festlegen (unterhalb Trichterausgang)
    

    Serial.begin(1200);
}


void loop() {

    position_S1 = 121;
    servo1.write(position_S1);    // Position unter dem Lichtsensor
    delay(2000);
  
    position_S1 = 151;   		     // Position über der Öffnung
    servo1.write(position_S1);
    delay(2000);
    
    position_S1 = 63;   		     // Servo1 zurück an Ausgangsposition
    servo1.write(position_S1);
    delay(2000);
    
}
