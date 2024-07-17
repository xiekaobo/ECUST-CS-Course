function y0=Neville(X,Y,x0)
%X,Y是已知的差值点坐标点,x0为插值点
%徐昊博21013134第二题
m=length(X);
P=zeros(m,1);
P1=zeros(m,1);
P=Y;
for i=1:m
    P1=P;
    k=1;
    for j=i+1:m
        k=k+1;
        P(j)=P1(j-1)+(P1(j)-P1(j-1))*(x0-X(k-1))/(X(j)-X(k-1));
    end
end
y0=P(m);
end
