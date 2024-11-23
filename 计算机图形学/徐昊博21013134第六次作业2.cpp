#include <GL/freeglut.h>
#include <math.h>
#include <vector>
using namespace std;
int winWidth=600,winHeight=600;
struct Vertex{
	GLfloat x,y;
};
vector<Vertex> V[3][7];//分别记录3条边各自6次迭代的数据（0、1、2、3、4、5、6）
int num=0;//记录迭代次数
//用户初始化函数
void Initial(void)
{
	//设置清除屏幕的颜色
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	Vertex Start[3],End[3];//初始元（三角形）的三个端点（每条边两个，有重合的）
	Start[0].x=100.0;
	Start[0].y=200.0;
	End[0].x=500;
	End[0].y=200;
	Start[1].x=End[0].x;
	Start[1].y=End[0].y;
	End[1].x=300;
	End[1].y=200+200*sqrt(3);
	Start[2].x=End[1].x;
	Start[2].y=End[1].y;
	End[2].x=Start[0].x;
	End[2].y=Start[0].y;
	//第零次迭代（没迭代）
	for(int i=0;i<3;i++){
		V[i][0].push_back(Start[i]);
		V[i][0].push_back(End[i]);
	}

}
void ChangeSize(int w,int h)
{
    winWidth=w; winHeight=h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
//计算当前迭代次数下的各顶点坐标
void compute()
{
	static int tmp=0;//记录上次绘制时迭代次数
	int flag=0;//记录迭代次数是否被更新过
	if(tmp<num){
		int len=V[0][num-1].size();
		for(int j=0;j<3;j++){
			for(int i=0;i<len-1;i++){
				V[j][num].push_back(V[j][num-1][i]);
				Vertex tmp;
				tmp.x=V[j][num-1][i].x+(V[j][num-1][i+1].x-V[j][num-1][i].x)/3;
				tmp.y=V[j][num-1][i].y+(V[j][num-1][i+1].y-V[j][num-1][i].y)/3;
				V[j][num].push_back(tmp);
				tmp.x=(V[j][num-1][i].x+V[j][num-1][i+1].x)/2-(V[j][num-1][i].y-V[j][num-1][i+1].y)*sqrt(3.0)/6;
				tmp.y=(V[j][num-1][i].y+V[j][num-1][i+1].y)/2-(V[j][num-1][i+1].x-V[j][num-1][i].x)*sqrt(3.0)/6;
				V[j][num].push_back(tmp);
				tmp.x=V[j][num-1][i].x+2*(V[j][num-1][i+1].x-V[j][num-1][i].x)/3;
				tmp.y=V[j][num-1][i].y+2*(V[j][num-1][i+1].y-V[j][num-1][i].y)/3;
				V[j][num].push_back(tmp);
			}
			V[j][num].push_back(V[j][num-1][len-1]);
		}
		tmp=num;
	}
}
//每桢OpenGL都会调用这个函数，用户应该把显示代码放在这个函数中
void Display(void)
{
	//清除屏幕缓冲
    glClear(GL_COLOR_BUFFER_BIT);
	compute();
	//开始绘制
	glColor3f(1.0f,0.0f,0.0f);
	for(int j=0;j<3;j++){
		glBegin(GL_LINE_STRIP);
		for(int i=0;i<V[j][num].size();i++){
			glVertex2f(V[j][num][i].x,V[j][num][i].y);
		}
		glEnd();
	}
	//交换前后缓冲区
	glutSwapBuffers();
}
void Key(unsigned char key,int x,int y)
{
	switch(key) {
		case 97:	//按a增加迭代次数
			if(num<6){
				num++;
			}
			break;
		case 100:	//按d减少迭代次数
			if(num>0){
				num--;
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


