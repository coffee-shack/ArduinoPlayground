// Smooth RGB mood lamp
// Changes an RGB LED's color smoothly that only turns on
// when it's dark around it.
// Author: Coffee Shack
// Date: 05/24/2014
// Version: 1.0
// ---------------------------------------------------
// The brightness of the leds follows these equations:
// Red = sin(x)
// Green = sin(x + PI/3)
// Blue = sin(x + 2PI/3)
// for x from 0 to PI
// ---------------------------------------------------

float RGB[3];
// int ldrPin = 0;     // LDR in Analog Input 0 to read the ambient light
// int ambientLight;   // variable to store the value of the ambient light
int blueLed   = 11;  // blue LED in Digital Pin 11 (PWM)
int greenLed = 10;  // green LED in Digital Pin 10 (PWM)
int redLed  = 9;   // red LED in Digital Pin 9 (PWM)

//Bluetooth 
byte btdata=0;

void setup(){
  pinMode(redLed,OUTPUT);  // tell arduino it's an output
  pinMode(greenLed,OUTPUT);// tell arduino it's an output
  pinMode(blueLed,OUTPUT); // tell arduino it's an output
 
  // set all the outputs to low
  digitalWrite(redLed,LOW);
  digitalWrite(greenLed,LOW);
  digitalWrite(blueLed,LOW);
  
  // Bluetooth I/O
  Serial.begin(9600); //Default connection rate for Bluetooth module
  
}

void loop() {

  switch (btdata) {
    case 1:
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed,LOW);
      digitalWrite(blueLed,LOW);
      Serial.write(1);
      break;
    case 2:
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed,LOW);
      digitalWrite(blueLed,LOW);
      Serial.write(2);
      break;
    case 3:
      digitalWrite(blueLed, HIGH);
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,LOW);
      Serial.write(3);
//    case 4:
    
      //transition();
  }
}
void serialEvent(){
btdata = Serial.read();
}


void transition(){
  for (float x=0;x<PI;x=x+0.0001){
    RGB[0]=255*abs(sin(x*(180/PI)));           // calculate the brightness for the red led
    RGB[1]=255*abs(sin((x+PI/3)*(180/PI)));    // calculate the brightness for the green led
    RGB[2]=255*abs(sin((x+(2*PI)/3)*(180/PI)));// calculate the brightness for the blue led
    //ambientLight=analogRead(ldrPin); // read an store the ambient light
    //if(ambientLight>600){ // start only if the ambient light is very low
      //  write the brightness on the leds
      analogWrite(redLed,RGB[0]);
      analogWrite(greenLed,RGB[1]);
      analogWrite(blueLed,RGB[2]);
      if(x==1){
        Serial.write(1);
      }
      if(x==2){
        Serial.write(2);
      }
        
      if(btdata != 4){
        Serial.write(5);
        return;
      }
    //}
    //else{
    // digitalWrite(redLed,LOW);
    //  digitalWrite(greenLed,LOW);
    //  digitalWrite(blueLed,LOW);
    //}
    for(int i=0;i<3;i++){
      if(RGB[i]<1){
        delay(100);
      }
      if(RGB[i]<5){
        delay(50);
      }
      if(RGB[i]<10){
        delay(10);
      }
      if(RGB[i]<100){
        delay(5);
      }
    }
    delay(1);
  }
}

