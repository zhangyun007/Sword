import wx

class MsgWindow(wx.Frame):
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title, pos=(640,0))
        
        #重要的就下边两句
        scroller = wx.ScrolledWindow(self, -1)
        scroller.SetScrollbars(1, 1, 1440, 900)
        pnl = wx.Panel(scroller)
        button=wx.Button(pnl,label='Close',pos=(125,10),size=(50,50));  


if __name__ == '__main__':
    app = wx.App(redirect=False)
    msg_win = MsgWindow(None, -1, u'消息')
    msg_win.Show(True)
    app.MainLoop()