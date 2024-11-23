#include<iostream>
#include<vector>
#include<windows.h>
#include<GL/glut.h>
using namespace std;
#include "setLookAt.h"
#include "getAxis.h"
#include "getTetrahedron.h"
GLuint objectID,axisID;//四面体对象ID、坐标轴ID、
int winWidth = 400, winHeight = 200; //窗口的宽度和高度
static float angle = 45.0;		//angle绕坐标轴的旋转角
static GLfloat xRot = 0.0f;  //旋转参数
static GLfloat yRot = 0.0f;  //旋转参数
static GLfloat zRot = 0.0f;  //旋转参数
static GLsizei iMode = 1;		//菜单值
static point3D s_eye(5.0,5.0,5.0); //观察点位置
static point3D s_at(0.0,0.0,0.0);  //视点中心
static point3D A(2.0f,0.0f,0.0),B(2.0f,1.0f,0.0),C(0.0f,1.0f,0.0),D(1.0f,1.0f,1.0);//如图7-41
void initial(void)
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}
void triangle (GLsizei mode)
{
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT ,vp); //获得视区的左下角坐标、宽度和高度信息
    int w = vp[2], h = vp[3];
    float aspect;
    if(w < h)
    {
        aspect = (float)w/(float)h;
    }
    else
    {
        aspect = (float)h/(float)w;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(mode==1)
    {
        setLookAt(iMode,s_eye,s_at);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-5.0,5.0,-5.0,5.0,-5,5);
        objectID=getTetrahedron(A, B, C, D);
        axisID=getAxis(3.0);
        glCallList(objectID);
        glCallList(axisID);
    }
    else if(mode==2)
    {
        setLookAt(xRot,yRot,zRot,s_eye,s_at);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45,aspect,-5,5);
        objectID=getTetrahedron(A, B, C, D);
        axisID=getAxis(3.0);
        glCallList(objectID);
        glCallList(axisID);
    }
}
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glViewport(0, 0, 200, 200);  // 左视区
    triangle(1);
    glViewport(200, 0, 200, 200);  // 右视区
    triangle(2);
    glutSwapBuffers();
}
void ChangeSize(int w,int h)
{
    winWidth=w; winHeight=h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void ProcessMenu(int value)
{
    iMode=value;
    glutPostRedisplay();
}
void Key(unsigned char key,int x,int y)
{
    if(key=='x')
    {
        xRot+=1;
    }
    if(key=='y')
    {
        yRot+=1;
    }
    if(key=='z')
    {
        zRot+=1;
    }
    glutPostRedisplay();//刷新
}
void SpecialKeys(int key,int x,int y)
{
    if(key == GLUT_KEY_UP)
    {
        angle = angle+2;
    }
    else if(key == GLUT_KEY_DOWN)
    {
        angle = angle-2;
    }
    glutPostRedisplay();//刷新
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE  | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("徐昊博21013134第三次拓展实验");
    int nGlutPolyMenu = glutCreateMenu(ProcessMenu);//创建菜单并定义菜单回调函数
    glutAddMenuEntry("front view XOZ(V)",1);
    glutAddMenuEntry("vertical view XOY(H)",2);
    glutAddMenuEntry("side view YOZ(W)",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);//主菜单与鼠标右键关联
    initial();
    glutDisplayFunc(Display);		//指定窗口重绘响应函数
    glutReshapeFunc(ChangeSize);    //指定窗口大小改变响应函数
    glutKeyboardFunc(Key);        //指定键盘响应函数
    glutSpecialFunc(SpecialKeys);   //指定功能键响应函数
    glutMainLoop();
    return 0;
}

