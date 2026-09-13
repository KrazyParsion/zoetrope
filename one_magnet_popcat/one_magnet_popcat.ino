//Notes
/* 
Please read everything from up to down to make sense of it, otherwise it is very brain-wreking.
*/

//pin for hall sensor and LED (cat)
const int hallsensor = 2;
const int cat = 13;

//volatile boolean variable for magnet that changes in the ISR
volatile bool magnet = false;

//time variables used in the main loop
unsigned long startMillis = 0; //time zero
unsigned long currentMillis = 0; //time current

//variables to repeat the same thing n times (change for 10 frames)
volatile int i = 0; //count
int n = 5; //number of frames + 1

//delay for the timing of the LED
float beforecat; //pause before led turns on
float caton; //pause for led to flash
float aftercat; //pause after led flashes


//delay multipliers (change for 10 frames)
const float beforecatMultiplier = 25.0/90.0;
const float aftercatMultiplier = 60.0/90.0;
const float catonMultiplier = 5.0/90.0;

//variables for calculating period, used in ISR
unsigned long currentTime = 0; //time current
unsigned long lastTime = 0; //time zero (beginning of the previous spin)
unsigned long cycle = 400; //length of the cycle (default is 400)

void setup() {
  //adding pins and interrupts
  pinMode (hallsensor, INPUT_PULLUP);
  pinMode (cat, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(hallsensor), rotation, FALLING); //interrupt added to hallsensor when it falls from HIGH to LOW
  Serial.begin (9600);
}

void rotation () {
  //inturrupt service routine that pauses main code
  magnet = true; //turns magnet true to start the timing
  currentTime = millis();
  cycle = currentTime - lastTime; //period
  lastTime = currentTime; //sets currentTime as reference to measure the next cycle
  i = 0; //returns i counter to 0
}

void loop() {

  if (magnet == true) { //started by the ISR
    //before anything starts, determine t0 and the timing of flashes
    if (i == 0) {

      startMillis = millis(); //sets startMillis to time zero
      //converts it into multiple pieces and figures out delay before, during, and after the flash
      int quartercycle = cycle/4;
      beforecat = quartercycle *beforecatMultiplier;
      caton = quartercycle *catonMultiplier;
      aftercat = quartercycle *aftercatMultiplier;
      i++; //increment by one to ensure this only runs once per magnet cycle
      }

    //loop that runs n - 1 times (in this case 4, because there are 4 frames in the animation)
    if (i < n) {
      currentMillis = millis(); //updates currentMillis
      unsigned long deltaT = currentMillis - startMillis; //change in time

      //beforecat adds time for the wheel to spin to the center
      if (caton + beforecat >= deltaT && deltaT >= beforecat) { //light on when between these two time frames
          digitalWrite (cat, HIGH); //light turns on in front of frame 
      }
      else if (aftercat + beforecat + caton >= deltaT && deltaT >= caton + beforecat) {   //light off between these two frams
          digitalWrite (cat, LOW); //light turns off
      }
      else if (deltaT >= aftercat + beforecat + caton){
          startMillis = millis();
          i++; //restarts the if
      }
      else{
        //cuz why not
      }
    }
    if (i >= n) {
      magnet = false; //after the if loop finishes, magnet returns to false

    }
  }
}
//only used if not while, because if checks for the condition of everything every iteration, but while only checks its codeblock's condition
//so while continues in the middle of the loop, and if checks restarts as it checks the conditions before that as well

/*
function for calculation the period of a cycle

variables for timing()
bool value = 0; //set to the hallsensor
bool previousValue = 1; //previous of value
unsigned long currentTime = 0; //time current
unsigned long lastTime = 0; //time zero (beginning of the previous spin)
unsigned long cycle = 400; //length of the cycle

int timing() {
  value = digitalRead(hallsensor); //reads the hallsensor
  currentTime = millis(); //time current
  if(value == LOW && previousValue == HIGH) {
    cycle = currentTime - lastTime; //period
    Serial.println(cycle);
    lastTime = currentTime; //sets currentTime as reference to measure the next cycle
  }
  previousValue = value; //since the if checks this every loop, the hallsensor goes 111...111000...000111...111, so it only changes from 0-1 once
  return cycle;
}
*/



