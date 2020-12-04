
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

const int ledPin = 16;
String mensaje = "";
char serial;
BluetoothSerial SerialBT;
void setup() {
  pinMode(ledPin,OUTPUT);
  Serial.begin(115200);
SerialBT.begin("ESP32test"); //Bluetooth device name
Serial.println("The device started, now you can pair it with bluetooth!");

}

void loop() {
  if (Serial.available()) {
SerialBT.write(Serial.read());
}
if(SerialBT.available()){
 char serie = SerialBT.read();
 if(serie != '\n'){
 mensaje += String(serie);
 }
 else{
  mensaje = "";
  }
  Serial.write(serie);
 }
  //Serial.write("hola"+mensaje);
 if(mensaje == "on"){
  digitalWrite(ledPin, HIGH);
  }
 else if(mensaje == "off"){
  digitalWrite(ledPin, LOW);
  }
  delay(20);
 }


