#include <gl/glut.h>
void Initial(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //设置窗口背景颜色为白色
    glMatrixMode(GL_PROJECTION); //设置投影参数
    gluOrtho2D(0.0,1200.0,0.0,400.0);
}
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //用当前背景色填充窗口
    glColor3f(0.0f, 0.0f, 0.0f); //设置当前的绘图颜色为黑色
    glLineWidth(3.0);
    //绘制“徐”
    glBegin(GL_LINE_STRIP);
    glVertex2i(25,250);
    glVertex2i(100,325);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(25,175);
    glVertex2i(100,250);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(75,50);
    glVertex2i(75,225);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(75,50);
    glVertex2i(75,225);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(125,225);
    glVertex2i(225,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(225,350);
    glVertex2i(325,225);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(175,250);
    glVertex2i(275,250);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(150,175);
    glVertex2i(300,175);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(225,50);
    glVertex2i(175,75);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(150,100);
    glVertex2i(200,150);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(250,150);
    glVertex2i(300,100);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(225,250);
    glVertex2i(225,50);
    glEnd();
    //绘制“昊”
    glBegin(GL_LINE_STRIP);
    glVertex2i(500,350);
    glVertex2i(700,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(500,300);
    glVertex2i(700,300);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(500,250);
    glVertex2i(700,250);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(500,250);
    glVertex2i(500,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(700,250);
    glVertex2i(700,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(500,200);
    glVertex2i(700,200);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(450,150);
    glVertex2i(750,150);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(600,150);
    glVertex2i(600,200);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(600,150);
    glVertex2i(550,75);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(550,75);
    glVertex2i(475,50);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(600,150);
    glVertex2i(650,75);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(650,75);
    glVertex2i(725,50);
    glEnd();

    //绘制“博”
    glBegin(GL_LINE_STRIP);
    glVertex2i(850,250);
    glVertex2i(950,250);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(900,50);
    glVertex2i(900,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(975,325);
    glVertex2i(1125,325);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1075,375);
    glVertex2i(1100,350);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1050,350);
    glVertex2i(1050,175);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(975,300);
    glVertex2i(975,175);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1125,300);
    glVertex2i(1125,175);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(975,300);
    glVertex2i(1125,300);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1100,200);
    glVertex2i(1125,175);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1000,275);
    glVertex2i(1100,275);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1000,225);
    glVertex2i(1100,225);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(950,150);
    glVertex2i(1125,150);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1075,175);
    glVertex2i(1075,50);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1025,75);
    glVertex2i(1075,50);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2i(1025,125);
    glVertex2i(1050,100);
    glEnd();
    glFlush(); //处理所有的OpenGL程序
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //初始化窗口的显示模式
    glutInitWindowSize(1200,400); //设置窗口的尺寸
    glutInitWindowPosition(0,120); //设置窗口的位置
    glutCreateWindow("徐昊博21013134"); //创建一个名为矩形的窗口
    glutDisplayFunc(Display); //设置当前窗口的显示回调函数
    Initial(); //完成窗口初始化
    glutMainLoop(); //启动主GLUT事件处理循环
    return 0;
}
