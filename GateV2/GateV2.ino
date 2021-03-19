// need to add a 1K resister from ground to a2, 5v is run through switch 
// then the magnet or push button will change level to high on pin2 

// define pins

//const int BLUE = 3;
//const int GREEN = 5;
//const int RED = 6;
const int gateCloseContact = 9;
const int openSwitch = 2;

void setup()
{
//  pinMode(RED, OUTPUT); // gate moving, not open or closed
//  pinMode(GREEN, OUTPUT); // gate open, waiting to close
//  pinMode(BLUE, OUTPUT); // gate closing contacts in close position
  pinMode(gateCloseContact, OUTPUT); // when high closes gate via powering external relay

  pinMode(openSwitch, INPUT);
//  digitalWrite(RED, LOW);
//  digitalWrite(GREEN, LOW);
//  digitalWrite(BLUE, LOW);
  digitalWrite(gateCloseContact, LOW);
//  Serial.begin(9600);
}

// define variables

// main loop
void loop(){
// If gate is open, delay 120 seconds, then close the opener contact

if (digitalRead(openSwitch) == HIGH){
  //Serial.println(digitalRead(openSwitch));
  //Serial.println("Start of loop\n");
  //digitalWrite(RED, LOW);
  //digitalWrite(BLUE, LOW);
  //digitalWrite(GREEN, HIGH);
  //Serial.println("In if, set green on\n");
  delay(120000);// 2 min
  //delay(1000);
  digitalWrite(gateCloseContact, HIGH);
  //digitalWrite(GREEN, LOW);
  //digitalWrite(BLUE, HIGH);
  delay(1000);// 1 sec
  digitalWrite(gateCloseContact, LOW);
  //digitalWrite(BLUE, LOW);
  //digitalWrite(RED, HIGH);
  delay(15000); // Delay 15 sec to allow gate to close fully
  //digitalWrite(RED, LOW);  
}

}
