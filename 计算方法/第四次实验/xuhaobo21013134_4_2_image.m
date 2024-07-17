x=linspace(0,3,1000000);
f=x.^3+10*x-20;
%徐昊博21013134
plot(x,f)
hold on
x=linspace(0,3);
ff=0*x;
text(1.6,10,'y=x.^3+10*x-20;')
plot(x,ff,'k')