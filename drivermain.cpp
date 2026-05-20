#include "stm32f10x.h"                  // Ukljucivanje zaglavlja za STM32F10x
#include "driver.h"               // Ukljucivanje drajvera zadatka

void pinMode(uint16_t pinNumber, uint16_t Mode) {
    // Aktivacija clock-a za odgovarajuci port
    if (pinNumber < 16) {
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Aktivacija clock-a za GPIOA
    } else if (pinNumber < 32) {
        RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Aktivacija clock-a za GPIOB
    } else if (pinNumber < 48) {
        RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Aktivacija clock-a za GPIOC
    } else {
        return; // Ako je broj pina nevalidan, izlaz iz funkcije
    }

    uint8_t pin = pinNumber % 16; // Odredivanje tacnog pina unutar porta

    // Konfiguracija moda pina
    if (Mode == OUTPUT) {
        // Konfiguracija za GPIOA
        if (pinNumber < 16) {
            if (pin < 8) {
                GPIOA->CRL &= ~(15 << (pin * 4)); // Resetovanje bita konfiguracije
                GPIOA->CRL |= (3 << (pin * 4));  // Postavljanje moda izlaza
            } else {
                GPIOA->CRH &= ~(15 << ((pin - 8) * 4));
                GPIOA->CRH |= (3 << ((pin - 8) * 4));
            }
        // Konfiguracija za GPIOB
        } else if (pinNumber < 32) {
            if (pin < 8) {
                GPIOB->CRL &= ~(15 << (pin * 4));
                GPIOB->CRL |= (3 << (pin * 4));
            } else {
                GPIOB->CRH &= ~(15 << ((pin - 8) * 4));
                GPIOB->CRH |= (3 << ((pin - 8) * 4));
            }
        // Konfiguracija za GPIOC
        } else {
            if (pin < 8) {
                GPIOC->CRL &= ~(15 << (pin * 4));
                GPIOC->CRL |= (3 << (pin * 4));
            } else {
                GPIOC->CRH &= ~(15 << ((pin - 8) * 4));
                GPIOC->CRH |= (3 << ((pin - 8) * 4));
            }
        }
    } else if (Mode == INPUT) {
        // Konfiguracija za GPIOA
        if (pinNumber < 16) {
            if (pin < 8) {
                GPIOA->CRL &= ~(15 << (pin * 4));
                GPIOA->CRL |= (8 << (pin * 4));  // Postavljanje moda ulaza
            } else {
                GPIOA->CRH &= ~(15 << ((pin - 8) * 4));
                GPIOA->CRH |= (8 << ((pin - 8) * 4));
            }
        // Konfiguracija za GPIOB
        } else if (pinNumber < 32) {
            if (pin < 8) {
                GPIOB->CRL &= ~(15 << (pin * 4));
                GPIOB->CRL |= (8 << (pin * 4));
            } else {
                GPIOB->CRH &= ~(15 << ((pin - 8) * 4));
                GPIOB->CRH |= (8 << ((pin - 8) * 4));
            }
        // Konfiguracija za GPIOC
        } else {
            if (pin < 8) {
                GPIOC->CRL &= ~(15 << (pin * 4));
                GPIOC->CRL |= (8 << (pin * 4));
            } else {
                GPIOC->CRH &= ~(15 << ((pin - 8) * 4));
                GPIOC->CRH |= (8 << ((pin - 8) * 4));
            }
        }
    }
}

void digitalWrite(uint16_t pinNumber, bool Value) {
    // Postavljanje stanja pina za GPIOA
    if (pinNumber < 16) {
        if (Value == HIGH) {
            GPIOA->ODR |= (1 << pinNumber); // Postavljanje pina na HIGH
        } else {
            GPIOA->ODR &= ~(1 << pinNumber); // Postavljanje pina na LOW
        }
    // Postavljanje stanja pina za GPIOB
    } else if (pinNumber < 32) {
        if (Value == HIGH) {
            GPIOB->ODR |= (1 << (pinNumber - 16));
        } else {
            GPIOB->ODR &= ~(1 << (pinNumber - 16));
        }
    // Postavljanje stanja pina za GPIOC
    } else if (pinNumber < 48) {
        if (Value == HIGH) {
            GPIOC->ODR |= (1 << (pinNumber - 32));
        } else {
            GPIOC->ODR &= ~(1 << (pinNumber - 32));
        }
    }
}

