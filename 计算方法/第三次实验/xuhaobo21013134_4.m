f=@f2;
a=0;
b=1;
N=10;%可以计算出h=0.1
ya=1;%初值y(0)=1
E=Adam4(f,a,b,N,ya);
y=solvef2(a:(b-a)/N:b);
m=[E,y'];
disp('m=     自变量值x       通过四阶Adams法得到的解       准确解')
disp(m)