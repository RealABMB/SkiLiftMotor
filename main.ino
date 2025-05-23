const int trigPin1 =10;
const int echoPin1 = 9;
const int trigPin2 = 4;
const int echoPin2 = 2;
const int enA = 5 ;
const int m1 = 7;
const int m2 = 6;

long duration;
int distance;
long duration2;
int distance2;
int ballRolled;
int cartArrive;

//bool sensorOn = true;
//Turn on later
const long motorWaitTime = 15000;

void setup() {
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);
  pinMode(enA, OUTPUT);
  pinMode(m1, OUTPUT);
	pinMode(m2, OUTPUT);

  digitalWrite(m1, LOW);
	digitalWrite(m2, LOW);

  Serial.begin(9600);

}

void loop() {
  //if (sensorOn == true){
    sensorControl();
  //}
}

void motorOn(){
  analogWrite(enA, 200);
  digitalWrite(m1, HIGH);
  delay(7000);
  analogWrite(enA, 140);
  stopSensor();
  
}

void sensorControl(){
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
 
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
 
  duration = pulseIn(echoPin1, HIGH);

  distance = duration * 0.034 / 2;
  
  if (distance > 35 || distance < 2.5){
    ballRolled ++;

    if (ballRolled == 2){
      ballRolled = 0;
      //sensorOn = false;
      Serial.println(distance);
      delay(1000);
      motorOn();
      digitalWrite(trigPin2, LOW);
      digitalWrite(echoPin2, LOW);
      delay(2000);
      //sensorOn = true;
    }
  }  
}

void stopSensor(){
  while (true){
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
  
    duration2 = pulseIn(echoPin2, HIGH);

    distance2 = duration2 * 0.034 / 2;
    Serial.println(distance2);

    if (distance2 > 1 && distance2 < 10){
      cartArrive ++;

      if (cartArrive == 1){
        cartArrive = 0;
        //sensorOn = false; 
        delay(200);
        digitalWrite(m1, LOW);
        digitalWrite(trigPin2, LOW);
        digitalWrite(echoPin2, LOW);
        Serial.println("motor stopped");
        break;
        //sensorOn = true;
      }
  }  
 }
}
