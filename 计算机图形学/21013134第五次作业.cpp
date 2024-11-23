#include <gl/glut.h>
void Initial(void)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}
void ChangeSize(int w,int h)
{
    if(h==0) h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fAspect;
    fAspect=(float)w/(float)h;
    gluPerspective(45.0,fAspect,1.0,700.0);
    glMatrixMode(GL_MODELVIEW);
}
void Display(void)
{
    static float fElect1=0.0f;
    static float fElect2=0.0f;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //画太阳
    glTranslatef(0.0f,0.0f,-250.0f);
    glColor3f(1.0f,0.0f,0.0f);
    glutSolidSphere(24.0f,15,15);
    //画地球
    glPushMatrix();// 保存当前的模型视图矩阵
    glColor3f(0.0f,0.0f,1.0f);
    glRotatef(fElect1,0.0f,0.0f,1.0f);
    glTranslatef(90.0f,0.0f,0.0f);
    glutSolidSphere(10.0f,15,15);
    //画月亮,注意此时还不能恢复到绘制地球前的模型视图矩阵，否则月亮也会绕着太阳转
    glColor3f(1.0f,1.0f,0.0f);
    glRotatef(fElect2,0.0f,0.0f,1.0f);
    glTranslatef(30.0f,0.0f,0.0f);
    glutSolidSphere(6.0f,15,15);
    glPopMatrix();//恢复到绘制地球前的模型视图矩阵
    glPopMatrix();//恢复到初始的模型视图矩阵

    fElect1+=1.0f;
    fElect2+=10.0f;
    if(fElect1>360.0f) fElect1=1.0f;
    if(fElect2>360.0f) fElect2=10.0f;
    glutSwapBuffers();
}
void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100,TimerFunc,1);
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH); //初始化窗口的显示模式
    glutCreateWindow("徐昊博21013134太阳月亮地球模型"); //创建一个名为矩形的窗口
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(Display);
    glutTimerFunc(500,TimerFunc,1); //设置当前窗口的显示回调函数
    Initial(); //完成窗口初始化
    glutMainLoop(); //启动主GLUT事件处理循环
    return 0;
}
