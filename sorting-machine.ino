#include "Servo.h"                // FISRO: only blocks are indented
                                    // FISRO: right indent after { left indent after }

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

//FARBSENSOR
//-------------------------
//Verbindung der Farbsensorkontakte mit dem Teensy festlegen
#define s0 2
#define s1 1      // s0, s1 Output-Frequenz regeln
#define s2 20
#define s3 19
#define OE 0
#define out 21

// Ein Array von 6 Bytes für jede Farbe vordefinieren
byte red_array[6]   = {0,0,0,0,0,0};  
byte green_array[6] = {0,0,0,0,0,0};
byte blue_array[6]  = {0,0,0,0,0,0};

// FISRO: number or stored colors
int colorCount = 0;    

// FISRO: the threshold a color will be seen as "new"
#define THRESHOLD 10

// FISRO: define the positions where the servo needs to turn for the different holes
byte holes[7] = {178,151,125,99,73,49,26};

//RGB - HSL
//-------------------------
float hsv;
float col[3];
float hue = 0.0;
double hsl[3];

double calculation = hsl[0];

int minimum = 0;

    
void setup() {
 
  Serial.begin(115200);
  
  //SERVO 1
  //-------------------------
  servo1.attach(datapin1);    // verknÃ¼pft den Servomotor mit Pin 3 mit dem Servo-Objekt
  position_S1 = 63;
  servo1.write(position_S1);    // Ausgangsposition festlegen (unterhalb Trichterausgang)
  
  //SERVO 2
  //-------------------------
  servo2.attach(datapin2);    // verknÃ¼pft den Servomotor mit Pin 17 mit dem Servo-Objekt
  position_S2 = 26;
  servo2.write(position_S2);    // Ausgangsposition festlegen (mittig)
  
  //FARBSENSOR
  //-------------------------
  // Kontakte des Farbsensors werden als Output festgelgt
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);  // Sensor-output als Arduino-Input definieren
  
  digitalWrite(s0, HIGH); //Die vier weiÃen LEDs am Farbsensor sollen leuchten
  digitalWrite(s1, HIGH);
}


void loop() {
    position_S1 = 121;
    servo1.write(position_S1); // Position unter dem Lichtsensor
    delay(2000);

    byte position = getColorPosition();
    // FISRO: make the servo turn to the position of holes[position]
    servo2.write(holes[position]);
    delay(1000);

    position_S1 = 151;       // Position Ã¼ber der Ãffnung
    servo1.write(position_S1);
    delay(2000);

    position_S1 = 63;       // Servo1 zurÃ¼ck an Ausgangposition
    servo1.write(position_S1);
    delay(2000);

}


boolean getColorPosition() {
  // FISRO: variable to store the actual color reading
  // FISRO: these do not need to be global as they are only used inside *this* function
  byte red   = 0;
  byte green = 0;
  byte blue  = 0;
   
  // FISRO: array to store the difference with the read values
  // FISRO: this does not need to be global as it is only used inside *this* function
  long delta[6] = {0,0,0,0,0,0};    

  // FISRO: read RGB values from the sensor
  // Rote Lichtwerte
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  red = pulseIn(out, HIGH);  // Output-frequenz lesen
  delay(500);
  
  // Grüne Lichtwerte
  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH);
  green = pulseIn(out, HIGH);
  delay(500);
  
  
  // Blaue Lichtwerte
  digitalWrite(s2,LOW);
  digitalWrite(s3,HIGH);
  blue = pulseIn(out, HIGH);    
  delay(500);
  
  Serial.println("R= "+(String)red+" G= "+(String)green+" B= "+(String)blue);

  // in case we have not yet detected a color, the values
  // we have can be taken as first detected color without 
  // any further calculations
  if (colorCount == 0) {
    Serial.println("First color found!");
    red_array[0]   = red;
    green_array[0] = green;
    blue_array[0]  = blue;
    // set the nomber of detected colors
    colorCount = 1;
    // this M&M's should go to the first hole
    return 0;
  }
  // in case we at least on detected color
  else {
      // calculate the "difference" to the stored colors
      for(int i=0; i<colorCount; i++)
      {
        delta[i] = abs(red_array[i]-red)+
                   abs(green_array[i]-green)+
                   abs(blue_array[i]-blue);
        Serial.println("Delta "+(String)i+" = "+(String)delta[i]);
      }

      // we want to find the closest color, compared to the above read values
      // so we need to search for the smalest value:
      // we know that we have at least one color, so let's suppose the first on
      // is the smallest and check if there is no smaller later in the array
      int posmin = 0;
      for(int i=1; i<colorCount; i++)
      {
        if(delta[i]<delta[posmin])
        {
          posmin=i;
        }
      }
      // know "posmin" holds the index of the smallest value of the array "color_code"

      // we have now two cases: 
      // 1) the read values are a *new* color
      // 2) we have detected 6 colors, so our array is full >> M&M's go to "trash" hole
      // 3) the read values are close enough to an exsting color
      if(delta[posmin]<=THRESHOLD) 
      {
        Serial.println("Found color "+(String)posmin);
        // existing color
        return posmin;
      }
      else if(colorCount>=6) // should never be >6, but let's be safe
      {
        Serial.println("New color, but array is full!");
        return 6;       // hole a index #6 is thge trash, #0 to #5 are the 6 colors.
      }
      else
      {
        Serial.println("New color!");
        // new color to be stored in the array
        red_array[colorCount]   = red;
        green_array[colorCount] = green;
        blue_array[colorCount]  = blue;
        // increment the number of detected colors
        colorCount = colorCount + 1;
        // where the M&M's should go to = the last inserted color position
        return colorCount-1;
      }
  }
  

}
