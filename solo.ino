//Autor: FILIPEFLOP
 
int valor_analogico;
 
void setup()
{
  Serial.begin(9600);
//  pinMode(pino_sinal_analogico, INPUT);
}
 
void loop()
{
  //Le o valor do pino A0 do sensor
  valor_analogico = analogRead(A0);
 
  //Mostra o valor da porta analogica no serial monitor
  Serial.print("Porta analogica: ");
  Serial.print(valor_analogico);
 
  //Solo umido, acende o led verde
  if (valor_analogico > 0 && valor_analogico < 400)
  {
    Serial.println(" Status: Solo umido");
  }
 
  //Solo com umidade moderada, acende led amarelo
  if (valor_analogico > 400 && valor_analogico < 800)
  {
    Serial.println(" Status: Umidade moderada");
  }
 
  //Solo seco, acende led vermelho
  if (valor_analogico > 800 && valor_analogico < 1024)
  {
    Serial.println(" Status: Solo seco");
  }

  
    // read the input on analog pin 0:
  int sensorValue = analogRead(A1);

  if (sensorValue > 800)
  {
    Serial.println("Tempo seco");
  }
  else if (sensorValue > 500)
  {
    Serial.println("Chuva fraca");
  }
  else if (sensorValue > 300)
  {
    Serial.println("Chuva moderada");
  }
  else
  {
    Serial.println("Chuva forte");
  }
  Serial.println(sensorValue);
  
  delay(1000);
}
