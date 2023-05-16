
#define GPX1CON      *(volatile unsigned int*)0x11000C20
#define EXT_INT41CON *(volatile unsigned int*)0x11000E04
#define EXT_INT41_MASK *(volatile unsigned int*)0x11000F04
#define EXT_INT41_PEND *(volatile unsigned int*)0x11000F44

#define ICCICR_CPU0  *(volatile unsigned int*)0x10480000
#define ICCPMR_CPU0  *(volatile unsigned int*)0x10480004
#define ICCIAR_CPU0  *(volatile unsigned int*)0x1048000c
#define ICCEOIR_CPU0 *(volatile unsigned int*)0x10480010

#define ICDDCR *(volatile unsigned int*)0x10490000
#define ICDISER1_CPU0 *(volatile unsigned int*)0x10490104
#define ICDICPR1_CPU0 *(volatile unsigned int*)0x10490284
#define ICDIPR14_CPU0 *(volatile unsigned int*)0x10490438
#define ICDIPTR14_CPU0 *(volatile unsigned int*)0x10490838

void do_irq()
{
    int id = ICCIAR_CPU0;
    uart_send('S');    
    EXT_INT41_PEND = EXT_INT41_PEND | (0x1<<1);
    ICDICPR1_CPU0 = ICDICPR1_CPU0 | 0x1<<25;
    ICCEOIR_CPU0 = id;
}

void key_init()
{
    GPX1CON = GPX1CON | (0xf<<4);
    EXT_INT41CON = EXT_INT41CON & ~(0x7<<4) | (0x2<<4);
    EXT_INT41_MASK = EXT_INT41_MASK & ~(0x1<<1);
}

void gic_init()
{
    //distributor
    ICDDCR = 0x1;
    ICDISER1_CPU0 = ICDISER1_CPU0 | 0x1<<25;
    ICDIPR14_CPU0 = ICDIPR14_CPU0 & ~(0xff<<8);
    ICDIPTR14_CPU0 = ICDIPTR14_CPU0 & ~(0xff<<8) | (0x1<<8);

    //cpu interface
    ICCICR_CPU0 = 0x1;
    ICCPMR_CPU0 = 0xff;
}

void main(void)
{
    gic_init();
	uart_init();
    key_init();
    uart_str("begin\n");    
    while(1)
	{
         mydelay();
	}
	return;
}

