#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
#include "lcd.h"

int* plcd = NULL;//指向帧缓冲的首地址

/*屏幕初始化*/
void lcd_init()
{
    //(1) 打开设备
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1) 
    {
        perror("open /dev/fb0 error");
        return ;
    }
    //(2) 获取屏幕信息

    //(3) int* plcd = mmap
    //   帧缓冲区域按行从左到右,从上到下,保存每个像素点的信息  ARGB 颜色值
    plcd = mmap(NULL,//第一个参数,映射到哪个地址上去,为NULL,系统自行分配
                800*480*4,//第二个参数,映射区域的长度
                PROT_WRITE | PROT_READ,//第三个参数,映射区域的权限
                MAP_SHARED,//第四个参数,映射方式,映射标记,"共享映射"
                lcd_fd,//第五个参数,文件描述符,表示你要映射哪个文件
                0);//第六个参数,文件偏移量,表示你要从哪个位置开始映射
    if (MAP_FAILED == plcd) 
    {
        perror("map /dev/fb0 error\n");
        return ;
    }
}
//解除映射和关闭文件
void lcd_uninit() 
{
    int lcd_fd = open("/dev/fb0", O_RDWR);
    munmap(plcd, 800 * 480 * 4);
    close(lcd_fd);
}

/*
    lcd_draw_point 画点函数，将（x，y）坐标上的像素点显示为color颜色
    @x      像素点的横坐标
    @y      像素点的纵坐标
    @color  像素点的颜色
*/
void lcd_draw_point(int x,int y,int color)
{
    
    if(x >= 0 && x < 800 && y >= 0 && y <= 480)
    {
        *(plcd + 800 * y + x) = color;
    }
}
//清屏
void clear_lcd(int color)
{
    for ( int y = 0; y < 480; y++)
    {
        for ( int x = 0; x < 800; x++)
        {
            lcd_draw_point(x,y,color); 
        }
    }
}


/* 
draw_round ：画圆
参数：
    int x0 ：圆心的X轴
    int y0 ：圆心的Y轴
    int r  ：圆的半径
    int color ：圆的颜色
 */
void draw_round(int x0,int y0,int r,int color)
{
    for ( int y = 0; y < 480; y++)
    {
        for ( int x = 0; x < 800; x++)
        {
            if((x - x0)*(x - x0) +(y - y0)*(y - y0) <= r*r)
            {
                lcd_draw_point(x,y,color); 
            } 
        }
    }
}
/*
    画棋盘背景颜色
    棋盘规格是 480*480
    棋子是11*11
*/

void chess_ground()
{
    for ( int y = 0; y < 480; y++)
    {
        for ( int x = 0; x < 480; x++)
        {
            lcd_draw_point(x,y,0x8b4513); 
        }
        for ( int x = 480; x < 800; x++)
        {
            lcd_draw_point(x,y,0xffffff); 
        }
    }
}
/*
    画棋盘线
    纵坐标每隔40 画一根黑线
    横坐标每隔40 画一根黑线
    用画圆函数
    画一个天元和四个星
*/
void chess_line()
{
    for(int y = 0;y < 480; y++)
    {
        if(y%40 == 0)//纵坐标每隔40 画一根黑线
        {
            for(int x = 0;x < 480;x++)
            {
                lcd_draw_point(x,y,0x000000);
            }
        }
    }

    for(int x = 0;x <= 480; x++)
    {
        if(x%40 == 0)//横坐标每隔40 画一根黑线
        {
            for(int y = 0;y < 480;y++)
            {
                lcd_draw_point(x,y,0x000000);
            }
        }
    }

    for ( int y = 0; y < 480; y++)
    {
        for ( int x = 0; x < 480; x++)
        {
            if((y-80)*(y-80)+(x-80)*(x-80)<=20 || 
            (y-80)*(y-80)+(x-400)*(x-400)<=20 || 
            (y-400)*(y-400)+(x-400)*(x-400)<=20 || 
            (y-400)*(y-400)+(x-80)*(x-80)<=20 ||
            (y-240)*(y-240)+(x-240)*(x-240)<=20)
            lcd_draw_point(x,y,0x000000); //画一个天元和四个星
        }
    }
}

/* 
    black：画黑棋 
    @x0：黑棋圆心横坐标
    @y0：黑棋圆心纵坐标

    返回值：无
 */
void black(int x0, int y0)

{
	for(int y=0; y<=480; y++)
	{
        for(int x=0; x<=800; x++)
		{
			if((x - x0)*(x - x0) + (y - y0)*(y - y0) <= 15*15)//棋子半径为15
			{
				lcd_draw_point(x,y,0x000000);//棋子为黑色
			}
		}
	}
}
 
 /* 
    black：画白棋 
    @x0：白棋圆心横坐标
    @y0：白棋圆心纵坐标

    返回值：无
 */
void white(int x0, int y0)
{
	for(int y=0; y<=480; y++)
	{
        for(int x=0; x<=800; x++)
		{
			if((x - x0)*(x - x0) + (y - y0)*(y - y0) <= 15*15)//棋子半径为15
			{
				lcd_draw_point(x,y,0xffffff);//棋子为黑色
			}
		}
	}
}
/*
    recover_round:恢复棋盘
    @x0：恢复棋盘圆心横坐标
    @y0：恢复棋盘圆心纵坐标

    返回值：无
*/

void recover_round(int x0,int y0)
{
    for(int y=0; y<=480; y++)
	{
        for(int x=0; x<=800; x++)
		{
			if((x - x0)*(x - x0) + (y - y0)*(y - y0) <= 15*15)//棋子半径为15
			{
				lcd_draw_point(x,y,0x8b4513);
			}
		}
	}
}

/*
    recover_line:恢复棋盘
    @x0：恢复棋盘圆心横坐标
    @y0：恢复棋盘圆心纵坐标

    返回值：无
*/
void recover_line(int x0,int y0)
{
    for(int y=y0-20; y<=y0+20; y++)
	{
        for(int x=x0-20; x<=x0+20; x++)
		{
			if((x - x0)*(x - x0) + (y - y0)*(y - y0) <= 15*15)//棋子半径为15
			{
				lcd_draw_point(x,y,0x000000);
			}
		}
	}
}