bool digitalRead(uint16_t pinNumber) {
    // Citanje stanja pina za GPIOA
    if (pinNumber < 16) {
        if ((GPIOA->IDR & (1 << pinNumber)) != 0) {
            return HIGH; // Ako je pin HIGH, vraca HIGH
        } else {
            return LOW;  // Inace vraca LOW
        }
    // Citanje stanja pina za GPIOB
    } else if (pinNumber < 32) {
        if ((GPIOB->IDR & (1 << (pinNumber - 16))) != 0) {
            return HIGH;
        } else {
            return LOW;
        }
    // Citanje stanja pina za GPIOC
    } else if (pinNumber < 48) {
        if ((GPIOC->IDR & (1 << (pinNumber - 32))) != 0) {
            return HIGH;
        } else {
            return LOW;
        }
    }
    return LOW; // Ako je pin nevalidan, vraca LOW
}
// ne radi
/*void pinModeAnalogIn() {
    // Omogucavanje ADC1 i konfigurisanje preskalera
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Omogucavanje ADC1
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;  // Podešavanje preskalera na 6

    // Konfigurisanje svih kanala A0 do A7 za ADC
    ADC1->SMPR2 |= 0b111 << (0 * 3);  // Uzorkovanje za A0 (kanal 0)
    ADC1->SMPR2 |= 0b111 << (1 * 3);  // Uzorkovanje za A1 (kanal 1)
    ADC1->SMPR2 |= 0b111 << (2 * 3);  // Uzorkovanje za A2 (kanal 2)
    ADC1->SMPR2 |= 0b111 << (3 * 3);  // Uzorkovanje za A3 (kanal 3)
    ADC1->SMPR2 |= 0b111 << (4 * 3);  // Uzorkovanje za A4 (kanal 4)
    ADC1->SMPR2 |= 0b111 << (5 * 3);  // Uzorkovanje za A5 (kanal 5)
    ADC1->SMPR2 |= 0b111 << (6 * 3);  // Uzorkovanje za A6 (kanal 6)
    ADC1->SMPR2 |= 0b111 << (7 * 3);  // Uzorkovanje za A7 (kanal 7)

    // Inicijalizacija konverzije za sve kanale
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;       // Resetuj SQ1
    ADC1->SQR3 |= 0;                   // Prvi kanal u sekvenci je A0 (kanal 0)
    
    // Ako želimo da imamo više kanala u sekvenci:
    ADC1->SQR3 |= (1 << 5);            // Drugi kanal je A1 (kanal 1)
    ADC1->SQR3 |= (2 << 10);           // Treci kanal je A2 (kanal 2)
    ADC1->SQR3 |= (3 << 15);           // Cetvrti kanal je A3 (kanal 3)
    ADC1->SQR3 |= (4 << 20);           // Peti kanal je A4 (kanal 4)
    ADC1->SQR3 |= (5 << 25);           // Šesti kanal je A5 (kanal 5)
    ADC1->SQR3 |= (6 << 30);           // Sedmi kanal je A6 (kanal 6)

    // Ukljucivanje ADC-a, kontiniusna konverzija
    ADC1->CR2 |= ADC_CR2_CONT;         // Kontinuirana konverzija
    ADC1->CR2 |= ADC_CR2_ADON;         // Aktiviranje ADC-a

    // Resetovanje i kalibracija ADC-a
    ADC1->CR2 |= ADC_CR2_RSTCAL;       // Reset kalibracije
    while (ADC1->CR2 & ADC_CR2_RSTCAL); // Cekaj dok reset kalibracije ne završi
    ADC1->CR2 |= ADC_CR2_CAL;          // Pokretanje kalibracije
    while (ADC1->CR2 & ADC_CR2_CAL);   // Cekaj dok kalibracija ne završi
    
    // Ponovo aktiviraj ADC
    ADC1->CR2 |= ADC_CR2_ADON;
}
*/
// ne radi
uint16_t analogRead() {
    static uint8_t current_channel = 0;

    // Odabir kanala u SQR3 (kanali A0 do A7)
    ADC1->SQR3 &= ~ADC_SQR3_SQ1; // Resetuj SQ1
    ADC1->SQR3 |= (current_channel << 0); // Postavi trenutni kanal u SQ1

    // Pokreni konverziju
    ADC1->CR2 |= ADC_CR2_SWSTART;

    // Cekaj dok konverzija ne bude gotova
    while (!(ADC1->SR & ADC_SR_EOC)); // Cekaj da se pojavi "End of Conversion"

    // Uvecaj kanal za sledece ocitavanje, i vrati na A0 ako prede A7
    current_channel++;
    if (current_channel > 7) {
        current_channel = 0; // Ako je prošao A7, vrati na A0
    }

    // Vratite rezultat konverzije
    return (ADC1->DR);
}




/*
void pinModeAnalogInA0() {
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
*/

// Funkcija za inicijalizaciju A0 za VRX
void pinModeAnalogInA0() {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;  // Omoguci ADC1
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;   // Preskaler na 6 za ADC
    ADC1->SMPR2 |= 0b111;  // Uzorkovanje za A0
    ADC1->SQR3 |= (0 << 0);  // Odaberi kanal 0 (PA0)

    ADC1->CR2 |= ADC_CR2_CONT;  // Kontinuirana konverzija
    ADC1->CR2 |= ADC_CR2_ADON;  // Ukljuci ADC

    // Resetiraj i kalibriraj ADC
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);

    ADC1->CR2 |= ADC_CR2_ADON;  // Ponovo ukljuci ADC
}
/* OVA DOLE RADI 
void pinModeAnalogInA0() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
    GPIOA->CRL &= ~(0xF << (0 * 4));  // PA0 u analogni mod
    ADC1->SMPR2 |= 0b111 << (0 * 3);  // Sample time za kanal 0
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->SQR3 = 0;                   // Kanal 0
    ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_RSTCAL; while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;    while (ADC1->CR2 & ADC_CR2_CAL);
    ADC1->CR2 |= ADC_CR2_ADON;
}
*/
void pinModeAnalogInA1() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
    GPIOA->CRL &= ~(0xF << (1 * 4));  // PA1 u analogni mod
    ADC1->SMPR2 |= 0b111 << (1 * 3);  // Kanal 1
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->SQR3 = 1;  // Kanal 1
    ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_RSTCAL; while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;    while (ADC1->CR2 & ADC_CR2_CAL);
    ADC1->CR2 |= ADC_CR2_ADON;
}

