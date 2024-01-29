#define CH1 22
#define CH2 24
#define CH3 26

int ch1value, ch2value;
int ch3value;

// Define motor pins
const int frontLeftMotorPin1 = 2;
const int frontLeftMotorPin2 = 3;
const int frontRightMotorPin1 = 4;
const int frontRightMotorPin2 = 5;
const int rearLeftMotorPin1 = 8;
const int rearLeftMotorPin2 = 9;
const int rearRightMotorPin1 = 10;
const int rearRightMotorPin2 = 11;

int enablepinFL=6;
int enablepinFR=7;
int enablepinRL=13;
int enablepinRR=12;

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue)
{
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}


void setup() {
  // Initialize motor pins as outputs


  Serial.begin(115200);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);


  pinMode(frontLeftMotorPin1, OUTPUT);
  pinMode(frontLeftMotorPin2, OUTPUT);
  pinMode(frontRightMotorPin1, OUTPUT);
  pinMode(frontRightMotorPin2, OUTPUT);
  pinMode(rearLeftMotorPin1, OUTPUT);
  pinMode(rearLeftMotorPin2, OUTPUT);
  pinMode(rearRightMotorPin1, OUTPUT);
  pinMode(rearRightMotorPin2, OUTPUT);
  pinMode(enablepinFL, OUTPUT);
  pinMode(enablepinFR, OUTPUT);
  pinMode(enablepinRL, OUTPUT);
  pinMode(enablepinRR, OUTPUT);
}

void leftTurn() {
  // Set motor directions for a left turn
  analogWrite(enablepinFR,abs(80));
  analogWrite(enablepinFL,abs(80));
  analogWrite(enablepinRR,abs(80));
  analogWrite(enablepinRL,abs(80));
  digitalWrite(frontLeftMotorPin1, LOW);
  digitalWrite(frontLeftMotorPin2, LOW);
  digitalWrite(frontRightMotorPin1, LOW);
  digitalWrite(frontRightMotorPin2, HIGH);
  digitalWrite(rearLeftMotorPin1, LOW);
  digitalWrite(rearLeftMotorPin2, LOW);
  digitalWrite(rearRightMotorPin1, LOW);
  digitalWrite(rearRightMotorPin2, HIGH);
}
void rightTurn() {
  // Set motor directions for a right turn
  analogWrite(enablepinFR,abs(80));
  analogWrite(enablepinFL,abs(80));
  analogWrite(enablepinRR,abs(80));
  analogWrite(enablepinRL,abs(80));
  digitalWrite(frontLeftMotorPin1, LOW);
  digitalWrite(frontLeftMotorPin2, HIGH);
  digitalWrite(frontRightMotorPin1, LOW);
  digitalWrite(frontRightMotorPin2, LOW);
  digitalWrite(rearLeftMotorPin1, LOW);
  digitalWrite(rearLeftMotorPin2, HIGH);
  digitalWrite(rearRightMotorPin1,LOW);
  digitalWrite(rearRightMotorPin2,LOW);


}

void moveForward() {
  // Set motor directions for forward motion
  analogWrite(enablepinFR,abs(120));
  analogWrite(enablepinFL,abs(120));
  analogWrite(enablepinRR,abs(120));
  analogWrite(enablepinRL,abs(120));
  digitalWrite(frontLeftMotorPin1, HIGH);
  digitalWrite(frontLeftMotorPin2, LOW);
  digitalWrite(frontRightMotorPin1, HIGH);
  digitalWrite(frontRightMotorPin2, LOW);
  digitalWrite(rearLeftMotorPin1, HIGH);
  digitalWrite(rearLeftMotorPin2, LOW);
  digitalWrite(rearRightMotorPin1, HIGH);
  digitalWrite(rearRightMotorPin2, LOW);
}

void stop_1() {
  // Set motor directions for forward motion
  analogWrite(enablepinFR,abs(0));
  analogWrite(enablepinFL,abs(0));
  analogWrite(enablepinRR,abs(0));
  analogWrite(enablepinRL,abs(0));
//  digitalWrite(frontLeftMotorPin1, HIGH);
//  digitalWrite(frontLeftMotorPin2, LOW);
//  digitalWrite(frontRightMotorPin1, HIGH);
//  digitalWrite(frontRightMotorPin2, LOW);
//  digitalWrite(rearLeftMotorPin1, HIGH);
//  digitalWrite(rearLeftMotorPin2, LOW);
//  digitalWrite(rearRightMotorPin1, HIGH);
//  digitalWrite(rearRightMotorPin2, LOW);
}



void reverse() {
  // Set motor directions for reverse motion
//  analogWrite(enablepinFR,120);
//  analogWrite(enablepinFL,120);
//  analogWrite(enablepinRR,120);
//  analogWrite(enablepinRL,120);
  analogWrite(enablepinFR,abs(80));
  analogWrite(enablepinFL,abs(80));
  analogWrite(enablepinRR,abs(80));
  analogWrite(enablepinRL,abs(80));
  digitalWrite(frontLeftMotorPin1, LOW);
  digitalWrite(frontLeftMotorPin2, HIGH);
  digitalWrite(frontRightMotorPin1, LOW);
  digitalWrite(frontRightMotorPin2, HIGH);
  digitalWrite(rearLeftMotorPin1, LOW);
  digitalWrite(rearLeftMotorPin2, HIGH);
  digitalWrite(rearRightMotorPin1, LOW);
  digitalWrite(rearRightMotorPin2, HIGH);
}

void loop() {

  ch1value = readChannel(CH2, -100, 100, 0);
  ch2value = readChannel(CH1, -100, 100, 0);
  ch3value = readChannel(CH3, -100, 100, 0);

    
  Serial.print("Ch1: ");
  Serial.println(ch1value);
  Serial.print(" Ch2: ");
  Serial.println(ch2value);
  Serial.print(" Ch3: ");
  Serial.println(ch3value);

/*
  if(ch1value>10)
  moveForward();

  else if(ch1value<-10)
  reverse();

  if(ch2value>10)
  rightTurn();

  else if(ch2value<-10)
  leftTurn();
  */

    if (ch2value > 10) {
    rightTurn(); // Right turn command
    } 
  else if (ch2value < -10) {
    leftTurn();  // Left turn command
  }
  // Check for move forward or reverse commands if no turn command detected
  else if (ch1value > 10) {
    moveForward(); // Move forward command
  } else if (ch1value < -10) {
    reverse();     // Reverse command
  }
 if (ch1value <10 && ch1value>-10)
    stop_1();
}
