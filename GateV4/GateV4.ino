// define pins
const int openSwitch = 6;
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
  digitalWrite(gateCloseRelayContact, LOW);
  digitalWrite(gateOpenRelayContact, LOW);
  //Serial.begin(9600);
  
}

void openGate(){
  digitalWrite(gateOpenRelayContact, HIGH);
  delay(18000); // 18 seconds
  digitalWrite(gateOpenRelayContact, LOW);
  status = "open";
}

// main loop
void loop(){
if (digitalRead(openSwitch) == HIGH){
  status = "open";
}
// monitor for remote open signal
if (analogRead(openSignal) > 1000) {
  //Serial.println("SignalA0 = " + String(analogRead(openSignal)));
  openGate();
}

// If gate is open, delay then close gate
if (digitalRead(openSwitch) == HIGH){  //pin6
  //Serial.println("Gate open switch is high");
  delay(60000);// 1 min allow the gate to fully open if in the middle of the cycle
  //delay(1000);// 1 sec
  digitalWrite(gateCloseRelayContact, HIGH); //pin3
  delay(18000); // 18 seconds
  digitalWrite(gateCloseRelayContact, LOW);
  status = "closed";
}

// Proximity sensor
 if (analogRead(proxSensor) >1000 && status == "closed" ) {
  openGate();
}

}
