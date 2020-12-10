#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
//Guardamos el valor que vamos a recibir 
int received;
//El valor que guardamos arriba lo guardamos aqui como CHAR
char receivedChar;

const char turnON ='e';
const char turnOFF ='a';

int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
 
// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;
 
void setup() {
  Serial.begin(115200);
  //Le ponemos el nombre que queramos a nuestro esp32
  SerialBT.begin("ESP32_IvanGR"); 
  Serial.println("El dispositivo a iniciado, ya puedes usar con bluetooth!");
  //Esto se imprime en el smonitor de arduino
  Serial.println("Para encender el motor envia: e");  
  Serial.println("Para apagar el motor envia: a"); 
  
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
 

}
 
void loop() {

    //Aqui le asignamos la variable para guardar lo que va a leer como instruccion
    receivedChar =(char)SerialBT.read();
  //Si el serial esta disponible entonces escribe lo que recibio
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  
  }
  //Si el serailBT esta disponible entonces le manda las lineas siguientes
  if (SerialBT.available()) {
    //Esto aparece en la app
    SerialBT.print("Instrucción recibida: ");
    //Aqui imprime la intruccion que se ingreso
    SerialBT.println(receivedChar);
    
         
    Serial.print ("Instrucción recibida: ");
    Serial.println(receivedChar);

     if(receivedChar == turnON)
    {
      //Se declara el cilo de trabajo
        while (dutyCycle <= 255){
    ledcWrite(pwmChannel, dutyCycle);   
    Serial.print("Adelante con el ciclo de trabajo: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 200;
     SerialBT.println("Motor ON: ");
     Serial.println("Motor ON: ");
     // Mueve el motor dc hacia adelante a maxima velocidad
    Serial.println("Moviendo hacia adelante");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH); 
    delay(5000);
 
    // Detiene el motor
    Serial.println("Motor detenido");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    delay(1000);
 
    // Mueve el motor dc en reversa a maxima velocidad
    Serial.println("Moviendo en reversa");
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW); 
    delay(5000);
 
    // Detiene el motor
    Serial.println("Motor detenido");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    delay(1000);
 
    // Mueve el motor dc en reversa incrementando la velocidad
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
  

       
    }
        //Si la intruccion es igual a TurnOFF (a), entonces apaga el motor y le dice que esta apagado tanto en arduino como en la app
    if(receivedChar == turnOFF)
    {
     SerialBT.println("Motor OFF: ");
     Serial.println("Motor OFF: ");
     Serial.println("Motor detenido");
     digitalWrite(motor1Pin1, LOW);
     digitalWrite(motor1Pin2, LOW);
    }   
    
    }

    
    
  
}
