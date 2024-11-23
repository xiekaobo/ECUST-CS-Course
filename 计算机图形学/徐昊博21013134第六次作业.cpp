#include<gl/glut.h>
#include<math.h>
#include <vector>
using namespace std;
int winWidth=600,winHeight=600;
struct Vertex{
	GLfloat x,y;
};
vector<Vertex> V[7];//6个容器分别记录6次迭代的数据（0、1、2、3、4、5、6）
int num=0;
void Initial(void)
{
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	Vertex Start,End;
	Start.x=100.0;
	Start.y=300.0;
	End.x=500.0;
	End.y=300.0;
	V[0].push_back(Start);
	V[0].push_back(End);
}
void ChangeSize(int w,int h)
{
    winWidth=w; winHeight=h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void compute()
{
	static int tmp=0;//记录上次绘制时迭代次数
	int flag=0;//记录迭代次数是否被更新过
	if(tmp<num){
		int len=V[num-1].size();
		for(int i=0;i<len-1;i++){
			V[num].push_back(V[num-1][i]);
			Vertex tmp;
			tmp.x=V[num-1][i].x+(V[num-1][i+1].x-V[num-1][i].x)/3;
			tmp.y=V[num-1][i].y+(V[num-1][i+1].y-V[num-1][i].y)/3;
			V[num].push_back(tmp);
			tmp.x=(V[num-1][i].x+V[num-1][i+1].x)/2+(V[num-1][i].y-V[num-1][i+1].y)*sqrt(3.0)/6;
			tmp.y=(V[num-1][i].y+V[num-1][i+1].y)/2+(V[num-1][i+1].x-V[num-1][i].x)*sqrt(3.0)/6;
			V[num].push_back(tmp);
			tmp.x=V[num-1][i].x+2*(V[num-1][i+1].x-V[num-1][i].x)/3;
			tmp.y=V[num-1][i].y+2*(V[num-1][i+1].y-V[num-1][i].y)/3;
			V[num].push_back(tmp);
		}
		V[num].push_back(V[num-1][len-1]);
		tmp=num;
	}
}
void Display(void)
{
	//清除屏幕缓冲
    glClear(GL_COLOR_BUFFER_BIT);
	compute();
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_LINE_STRIP);
		for(int i=0;i<V[num].size();i++){
			glVertex2f(V[num][i].x,V[num][i].y);
		}
	glEnd();
	glutSwapBuffers();
}
void Key(unsigned char key,int x,int y)
{
	switch(key) {
		case 'a':	//按a增加迭代次数
			if(num<6)
            {
            num++;
            }
			break;
		case 'b':	//按d减少迭代次数
			if(num>0)
            {
				num--;
			}
			break;
	}
	glutPostRedisplay();
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); //初始化窗口的显示模式
    glutInitWindowSize(600,600); //设置窗口的尺寸
    glutInitWindowPosition(100,100); //设置窗口的位置
    glutCreateWindow("徐昊博21013134第6次作业");//创建窗口
    glutKeyboardFunc(Key);
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);
    Initial(); //完成窗口初始化
    glutMainLoop(); //启动主GLUT事件处理循环
    return 0;
}
