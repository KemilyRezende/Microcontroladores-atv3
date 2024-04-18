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

Disponível em: https://wokwi.com/projects/395521541596680193

### 2. Medidor de Tempo de Interrupção.

O objetivo deste experimento é desenvolver um programa que meça o tempo entre duas interrupções externas em milissegundos. O início e o fim do tempo são disparados por dois botões diferentes, cada um conectado a seu próprio pino de interrupção (pino 2 e pino), de acordo com o circuito abaixo. O tempo decorrido é exibido no Serial Monitor.

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

```

Quando o primeiro botão é pressionado, a função `initTime()` é chamada e registra o tempo atual (`initialTime`) usando a função `millis()`. Quando o segundo botão é pressionado, a função `finishTime()` é chamada para registrar o tempo atual (`finalTime`). Se `initialTime` for menor que `finalTime` e não houver debounce ativo, o programa calcula o tempo decorrido entre os dois eventos e o exibe no Serial Monitor em milissegundos. Depois, o programa zera `initialTime` e `finalTime e define debounce como verdadeiro para evitar múltiplas leituras por um curto período. O loop principal gerencia a lógica de debounce para garantir medições precisas.

Disponível em: https://wokwi.com/projects/395519406654782465

### 3. Alarme de Interrupção com Cancelamento.

Disponível em: https://wokwi.com/projects/395519895410805761

### 4. Alarme com Função Soneca.

O objetivo deste experimento é fazer um alarme que, ao ser disparado, emite um som e, se a função soneca for ativada, silencia por um período de tempo antes de soar novamente. Foi utilizado um buzzer para o som do alarme e botões para disparar (desligar) o alarme e ativar a função soneca de acordo com o circuito. Se o alarme não for desligado pelo botão, ele deve desligar sozinho após 30 segundos de funcionamento.

<figure>
<img src="questão 4/soneca.png"/>
<figcaption> Circuito Medidor</figcaption>
</figure>

Para aplicar a lógica, algorítmo abaixo foi desenvolvido: 

```ino
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

```

O buzzer é acionado com uma frequência de 1000 Hz e é controlado pelas interrupções nos pinos digitais 2 e 3. Quando uma interrupção ocorre no pino 2, a função `off()` é chamada para desligar o buzzer. Se a interrupção ocorre no pino 3, a função `sleep()` ativa o modo de descanso (`sleepMode`) se o tempo entre interrupções for superior a 450 milissegundos, atualizando o último tempo de interrupção. No loop principal, se o modo de descanso estiver ativo, o buzzer é desligado por 5 segundos e depois é ligado novamente. Além disso, o buzzer será desligado se o tempo de execução exceder 30 segundos.

Disponível em: https://wokwi.com/projects/395524723483063297

## Conclusões

Neste estudo, foi analisado como interrupções em microcontroladores podem ser aplicadas utilizando simulações na plataforma Wokwi. Foi demonstrado a importância dessas interrupções para a realização de tarefas críticas e para melhorar a eficiência em sistemas embarcados. As simulações mostraram o quão crucial é lidar com problemas como debounce e gerenciamento de estados para evitar erros, assegurando um desempenho satisfatório do Arduino ao lidar com interrupções.
