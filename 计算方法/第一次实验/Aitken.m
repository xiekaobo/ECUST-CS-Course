function y0=Aitken(x,y,x1)
%x,y是已知的差值点坐标点,x1为插值点
%徐昊博21013134第二题
n=length(x);
A=zeros(n,n);
for i=1:n
    A(i,1)=y(i);
end
for i=2:n
    A(i,2)=(x1-x(i))/(x(1)-x(i))*y(1)+(x1-x(1))/(x(i)-x(1))*y(i);
end
for i=3:n
    for j=i:n
        A(j,i)=(x1-x(j))/(x(i-1)-x(j))*A(i-1,i-1)+(x1-x(i-1))/(x(j)-x(i-1))*A(j,i-1);
    end
end
y0=A(n,n);
end