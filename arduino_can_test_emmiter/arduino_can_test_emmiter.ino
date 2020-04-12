/*CODE BY A. ADRIAN GLEZ. PEDROUZO 2020 based in Seeed Studio examples*/

//SCRIPT PARA ENVIAR INFORMACIÓN POR EL CAN BUS (EMISOR)
//Controlamos el mensaje enviado con un boton en el pin 2 del controlador
//SE incluye código para controlar el encendido y apagado de un led situado
//al otro lado del bus CAN (otra microcontroladora. Ver arduino_can_test_receiver.ino)

//Biblioteca ría SPI de arduino
#include <SPI.h>
//Biblioteca de CAN Bus (La puedes descargar en: https://github.com/Seeed-Studio/CAN_BUS_Shield)
#include <mcp_can.h>

//Pin SPI
const int spiCSPin = 10;

//Pin del botón
const int pinButton = 2;

//Struct de la biblioteca para gestionar el CAN
MCP_CAN CAN(spiCSPin);

//Función de setup
void setup()
{
    //Inicializamos el monitor serie a 115200 baudios (debe configurarse 
    //así también en la ventana del monitor serie para poder visualizar
    //la salida adecuadamente).
    Serial.begin(115200);
  
    //Esperamos a que se inicialice el módulo CAN, a una velocidad de 500kbps (puede ser modificada)
    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN BUS init Failed");
        delay(100);
    }
    Serial.println("CAN BUS Shield Init OK!");
}

//Array de 8 elementos = 8 bytes de mensaje CAN (valores: 0 1 2 3 4 5 6 7)
unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};

//Bucle principal
void loop()
{   
  int stateButton = digitalRead(pinButton); //leer estado del botón

  if (stateButton==1) {
    Serial.println("Pulsado!!!"); //Mensaje monitor serie al estar pulsado
    
  }
  //Escribimos en el primer byte del mensaje CAN el estado del botón (0/1)
  stmp[0] = stateButton;
  
  Serial.println("In loop"); //Muestra que seguimos iterando
  
  //ENVÍO DEL MENSAJE POR CAN BUS, con ID 0x43, longitud 8
  CAN.sendMsgBuf(0x43, 0, 8, stmp);
  
  delay(10);
}
