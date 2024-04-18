// Definindo os pinos para o LED, buzzer e botões
const int pin_LED = 13;
const int pin_buzzer = 12;
const int pin_sensor = 2;
const int pin_cancel_button = 3;

// Variáveis para controlar o estado do alarme e do botão de cancelamento
volatile bool alarme_ativo = false;
volatile bool cancelamento_ativo = false;

void setup() {
  // Configurando os pinos como entrada ou saída
  pinMode(pin_LED, OUTPUT);
  pinMode(pin_buzzer, OUTPUT);
  pinMode(pin_sensor, INPUT);
  pinMode(pin_cancel_button, INPUT);

  // Configurando as interrupções externas para os pinos dos botões
  attachInterrupt(digitalPinToInterrupt(pin_sensor), ativarAlarme, RISING);
  attachInterrupt(digitalPinToInterrupt(pin_cancel_button), desativarAlarme, RISING);
}

void loop() {
  // Verificando se o alarme está ativo
  if (alarme_ativo) {
    // Se o alarme estiver ativo, ligar o LED e emitir um som
    digitalWrite(pin_LED, HIGH);
    tone(pin_buzzer, 1000);
  } else {
    // Se o alarme estiver desativado, desligar o LED e parar o som
    digitalWrite(pin_LED, LOW);
    noTone(pin_buzzer);
  }
}

// Função para ativar o alarme
void ativarAlarme() {
  // Definindo a variável do alarme como verdadeira
  alarme_ativo = true;
}

// Função para desativar o alarme
void desativarAlarme() {
  // Definindo a variável do alarme como falsa
  alarme_ativo = false;
}
