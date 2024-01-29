#define CH1 5
#define CH2 3
#define CH5 10

int motor1pin1=22;
int motor1pin2=24;

int motor2pin1=26;
int motor2pin2=28;
int enablepin12=9;
int enablepin34=6;

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Red the channel and return a boolean value
bool redSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}


void setup(){
  Serial.begin(9600);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH5, INPUT);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(enablepin12, OUTPUT);
  pinMode(enablepin34, OUTPUT);
}

int ch1value, ch2value;
bool ch5value;


void forward(){
//  analogWrite(enablepin12,ch1value);
//  analogWrite(enablepin34,ch1value);
  analogWrite(enablepin12,180);
  analogWrite(enablepin34,180);
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

}

void backward(){
       analogWrite(enablepin12,120);
       analogWrite(enablepin34,120);
       digitalWrite(motor1pin1, LOW);
       digitalWrite(motor1pin2, LOW);
       digitalWrite(motor2pin1,  LOW);
       digitalWrite(motor2pin2, LOW);

}

void rightturn()
{
  analogWrite(enablepin12,120);
  analogWrite(enablepin34,120);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}
void leftturn()
{

  analogWrite(enablepin12,120);
  analogWrite(enablepin34,120);
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

}

void stop_1() {
  // Set motor directions for forward motion
   analogWrite(enablepin12,abs(0));
  analogWrite(enablepin34,abs(0));
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}


void loop() {
  ch1value = readChannel(CH1, -100, 100, 0);
  ch2value = readChannel(CH2, -100, 100, 0);
  ch5value = redSwitch(CH5, false);

    
  Serial.print("Ch1: ");
  Serial.println(ch1value);
  Serial.print(" Ch2: ");
  Serial.println(ch2value);
    Serial.print(" Ch5: ");
  Serial.println(ch5value);

//if(ch1value>-5 && ch1value<5)
// ch1value = 0;
//
//if(ch2value>-5 && ch2value<5)
// ch2value = 0;
  

    if(ch2value>5)
  rightturn();

  else if(ch2value<-5)
  leftturn();

   else if(ch1value>5)
  forward();

  else if(ch1value<-5)
  backward();



}
