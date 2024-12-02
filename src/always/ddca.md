## DDCA

### 课程网站

> [start Digital Design and Computer Architecture - Spring 2023](https://safari.ethz.ch/digitaltechnik/spring2023/doku.php?id=start)

### verilog

```verilog
// You can assign partial buses
wire [15:0] longbus;
wire [7:0] shortbus;
assign shortbus = longbus[12:5];
```

```verilog
// Concatenating is by ()
assign y = (a[2],a[1],a[o],a[e]);
```

```verilog
Possible to define multiple copies
assign x = {a[el, a[e], a[o], a[o])
assign y = { 4(a[o]} }
```

### 赋值

```verilog
8'bZ#高阻态
8'b0000_1001 # 00001001
8'bxX0X1zZ1  # XX0X1ZZ1
```

