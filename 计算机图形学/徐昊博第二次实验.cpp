#include<gl/glut.h>
#include <vector>
#include "lineClipping.h"
using namespace std;
int Abs(int a)
{
    if(a<0)
    {
        return -a;
    }
    else return a;
}
int MAX(int a,int b)
{
    if(a>b) return a;
    else return b;
}
int MIN(int a,int b)
{
    if(a<b) return a;
    else return b;
}
int iPointNum=0,iKeyPointNum=0;
int x1=0,x2=0,y1=0,y2=0,p1=0,q1=0,p2=0,q2=0,a;
int winWidth=600,winHeight=600;
int draw=0,done=0;
vector <point> LINE;
std::vector<point>::iterator it;
rect winObj;
/***********************************************
*如果p参数<0，计算、更新umax，保证umax是最大u值
*如果p参数>0，计算、更新umin，保证umin是最小u值
*如果umax>umin，返回0，否则返回1
***********************************************/
int Clip_Top(float p,float q,float &umax,float &umin){
	float r=0.0;
    if(p<0.0)	//线段从裁剪窗口外部延伸到内部，取最大值r并更新umax
	{
		r=q/p;
		if (r>umin) return 0;	//umax>umin的情况，弃之
		else if (r>umax)  umax=r;
	}
	else if(p>0.0)      //线段从裁剪窗口内部延伸到外部,取最小值r并更新umin
		{
			r=q/p;
			if (r<umax) return 0;	//umax>umin的情况，弃之
			else if(r<umin)  umin=r;
		}
	   else 		//p=0时，线段平行于裁剪窗口
	      if(q<0.0) return 0;
	 return 1;
}
/*************************************************************
*已知winRect：矩形对象，存放标准裁剪窗口4条边信息
*    points：点的动态数组，存放直线2个端点信息
*根据裁剪窗口的左、右边界，求umax；
*根据裁剪窗口的下、上边界，求umin
*如果umax>umin，裁剪窗口和直线无交点，否则求裁剪后直线新端点
***************************************************************/
void Line_Clipping(vector<point> &points,rect & winRect){
	//比较左、右边界，获得最大的umax
    for (it = points.begin(); std::next(it) != points.end(); ++it)
    {
	point &p1=*it,&p2=*std::next(it);
	float dx=p2.x-p1.x,dy=p2.y-p1.y,umax=0.0,umin=1.0;
	point p=p1;
	if (Clip_Top(-dx,p1.x- winRect.w_xmin,umax,umin))  //左边界
		if (Clip_Top(dx,winRect.w_xmax-p1.x, umax,umin)) //右边界
			//比较下、上边界，获得最小的umin
			if (Clip_Top(-dy,p1.y- winRect.w_ymin, umax,umin)) //下边界
				if (Clip_Top(dy,winRect.w_ymax-p1.y, umax,umin)) //上边界
				{//求裁剪后直线新端点
					p1.x=(int)(p.x+umax*dx);
					p1.y=(int)(p.y+umax*dy);
					p2.x=(int)(p.x+umin*dx);
					p2.y=(int)(p.y+umin*dy);
				}
    }
}
void Initial(void)
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}
void ChangeSize(int w,int h)
{
    winWidth=w; winHeight=h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);
    if(iPointNum>=1)
    {
        glBegin(GL_LINES);
        glVertex2i(x1,y1);
        glVertex2i(x2,y1);

        glVertex2i(x2,y1);
        glVertex2i(x2,y2);

        glVertex2i(x2,y2);
        glVertex2i(x1,y2);

        glVertex2i(x1,y2);
        glVertex2i(x1,y1);
        glEnd();
    }
    if(iKeyPointNum>=1)
    {
        if(draw==1)
        {
            glBegin(GL_LINES);
            for (it = LINE.begin(); it != LINE.end(); std::advance(it, 2))
            {
            glVertex2i(it->x, it->y);
            std::advance(it, 1);
            glVertex2i(it->x, it->y);
            }
            glEnd();
            draw=0;
        }
        else
        {
            glBegin(GL_LINES);
            for (it = LINE.begin(); it != LINE.end(); std::advance(it, 2))
            {
            glVertex2i(it->x, it->y);
            std::advance(it, 1);
            glVertex2i(it->x, it->y);
            }
            glEnd();
        }

    }
    glutSwapBuffers();
}

void Key(unsigned char key, int x, int y)
{
	switch(key){
    case 'p':
        if(done!=0)
        {
            iKeyPointNum = 1;
            p1 = x;	q1 = winHeight - y;
            point n(p1,q1);
            LINE.push_back(n);
        }
        glutPostRedisplay();
        break;
    case 'c':
        draw=1;
        Line_Clipping(LINE,winObj);
        break;
    case 'e':
        done = 1;
		glutPostRedisplay();
		break;
    default: break;
    	}
}
void MousePlot(GLint button, GLint action,GLint xMouse,GLint yMouse)
{
    if(button==GLUT_LEFT_BUTTON&&action==GLUT_DOWN)
    {
        if(iPointNum==0||iPointNum==2)
        {
            iPointNum=1;
            x1=xMouse;
            y1=winHeight-yMouse;
        }
        else if(iPointNum==1)
        {
            iPointNum=2;
            x2=xMouse;
            y2=winHeight-yMouse;
            winObj.w_xmin=MIN(x1,x2);
            winObj.w_xmax=MAX(x1,x2);
            winObj.w_ymin=MIN(y1,y2);
            winObj.w_ymax=MAX(y1,y2);
            glutPostRedisplay();
        }
    }
    if(button==GLUT_RIGHT_BUTTON&&action==GLUT_DOWN)
    {
        iPointNum=0;
        glutPostRedisplay();
    }
}
void PassiveMouseMove(GLint xMouse,GLint yMouse)
{
    if(iPointNum==1)
    {
        x2=xMouse;
        y2=winHeight-yMouse;
        glutPostRedisplay();
    }
    if(done!=0)
    {
        p1 = xMouse;	q1 = winHeight - yMouse;
        point n(p1,q1);
        LINE.push_back(n);
        glutPostRedisplay();
    }
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); //初始化窗口的显示模式
    glutInitWindowSize(600,600); //设置窗口的尺寸
    glutInitWindowPosition(100,100); //设置窗口的位置
    glutCreateWindow("徐昊博21013134第二次实验");//创建窗口
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(MousePlot);
    glutKeyboardFunc(Key);
    glutPassiveMotionFunc(PassiveMouseMove);
    Initial(); //完成窗口初始化
    glutMainLoop(); //启动主GLUT事件处理循环
    return 0;
}
