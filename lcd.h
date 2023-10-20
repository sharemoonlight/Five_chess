#ifndef _LCD_H__
#define _LCD_H__

void lcd_init();/*屏幕初始化*/
void lcd_uninit();/*解除映射和关闭文件*/
void clear_lcd(int color);//清屏

/*
    lcd_draw_point 画点函数，将（x，y）坐标上的像素点显示为color颜色
    @x      像素点的横坐标
    @y      像素点的纵坐标
    @color  像素点的颜色
*/
void lcd_draw_point(int x,int y,int color);

/* 
draw_round ：画圆
参数：
    int x0 ：圆心的X轴
    int y0 ：圆心的Y轴
    int r  ：圆的半径
    int colour ：圆的颜色
 */
void draw_round(int x0,int y0,int r,int color);
/*
    画棋盘背景颜色
*/

void chess_ground();

/*
    画棋盘线
*/
void chess_line();
void black(int x0, int y0);//画黑棋 a b为圆心的坐标
void white(int x0, int y0);//画白棋 a b为圆心的坐标

/*
    recover_round:恢复棋盘
    @x0：恢复棋盘圆心横坐标
    @y0：恢复棋盘圆心纵坐标

    返回值：无
*/

void recover_round(int x0,int y0);
/*
    recover_line:恢复棋盘
    @x0：恢复棋盘圆心横坐标
    @y0：恢复棋盘圆心纵坐标

    返回值：无
*/
void recover_line(int x0,int y0);


#endif