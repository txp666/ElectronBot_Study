这些是舵机对应的f030f4p6对应的固件，烧录即可，不需要重新调试设置id

测试舵机是否正常工作：将main.cpp复制到f4主控的clion工程替换，更改n

n=1-6 对应 id 2~12

**PS**：如果舵机没反应，将f030芯片全部擦除再刷即可（烧录工具有个橡皮擦）

**PS**: 上位机体调试的时候，如果舵机转动方向与上位机中的不一样，调换电机线，同时调换电位器正反（adc以外的两条）即可

![id](https://user-images.githubusercontent.com/52451470/164890677-099a2010-8218-4732-b889-47cd77226090.png)


**注意**stlinkUtility连接舵机板设置如下

![屏幕截图 2022-05-20 202718](https://user-images.githubusercontent.com/52451470/169528242-aaeb6aa1-e515-457f-9746-c66ecbd3c76d.png)
