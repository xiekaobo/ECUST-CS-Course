#include<iostream>
#include<vector>
#include<windows.h>
#include<gl/glut.h>
using namespace std;
#include "setLookAt.h"       //给出三维坐标点point3D的定义和建立视角视觉效果函数setLookAt()
#include "getAxis.h"         //给出轴长，定义三维坐标轴图段，x轴为红色、y轴为绿色、z轴为蓝色
#include "getTetrahedron.h"  //给出4个三维坐标点ABCD，定义四面体图段

static GLsizei iMode = 1;   //三视图菜单项
float axisLength = 20.0;    //三维坐标轴长

GLuint objectID,axisID;          //四面体对象ID、坐标轴ID、
int winWidth = 400, winHeight = 200;    //窗口的宽度和高度
static float angle = 45.0;		 //绕坐标轴的旋转角
static point3D s_eye(5.0,5.0,5.0);      //观察点位置
static point3D s_at(0.0,0.0,0.0);       //视点中心
static point3D A(2.0f,0.0f,0.0),B(2.0f,1.0f,0.0),C(0.0f,1.0f,0.0),D(1.0f,1.0f,1.0);//四面体四点坐标

void initial(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //设置窗口背景颜色为白色
}

void ChangeSize(GLsizei w, GLsizei h)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//多边形模式为线框
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);                 //指定窗口显示区域
	glMatrixMode(GL_PROJECTION);            //设置投影参数
	glLoadIdentity();
}

void triangle(GLsizei mode)     //左右视图的绘制，mode决定选左or选右
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//多边形模式为线框
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT ,vp); //获得视区的左下角坐标、宽度和高度信息
    int w = vp[2], h = vp[3];
    float aspect;
    if(w < h){
        aspect = (float)w/(float)h;
    }
    else{
        aspect = (float)h/(float)w;
    }
	glMatrixMode(GL_MODELVIEW);            //指定当前操作模型视图矩阵堆栈
	glLoadIdentity();                      //恢复初始坐标系，将当前点移动到屏幕中心

	if(mode==1)//左视区
    {
        setLookAt(iMode, s_eye, s_at);//根据菜单iMode选择三视图，建立视角视觉效果
    	glMatrixMode(GL_PROJECTION);            //设置投影参数
        glLoadIdentity();
        glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, -5.0);//定义左视区的三维正交观察可视体，创建一个正射投影矩阵
    }
    else//右视区
    {
        setLookAt(iMode, angle, s_eye, s_at);//根据菜单iMode选择的三视图，根据右手原则，围绕某坐标轴旋转angle，建立视角视觉效果
    	glMatrixMode(GL_PROJECTION);            //设置投影参数
        glLoadIdentity();
        gluPerspective(45.0f, aspect, 0.0f, 10.0f);//定义右视区的三维透视观察可视体
    }
    glCallList(objectID);                   //执行显示列表所存储的函数
    glCallList(axisID);
}

void SpecialKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
    {
        angle = angle + 1;
    }
    else if(key == GLUT_KEY_DOWN)
    {
        angle = angle - 1;
    }
    glutPostRedisplay();//刷新

}

void ProcessMenu(int value)//处理菜单响应
{
    iMode = value;
    glutPostRedisplay();
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    axisID = getAxis(axisLength);             //根据轴长axisLength定义XYZ三维坐标系
    objectID = getTetrahedron( A, B, C, D);     //4点ABCD定义四面体图元

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//多边形模式为线框
    //左视区
    glViewport(0, 0, 200, 200);//指定从0，0开始，长宽均为200的视区
    triangle(1);
    //右视区
    glViewport(200, 0, 200, 200);//指定从200，0开始，长宽均为200的视区
    triangle(2);
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE  | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("20002462");//多视区
    //创建菜单并定义菜单回调函数
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("To__XOZ(V)",1);
    glutAddMenuEntry("To__XOY(H)",2);
    glutAddMenuEntry("To__YOZ(W)",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);//主菜单与鼠标右键关联
    initial();
    glutDisplayFunc(Display);		//指定窗口重绘响应函数
    glutReshapeFunc(ChangeSize);    //指定窗口大小改变响应函数
    glutSpecialFunc(SpecialKeys);   //指定功能键响应函数
    glutMainLoop();
    return 0;
}
