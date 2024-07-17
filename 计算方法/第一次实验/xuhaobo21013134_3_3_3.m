x=-5:0.001:5;
y=1./(1+x.^2);
plot(x,y,'b')
text(-1.6,0.1,'徐昊博21013134第三题')
text(0,1.2,'原函数（蓝色）')
hold on

x=linspace(-5,5,1000);
y=1./(1+x.^2);
x0=linspace(-5,5,11);
y0=1./(1+x0.^2);
y1=interp1(x0,y0,x);
plot(x,y1,'r');
text(0.475,0.762,'线性插值（红色）')
hold on

x0=linspace(-5,5,11);
y0=1./(1+x0.^2);
y1=2*x0./(x0.^4+2*x0.^2+1);
x=linspace(-5,5,1000);
y=zeros(1000);
for index=1:1000
    y(index)=Hermite3(x0,y0,y1,x(index));
end
plot(x,y,'k')
text(1.16,0.53,'Hermite三次（黑色）')
ylim([-1,3])
