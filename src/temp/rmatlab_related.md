## matlab相关函数使用

### matlab 多目标最优 paretosearch

```matlab
%main.m
clc
clear
fun=@(x)func_temp(x);
A=[-1 0;
   0 -1];
b=[-1 ;-2];
x=paretosearch(fun,2,A,b);
plot(x(:,1),x(:,2),'m*');
xlabel('x(1)');
ylabel('x(2)');
```

```matlab
%func_temp.m
function f=func_temp(x)
    f(1)=x(1)+x(2);
    f(2)=2*x(2)+x(2);
end
```