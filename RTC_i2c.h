/*
  RTC_i2c.h - Biblioteca RTC para Arduino desenvolvida por
  Luiz Fernando M. Arruda
*/

#ifndef RTC_i2c_h
#define RTC_i2c_h

#include "Arduino.h"

class RTC_i2c {
    public:
     
		byte getSemana();
		byte getDia();
		byte getMes();
		byte getAno();
		byte getHora();
		byte getMin();
		byte getSec();
	  
		String getData();
		String getTempo();
	  
		void setSemana(byte);
		void setDia(byte);
		void setMes(byte);
		void setAno(byte);
		void setHora(byte);
		void setMin(byte);
		void setSec(byte);
      
		void setDateTime(byte Semana, byte Dia, byte Mes, byte Ano, byte Hora, byte Min, byte Sec);
		void getDateTime();
     
    private:
		byte _Semana;
		byte _Dia;
		byte _Mes;
		byte _Ano;
		byte _Hora;
		byte _Min;
		byte _Sec;
		byte bcd2bin(byte bcd_value);
		byte bin2bcd(byte binary_value);
};

#endif
