(define (string5 x) (<=(string-length x) 5))
(define (string6 x) (<=(string-length x) 6))
(define (string8 x) (<=(string-length x) 8))

(define-class ctl_PermanentTerminalSpecificData
              no-parent
              (define-property ifdSerialNumber no-default 'string string8)
              (define-property commandKeyBypassPinLabel no-default 'string string6)
              (define-property commandKeyClearLabel no-default 'string string5)
              (define-property commandKeyEnterLabel no-default 'string string5)
              (define-property commandKeyScrollLabel no-default 'string string5)
              (define-property commandKeyChangeApplicationLabel no-default 'string string5))

(define-input-var ctl_e0 'no-value 'ctl_PermanentTerminalSpecificData)

(define-external-function run-program true true no-return-value)

(define (run)
  (set! interactive? #f)
  (run-program))
