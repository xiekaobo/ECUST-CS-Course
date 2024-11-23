#include "onMidPointEllispe.h"
#include<gl/glut.h>
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
int iPointNum=0;
int ellipse=0;
int x1=0,x2=0,y1=0,y2=0,x20,y20,a0,b0,a;
int winWidth=600,winHeight=600;
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
    if(ellipse==1)//在菜单中
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f,0.0f,0.0f);
        if(iPointNum>=1)
        {
            if(iPointNum==1)
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
                glEnd();//画出外接矩形
            }
        if(iPointNum==2||iPointNum==1)
        {
            glTranslated((x1+x2)/2,(y1+y2)/2,0);
            //平移世界坐标原点
            onMidPointEllispe(Abs(x1-x2)/2,Abs(y1-y2)/2);
            //计算长短轴导入函数
            glTranslated(-(x1+x2)/2,-(y1+y2)/2,0);
            //平移回世界坐标原点，重新绘制
        }
        }
    glutSwapBuffers();
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glutSwapBuffers();
    }
}
/**************************************************
* 已知椭圆的长短轴a,b
* 根据椭圆的中点Bresenham算法，扫描转换椭圆
* 以glBegin(GL_POINTS);glEnd();方式，绘制椭圆
***************************************************/
void  onMidPointEllispe(int a,int b){
	int x,y;
    float d1,d2;
	glBegin(GL_POINTS);
		x=0;y=b;
		d1=b*b+a*a*(-b+0.25);
		glVertex2i(x,y);
		glVertex2i(-x,-y);
		glVertex2i(-x,y);
		glVertex2i(x,-y);
		while(b*b*(x+1)<a*a*(y-0.5))
		{
			if(d1<=0){
				d1+=b*b*(2*x+3);
				x++;
			}
			else{
				d1+=b*b*(2*x+3)+a*a*(-2*y+2);
				x++; y--;
			}
			glVertex2f(x,y);
			glVertex2f(-x,-y);
			glVertex2f(-x,y);
			glVertex2f(x,-y);
		}/*while上半部分*/
		d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
		while(y>0)
		{
			if(d2<=0){
        		d2+=b*b*(2*x+2)+a*a*(-2*y+3);
				x++; y--;
			}
			else{
				d2+=a*a*(-2*y+3);
				y--;
			}
			glVertex2f(x,y);
			glVertex2f(-x,-y);
			glVertex2f(-x,y);
			glVertex2f(x,-y);
		}
	glEnd();
}

void menu(int value)//菜单处理函数
{
    switch(value)
    {
        case 1:
        {
            ellipse=1;
            iPointNum=0;
        }
    }
}
void createMenu()//创建菜单并为菜单选项指定处理函数
{
    glutCreateMenu(menu);
    glutAddMenuEntry("Draw Ellipse", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);//将菜单绑定到右键
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
            glutPostRedisplay();
            if(glutGetModifiers() & GLUT_ACTIVE_SHIFT)
            {
                x20=xMouse;
                y20=winHeight-yMouse;
                a0=Abs(x20-x1);
                b0=Abs(y20-y1);
                a=MIN(a0,b0);
                if(x20>x1) x2=x1+a;
                else x2=x1-a;
                if(y20>y1) y2=y1+a;
                else y2=y1-a;
                glutPostRedisplay();
            }
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
        if(glutGetModifiers() & GLUT_ACTIVE_SHIFT)
        {
            x20=xMouse;
            y20=winHeight-yMouse;
            a0=Abs(x20-x1);
            b0=Abs(y20-y1);
            a=MIN(a0,b0);
            if(x20>x1) x2=x1+a;
            else x2=x1-a;
            if(y20>y1) y2=y1+a;
            else y2=y1-a;
            glutPostRedisplay();
        }
        else
        {
            x2=xMouse;
            y2=winHeight-yMouse;
            glutPostRedisplay();
        }
    }
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); //初始化窗口的显示模式
    glutInitWindowSize(600,600); //设置窗口的尺寸
    glutInitWindowPosition(100,100); //设置窗口的位置
    glutCreateWindow("徐昊博21013134第一次实验");//创建窗口
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(MousePlot);
    glutPassiveMotionFunc(PassiveMouseMove);
    createMenu();
    Initial(); //完成窗口初始化
    glutMainLoop(); //启动主GLUT事件处理循环
    return 0;
}
