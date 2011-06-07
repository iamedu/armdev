#include <at91/dbgu.h>
#include <at91/devices.h>

/* Write DBGU register */
static inline void write_dbgu(unsigned int offset, const unsigned int value)
{
	writel(value, offset + DBGU_BASE);
}

/* Read DBGU registers */
static inline unsigned int read_dbgu( unsigned int offset)
{
	return readl(offset + DBGU_BASE);
}


//*----------------------------------------------------------------------------
//* \fn    dbg_init
//* \brief This function is used to configure the DBGU COM port
//*----------------------------------------------------------------------------*/
void dbg_init(unsigned int baudrate)
{
	/* Disable interrupts */
	write_dbgu(US_IDR, -1);
	/* Reset the receiver and transmitter */
	write_dbgu(US_CR, AT91C_US_RSTRX | AT91C_US_RSTTX | AT91C_US_RXDIS  | AT91C_US_TXDIS);
	/* Configure the baudrate */
	write_dbgu(US_BRGR, baudrate);
	/* Configure USART in Asynchronous mode */
	write_dbgu(US_MR, AT91C_US_PAR);
	/* Enable RX and Tx */
	write_dbgu(US_CR, AT91C_US_RXEN | AT91C_US_TXEN);
}

//*----------------------------------------------------------------------------
//* \fn    dbg_print
//* \brief This function is used to configure the DBGU
//*----------------------------------------------------------------------------*/

void dbg_putch(char c) {
	while ( !(read_dbgu(DBGU_CSR) & AT91C_US_TXRDY) );
	write_dbgu(DBGU_THR, c);
}

void dbg_print(const char *ptr)
{
	int i=0;

	while (ptr[i] != '\0') {
		while ( !(read_dbgu(DBGU_CSR) & AT91C_US_TXRDY) );
		write_dbgu(DBGU_THR, ptr[i]);
		i++;
	}
}

