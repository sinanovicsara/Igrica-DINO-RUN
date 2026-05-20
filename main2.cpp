
	#include "stm32f10x.h" // Device header
 int raw;
 int main()
 {
	 
 RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	ADC1->SMPR2 |= 0b111;
	ADC1->SQR3 |= (0 << 0);
	
	ADC1->CR2 |= ADC_CR2_CONT;
	ADC1->CR2 |= ADC_CR2_ADON;
	
	ADC1->CR2 |= ADC_CR2_RSTCAL;
	while (ADC1->CR2 & ADC_CR2_RSTCAL);
	ADC1->CR2 |= ADC_CR2_CAL;
	while (ADC1->CR2 & ADC_CR2_CAL);
	
	ADC1->CR2 |= ADC_CR2_ADON;
	
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 /*
 
 #include "stm32f10x.h"  // Device header

int raw;

int main()
{
    // Step 1: Enable ADC1 Clock and GPIOA clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;  // Enable ADC1 clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // Enable GPIOA clock (assuming A0 is used)

    // Step 2: Configure the ADC clock prescaler (optional)
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;   // Set ADC clock to 12 MHz (recommended max is 14 MHz)

    // Step 3: Set Sampling Time for Channel 0 (A0)
    ADC1->SMPR2 |= 0b111;  // Set sampling time (111 for the maximum sampling time)

    // Step 4: Configure the ADC sequence
    ADC1->SQR3 |= (0 << 0);  // Set channel 0 to be the first channel in the conversion sequence

    // Step 5: Reset ADC Calibration and Start Calibration
    ADC1->CR2 |= ADC_CR2_RSTCAL;   // Start calibration reset
    while (ADC1->CR2 & ADC_CR2_RSTCAL);  // Wait for the reset calibration to complete

    ADC1->CR2 |= ADC_CR2_CAL;    // Start the calibration
    while (ADC1->CR2 & ADC_CR2_CAL);  // Wait for calibration to finish

    // Step 6: Enable ADC in Continuous Conversion Mode and turn ADC on
    ADC1->CR2 |= ADC_CR2_CONT;    // Enable continuous conversion mode
    ADC1->CR2 |= ADC_CR2_ADON;    // Turn on the ADC (ADC ready for conversion)

    // Step 7: Start Conversion
    while (1)
    {
        // Step 8: Wait for End of Conversion (EOC) bit to be set
        while (!(ADC1->SR & ADC_SR_EOC));  // Wait until EOC flag is set (End of Conversion)

        // Step 9: Read the raw ADC value from the ADC Data Register (DR)
        raw = ADC1->DR;  // Read the 12-bit result from the ADC Data Register
    }
}

 
 */
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

	