#include <SoftwareSerial.h>
#include "LedControlMS.h" 
 
 
 
LedControl lc=LedControl(12,9,8,1); // Los numeros se refieren a que pin de ARDUINO tienes en cada uno de los terminales
 
/* 12 para el DIN, 9 para el CLK, 8 para el CS y el 1 se refiere a la asignacion de la matriz*/ 
char DATO=0;


SoftwareSerial miBT(10, 11);

 byte Izquierda_datos[] = {
 
  B00011000,
 
  B00111000,
 
  B01111111,
 
  B11111111,
 
  B11111111,
 
  B01111111,
 
  B00111000,
 
  B00011000};
 byte Derecha_datos[] = 
 
{B00011000,
 
B00011100,
 
B11111110,
 
B11111111,
 
B11111111,
 
B11111110,
 
B00011100,
 
B00011000};

byte parar[] = {
B00111100,
B01100010,
B11110001,
B10111001,
B10011101,
B10001111,
B01000110,
B00111100};

byte apagar[] = {
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000};

//Funcion de transicion para llenar y vaciar la pantalla de puntos
void trans(){
  for (int row=0; row<8; row++){
    for (int col=0; col<8; col++){
      lc.setLed(0,col,row,true); // 
      delay(25);
    }
  }
  for (int row=0; row<8; row++){
    for (int col=0; col<8; col++){
      lc.setLed(0,col,row,false); // 
      delay(25);
    }
  }
}

void setup(){
  Serial.begin(9600);
  miBT.begin(38400);
  //
  lc.shutdown(0,false);
 
  lc.setIntensity(0,8);// La valores estan entre 1 y 15 
 
  lc.clearDisplay(0);

}
  void loop(){

  DATO = miBT.read();
    switch(DATO){
      case '0':
        trans();
      break;
      case '2':
      for(int i=0;i<=20;i++){
        Representar(Izquierda_datos,500);
        delay(50);
        Representar(apagar, 250);
        delay(50);
      }
      break;
      case '1':
       for(int i=0;i<=20;i++){
        Representar(Derecha_datos,500);
        delay(50);
        Representar(apagar, 250);
        delay(50);
      }
      break;
      case '3':
        for(int i=0;i<=20;i++){
        Representar(parar,500);
        delay(50);
        Representar(apagar, 250);
        delay(50);
        }
      break;
      default:
        lc.clearDisplay(0);
    }
//    if (miBT.available()){
//      DATO = miBT.read();
//      if(DATO=='1')
//      Representar(Izquierda_datos,5000);
//    }
//    if (miBT.available()){
//      DATO = miBT.read();
//      if(DATO=='2')
//      Representar(Derecha_datos,5000);
//    }
//    
//     if (miBT.available()){
//      DATO = miBT.read();
//      if(DATO=='3')
//      Representar(parar,5000);
//    }
    
  }




  void Representar(byte *Datos,int retardo) //Funcion para la representacion de bytes de datos para una matriz de 8x8 
 
{
 
  for (int i = 0; i < 8; i++)  
 
  {
 
    lc.setColumn(0,i,Datos[7-i]);
 
  }
 
  delay(retardo);
 
}
