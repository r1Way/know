## 42步进电机控制

## 硬件

### A4988+扩展板

> [接口详解](https://www.bilibili.com/video/BV13x411R7Vi?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

fpga

> [FPGA产生可调频率占空比的PWM - IntoTheSky - 博客园 (cnblogs.com)](https://www.cnblogs.com/intothesky/p/15490004.html)

### S42H40D20步进电机（额定功率6.12W，额定电流1.7A,电机驱动电压24V）

> [判断哪两根线是一组](https://www.bilibili.com/video/BV11h4y1V7vK?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

[A4988驱动NEMA步进电机(42步进电机) – 太极创客 (taichi-maker.com)](http://www.taichi-maker.com/homepage/reference-index/motor-reference-index/arduino-a4988-nema-stepper-motor/)

## 接口

### 按钮

按下为0

```verilog
`timescale 1ns / 1ps
module inverse
(
    );
```



## 演示

【用 A4988 控制步进电机】https://www.bilibili.com/video/BV1m84y1a79w?vd_source=ec4e4974e1b56ed330afdb6c6ead1501

## 脉冲波

```verilog
module pwm_test(
    input wire sys_clk,          // FPGA时钟信号
    input wire btn,          // 按钮输入信号
    output reg pulse_out     // 脉冲输出信号
);

// 定义计数器的位宽，足以计数到1000微秒
// 假设FPGA时钟频率为50MHz，计数器需要计数到50000（1000微秒 * 50MHz）
// 因此，至少需要16位宽（2^16 > 50000）
reg [15:0] counter = 0;

// 检测按钮按下（上升沿）
wire btn_press = btn && !btn_last;
reg btn_last = 0;

always @(posedge sys_clk) begin
    btn_last <= btn;
end

// 生成脉冲
always @(posedge sys_clk) begin
    if (btn_press) begin
        // 按钮按下时，启动计数器
        counter <= 0;
        pulse_out <= 1;
    end else if (pulse_out && counter == 50000) begin
        // 计数器达到1000微秒时，停止计数并结束脉冲
        pulse_out <= 0;
    end else if (pulse_out) begin
        // 计数器进行计数
        counter <= counter + 1;
    end else begin
        
        
        // 按钮未按下且脉冲结束时，计数器清零
        counter <= 0;
    end
end

endmodule
```

