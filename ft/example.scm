(define (string5 x) (<=(string-length x) 5))
(define (string6 x) (<=(string-length x) 6))
(define (string8 x) (<=(string-length x) 8))

; TODO Add support for optional properties
(define-class ctl_PermanentTerminalSpecificData
              no-parent
              (define-property ifdSerialNumber "" 'string string8)
              (define-property commandKeyBypassPinLabel "" 'string string6)
              (define-property commandKeyClearLabel no-default 'string string5)
              (define-property commandKeyEnterLabel no-default 'string string5)
              (define-property commandKeyScrollLabel no-default 'string string5)
              (define-property commandKeyChangeApplicationLabel no-default 'string string5))

(define-class ctl-TransactionTypeCapability no-parent
              (define-property cash #f 'boolean)
              (define-property goods #f 'boolean)
              (define-property services #f 'boolean)
              (define-property cashback #f 'boolean)
              (define-property inquiry #f 'boolean)
              (define-property transfer #f 'boolean)
              (define-property payment #f 'boolean)
              (define-property administrative #f 'boolean)
              (define-property cashDeposit #f 'boolean))

(define-class ctl-TransactionDataInputCapability no-parent
              (define-property numericKeys #f 'boolean)
              (define-property alphabeticAndSpecialCharactersKeys #f 'boolean)
              (define-property commandKeys #f 'boolean)
              (define-property functionKeys #f 'boolean))

(define-class ctl-TransactionDataOutputCapability no-parent
              (define-property printAttendant #f 'boolean)
              (define-property printCardholder #f 'boolean)
              (define-property displayAttendant #f 'boolean)
              (define-property displayCardholder #f 'boolean)
              (define-property codeTable1 #f 'boolean)
              (define-property codeTable2 #f 'boolean)
              (define-property codeTable3 #f 'boolean)
              (define-property codeTable4 #f 'boolean)
              (define-property codeTable5 #f 'boolean)
              (define-property codeTable6 #f 'boolean)
              (define-property codeTable7 #f 'boolean)
              (define-property codeTable8 #f 'boolean)
              (define-property codeTable9 #f 'boolean)
              (define-property codeTable10 #f 'boolean))

(define-class ctl-AdditionalTerminalCapabilities no-parent
              (define-property transactionType (make ctl-TransactionTypeCapability)
                               'ctl-TransactionTypeCapability)
              (define-property terminalDataInput (make ctl-TransactionDataInputCapability)
                               'ctl-TransactionDataInputCapability)
              (define-property terminalDataOutput (make ctl-TransactionDataOutputCapability)
                               'ctl-TransactionDataOutputCapability))

(define-class ctl-EeaProcessSettings no-parent
        (define-property upfrontButtonOnScreenSupported #f 'boolean)
        (define-property offerOverride #f 'boolean)
        (define-property doNotOfferOverrideWhenOnlyOneEntry #f 'boolean))

(define-class ctl-TerminalSpecificData
              no-parent
              (define-property additionalTerminalCapabilities (make ctl-AdditionalTerminalCapabilities)
                               'ctl-AdditionalTerminalCapabilities)
              (define-property eeaProcessSettings (make ctl-EeaProcessSettings)
                               'ctl-EeaProcessSettings))

(define-input-var ctl_e0
                  (make ctl_PermanentTerminalSpecificData
                        (ifdSerialNumber "123456")
                        (commandKeyBypassPinLabel "NO PIN")
                        (commandKeyClearLabel "CLEAR")
                        (commandKeyEnterLabel "ENTER")
                        (commandKeyScrollLabel "SCROL")
                        (commandKeyChangeApplicationLabel "C APP"))
                  'ctl_PermanentTerminalSpecificData)

(define-input-var ctl-e1
                  (make ctl-TerminalSpecificData)
                  'ctl-TerminalSpecificData)

(define-external-function run-program true true no-return-value)

(define (run)
  (set! interactive? #f)
  (run-program))
