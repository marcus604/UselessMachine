#include <Servo.h>

Servo armServo;
Servo doorServo;
Servo flagServo;

int const armPin = 6;
int const doorPin = 10;
int const flagPin = 4;

int const switchPin = 3;

int const DOOR_OPEN = 12;
int const DOOR_OPEN_SLOW = 10;
int const ARM_PRESS = 118;
int const ARM_PRESS_SLOW = 126;

int const DOOR_START = 50;
int const ARM_START = 50;
int const FLAG_START = 50;
int const FLAG_UP = 145;
int angle;  

int numOfFlips;

String previousFlipState;


void setup() {
  Serial.begin(9600);
  printWhole("Powered up!");
  armServo.attach(armPin);
  doorServo.attach(doorPin);
  flagServo.attach(flagPin);
 
  pinMode(switchPin, INPUT);

  resetServos();
  delay(500);
  

  bool switchOn = isSwitchOn();

  //If turned on and switch is already flipped, flip it off and then start sequence
  if(switchOn) {
    basicFlip();
  }

  previousFlipState = "Off";
  
  numOfFlips = 0;
  angle = 0;
}

void printWhole(String s) {
  Serial.println("");
  Serial.print(s);
  Serial.println("");
}

void printStart(String s) {
  Serial.println("");
  Serial.print(s);
}

void printEnd(String s) {
  Serial.print(s);
  Serial.println("");
}

void resetServos() {
  printWhole("Resetting servos");
  armServo.write(ARM_START);
  doorServo.write(DOOR_START);
  flagServo.write(FLAG_START);
}

void turnServo(Servo servo, int amount) {
  printStart("Turning servo: ");
  Serial.print(amount);
  printEnd(" degrees");
  servo.write(amount);
}

// Slowly turn arm servo either from 0 to 68 or 68 to 0
void slowTurnArmServo(Servo servo, int startAngle, int stopAngle, bool fastFinish) {
  printStart("Turning servo from: ");
  Serial.print(startAngle);
  Serial.print(" to ");
  Serial.print(stopAngle);
  printEnd(" degrees");
  if(fastFinish){ //flip4
    if(startAngle < stopAngle){
      int newStopAngle = stopAngle - 24;
      for(angle = startAngle; angle<=newStopAngle; angle+= 1){     
        turnServo(servo, angle); 
        delay(50);                       
      }
      turnServo(servo, stopAngle); 
    } else {
      for(angle = startAngle; angle>=stopAngle; angle-= 1)     // command to move from 180 degrees to 0 degrees 
      {                                
        turnServo(servo, angle);
        delay(50);                       
      }
    }
  } else { //flip3
    if(startAngle < stopAngle){
      for(angle = startAngle; angle<=stopAngle; angle+= 1){     
        turnServo(servo, angle); 
        delay(50);                       
      } 
    } else {
      for(angle = startAngle; angle>=stopAngle; angle-= 1)     // command to move from 180 degrees to 0 degrees 
      {                                
        turnServo(servo, angle);
        delay(50);                       
      }
    }
  }
  
}

// Slowly turn arm servo 
void slowTurnDoorServo(Servo servo, int startAngle, int stopAngle) {
  printStart("Turning servo from: ");
  Serial.print(startAngle);
  Serial.print(" to ");
  Serial.print(stopAngle);
  printEnd(" degrees");
  if(startAngle < stopAngle){
      for(angle = startAngle; angle<=stopAngle; angle+= 1){     
        turnServo(servo, angle); 
        delay(50);                       
      }
      turnServo(servo, stopAngle); 
  } else {
    for(angle = startAngle; angle>=stopAngle; angle-= 1)     // command to move from 180 degrees to 0 degrees 
    {                                
      turnServo(servo, angle);
      delay(50);                       
    }
  }
}

// Slowly turn arm servo 
void slowTurnFlagServo(Servo servo, int startAngle, int stopAngle) {
  printStart("Turning servo from: ");
  Serial.print(startAngle);
  Serial.print(" to ");
  Serial.print(stopAngle);
  printEnd(" degrees");
  if(startAngle < stopAngle){
      for(angle = startAngle; angle<=stopAngle; angle+= 5){     
        turnServo(servo, angle); 
        delay(50);                       
      }
      turnServo(servo, stopAngle); 
  } else {
    for(angle = startAngle; angle>=stopAngle; angle-= 5)     // command to move from 180 degrees to 0 degrees 
    {                                
      turnServo(servo, angle);
      delay(50);                       
    }
  }
}


void loop() {
  //Serial.println("");
  //Serial.print("Number of flips: ");
  //Serial.print(numOfFlips);
  bool switchOn = isSwitchOn();
  
  if(switchOn)
  {
    switch (numOfFlips) {
      
      case 1:
        printWhole("Flip case 1");    
        basicFlip();
        break;
      case 2:    
        printWhole("Flip case 2"); 
        basicFlip();
        break;
      case 3:    
        printWhole("Flip case 3"); 
        flip2();
        break;
      case 4:
        printWhole("Flip case 4");    
        flip4();
        break;
      case 5:    
        printWhole("Flip case 5"); 
        flip5();
        break;
      case 6:    
        printWhole("Flip case 6"); 
        flip6();
        break;
      case 7:
        printWhole("Flip case 7");    
        flip7();
        break;
      case 8:    
        printWhole("Flip case 8"); 
        flip8();
        break;
      case 9:    
        printWhole("Flip case 9"); 
        flip9();
        break;
      case 10:    
        printWhole("Flip case 11"); 
        flip10();
        numOfFlips = 0;
        delay(1000);
        break;
      default:
        break;
    }
  }
  delay(1000);
}

