#lang racket

[require racket/gui/base]

(define frame (new frame% [label "Example"]))

(define panel (new horizontal-panel% [parent frame][style (list 'border)][min-width 200][min-height 200]))

(define msg (new message% [parent frame]
                          [label "No events so far..."]))

(for ([i (in-range 30)])
  (new button% [parent panel]
             [label "Left"]
             [callback (lambda (button event)
                         (send msg set-label "Left click"))])
  
  )

(new button% [parent panel]
             [label "Right"]
             [callback (lambda (button event)
                         (send msg set-label "Right click"))])

(send frame show #t)
