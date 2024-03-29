/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#include<stdio.h>
#include<stdint.h>
/*
struct Packet
{
	uint8_t		crc;
	uint8_t		status;
	uint16_t	payload;
	uint8_t		bat;
	uint8_t		sensor;
	uint8_t		longAddr;
	uint8_t		shortAddr;
	uint8_t		addrMode;
};*/

int sizes(void);

/*int led(void);

int led_shift(void);

int readPin(void);

void padding(void);*/

void keyPad(void);
void delay(void);
void strings(void);

int main(void)
{

	sizes();

	return 0;

}

void strings(void)
{
	char msg1[] = "Hello how are you?";
	char const *pmsg2 = "fastbitlab.com"; // the best way is to make it const because the pointer is pointing to the variable stored in FLASH


	printf("Message is: %s\n", msg1);
	printf("Message 2 is: %s\n", pmsg2);
	printf("Address of 'msg1' variable = %p\n", &msg1);
	printf("Address of 'msg2' variable = %p\n", &pmsg2);
	printf("Value of 'msg1' variable = %p\n", msg1);
	printf("Value of 'msg2' variable = %p\n", pmsg2);


	for(;;);
}

void delay(void)
{
	for(uint32_t i=0; i<300000; i++);
}
/*
*	Keypad exercise
*/
void keyPad(void)
{
	uint32_t volatile * const 		RCC_AHB1ENR	= (uint32_t*)0x40023830;	// Address of the AHB1 peripheral bus clock enable register 0x40020800 + 0x30
	uint32_t volatile * const		GPIOC_MODER	= (uint32_t*)0x40020800;	// Address of the GPIOC mode register
	uint32_t volatile * const		GPIOC_PUPDR	= (uint32_t*)0x4002080C;	// Address of the GPIOC mode register + 0x0C
	uint32_t volatile * const		GPIOC_IDR	= (uint32_t*)0x40020810;	// Address of the GPIOC mode register + 0x10
	uint32_t volatile * const		GPIOC_ODR	= (uint32_t*)0x40020814;	// Address of the GPIOC mode register + 0x14

	/* Enables the GPIOC peripheral clock by setting bit 2 of RCC_AHB1ENR */
	*RCC_AHB1ENR |= (1 << 2);

	/* Configures the GPIOC pins 0-3 as General Purpose output */
	*GPIOC_MODER |= (0x55);

	/* Configures the GPIOC pins 10-12 as General Purpose inputs */
	*GPIOC_MODER &= ~(0x3F << 20);

	/* Enable internal pull up resistors for 10-12 */
	*GPIOC_PUPDR |= (0x15 << 20);

	while(1)
	{
		uint8_t col = 1;

		for(uint8_t row = 0; row <=3; row ++)
		{
			/* Make all rows high */
			*GPIOC_ODR |= 0x0F;

			/* Make R1 Low PC10*/
			*GPIOC_ODR &= ~(1 << row);

			/* Scan the columns */
			/* Check for PC10 */
			if(! (*GPIOC_IDR & (1 << 10)) )
			{
				delay();
				printf("%u\n", col);
			}
			col++;
			if(! (*GPIOC_IDR & (1 << 11)) )
			{
				delay();
				printf("%u\n", col);
			}
			col++;
			if(! (*GPIOC_IDR & (1 << 12)) )
			{
				delay();
				printf("%u\n", col);
			}
			col++;
		}
	}
}


/*
*	Padding example
*//*
void padding(void)
{
	uint32_t	packetValue;
	printf("Enter the 32bit packet value: ");
	scanf("%X", &packetValue);

	struct Packet packet;

	packet.crc 			= (uint8_t)(packetValue & 0x3);
	packet.status		= (uint8_t)((packetValue >> 2) & 0x1);
	packet.payload		= (uint16_t)((packetValue >> 3) & 0xFFF);
	packet.bat			= (uint8_t)((packetValue >> 15) & 0x7);
	packet.sensor		= (uint8_t)((packetValue >> 18) & 0x7);
	packet.longAddr		= (uint8_t)((packetValue >> 21) & 0xFF);
	packet.shortAddr	= (uint8_t)((packetValue >> 29) & 0x3);
	packet.addrMode		= (uint8_t)((packetValue >> 31) & 0x1);

	printf("crc			: %#x \n",	packet.crc);
	printf("status		: %#x \n",	packet.status);
	printf("payload		: %#x \n",	packet.payload);
	printf("bat			: %#x \n",	packet.bat);
	printf("sensor		: %#x \n",	packet.sensor);
	printf("longAddr	: %#x \n",	packet.longAddr);
	printf("shortAddr	: %#x \n",	packet.shortAddr);
	printf("addrMode	: %#x \n",	packet.addrMode);
}*/

