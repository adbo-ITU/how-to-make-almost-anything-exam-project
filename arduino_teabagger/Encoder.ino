// display setup 
// https://docs.arduino.cc/learn/electronics/lcd-displays/

#define pinA 11
#define pinB 12
#define buttonpin 13

const int maxMin = 99;
int minutes = 0;
int aState;
int aLastState;
bool buttonState;
bool buttonLastState;
int globalState;

void setup() { 
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(buttonpin, INPUT);
   
  Serial.begin(9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(pinA);
  buttonLastState = digitalRead(buttonpin);
  globalState = 1;
} 

void loop() {
  if (globalState == 0){ // Select temp
  

  }
  if (globalState == 1){ // Select time
    aState = 0;

    aState = digitalRead(pinA); // Reads the "current" state of the outputA
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    if (aState != aLastState){     
      // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
      if (digitalRead(pinB) != aState) { 
        if(minutes > 0) {minutes --;} // 
      } else {
        if(minutes < maxMin) {minutes ++;} // 
      }
      Serial.print("Minutes: ");
      Serial.println(minutes);
    } 
    aLastState = aState; // Updates the previous state of the outputA with the current state


    buttonState = digitalRead(buttonpin);

    if (buttonState != buttonLastState) {
      if (buttonState == 0) {
        Serial.println("Button was pressed");
        globalState = 2;
      }
      buttonLastState = buttonState;
    }
  }
  if(globalState == 2){ // Timer countDown

  }
}

