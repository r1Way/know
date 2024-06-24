## matlab绘制datetime与因变量关系图

```matlab
clc
clear
close all
fileName1_1="attach1_1.CSV";
data=readtable(fileName1_1)
% Assuming "data" is your array with missing values
data = rmmissing(data);%清理数据，删除数据丢失的行

time=datetime(table2array(data(:,1)),'InputFormat', 'yyyy-MM-dd HH:mm:ss');
T1=table2array(data(:,2));%table转数值数组
T2=table2array(data(:,3));

figure;
plot(time,T1);%打印
hold on;
plot(time,T2);%打印
hold on;
hold off;
```

