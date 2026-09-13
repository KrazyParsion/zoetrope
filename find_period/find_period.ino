const int hallSensor = 2;
unsigned long currentTime = 0;
unsigned long lastTime = 0;
unsigned long period;

void setup() {
  // put your setup code here, to run once:
  pinMode(hallSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hallSensor), rotation, FALLING);
  Serial.begin(9600);
}

void rotation() {
  currentTime = millis();
  period = currentTime - lastTime;
  lastTime = currentTime;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(period);
}
