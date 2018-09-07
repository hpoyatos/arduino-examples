#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

IPAddress server_addr(192,168,0,100);  // IP of the MySQL *server* here
char user[] = "nodemcu2";              // MySQL user login username
char password[] = "teste";        // MySQL user login password

WiFiClient client;
MySQL_Connection conn((Client *)&client);

// Set these to run example.
//#define FIREBASE_HOST "nodemcu-acd5f.firebaseio.com"
//#define FIREBASE_AUTH "LqVDaIJOkcnV6vKqiU977B9mYpoxxSELbpnYPGWR"
#define WIFI_SSID "TUX_ext"
#define WIFI_PASSWORD "sJMkLPCUEZ7kv4d"

int valor_analogico;

 // Sample query
  char INSERT_SQL[] = "INSERT INTO nodemcu.chuva (vl_chuva) VALUES (%s)";

void setup() {
  Serial.begin(9600);

  Serial.println(WiFi.macAddress());
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

//  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Serial.println("Conectando MySQL...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
  }
  else
  {
    Serial.println("Conexão falhou.");
  }
}

void loop() {  
  valor_analogico = analogRead(A0);


  char query[64];
  char medicao[10];
  dtostrf(valor_analogico, 1, 1, medicao);
  sprintf(query, INSERT_SQL, medicao);
  Serial.println(query);

  Serial.println("Recording data.");

  //Firebase.setFloat("chuva", 200);
  // handle error
  //if (Firebase.failed()) {
 //     Serial.print("setting /number failed:");
 //     Serial.println(Firebase.error());  
 //     return;
  //}

 
  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
  
  cur_mem->execute(query);
  // Note: since there are no results, we do not need to read any data
  // Deleting the cursor also frees up memory used
  delete cur_mem;

  delay(60000);

}
