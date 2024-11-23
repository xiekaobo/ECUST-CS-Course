#include<iostream>
#include<vector>
#include<windows.h>
#include<gl/glut.h>
#include "setLookAt.h"
#include "getAxis.h"
#include "getTetrahedron.h"
using namespace std;
GLuint objectID, axisID;				//四面体对象ID、坐标轴ID、
int winWidth = 800, winHeight = 400;	//窗口的宽度和高度
static float angle = 45.0;				//angle绕坐标轴的旋转角
static GLfloat xRot = 0.0f;				//旋转参数
static GLfloat yRot = 0.0f;				//旋转参数
static GLfloat zRot = 0.0f;				//旋转参数
static GLsizei iMode = 1;				//菜单值
static point3D s_eye(5.0, 5.0, 5.0);	//观察点位置
static point3D s_at(0.0, 0.0, 0.0);		//视点中心
static point3D A(2.0f, 0.0f, 0.0), B(2.0f, 1.0f, 0.0), C(0.0f, 1.0f, 0.0), D(1.0f, 1.0f, 1.0);//如图7-41

void Initial(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	objectID = getTetrahedron(A, B, C, D);//绘制四面体
	axisID = getAxis(3);
}

void Triangle(GLsizei mode){
	float x;
	if (winWidth > winHeight * 2) x = (float)(winHeight) / ((float)winWidth / 2.0);
	else { x = ((float)winWidth / 2) / (float)(winHeight); }
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3 * x, 3 * x, -3 * x, 3 * x, -20, 20);
	if (mode == 1) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		setLookAt(iMode, s_eye, s_at);//设置三视图菜单
		glCallList(objectID);
		glCallList(axisID);
		glPopMatrix();
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glMatrixMode(GL_PROJECTION);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(s_eye.x, s_eye.y, s_eye.z, 0, 0, 0, 0, 1, 0);
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glEnable(GL_POLYGON_STIPPLE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCallList(objectID);
		glRectf(50.0f, 100.0f, 150.0f, 50.0f);
		glDisable(GL_POLYGON_STIPPLE);
		glLineWidth(5.0);
		glColor4f(0.0, 0.6, 1.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glCallList(objectID);
		glCallList(axisID);
		glPopMatrix();
		getAxis(2);
	}
}

void rotateX(float degree)
{
	degree *= PI / 180;
	double tmp = s_eye.y * cos(degree) - s_eye.z * sin(degree);
	s_eye.z = s_eye.y * sin(degree) + s_eye.z * cos(degree);
	s_eye.y = tmp;
}

void rotateY(float degree)
{
	degree *= PI / 180;
	float tmp = s_eye.z * sin(degree) + s_eye.x * cos(degree);
	s_eye.z = s_eye.z * cos(degree) - s_eye.x * sin(degree);
	s_eye.x = tmp;
}

void Key(int key,int x,int y){
	switch (key) {
	case GLUT_KEY_UP: {
		rotateX(1);
		break;
	}
	case GLUT_KEY_DOWN: {
		rotateX(-1);
		break;
	}
	case GLUT_KEY_LEFT: {
		rotateY(1);
		break;
	}
	case GLUT_KEY_RIGHT: {
		rotateY(-1);
		break;
	}
	default: break;
	}

	glutPostRedisplay();
}
void Display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);
	glViewport(0, 0, winWidth / 2, winHeight);
	Triangle(1);
	glColor3f(0, 0, 1);
	glViewport(winWidth / 2, 0, winWidth / 2, winHeight);
	Triangle(2);

	glFlush();
	glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
	winWidth = w;
	winHeight = h;
	glLoadIdentity();
	glutPostRedisplay();
}

void ProcessMenu(int value){
	iMode = value;
	glutPostRedisplay();
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Experiment3-多视区");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(Display);
	glutSpecialFunc(Key);//键盘响应事件按
	//定义主菜单，菜单项为“正视图XOZ(V)”、“侧视图YOZ(W)”和“俯视图XOY(H)”
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("FrontViewXOZ(V)", 1);
	glutAddMenuEntry("SideViewYOZ(W)", 2);
	glutAddMenuEntry("HeighViewXOY(H)", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	Initial();

	glutMainLoop();
	return 0;
}
