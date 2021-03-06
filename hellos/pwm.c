/*
*学号3113002642
*芯片STC12c5a
*键盘钢琴
*发声方法：pwm方式    T0 8位自动装载  1T     公式:  PWM频率=T0溢出率/256
*2015-12-24
*/

#include "D:\51soft\C51\INC\stc12c5a.h"
#include "D:\51soft\C51\INC\intrins.h"


#define uint unsigned int
#define uchar unsigned char


#define true 1
#define false 0

uchar isPressed = 0;//1~7键按下状态
uchar isPlay = 0;//播放状态
uchar keyValue;//基础音调
uchar add;//音调 加强/减弱
#define M 0 //中音
#define L 7 //低音
#define H 14 //高音

//通过计算得出21种音调对应的T0溢出值
code uchar T0value[]={0,
0xAD,0xB3,0xBF,0xC2,0xC9,0xCF,0xD4,
0x5B,0x6D,0x7D,0x84,0x92,0x9E,0xA9,
0xD7,0xDB,0xDF,0xE1,0xE4,0xE7,0xEA
};


void test(uchar);
uchar invalidPress();
void delay(uint z);//ms
void Timer0Init(void);	//T0 1T 8位自动@11.0592Mhz
void PwmInit();
void PwmStart();
void PwmStop();
void keySetting(uchar key);
void KeyScan();
void PlayCtrl();
uchar invalidPress();//无效组合检测



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

void Timer0Init(void)	//T0 1T 8位自动@11.0592Mhz
{
	AUXR |= 0x80;
	TMOD &= 0xF0;
	TMOD |= 0x02;
	TH0 = TL0 = 91;
	TF0 = 0;
}

void PwmInit(){
	CCON = 0;                       //初始化PCA控制寄存器

	CL = 0;                         //
	CH = 0;
	CMOD = 0x04;                    //配置PCA时钟源采用定时器T0产生 公式:  PWM频率=T0溢出率/256
																			//Disable PCA timer overflow interrupt
	CCAP0H = CCAP0L = 0x80;         //设置Pwm输出口的占空比为50%
	CCAPM0 = 0x42;

	TR0 = 1;						//启动定时器T0，为PWM提供时钟
	CR = 0;							//先使关闭PWM功能
}

//播放声音
void PwmStart()
{
	CR = 1;
}

//停止播放
void PwmStop()
{
	CR = 0;
}

//设置音调
void keySetting(uchar key)
{
	TH0 = TL0 = key;
}


void KeyScan()//检测按键，并确定isPressed isPlay 状态 以及 音调值
{


	if(invalidPress())
	{
		isPressed = 0;
		isPlay = 0;
	}

	else//按下时
	{
		P3 = 0x7F;//检测1~4
		delay(1);//延时保证P3已经被赋值
		switch(P3&0x0F)
		{
			case 0x07:keyValue=1;isPressed=1;;break;
			case 0x0b:keyValue=2;isPressed=1;;break;
			case 0x0d:keyValue=3;isPressed=1;;break;
			case 0x0e:keyValue=4;isPressed=1;;break;
			default:break;
		}

		if(!isPressed)//若没有按1~4，继续检查5~7
		{
			P3 = 0xBF;//检测5~7
			delay(1);//延时保证P3已经被赋值
			switch(P3&0x0F)
			{
				case 0x07:keyValue=5;isPressed=1;break;
				case 0x0b:keyValue=6;isPressed=1;break;
				case 0x0d:keyValue=7;isPressed=1;break;
				default:break;
			}
		}

		if(isPressed)//若1~7有按下则继续检查H、L， 并且配置音调和开启播放状态isPlay
		{
			P3 = 0xEF;
			delay(1);//延时保证P3已经被赋值
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

uchar invalidPress()//无效组合检测()
{
	P3=0x3F;//1~7不按且剩余按键按下时
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

	P3 = 0x0F;//都不按时
	if(P3==0x0F)
	{
		delay(10);
		if(P3==0x0F)
			return true;
	}

	return false;
}



void PlayCtrl()//监视isPlay状态 并 控制播放/停止
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























