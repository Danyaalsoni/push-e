/*

*/

const int echopin = 6;
const int trigpin = 7;
const int echopin2=5;
const int trigpin2=4;
int timeTurning=0;

long duration;
long durationDown;
long distance;
long distanceDown;
int maximumRange = 50;
int minimumRange = 2;
int maximumRangeDown=15;
int minimumRangeDown=0;

void setup() 
{ 
 
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
  pinMode(echopin2,INPUT);
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
  digitalWrite(10, HIGH);
  // motor 2 forward 
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  delay (40);  //adjust!!!! 
  // motor 2 stop 
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);  
}


void turn_right()
{
//  Serial.println("RIGHT");  
  // motor 1 forward
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  // motor 2 stop 
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  delay (10); //adjust!!!!
  // motor 1 stop 
  digitalWrite(11, LOW);
  digitalWrite(12, LOW); 
  timeTurning++; 
}
void robot_reverse(){
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  // motor 2 forward
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}
int checkDist(){
 int dist;
 digitalWrite(trigpin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigpin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigpin, LOW);
 duration = pulseIn(echopin, HIGH);
 dist = duration/58.2;
 return dist;
}
int checkDistDown(){
 int dist;
 digitalWrite(trigpin2, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigpin2, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigpin2, LOW);
 durationDown = pulseIn(echopin2, HIGH);
 dist = durationDown/58.2;
 return dist;
}
void loop() 
{
  distance=checkDist();
  distanceDown=checkDistDown();
  Serial.println(distance);
  //Serial.println(distanceDown);
  int tempDist=4;
  timeTurning=0;

   
 while ((distance >= maximumRange || distance <= minimumRange )&&(distanceDown <=15||distanceDown>=10)){
 //Turn LED ON 
// to indicate "out of range" 

    timeTurning=0;
    distance=checkDist();
    distanceDown=checkDistDown();
    digitalWrite(LED_BUILTIN, LOW);
    robot_forward();
    if((!(distance >= maximumRange || distance <= minimumRange)&&(distanceDown <=15||distanceDown>=10))){
        digitalWrite(LED_BUILTIN, HIGH);
        robot_stop();
//        if(timeTurning>10){
//          //robot_reverse();
//          delayMicroseconds(10);
//          robot_stop();
//        }
        turn_right();
    } 
  
 }
 
 if((!(distance >= maximumRange || distance <= minimumRange))&&(distanceDown <=15||distanceDown>=10)){
        digitalWrite(LED_BUILTIN, HIGH);
        robot_stop();
        turn_right();
 }
 if(distanceDown < 10){
    robot_reverse();
    delay(200);
    robot_stop();
    turn_right();
 }
 
 //Delay 50ms before next reading.
 delay(50);
 
 //Calculate the distance (in cm) based on the speed of sound.
 

//  servo.write(90);   // looks forward
//  delay (200);
//  distance_ahead = analogRead (pinSensor);
//  Serial.println("distance ahead");
//  Serial.println(distance_ahead);
//  delay (1000);
//  if (distance_ahead > distance_dangerous) // bigger distance lesser output from sensor!!!
//  {
//    robot_stop();
//    if (distance_right() > distance_left()) turn_left(); else turn_right();
//  }
//  else robot_forward();
}
