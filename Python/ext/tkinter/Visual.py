from tkinter import *
 
m1 = PanedWindow(showhandle=True, sashrelief=SUNKEN)  #默认是左右分布的
m1.pack(fill=BOTH, expand=1)
 

left = Label(m1, text='left pane')
m1.add(left)


# 创建一个纵向滚动的滚动条,打包到窗口右侧，铺满Y方向
scrollbar = Scrollbar(m1,orient=VERTICAL)#orient默认为纵向
scrollbar.pack(fill=Y, side=RIGHT)

# 打包一个文本域到窗口，y方向滚动文本的监听丢给滚动条的set函数（文本域主动关联滚动条）
text = Text(m1,width=100, yscrollcommand=scrollbar.set)
text.pack()

scrollbar.config(command=text.yview)

 
m2 = PanedWindow(orient=VERTICAL, showhandle=True, sashrelief=SUNKEN)
m1.add(m2)
 
top = Label(m2, text='top pane')
m2.add(top)
 
bottom = Label(m2, text='bottom pane')
m2.add(bottom)
 
mainloop()
