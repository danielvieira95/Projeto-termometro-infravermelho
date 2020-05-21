/*
 * Código para realizar o monitoramento do barramento I2C do Arduino nano
 */
#include <Wire.h>
 
void setup()  {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Scanner I2C");
}
 
void loop() {
  byte erro, endereco;
  int dispositivos;
 
  Serial.println("Procurando Dispositivo I2C ...");
 
  dispositivos = 0;
 
  for (endereco = 1; endereco < 127; endereco++ )   {
    Wire.beginTransmission(endereco);
    erro = Wire.endTransmission();
 
    if (erro == 0)  {
      Serial.print("Dispositivo I2C encontrado. Endereco 0x");
 
      if (endereco < 16)   Serial.print("0");
      Serial.print(endereco, HEX);
      Serial.println("  !");
      dispositivos++;
    }
 
    else if (erro == 4)    {
      Serial.print("Erro desconhecido no Endereco 0x");
      if (endereco < 16)    Serial.print("0");
    }
  }
 
  if (dispositivos == 0)
    Serial.println("Nenhum dispositivo I2C encontrado\n");
 
  else
    Serial.println("Scaneamento Concluido\n");
    while(Serial);
}
