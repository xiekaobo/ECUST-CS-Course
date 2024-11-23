#include <gl/glut.h>
#include <stdio.h>
#include <vector>

using namespace std;
#include "lineClipping.h"

int iPointNum = 0, iKeyPointNum = 0;							//已经确定的点的数量
int xKey1 = 0, yKey1 = 0, xKey2 = 0, yKey2 = 0;					//记录当前折线点
int m_x1 = 0, m_x2 = 0, m_y1 = 0, m_y2 = 0;						//记录当前矩形点
int winWidth = 400, winHeight = 300;							//初始窗口大小
bool endDrow = false;											//是否结束折线输入
int ctimes = 0;													//是否进行了Liang_Barsky算法

vector<point> m_points;		//折线点数组
rect m_winRect;				//裁剪框

/***********************************************
*如果p参数<0，计算、更新umax，保证umax是最大u值
*如果p参数>0，计算、更新umin，保证umin是最小u值
*如果umax>umin，返回0，否则返回1
***********************************************/
int Clip_Top(float p, float q, float& umax, float& umin) {
	float r = 0.0;
	if (p < 0.0)	//线段从裁剪窗口外部延伸到内部，取最大值r并更新umax
	{
		r = q / p;
		if (r > umin) return 0;	//umax>umin的情况，弃之
		else if (r > umax)  umax = r;
	}
	else if (p > 0.0)      //线段从裁剪窗口内部延伸到外部,取最小值r并更新umin
	{
		r = q / p;
		if (r < umax) return 0;	//umax>umin的情况，弃之
		else if (r < umin)  umin = r;
	}
	else 		//p=0时，线段平行于裁剪窗口
		if (q < 0.0) return 0;
	return 1;
}
/*************************************************************
*已知winRect：矩形对象，存放标准裁剪窗口4条边信息
*    points：点的动态数组，存放直线2个端点信息
*根据裁剪窗口的左、右边界，求umax；
*根据裁剪窗口的下、上边界，求umin
*如果umax>umin，裁剪窗口和直线无交点，否则求裁剪后直线新端点
***************************************************************/
void Line_Clipping(vector<point>& points, rect& winRect) {		//(折线点数组,裁剪框)
	vector<point> new_points;								//存储裁剪结果
	for (int i = 0; i < iKeyPointNum - 1; i++)
	{
		while (new_points.size() <= 2 * i + 2)
		{
			new_points.push_back((0, 0));
		}
		point& p1 = points[i], & p2 = points[i + 1];
		float dx = p2.x - p1.x, dy = p2.y - p1.y, umax = 0.0, umin = 1.0;
		point p = p1;
		//比较左、右边界，获得最大的umax
		if (Clip_Top(-dx, p1.x - winRect.w_xmin, umax, umin))  //左边界
			if (Clip_Top(dx, winRect.w_xmax - p1.x, umax, umin)) //右边界
				//比较下、上边界，获得最小的umin
				if (Clip_Top(-dy, p1.y - winRect.w_ymin, umax, umin)) //下边界
					if (Clip_Top(dy, winRect.w_ymax - p1.y, umax, umin)) //上边界
					{		//求裁剪后直线新端点
						new_points[2 * i].x = (int)(p.x + umax * dx);
						new_points[2 * i].y = (int)(p.y + umax * dy);
						new_points[2 * i + 1].x = (int)(p.x + umin * dx);
						new_points[2 * i + 1].y = (int)(p.y + umin * dy);
					}
	}

	//结果赋值给原Vector
	for (int i = 0; i < new_points.size(); i++)
	{
		while (m_points.size() < new_points.size())
		{
			m_points.push_back((0, 0));
		}
		m_points[i] = new_points[i];
	}
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //用当前背景色填充窗口
	glColor3f(1.0f, 0.0f, 0.0f); //设置当前的绘图颜色为红色

	//绘制矩形窗口
	if (iPointNum >= 1) {
		if (1) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(m_x1, m_y1, 0.0);
			glVertex3f(m_x2, m_y1, 0.0);
			glVertex3f(m_x2, m_y2, 0.0);
			glVertex3f(m_x1, m_y2, 0.0);
			glEnd();
		}
	}

	//绘制折线段
	if (iKeyPointNum >= 1) {
		for (int i = 0; i < m_points.size() - 2; i++)
		{
			glBegin(GL_LINES);
			glVertex3f(m_points[i].x, m_points[i].y, 0.0);
			glVertex3f(m_points[i + 1].x, m_points[i + 1].y, 0.0);
			glEnd();
		}
		//动态显示当前绘制折线段（用数组则出现错误?）
		if (!endDrow) {
			glBegin(GL_LINES);
			glVertex3f(xKey1, yKey1, 0.0);
			glVertex3f(xKey2, yKey2, 0.0);
			glEnd();
		}
	}

	glutSwapBuffers();
}
void reStart() {
	endDrow = false;
	iKeyPointNum = 0;
	m_points.clear();
	m_points.push_back((0, 0));
	ctimes = 0;
}
void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (iPointNum == 0 || iPointNum == 2) {
			iPointNum = 1;
			m_x1 = xMouse;
			m_y1 = winHeight - yMouse;
		}
		else
		{
			iPointNum = 2;
			m_x2 = xMouse;
			m_y2 = winHeight - yMouse;
			rect temp(min(m_x1, m_x2), min(m_y1, m_y2), max(m_x1, m_x2), max(m_y1, m_y2));		//创建裁剪框
			m_winRect = temp;
			glutPostRedisplay();
		}
		reStart();
		glutPostRedisplay();
	}
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
		iPointNum = 0;
		glutPostRedisplay();
	}
}


