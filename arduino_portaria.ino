// Programa : RFID - Controle de acesso / cancela
// Autor : Arduino e Cia

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); 

// Leds indicadores acesso liberado ou negado
int led_liberado = 6;
int led_negado = 5;

char st[20];

void setup() 
{
  pinMode(led_liberado, OUTPUT);
  pinMode(led_negado, OUTPUT);

  Serial.begin(9600);
  // Inicia  SPI bus
  SPI.begin();
  // Inicia MFRC522
  mfrc522.PCD_Init(); 
  // Mensagens iniciais no serial monitor
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
}

void loop() 
{
  // Aguarda a aproximacao do cartao
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Seleciona um dos cartoes
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  // Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  
// F4 27 CA 49 chaveiro azul
// 3A 8A 7E 29 cartao branco
// 04 7B E2 5A 09 40 80 fita amarela
// 04 BE 0B 82 09 40 84 fita verde

 
  // Testa se o cartao branco foi lido
  if (conteudo.substring(1) == "3A 8A 7E 29")
  {
    // Levanta a cancela e acende o led verde
    digitalWrite(led_liberado, HIGH);
    Serial.println("Cartao Branco - Acesso liberado !");
    Serial.println();
    delay(3000);
    digitalWrite(led_liberado, LOW);
  }

  // Testa se o fita verde foi lida
  if (conteudo.substring(1) == "04 BE 0B 82 09 40 84")
  {
    // Levanta a cancela e acende o led verde
    digitalWrite(led_liberado, HIGH);
    Serial.println("Fita verde - Acesso liberado !");
    Serial.println();
    delay(3000);
    digitalWrite(led_liberado, LOW);
  }

  // Testa se o chaveiro azul foi lido
  if (conteudo.substring(1) == "F4 27 CA 49")
  {
    Serial.println("Chaveiro azul - Acesso negado !!");
    Serial.println();
    // Pisca o led vermelho
    for (int i= 1; i<5 ; i++)
    {
      digitalWrite(led_negado, HIGH);
      delay(200);
      digitalWrite(led_negado, LOW);
      delay(200);
    }
  }
  
  // Testa se o fita amarela foi lida
  if (conteudo.substring(1) == "04 7B E2 5A 09 40 80")
  {
    Serial.println("Fita amarela - Acesso negado !!");
    Serial.println();
    // Pisca o led vermelho
    for (int i= 1; i<5 ; i++)
    {
      digitalWrite(led_negado, HIGH);
      delay(200);
      digitalWrite(led_negado, LOW);
      delay(200);
    }
  }

  delay(1000);
}