void pinModeAnalogInA2() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
    GPIOA->CRL &= ~(0xF << (2 * 4));
    ADC1->SMPR2 |= 0b111 << (2 * 3);
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->SQR3 = 2;
    ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_RSTCAL; while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;    while (ADC1->CR2 & ADC_CR2_CAL);
    ADC1->CR2 |= ADC_CR2_ADON;
}

void pinModeAnalogInA3() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
    GPIOA->CRL &= ~(0xF << (3 * 4));
    ADC1->SMPR2 |= 0b111 << (3 * 3);
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->SQR3 = 3;
    ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_RSTCAL; while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;    while (ADC1->CR2 & ADC_CR2_CAL);
    ADC1->CR2 |= ADC_CR2_ADON;
}

void pinModeAnalogInA4() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
    GPIOA->CRL &= ~(0xF << (4 * 4));
    ADC1->SMPR2 |= 0b111 << (4 * 3);
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->SQR3 = 4;
    ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_RSTCAL; while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;    while (ADC1->CR2 & ADC_CR2_CAL);
    ADC1->CR2 |= ADC_CR2_ADON;
}

void pinModeAnalogInA5() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
    GPIOA->CRL &= ~(0xF << (5 * 4));
    ADC1->SMPR2 |= 0b111 << (5 * 3);
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->SQR3 = 5;
    ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_RSTCAL; while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;    while (ADC1->CR2 & ADC_CR2_CAL);
    ADC1->CR2 |= ADC_CR2_ADON;
}

void pinModeAnalogInA6() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
    GPIOA->CRL &= ~(0xF << (6 * 4));
    ADC1->SMPR2 |= 0b111 << (6 * 3);
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->SQR3 = 6;
    ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_RSTCAL; while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;    while (ADC1->CR2 & ADC_CR2_CAL);
    ADC1->CR2 |= ADC_CR2_ADON;
}

void pinModeAnalogInA7() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
    GPIOA->CRL &= ~(0xF << (7 * 4));
    ADC1->SMPR2 |= 0b111 << (7 * 3);
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->SQR3 = 7;
    ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_RSTCAL; while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;    while (ADC1->CR2 & ADC_CR2_CAL);
    ADC1->CR2 |= ADC_CR2_ADON;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Funkcija za citanje analognih vrijednosti sa A0
uint16_t analogReadA0() {
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;  // Resetiraj prvi kanal u sekvenci
    ADC1->SQR3 |= (0 << 0);       // Odaberi kanal 0 (PA0)
    ADC1->CR2 |= ADC_CR2_SWSTART; // Pokreni konverziju
    while (!(ADC1->SR & ADC_SR_EOC));  // Cekaj da konverzija završi
    return ADC1->DR;  // Vrati rezultat
}

/* OVA DOL RADI
uint16_t analogReadA0() {
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;         // Resetuj prvi kanal u sekvenci
    ADC1->SQR3 |= (0 << 0);              // Odaberi kanal 0 (PA0)
    ADC1->CR2 |= ADC_CR2_SWSTART;        // Start konverzije
    while (!(ADC1->SR & ADC_SR_EOC));    // Cekaj da konverzija završi
    return ADC1->DR;                     // Vrati rezultat
}
*/

uint16_t analogReadA1() {
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= (1 << 0);
    ADC1->CR2 |= ADC_CR2_SWSTART;
    while (!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}

uint16_t analogReadA2() {
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= (2 << 0);
    ADC1->CR2 |= ADC_CR2_SWSTART;
    while (!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}

uint16_t analogReadA3() {
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= (3 << 0);
    ADC1->CR2 |= ADC_CR2_SWSTART;
    while (!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}

uint16_t analogReadA4() {
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= (4 << 0);
    ADC1->CR2 |= ADC_CR2_SWSTART;
    while (!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}

uint16_t analogReadA5() {
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= (5 << 0);
    ADC1->CR2 |= ADC_CR2_SWSTART;
    while (!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}

uint16_t analogReadA6() {
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= (6 << 0);
    ADC1->CR2 |= ADC_CR2_SWSTART;
    while (!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}

uint16_t analogReadA7() {
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 |= (7 << 0);
    ADC1->CR2 |= ADC_CR2_SWSTART;
    while (!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
