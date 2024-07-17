function [x,y]=Chord(f,x1,x2,emg)
%用弦截法解非线性方程的根
%f表示非线性方程左端函数
%x1,x2表示迭代初值
%emg是指标
%k表示循环次数
%徐昊博21013134
k=1;
x(k)=x1;
y(k)=feval(f,x1);
k=k+1;
x(k)=x2;
y(k)=feval(f,x2);
while abs(x(k)-x(k-1))>emg
    x(k+1)=x(k)-(x(k)-x(1))*y(k)/(y(k)-y(1));
    y(k+1)=feval(f,x(k+1));
    k=k+1;
end
end