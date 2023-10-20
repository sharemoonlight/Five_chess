#ifndef _GAME_H__
#define _GAME_H__

/* 
    local_init：五子棋棋子位置初始化
    返回值：无
 */
void local_init();
/*
    get_blackandwhitte：下黑棋和白棋
    返回值 ：无
*/
void get_blackandwhite();
/* 
    Game_victory：判断游戏胜利
    返回值：
 */

int Game_victory();


//显示开始按钮
void lcd_start_button();

/*
	white_win:白棋获胜返回游戏
*/
void white_win();

/*
	black_win:黑棋获胜返回游戏
*/
void biack_win();

void huiqi(int x0,int y0,int flag);

void xiaqi(int x0,int y0,int flag);
#endif