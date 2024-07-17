function [x,k]=SOR(A,b,x0,N,emg,w)
%21013134徐昊博
%A是线性方程组的左端矩阵,b是右端向量
%x0是初始迭代值,N表示迭代次数上限，若迭代次数大于N，则迭代失败
%emg表示控制精度,w代表松弛因子
%用Jacobi迭代法求线性方程组Ax=b的解
%k表示迭代次数,x表示用迭代法求得的线性方程组的近似解
n=length(A);
x1=zeros(n,1);x2=zeros(n,1);
x1=x0;k=0;
r=max(abs(b-A*x1));
while r>emg
    for i=1:n
        sum=0;
        for j=1:n
            if j>=i
                sum=sum+A(i,j)*x1(j);
            elseif j<i
                sum=sum+A(i,j)*x2(j);
            end
        end
        x2(i)=x1(i)+w*(b(i)-sum)/A(i,i);
    end
    r=max(abs(x2-x1));
    x1=x2;
    k=k+1;
    if k>N
        disp("迭代失败，返回");
        return;
    end
end
x=x1;
end
