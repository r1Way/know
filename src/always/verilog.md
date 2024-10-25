# Verilog

板子 boolean board

芯片型号xc7s50csga324-1

板子 达芬奇xc7a35tfgg484-2

芯片型号

## 流程

1. 综合分析(synthesis)
2. 实施(implemention)
3. 仿真
4. generate bitstream
5. open target

## 数据

二进制n，八进制o，十进制d，十六进制h

```verilog
3'b010//3位二进制
```

## 其它

### 顶层文件名需与项目名称一致

### 修改总线数据类型（二进制/ascii/binary)

* 仿真后右键，radix

### 仿真end time

* settings->simulation->simulation->xsim.simulate.runtime

### 仿真区操作

* 向左/右拖动 放大缩小（每格代表的时间长度，与示波器类似）

![351ec9f78ac59703feb4dfe57c32acf9](G:\know\src\image\351ec9f78ac59703feb4dfe57c32acf9.png)

* 滑动槽可改变观看区域

### wire型变量不能初始化

reg才行

### initial与always执行顺序关系

仿真开始时，所有`initial`块按照它们在代码中出现的顺序执行一次。这意味着在任何`always`块执行之前，所有的`initial`块已经执行完毕。

### 计数器加满后，会置零重新加

### 模块内有reg

可在模块设计时初始化

```verilog
`timescale 1ns / 1ps
module Lab_5_1(
input wire clk,
output reg q=0,
output reg front=0,
output reg behind=0
    );
    ······
endmodule
```

### 仿真时不要将wire赋值

```verilog
module tb(
    );
    
reg clk=0;
wire q;
wire front;
wire behind;

initial begin
clk=0;
end

always #10 clk=~clk;

Lab_5_1 test(
.clk(clk),
.q(q),
.front(front),
.behind(behind)
);

endmodule

```

### 仿真的内容

只要是在testbanch中定义的东西，都会在仿真中出现

### .veo文件查看ip核使用方法

### initial模块一般只在仿真中使用

> https://reborn.blog.csdn.net/article/details/107307958?fromshare=blogdetail&sharetype=blogdetail&sharerId=107307958&sharerefer=PC&sharesource=r1Way&sharefrom=from_link

### 查看内部器件的仿真信号

> https://jianght.blog.csdn.net/article/details/105813222?fromshare=blogdetail&sharetype=blogdetail&sharerId=105813222&sharerefer=PC&sharesource=r1Way&sharefrom=from_link

## 硬件图

### 开关

![ca21a64f3cae703e7092c1633821e720](G:\know\src\image\ca21a64f3cae703e7092c1633821e720.png)

## 语法

### module

```verilog
module boolean_demo(//模块的输入输出
input [15:0] sw,
output [15:0] led
    );
    
assign led=sw;//各接口连接方式
endmodule
```

### always

```verilog
always@(*)begin
end
```

```verilog
always #10 clk = ~clk;// 语句意味着在某些条件下会反复执行块内的代码。在这里，#10 是一种延迟控制，表示在每次执行该语句后等待 10 时间单位（可以是纳秒、皮秒等，取决于模拟的时间单位），然后再执行块内的代码。
```



### initial

```verilog
initial begin
in=3'b000;
#10;
in=3'b001;
#10;
in=3'b010;
end
```

### case

```verilog
case(in)
    3'b000: y=8'b00000001;
    3'b001: y=8'b00000010;
    3'b010: y=8'b00000100;
    3'b011: y=8'b00001000;
    3'b100: y=8'b00010000;
    3'b101: y=8'b00100000;
    3'b110: y=8'b01000000;
    3'b111: y=8'b10000000;
endcase
```

### reg

```verilog
reg a[0:3];   // 声明一个数组，包含4个元素  
initial begin  
    a[0] = 7; // 只给第一个元素赋值为 7，其他元素为 0  
end  
```

```verilog
reg [3:0] a; // 声明一个4位的reg变量  
initial begin  
    a = 7; // 将a赋值为7  
