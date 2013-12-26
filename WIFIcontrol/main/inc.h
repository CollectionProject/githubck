#ifndef __INC__H__
#define __INC__H__

#define __LXHZ__
//#define __AD_HOC__

#define INPUT_0_PIN  ((GPIOB->IDR&(1<<5)) != 0)//0 PB5
#define INPUT_1_PIN  ((GPIOA->IDR&(1<<12)) != 0)// 1 pa12
#define INPUT_2_PIN  ((GPIOC->IDR&(1<<7)) != 0)//  2 pc7
#define INPUT_3_PIN  ((GPIOA->IDR&(1<<11)) != 0)//  3 pa11
#define INPUT_4_PIN  ((GPIOC->IDR&(1<<6)) != 0)//  4 pc6
#define INPUT_5_PIN  ((GPIOA->IDR&(1<<8)) != 0)//  5 pa8
#define INPUT_6_PIN  ((GPIOB->IDR&(1<<15)) != 0)//  6 pb15
#define INPUT_7_PIN  ((GPIOB->IDR&(1<<6)) != 0)//  7 pB6
#endif
