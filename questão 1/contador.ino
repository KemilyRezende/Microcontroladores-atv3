volatile int counter = 0;
volatile bool buttonPressed = false;
unsigned long last_interrupt_time = 0;

void press() {
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 450) 
  {
    buttonPressed = true;
  }
  last_interrupt_time = interrupt_time;
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), press, FALLING);
}

void loop() {
  if(buttonPressed){ 
    counter++;
    Serial.print("Contador: ");
    Serial.println(counter);
    buttonPressed = false;
  }
}
