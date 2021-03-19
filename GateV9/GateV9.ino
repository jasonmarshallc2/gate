// 12/13/2020 Jason Marshall
const int openSignal = 2;
const int closeSignal = 3;
const int openSwitch = 4;
const int proxSensor = 5;
const int gateOpenRelayContact = 6;
const int gateCloseRelayContact = 7;
const int lightRelayContact = 8;
long unsigned startOpenMillis = 0;
long unsigned startCounter = 0;
int position = 4;
/*
 * 1= opening
 * 2= open
 * 3= closing
 * 4= closed
 */
void setup()
{
  pinMode(gateOpenRelayContact, OUTPUT);
  pinMode(gateCloseRelayContact, OUTPUT);
  pinMode(lightRelayContact, OUTPUT);
  pinMode(openSwitch, INPUT);
  pinMode(openSignal, INPUT);
  pinMode(closeSignal, INPUT);
  pinMode(proxSensor, INPUT);
  digitalWrite(gateCloseRelayContact, HIGH);
  digitalWrite(gateOpenRelayContact, HIGH);
  digitalWrite(lightRelayContact, HIGH);
  digitalWrite(openSwitch, LOW);
  position = 4;
  Serial.begin(9600);
}

int openGate(){
  Serial.println("Open Gate Started");
  if (digitalRead(gateCloseRelayContact) == LOW){
    digitalWrite(gateCloseRelayContact, HIGH);
  }
  digitalWrite(gateOpenRelayContact, LOW);
  startOpenMillis = millis();
  startCounter = millis();
  digitalWrite(lightRelayContact, LOW);
  return 1; 
}

int closeGate(){
  Serial.println("Close Gate Started");
  Serial.println(gateCloseRelayContact);
  if (digitalRead(gateOpenRelayContact == LOW)){
    digitalWrite(gateOpenRelayContact, HIGH);
  } 
  digitalWrite(gateCloseRelayContact, LOW);
  digitalWrite(lightRelayContact, LOW);
  return 3;
}

// main loop
void loop(){
// determine if gate is fully open
if (position == 1 && (millis() - startOpenMillis > 18000)){
  Serial.println("Open cycle complete, marking gate open");
  digitalWrite(gateOpenRelayContact, HIGH);
  position = 2;
  digitalWrite(lightRelayContact, LOW);
}

// Determine if gate is fully closed
if (position == 3 && digitalRead(openSwitch) == HIGH){
  Serial.println("openSwitch = " + String(digitalRead(openSwitch)));
  Serial.println("Gate closing cycle complete, marking gate closed");
  delay(3500);
  digitalWrite(gateCloseRelayContact, HIGH);
  position = 4;
  digitalWrite(lightRelayContact, HIGH);
}

// monitor for remote open signal
if ((digitalRead(openSignal) == HIGH) && (position == 3 || position == 4)) {
  Serial.println("Gate open signal received");
  position = openGate();
  digitalWrite(openSignal, LOW);
}

// monitor for remote close signal
if (digitalRead(closeSignal) == HIGH && (position == 1 || position == 2)) {
  Serial.println("closeSignal = " + String(digitalRead(closeSignal)));
  Serial.println("position = " + position);
  Serial.println("Remote close signal recieved");
  position = closeGate();
}

// Proximity sensor
if (digitalRead(proxSensor) == HIGH && (position == 3 || position == 4)) {
  Serial.println("Prox sensor received, opening gate");
  position = openGate();
  }

// Auto close
if (position == 2){
  if (millis() - startCounter > 120000){ // change back to 120000 later
    Serial.println("Auto close time exceeded");
    position = closeGate();
    }
  }
// Turn light off
if (digitalRead(lightRelayContact) == HIGH && position == 4){
  digitalWrite(lightRelayContact, HIGH);
  }
}

