(; "β�����Ż�")

(set (f (open "test.s" "r")))
(set (s (f.read))) s

(define (testa x) x ) (testa 12)

(class point (
    (set n 12)
    (define fun (lambda x (* 2 x)))
))

(quote "��δʹ��û�о���")
(class envi (
    (set my (dict (')))
    (set father nil)
    (define setfa (lambda x (set (father x))))
))

(env)  (set (env_g (envi))) env_g

(set (d (dict (' (' "+" +) 
    (' "-" -)
    (' "*" *)
    (' "/" /)
    )))
) d

(env_g.my.update d) env_g.my
(set (l (' (d.keys)))) l ()
