//HEAVILY COMMENTED 
//WORKING CODE
//FOR DC MOTOR AND BLUETOOTH

//note:code is messy and some of the code served no purpose,, still works tho

//References from
//https://www.youtube.com/watch?v=uT8-HPMS1cU&ab_channel=TechatHome
//&
//https://www.youtube.com/watch?v=qaFMSq-YNkg&ab_channel=EnjoyMechatronics
//&
//https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
//https://arduino.stackexchange.com/questions/35873/whats-the-difference-between-analogwrite-and-digitalwrite
//https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/
//https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
//https://components101.com/modules/l293n-motor-driver-module

//for the BLUETOOTH CONTROLLER,, download this APK(ANDROID ONLY)(KINDA SHADY)
//https://drive.google.com/file/d/1WDyfUH6FnJeDbSP0XKtv6eiSfCAfAm4r/view?usp=drive_link
//watch this vid to go with it
//https://www.youtube.com/watch?v=uT8-HPMS1cU&ab_channel=TechatHome

//IIRC,, the motor were wired like the "enjoy mechanics" tutorial,, so keep that in mind when wiring and testing

  /* this entire block was a copy and paste error but it was kinda useful so im keeping it for the time being
  cessfu
  cessfu
  cessfu

  . — Today at 17:18
  https://drive.google.com/file/d/1hS4aA56TgmIO72uycHfuEImfgF0eGGRN/view
  Google Docs
  nextprototypes-btserialcontroller-8-18179476-a2017bffc086c716ee072e...
  https://www.youtube.com/watch?v=uT8-HPMS1cU
  YouTube
  Tech at Home
  HC-05 Bluetooth Module with Arduino | Blinking LED with Phone [Code...
  Image
  . — Today at 18:30
  #define in1 5 //L298n Motor Driver pins.
  #define in2 6
  #define in3 10
  #define in4 11
  //#define LED 13//serves no purpose
  int command; //Int to store app command state.
  Expand
  code.txt
  4 KB
  ﻿
  */

int motorSpeedPinR = 5;
int motorR1 = 6;
int motorR2 = 7;

//Motor Left Pins
int motorL2= 8;
int motorL1 = 9;
int motorSpeedPinL = 10;

  //#define LED 13//serves no purpose,,we didn't use an LED in our testing


  //phone----->BTcontroller------>ardy----->command  (dont quote me on this,, just refernece)
  
  char command; //this variable holds the value given by the bluetooth controller//Int to store app command state.
  int Speed = 204; //should probably get this var working if we want variable speeds //range is 0 - 255.
  int num;
  //rest of these vars are unknown purpose
  int Speedsec;
  int buttonState = 0;
  int lastButtonState = 0;
  int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
  int brakeTime = 45;
  int brkonoff = 1; //1 for the electronic braking system, 0 for normal.

  void setup() {
    pinMode(motorSpeedPinR , OUTPUT);
    pinMode(motorSpeedPinL , OUTPUT);
    analogWrite(motorSpeedPinR , 255);
    analogWrite(motorSpeedPinL , 255);
    pinMode(motorR1 , OUTPUT);
    pinMode(motorL1 , OUTPUT);
    pinMode(motorR2 , OUTPUT);
    pinMode(motorL2 , OUTPUT);
    
    Serial.begin(9600);
  }
  
  void loop() {
    if (Serial.available()) {//if the thingymabob (either BTmodule or ardy IDK) is reading something (if its reading, its greater than zero)
      command = Serial.read();//serial.read takes input given from the bluetooth controller and assiges command with the taken value
      Serial.println(command);//print command(what just came from the BTcontroller) to the serial monitor(cntrl-shft-m),, also adds new line
      //Stop(); //Initialize with motors stoped.

      switch (command) {//basic switch that tells ardy what to do with command that it just recieved
        case '4':
          Serial.println("Called");
          forward();
          break;
        case '6':
          back();
          break;
        //(all cases(besides break) are random and dont do anthing... plz fix)
        case '0': 
          Stop(); 
          break;
        case'8': 
          right();
          break;
        case '7':
          left(); 
          break; 
        
        /*default://switch is probably broken if this ever runs,, make sure the cases work properly
          Serial.println("Nothing is being sent");
          delay(2000);
          break;*/
      }//========end of switch=========
    }//==========end of if statemnt========
  }//=======end of master loop=========
  
  //--------method / function definitions--------------
  void forward() {
    //MOTOR Right speed:100
    digitalWrite(motorR1 , HIGH);
    digitalWrite(motorL1,HIGH);
    digitalWrite(motorR2 , LOW);
  
  //MOTOR Left speed:100
    
    digitalWrite(motorL2,LOW);

    Serial.println("we called forward");
  }
  
  //------------the rest of these funcitons are untested
  void back() {
  
   //MOTOR Right speed:100
    digitalWrite(motorR1 , LOW);
    digitalWrite(motorR2 , HIGH);
  
  //MOTOR Left speed:100
    digitalWrite(motorL1,LOW);
    digitalWrite(motorL2,HIGH);

    Serial.println("we called backward");
  }
  void right()
  {
       //MOTOR Right speed:100
    digitalWrite(motorR1 , LOW);
    digitalWrite(motorR2 , LOW);
  
  //MOTOR Left speed:100
    digitalWrite(motorL1,HIGH);
    digitalWrite(motorL2,LOW);

    Serial.println("we called right");

  }
  void left()
  {
        //MOTOR Right speed:100
    digitalWrite(motorR1 , HIGH);
    digitalWrite(motorR2 , LOW);
  
  //MOTOR Left speed:100
    digitalWrite(motorL1,LOW);
    digitalWrite(motorL2,LOW);

    Serial.println("we called left");
  }
  void Stop() {
      
    digitalWrite(motorR1 , LOW);
    digitalWrite(motorR2 , LOW);
  
  
    digitalWrite(motorL1,LOW);
    digitalWrite(motorL2,LOW);

    Serial.println("we called stop");
  
  }