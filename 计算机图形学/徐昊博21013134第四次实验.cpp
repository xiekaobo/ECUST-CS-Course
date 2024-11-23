#include <vector>
using namespace std;
#include <GL/glut.h>
#include "graphicType.h"
//绘制折线
vector <point> pointVertex;   //控制多边形顶点序列
point temp,mouse;   //控制多边形顶点序列
bool isEnd=false;			  //标识控制多边形是否确定
const GLint ControlN=4;       //由4个控制点定义三次bezier曲线段
color redColor(1,0,0),blackColor(0,0,0);//红色、黑色
int x,y,p;
int winWidth = 600, winHeight = 600;
static GLsizei iMode=1;
void drawPolygonalLine(vector<point> &points,color &c ){
    //根据点序列向量数组points，绘制折线
	glColor3f(c.r, c.g, c.b);
	glBegin (GL_LINE_STRIP);
		for(int i=0;i<points.size();i++){
			glVertex2i(points[i].x, points[i].y);
		}
	glEnd();
}
//绘制折线
void drawPolygonalLine(vector<point> &points ,point &p,color &c){
    //根据点序列向量数组points，绘制折线
	glColor3f(c.r, c.g, c.b);
	glBegin (GL_LINE_STRIP);
		for(int i=0;i<points.size();i++){
			glVertex2i(points[i].x, points[i].y);
		}
		glVertex2i(p.x, p.y);
	glEnd();
}
//如果控制点数n<4，绘制一段n-1次Bezier曲线段，否则绘制一段三次Bezier曲线
void drawBezierCurve(vector<Point> &points,color &c){
	GLfloat ControlP[4][3];
	int iPointNum=points.size();
	int i;
	if(iPointNum<4){//控制点数<4，绘制一段n-1次Bezier曲线段
		for(i=0;i<iPointNum;i++){
			ControlP[i][0]=points[i].x;
			ControlP[i][1]=points[i].y;
			ControlP[i][2]=0.0;
		}
	}
	else{
		for(i=0;i<4;i++){//控制点数>=4，绘制一段三次Bezier曲线段
			ControlP[i][0]=points[i].x;
			ControlP[i][1]=points[i].y;
			ControlP[i][2]=0.0;
		}
	}
	glColor3f(c.r, c.g, c.b);
	glPointSize(2);
	if(iPointNum>4)
		glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,*ControlP);//定义一维取值器
	else
		glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,iPointNum,*ControlP);//定义一维取值器
	glEnable(GL_MAP1_VERTEX_3);
	glMapGrid1f(100,0.0,1.0);//生成均匀分布的一维网格参数值
	glEvalMesh1(GL_LINE, 0, 100);//绘制Bezier曲线
}
//通过（m×3+1）控制点，绘制m段n-1次ezier曲线段
void drawBezierCurve(vector<Point> &points,int n,color &c)
{
    GLfloat ControlP[4][3];
	int iPointNum=points.size();
	int i,temp=0;
	while(temp<iPointNum)
    {
    if((iPointNum-temp)<4)
    {//控制点数<4，绘制一段n-1次Bezier曲线段
        p=iPointNum-temp;
        for(i=0;i<p;i++)
        {
            ControlP[i][0]=points[temp].x;
            ControlP[i][1]=points[temp].y;
            ControlP[i][2]=0.0;
            temp++;
        }
        glColor3f(c.r, c.g, c.b);
        glPointSize(2);
        glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,p,*ControlP);
        glEnable(GL_MAP1_VERTEX_3);
        glMapGrid1f(100,0.0,1.0);//生成均匀分布的一维网格参数值
        glEvalMesh1(GL_LINE, 0, 100);//绘制Bezier曲线
    }
    if((iPointNum-temp)>=4)
    {
        for(i=0;i<4;i++)
        {//控制点数>=4，绘制一段三次Bezier曲线段
            ControlP[i][0]=points[temp].x;
            ControlP[i][1]=points[temp].y;
            ControlP[i][2]=0.0;
            temp++;
        }
        glColor3f(c.r, c.g, c.b);
        glPointSize(2);
        glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,*ControlP);
        glEnable(GL_MAP1_VERTEX_3);
        glMapGrid1f(100,0.0,1.0);//生成均匀分布的一维网格参数值
        glEvalMesh1(GL_LINE, 0, 100);//绘制Bezier曲线
        temp--;
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
    if(isEnd==false&&iMode==4)
    {
        glLineStipple(1,0x00FF);
        glEnable(GL_LINE_STIPPLE);
        drawPolygonalLine(pointVertex,mouse,blackColor);
    }
    if(isEnd==true&&iMode==4)
    {
        drawPolygonalLine(pointVertex,mouse,blackColor);
        glDisable(GL_LINE_STIPPLE);
        drawBezierCurve(pointVertex,4,redColor);
    }
    glutSwapBuffers();
}
void MousePlot(GLint button, GLint action,GLint xMouse,GLint yMouse)
{
    if(button==GLUT_LEFT_BUTTON&&action==GLUT_DOWN&&iMode==4)
    {
        temp.x=xMouse;
        temp.y=winHeight-yMouse;
        pointVertex.push_back(temp);
    }
    if(button==GLUT_RIGHT_BUTTON&&action==GLUT_DOWN&&iMode==4)
    {
        isEnd=true;
    }
}
void PassiveMouseMove(GLint xMouse,GLint yMouse)
{
    if(isEnd==false)
    {
        mouse.x=xMouse;
        mouse.y=winHeight-yMouse;
        pointVertex.push_back(temp);
        glutPostRedisplay();
        pointVertex.pop_back();
    }
}
void ProcessMenu(int value)
{
    iMode=value;
    glutPostRedisplay();
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); //初始化窗口的显示模式
    glutInitWindowSize(600,600); //设置窗口的尺寸
    glutInitWindowPosition(100,100); //设置窗口的位置
    glutCreateWindow("徐昊博21013134第四次实验");//创建窗口
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("DrawBezier",4);
    glutAddMenuEntry("DrawBezier2",5);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(MousePlot);
    glutPassiveMotionFunc(PassiveMouseMove);
    Initial(); //完成窗口初始化
    glutMainLoop(); //启动主GLUT事件处理循环
    return 0;
}
