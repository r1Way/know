## 让原点在右上角，x轴向左，y轴向右

```matlab
set(gca, 'XDir', 'reverse');  % x 轴方向反转
set(gca, 'YDir', 'reverse');  % y 轴方向反转
set(gca, 'XAxisLocation', 'top');  % x 轴在顶部
set(gca, 'YAxisLocation', 'right');  % y 轴在右侧
```

