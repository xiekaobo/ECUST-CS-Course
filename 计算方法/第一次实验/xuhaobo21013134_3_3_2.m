x=-5:0.001:5;
y=1./(1+x.^2);
plot(x,y,'b')
text(-4,0,'原函数')
text(-1.6,0.1,'徐昊博21013134第三题')
hold on

x=linspace(-5,5,3);
y=1./(1+x.^2);
y1=2*x./(x.^4+2*x.^2+1);
x0=linspace(-5,5,1000);
y2=Hermite(x,y,y1,x0);
plot(x0,y2,'r')
ylim([0,1])
text(2.2,0.7,'n=2')
hold on

x=linspace(-5,5,5);
y=1./(1+x.^2);
y1=2*x./(x.^4+2*x.^2+1);
x0=linspace(-5,5,1000);
y2=Hermite(x,y,y1,x0);
plot(x0,y2,'r')
ylim([0,1])
text(4.43,0.3,'n=4')
hold on

x=linspace(-5,5,7);
y=1./(1+x.^2);
y1=2*x./(x.^4+2*x.^2+1);
x0=linspace(-5,5,1000);
y2=Hermite(x,y,y1,x0);
plot(x0,y2,'k')
ylim([0,1])
text(4,0.85,'n=6')
hold on

x=linspace(-5,5,9);
y=1./(1+x.^2);
y1=2*x./(x.^4+2*x.^2+1);
x0=linspace(-5,5,1000);
y2=Hermite(x,y,y1,x0);
plot(x0,y2,'k')
ylim([0,1])
text(3.2,0.74,'n=8')
hold on

x=linspace(-5,5,11);
y=1./(1+x.^2);
y1=2*x./(x.^4+2*x.^2+1);
x0=linspace(-5,5,1000);
y2=Hermite(x,y,y1,x0);
plot(x0,y2,'r')
ylim([0,1])
text(1.41,0.58,'n=10')
hold on
