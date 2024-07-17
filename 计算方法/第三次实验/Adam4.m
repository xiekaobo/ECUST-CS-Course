function A =Adam4(f,a,b,N,ya)
%21013134徐昊博
%f是微分方程右端函数句柄
%a,b是自变量的取值区间[a,b]的端点
%N是区间等分的个数
%ya表初值y(a)
%A=[x',y']是自变量X和解Y所组成的矩阵。x'表示x向量的转置，便于视觉上观察
if N<4
    return;
end  %为代码鲁棒性设计的特殊情况处理
h=(b-a)/N;
y=zeros(1,N+1);
x=zeros(1,N+1);
y(1)=ya;
x=a:h:b;
F=zeros(1,4);
for i=1:N
    if i<4    %用四阶Runge-Kutta法求初始解
       k1=feval(f,x(i),y(i));
       k2=feval(f,x(i)+h/2,y(i)+(h/2)*k1);
       k3=feval(f,x(i)+h/2,y(i)+(h/2)*k2);
       k4=feval(f,x(i)+h,y(i)+h*k3);
       y(i+1)=y(i)+(h/6)*(k1+2*k2+2*k3+k4);
    else
        F=[feval(f,x(i-3),y(i-3)),feval(f,x(i-2),y(i-2)),feval(f,x(i-1),y(i-1)),feval(f,x(i),y(i))];
        py=y(i)+(h/24)*(F*[-9,37,-59,55]');
        p=feval(f,x(i+1),py);
        F=[F(2),F(3),F(4),p];
        y(i+1)=y(i)+(h/24)*(F*[1,-5,19,9]');
    end
end
A=[x',y'];