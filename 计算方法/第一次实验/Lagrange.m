function [y0,N] =Lagrange(X,Y,x0)
%X,Y是已知的差值点坐标点,x0为插值点
%徐昊博21013134第一题
m=length(X);
N=zeros(m,1);
y0=0;
for i=1:m
    N(i)=1;
    for j=1:m
        if j~=i
            N(i)=N(i)*(x0-X(j))/(X(i)-X(j));
        end
    end
    y0=y0+Y(i)*N(i);
end
end