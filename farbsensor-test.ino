// Farbsensor Test

//Verbindung der Farbsensorkontakte mit dem Arduino festlegen
#define s0 8
#define s1 5  // s0, s1 Output-Frequenz regeln
#define s2 6
#define s3 7
#define out 4

int red = 0;
int blue = 0;
int green = 0;

int colorvalue = 0;


void setup() {
  
// Kontakte des Farbsensors werden als Output festgelgt
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);  // Sensor-output als Arduino-Input definieren
 
  digitalWrite(s0, LOW); //Die vier weißen LEDs am Farbsensor sollen leuchten
  digitalWrite(s1, HIGH);
  
  Serial.begin(1200); // Serielle Kommunikation starten

}

void loop() {

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
  delay(500);

}