//动态显示当前线段
void PassiveMouseMove(GLint xMouse, GLint yMouse) {
	//绘制裁剪框
	if (iPointNum == 1) {
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			m_x2 = xMouse;
			m_y2 = m_y1 + m_x2 - m_x1;
		}
		else {
			m_x2 = xMouse;
			m_y2 = winHeight - yMouse;
		}
		glutPostRedisplay();
	}

	//绘制折线
	if (!endDrow) {
		xKey2 = xMouse;
		yKey2 = winHeight - yMouse;
		point temp = (xKey2, yKey2);
		m_points[iKeyPointNum] = temp;
		glutPostRedisplay();
	}
}

void Key(unsigned char key, int x, int y) {
	switch (key) {
	case'p':			//确定折线端点
		if (!endDrow) {
			xKey1 = x;
			yKey1 = winHeight - y;
			//存入端点
			point temp(xKey1, yKey1);
			if (m_points.size() < iKeyPointNum + 2) {
				m_points.push_back(temp);
			}
			m_points[iKeyPointNum] = temp;
			iKeyPointNum++;
			glutPostRedisplay();
		}
		else {
			reStart();
		}
		break;
	case'c':			//执行Liang_Barsky裁剪
		if (endDrow && iPointNum == 2&& ctimes==0) {
			Line_Clipping(m_points, m_winRect);
			ctimes = 1;
			glutPostRedisplay();
		}
		else {
			reStart();
		}
		break;
	case'e':			//结束绘制折线
		endDrow = true;
		glutPostRedisplay();
		break;
	default:break;
	}
}

void ChangeSize(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);					//设置投影参数(指定要控制的单元)
	glLoadIdentity();								//调用单位矩阵。去掉以前的投影参数设置
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);		//设置投影参数
}

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //设置窗口背景颜色为白色
	m_points.push_back((0, 0));
}

int min(int a, int b) {
	if (a > b) {
		return b;
	}
	else {
		return a;
	}
}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);				//初始化窗口的显示模式
	glutInitWindowSize(winWidth, winHeight);					//设置窗口的尺寸
	glutInitWindowPosition(100, 100);							//设置窗口的位置

	glutCreateWindow("橡皮筋技术");

	glutDisplayFunc(Display);									//设置当前窗口的显示回调函数
	glutReshapeFunc(ChangeSize);								//当窗口大小改变时函数被调用

	glutMouseFunc(MousePlot);
	glutKeyboardFunc(Key);
	glutPassiveMotionFunc(PassiveMouseMove);


	Initial();													//完成窗口初始化
	glutMainLoop();												//启动主GLUT事件处理循环
	return 0;
}
