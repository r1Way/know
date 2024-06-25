## Lingo

> [Lingo资料](https://www.mmpt.edu.cn/__local/3/E9/96/CE1A372A1F4346E69E29F023774_444B1B91_B6656.pdf?e=.pdf)

### 注释

```shell
!感叹号靠头，分号结尾;
```

### sets 集合  

* setname [/member_list/] [:attribute_list];其实更像是字典，通过member_list来索引

```shell
sets:
 students/John Jill, Rose Mike/: sex, age;
 endsets
```



### data 参数，多为定值

```shell
data:
a=1 2 3 4;
b=1.2 4.3 212 32;
enddata
```

### variables 决策变量

### 样例

#### 使用sets min

```shell
model:
sets:
	set/1..5/:f,theta;
endsets
!data里如果设置了变量，则为强约束;
data: 
enddata
f(1)>=3;
@for(set(i)|i#ge#2:
	f(i)>=2);
Min=@sum(set(i):f(i));
end
```

#### 使用 #and# 

```shell
model:
sets:
	set/1..5/:f,theta;
endsets

@for(set(i)|i#le#4 #and# i#ge#2 :f(i)>=5);

Min=@sum(set(i):f(i));

end
```

### 多约束

```shell
model:
sets:
	set/1..5/:f,theta;
endsets

@for(set(i):f(i)<=5);

@for(set(i):	f(i)>=2);

Min=@sum(set(i):f(i));

end
```

### @cos(x)

```shell
model:
sets:
	set/1..5/:f,theta;
endsets

@for(set(i):f(i)=@cos(i));

Min=@sum(set(i):f(i));

@for(set(i):@free(f(i)));

end
```

