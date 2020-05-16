(begin (define i 1)

(if (< i 19) (print (+ i 1))
    )
(while (< i 23) (begin (print i) (set i (+ i 1))(if (eq? i 12) break)))
(for (set i 23) (< i 45) (set i (+ i 2)) (begin (print i) (if (eq? i 41) break)))

  (define (sum x r)
      (if (eq? x 0)
          r
          (sum (- x 1) (+ x r))
       )
    )
   (sum 200 0)
)
