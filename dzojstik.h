#include "stm32f10x.h" // Device header
 int raw;
 int main()
 {
	 
 //enable ADC1 in RCC enable clock on PORTA and alternative function bit
 RCC->APB2ENR |=RCC_APB2ENR_ADC1EN;
 //set ADC clock -> CFGR prescaler max 14MHZ recommended 12MHz
 
 //select sampling time on ch0 pin A0 "SMPR2 register" -> Tconve = cycles / ADCCLK -> 111
 //select sequence -> we only have one on first chanel so we "point" to first sequence on SQR3 register 
 ADC1 ->SQR3 |=(0<<0);
 
 //enable ADC_CR2_CONT
 //enable ADON bit -> wake up ADC
 
 // reset calibration in CR2
 //wait a litle bit
 //CR2 register -> init calibration bit and wiat until HW reset it CAL bit
 //wait a litle bit
 //once again set 1 to ADON bit -> first time wake up second time start conversion  
 while(1)
 {
 //wait until EOC bit is set ADC_SR registar Bit 1 EOC: End of conversion
 //wait until End of conversion EOC bit is "0"
 // read raw binary data from varible 
raw= ADC1->DR; //register
 }
 }
 
 