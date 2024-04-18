# Microprocessadores e Microcontroladores - Atividade 3

## Autores
João Victor Francisco de Barros

Kemily Rezende Silva

## Resumo

Este trabalho aborda conceitos fundamentais de interrupções no Arduino por meio de simulações na plataforma Wokwi. Os exercícios propostos incluem um contador de interrupções externas, um medidor de tempo de interrupção, um alarme com cancelamento e um alarme com função soneca. 

## Introdução
Este trabalho tem como objetivo fornecer uma compreensão aprofundada dos conceitos fundamentais de interrupções no arduíno por meio de quatro simulações realizadas na plataforma Wokwi. Para o mesmo, foram propostos os seguintes exercícios:
1. Contador de Interrupções Externas.
2. Medidor de Tempo de Interrupção.
3. Alarme de Interrupção com Cancelamento.
4. Alarme com Função Soneca.
### Wokwi
O Wokwi é uma plataforma de simulação gratuita que oferece suporte a uma ampla variedade de placas, incluindo Arduino, ESP32 e STM32, entre outras. Com uma interface intuitiva, os usuários podem projetar e simular circuitos eletrônicos complexos diretamente no navegador, arrastando e soltando componentes e programando microcontroladores. Com recursos avançados de simulação, o Wokwi permite testar projetos e depurar problemas antes da implementação em hardware real.


## Metodologia

### 1. Contador de Interrupções Externas.

<figure>
<img src="questão 1/contador.png"/>
<figcaption> Circuito Contador de Interrupções Externas</figcaption>
</figure>

```ino
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

```

Disponível em: https://wokwi.com/projects/395521541596680193

### 2. Medidor de Tempo de Interrupção.

O objetivo deste experimento é desenvolver um programa que meça o tempo entre duas interrupções externas em milissegundos. O início e o fim do tempo são disparados por dois botões diferentes, cada um conectado a seu próprio pino de interrupção (pino 2 e pino 3), de acordo com o circuito abaixo. O tempo decorrido é exibido no Serial Monitor.

<figure>
<img src="questão 2/medidor.png"/>
<figcaption> Circuito Medidor</figcaption>
</figure>

Para aplicar a lógica, algorítmo abaixo foi desenvolvido: 

```ino
volatile unsigned long initialTime = 0;
volatile unsigned long finalTime = 0;
bool debounce = false;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), initTime, RISING);
  attachInterrupt(digitalPinToInterrupt(3), finishTime, RISING);

}

void loop() {
  if(initialTime < finalTime && !debounce){ // Se não houver debounce ativo calcula a diferença nos dois tempos.
    Serial.print("Tempo decorrido: ");
    Serial.print(finalTime - initialTime);
    Serial.println(" ms");
    initialTime = 0;
    finalTime = 0;
    debounce = true; // Ativa o debounce para impedir incertezas
    delay(250);
  }
  else {
    debounce = false; // Desativa o debounce para habilitar novo cálculo
  }
}

void initTime(){ // Define o tempo inicial se não houver debounce ativo
  if (!debounce){
    initialTime = millis();
  }
}

void finishTime(){  // Define o tempo final se não houver debounce ativo
  if(!debounce){
    finalTime = millis();
  }
}

```

Quando o primeiro botão é pressionado, a função `initTime()` é chamada e registra o tempo atual (`initialTime`) usando a função `millis()`. Quando o segundo botão é pressionado, a função `finishTime()` é chamada para registrar o tempo atual (`finalTime`). Se `initialTime` for menor que `finalTime` e não houver debounce ativo, o programa calcula o tempo decorrido entre os dois eventos e o exibe no Serial Monitor em milissegundos. Depois, o programa zera `initialTime` e `finalTime` e define debounce como verdadeiro para evitar múltiplas leituras por um curto período. O loop principal gerencia a lógica de debounce para garantir medições precisas.

Disponível em: https://wokwi.com/projects/395519406654782465

### 3. Alarme de Interrupção com Cancelamento.

<figure>
<img src="questão 3/alarme.png"/>
<figcaption> Circuito Alarme de Interrupção com Cancelamento</figcaption>
</figure>

```ino
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

```

Disponível em: https://wokwi.com/projects/395519895410805761

### 4. Alarme com Função Soneca.

O objetivo deste experimento é fazer um alarme que, ao ser disparado, emite um som e, se a função soneca for ativada, silencia por um período de tempo antes de soar novamente. Foi utilizado um buzzer para o som do alarme e botões para disparar (desligar) o alarme e ativar a função soneca de acordo com o circuito. Se o alarme não for desligado pelo botão, ele deve desligar sozinho após 30 segundos de funcionamento.

<figure>
<img src="questão 4/soneca.png"/>
<figcaption> Circuito Alarme com Função Soneca</figcaption>
</figure>

Para aplicar a lógica, algorítmo abaixo foi desenvolvido: 

```ino
int buzzer = 10;
volatile bool sleepMode = false;
unsigned long last_interrupt_time = 0;

void off(){ // Função que desliga o alarme
  noTone(buzzer);
}

void sleep(){ // Função que ativa a soneca
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
  tone(buzzer, 1000); // Inicia o alarme 
}

void loop() {
  if(sleepMode) { // Se a função soneca foi ativada desliga o alarme por 5 segundos
    noTone(buzzer);
    delay(5000);
    tone(buzzer, 1000);
    sleepMode = false;
  }
  unsigned long currentTime = millis();
  if(currentTime > 30000){ // Se o tempo atual for maior que 30s desliga o alarme
    off();
  }
}

```

O buzzer é acionado com uma frequência de 1000 Hz e é controlado pelas interrupções nos pinos digitais 2 e 3. Quando uma interrupção ocorre no pino 2, a função `off()` é chamada para desligar o buzzer. Se a interrupção ocorre no pino 3, a função `sleep()` ativa o modo de descanso (`sleepMode`) se o tempo entre interrupções for superior a 450 milissegundos, atualizando o último tempo de interrupção. No loop principal, se o modo de descanso estiver ativo, o buzzer é desligado por 5 segundos e depois é ligado novamente. Além disso, o buzzer será desligado se o tempo de execução exceder 30 segundos.

Disponível em: https://wokwi.com/projects/395524723483063297

## Conclusões

Neste estudo, foi analisado como interrupções em microcontroladores podem ser aplicadas utilizando simulações na plataforma Wokwi. Foi demonstrado a importância dessas interrupções para a realização de tarefas críticas e para melhorar a eficiência em sistemas embarcados. As simulações mostraram o quão crucial é lidar com problemas como debounce e gerenciamento de estados para evitar erros, assegurando um desempenho satisfatório do Arduino ao lidar com interrupções.
