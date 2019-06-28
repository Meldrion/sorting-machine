  #include <Servo.h>
    
  //SERVO 1
  //-------------------------
    Servo servo1;
    const byte datapin1 = 3;
    byte position_S1 = 0;
  
  //SERVO 2
  //-------------------------
    Servo servo2;
    const byte datapin2 = 17;
    byte position_S2 = 0;
    

void setup() {
  
  //SERVO 1
  //-------------------------
    servo1.attach(datapin1);    // verknüpft den Servomotor mit Pin 3 mit dem Servo-Objekt
    position_S1 = 63;
    servo1.write(position_S1);    // Ausgangsposition festlegen (unterhalb Trichterausgang)

  //SERVO 2
  //-------------------------
    servo2.attach(datapin2);    // verknüpft den Servomotor mit Pin 17 mit dem Servo-Objekt
    position_S2 = 99;
    servo2.write(position_S2);    // Ausgangsposition festlegen (mittig)
    
    Serial.begin(1200);
}


void loop() {
  
    position_S1 = 121;
    servo1.write(position_S1);    // Position unter dem Lichtsensor
    delay(1000);

    position_S2 = 178;
    servo2.write(position_S2);
    delay(100);

    position_S1 = 151;            // Position über der Öffnung
    servo1.write(position_S1);
    delay(1000);

    position_S1 = 63;             // Servo1 zurück an Ausgangposition
    servo1.write(position_S1);
    delay(1000);
    

}
