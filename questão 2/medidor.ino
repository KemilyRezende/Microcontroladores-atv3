volatile unsigned long initialTime = 0;
volatile unsigned long finalTime = 0;
bool debounce = false;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), initTime, RISING);
  attachInterrupt(digitalPinToInterrupt(3), finishTime, RISING);

}

void loop() {
  if(initialTime < finalTime && !debounce){
    Serial.print("Tempo decorrido: ");
    Serial.print(finalTime - initialTime);
    Serial.println(" ms");
    initialTime = 0;
    finalTime = 0;
    debounce = true;
    delay(250);
  }
  else {
    debounce = false;
  }
}

void initTime(){
  if (!debounce){
    initialTime = millis();
  }
}

void finishTime(){
  if(!debounce){
    finalTime = millis();
  }
}
