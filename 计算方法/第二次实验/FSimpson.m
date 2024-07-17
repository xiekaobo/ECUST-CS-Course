function S=FSimpson(f,a,b,N)
%徐昊博21013134
h=(b-a)/N;
fa=feval(f,a);
fb=feval(f,b);
S=fb+fa;
x=a;
for i=1:N
    x=x+h/2;
    fx=feval(f,x);
    S=S+4*fx;
    x=x+h/2;
    fx=feval(f,x);
    S=S+2*fx;
end
S=S-2*fb;
S=h*S/6;
end