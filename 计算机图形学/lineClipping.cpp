#include <vector>
using namespace std;
#include "lineClipping.h"
/***********************************************
*如果p参数<0，计算、更新umax，保证umax是最大u值
*如果p参数>0，计算、更新umin，保证umin是最小u值
*如果umax>umin，返回0，否则返回1
***********************************************/
int Clip_Top(float p,float q,float &umax,float &umin){	
	float r=0.0;
    if(p<0.0)	//线段从裁剪窗口外部延伸到内部，取最大值r并更新umax
	{  
		r=q/p;
		if (r>umin) return 0;	//umax>umin的情况，弃之
		else if (r>umax)  umax=r; 
	}
	else if(p>0.0)      //线段从裁剪窗口内部延伸到外部,取最小值r并更新umin
		{  
			r=q/p;
			if (r<umax) return 0;	//umax>umin的情况，弃之
			else if(r<umin)  umin=r; 
		}
	   else 		//p=0时，线段平行于裁剪窗口
	      if(q<0.0) return 0;
	 return 1;
}
/*************************************************************
*已知winRect：矩形对象，存放标准裁剪窗口4条边信息
*    points：点的动态数组，存放直线2个端点信息
*根据裁剪窗口的左、右边界，求umax；
*根据裁剪窗口的下、上边界，求umin
*如果umax>umin，裁剪窗口和直线无交点，否则求裁剪后直线新端点
***************************************************************/
void Line_Clipping(vector<point> &points,rect & winRect){
	//比较左、右边界，获得最大的umax
	point &p1=points[0],&p2=points[1];
	float dx=p2.x-p1.x,dy=p2.y-p1.y,umax=0.0,umin=1.0;		  
	point p=p1;
	if (Clip_Top(-dx,p1.x- winRect.w_xmin,umax,umin))  //左边界
		if (Clip_Top(dx,winRect.w_xmax-p1.x, umax,umin)) //右边界
			//比较下、上边界，获得最小的umin
			if (Clip_Top(-dy,p1.y- winRect.w_ymin, umax,umin)) //下边界
				if (Clip_Top(dy,winRect.w_yman-p1.y, umax,umin)) //上边界
				{//求裁剪后直线新端点	
					p1.x=(int)(p.x+umax*dx);
					p1.y=(int)(p.y+umax*dy);
					p2.x=(int)(p.x+umin*dx);
					p2.y=(int)(p.y+umin*dy);
				}
} 