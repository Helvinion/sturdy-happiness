; Contient grossi�rement l'adresse des trois m�thodes � appeller quand arrivent certains evenements

.import start, nmi, irq

.segment "VECTORS"
   .word nmi	;$fffa vblank nmi
   .word start	;$fffc reset
   .word irq	;$fffe irq / brk
