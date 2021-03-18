#include <Servo.h>   //Biblioteca servo-motor
Servo myservo;      // Servo motor

long duration;  
float distance;

void setup() {
  //Pini
  pinMode(2,OUTPUT);    //Trig pin de la ultrasonic
  pinMode(3,INPUT);     //Echo pin de la ultrasonic
  pinMode(4,OUTPUT);    //Setez pin 4 iesire pentru servo-motor
  pinMode(5,OUTPUT);    //Setez pin 5 iesire pentru buzzer
  pinMode(6,OUTPUT);    //Pinul pentru LED-ul albastru
  pinMode(7,OUTPUT);    //Pinul pentru LED-ul verde
  pinMode(8,OUTPUT);    //Pinul pentru LED-ul rosu
  pinMode(9,INPUT);     //Pin pozitie switch
  pinMode(10,OUTPUT);   //Pin indicare mod de functionare sistem activ/inactiv
  pinMode(11,OUTPUT);   //Indicare stare frane: liber/blocat
  //Servo
  myservo.attach(4);    //Atasez pinul 4 pentru servo-motor
  myservo.write(0);     //Setez motorul in pozitie de 0 grade
  digitalWrite(11,LOW);
  //Comunicarea seriala pt Serial Monitor
  Serial.begin(9600);   
  //Comunicare buzzer+servo
  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
}


void loop() {
  digitalWrite(2,LOW);
  delay(2);                 //trig trebe sa fie LOW cand rulez prima data

  digitalWrite(2,HIGH);     //pornesc trig (incep sa trimit ultrasonice)
  delay(10);                //Astept 10 milisecunde
  digitalWrite(2,LOW);      //Opresc trig

  duration=pulseIn(3,HIGH); //Masor durata pana ajunge semnalul inapoi
  distance = duration/2*0.034;//calculez distanta

  Serial.print("Distanta este: "); 
  Serial.print(distance);    //Afisarea distantei in Serial Monitor
  Serial.println();

  digitalWrite(6,LOW);      //
  digitalWrite(7,LOW);      //   Opresc LED-urile
  digitalWrite(8,LOW);      //

  //Resetare pozitie servo-motor + led indicator
  if(digitalRead(9)==LOW){
    if(myservo.read()==180){
      myservo.write(0);
      digitalWrite(11,LOW);}
      digitalWrite(10,HIGH);
    }else{
      digitalWrite(10,LOW);
      }
      
  //Verificare distanta
   if(distance<=70)
  {
    //Cazul 1
    if((distance<70)&&(distance>45))
    {
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(5,HIGH);
      delay(300);
      digitalWrite(5,LOW);
      delay(500);
    }
    //Cazul 2
    else if((distance<=45)&&(distance>10))
    {
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(5,HIGH);
      delay(200);
      digitalWrite(5,LOW);
      delay(100);
      digitalWrite(5,HIGH);
      delay(200);
      digitalWrite(5,LOW);
      delay(300);
    }
    //Cazul 3
    else
    {
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(5,HIGH);
      delay(800);
      
      //Cand distanta scade sub 7 cm sistemul de blocare se activeaza
      if((distance<7)&&(digitalRead(9)==HIGH)){
         myservo.write(180);
         digitalWrite(11,HIGH);
         digitalWrite(5,LOW);
         delay(100);
        }
        digitalWrite(5,LOW);
        delay(100);
    }
   }
}
