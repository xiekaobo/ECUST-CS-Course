#include <vector>
using namespace std;
#include <GL/glut.h>
#include "graphicType.h"
//绘制折线
void drawPolygonalLine(vector<point> &points,color &c ){//根据点序列向量数组points，绘制折线	 
	glColor3f(c.r, c.g, c.b); 
	glBegin (GL_LINE_STRIP);
		for(int i=0;i<points.size();i++){
			glVertex2i(points[i].x, points[i].y);
		}		
	glEnd();
}
//绘制折线
void drawPolygonalLine(vector<point> &points ,point &p,color &c){//根据点序列向量数组points，绘制折线	
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
void drawBezierCurve(vector<Point> &points,int n,color &c){	
}
 
 