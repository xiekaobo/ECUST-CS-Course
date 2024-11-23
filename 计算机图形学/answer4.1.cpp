#include <iostream>
#include <vector>
#include <windows.h>
#include <GL/glut.h>
#include <cstdio>
#include "graphicType.h"
using namespace std;
int winWidth = 600, winHeight = 400;
int iMode = 0;

vector <point> pointVertex;        //控制折线顶点序列
bool isEnd=false;			        //标识折线是否绘制完成
const GLint ControlN = 4;           //由4个控制点定义三次bezier曲线段
color redColor(1,0,0),blackColor(0,0,0);//红色、黑色
int iMousePointNum = 0;              //鼠标单击确定折线顶点个数

//根据点序列向量数组points，绘制折线
void drawPolygonalLine(vector<point> &points,color &c )
{
	glColor3f(c.r, c.g, c.b);
	glBegin (GL_LINE_STRIP);
    for(int i=0;i<iMousePointNum;i++)
    {
        glVertex2i(points[i].x, points[i].y);
    }
	glEnd();
}

//如果控制点数n<4，绘制一段n-1次Bezier曲线段，否则绘制一段三次Bezier曲线段
void drawBezierCurve(vector<Point> &points,color &c)
{
	GLfloat ControlP[4][3];
	int iPointNum = iMousePointNum;
	int i;
	if(iPointNum<4)//控制点数<4，绘制一段n-1次Bezier曲线段
    {
		for(i=0;i<iPointNum;i++)
		{
			ControlP[i][0]=points[i].x;
			ControlP[i][1]=points[i].y;
			ControlP[i][2]=0.0;
		}
	}
	else          //控制点数>=4，绘制一段三次Bezier曲线段
	{
		for(i=0;i<4;i++)
		{
			ControlP[i][0]=points[i].x;
			ControlP[i][1]=points[i].y;
			ControlP[i][2]=0.0;
		}
	}
	glColor3f(c.r, c.g, c.b);
	glPointSize(2);
	if(iPointNum > 4)
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4,         *ControlP);//定义一维取值器
	else
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, iPointNum, *ControlP);//定义一维取值器
	glEnable(GL_MAP1_VERTEX_3);
	glMapGrid1f(100, 0.0, 1.0);    //生成均匀分布的一维网格参数值
	glEvalMesh1(GL_LINE, 0, 100);  //绘制Bezier曲线
}

void Initial(void)//初始化窗口
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //设置窗口背景颜色为白色
}
void ChangeSize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);                 //指定窗口显示区域
	glMatrixMode(GL_PROJECTION);            //设置投影参数
	glLoadIdentity();
	gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void ProcessMenu(int value)                //处理菜单响应
{
    iMode = value;
    glutPostRedisplay();
}

void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    Point p0;
    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && iMode==4)//鼠标左击，绘制折线上的点
    {
        p0.x = xMouse;
        p0.y = winHeight - yMouse;
        pointVertex.push_back(p0);
        iMousePointNum++;
    }
    else if(button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN && iMode==4)//鼠标右击，结束折线绘制
    {
        isEnd = TRUE;//结束
    }
}

void PassiveMouseMove (GLint xMouse, GLint yMouse)//鼠标移动过程中
{
	if(iMousePointNum>=1 && !isEnd)//正在绘制折线
    {
        Point p0;
        p0.x = xMouse;
        p0.y = winHeight - yMouse;
        pointVertex.push_back(p0);
        glutPostRedisplay();       //窗口执行重新绘制操作
        pointVertex.pop_back();
	}
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //用当前背景色填充窗口
    switch(iMode)
    {
        case 4:
            glColor3f(0.0f, 0.0f, 0.0f); //设置折线颜色为黑色
            glLineStipple(1, 0x00FF);    //设置折线类型为虚线
            glEnable(GL_LINE_STIPPLE);
            if(iMousePointNum >= 1)      //绘制折线
            {
                drawPolygonalLine(pointVertex, blackColor);
                if(!isEnd)
                {
                    glBegin(GL_LINES);
                    glVertex2i(pointVertex[iMousePointNum-1].x, pointVertex[iMousePointNum-1].y);
                    glVertex2i(pointVertex[iMousePointNum].x, pointVertex[iMousePointNum].y);
                    glEnd();
                }
            }
            glDisable(GL_LINE_STIPPLE);
            if(isEnd)                  //绘制Bezier曲线
            {
                drawBezierCurve(pointVertex, redColor);
            }
            break;
        default: break;
    }
    glutSwapBuffers();         //交换缓冲区
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //使用“双缓存”以及RGB模型
	glutInitWindowSize(600,400);
	glutInitWindowPosition(200,200);
	glutCreateWindow("实验4_by_20002462");

    //创建菜单并定义菜单回调函数
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Ellispe", 1);
    glutAddMenuEntry("LineClipping", 2);
    glutAddMenuEntry("Graphic", 3);
    glutAddMenuEntry("Bezier", 4);//选择菜单4
    glutAddMenuEntry("Bezier_Extend", 5);
    glutAttachMenu(GLUT_MIDDLE_BUTTON); //将主菜单与鼠标中心键关联

	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);                 //指定窗口在整形回调函数
	glutMouseFunc(MousePlot);                    //指定鼠标响应函数
	glutPassiveMotionFunc(PassiveMouseMove);     //指定鼠标移动响应函数
	Initial();
	glutMainLoop();
	return 0;
}
