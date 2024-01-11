// Código para um protótipo virtual de sistema de alarme
// Desenvolvido no 2o sem. de 2023 para a disciplina UPX
// ADS - Facens - Sorocaba - SP

int pinLed = 13;
int pinBuzzer = 12;
int pinDiodo = 11;
int pinPIR = 10;
int pinBotao = 9;
int pinLDR = A0;

int leituraLDR = 0; //recebe leitura do LDR

int tempo = 10; //variavel para temporizador
int flag = 0;   //sinaliza inicio do temporizador

void setup()
{
  Serial.begin(9600);
  
  pinMode(pinLed, OUTPUT);        // LED
  pinMode(pinBuzzer, OUTPUT);     // buzzer
  pinMode(pinDiodo, OUTPUT);      // diodo laser
  pinMode(pinPIR, INPUT);         // sensor PIR
  pinMode(pinLDR, INPUT);         // sensor LDR
  pinMode(pinBotao,INPUT_PULLUP); // Botao para desativação do alarme no protótipo
  
  delay(3000); //atraso para inicio do sistema no protótipo virtual
}

void loop()
{
  leituraLDR = analogRead(pinLDR); //recebe a leitura do LDR
  
  Serial.print("Valor do sensor PIR: "); 
  Serial.print(digitalRead(pinPIR));  
  Serial.print("\tValor do sensor LDR: ");
  Serial.println(leituraLDR); //impressão do valor para conferência
  
  if(digitalRead(pinPIR) == HIGH || leituraLDR <= 950){ //valor de referência no protótipo virtual
    flag = 1;
    while(flag == 1){
      tempo--;
  	  digitalWrite(pinLed, HIGH);
  	  tone(pinBuzzer,260,250);
  	  delay(1000);
      if(tempo == 0 || digitalRead(pinBotao) == LOW){
        flag = 0;
        tempo = 10;
      }
    }
  }
  else{
    digitalWrite(pinLed, LOW);
    noTone(pinBuzzer);
    delay(1000);
  }
}
