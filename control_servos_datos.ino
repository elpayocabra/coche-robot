#include <SoftwareSerial.h>
#include <Servo.h>

// CODIGO PARA EL BUZZER---------------------------------------------------------
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int tempo = 120;
int buzzer = 4;
int melody[] = {  
  NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16,

  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,//4
  NOTE_E5,4, NOTE_E5,4, NOTE_E5,4, NOTE_F5,-8, NOTE_C5,16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,    
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;
// FIN CODIGO PARA EL BUZZER-----------------------------------------------------

Servo ser_hor, ser_ver;   // cremos los objetos para los servos horizontal y vertical
int servopos_hor = 90;    // posicion inicial del servo horizontal
int servopos_ver = 90;    // posicion inicial del servo vertical


int laser = 2;
int ledBlanco = 3;
int motor = 6;
int TRIG = 7;
int ECHO = 8;
int TRIG2 = 12;
int ECHO2 = 13;
char opcion;

long tiempo;
long distancia;
long tiempo2;
long distancia2;

SoftwareSerial blue(0, 1); //PINES TX Y RX

void setup() {
  blue.begin(9600); //velocidad de comunicación
  ser_hor.attach(5);  // inicializacion de servo conectado al pin 5
  ser_ver.attach(9);  // inicializacion de servo conectado al pin 9

// SETUP PARA EL BUZZER------------------------------------------------
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }
    tone(buzzer, melody[thisNote], noteDuration*0.9);
    delay(noteDuration);
    noTone(buzzer);
// FIN DEL SETUP DEL BUZZER-------------------------------------------
    
  }
  pinMode(laser, OUTPUT);
  pinMode(ledBlanco, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);  
  Serial.begin(9600);
}

void loop() {
  
    if (blue.available() > 0)
    opcion = blue.read();
  switch (opcion)
  {    
      case 'O':
      digitalWrite(laser, LOW);
      digitalWrite(ledBlanco, LOW);
      digitalWrite(motor, LOW);
      break;

      case 'E': 
      digitalWrite(laser, HIGH);
      break;
      
      case 'F':
      digitalWrite(laser, LOW);
      break;

      case 'c': 
      digitalWrite(ledBlanco, HIGH);
      break;

      case 'H':
      digitalWrite(ledBlanco, LOW);
      break;

      case 'M': 
      digitalWrite(motor, HIGH);
      break;

       case 'N':
      digitalWrite(motor, LOW);
      break;
           
  }
  {
    unsigned int servopos = blue.read();
    unsigned int servopos1 = blue.read();
    unsigned int realservo = (servopos1 *256) + servopos;
    Serial.print(realservo);

    if (realservo >= 1000 && realservo <1180){
    int servo1 = realservo;
    servo1 = map(servo1, 1000,1180,0,180);
    ser_hor.write(servo1);
    Serial.print("ser_hor ON");
    delay(10);
    
    }
    
    if (realservo >= 2000 && realservo <2180){
    int servo2 = realservo;
    servo2 = map(servo2, 2000,2180,0,180);
    ser_ver.write(servo2);
    Serial.print("ser_ver ON");
    delay(10);
    }
  }
// ULTRASONIDOS 1  
  digitalWrite(TRIG, 0);
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH);
  tiempo=pulseIn(ECHO, HIGH);
  tiempo = tiempo / 2;
  distancia = int(0.034 * tiempo);
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  blue.println(distancia);
  delay(100); 

// ULTRASONIDOS 2    
  digitalWrite(TRIG2, 0);
  delayMicroseconds(5);
  digitalWrite(TRIG2, HIGH);
  tiempo2=pulseIn(ECHO2, HIGH);
  tiempo2 = tiempo2 / 2;
  distancia2 = int(0.034 * tiempo2);
  Serial.print("Distancia2: ");
  Serial.print(distancia2);
  Serial.println(" cm");
  blue.println(distancia2);
  delay(100);
  
}
