(quote "�ó�����������Զ�����ģʽ��ӡ�ļ�")
(set (f (open "luac.out" "rb")))
(set (s (f.read)))
(print s)

(quote
' '.join(format(ord(x), 'x') for x in st)
)

(set (t ";"))

(print (t.join (' "hello" "world")))
()