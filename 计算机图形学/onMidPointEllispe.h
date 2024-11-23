#include <vector>
#include <windows.h>  
#include <GL/glut.h>
using namespace std;
typedef struct Point {
	int x, y;
	Point(int a = 0, int b = 0)	{
		x = a, y = b;
	}
} point;
void  onMidPointEllispe(int a,int b);
