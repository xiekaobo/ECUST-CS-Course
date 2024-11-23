#include <GL/freeglut.h>
#include <math.h>
#include <vector>
#define max_iteration_num 6
using namespace std;

struct Vertex{
	GLfloat x,y;
};
vector<Vertex> V[max_iteration_num+1];//6个容器分别记录6次迭代的数据（0、1、2、3、4、5、6）
int iteration_num=0;//记录迭代次数

//用户初始化函数
void myinit(void)
{
	//设置清除屏幕的颜色
	glClearColor(1.0f,1.0f,1.0f,1.0f);

	Vertex Start,End;//初始元（直线段）的两个端点
	//初始元（直线段）的两个端点
	Start.x=0.0;
	Start.y=400.0;
	End.x=800.0;
	End.y=400.0;
	//第零次迭代（没迭代）
	V[0].push_back(Start);
	V[0].push_back(End);
}

//窗口大小变化时的回调函数
void myReshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0.0,800.0,0.0,800.0);
}
//计算当前迭代次数下的各顶点坐标
void compute()
{
	static int tmp=0;//记录上次绘制时迭代次数
	int flag=0;//记录迭代次数是否被更新过
	if(tmp<iteration_num){
		int len=V[iteration_num-1].size();
		for(int i=0;i<len-1;i++){
			V[iteration_num].push_back(V[iteration_num-1][i]);
			Vertex tmp;
			tmp.x=V[iteration_num-1][i].x+(V[iteration_num-1][i+1].x-V[iteration_num-1][i].x)/3;
			tmp.y=V[iteration_num-1][i].y+(V[iteration_num-1][i+1].y-V[iteration_num-1][i].y)/3;
			V[iteration_num].push_back(tmp);
			tmp.x=(V[iteration_num-1][i].x+V[iteration_num-1][i+1].x)/2+(V[iteration_num-1][i].y-V[iteration_num-1][i+1].y)*sqrt(3.0)/6;
			tmp.y=(V[iteration_num-1][i].y+V[iteration_num-1][i+1].y)/2+(V[iteration_num-1][i+1].x-V[iteration_num-1][i].x)*sqrt(3.0)/6;
			V[iteration_num].push_back(tmp);
			tmp.x=V[iteration_num-1][i].x+2*(V[iteration_num-1][i+1].x-V[iteration_num-1][i].x)/3;
			tmp.y=V[iteration_num-1][i].y+2*(V[iteration_num-1][i+1].y-V[iteration_num-1][i].y)/3;
			V[iteration_num].push_back(tmp);
		}
		V[iteration_num].push_back(V[iteration_num-1][len-1]);
		tmp=iteration_num;
	}
}
//每桢OpenGL都会调用这个函数，用户应该把显示代码放在这个函数中
void display(void)
{
	//清除屏幕缓冲
    glClear(GL_COLOR_BUFFER_BIT);
	compute();
	//开始绘制
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_STRIP);
		for(int i=0;i<V[iteration_num].size();i++){
			glVertex2f(V[iteration_num][i].x,V[iteration_num][i].y);
		}
	glEnd();
	//交换前后缓冲区
	glutSwapBuffers();
}
void processNormalKeys(unsigned char key,int x,int y)
{
	switch(key) {
		case 97:	//按a增加迭代次数
			if(iteration_num<max_iteration_num){
				iteration_num++;
			}
			break;
		case 100:	//按d减少迭代次数
			if(iteration_num>0){
				iteration_num--;
			}
			break;
		case 27:	//"esc"
			exit(0);
	}
	glutPostRedisplay();
}

//主函数
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//初始化OPENGL显示方式
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	//设定OPENGL窗口位置和大小
	glutInitWindowSize (800, 800);
	glutInitWindowPosition (100, 100);
	//打开窗口
	glutCreateWindow ("kock曲线");
	//调用初始化函数
    myinit();
	//设定窗口大小变化的回调函数
	glutReshapeFunc(myReshape);
	//设定键盘控制的回调函数
	glutKeyboardFunc(processNormalKeys);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}


