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
  
  //FARBSENSOR
  //-------------------------
  //Verbindung der Farbsensorkontakte mit dem Teensy festlegen
    #define s0 B2
    #define s1 B1      // s0, s1 Output-Frequenz regeln
    #define s2 F1
    #define s3 F4
    #define OE B0
    #define out F0
    
    byte red = 0;
    byte green = 0;
    byte blue = 0;
    
    int colorvalue = 0;
    
  // Ein Array von 6 Bytes für jede Farbe vordefinieren
    byte red_array[6]   = {0,0,0,0,0,0};
    byte green_array[6] = {0,0,0,0,0,0};
    byte blue_array[6] = {0,0,0,0,0,0};

    int count = 0;    // gibt die Stelle an, an welcher ich mich im Array befinde
    
    long color_code[6] = {0,0,0,0,0,0};    // speichert spÃ¤ter die endgültigen Farbcodes

    int diff = 0.1;   // zu beachtender Prozentsatz beim Vergleichen
    
  //RGB - HSL
  //-------------------------
    float hsv;
    float col[3];
    float hue = 0.0;
    double hsl[3];
    
    double calculation = hsl[0];
    
    
void setup() {
  
    Serial.begin(1200);
  
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
  
  //RGB - HSL
  //-------------------------
  rgbToHsl(red,green,blue,hsl);
  Serial.println(hsl[0]);
  Serial.println(hsl[1]);
  Serial.println(hsl[2]);
}


void loop() {

    position_S1 = 121;
    servo1.write(position_S1); // Position unter dem Lichtsensor
    delay(2000);

    initialize_color();

    position_S1 = 151;       // Position Ã¼ber der Ãffnung
    servo1.write(position_S1);
    delay(2000);

    position_S1 = 63;       // Servo1 zurÃ¼ck an Ausgangposition
    servo1.write(position_S1);
    delay(2000);

}


void initialize_color() {
   
   // Rote Lichtwerte
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
    red = pulseIn(out, HIGH);  // Output-frequenz lesen
  
    Serial.print("R= ");
    Serial.print(red);
    Serial.print("  ");
    delay(500);

  
   // Grüne Lichtwerte
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
    green = pulseIn(out, HIGH);
    
    Serial.print("G= ");
    Serial.print(green);
    Serial.print("  ");
    delay(500);
  
    
   // Blaue Lichtwerte
    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);
    blue = pulseIn(out, HIGH);    
    
    Serial.print("B= ");
    Serial.print(blue);
    Serial.print("\n");
        
    delay(2000);
    
    
    rgbToHsl(byte red, byte green, byte blue, double hsl[])  // RGB-Werte nach HSL umrechnen


    if (count == 0) {
			red_array[0] = red;
			green_array[0] = green;
			blue_array[0] = blue;
			color_code[0] = calculation;
			count = 1;
		}

    else {
            switch(count) {
    
            case 1:
                 if ((calculation < (1 + diff) * color_code[0]) || (calculation > (1 - diff) * color_code[0])) {
        	      count = 1;
        	      }
        	 else {
         	      position_S2 = 26;
                      servo2.write(position_S2);
                      color_code[1] = calculation;
            	      count = 2;
            	      }
                 break;
        
        
            case 2:
                 if () {
                      count = 2;
                      }
                 else {
                      count = 3;
                      }
                 break;
                 
                 
            case 3:
                 if () {
                      count = 2;
                 }
                 else {
                      count = 3;
                 }
                 break;
                 
                 
            case 4:
                 if () {
                      count = 2;
                 }
                 else {
                      count = 3;
                 }
                 break;
                 
    
            case 5:
                 if () {
                      count = 2;
                 }
                 else {
                      count = 3;
                 }
                 break;
                 
                 
            default:
                 
        }
  }


  //RGB Farben nach HSL-Code umrechnen
  //-------------------------
  // Source: https://github.com/ratkins/RGBConverter

void rgbToHsl(byte red, byte green, byte blue, double hsl[]) { 
    
    double rd = (double) red/255;
    double gd = (double) green/255;
    double bd = (double) blue/255;
    double max = threeway_max(rd, gd, bd);
    double min = threeway_min(rd, gd, bd);
    double h, s, l = (max + min) / 2;
    
    if (max == min) {
        h = s = 0; // achromatic
    } else {
        double d = max - min;
        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
        if (max == rd) {
            h = (gd - bd) / d + (gd < bd ? 6 : 0);
        } else if (max == gd) {
            h = (bd - rd) / d + 2;
        } else if (max == bd) {
            h = (rd - gd) / d + 4;
        }
        h /= 6;
    }
    hsl[0] = h;
    hsl[1] = s;
    hsl[2] = l;
}

double threeway_max(double a, double b, double c) {
    return max(a, max(b, c));
}

double threeway_min(double a, double b, double c) {
    return min(a, min(b, c));
}

//