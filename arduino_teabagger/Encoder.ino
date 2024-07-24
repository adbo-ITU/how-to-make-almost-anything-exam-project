// display setup 
// https://docs.arduino.cc/learn/electronics/lcd-displays/

#define pinA 11
#define pinB 12
#define encoderButtonpin 13

const int maxMin = 99;
const int maxTemp = 100;
float temp;
float minutes;
int aState;
int aLastState;
bool encoderButtonState;
bool encoderButtonLastState;
int globalState;

void setup() { 
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(encoderButtonpin, INPUT);
   
  Serial.begin(9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(pinA);
  encoderButtonLastState = digitalRead(encoderButtonpin);
  globalState = 0;
  temp = 100;
  minutes = 0;
} 

void loop() {
  if (globalState == 0){ // Select temp
    updateValEncoder(temp, maxTemp, 0, 5);
    confirmSelection();
  }
  if (globalState == 1){ // Select time
    updateValEncoder(minutes, maxMin, 0, 0.5);
    confirmSelection();
  }
  if (globalState == 2){ // Timer countDown
  }
}

void updateValEncoder(float &val, int maxval, int minval, float interval){
    aState = digitalRead(pinA); // Reads the "current" state of the outputA
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    if (aState != aLastState){     
      // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
      if (digitalRead(pinB) != aState) { 
        if(val > minval) {val -=interval;} // 
      } else {
        if(val < maxval) {val +=interval;} // 
      }
      Serial.print("value: ");
      Serial.println(val);
    } 
    aLastState = aState; // Updates the previous state of the outputA with the current state
}

void confirmSelection(){
  encoderButtonState = digitalRead(encoderButtonpin);
  if (encoderButtonState !=encoderButtonLastState) {
    if (encoderButtonState == 0) {
      Serial.println("Button was pressed");
      globalState ++;
      Serial.println(globalState);
    }
    encoderButtonLastState = encoderButtonState;
  }
}
