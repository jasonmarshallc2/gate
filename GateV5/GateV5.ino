// define pins
const int openSwitch = 4;
const int openSignal = A0;
const int proxSensor = A1;
const int gateOpenRelayContact = 2;
const int gateCloseRelayContact = 3;
String status = "closed";

void setup()
{
  pinMode(gateOpenRelayContact, OUTPUT);
  pinMode(gateCloseRelayContact, OUTPUT);
  pinMode(openSwitch, INPUT);
  pinMode(openSignal, INPUT);
  pinMode(proxSensor, INPUT);
  digitalWrite(gateCloseRelayContact, HIGH);
  digitalWrite(gateOpenRelayContact, HIGH);
  digitalWrite(openSwitch, LOW);
  //Serial.begin(9600);
  
}

void openGate(){
  //Serial.println("Open Gate");
  digitalWrite(gateOpenRelayContact, LOW);
  delay(18000); // 18 seconds
  //delay(1000); // 18 seconds
  digitalWrite(gateOpenRelayContact, HIGH);
  status = "open";
}

// main loop
void loop(){
if (digitalRead(openSwitch) == LOW){
  status = "open";
  //Serial.println("status = open");
}
// monitor for remote open signal
if (analogRead(openSignal) > 1000) {
  //Serial.println("SignalA0 = " + String(analogRead(openSignal)));
  openGate();
}

// If gate is open, delay then close gate
if (status == "open"){  
  //Serial.println("Gate open and will close");
  delay(60000);
  //delay(10000);// 1 sec
  digitalWrite(gateCloseRelayContact, LOW); //pin3
  delay(18000); // 18 seconds
  digitalWrite(gateCloseRelayContact, HIGH);
  status = "closed";
  //Serial.println("Gate open process complete");
  
}

// Proximity sensor
 if (analogRead(proxSensor) >1000 && status == "closed" ) {
  openGate();
}

}