end  
```

### wire

```verilog
wire [7:0] c;// 用于表示一个 8 位宽的单一信号，适合处理一个完整数据字。
```

```verilog
wire c[7:0];//用于表示一个有 8 个元素的数组，每个元素是一个单比特的 wire，适合处理多个分散的信号。
```



### 仿真

```verilog
module testbench();
reg[2:0] in;
wire[7:0] y;
       
Lab_2_1 test(//实例化 类名 对象名
.in(in),
.y(y)
);
    
initial begin
in=3'b000;
```

> 注意输入要用reg，输出要用wire

## 项目

### lab1 按键控制led

* Design sources

```verilog
module boolean_demo(
input [15:0] sw,
output [15:0] led
    );
    
assign led=sw;
endmodule
```

* Simulation sources

```verilog
module TestBench();
    
    reg [15:0] sw;
    wire [15:0] led;
    integer i;
    
    initial begin
    sw=0;
        for(i=0;i<=15;i=i+1) begin
            sw[i]=#100 1;
        end
   end
   
   boolean_demo test(
   .sw(sw),
   .led(led)
   ); 
endmodule
```

* Constrains

``` verilog
set_property -dict {PACKAGE_PIN V2 IOSTANDARD LVCMOS33} [get_ports {sw[0]}]
set_property -dict {PACKAGE_PIN U2 IOSTANDARD LVCMOS33} [get_ports {sw[1]}]
set_property -dict {PACKAGE_PIN U1 IOSTANDARD LVCMOS33} [get_ports {sw[2]}]
set_property -dict {PACKAGE_PIN T2 IOSTANDARD LVCMOS33} [get_ports {sw[3]}]
set_property -dict {PACKAGE_PIN T1 IOSTANDARD LVCMOS33} [get_ports {sw[4]}]
set_property -dict {PACKAGE_PIN R2 IOSTANDARD LVCMOS33} [get_ports {sw[5]}]
set_property -dict {PACKAGE_PIN R1 IOSTANDARD LVCMOS33} [get_ports {sw[6]}]
set_property -dict {PACKAGE_PIN P2 IOSTANDARD LVCMOS33} [get_ports {sw[7]}]
set_property -dict {PACKAGE_PIN P1 IOSTANDARD LVCMOS33} [get_ports {sw[8]}]
set_property -dict {PACKAGE_PIN N2 IOSTANDARD LVCMOS33} [get_ports {sw[9]}]
set_property -dict {PACKAGE_PIN N1 IOSTANDARD LVCMOS33} [get_ports {sw[10]}]
set_property -dict {PACKAGE_PIN M2 IOSTANDARD LVCMOS33} [get_ports {sw[11]}]
set_property -dict {PACKAGE_PIN M1 IOSTANDARD LVCMOS33} [get_ports {sw[12]}]
set_property -dict {PACKAGE_PIN L1 IOSTANDARD LVCMOS33} [get_ports {sw[13]}]
set_property -dict {PACKAGE_PIN K2 IOSTANDARD LVCMOS33} [get_ports {sw[14]}]
set_property -dict {PACKAGE_PIN K1 IOSTANDARD LVCMOS33} [get_ports {sw[15]}]
# On-board LEDs
set_property -dict {PACKAGE_PIN G1 IOSTANDARD LVCMOS33} [get_ports {led[0]}]
set_property -dict {PACKAGE_PIN G2 IOSTANDARD LVCMOS33} [get_ports {led[1]}]
set_property -dict {PACKAGE_PIN F1 IOSTANDARD LVCMOS33} [get_ports {led[2]}]
set_property -dict {PACKAGE_PIN F2 IOSTANDARD LVCMOS33} [get_ports {led[3]}]
set_property -dict {PACKAGE_PIN E1 IOSTANDARD LVCMOS33} [get_ports {led[4]}]
set_property -dict {PACKAGE_PIN E2 IOSTANDARD LVCMOS33} [get_ports {led[5]}]
set_property -dict {PACKAGE_PIN E3 IOSTANDARD LVCMOS33} [get_ports {led[6]}]
set_property -dict {PACKAGE_PIN E5 IOSTANDARD LVCMOS33} [get_ports {led[7]}]
set_property -dict {PACKAGE_PIN E6 IOSTANDARD LVCMOS33} [get_ports {led[8]}]
set_property -dict {PACKAGE_PIN C3 IOSTANDARD LVCMOS33} [get_ports {led[9]}]
set_property -dict {PACKAGE_PIN B2 IOSTANDARD LVCMOS33} [get_ports {led[10]}]
set_property -dict {PACKAGE_PIN A2 IOSTANDARD LVCMOS33} [get_ports {led[11]}]
set_property -dict {PACKAGE_PIN B3 IOSTANDARD LVCMOS33} [get_ports {led[12]}]
set_property -dict {PACKAGE_PIN A3 IOSTANDARD LVCMOS33} [get_ports {led[13]}]
set_property -dict {PACKAGE_PIN B4 IOSTANDARD LVCMOS33} [get_ports {led[14]}]
set_property -dict {PACKAGE_PIN A4 IOSTANDARD LVCMOS33} [get_ports {led[15]}]
```

### lab2 组合逻辑电路

译码器与编码器

* design 

```verilog
`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/10/02 20:17:40
// Design Name: 
// Module Name: project_2_decoder
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module project_2_decoder(
    input wire[2:0] in,
    output reg[7:0] y
    );
    
    always@(*)begin
        case(in)
        3'b000: y=8'b00000001;
        3'b001: y=8'b00000010;
        3'b010: y=8'b00000100;
        3'b011: y=8'b00001000;
        3'b100: y=8'b00010000;
        3'b101: y=8'b00100000;
        3'b110: y=8'b01000000;
        3'b111: y=8'b10000000;
        endcase
    end
endmodule
```

