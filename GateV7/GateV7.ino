using namespace std;
const int openSwitch = 4;
const int openSignal = A0;
const int closeSignal = A2;
const int proxSensor = A1;
const int gateOpenRelayContact = 2;
const int gateCloseRelayContact = 3;
String status = "closed"; 
unsigned long gateOpenTime = 0;
unsigned long currentTime = 0;
int debug = 1;
char parm1[10];
string openGate(string arg1);

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

void openGate(string arg1){
  if (debug = 1){
    Serial.println("Open Gate Started");
  }
  digitalWrite(gateOpenRelayContact, LOW);
  //return "opening"; 
}

void closeGate(string arg1){
  digitalWrite(gateCloseRelayContact, LOW);
  arg1 = "closing";
}

// main loop
void loop(){
if (digitalRead(openSwitch) == LOW){
  status = "open";
  if (debug = 1){
    Serial.println("status = open");
    }
  } else {
  status = "closed";
  }

// monitor for remote open signal
if (analogRead(openSignal) > 1000) {
  if (debug = 1){
    Serial.println("SignalA0 = " + String(analogRead(openSignal)));
  }
  gateOpenTime = millis();
  openGate(status);
}

if (status == "opening" && millis() - gateOpenTime >= 18000){
  digitalWrite(gateOpenRelayContact, HIGH);
  status = "open";
  }

// monitor for remote close signal
if (analogRead(closeSignal) > 1000 && status == "open") {
  if (debug = 1){
    Serial.println("Remote close signal recieved");
    }
  closeGate(status);
  }

if (status == "closing" && digitalRead(openSwitch) == HIGH) {
  delay(500); //the magnet switch makes contact just before the gate actually closes, give it time to fully close
  digitalWrite(gateCloseRelayContact, HIGH);
  status = "closed";
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
