// define pins
const int openSwitch = 4;
const int openSignal = A0;
const int closeSignal = A2;
const int proxSensor = A1;
const int gateOpenRelayContact = 2;
const int gateCloseRelayContact = 3;
String status = "closed";
int debug = 1;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

void setup()
{
  pinMode(gateOpenRelayContact, OUTPUT);
  pinMode(gateCloseRelayContact, OUTPUT);
  pinMode(openSwitch, INPUT);
  pinMode(openSignal, INPUT);
  pinMode(closeSignal, INPUT);
  pinMode(proxSensor, INPUT);
  digitalWrite(gateCloseRelayContact, HIGH);
  digitalWrite(gateOpenRelayContact, HIGH);
  digitalWrite(openSwitch, LOW);
  Serial.begin(9600);
}

void openGate(){
  if (debug = 1){
    Serial.println("Open Gate");
  }
  digitalWrite(gateOpenRelayContact, LOW);
  if (debug = 0){
    //delay(18000); // 18 seconds
    if (currentMillis - previousMillis > 18000 ){
      digitalWrite(gateOpenRelayContact, HIGH);
      status = "open";
      }
    else {
      delay(1000); // 1 second
    }
  }
}
void closeGate(){
  if (debug = 1){
    Serial.println("Close Gate");
  }
  digitalWrite(gateCloseRelayContact, LOW);
  if (debug = 0){
    delay(18000); // 18 seconds
    }
    else {
    delay(1000); // 1 second
  }
  digitalWrite(gateCloseRelayContact, HIGH);
  status = "close";
}
// main loop
void loop(){
if (digitalRead(openSwitch) == LOW){
  status = "open";
  if (debug = 1){
    Serial.println("status = open");
  }
}
// monitor for remote open signal
if (analogRead(openSignal) > 1000) {
  if (debug = 1){
    Serial.println("SignalA0 = " + String(analogRead(openSignal)));
  }
  openGate();
}
// monitor for remote close signal
if (analogRead(closeSignal) > 1000) {
  if (debug = 1){
    Serial.println("Remote close signal recieved");
  }
  closeGate();
}

// If gate is open, delay then close gate
if (status == "open"){  
  if (debug = 1){
    Serial.println("Gate open and will close");
    delay(1000);
  }
  else{
    delay(60000);
  }
 closeGate();
}

// Proximity sensor
 if (analogRead(proxSensor) >1000 && status == "closed" ) {
  openGate();
}

}
