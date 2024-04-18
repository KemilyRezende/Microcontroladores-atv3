volatile int counter = 0;
volatile bool buttonPressed = false;
unsigned long last_interrupt_time = 0;

void press() {
  // Marca o tempo da interrupção atual
  unsigned long interrupt_time = millis();
  // Se a última interrupção ocorreu a menos de 400ms considera como bounce
  if (interrupt_time - last_interrupt_time > 450) 
  {
    buttonPressed = true;
  }
  last_interrupt_time = interrupt_time;
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); // Configura o pino 2 como entrada com pull-up interno
  attachInterrupt(digitalPinToInterrupt(2), press, FALLING); // Muda para FALLING
}

void loop() {
  if(buttonPressed){ //Ao pressionar o botão conta a interrupção
    counter++;
    Serial.print("Contador: ");
    Serial.println(counter);
    buttonPressed = false;
  }
}
