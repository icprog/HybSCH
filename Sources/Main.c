#include "./Headers/PreMacro.h"
#include "./Headers/HybSCH.h"

//�ǵ�ȥ����SCH_MAX_TASKS ��HybSCH.h�ļ���

//����IO�ڵĻ���
#define LOCKED (bit)1
#define UNLOCKED (bit)0
#define LED_PORT P1

sbit LED = P1 ^ 0;
static bit led_lock = UNLOCKED;

void led_short_flash(void){
	if(led_lock == LOCKED){
		return;
	}
	led_lock = LOCKED;
	LED = ~LED;
	led_lock = UNLOCKED;
}

void led_long_flash(void){
	static u8 i = 0;
	if(led_lock==LOCKED){
		return;
	}
	led_lock = LOCKED;
	for(i=0;i<3;++i){

		LED_PORT = 0xf0;
		hard_delay_ms(500);
		LED_PORT = 0x0f;
		hard_delay_ms(500);
	}
	led_lock = UNLOCKED;
}

void main(void)
{
    hsch_init_timmer2();
	
	//led_short_flash ����ռ��ʽ���У�����Ϊ1s
	hsch_add_task(led_short_flash,0,1000,0);

	//led_long_flash �Ժ�����ʽ���У�����Ϊ20s
    hsch_add_task(led_long_flash, 0, 20000, 1);

    hsch_start();
    while(true)
    {
        hsch_dispatch_tasks();
    }
}