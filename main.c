#include <stdio.h>
#include <pthread.h>
#include "touch.h"
#include "lcd.h"
#include "bmp.h"
#include "game.h"




int main()
{
    /*屏幕初始化*/
    lcd_init();

    //显示开始游戏按钮
    lcd_start_button();
    //下黑棋和白棋
    get_blackandwhite();
    //解除映射和关闭文件
    lcd_uninit();
    return 0; 
}