# LCD显示

## 硬件

型号：ATK-MD0430R-800480

> 【京东】https://3.cn/27-459X6「正点原子4.3英寸RGB屏模块800480」
> 点击链接直接打开

## 相关资料

1_【正点原子】达芬奇之FPGA开发指南 V2.2

> [整体介绍（更细节，包含实验展示与字符产生器，获取id）](https://blog.csdn.net/qq_71979946/article/details/139174729?fromshare=blogdetail&sharetype=blogdetail&sharerId=139174729&sharerefer=PC&sharesource=r1Way&sharefrom=from_link)
>
> [集中展示代码](https://blog.csdn.net/m0_37690102/article/details/100535576?fromshare=blogdetail&sharetype=blogdetail&sharerId=100535576&sharerefer=PC&sharesource=r1Way&sharefrom=from_link)
>
> [包含硬件连接图](https://blog.csdn.net/m0_51466525/article/details/122479362?fromshare=blogdetail&sharetype=blogdetail&sharerId=122479362&sharerefer=PC&sharesource=r1Way&sharefrom=from_link)

## RGB-LCD与TFT-LCD

> [【原创】TFTLCD和RGBLCD的区别 - 学习提问与解答专区 - 芯路恒电子技术论坛 - Powered by Discuz!](https://www.corecourse.cn/forum.php?mod=viewthread&tid=27571)

## 彩条实验

### lcd_rgb_colorbar

顶层文件

```verilog
//****************************************Copyright (c)***********************************//
//原子哥在线教学平台：www.yuanzige.com
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com 
//关注微信公众平台微信号："正点原子"，免费获取ZYNQ & FPGA & STM32 & LINUX资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved                               
//----------------------------------------------------------------------------------------
// File name:           lcd_rgb_colorbar
// Last modified Date:  2019/8/07 10:41:06
// Last Version:        V1.0
// Descriptions:        LCD彩条显示顶层模块
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        2019/8/07 10:41:06
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module lcd_rgb_colorbar(
    input                sys_clk,     //系统时钟
    input                sys_rst_n,   //系统复位

    //RGB LCD接口
    output               lcd_de,      //LCD 数据使能信号
    output               lcd_hs,      //LCD 行同步信号
    output               lcd_vs,      //LCD 场同步信号
    output               lcd_bl,      //LCD 背光控制信号
    output               lcd_clk,     //LCD 像素时钟
    output               lcd_rst,     //LCD 复位
    inout        [23:0]  lcd_rgb      //LCD RGB888颜色数据
    );                                                      
    
//wire define    
wire  [15:0]  lcd_id    ;    //LCD屏ID
wire          lcd_pclk  ;    //LCD像素时钟
              
wire  [10:0]  pixel_xpos;    //当前像素点横坐标
wire  [10:0]  pixel_ypos;    //当前像素点纵坐标
wire  [10:0]  h_disp    ;    //LCD屏水平分辨率
wire  [10:0]  v_disp    ;    //LCD屏垂直分辨率
wire  [23:0]  pixel_data;    //像素数据
wire  [23:0]  lcd_rgb_o ;    //输出的像素数据
wire  [23:0]  lcd_rgb_i ;    //输入的像素数据

//*****************************************************
//**                    main code
//*****************************************************

//像素数据方向切换
assign lcd_rgb = lcd_de ?  lcd_rgb_o :  {24{1'bz}};
assign lcd_rgb_i = lcd_rgb;

//读LCD ID模块
rd_id u_rd_id(
    .clk          (sys_clk  ),
    .rst_n        (sys_rst_n),
    .lcd_rgb      (lcd_rgb_i),
    .lcd_id       (lcd_id   )
    );    

//时钟分频模块    
clk_div u_clk_div(
    .clk           (sys_clk  ),
    .rst_n         (sys_rst_n),
    .lcd_id        (lcd_id   ),
    .lcd_pclk      (lcd_pclk )
    );    

//LCD显示模块    
lcd_display u_lcd_display(
    .lcd_pclk       (lcd_pclk  ),
    .rst_n          (sys_rst_n ),
    .pixel_xpos     (pixel_xpos),
    .pixel_ypos     (pixel_ypos),
    .h_disp         (h_disp    ),
    .v_disp         (v_disp    ),
    .pixel_data     (pixel_data)
    );    

//LCD驱动模块
lcd_driver u_lcd_driver(
    .lcd_pclk      (lcd_pclk  ),
    .rst_n         (sys_rst_n ),
    .lcd_id        (lcd_id    ),
    .pixel_data    (pixel_data),
    .pixel_xpos    (pixel_xpos),
    .pixel_ypos    (pixel_ypos),
    .h_disp        (h_disp    ),
    .v_disp        (v_disp    ),
	.data_req	   (		  ),
	
    .lcd_de        (lcd_de    ),
    .lcd_hs        (lcd_hs    ),
    .lcd_vs        (lcd_vs    ),
    .lcd_bl        (lcd_bl    ),
    .lcd_clk       (lcd_clk   ),
    .lcd_rst       (lcd_rst   ),
    .lcd_rgb       (lcd_rgb_o )
    );

endmodule
```



### rd_id 

获取id

```verilog
//****************************************Copyright (c)***********************************//
//原子哥在线教学平台：www.yuanzige.com
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com 
//关注微信公众平台微信号："正点原子"，免费获取ZYNQ & FPGA & STM32 & LINUX资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved                               
//----------------------------------------------------------------------------------------
// File name:           rd_id
// Last modified Date:  2019/8/07 10:41:06
// Last Version:        V1.0
// Descriptions:        读取LCD ID模块
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        2019/8/07 10:41:06
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module rd_id(
    input                   clk    ,    //时钟
    input                   rst_n  ,    //复位，低电平有效
    input           [23:0]  lcd_rgb,    //RGB LCD像素数据,用于读取ID
    output   reg    [15:0]  lcd_id     //LCD屏ID
    );

//reg define
reg            rd_flag;  //读ID标志

//*****************************************************
//**                    main code
//*****************************************************

//获取LCD ID   M2:B7  M1:G7  M0:R7
always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        rd_flag <= 1'b0;
        lcd_id <= 16'd0;
    end    
    else begin
        if(rd_flag == 1'b0) begin
            rd_flag <= 1'b1; 
            case({lcd_rgb[7],lcd_rgb[15],lcd_rgb[23]})
                3'b000 : lcd_id <= 16'h4342;    //4.3' RGB LCD  RES:480x272
                3'b001 : lcd_id <= 16'h7084;    //7'   RGB LCD  RES:800x480
                3'b010 : lcd_id <= 16'h7016;    //7'   RGB LCD  RES:1024x600
                3'b100 : lcd_id <= 16'h4384;    //4.3' RGB LCD  RES:800x480
                3'b101 : lcd_id <= 16'h1018;    //10'  RGB LCD  RES:1280x800
                default : lcd_id <= 16'd0;
            endcase    
        end
    end    
end

endmodule

```



### clk_div

```verilog
//****************************************Copyright (c)***********************************//
//原子哥在线教学平台：www.yuanzige.com
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com 
//关注微信公众平台微信号："正点原子"，免费获取FPGA & STM32 & LINUX资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved                               
//----------------------------------------------------------------------------------------
// File name:           clk_div
// Last modified Date:  2019/8/7 10:41:06
// Last Version:        V1.0
// Descriptions:        时钟分频模块
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        2019/8/7 10:41:06
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module clk_div(
    input               clk,          //50Mhz
    input               rst_n,
    input       [15:0]  lcd_id,
    output  reg         lcd_pclk
    );

//reg define
reg          clk_25m;
reg          clk_12_5m;
reg          div_4_cnt;

//*****************************************************
//**                    main code
//*****************************************************

//时钟2分频 输出25MHz时钟 
always @(posedge clk or negedge rst_n) begin
    if(!rst_n)
        clk_25m <= 1'b0;
    else 
        clk_25m <= ~clk_25m;
end

//时钟4分频 输出12.5MHz时钟 
always @(posedge clk or negedge rst_n) begin
    if(!rst_n) begin
        div_4_cnt <= 1'b0;
        clk_12_5m <= 1'b0;
    end    
    else begin
        div_4_cnt <= div_4_cnt + 1'b1;
        if(div_4_cnt == 1'b1)
            clk_12_5m <= ~clk_12_5m;
		else
			clk_12_5m <= clk_12_5m;
    end        
end

always @(*) begin
    case(lcd_id)
        16'h4342 : lcd_pclk = clk_12_5m;
        16'h7084 : lcd_pclk = clk_25m;       
        16'h7016 : lcd_pclk = clk;
        16'h4384 : lcd_pclk = clk_25m;
        16'h1018 : lcd_pclk = clk;
        default :  lcd_pclk = 1'b0;
    endcase      
end

endmodule

```



### lcd_driver

```verilog
//****************************************Copyright (c)***********************************//
//原子哥在线教学平台：www.yuanzige.com
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com 
//关注微信公众平台微信号："正点原子"，免费获取ZYNQ & FPGA & STM32 & LINUX资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved                               
//----------------------------------------------------------------------------------------
// File name:           lcd_driver
// Last modified Date:  2019/8/07 10:41:06
// Last Version:        V1.0
// Descriptions:        LCD驱动模块
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        2019/8/07 10:41:06
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module lcd_driver(
    input                lcd_pclk,    //时钟
    input                rst_n,       //复位，低电平有效
    input        [15:0]  lcd_id,      //LCD屏ID
    input        [23:0]  pixel_data,  //像素数据
    output  reg  [10:0]  pixel_xpos,  //当前像素点横坐标
    output  reg  [10:0]  pixel_ypos,  //当前像素点纵坐标   
    output  reg  [10:0]  h_disp,      //LCD屏水平分辨率
    output  reg  [10:0]  v_disp,      //LCD屏垂直分辨率 
	output  reg          data_req,    //数据请求信号
    //RGB LCD接口
    output  reg          lcd_de,      //LCD 数据使能信号
    output               lcd_hs,      //LCD 行同步信号
    output               lcd_vs,      //LCD 场同步信号
    output               lcd_bl,      //LCD 背光控制信号
    output               lcd_clk,     //LCD 像素时钟
    output               lcd_rst,     //LCD复位
    output       [23:0]  lcd_rgb      //LCD RGB888颜色数据
    );

//parameter define  
// 4.3' 480*272
parameter  H_SYNC_4342   =  11'd41;     //行同步
parameter  H_BACK_4342   =  11'd2;      //行显示后沿
parameter  H_DISP_4342   =  11'd480;    //行有效数据
parameter  H_FRONT_4342  =  11'd2;      //行显示前沿
parameter  H_TOTAL_4342  =  11'd525;    //行扫描周期
   
parameter  V_SYNC_4342   =  11'd10;     //场同步
parameter  V_BACK_4342   =  11'd2;      //场显示后沿
parameter  V_DISP_4342   =  11'd272;    //场有效数据
parameter  V_FRONT_4342  =  11'd2;      //场显示前沿
parameter  V_TOTAL_4342  =  11'd286;    //场扫描周期
   
// 7' 800*480   
parameter  H_SYNC_7084   =  11'd128;    //行同步
parameter  H_BACK_7084   =  11'd88;     //行显示后沿
parameter  H_DISP_7084   =  11'd800;    //行有效数据
parameter  H_FRONT_7084  =  11'd40;     //行显示前沿
parameter  H_TOTAL_7084  =  11'd1056;   //行扫描周期
   
parameter  V_SYNC_7084   =  11'd2;      //场同步
parameter  V_BACK_7084   =  11'd33;     //场显示后沿
parameter  V_DISP_7084   =  11'd480;    //场有效数据
parameter  V_FRONT_7084  =  11'd10;     //场显示前沿
parameter  V_TOTAL_7084  =  11'd525;    //场扫描周期       
   
// 7' 1024*600   
parameter  H_SYNC_7016   =  11'd20;     //行同步
parameter  H_BACK_7016   =  11'd140;    //行显示后沿
parameter  H_DISP_7016   =  11'd1024;   //行有效数据
parameter  H_FRONT_7016  =  11'd160;    //行显示前沿
parameter  H_TOTAL_7016  =  11'd1344;   //行扫描周期
   
parameter  V_SYNC_7016   =  11'd3;      //场同步
parameter  V_BACK_7016   =  11'd20;     //场显示后沿
parameter  V_DISP_7016   =  11'd600;    //场有效数据
parameter  V_FRONT_7016  =  11'd12;     //场显示前沿
parameter  V_TOTAL_7016  =  11'd635;    //场扫描周期
   
// 10.1' 1280*800   
parameter  H_SYNC_1018   =  11'd10;     //行同步
parameter  H_BACK_1018   =  11'd80;     //行显示后沿
parameter  H_DISP_1018   =  11'd1280;   //行有效数据
parameter  H_FRONT_1018  =  11'd70;     //行显示前沿
parameter  H_TOTAL_1018  =  11'd1440;   //行扫描周期
   
parameter  V_SYNC_1018   =  11'd3;      //场同步
parameter  V_BACK_1018   =  11'd10;     //场显示后沿
parameter  V_DISP_1018   =  11'd800;    //场有效数据
parameter  V_FRONT_1018  =  11'd10;     //场显示前沿
parameter  V_TOTAL_1018  =  11'd823;    //场扫描周期

// 4.3' 800*480   
parameter  H_SYNC_4384   =  11'd128;    //行同步
parameter  H_BACK_4384   =  11'd88;     //行显示后沿
parameter  H_DISP_4384   =  11'd800;    //行有效数据
parameter  H_FRONT_4384  =  11'd40;     //行显示前沿
parameter  H_TOTAL_4384  =  11'd1056;   //行扫描周期
   
parameter  V_SYNC_4384   =  11'd2;      //场同步
parameter  V_BACK_4384   =  11'd33;     //场显示后沿
parameter  V_DISP_4384   =  11'd480;    //场有效数据
parameter  V_FRONT_4384  =  11'd10;     //场显示前沿
parameter  V_TOTAL_4384  =  11'd525;    //场扫描周期    

//reg define
reg  [10:0] h_sync ;
reg  [10:0] h_back ;
reg  [10:0] h_total;
reg  [10:0] v_sync ;
reg  [10:0] v_back ;
reg  [10:0] v_total;
reg  [10:0] h_cnt  ;
reg  [10:0] v_cnt  ;

//*****************************************************
//**                    main code
//*****************************************************

//RGB LCD 采用DE模式时，行场同步信号需要拉高
assign  lcd_hs = 1'b1;        //LCD行同步信号
assign  lcd_vs = 1'b1;        //LCD场同步信号

assign  lcd_bl = 1'b1;        //LCD背光控制信号  
assign  lcd_clk = lcd_pclk;   //LCD像素时钟
assign  lcd_rst= 1'b1;        //LCD复位

//RGB888数据输出
assign lcd_rgb = lcd_de ? pixel_data : 24'd0;

//像素点x坐标
always@ (posedge lcd_pclk or negedge rst_n) begin
    if(!rst_n)
        pixel_xpos <= 11'd0;
    else if(data_req)
        pixel_xpos <= h_cnt + 2'd2 - h_sync - h_back ;
    else 
        pixel_xpos <= 11'd0;
end
   
//像素点y坐标   
always@ (posedge lcd_pclk or negedge rst_n) begin
    if(!rst_n)
        pixel_ypos <= 11'd0;
    else if(v_cnt >= (v_sync + v_back)&&v_cnt < (v_sync + v_back + v_disp))
        pixel_ypos <= v_cnt + 1'b1 - (v_sync + v_back) ;
    else 
        pixel_ypos <= 11'd0;
end

//行场时序参数
always @(*) begin
    case(lcd_id)
        16'h4342 : begin
            h_sync  = H_SYNC_4342; 
            h_back  = H_BACK_4342; 
            h_disp  = H_DISP_4342; 
            h_total = H_TOTAL_4342;
            v_sync  = V_SYNC_4342; 
            v_back  = V_BACK_4342; 
            v_disp  = V_DISP_4342; 
            v_total = V_TOTAL_4342;            
        end
        16'h7084 : begin
            h_sync  = H_SYNC_7084; 
            h_back  = H_BACK_7084; 
            h_disp  = H_DISP_7084; 
            h_total = H_TOTAL_7084;
            v_sync  = V_SYNC_7084; 
            v_back  = V_BACK_7084; 
            v_disp  = V_DISP_7084; 
            v_total = V_TOTAL_7084;        
        end
        16'h7016 : begin
            h_sync  = H_SYNC_7016; 
            h_back  = H_BACK_7016; 
            h_disp  = H_DISP_7016; 
            h_total = H_TOTAL_7016;
            v_sync  = V_SYNC_7016; 
            v_back  = V_BACK_7016; 
            v_disp  = V_DISP_7016; 
            v_total = V_TOTAL_7016;            
        end
        16'h4384 : begin
            h_sync  = H_SYNC_4384; 
            h_back  = H_BACK_4384; 
            h_disp  = H_DISP_4384; 
            h_total = H_TOTAL_4384;
            v_sync  = V_SYNC_4384; 
            v_back  = V_BACK_4384; 
            v_disp  = V_DISP_4384; 
            v_total = V_TOTAL_4384;             
        end        
        16'h1018 : begin
            h_sync  = H_SYNC_1018; 
            h_back  = H_BACK_1018; 
            h_disp  = H_DISP_1018; 
            h_total = H_TOTAL_1018;
            v_sync  = V_SYNC_1018; 
            v_back  = V_BACK_1018; 
            v_disp  = V_DISP_1018; 
            v_total = V_TOTAL_1018;        
        end
        default : begin
            h_sync  = H_SYNC_4342; 
            h_back  = H_BACK_4342; 
            h_disp  = H_DISP_4342; 
            h_total = H_TOTAL_4342;
            v_sync  = V_SYNC_4342; 
            v_back  = V_BACK_4342; 
            v_disp  = V_DISP_4342; 
            v_total = V_TOTAL_4342;          
        end
    endcase
end
	
//数据使能信号		
always@ (posedge lcd_pclk or negedge rst_n) begin
    if(!rst_n)	
		lcd_de <= 1'b0;
	else
		lcd_de <= data_req;
end
				  
//请求像素点颜色数据输入  
always@ (posedge lcd_pclk or negedge rst_n) begin
    if(!rst_n)	
		data_req<=1'b0;
	else if((h_cnt >= h_sync + h_back - 2'd2) && (h_cnt < h_sync + h_back + h_disp - 2'd2)
             && (v_cnt >= v_sync + v_back) && (v_cnt < v_sync + v_back + v_disp))
		data_req <= 1'b1;
	else
		data_req <= 1'b0;
end
				  
//行计数器对像素时钟计数
always@ (posedge lcd_pclk or negedge rst_n) begin
    if(!rst_n) 
        h_cnt <= 11'd0;
    else begin
        if(h_cnt == h_total - 1'b1)
            h_cnt <= 11'd0;
        else
            h_cnt <= h_cnt + 1'b1;           
    end
end

//场计数器对行计数
always@ (posedge lcd_pclk or negedge rst_n) begin
    if(!rst_n) 
        v_cnt <= 11'd0;
    else begin
        if(h_cnt == h_total - 1'b1) begin
            if(v_cnt == v_total - 1'b1)
                v_cnt <= 11'd0;
            else
                v_cnt <= v_cnt + 1'b1;    
        end
    end    
end

endmodule
```

### driver_display

用来提供(pixel_xpos,pixel_ypos)处的颜色data

```verilog
//****************************************Copyright (c)***********************************//
//原子哥在线教学平台：www.yuanzige.com
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com 
//关注微信公众平台微信号："正点原子"，免费获取ZYNQ & FPGA & STM32 & LINUX资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved                               
//----------------------------------------------------------------------------------------
// File name:           lcd_display
// Last modified Date:  2019/8/07 10:41:06
// Last Version:        V1.0
// Descriptions:        LCD显示模块
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        2019/8/07 10:41:06
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module lcd_display(
    input                lcd_pclk,    //时钟
    input                rst_n,       //复位，低电平有效
    input        [10:0]  pixel_xpos,  //当前像素点横坐标
    input        [10:0]  pixel_ypos,  //当前像素点纵坐标  
    input        [10:0]  h_disp,      //LCD屏水平分辨率
    input        [10:0]  v_disp,      //LCD屏垂直分辨率       
    output  reg  [23:0]  pixel_data   //像素数据
    );

//parameter define  
parameter WHITE = 24'hFFFFFF;  //白色
parameter BLACK = 24'h000000;  //黑色
parameter RED   = 24'hFF0000;  //红色
parameter GREEN = 24'h00FF00;  //绿色
parameter BLUE  = 24'h0000FF;  //蓝色

//*****************************************************
//**                    main code
//*****************************************************

//根据当前像素点坐标指定当前像素点颜色数据，在屏幕上显示彩条
always @(posedge lcd_pclk or negedge rst_n) begin
    if(!rst_n)
        pixel_data <= BLACK;
    else begin
        if((pixel_xpos >= 11'd0) && (pixel_xpos < h_disp/5*1))
            pixel_data <= WHITE;
        else if((pixel_xpos >= h_disp/5*1) && (pixel_xpos < h_disp/5*2))    
            pixel_data <= BLACK;
        else if((pixel_xpos >= h_disp/5*2) && (pixel_xpos < h_disp/5*3))    
            pixel_data <= RED;   
        else if((pixel_xpos >= h_disp/5*3) && (pixel_xpos < h_disp/5*4))    
            pixel_data <= GREEN;                
        else
            pixel_data <= BLUE; 
    end    
end
  
endmodule
```

## 字符实验



## 相关概念

### 行场同步模式（HV Mode）

*  LCD的行显示对应时序

HSYNC：行同步信号，当此信号有效的时候就表示开始显示新的一行数据，查阅所使用的 LCD 数据手册可以知道此信号是低电平有效还是高电平有效，在这里是 低电平有效
HSPW：行同步信号宽度，也就是 HSYNC 信号持续时间。HSYNC 信号不是一个脉冲，而是需要持续一段时间才是有效的，单位为 CLK。
HBP：行显示后沿（或后肩），单位是 CLK。
HOZVAL：行有效显示区域，即显示一行数据所需的时间，假如屏幕分辨率为 1024*600，那么HOZVAL 就是 1024，单位为 CLK。
HFP：行显示前沿（或前肩），单位是 CLK。当 HSYNC 信号发出以后，需要等待 HSPW+HBP 个 CLK 时间才会接收到真正有效的像素数据。当显示完一行数据以后需要等待 HFP 个 CLK 时间才能发出下一个 HSYNC 信号，所以显示一行所需要的时间就是：HSPW + HBP + HOZVAL + HFP。

* RGB LCD的 帧显示时序图

SYNC：帧（场）同步信号，当此信号有效的时候就表示开始显示新的一帧数据，查阅所使用的
LCD 数据手册可以知道此信号是低电平有效还是高电平有效，图 18.1.8 为低电平有效。
VSPW：帧同步信号宽度，也就是 VSYNC 信号持续时间，单位为 1 行的时间。
VBP：帧显示后沿（或后肩），单位为 1 行的时间。
LINE：帧有效显示区域，即显示一帧数据所需的时间，假如屏幕分辨率为 1024*600，那么 LINE 就是
600 行的时间。
VFP：帧显示前沿（或前肩），单位为 1 行的时间。
显示一帧所需要的时间就是：VSPW+VBP+LINE+VFP 个行时间，最终的计算公式：
T = (VSPW+VBP+LINE+VFP) * (HSPW + HBP + HOZVAL + HFP)

```verilog
// 4.3' 800*480   
parameter  H_SYNC_4384   =  11'd128;    //行同步
parameter  H_BACK_4384   =  11'd88;     //行显示后沿
parameter  H_DISP_4384   =  11'd800;    //行有效数据
parameter  H_FRONT_4384  =  11'd40;     //行显示前沿
parameter  H_TOTAL_4384  =  11'd1056;   //行扫描周期
   
parameter  V_SYNC_4384   =  11'd2;      //场同步
parameter  V_BACK_4384   =  11'd33;     //场显示后沿
parameter  V_DISP_4384   =  11'd480;    //场有效数据
parameter  V_FRONT_4384  =  11'd10;     //场显示前沿
parameter  V_TOTAL_4384  =  11'd525;    //场扫描周期    
```

> https://blog.csdn.net/qlexcel/article/details/86301007?fromshare=blogdetail&sharetype=blogdetail&sharerId=86301007&sharerefer=PC&sharesource=r1Way&sharefrom=from_link
>
> https://blog.csdn.net/weixin_50965981/article/details/134496428?fromshare=blogdetail&sharetype=blogdetail&sharerId=134496428&sharerefer=PC&sharesource=r1Way&sharefrom=from_link

### 数据使能同步模式（DE Mode）
