x=[0.8,0.9];
y=[0.88811,1.02652];
x0=0.85;
disp('21013134 徐昊博 第一题');
disp('一次Lagrange插值公式：');
disp('y0=');
disp(Lagrange(x,y,x0));

x=[0.55,0.8,0.9];
y=[0.57815,0.88811,1.02652];
disp('二次Lagrange插值公式：');
disp('y0=');
disp(Lagrange(x,y,x0));

x=[0.55,0.8,0.9,1.0];
y=[0.57815,0.88811,1.02652,1.17520];
disp('三次Lagrange插值公式：');
disp('y0=');
disp(Lagrange(x,y,x0));