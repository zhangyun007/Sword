#移动鼠标

import pyautogui

for i in range(2):
   pyautogui.moveTo(300, 300, duration=0.25)
   pyautogui.moveTo(400, 300, duration=0.25)
   pyautogui.moveTo(400, 400, duration=0.25)
   pyautogui.moveTo(300, 400, duration=0.25)

#Windows开始菜单按钮的位置   
pyautogui.click(x=29, y=747)
time.sleep(1.0)
pyautogui.click(x=29, y=747)
time.sleep(1.0)
pyautogui.click(clicks=2) 