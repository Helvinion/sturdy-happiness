; Contient grossièrement l'adresse des trois méthodes à appeller quand arrivent certains evenements

.import start, nmi, irq

.segment "VECTORS"
   .word nmi	;$fffa vblank nmi
   .word start	;$fffc reset
   .word irq	;$fffe irq / brk
