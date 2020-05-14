(quote must write code as lines)

(+ 2 5)

(define i 1)
i

(if (< i 19) (print (+ i 1)))
(while (< i 23) (begin (print i) (set i (+ i 1))(if (eq? i 12) break)))
(for (set i 23) (< i 45) (set i (+ i 2)) (begin (print i) (if (eq? i 43) break)))

(define f (open test.ss r))
((. f read))

(define define 12)

define

(class point (list (list n 2)(list m (lambda x (* 2 x)))))
(define x (point))
(. x n)
((. x m) 4)