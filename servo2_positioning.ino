  #include <Servo.h>
    
  //SERVO 2
  //-------------------------
    Servo servo2;
    const byte datapin2 = 17;
    byte position_S2 = 0;
  

void setup() {
  
  //SERVO 2
  //-------------------------
    servo2.attach(datapin2);        // verknüpft den Servomotor mit Pin 17 mit dem Servo-Objekt
    position_S2 = 99;
    servo2.write(position_S2);     // Ausgangsposition festlegen
    

    Serial.begin(1200);
}


void loop() {

    position_S2 = 178;
    servo2.write(position_S2);
    delay(2000);

    position_S2 = 151;
    servo2.write(position_S2);
    delay(2000);

    position_S2 = 125;
    servo2.write(position_S2);
    delay(2000);
    
    position_S2 = 99;   		      // Servo1 zurück an Ausgangsposition
    servo2.write(position_S2);
    delay(2000);

    position_S2 = 73;
    servo2.write(position_S2);
    delay(2000);

    position_S2 = 49;
    servo2.write(position_S2);
    delay(2000);

    position_S2 = 26;
    servo2.write(position_S2);
    delay(2000);
    
}
