/*
Demonstração biblioteca RTC_i2c trabalhando com DS1307 
*/
#include <RTC_i2c.h>
#include <Wire.h>

RTC_i2c diario;
#define i2c_rtc 0x68

void setup() {
  Serial.begin(9600);
  Serial.println("Testando modulos no barramento i2c.");
  Wire.begin(); 
  // testa comunicacao RTC
  Wire.beginTransmission(i2c_rtc);
  int error = Wire.endTransmission();
  if (error == 0) {
    Serial.println("RTC Online");
  } else {
    Serial.println("RTC Offline");
  }
  
  diario.setDateTime(1, 22, 5, 99,14, 22, 10);
}

void loop() {
  // put your main code here, to run repeatedly:
  diario.getDateTime();
  byte Hora = diario.getHora();
  byte Min = diario.getMin();
  byte Sec = diario.getSec();
  Serial.print(Hora);
  Serial.print(":");
  Serial.print(Min);
  Serial.print(":");
  Serial.println(Sec);
  
  byte Ano = diario.getAno();
  byte Mes = diario.getMes();
  byte Dia = diario.getDia();

  
  Serial.print(Dia);
  Serial.print("/");
  Serial.print(Mes);
  Serial.print("/20");
  Serial.println(Ano);
  delay(1000);
  
}
