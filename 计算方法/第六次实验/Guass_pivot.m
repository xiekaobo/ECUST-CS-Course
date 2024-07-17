function x=Guass_pivot(A,b)
%用Guass列主元消去法解线性方程组Ax=b
%x是未知向量
%21013134徐昊博
n=length(b);x=zeros(n,1);c=zeros(1,n);
d1=0;
for i=1:n-1
    max=abs(A(i,i));
    m=i;
    for j=i+1:n
        if max<abs(A(j,i))
            max=abs(A(j,i));
            m=j;
        end
    end
    if(m~=i)
        for k=1:n
            c(k)=A(i,k);
            A(i,k)=A(m,k);
            A(m,k)=c(k);
        end
        d1=b(i);
        b(i)=b(m);
        b(m)=d1;
    end
    for k=i+1:n
        for j=i+1:n
            A(k,j)=A(k,j)-A(i,j)*A(k,i)/A(i,i);
        end
        b(k)=b(k)-b(i)*A(k,i)/A(i,i);
        A(k,i)=0;
    end
end
%回代求解
x(n)=b(n)/A(n,n);
for i=n-1:-1:1
    sum=0;
    for j=i+1:n
        sum=sum+A(i,j)*x(j);
    end
    x(i)=(b(i)-sum)/A(i,i);
end
end