x=-5:0.001:5;
y=1./(1+x.^2);
plot(x,y,'b')
text(-4,0,'原函数')
text(0,2.5,'徐昊博21013134第三题')
hold on

x=linspace(-5,5,3);
y=1./(1+x.^2);
x0=linspace(-5,5,1000);
y0=zeros(1000);
for index=1:1000
    y0(index)=Lagrange(x,y,x0(index));
end
plot(x0,y0,'r')
ylim([-1,3])
text(2,1,'n=2')
hold on

x=linspace(-5,5,5);
y=1./(1+x.^2);
x0=linspace(-5,5,1000);
y0=zeros(1000);
for index=1:1000
    y0(index)=Lagrange(x,y,x0(index));
end
plot(x0,y0,'r')
ylim([-1,3])
text(2,0.6,'n=4')
hold on

x=linspace(-5,5,7);
y=1./(1+x.^2);
x0=linspace(-5,5,1000);
y0=zeros(1000);
for index=1:1000
    y0(index)=Lagrange(x,y,x0(index));
end
plot(x0,y0,'r')
ylim([-1,3])
text(2,-0.1,'n=6')
hold on

x=linspace(-5,5,9);
y=1./(1+x.^2);
x0=linspace(-5,5,1000);
y0=zeros(1000);
for index=1:1000
    y0(index)=Lagrange(x,y,x0(index));
end
plot(x0,y0,'r')
ylim([-1,3])
text(4,-0.7,'n=8')
hold on

x=linspace(-5,5,11);
y=1./(1+x.^2);
x0=linspace(-5,5,1000);
y0=zeros(1000);
for index=1:1000
    y0(index)=Lagrange(x,y,x0(index));
end
plot(x0,y0,'r')
ylim([-1,3])
text(4.5,1.5,'n=10')