// 03/04/2021 Jason Marshall
const int openSignal = 2; // this is an analog signal from the liftmaster unit set to open
const int stayOpenSignal = 3; // this is an analog signal from the liftmaster unit that will force the gate to stay open
const int openSwitch = 4; // this is an anolog signal from a magnetic switch on the gate that is used to determine if the gate is open or closed position
const int proxSensor = 5; // this is an anolog signal from a PIR sensor mounted on the inside to allow vehicles to leave without a remote
const int gateOpenRelayContact = 6; // used to close an external relay that is connected to the open circuit on the ram
const int gateCloseRelayContact = 7; // used to close an external relay that is connected to the close circuit on the ram
const int lightRelayContact = 8; // the light turns on when the gate is open, opening, or closing
long unsigned startOpenMillis = 0; // counter used to auto close the gate after xx seconds
long unsigned startCounter = 0;
int position = 4;
int forceOpen = 0;
/*
 * 1= opening
 * 2= open
 * 3= closing
 * 4= closed
 */
void setup()
{
  pinMode(gateOpenRelayContact, OUTPUT); // initialize all the pins to default values
  pinMode(gateCloseRelayContact, OUTPUT);
  pinMode(lightRelayContact, OUTPUT);
  pinMode(openSwitch, INPUT);
  pinMode(openSignal, INPUT);
  pinMode(stayOpenSignal, INPUT);
  pinMode(proxSensor, INPUT);
  digitalWrite(gateCloseRelayContact, HIGH);
  digitalWrite(gateOpenRelayContact, HIGH);
  digitalWrite(lightRelayContact, HIGH);
  digitalWrite(openSwitch, LOW);
  position = 4;
  Serial.begin(9600);
}
// returns the value used in 'position' to save the state of the gate
int openGate(){
  Serial.println("Open Gate Started");
  //if (digitalRead(gateCloseRelayContact) == LOW){
    digitalWrite(gateCloseRelayContact, HIGH);
    delay(1000);
  //}
  digitalWrite(gateOpenRelayContact, LOW);
  startOpenMillis = millis(); // begins the counter to auto-close the gate
  startCounter = millis();
  digitalWrite(lightRelayContact, LOW);
  return 1; 
}

int closeGate(){
  Serial.println("Close Gate Started");
  Serial.println(gateCloseRelayContact);
  //if (digitalRead(gateOpenRelayContact == LOW)){
    digitalWrite(gateOpenRelayContact, HIGH);
    delay(500);
  //} 
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

// Determine if gate is fully closed following the close cycle
if (position == 3 && digitalRead(openSwitch) == HIGH){
  Serial.println("openSwitch = " + String(digitalRead(openSwitch)));
  Serial.println("Gate closing cycle complete, marking gate closed");
  delay(3500);
  digitalWrite(gateCloseRelayContact, HIGH);
  position = 4;
  digitalWrite(lightRelayContact, HIGH);
}

// monitor for remote signal
if ((digitalRead(openSignal) == HIGH)) {
  Serial.println("Gate signal received");
  delay(1000);
  if(forceOpen == 1){
    forceOpen = 0;
    position = closeGate();
  } else {
  switch(position) {
    case 1 :
    Serial.println("case 1");
      position = closeGate(); 
      break;
    case 2 :
    Serial.println("case 2");
      position = closeGate(); 
      break;
    case 3 :
    Serial.println("case 3");
      position = openGate(); 
      break;
    case 4 :
    Serial.println("case 4");
      position = openGate(); 
      break;
  };
  }}

// monitor for forced open signal
if ((digitalRead(stayOpenSignal)) == HIGH){
  if (forceOpen == 0){
    forceOpen = 1;
    position = openGate();
  }
  else {
    forceOpen = 0;
  }
}

// Proximity sensor
if (digitalRead(proxSensor) == HIGH && (position == 3 || position == 4)) {
  Serial.println("Prox sensor received, opening gate");
  position = openGate();
  }

// Auto close
if (position == 2 && forceOpen == 0){
  if (millis() - startCounter > 120000){ 
    Serial.println("Auto close time exceeded");
    position = closeGate();
    }
  }
  
// Turn light off
if (digitalRead(lightRelayContact) == HIGH && position == 4){
  digitalWrite(lightRelayContact, HIGH);
  }
if (forceOpen == 1){
  digitalWrite(lightRelayContact, HIGH);  
}
delay(50);
}
