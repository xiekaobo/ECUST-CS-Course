f=@f2;
ff=@f22;
x=1;
t=0;
disp('徐昊博21013134')
disp('利用牛顿法求得的根的过程：')
while (abs(x-t)>0.00005)
    t=x;
    x=x-f(x)/ff(x);
    disp(x)
end