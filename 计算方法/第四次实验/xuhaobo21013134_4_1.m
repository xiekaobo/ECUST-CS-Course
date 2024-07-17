t=0;
x=1;
disp('徐昊博21013134')
disp('利用迭代法求得的根的过程：')
while (abs(x-t)>0.00005)
    t=x;
    x=(x^3-exp(x)+2)/3;
    disp(x)
end
%(x^3-exp(x)+2)/3 (exp(x)+3*x-2)^(1/3)