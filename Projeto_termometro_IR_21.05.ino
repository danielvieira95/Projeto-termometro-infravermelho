/*
  Projeto : Termometro  utilizando o sensor de temperatura infravermelho MLX90614
  Autor Daniel Vieira
 */

// --- Inclusao de bibliotecas 
#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_GFX.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_SSD1306.h> //INCLUSÃO DE BIBLIOTECA
#include <SparkFunMLX90614.h> 

Adafruit_SSD1306 display = Adafruit_SSD1306(); //OBJETO DO TIPO Adafruit_SSD1306

IRTherm temperatura; // Instancia a variavel temperatura como um objeto do IRTherm

// ----MAPEAMENTO DE HARDWARE
#define B0 2 // Mapeia o pino 2 como B0
#define led_azul 5 //
#define led_vermelho 6


//--- Declaração de variaveis

float  soma_temp =0, media_temp =0;
boolean en_sensor =0;
unsigned long interval = 200;
void setup()
{
   temperatura.begin(0x5A);
   temperatura.setUnit(TEMP_C);
   Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  display.begin(0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
  pinMode(B0,INPUT);
  pinMode(led_azul,OUTPUT);
  pinMode(led_vermelho,OUTPUT);
    Serial.begin(9600);
  Serial.println("Termometro infravermelho ");
  Serial.println("Covid 19 ");
  display.setCursor(10, 0);       // Posiciona o cursor
  display.setTextSize(1);       // Define tamanho da fonte
  display.print("TERMOMETRO IR "); 
  delay(2000);
}
void loop()
{
      
   if(!digitalRead(B0) && en_sensor==0)
  {
      en_sensor =1;
      display.clearDisplay();
     
     while(digitalRead(B0)==0);
  }
   if(!digitalRead(B0) && en_sensor==1)
  {
      en_sensor =0 ;
      display.clearDisplay();
      
      digitalWrite(led_azul,0);
     while(digitalRead(B0)==0);
  }
    if(en_sensor ==1)
    {
      display.clearDisplay();
      digitalWrite(led_azul,1);       
          
    if(millis () - interval >200 )
    {
      if (temperatura.read()) 
    
    {
       interval = millis();
       for (int i=0; i<10; i++)
       {
          soma_temp+= temperatura.object();
          delay(100);
       }

       media_temp = soma_temp /10;
       soma_temp =0;
       
       display.clearDisplay();
       display.setCursor(10, 0);       // Posiciona o cursor
       display.setTextSize(1);       // Define tamanho da fonte
       display.print("TERMOMETRO IR ");
       display.setCursor(0, 10);       // Posiciona o cursor
       display.setTextSize(1);        // Define tamanho da fonte
 
       display.print("Temperatura: " + String(media_temp, 2));
       display.println(" oC ");
       Serial.print("Temperatura objeto :");
       Serial.print(media_temp, 2);
       Serial.println(" oC ");
           // Imprime ...
            
      
      if(media_temp >39 )
      {
         display.setCursor(0, 20);       // Posiciona o cursor
         display.setTextSize(1);        // Define tamanho da fonte
         display.print("Procure um medico !" );
         digitalWrite(led_vermelho,1);
      }

       else 
      {
         display.setCursor(0, 20);       // Posiciona o cursor
         display.setTextSize(1);        // Define tamanho da fonte
         display.print("Temperatura normal !" );
         digitalWrite(led_vermelho,0);
      }
     display.display();

     
    //display.print("Ambiente: " + String(temperatura.ambient(), 2));
   // Serial.print("Temperatura ambiente :");
   // Serial.print(temperatura.ambient(), 2);
   // Serial.println(" oC ");
   // display.print(" oC");       // Imprime ...
    
    
  }
  
  }
     
     
   
    }  
 

}
 
            


