int hall = 2;
int LED = 13;
int currentmils;
int previousmils = 0;
int cycle;
bool previousValue = false;
int value = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(hall, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = digitalRead(hall);
  currentmils = millis();
  if(value == HIGH && previousValue == LOW) {
    cycle = currentmils - previousmils
    Serial.println((cycle));
    return(cycle);
    previousmils = currentmils;
  }
  previousValue = value;
}






