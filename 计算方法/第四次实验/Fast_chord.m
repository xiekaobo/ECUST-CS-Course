function [x,y]=Fast_chord(f,x1,x2,emg)
%用快速弦截法解非线性方程的根
%f表示非线性方程左端函数
%x1,x2表示迭代初值
%emg是指标
%k表示循环次数
k=1;
y1=feval(f,x1);
y2=feval(f,x2);
x(k)=x2-(x2-x1)*y2/(y2-y1);
y(k)=feval(f,x(k));
k=k+1;
x(k)=x(k-1)-(x(k-1)-x2)*y(k-1)/(y(k-1)-y2);
while abs(x(k)-x(k-1))>emg
    y(k)=feval(f,x(k));
    x(k+1)=x(k)-(x(k)-x(k-1))*y(k)/(y(k)-y(k-1));
    k=k+1;
end