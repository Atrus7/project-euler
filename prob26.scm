;; A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

;; Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

;; Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.

(use-modules (srfi srfi-1)) ;; lists
(use-modules (srfi srfi-64)) ;; tests

(define % remainder)
(define idiv quotient)

(define *infinite-loop-limit* 5000)

(define (prob n)
  (define *cycle* #f)
  (define *rem-stack* '())
  (define *catcher* 0)

  (define (runner n fn)
    (reset)
    (if (zero? n)
        '()
        (cons (fn n) (runner (- n 1) fn))))

  ;; Where stack is a list like '(match . list-of-remainders)
  (define (get-cycle-length stack)
    ;; final element - first occurence of element
    (let ((candidate (car stack))
          (non-repeating-divisions (reverse (cdr stack))))

      (- (length non-repeating-divisions)
         (list-index (lambda (x) (= x candidate))
                     non-repeating-divisions))))

  ;; Returns result. If there's a repeating value, set *cycle* to true
  (define (long-division num dem)
    (define (ld num dem)
      (set! *catcher* (+ 1 *catcher*))
      (if (> *catcher* *infinite-loop-limit*)
          0
          (let* ((div (idiv num dem))
                 (rem (% num dem)))
            (cond
             ((zero? rem) div) ;; finished division
             ((memq rem *rem-stack*) ;; remainder has been seen before
              (begin
                (set! *rem-stack* (cons rem *rem-stack*))
                (set! *cycle* #t)
                div))
             (else
              (begin
                (set! *rem-stack* (cons rem *rem-stack*))
                (+ div (* .1
                          (ld (* rem 10) dem)))))))))


    ;; kick things off
    (ld num dem)
    )

  (define (division-cycle x)

    (long-division 1 x)
    (if (not *cycle*)
        0
        (get-cycle-length *rem-stack*))
    )

  (define (reset)
    ;; utility notice: did we abort early?
    (if (> *catcher* *infinite-loop-limit*)
        (display "ABORT INFINITY\n"))
    (set! *catcher* 0)
    (set! *cycle* #f)
    (set! *rem-stack* '()))

  ;; (test-begin "prob")
  ;; (test-equal (long-division 1 2)	0.5)
  ;; (reset)
  ;; (test-equal (long-division 1 3)	0.3)
  ;; (reset)
  ;; (test-equal (long-division 1 4)	0.25)
  ;; (reset)
  ;; (test-equal (long-division 1 5)	0.2)
  ;; (reset)
  ;; (test-equal (long-division 1 6)	0.16)
  ;; (reset)
  ;; (test-equal (long-division 1 7)	0.142857)
  ;; (reset)
  ;; (test-equal (long-division 1 8)	0.125)
  ;; (reset)
  ;; (test-equal (long-division 1 9)	0.1)
  ;; (reset)
  ;; (test-equal (long-division 1 10) 0.1)
  ;; (reset)
  ;; (test-end "prob")

  ;; TODO Fix this... need reverse because we built up using cons...
  (reverse (runner n division-cycle))
  )

(define (greatest-get-index lst)
  (define (recur lst iter index max-so-far)
    (cond ((null? lst) index)

          ((> (car lst) max-so-far)
           (recur (cdr lst) (+ iter 1) iter (car lst)))

          (else (recur (cdr lst) (+ iter 1) index max-so-far))
          )

    )

  (recur lst 1 0 0))

;; FINAL ANSWER
(greatest-get-index (prob 1000))
