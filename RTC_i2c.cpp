/*
	RTC_i2c.cpp - Biblioteca RTC para Arduino desenvolvida por
  Luiz Fernando M. Arruda
*/

#include "Arduino.h"
#include <Wire.h>
#include "RTC_i2c.h"

#define End 0x68

byte RTC_i2c::getSemana(){
   return _Semana;
}

byte RTC_i2c::getDia(){
  return _Dia;
}

byte RTC_i2c::getMes(){
  return _Mes;
}

byte RTC_i2c::getAno(){
  return _Ano;
}

byte RTC_i2c::getHora(){
  return _Hora;
}

byte RTC_i2c::getMin(){
  return _Min;
}

byte RTC_i2c::getSec(){
  return _Sec;
}


String RTC_i2c::getData(){
  String Imprime = "";
  if (_Dia < 10){
    Imprime = Imprime + "0";
    }
  Imprime = Imprime + _Dia + "/";
  if (_Mes < 10){
    Imprime = Imprime + "0";
    }
  Imprime = Imprime + _Mes + "/";
  if (_Ano < 10){
    Imprime = Imprime + "0";
    }
  Imprime = Imprime + "20" + _Ano;
  
  return Imprime;
}

String RTC_i2c::getTempo(){
  String Imprime = "";
  if (_Hora < 10){
    Imprime = Imprime + "0";
    }
  Imprime = Imprime + _Hora + ":";
  if (_Min < 10){
    Imprime = Imprime + "0";
    }
  Imprime = Imprime + _Min + ":";
  if (_Sec < 10){
    Imprime = Imprime + "0";
    }
  Imprime = Imprime + _Sec;
  
  return Imprime;
}

void RTC_i2c::setSemana(byte Semana){
  _Semana = Semana;
  Wire.beginTransmission(End);
  Wire.write(0x03);
  Wire.write(bin2bcd(Semana));// Dia da Semana
  Wire.endTransmission(); 
}

void RTC_i2c::setDia(byte Dia){
  _Dia = Dia;
  Wire.beginTransmission(End);
  Wire.write(0x04);
  Wire.write(bin2bcd(Dia));// Dia da Semana
  Wire.endTransmission(); 
}

void RTC_i2c::setMes(byte Mes){
  _Mes = Mes;
  Wire.beginTransmission(End);
  Wire.write(0x05);
  Wire.write(bin2bcd(Mes));// Dia da Semana
  Wire.endTransmission(); 
}

void RTC_i2c::setAno(byte Ano){
  _Ano = Ano;
  Wire.beginTransmission(End);
  Wire.write(0x06);
  Wire.write(bin2bcd(Ano));// Dia da Semana
  Wire.endTransmission(); 
}

void RTC_i2c::setHora(byte Hora){
  _Hora = Hora;
  Wire.beginTransmission(End);
  Wire.write(0x02);
  Wire.write(bin2bcd(Hora));// Dia da Semana
  Wire.endTransmission(); 
}

void RTC_i2c::setMin(byte Min){
  _Min = Min;
  Wire.beginTransmission(End);
  Wire.write(0x01);
  Wire.write(bin2bcd(Min));// Dia da Semana
  Wire.endTransmission(); 
}

void RTC_i2c::setSec(byte Sec){
  _Sec = Sec;
  Wire.beginTransmission(End);
  Wire.write(0x00);
  Wire.write(bin2bcd(Sec));// Dia da Semana
  Wire.endTransmission(); 
}
void RTC_i2c::setDateTime(byte Semana, byte Dia, byte Mes, byte Ano, byte Hora, byte Min, byte Sec){
  Wire.beginTransmission(End);
  Wire.write(0x00);
  Wire.write(bin2bcd(Sec));   // segundo
  Wire.write(bin2bcd(Min));   // minuto
  Wire.write(bin2bcd(Hora));  // hora
  Wire.write(bin2bcd(Semana));// Dia da Semana
  Wire.write(bin2bcd(Dia));   // dia
  Wire.write(bin2bcd(Mes));   // mes
  Wire.write(bin2bcd(Ano));   // Ano 
  Wire.endTransmission(); 
}

void RTC_i2c::getDateTime(){
  byte temp;
  Wire.beginTransmission(End);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(End,7);
  if (Wire.available()){
    temp = Wire.read() & 0x7f;
    _Sec = bcd2bin(temp);
    temp = Wire.read() & 0x7f;
    _Min = bcd2bin(temp);
    temp = Wire.read() & 0x3f;
    _Hora = bcd2bin(temp);
    temp = Wire.read() & 0x7f;
    _Semana = bcd2bin(temp);
    temp = Wire.read() & 0x3f;
    _Dia = bcd2bin(temp);
    temp = Wire.read() & 0x1f;
    _Mes = bcd2bin(temp);
    temp = Wire.read();
    _Ano = bcd2bin(temp);
  }
  Wire.endTransmission();
}

byte RTC_i2c::bcd2bin(byte bcd_value){
  byte temp;
  temp = bcd_value;
  temp >>=1;
  temp = temp & 0x78;
  return (temp + (temp >>2) + (bcd_value & 0x0f));
} 

byte RTC_i2c::bin2bcd(byte binary_value){
  byte temp;
  byte retval;
  
  temp = binary_value;
  retval = 0;

  while(1){
    if (temp >=10){
      temp -= 10;
      retval +=0x10;
    } else {
      retval += temp;
      break;
    }
  }
  return retval;
}

