#include<gl/glut.h>
void Initial(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //设置窗口背景颜色为白色
    glMatrixMode(GL_PROJECTION); //设置投影参数
    gluOrtho2D(0.0,400.0,0.0,400.0);
}
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //用当前背景色填充窗口
    glColor3f(0.0f, 0.0f, 0.0f); //设置当前的绘图颜色为黑色
    glBegin(GL_POINTS);
    float x=0,y;
    while(x<=400)
    {
        y=300+50*sin(x/50);
        glVertex2f(x,y);
        x=x+0.5;
    }
    glEnd();
    glBegin(GL_POINTS);
    x=0;
    while(x<=400)
    {
        y=150+50*cos(x/50);
        glVertex2f(x,y);
        x=x+0.5;
    }
    glEnd();
    float x1=0,y1,x2=0,y2;
    glBegin(GL_LINE_STRIP);
    while(x2<=400)
    {
        y1=250+50*sin(x1/50);
        x2=x1+0.5;
        y2=250+50*sin(x2/50);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        x1+=0.5;
    }
    glEnd();
    x1=0;
    x2=0;
    glBegin(GL_LINE_STRIP);
    while(x2<=400)
    {
        y1=100+50*cos(x1/50);
        x2=x1+0.5;
        y2=100+50*cos(x2/50);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        x1+=0.5;
    }
    glEnd();
    glFlush();
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //初始化窗口的显示模式
    glutInitWindowSize(400,400); //设置窗口的尺寸
    glutInitWindowPosition(0,120); //设置窗口的位置
    glutCreateWindow("两个模式下的正弦余弦图，从上到下依次为正弦点模式，正弦折线模式，余弦点模式，余弦折线模式"); //创建窗口
    glutDisplayFunc(Display);
    Initial(); //完成窗口初始化
    glutMainLoop(); //启动主GLUT事件处理循环
    return 0;
}
