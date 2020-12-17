#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>

//Token generado por la aplicacion
char tok[] = "gZCyPBL1tEHDxxNJBcfuW6B19C7wBnFy";

//Datos para la conexion
char ssid[] = "INFINITUM4524_2.4";
char pass[] = "Peepeepoopoocheck77.";

void setup() {
  Serial.begin(115200);
  Blynk.begin(tok, ssid, pass);

  //Enviar por corrreo electronico al servidor Blynk
  //Correo,Asunto,Mensaje
  Blynk.email("seashell.marquez17@tectijuana.edu.mx","Subject","Mi proyecto");
  pinMode(16,INPUT);//sensor5
  pinMode(17,OUTPUT);//bocina4
}
void Alarma(){
  //Si la alarma se enciende se envia un correo y espera 15sg

  int Sensor = digitalRead(16);//Variable para guardar estado del sensor
  Serial.println(Sensor);
  //si se activa la alarma
  if(Sensor == 0){
    Serial.println("Alarma activada");
    Serial.println(Sensor);
       Blynk.email("seashell.marquez17@tectijuana.edu.mx","Alarma activada","Movimiento sospechoso");
    delay(200);
    }
  }
void loop() {
  Alarma();
  Blynk.run();
}
