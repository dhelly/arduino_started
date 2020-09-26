#include <dht.h> //Inclusão da biblioteca - Temp
#include <Wire.h> //INCLUSÃO DA BIBLIOTECA - Clock
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA - Clock

#include <ClosedCube_HDC1080.h> //sensor de precisão

#include <LiquidCrystal.h> //display

#define DHT11_PIN A1

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
dht DHT;

RTC_DS1307 rtc; //OBJETO DO TIPO RTC_DS1307
//DECLARAÇÃO DOS DIAS DA SEMANA
//char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};
char daysOfTheWeek[7][12] = {"DOM", "SEG", "TER", "QUA", "QUI", "SEX", "SAB"};
int dia;
int mes;
int ano;
int hora;
char result;
int minuto;
int segundo;

ClosedCube_HDC1080 hdc1080; //objeto hdc1080

void setup()
{
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
//  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");

  lcd.begin(16, 2);
  
  if (! rtc.begin()) { // SE O RTC NÃO FOR INICIALIZADO, FAZ
    Serial.println("DS1307 não encontrado"); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
  if (! rtc.isrunning()) { //SE RTC NÃO ESTIVER SENDO EXECUTADO, FAZ
    Serial.println("DS1307 rodando!"); //IMPRIME O TEXTO NO MONITOR SERIAL
    //REMOVA O COMENTÁRIO DE UMA DAS LINHAS ABAIXO PARA INSERIR AS INFORMAÇÕES ATUALIZADAS EM SEU RTC
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
    //rtc.adjust(DateTime(2020, 9, 5, 9, 10, 30)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
  }
  delay(1000); //INTERVALO DE 100 MILISSEGUNDOS

  //Inicializa o HDC1080 no endereço 0x40
  hdc1080.begin(0x40);
  Serial.println("Sensor HDC1080 com Arduino");
}

void loop()
{
  // READ DATA
//  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
//  switch (chk)
//  {
//    case DHTLIB_OK:  
//                Serial.print("OK,\t"); 
//                break;
//    case DHTLIB_ERROR_CHECKSUM: 
//                Serial.print("Checksum error,\t"); 
//                break;
//    case DHTLIB_ERROR_TIMEOUT: 
//                Serial.print("Time out error,\t"); 
//                break;
//    case DHTLIB_ERROR_CONNECT:
//        Serial.print("Connect error,\t");
//        break;
//    case DHTLIB_ERROR_ACK_L:
//        Serial.print("Ack Low error,\t");
//        break;
//    case DHTLIB_ERROR_ACK_H:
//        Serial.print("Ack High error,\t");
//        break;
//    default: 
//                Serial.print("Unknown error,\t"); 
//                break;
//  }


  //Dados de temperatura e humidade
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.setCursor(2,0);
  lcd.print(DHT.temperature);

  lcd.setCursor(9,0);
  lcd.print("H:");
  lcd.setCursor(11,0);
  lcd.print(DHT.humidity);

  //TIME
  DateTime now = rtc.now(); //CHAMADA DE FUNÇÃO  

  delay(1000); //INTERVALO DE 1 SEGUNDO;

  //DISPLAY TIME(col,lin)

  //Time

  //hora
  lcd.setCursor(0,1);  
  hora = (int) now.hour();
  if(hora < 9) lcd.print('0');
  lcd.print(now.hour());

  //minuto
  lcd.setCursor(2,1);
  lcd.print(':');    
  minuto = (int) now.minute();
  if(minuto < 9) lcd.print('0');    
  lcd.print(now.minute());

  //segundo
  lcd.setCursor(5,1);
  lcd.print(':');    
  segundo = (int) now.second();
  if(segundo < 9) lcd.print('0');    
  lcd.print(now.second());

  //dia
  lcd.setCursor(11,1);
  dia = (int) now.day();
  if(dia < 10) lcd.print(0);
  lcd.print(dia);

  //mes
  lcd.print('/');
  lcd.setCursor(14,1);
  mes = (int) now.month();
  if(mes < 10) lcd.print(0);
  lcd.print(mes);

//formato para o datalog

  // DISPLAY DATA
//  Serial.print(now.day(), DEC); //IMPRIME NO MONITOR SERIAL O DIA
//  Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
//  Serial.print(now.month(), DEC); //IMPRIME NO MONITOR SERIAL O MÊS
//  Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
//  Serial.print(now.year(), DEC); //IMPRIME NO MONITOR SERIAL O ANO
//  Serial.print(";");
//
//  Serial.print(now.hour(), DEC); //IMPRIME NO MONITOR SERIAL A HORA
//  Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
//  Serial.print(now.minute(), DEC); //IMPRIME NO MONITOR SERIAL OS MINUTOS
//  Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
//  Serial.print(now.second(), DEC); //IMPRIME NO MONITOR SERIAL OS SEGUNDOS
//  Serial.print(";");
//  
//  Serial.print(DHT.humidity, 1);
//  Serial.print(";");
//  Serial.print(DHT.temperature, 1);
  
///  Serial.println();

  //Le os valores de temperatura e umidade
  float t = hdc1080.readTemperature();
  float h = hdc1080.readHumidity();

  //Mostra os valores no Serial Monitor
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" C, Umidade: ");
  Serial.print(h);
  Serial.println(" %");

}
