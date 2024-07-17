f=@f1;
t=0;
x=1;
disp('徐昊博21013134')
disp('利用迭代法在Aitken方法加速求得的根的过程：')
while (abs(x-t)>0.00005)
    t=x;
    x1=f(x);
    x2=f(x1);
    x=x2-(x2-x1)^2/(x2-2*x1+x);
    disp(x)
end