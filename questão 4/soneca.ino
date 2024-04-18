int buzzer = 10;
volatile bool sleepMode = false;
unsigned long last_interrupt_time = 0;

void off(){
  noTone(buzzer);
}

void sleep(){
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 450) {
    sleepMode = true;
    last_interrupt_time = interrupt_time;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), off, RISING);
  attachInterrupt(digitalPinToInterrupt(3), sleep, RISING);
  tone(buzzer, 1000);
}

void loop() {
  if(sleepMode) {
    noTone(buzzer);
    delay(5000);
    tone(buzzer, 1000);
    sleepMode = false;
  }
  unsigned long currentTime = millis();
  if(currentTime > 30000){
    off();
  }
}
