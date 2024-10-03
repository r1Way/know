# Verilog

板子型号xc7s50csga324-1

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

