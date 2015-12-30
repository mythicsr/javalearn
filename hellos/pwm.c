/*
*ѧ��3113002642
*оƬSTC12c5a
*���̸���
*����������pwm��ʽ    T0 8λ�Զ�װ��  1T     ��ʽ:  PWMƵ��=T0�����/256
*2015-12-24
*/

#include "D:\51soft\C51\INC\stc12c5a.h"
#include "D:\51soft\C51\INC\intrins.h"


#define uint unsigned int
#define uchar unsigned char


#define true 1
#define false 0

uchar isPressed = 0;//1~7������״̬
uchar isPlay = 0;//����״̬
uchar keyValue;//��������
uchar add;//���� ��ǿ/����
#define M 0 //����
#define L 7 //����
#define H 14 //����

//ͨ������ó�21��������Ӧ��T0���ֵ
code uchar T0value[]={0,
0xAD,0xB3,0xBF,0xC2,0xC9,0xCF,0xD4,
0x5B,0x6D,0x7D,0x84,0x92,0x9E,0xA9,
0xD7,0xDB,0xDF,0xE1,0xE4,0xE7,0xEA
};


void test(uchar);
uchar invalidPress();
void delay(uint z);//ms
void Timer0Init(void);	//T0 1T 8λ�Զ�@11.0592Mhz
void PwmInit();
void PwmStart();
void PwmStop();
void keySetting(uchar key);
void KeyScan();
void PlayCtrl();
uchar invalidPress();//��Ч��ϼ��



void main()
{
	uint i = 0;
  Timer0Init();
	PwmInit();
	while (1)
	{
		KeyScan();
		PlayCtrl();
	}
}


void delay(uint z)//ms
{
	uint x,y;
	for(x=z; x>0; x--)
		for(y=113; y>0; y--);
}

void Timer0Init(void)	//T0 1T 8λ�Զ�@11.0592Mhz
{
	AUXR |= 0x80;
	TMOD &= 0xF0;
	TMOD |= 0x02;
	TH0 = TL0 = 91;
	TF0 = 0;
}

void PwmInit(){
	CCON = 0;                       //��ʼ��PCA���ƼĴ���

	CL = 0;                         //
	CH = 0;
	CMOD = 0x04;                    //����PCAʱ��Դ���ö�ʱ��T0���� ��ʽ:  PWMƵ��=T0�����/256
																			//Disable PCA timer overflow interrupt
	CCAP0H = CCAP0L = 0x80;         //����Pwm����ڵ�ռ�ձ�Ϊ50%
	CCAPM0 = 0x42;

	TR0 = 1;						//������ʱ��T0��ΪPWM�ṩʱ��
	CR = 0;							//��ʹ�ر�PWM����
}

//��������
void PwmStart()
{
	CR = 1;
}

//ֹͣ����
void PwmStop()
{
	CR = 0;
}

//��������
void keySetting(uchar key)
{
	TH0 = TL0 = key;
}


void KeyScan()//��ⰴ������ȷ��isPressed isPlay ״̬ �Լ� ����ֵ
{


	if(invalidPress())
	{
		isPressed = 0;
		isPlay = 0;
	}

	else//����ʱ
	{
		P3 = 0x7F;//���1~4
		delay(1);//��ʱ��֤P3�Ѿ�����ֵ
		switch(P3&0x0F)
		{
			case 0x07:keyValue=1;isPressed=1;;break;
			case 0x0b:keyValue=2;isPressed=1;;break;
			case 0x0d:keyValue=3;isPressed=1;;break;
			case 0x0e:keyValue=4;isPressed=1;;break;
			default:break;
		}

		if(!isPressed)//��û�а�1~4���������5~7
		{
			P3 = 0xBF;//���5~7
			delay(1);//��ʱ��֤P3�Ѿ�����ֵ
			switch(P3&0x0F)
			{
				case 0x07:keyValue=5;isPressed=1;break;
				case 0x0b:keyValue=6;isPressed=1;break;
				case 0x0d:keyValue=7;isPressed=1;break;
				default:break;
			}
		}

		if(isPressed)//��1~7�а�����������H��L�� �������������Ϳ�������״̬isPlay
		{
			P3 = 0xEF;
			delay(1);//��ʱ��֤P3�Ѿ�����ֵ
			switch(P3&0x0F)
			{
				case 0x07:add=L;break;
				case 0x0b:add=H;break;
				default:	add=M;break;
			}

			keySetting(T0value[keyValue+add]);
			isPlay=1;
		}
	}
}

uchar invalidPress()//��Ч��ϼ��()
{
	P3=0x3F;//1~7������ʣ�ఴ������ʱ
	if(P3==0x3F)
	{
		delay(10);
		if(P3==0x3F)
		{
			P3=0xCF;
			if(P3!=0xCF)
				delay(2);
				if(P3!=0xCF)
					return true;
		}
	}

	P3 = 0x0F;//������ʱ
	if(P3==0x0F)
	{
		delay(10);
		if(P3==0x0F)
			return true;
	}

	return false;
}



void PlayCtrl()//����isPlay״̬ �� ���Ʋ���/ֹͣ
{
	if(isPlay)
	{
		PwmStart();
	}
	else
	{
		PwmStop();
	}
}






















