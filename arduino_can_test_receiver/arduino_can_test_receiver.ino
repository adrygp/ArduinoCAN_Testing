/*CODE BY A. ADRIAN GLEZ. PEDROUZO 2020 based in Seeed Studio examples*/

//SCRIPT PARA LEER DEL CAN BUS (RECEPTOR)
//Adicionalmente a la lectura (que se muestra por el monitor serie)
//SE incluye código para controlar el encendido y apagado de un led,
//situado en el pin 2 del controlador.

//Biblioteca ría SPI de arduino
#include <SPI.h>
//Biblioteca de CAN Bus (La puedes descargar en: https://github.com/Seeed-Studio/CAN_BUS_Shield)
#include <mcp_can.h>

//Pin SPI
const int spiCSPin = 10;

//Pin del led
const int ledPin = 2;
//Booleano que indica el estado del led (encendido/apagado)
boolean ledON = 1;

//Struct de la biblioteca para gestionar el CAN
MCP_CAN CAN(spiCSPin);

//Función de setup
void setup()
{
    //Inicializamos el monitor serie a 115200 baudios (debe configurarse 
    //así también en la ventana del monitor serie para poder visualizar
    //la salida adecuadamente).
    Serial.begin(115200);
    pinMode(ledPin,OUTPUT); //Pin led establecido como salida

    //Esperamos a que se inicialice el módulo CAN, a una velocidad de 500kbps (puede ser modificada)
    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN BUS Init Failed");
        delay(100);
    }
    Serial.println("CAN BUS  Init OK!");
}

//Bucle principal
void loop()
{
    //Longitud del mensaje CAN (<= 8)
    unsigned char len = 0;
    //Contenido del mensaje CAN
    unsigned char buf[8];

    //Comprobamos si hay un mensaje disponible
    if(CAN_MSGAVAIL == CAN.checkReceive())
    {
        //Leemos el mensaje
        CAN.readMsgBuf(&len, buf);

        //Obtenemos el ID CAN
        unsigned long canId = CAN.getCanId();

        //Mostramos por monitor serie la información obtenida
        Serial.println("-----------------------------");
        Serial.print("Data from ID: 0x");
        Serial.println(canId, HEX);

        for(int i = 0; i<len; i++)
        {
            Serial.print(buf[i]);
            Serial.print("\t");
        }

        //Controlamos el led en función del primer byte
        if(ledON && buf[0] == 0) {
          ledON = 0;
          digitalWrite(ledPin, 0);
        }
        else if (!ledON && buf[0] == 1){
          ledON = 1;
          digitalWrite(ledPin, 1);
        }
        Serial.println();
    }
}
