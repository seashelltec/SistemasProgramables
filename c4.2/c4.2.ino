
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "INFINITUM4524_2.4";
const char* password = "Peepeepoopoocheck77.";

WiFiServer server(80);
String header;
String output26State = "off";
const int output26 = 26;

// Current time
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  pinMode(output26, OUTPUT);
  digitalWrite(output26, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Escuchando al cliente

  if (client) {                             // Si nos logramos conectar
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // Imprimimos si ya entraron al puerto
    String currentLine = "";                // Lo que mandara el cliente
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // Ciclo para el cliente cpnectado
      currentTime = millis();
      if (client.available()) {             // Si esta leyendo con el cliente
        char c = client.read();             // lee y despues
        Serial.write(c);                    // escribe en el serial
        header += c;
        if (c == '\n') {                    // Si es una nueva linea de caracteres
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Apagar y enceder la luz
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
            } 
            
            // HTM de la pagina
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            //CSS que usan los botones y la pagina en general
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Para los botones off/on o mejor dicho el boton 
            client.println("<p>GPIO 26 - State " + output26State + "</p>");     
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            client.println("</body></html>");
            
            client.println();
            // Break de nuestro ciclo
            break;
          } else { // 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    // Limpiar la variable
    header = "";
    // Cerrar la conexion
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
