/* ADT7301 Digital Temperature Sensor .
 *	Simple demo for SPI modules in BBBio library ,	Read temperature per second .
 *
 *	1. Please check the PIN status of SPI-1 in BBB , if your PIN status not in SPI mode ,
 *		 please follow "overlay" step in README.md to load BBBIO-SPI1 .
 *
 *	2. CircuitLayout in Demo/Demo_ADT7301/CircuitLayout_ADT7301.png
 */
/* ----------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include "../../BBBio_lib/BBBiolib.h"
/* ------------------------------------------------------------------------ */
int main(void)
{
    int Rx_temp = 0;
    int i = 0;

    iolib_init();

    //	if(BBBIO_McSPI_Enable(BBBIO_McSPI_SPI1)) {
    if(BBBIO_McSPI_Enable(BBBIO_McSPI_SPI0)) {
	BBBIO_McSPI_channel_ctrl(BBBIO_McSPI_SPI0 ,
				 //       BBBIO_McSPI_channel_ctrl(BBBIO_McSPI_SPI1 ,
				 BBBIO_McSPI_CH0 ,
				 BBBIO_McSPI_Master ,
				 //		BBBIO_McSPI_Rx_Only ,		
				 BBBIO_McSPI_TxRx ,		
				 //		 BBBIO_McSPI_CLDIV_32 ,		/* 48Mhz div 32 as SPI speed */
				 BBBIO_McSPI_CLDIV_1 ,		/* 48Mhz div 1 as SPI speed */
				 BBBIO_McSPI_CLK_MODE3 ,		/* CLK active low and sampling occurs on the rising edge */
				 BBBIO_McSPI_EN_ACT_LOW ,	/* CS/En pin low when active */
				 //	 BBBIO_McSPI_D0O_D1I ,		/* data0 output , data1 input */
			       BBBIO_McSPI_D0I_D1O ,		/* data0 output , data1 input */
				 //16);				/* 16 bit TxRx per work */
				 32);				/* 32 bit TxRx per work */

	for(i = 0 ; i < 5 ; i++) {
	    int tx = 0x08154711;
	    Rx_temp=0;
	    //			BBBIO_McSPI_work(BBBIO_McSPI_SPI1, BBBIO_McSPI_CH0, &tx, &Rx_temp);
	    int rc = BBBIO_McSPI_work(BBBIO_McSPI_SPI0, BBBIO_McSPI_CH0, tx, &Rx_temp);
	    // Rx_temp &= 0x0FFFF;
	    printf("rc=%d MCSPI_RX0 , Raw : %X \n", rc, Rx_temp);
	    sleep(1);
	}
	//	BBBIO_McSPI_Disable(BBBIO_McSPI_SPI1);
	BBBIO_McSPI_Disable(BBBIO_McSPI_SPI0);
    }
    else {
	printf("McSPI init failed\n");
    }
    iolib_free();
    return 0 ;
}
