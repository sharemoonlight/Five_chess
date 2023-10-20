#ifndef _TOUCH_H__
#define _TOUCH_H__
#define UP 		1
#define DOWN 	2
#define LEFT  	3
#define RIGHT	4

/*
//注意 : 触屏屏的分辨率是1024*600,lcd屏是800*480,等比例缩放
get_usr_touch :获取用户触摸屏的坐标
@x : 指向的空间保存的是x轴坐标
@y : 指向的空间保存的是y轴坐标
返回值 :
无
*/
void get_usr_touch(int *x,int* y);

/*
	get_fingle_move；获取手指滑动的方向
	返回值：
	返回 UP  	1
	返回 DOWN 	2
	返回 LEFT	3
	返回 RIGHT 	4
	返回 -1 	失败
*/
int get_fingle_move();


#endif