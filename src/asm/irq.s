.export irq

.segment "STARTUP"
irq:
    rti ; Return from interrupt
