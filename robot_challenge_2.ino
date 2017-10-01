/*

*/

//int distance_dangerous = 150; // about 50cm
//int distance_ahead;
const int echopin = 6;
const int trigpin = 7;
const int echopin2=2;
const int trigpin2=3;


long duration;
long durationDown;
long distance;
long distanceDown;
int maximumRange = 200;
int minimumRange = 0;
int maximumRangeDown=15;
int minimumRangeDown=0;

void setup() 
{ 
  //servo.attach(8);  // attaches the servo on pin 8 to the servo object 
  // quadruple half-H bridge SN754410NE
  // always enabled -> 1,2EN & 3,4EN connected to high level 
  // motor 1: pins 9 & 10 (outputs 1A i 2A)
  // motor 2: pins 11 & 12 (outputs 3A i 4A)
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(trigpin2,OUTPUT);
  pinMode(echopin2,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
}

void robot_stop()
{
//  Serial.println("STOP");
  // motor 1 stop
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  // motor 2 stop 
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}

void robot_reverse(){
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  // motor 2 forward
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}
void robot_forward()
{
//  Serial.println("FORWARD");  
  // motor 1 forward
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  // motor 2 forward
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}


void turn_left()
{
//  Serial.println("LEFT");  
  // motor 1 stop
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  // motor 2 forward 
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  delay (400);  //adjust!!!! 
  // motor 2 stop 
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);  
}


void turn_right()
{
//  Serial.println("RIGHT");  
  // motor 1 forward
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  // motor 2 stop 
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  delay (600); //adjust!!!!
  // motor 1 stop 
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);  
}

void loop() 
{
 digitalWrite(trigpin, LOW); //measure ultrasonic sensor up
 delayMicroseconds(2); 

 digitalWrite(trigpin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigpin, LOW);
 duration = pulseIn(echopin, HIGH);
 distance = duration/58.2;

 digitalWrite(trigpin2, LOW); //measure ultrasonic sensor down
 delayMicroseconds(2); 

 digitalWrite(trigpin2, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigpin2, LOW);
 durationDown = pulseIn(echopin2, HIGH);
 distanceDown = durationDown/58.2;
 robot_forward();
 turn_left();
 turn_right();
 if(distanceDown >= maximumRangeDown){
  //out of range
  robot_stop();
  robot_reverse();
  turn_left();
 }
 while (distance >= maximumRange){
 /* Send a negative number to computer and Turn LED ON 
 to indicate "out of range" */
 //Serial.println("-1");
 digitalWrite(LED_BUILTIN, LOW);
 robot_stop();
 turn_left();
  
 }
 /* Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading. */
 //Serial.println(distance);
 digitalWrite(LED_BUILTIN, HIGH);
 robot_forward();
 
 
 
 //Delay 50ms before next reading.
 delay(50);
 
}
