#include <MFRC522.h>

// Programa : RFID - Supermercado
// Autor : Henrique Poyatos

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); 

// Leds indicadores acesso liberado ou negado
int led_verde = 6;

char st[20];

byte total_produtos = 7;

String produtos[7] = {
  "",
  "04 2B 2F CA 09 40 81",
  "04 84 62 32 09 40 81",
  "04 BE 0B 82 09 40 84",
  "04 7B E2 5A 09 40 80",
  "04 1B 2F CA 09 40 81",
  "04 6F 63 32 09 40 81"
};
  
String produtos_nome[7] = {
  "",
  "Suco de laranja e maca",
  "Biscoito Belvita",
  "Cha de hibisco",
  "Molho shoyu",
  "Condicionador Dove",
  "Caixa de fósforos Fiat Lux"
};
  
float produtos_preco[] = {
  0,
  5.0,
  6.0,
  3.0,
  7.0,
  11.5,
  2.5
};

  
float total = 0.0;
  
byte j=0;
byte carrinho[10];

void setup() 
{
  pinMode(led_verde, OUTPUT);
  
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
  //Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  Serial.print("RFid identificado");
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);

     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.println("Mensagem : ");
  conteudo.toUpperCase();
  
  verifica_produto(conteudo.substring(1));
  

  delay(1000);
}

void verifica_produto(String tagId)
{
  for (byte i = 0; i < total_produtos; i++)
  {
    if (tagId.equals(produtos[i]))
    {
      Serial.print("\nProduto registrado: "+produtos_nome[i]+"(R$ ");
      Serial.print(produtos_preco[i]);
      Serial.println(")\n");
      
      total += produtos_preco[i];
      
      carrinho[j] = i;
      j++;
      
      // Pisca o led verde
      for (int i= 1; i<5 ; i++)
      {
        digitalWrite(led_verde, HIGH);
        delay(200);
        digitalWrite(led_verde, LOW);
        delay(200);
      }
    }
  }

  exibe_lista_de_compras();
}

void exibe_lista_de_compras()
{
  Serial.println("========================================");
  Serial.println("| LISTA DE COMPRAS                     |");
  Serial.println("========================================");

  for (byte i=0; i< 10; i++)
  {
    if (carrinho[i] > 0)
    {
      Serial.print("| "+produtos_nome[carrinho[i]]+" (R$ ");      
      Serial.print(produtos_preco[carrinho[i]]);
      Serial.println(")");
    }
  }
    
  Serial.println("========================================");
  Serial.print("| TOTAL : R$ ");
  Serial.print(total);
  Serial.println("                     |");
  Serial.println("========================================\n");
    
}
