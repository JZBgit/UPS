# 单相在线式不间断电源

### ——2020年TI杯大学生电子设计竞赛（B题）

#### 1. 任务

设计并制作交流正弦波在线式不间断电源（UPS)，结构框图如图1所示。

<img src="C:\Users\JZB\AppData\Roaming\Typora\typora-user-images\image-20241005093444850.png" alt="image-20241005093444850" style="zoom:70%;" />

图1 在线式不间断电源原理框图

#### 2. 要求
$$
E = mc^2
$$
$
E = mc^2
$

（1） 交流供电，\(U_1\)=36V，输出交流电流$ I_o $=1A时，输出交流电压$U_o$=30V±0.2V，频率f=50±0.2Hz。(10分)（2）交流供电，$U_1$=36V，$I_o$在0.1A～1.0A范围变化，负载调整率$S_I$≤0.5%。(20分)
（3）交流供电，$I_o$=1A，$U_1$在29V~43V范围内变化，电压调整率$S_u$≤0.5%。(20分)
（4）在要求(1)条件下，不间断电源输出电压为正弦波，失真度$THD$≤2%。( 15分)
（5）断开交流电源，即时切换至直流（储能器件侧）供电，$U_d$=24V，输出交流电流$I_o$=1A时，输出交流电压$U_o$=30V±0.2V，频率$f $=50±0.2Hz。( 10分)
（6）直流供电，$U_d$=24V，在$U_o$=30V，$I_o$=1A的条件下，使在线式不间断电源效率$η$尽可能高。(20分)
（7）其他(5 分)
（8）设计报告(20分)

<img src="C:\Users\JZB\AppData\Roaming\Typora\typora-user-images\image-20241005100439531.png" alt="image-20241005100439531" style="zoom:60%;" />

#### 3. 说明

（1）作品不得使用相关产品改制。
（2）图1中的变压器由自耦变压器和隔离变压器构成。
（3）题中所有交流参数均为有效值。
（4）本题定义:负载调整率$S_I=|U_{o(1A)}-U_{o(1A)}|/30$、电压调整率$S_U=|U_{o(43V)}-U_{o(29V)}|/30$、效率$η=(U_oI_o)/(U_dI_d)$；其中$U_{o(0.1A)}$、$U_{o(1A)}$分别为负载调整率测试时，输出电流$I_o$为0.1A、1A时所对应的输出电压$U_o$；其中$U_{o(43V)}$、$U_{o(29V)}$分别为电压调整率测试时，输入电压$U_1$为43V、29V时所对应的输出电压$U_o$
（5）图1中的储能器件（蓄电池等）用直流稳压电源代替。
（6）制作时须考虑测试方便，合理设置测试点，如图1所示。
（7）为保证运行、测试安全，作品应具备必要的过压、过流保护功能。



# 本人作品

我们使用的方案是将交流电转化成直流电，储能设备的直流电加在这个直流电上，然后升压，再通过逆变电路转换成交流电。

## 1 AC-DC电路

AC电源输入$U_1$经过整流滤波后电压大小为$1.414*U_{o(29-43V)}=U_{o(40-60V)}'$，直流电$U_d$通过二极管接到$U_o'$上，当交流电$U_1$断开时，二极管导通，直流电$U_d$接在电源上。

![image-20241005142654629](C:\Users\JZB\AppData\Roaming\Typora\typora-user-images\image-20241005142654629.png)

## 2 Boost电路

因为电源输出交流电$U_o$=30V，我们采用全桥逆变电路，所以电压峰值应当为42V。但是我们考虑到极值的影响，避免PWM的值出现0%和100%的情况，将最大值和最小值预留了20%，即PWM的取值范围20~80%。所以我们将电压升至75V。在做的过程中我们发现一个Boost电路的指标差些，所以有了两级Boost电路。

我们首先将输入的电压升值40V，然后在40V的基础上升至75V。

![image-20241005142806030](C:\Users\JZB\AppData\Roaming\Typora\typora-user-images\image-20241005142806030.png)

## 3 全桥&Buck电路

我们使用UCC27712芯片控制H桥，该芯片具有互锁和死区时间功能可防止两个输出同时打开，防止烧坏电路。同时利用SP3485产生互补SPWM波，从硬件上锁定互补的SPWM，避免出现死区。Buck电路为升压芯片，和以上两个芯片供电。

![image-20241005142906305](C:\Users\JZB\AppData\Roaming\Typora\typora-user-images\image-20241005142906305.png)

## 4 滤波电路

全桥输出的SPWM波经过滤波后变成交流电。

![image-20241005143005733](C:\Users\JZB\AppData\Roaming\Typora\typora-user-images\image-20241005143005733.png)

## 5 采样电路

输出的电路采样反馈给单片机，单片机进行控制和显示。

![image-20241005143105440](C:\Users\JZB\AppData\Roaming\Typora\typora-user-images\image-20241005143105440.png)