/*
*	Read GPIOA0 to control GPIOA5
*/
/*int readPin(void)
{
	uint32_t volatile * const 		RCC_AHB1ENR	= (uint32_t*)0x40023830;	// Address of the AHB1 peripheral bus clock enable register
	uint32_t volatile * const 		GPIOA_MODER	= (uint32_t*)0x40020000;	// Address of the GPIOA mode register
	uint32_t volatile * const		GPIOC_MODER	= (uint32_t*)0x40020800;	// Address of the GPIOC mode register
	uint32_t volatile * const 		GPIOA_ODR	= (uint32_t*)0x40020014;	// Address of the GPIOA output data register
	uint32_t const volatile	* const	GPIOC_IDR	= (uint32_t*)0x40020810;	// Address of the GPIOC input data register

	// Enables the GPIOA peripheral clock by setting bit 0 of RCC_AHB1ENR
	*RCC_AHB1ENR |= (1 << 0);
	// Enables the GPIOC peripheral clock by setting bit 2 of RCC_AHB1ENR
	*RCC_AHB1ENR |= (1 << 2);

	// Configures the GPIOA pin 5 as General Purpose output mode
	*GPIOA_MODER |= (1 << 10);

	// Configures the GPIOC pin 0 as General Purpose input mode by clearing first 2 bits
	*GPIOC_MODER &= ~(3 << 0);

	do{
		uint8_t pinStatus = (uint8_t)(*GPIOC_IDR & 0x1);

		if( pinStatus )
		{
			// Writes 1 to pin 5 only of the output data register so the LED is turned on
				*GPIOA_ODR |= (1 << 5);
		}else{
			// Writes 0 to pin 5 only of the output data register so the LED is turned off
				*GPIOA_ODR &= ~(1 << 5);
			}

	}while(1);

	return 0;
}*/

/*
*	Control GPIOA bit 5 to turn LED on
*/
/*
int led_shift(void)
{
	uint32_t * RCC_AHB1ENR	= (uint32_t*)0x40023830;	// Address of the AHB1 peripheral bus clock enable register
	uint32_t * GPIOA_MODER	= (uint32_t*)0x40020000;	// Address of the GPIOA mode register
	uint32_t * GPIOA_ODR	= (uint32_t*)0x40020014;	// Address of the GPIOA output data register
	uint8_t	   x			= 0;

	// Enables the GPIOA peripheral clock by setting bit 0 of RCC_AHB1ENR
	*RCC_AHB1ENR |= (1 << 0);

	// Configures the GPIOA pin 5 as General Purpose output mode
	*GPIOA_MODER |= (1 << 10);

	do{

		// Writes 1 to pin 5 only of the output data register so the LED is turned on
		for(uint32_t c=0; c<=30000; c++)
			*GPIOA_ODR |= (1 << 5);

		// Writes 0 to pin 5 only of the output data register so the LED is turned off
		for(uint32_t c=0; c<=30000; c++)
			*GPIOA_ODR &= ~(1 << 5);

		x++;

	}while(x<20);

	return 0;
}*/

/*
*	Control GPIOA bit 5 to turn LED on
*/
/*
int led(void)
{
	uint32_t * RCC_AHB1ENR	= (uint32_t*)0x40023830;	// Address of the AHB1 peripheral bus clock enable register
	uint32_t * GPIOA_MODER	= (uint32_t*)0x40020000;	// Address of the GPIOA mode register
	uint32_t * GPIOA_ODR	= (uint32_t*)0x40020014;	// Address of the GPIOA output data register
	uint8_t	   x			= 0;

	// Enables the GPIOA peripheral clock by setting bit 0 of RCC_AHB1ENR
	*RCC_AHB1ENR |= 0x0001;

	// Configures the GPIOA pin 5 as General Purpose output mode
	*GPIOA_MODER |= 0x0400;

	do{

		// Writes 1 to pin 5 only of the output data register so the LED is turned on
		for(uint32_t c=0; c<=30000; c++)
			*GPIOA_ODR |= 0x0020;
		// Writes 0 to pin 5 only of the output data register so the LED is turned off
		for(uint32_t c=0; c<=30000; c++)
			*GPIOA_ODR &= 0xFFDF;

		x++;

	}while(x<20);

	return 0;
}*/


int sizes(void)
{


	printf("Size of CHAR \t\t= %u byte(s)\n",  	 sizeof(char) );
	printf("Size of SHORT \t\t= %u byte(s)\n", 	 sizeof(short) );
	printf("Size of INT \t\t= %u byte(s)\n",   	 sizeof(int) );
	printf("Size of LONG \t\t= %u byte(s)\n",  	 sizeof(long) );
	printf("Size of LONG LONG \t= %u byte(s)\n", sizeof(long long) );
	printf("Size of DOUBLE \t\t= %u byte(s)\n", sizeof(double) );


	return 0;
}
