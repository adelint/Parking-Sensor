// Servo library
#include <Servo.h>

// Servo
Servo myservo;      

// Time duration until the signal is received back
long duration;  

// Distance to a possible obstacle
float distance;

// Setup function
void setup() {
  // Pins settings
  pinMode(2,OUTPUT);    // Trig from ultrasonic
  pinMode(3,INPUT);     // Echo from ultrasonic
  pinMode(4,OUTPUT);    // Output for servomotor
  pinMode(5,OUTPUT);    // Output for buzzer
  pinMode(6,OUTPUT);    // Pin for blue LED
  pinMode(7,OUTPUT);    // Pin for green LED
  pinMode(8,OUTPUT);    // Pin for red LED
  pinMode(9,INPUT);     // Pin for switch position
  pinMode(10,OUTPUT);   // Pin for indicating system activation: ON/OFF
  pinMode(11,OUTPUT);   // Pin for indicating brake system functionality: active/inactive
  
  // ---- Servo -----
  // Attach servo to pin 4
  myservo.attach(4); 
  
  // Set de servo position to 0 degree
  myservo.write(0);     
  
  // Releasing the brake system
  digitalWrite(11,LOW); 
  
  // Serial communication for serial monitor
  Serial.begin(9600);   
  
  // Communication buzzer->servo
  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
}

// Loop function
void loop() {
  // Reset the trig signal
  digitalWrite(2,LOW);
  delay(2);

  // Start to send ultrasonic signal
  digitalWrite(2,HIGH); 
  delay(10);
  digitalWrite(2,LOW);      

  // Measure time duration between sending and receiving the signal
  duration=pulseIn(3,HIGH); 
  
  // Determine the distance using time duration
  distance = duration/2*0.034;

  // Display the distance 
  Serial.print("Distanta este: "); 
  Serial.print(distance);    
  Serial.println();

  // Turn off the LEDs
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);   

  // Verify if the system is activated
  if(digitalRead(9)==LOW){
    if(myservo.read()==180){
      myservo.write(0);
      digitalWrite(11,LOW);}
      digitalWrite(10,HIGH);
    }else{
      digitalWrite(10,LOW);
      }
      
  // Distance verifying
   if(distance<=70)
  {
    // Case 1
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
    // Case 2
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
    // Case 3
    else
    {
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(5,HIGH);
      delay(800);
      
      // If the distance decreases below 7 and the system is activated, the brake system will stop the wheels 
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
