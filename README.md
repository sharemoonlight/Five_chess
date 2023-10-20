项目名称 ：基于 Linux GEC6818 开发板 五子棋小游戏

项目制作人 ：彭万翔

项目介绍 ：
	项目实现功能:棋子 横 ，竖，左上，右上，左下，右下，
                有五个连续相同棋子白子则表示白子胜出
                有五个连续相同棋子黑子则表示黑子胜出
		        点击首页开始游戏- - - - - >进入游戏页面
                然后右上角显示准备开始1s后就开始下棋 右上角会显示黑方走棋
		        首先是黑子先行，黑子落棋然后右上角显示白方走棋，再白子落棋（以此类推）
                白方或黑方胜出后会出现白方或黑方胜利的界面，在右上角会出现返回游戏
                点击之后可以继续回去重新开始游戏
		        点击玩家悔棋按键时 ：再点击棋盘上玩家要返回的那个棋子（黑或白），玩家再下返回那种棋子（黑或白）
                点击退出游戏按键时 ：会回到开始游戏界面

主要用到工具:Visual Studio Code ,VMware Workstation 16 Player,SecureCRT,GEC6818 开发板,网线

	     Visual Studio Code ：主要实现代码的编写
	     主要分为 ：图片显示部分 ，按键部分，五子棋判断胜出部分，图片像素点部分，棋子放入部分等等
	    
	     VMware Workstation 16 Playe ：主要实现代码编译	           
	     Code写好的代码存入共享文件夹share内，Ubuntu找到这个共享文件夹路径进行 make 编译 ，编译好的 arm-linux 可执行文件存入
	     /home/china/tftpboot文件中。

	     网线 ：Ubuntu 和 SecureCRT 形成局域网进行文件传输

	     SecureCRT ：主要实现将可执行文件传入GEC6818 开发板
                     根据 tftp -g -r 文件名 Ubuntu网址指令，将 Ubuntu 内 tftpboot 里面的文件 经过网线传输到 SecureCRT ，然后执行可执行文件下载到
	     GEC6818 开发板

	     GEC6818 开发板：显示效果
主要功能用到的函数：
	lcd.c:
		void lcd_init()//用映射屏幕初始化     void lcd_uninit() //解除映射和关闭文件 
		 void lcd_draw_point(int x,int y,int color)//画点函数，将（x，y）坐标上的像素点显示为color颜色
		 void draw_round(int x0,int y0,int r,int color)//画圆函数
		运用画点函数和画圆函数可以将棋盘和黑白棋子的画好：
		 void chess_ground()//画棋盘背景颜色  void chess_line()画棋盘线
		void black(int x0, int y0)//black：画黑棋 void white(int x0, int y0)//white：画白棋
	touch.c:
		void get_usr_touch(int *x0,int* y0)//获取用户触摸屏的坐标 触屏事件 
	bmp.c:	
		void show_bmp(int x0,int y0,char* bmpfile)//显示bmp图片
	game.c:
		void local_init()//五子棋棋子位置初始化 
		用一个二维数组保存棋子的位置  piece_position[x][y] = 0;//初始位置默认为0
		get_blackandwhite()//下黑棋和白棋
		int Game_victory()//判断游戏胜利
		void white_win()//白棋获胜
		void biack_win()//黑棋获胜
		void lcd_start_button()//显示开始游戏按钮

		在get_blackandwhite()中
		先获取用户触屏的坐标 首先是黑棋子先行，当用手指触屏在棋盘
		上时判断触屏的位置是否处在可以画棋子的位置 然后用画黑棋函数 画出黑棋，下白棋也一样 
		在int Game_victory()中
		可以用棋子坐标实现判断棋子 横 ，竖，左上，右上，左下，右下，有五个连续相同棋子白子（黑子）则表示白子（黑子）胜出

项目遇到的问题： 
		在下棋的过程中 下黑棋和白棋会出现重叠的情况 我用初始化的二维数组piece_position[x][y] = 1 保存白棋的位置
		piece_position[x][y] = 2 保存黑棋的位置 在每次下棋的时候判断一下就不会出现这类情况了
                
		
		