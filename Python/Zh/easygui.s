(quote "��ȡһ��GUI�Ű��ļ�������ִ��ͼ�γ���")
(set (f (open "test.gui" "r")))
(set (l (f.readlines)))

(for (set (i 0)) (< i (len l)) (set (i (+ i 1))) ((l|i) "----"))

tkinter
(set (top (tkinter::Tk)))
top
(set (label (tkinter::Label top "��������")))
label
label.pack
(tkinter::mainloop)

()