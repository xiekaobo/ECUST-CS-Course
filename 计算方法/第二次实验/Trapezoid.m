function S=Trapezoid(f,a,b,N)
%徐昊博21013134
h=(b-a)/N;
fa=feval(f,a);
fb=feval(f,b);
S=fb+fa;
x=a;
for i=1:N-1
    x=x+h;
    fx=feval(f,x);
    S=S+2*fx;
end
S=h*S/2;
end