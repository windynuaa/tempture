#define GATE_LEN 5
#define KEY_BAK 15
void keyboard_init()
{



}

char get_keyboard()
{


	
}

void set_alarm(int *gate)
{
	int a,count;
	char b=1;
	a=0;
	count=0;
	while(count<GATE_LEN)
	{
		b=get_keyboard();
		a+=b;
		a*=10;
		count++;
	}
	*gate=a;
}