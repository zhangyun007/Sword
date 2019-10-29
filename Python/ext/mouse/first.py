#移动鼠标

import pyautogui

for i in range(1):
   pyautogui.moveTo(300, 300, duration=0.25)
   pyautogui.moveTo(400, 300, duration=0.25)
   pyautogui.moveTo(400, 400, duration=0.25)
   pyautogui.moveTo(300, 400, duration=0.25)

#Windows开始菜单按钮的位置   
pyautogui.click(x=29, y=747)

#Windows任务栏第一个任务
pyautogui.click(x=130, y=750)

#点击Firefox地址栏
pyautogui.click(x=360, y=50)

#输入访问地址
pyautogui.typewrite('http://baidu.com', 0.25)  # 0.25表示每输完一个字符串延时0.25秒

#Dota2匹配按钮的坐标
#pyautogui.click(x=860, y=740)


#按两下F1，选中英雄
#pyautogui.press('f1')

#Dota2最后一个技能，快捷键为r键。
#pyautogui.keyDown('R')

#这里使用技能图标的坐标
#pyautogui.click(x=590, y=690)

#pyautogui.click(x=400, y=400)