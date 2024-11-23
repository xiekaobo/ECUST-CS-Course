#include <iostream>
#include <vector>
#include <windows.h>
#include <GL/glut.h>
using namespace std;
//点类型point
typedef struct Point {
	int x, y;
	Point(int a = 0, int b = 0)
	{
		x = a, y = b;
	}
} point;
//矩形类型rect
typedef struct Rectangle{
	float w_xmin,w_ymin;
	float w_xmax,w_ymax;
	Rectangle(float xmin = 0.0, float ymin = 0.0,float xmax=0.0,float ymax=0.0){
		w_xmin = xmin;	w_ymin = ymin;
		w_xmax = xmax;	w_ymax = ymax;
	}
}rect;
int Clip_Top(float p,float q,float &umax,float &umin);
void Line_Clipping(vector<point> &points,rect & winRect);
void  onMidPointEllispe(int a,int b);
void  OnMidpointellispe(int a,int b,vector<point> &points);
