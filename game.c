#include <stdio.h>
#include "game.h"
#include "touch.h"
#include "lcd.h"
#include "bmp.h"
#include <unistd.h>
int piece_position[480][480] ;//定义一个二维数组保存棋子的位置

/* 

    local_init：五子棋棋子位置初始化
                用一个二维数组
    返回值：无
 */
void local_init()
{
    for ( int y = 0; y < 480; y+=40)
    {
        for (int x = 0; x < 480; x+=40)
        {
            piece_position[x][y] = 0;//初始位置默认为0
        }
        
    }  
}


/* 
    Game_victory：判断游戏胜利
    记录五个黑棋和五个白棋的坐标
    分别从横向，竖向，左上到右下，左下到右上
    判断是否是连续的五个白棋或者五个连续的黑棋

    返回值： return    1白棋胜
            return    2黑棋胜
 */

int Game_victory()
{
    for (int y = 40; y < 480; y+=40)
	{
		for (int x = 40; x < 480; x+=40)
		{

            //1.判断连续五个白棋
            if( piece_position[x][y] == 1 &&
                piece_position[x+40][y] == 1 &&
                piece_position[x+80][y] == 1 &&
                piece_position[x+120][y] == 1 &&
                piece_position[x+160][y] == 1 ) //连续横着的五个白棋
            {
                return 1;//白棋胜
                break;
            }

            if( piece_position[x][y] == 1 &&
                piece_position[x][y+40] == 1 &&
                piece_position[x][y+80] == 1 &&
                piece_position[x][y+120] == 1 &&
                piece_position[x][y+160] == 1 ) //连续竖着的五个白棋
            {
                return 1;//白棋胜
                break;
            }

            if( piece_position[x][y] == 1 &&
                piece_position[x+40][y+40] == 1 &&
                piece_position[x+80][y+80] == 1 &&
                piece_position[x+120][y+120] == 1 &&
                piece_position[x+160][y+160] == 1 ) //连续从左向右斜着的五个白棋
            {
                return 1;//白棋胜
                break;
            }

            if( piece_position[x][y] == 1 &&
                piece_position[x-40][y+40] == 1 &&
                piece_position[x-80][y+80] == 1 &&
                piece_position[x-120][y+120] == 1 &&
                piece_position[x-160][y+160] == 1 ) //连续从右向左斜着的五个白棋
            {
                return 1;//白棋胜
                break;
            }

            //1.判断连续五个黑棋
            if( piece_position[x][y] == 2 &&
                piece_position[x+40][y] == 2 &&
                piece_position[x+80][y] == 2 &&
                piece_position[x+120][y] == 2 &&
                piece_position[x+160][y] == 2 ) //连续横着的五个黑棋
            {
                return 2;//黑棋胜
                break;
            }

            if( piece_position[x][y] == 2 &&
                piece_position[x][y+40] == 2 &&
                piece_position[x][y+80] == 2 &&
                piece_position[x][y+120] == 2 &&
                piece_position[x][y+160] == 2 ) //连续横着的五个黑棋
            {
                return 2;//黑棋胜
                break;
            }

            if( piece_position[x][y] == 2 &&
                piece_position[x+40][y+40] == 2 &&
                piece_position[x+80][y+80] == 2 &&
                piece_position[x+120][y+120] == 2 &&
                piece_position[x+160][y+160] == 2 ) //连续从左向右斜着的五个黑棋
            {
                return 2;//黑棋胜
                break;
            }

            if( piece_position[x][y] == 2 &&
                piece_position[x-40][y+40] == 2 &&
                piece_position[x-80][y+80] == 2 &&
                piece_position[x-120][y+120] == 2 &&
                piece_position[x-160][y+160] == 2 ) //连续从右向左斜着的五个黑棋
            {
                return 2;//黑棋胜
                break;
            }            
        }
    }
}






/*
    get_blackandwhitte：下黑棋和白棋
    触屏函数获取用户触摸屏的坐标,然后右上角显示准备开始1s后就开始下棋 右上角会显示黑方走棋
	首先是黑子先行，黑子落棋然后右上角显示白方走棋，再白子落棋（以此类推）
    白方或黑方胜出后会出现白方或黑方胜利的界面，在右上角会出现返回游戏
    点击之后可以继续回去重新开始游戏
	点击玩家悔棋按键时 ：再点击棋盘上玩家要返回的那个棋子（黑或白），玩家再下返回那种棋子（黑或白）
    点击退出游戏按键时 ：会回到开始游戏界面
    返回值 ：无
*/
void get_blackandwhite()
{
	int x0,y0;//触屏点的横坐标和纵坐标
    int x1,y1;
	int flag = 0;//定义一个标志位
    int win; //win = 1 白棋胜利
             //win = 2 黑棋胜利
    int num = 0;
    int count = 0;//记录下的棋子数
    
	while(1)
	{
		get_usr_touch(&x0,&y0);//触屏函数获取用户触摸屏的坐标
        if(num == 0)
        {
            show_bmp(481,0,"./pic/6.bmp");//准备开始
            sleep(1);
            show_bmp(481,0,"./pic/4.bmp");//黑方走棋
            show_bmp(481,240,"./pic/7.bmp");//显示悔棋和退出游戏
            num++;
        }

        else if(num == 1)
        {
                if(x0>0&&x0<480&&y0>0&&y0<480)
                {
                    xiaqi(x0,y0,flag);
                    win = Game_victory();
                    if(win == 1)//黑棋胜
                    {
                        white_win();//显示白棋获胜的图片
                        win = 0;
                        flag = 0;//标志位清零
                        num = 0;
                        break;
                    }

                    if(win == 2)//黑棋胜
                    {
                        biack_win();//显示黑棋获胜的图片
                        win = 0;
                        flag = 0;//标志位清零
                        num = 0;
                        break;
                    } 
                }
                if(x0>=520&&x0<=750&&y0>=170&&y0<=260)
                {
                    huiqi(x0,y0,flag);
                }
                if(x0>=520&&x0<=750&&y0>=380&&y0<=460)//退出游戏
                {
                    //显示开始游戏按钮
                    lcd_start_button();
                    flag = 0;
                    num = 0;
                    break;
                }
        }
    }
            	
}		