//Case 1 & 2
//Open door and flip switch
void basicFlip() {
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  turnServo(armServo, ARM_PRESS);
  delay(300);
  turnServo(armServo, ARM_START);
  delay(100);
  turnServo(doorServo, DOOR_START);
}

void flip2() {
  turnServo(doorServo, DOOR_OPEN);
  delay(2000);
  turnServo(armServo, ARM_PRESS);
  delay(1000);
  turnServo(armServo, ARM_START);
  delay(300);
  turnServo(doorServo, DOOR_START);
}


//broken
void flip3() {
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  slowTurnArmServo(armServo, ARM_START, ARM_PRESS_SLOW, false);
  delay(2000);
  slowTurnArmServo(armServo, ARM_PRESS_SLOW, ARM_START, false);
  delay(300);
  turnServo(doorServo, DOOR_START);
}

void flip4() {
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  slowTurnArmServo(armServo, ARM_START, ARM_PRESS_SLOW, true);
  delay(2000);
  slowTurnArmServo(armServo, ARM_PRESS_SLOW, ARM_START, true);
  delay(300);
  turnServo(doorServo, DOOR_START);
}

void flip5() {
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  int newAngle = ARM_PRESS - 24;
  turnServo(armServo, newAngle);
  delay(4000);
  turnServo(armServo, ARM_PRESS_SLOW);
  delay(100);
  turnServo(armServo, newAngle);
  delay(2000);
  turnServo(armServo, ARM_START);
  delay(300);
  turnServo(doorServo, DOOR_START);
}

void flip6() {
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  int newAngle = ARM_PRESS - 24;
  turnServo(armServo, newAngle);
  delay(3000);
  turnServo(armServo, ARM_PRESS_SLOW);
  delay(3000);
  slowTurnArmServo(armServo, ARM_PRESS_SLOW, ARM_START, false);
  delay(300);
  turnServo(doorServo, DOOR_START);
}

void flip7() {
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  turnServo(doorServo, DOOR_START);
  delay(100);
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  turnServo(doorServo, DOOR_START);
  delay(100);
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  turnServo(doorServo, DOOR_START);
  delay(1000);
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  turnServo(doorServo, DOOR_START);
  delay(100);
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  turnServo(doorServo, DOOR_START);
  delay(100);
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  turnServo(doorServo, DOOR_START);
  delay(1000);
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  turnServo(armServo, ARM_PRESS);
  delay(300);
  turnServo(armServo, ARM_START);
  delay(100);
  turnServo(doorServo, DOOR_START);
}

void flip8() {
  slowTurnDoorServo(doorServo, DOOR_START, DOOR_OPEN_SLOW);
  delay(300);
  turnServo(armServo, ARM_PRESS);
  delay(300);
  turnServo(armServo, ARM_START);
  delay(100);
  slowTurnDoorServo(doorServo, DOOR_OPEN_SLOW, DOOR_START);
}

void flip9() {
  slowTurnDoorServo(doorServo, DOOR_START, DOOR_OPEN_SLOW);
  delay(300);
  int newAngle = ARM_PRESS - 24;
  turnServo(armServo, newAngle);
  delay(300);
  turnServo(armServo, ARM_START);
  delay(300);
  turnServo(armServo, newAngle);
  delay(300);
  turnServo(armServo, ARM_START);
  delay(300);
  turnServo(armServo, newAngle);
  delay(300);
  turnServo(armServo, ARM_START);
  delay(300);
  turnServo(armServo, ARM_PRESS);
  delay(3000);
  slowTurnArmServo(armServo, ARM_PRESS, ARM_START, true);
  delay(100);
  slowTurnDoorServo(doorServo, DOOR_OPEN_SLOW, DOOR_START);
}

void flip10() {
  turnServo(doorServo, DOOR_OPEN);
  delay(100);
  waveFlag();
  turnServo(doorServo, DOOR_START);
  delay(3000);
  basicFlip();
}

//Case 9
//Open door
//Turn flag servo back and forth
void waveFlag() {
  slowTurnFlagServo(flagServo, FLAG_START, FLAG_UP);
  delay(2000);
  int waveAngle = 110;
  turnServo(flagServo, waveAngle);
  delay(200);
  turnServo(flagServo, FLAG_UP);
  delay(200);
  turnServo(flagServo, waveAngle);
  delay(200);
  turnServo(flagServo, FLAG_UP);
  delay(200);
  turnServo(flagServo, waveAngle);
  delay(200);
  turnServo(flagServo, FLAG_UP);
  delay(200);
  slowTurnFlagServo(flagServo, FLAG_UP, FLAG_START);
  delay(500);
}

bool isSwitchOn() {

  int switchVal = digitalRead(switchPin);
  
  if(switchVal == HIGH) { //Flipped on
    if(previousFlipState == "On") {
      return true;
    }
    previousFlipState = "On";
    numOfFlips += 1;
    printStart("Switch flipped on ");
    Serial.print(numOfFlips);
    printEnd(" times");
    return true;
  } else {   // LOW
    if(previousFlipState == "Off") {
      return false;
    }
    previousFlipState = "Off";
    return false;
  }
}



 
 
  
