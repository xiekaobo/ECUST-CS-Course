function y0=Hermite3(X,Y,DY,x0)
N=length(X);
for i=1:N
    if x0>=X(i)&&x0<=X(i+1)
        k=i;break;
    end
end
a1=x0-X(k+1);
a2=x0-X(k);
a3=X(k)-X(k+1);
y0=(a1/a3)^2*(1-2*a2/a3)*Y(k)+(-a2/a3)^2*(1+2*a1/a3)*Y(k+1)+(a1/a3)^2*a2*DY(k)+(-a2/a3)^2*a1*DY(k+1);
end