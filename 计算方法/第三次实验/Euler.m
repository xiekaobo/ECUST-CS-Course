function E =Euler(f,a,b,N,ya)
%21013134徐昊博
%f是微分方程右端函数句柄
%a,b是自变量的取值区间[a,b]的端点
%N是区间等分的个数
%ya表初值y(a)
%E=[x',y']是自变量X和解Y所组成的矩阵。x'表示x向量的转置，便于视觉上观察
h=(b-a)/N;
y=zeros(1,N+1);
x=zeros(1,N+1);
y(1)=ya;
x=a:h:b;
for i=1:N
    y(i+1)=y(i)+h*feval(f,x(i),y(i));
end
E=[x',y'];
end