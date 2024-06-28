#include<reg51.h>
#include<string.h>
#define lcd P1
#define input P0

sbit rd=P2^4;
sbit wr=P2^3;
sbit intr=P2^2;
sbit rs=P2^5;
sbit rw=P2^6;
sbit e=P2^7;

void delay (unsigned int);
void cmd (unsigned char);
void ldata (unsigned char);
unsigned int adc();
void string (char *c);

void delay (unsigned int d)
{
    unsigned int i;
    for(;d>0;d--)
    {
        for(i=250;i>0;i--);
    }
}

void cmd (unsigned char c)
{
    lcd=c;
    rs=0;
    rw=0;
    e=1;
    delay(5);
    e=0;
}

void ldata (unsigned char c)
{
    lcd=c;
    rs=1;
    rw=0;
    e=1;
    delay(5);
    e=0;
}

unsigned int adc()
{
    unsigned int adc=0x00;
    rd=1;
    wr=0;
    delay(10);
    wr=1;
    while(intr==1);
    rd=0;
    intr=1;
    delay(10);
    adc=input;
    return(adc);
}

void string (char *c)
{
    while (*c)
    {
        ldata (*c++);
    }
}

void printWithDelay(char *c, int d)
{
	cmd(0x38);
	cmd(0x0c);
	cmd(0x01);
	cmd(0x80);
	
	string(c);
	delay(d);
}

void animate(char *carr, int size) 
{
	if (size < 15) {
		printWithDelay(carr, 200);
	} else {
		int i=0;
		while (i<size) {
		 	char temp[15];
			int j;
			int k;
			for (j=i, k=0; j<i+15; j++, k++) {
			 	temp[k] = carr[j];
				
			}
			printWithDelay(temp, 25);
			i+=1;
		}
	}
}

void main()
{

	char dat[54] = "Digital Thermometer by Abdul Rehman and Abdullah - DLD";

    int i=0, j=0;
	unsigned char x3;
	unsigned char tmpAdcData;
	

	animate(dat, 54);
	

	while (1)
	{
	 	delay(10);
		cmd(0x80);
		input=0xff;
		string("temp:");
		cmd(0x85);
		tmpAdcData=adc();
		ldata((tmpAdcData/1000)+(0x30)); // Separate buts and print
		tmpAdcData = tmpAdcData%1000;
		ldata((tmpAdcData/100)+(0x30));
		tmpAdcData = tmpAdcData%100;
		ldata((tmpAdcData/10)+(0x30));
		tmpAdcData = tmpAdcData%10;
		ldata((tmpAdcData/10)+(0x30));
		x3=0xDF;
		ldata(x3);
		string("c");
	}
}
