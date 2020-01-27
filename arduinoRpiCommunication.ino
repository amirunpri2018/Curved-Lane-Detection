
int myPins[6] = {5, 7, 8, 9, 11,6};      // MOTOR PIN NUMBERS

char number[50];
char c;
int state = 0;
String myStringRec;
int stringCounter = 0;
bool stringCounterStart = false;
String myRevivedString;
int stringLength = 9;

int recSpeedLeft = 0;
int recSpeedRight= 0;


void setup() {
 for (int i = 0; i < 6; i++) {
    pinMode(myPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
receiveData();
moveRobot(recSpeedLeft,recSpeedRight);
}



void moveRobot(int myLeftSpeed, int myRightSpeed)
{
  if (myLeftSpeed <= 0) {
    digitalWrite(myPins[1], 0);
    digitalWrite(myPins[2], 1);
  }
  else {
    digitalWrite(myPins[1], 1);
    digitalWrite(myPins[2], 0);
  }

  if (myRightSpeed <= 0) {
    digitalWrite(myPins[3], 0);
    digitalWrite(myPins[4], 1);
  }
  else {
    digitalWrite(myPins[3], 1);
    digitalWrite(myPins[4], 0);
  }

  analogWrite(myPins[0], abs(myLeftSpeed));
  analogWrite(myPins[5], abs(myRightSpeed));
}


void receiveData() {
  int i = 0;
  while (Serial.available()) {
   char c = Serial.read();
  
    if (c == '$') {
      stringCounterStart = true;
    }
    if (stringCounterStart == true )
    {
      if (stringCounter < stringLength)
      {
        myRevivedString = String(myRevivedString + c);
        stringCounter++;
      }
      if (stringCounter >= stringLength) {
        stringCounter = 0; stringCounterStart = false;
        recSpeedLeft = myRevivedString.substring(1, 5).toInt();
        recSpeedRight = myRevivedString.substring(5, 9).toInt();
        Serial.print(recSpeedLeft);
        Serial.print(" ");
        Serial.println(recSpeedRight);
        myRevivedString = "";
      }
    }
  }
}
