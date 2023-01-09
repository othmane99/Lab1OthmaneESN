#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include <stdint.h>
#include "unistd.h"

int main()
{
	uint16_t leds;
	
	// Récupère l'état des switchs 0 à 9
	uint16_t switchs = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE);
	// Allume les leds en fonction de l'état des switchs 0 à 9
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, switchs);
	
	while (1)
	{
		// Récupère l'état des switchs 0 à 9
		uint16_t speed = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE); 
		// Modifie la vitesse de défilement du chenillard en fonction de l'état des switchs 0 à 9
		usleep(1000*speed);
		// Récupère l'état des leds 0 à 9
		leds = IORD_ALTERA_AVALON_PIO_DATA(PIO_1_BASE);
		
		// Fait avancer le chenillard
		if (leds == 0x200)
		{
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, switchs);
		}
		else
		{
			if (leds & 0x0200)
			{
				IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, (leds<<1) + 0x1);
			}
			else
			{
				IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, (leds<<1));
			}
		}
	}	
	return 0;
}