#include <gl/glut.h>
void Initial()
{
	glEnable(GL_DEPTH_TEST);       // 启用深度测试
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );	//背景为白色
}

void ChangeSize(int w, int h)
{
	if(h == 0)	h = 1;
    glViewport(0, 0, w, h);               // 设置视区尺寸
	glMatrixMode(GL_PROJECTION);    // 指定当前操作投影矩阵堆栈
	glLoadIdentity();                   // 重置投影矩阵

	GLfloat fAspect;
	fAspect = (float)w/(float)h;            // 计算视区的宽高比
	gluPerspective(45.0, fAspect, 1.0, 500.0); // 指定透视投影的观察空间
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display(void)
{
	static float fElect1 = 0.0f; // 地球绕太阳旋转的角度
    static float fElect2 = 0.0f; // 月亮绕地球旋转的角度

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色和深度缓冲区

    glMatrixMode(GL_MODELVIEW); // 指定当前操作模型视图矩阵堆栈
    glLoadIdentity();           // 重置模型视图矩阵
    glTranslatef(0.0f, 0.0f, -250.0f); // 将图形沿z轴负向移动

    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(20.0f, 15, 15); // 绘制红色的太阳

    glPushMatrix(); // 保存当前的模型视图矩阵
    glRotatef(fElect1, 0.0f, 0.0f, 1.0f); // 绕y轴旋转地球的角度
    glTranslatef(90.0f, 0.0f, 0.0f); // 平移一段距离
    glPushMatrix(); // 保存当前的模型视图矩阵

    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidSphere(10.0f, 15, 15); // 绘制地球
    glPopMatrix(); // 恢复模型视图矩阵

    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(fElect2, 0.0f, 0.0f, 1.0f); // 绕y轴旋转月亮的角度
    glTranslatef(30.0f, 0.0f, 0.0f); // 平移一段距离
    glutSolidSphere(5.0f, 15, 15); // 绘制月亮
    glPopMatrix(); // 恢复模型视图矩阵



    fElect1 += 10.0f; // 增加地球的旋转角度，产生动画效果
    fElect2 += 10.0f; // 增加月亮的旋转角度，产生动画效果
    if (fElect1 > 360.0f) fElect1 = 10.0f;
    if (fElect2 > 360.0f) fElect2 = 10.0f;

    glutSwapBuffers();
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("太阳、地球、月亮运动模型");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(Display);
    glutTimerFunc(500, TimerFunc, 1);     //指定定时器回调函数
	Initial();
	glutMainLoop();
	return 0;
}
