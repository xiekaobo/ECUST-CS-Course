x=linspace(0,1,1000000);
f=x.*exp(x)-1;
%徐昊博21013134
plot(x,f)
hold on
x=linspace(0,3);
ff=0*x;
text(0.5,0.5,'x*exp(x)-1')
plot(x,ff,'k')