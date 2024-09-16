# Python

### for与if语句

```py
# 定义一个数字列表
numbers = [1, 2, 3, 4, 5, 6]

# 使用for循环遍历列表
for number in numbers:
    # 使用if判断条件
    if number % 2 == 0:  # 判断数字是否为偶数
        print(number, "is even.")
    else:
        print(number, "is odd.")
```

### 复制 numpy

```py
copy = original[1:3, 2:4].copy()
```

### 二维数组调用

```py
if data[i,0]%2==0:
```

### 格式化输出

```py
# 假设odd列表已经被填充了奇数元组
odd = [(1, 1.1), (3, 2.2), (5, 3.3)]

# 遍历odd列表中的每一行
for odd_item in odd:
    # 访问元组中的每个元素
    wi, di = odd_item
    print(f"WI: {wi}, DI: {di}")
```

### 记录程序用时

```python
import time

start_time = time.time()  # 获取当前时间的时间戳
# 执行你的代码
time.sleep(2)  # 假设这是你要测量的代码
end_time = time.time()  # 获取当前时间的时间戳

print(f"程序运行时间：{end_time - start_time}秒")
```

### 生成随机数

```py
import random
# 生成第二列：0~207的随机整数
second_column = random.randint(0, 207)
# 生成第三列：0~960的随机浮点数，精度到小数点后一位
third_column = round(random.uniform(0, 960), 1)
```