* simulation

```verilog
`timescale 1ns / 1ps
module testbench();
reg[2:0] in;
wire[7:0] y;

project_2_decoder test(
.in(in),
.y(y)
);

initial begin
in=3'b000;
#10;
in=3'b001;
#10;
in=3'b010;
#10;
in=3'b011;
#10;
in=3'b100;
#10;
in=3'b101;
#10;
in=3'b110;
#10;
in=3'b111;
end
endmodule
```

* contrains

```verilog
# On-board Slide Switches
set_property -dict {PACKAGE_PIN V2 IOSTANDARD LVCMOS33} [get_ports {in[0]}]
set_property -dict {PACKAGE_PIN U2 IOSTANDARD LVCMOS33} [get_ports {in[1]}]
set_property -dict {PACKAGE_PIN U1 IOSTANDARD LVCMOS33} [get_ports {in[2]}]
# On-board LEDs
set_property -dict {PACKAGE_PIN G1 IOSTANDARD LVCMOS33} [get_ports {y[0]}]
set_property -dict {PACKAGE_PIN 
G2 IOSTANDARD LVCMOS33} [get_ports {y[1]}]
set_property -dict {PACKAGE_PIN F1 IOSTANDARD LVCMOS33} [get_ports {y[2]}]
set_property -dict {PACKAGE_PIN F2 IOSTANDARD LVCMOS33} [get_ports {y[3]}]
set_property -dict {PACKAGE_PIN E1 IOSTANDARD LVCMOS33} [get_ports {y[4]}]
set_property -dict {PACKAGE_PIN E2 IOSTANDARD LVCMOS33} [get_ports {y[5]}]
set_property -dict {PACKAGE_PIN E3 IOSTANDARD LVCMOS33} [get_ports {y[6]}]
set_property -dict {PACKAGE_PIN E5 IOSTANDARD LVCMOS33} [get_ports {y[7]}]
```

### lab3 rgb  pwm

* design

```
module Lab_3_2(
output r, output g, output b, input en, input clk_100MHz
);
reg [31:0]freq=1000000;//1MHz
reg [6:0]duty_r=50;
reg [6:0]duty_g=50;
reg [6:0]duty_b=50;
reg rst=1;
reg [31:0]cnt=0;
reg [7:0]cnt2=1;
//简单的分频代码，也可以使用分频的 IP 进行分频
always@(posedge clk_100MHz) begin
if(cnt<10000000) begin //变化频率 0.1s
cnt=cnt+1;
end
else begin
cnt=0;
if(cnt2<=150) begin
cnt2=cnt2+1;
end
else begin
cnt2=1;
end
end
if(cnt2>0 && cnt2<=50) begin
duty_r<=cnt2;
duty_g<=0;
duty_b<=0;
end
else if(cnt2>50 && cnt2<=100) begin
duty_g<=cnt2-50;
duty_r<=0;
duty_b<=0;
end
else begin
duty_b<=cnt2-100;
duty_g<=0;
duty_r<=0;
end
end
Driver_PWM_0 pwm_r (
.clk_100MHz(clk_100MHz), // input wire clk_100MHz
.Freq(freq), // input wire [31 : 0] Freq
.Duty(duty_r), // input wire [6 : 0] Duty
.Rst(rst), // input wire Rst
.En(en), // input wire En
.PWM(r) // output wire PWM
);
Driver_PWM_0 pwm_g (
.clk_100MHz(clk_100MHz), // input wire clk_100MHz
.Freq(freq), // input wire [31 : 0] Freq
.Duty(duty_g), // input wire [6 : 0] Duty
.Rst(rst), // input wire Rst
.En(en), // input wire En
.PWM(g) // output wire PWM
);
Driver_PWM_0 pwm_b (
.clk_100MHz(clk_100MHz), // input wire clk_100MHz
.Freq(freq), // input wire [31 : 0] Freq
.Duty(duty_b), // input wire [6 : 0] Duty
.Rst(rst), // input wire Rst
.En(en), // input wire En
.PWM(b) // output wire PWM
);
```

* constrain

```verilog
create_clock -period 10.000 -name gclk [get_ports clk_100MHz]
set_property -dict {PACKAGE_PIN F14 IOSTANDARD LVCMOS33} [get_ports {clk_100MHz}]
set_property -dict {PACKAGE_PIN V2 IOSTANDARD LVCMOS33} [get_ports {en}]; #sw0
set_property -dict {PACKAGE_PIN V6 IOSTANDARD LVCMOS33} [get_ports {r}]; # RBG0_R
set_property -dict {PACKAGE_PIN V4 IOSTANDARD LVCMOS33} [get_ports {g}]; #RBG0_G
set_property -dict {PACKAGE_PIN U6 IOSTANDARD LVCMOS33} [get_ports {b}]; #RBG0_B
```

### lab5 分频器

三分频

* design

```verilog
`timescale 1ns / 1ps

module Lab_5_1(
input wire clk,
output reg q=0,
output reg front=0,
output reg behind=0
    );

reg [1:0]count=0;

   
always@(posedge clk) begin
    if(count!=2) begin
    count=count+1;
    end
    else begin
    count=0;
    end
end

always@(posedge clk) begin
    if(count==0) begin
    front<=1;
    end
    else begin
    front<=0;
    end
end

always@(negedge clk) begin
    if(count==0) begin
    behind<=1;
    end
    else begin
    behind<=0;
    end
end

always@(posedge front)begin
    q=1;
end

always@(negedge behind)begin
    q=0;
end
endmodule
```

* simulation

```verilog
`timescale 1ns / 1ps

module tb(
    );
    
reg clk=0;
wire q;
wire front;
wire behind;

initial begin
clk=0;
end

always #10 clk=~clk;

Lab_5_1 test(
.clk(clk),
.q(q),
.front(front),
.behind(behind)
);

endmodule
```

### 比较两数大小

> [verilog比较两个数大小 - CSDN文库](https://wenku.csdn.net/answer/2fcd241fed3c4deea194904de5ea4570#:~:text=可以使用 Veril)

### 车牌识别

> [jjejdhhd/License-Plate-Recognition-FPGA: 基于FPGA进行车牌识别 (github.com)](https://github.com/jjejdhhd/License-Plate-Recognition-FPGA)

### UART

> [新新新手Icer练习（八）：uart的基本组成及其verilog实现](https://www.bilibili.com/video/BV1he411F7UF?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)