/*
    显示开始游戏界面
    显示一张五子棋的界面
    中间有个开始游戏的按钮
    点击之后会进入五子棋下棋界面
    返回值：无
*/

void lcd_start_button()
{
	clear_lcd(0x000000);//清屏
    show_bmp(0,0,"./pic/1.bmp");//展示游戏开始的界面
    int x,y;
    while(1)
    {
        get_usr_touch(&x,&y);//获取开始游戏的坐标
        if(x>=260&&x<=550&&y>=350&&y<=480)
        {
			/*
			画棋盘背景颜色
			*/
			chess_ground();
			/*
			画棋盘线
			*/
			chess_line();
			/* 
			五子棋棋子位置初始化
			*/
			local_init();
            break;
        }
    }
}
/*
	white_win:白棋获胜返回游戏
    白棋五子连珠会出现白棋获胜界面
    点击右上角返回游戏会继续开始游戏
    返回值：无
*/
void white_win()
{
	show_bmp(0,0,"./pic/2.bmp");//白棋获胜
	int x,y;
	while(1)
	{
		 get_usr_touch(&x,&y);//获取返回游戏的坐标
        if(x>=640&&x<=800&&y>=0&&y<=130)
        {
			/*
			画棋盘背景颜色
			*/

			chess_ground();
			/*
			画棋盘线
			*/
			chess_line();
			/* 
			五子棋棋子位置初始化
			*/
			local_init();
            break;
        }
	}
}

/*
	black_win:黑棋获胜返回游戏
    黑棋五子连珠会出现黑棋获胜界面
    点击右上角返回游戏会继续开始游戏
    返回值：无
*/
void biack_win()
{
	show_bmp(0,0,"./pic/3.bmp");//黑棋获胜
	int x,y;
	while(1)
	{
		 get_usr_touch(&x,&y);//获取返回游戏的坐标
        if(x>=640&&x<=800&&y>=0&&y<=130)
        {
			/*
			画棋盘背景颜色
			*/

			chess_ground();
			/*
			画棋盘线
			*/
			chess_line();
			/* 
			五子棋棋子位置初始化
			*/
			local_init();
            break;
        }
	}
}

void xiaqi(int x0,int y0,int flag)
{
    for (int y = 40; y < 480; y+=40)
    {
        for (int x = 40; x < 480; x+=40)
        {
            if((x0-x)*(x0-x)+ (y0 - y) * (y0 - y) <= 20*20 && flag == 0 && piece_position [x][y] == 0)//flag == 0 下黑棋
            {
                show_bmp(481,0,"./pic/5.bmp");//白方走棋
                black(x,y);//画黑棋
                printf("x,y(%d , %d)\n",x,y);//打印黑棋子落到棋盘上的坐标
                flag+=1;
                piece_position [x][y] = 2;//黑棋的piece_position 为 2
            }
            
            else if((x0-x)*(x0-x)+ (y0 - y) * (y0 - y) <= 20*20 && flag == 1 && piece_position [x][y] == 0)//flag == 1 下白棋
            {
                show_bmp(481,0,"./pic/4.bmp");//黑方走棋
                white(x,y);//画白棋
                printf("x,y(%d , %d)\n",x,y);//打印白棋子落到棋盘上的坐标
                flag-=1;
                piece_position [x][y] = 1;//白棋的piece_position 为 1
            }
        }
    }
}
 










void huiqi(int x0,int y0,int flag)
{
    
    for (int y = 40; y < 480; y+=40)
    {
        for (int x = 40; x < 480; x+=40)
        {
            if((x0-x)*(x0-x)+ (y0 - y) * (y0 - y) <= 20*20 && flag == 1 && piece_position [x][y] == 2)//flag == 1 要悔棋的是黑棋
            {
                recover_round(x,y);
                recover_line(x,y);
                flag-=1;
            }
            if((x0-x)*(x0-x)+ (y0 - y) * (y0 - y) <= 20*20 && flag == 0 && piece_position [x][y] == 1)//flag == 0 要悔棋的是白棋
            {
                recover_round(x,y);
                recover_line(x,y);
                flag+=1;
            }
        }
    }
}
