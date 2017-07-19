.export sp           =    $00   ; Le Stack pointeur du code C
.export sreg         =    $02   ; Un registre quelconque pour le code C
.export regsave      =    $04   ; Encore une zone pour stocker des trucs dans le code C
.export ptr1         =    $08   ; Un registre pour stocker un pointeur
.export ptr2         =    $0A   ; Un registre pour stocker un pointeur
.export ptr3         =    $0C   ; Un registre pour stocker un pointeur
.export ptr4         =    $0E   ; Un registre pour stocker un pointeur
.export tmp1         =    $10   ; Un registre quelconque
.export tmp2         =    $11   ; Un registre quelconque
.export tmp3         =    $12   ; Un registre quelconque
.export tmp4         =    $13   ; Un registre quelconque
.export regbank      =    $14   ; Encore une zone pour stocker des trucs dans le code C

.export TAILLE_ZP_CC65  = $20   ; Ici commence la zéropage utilisable par le codeur (moi !)

.export regbanksize     = TAILLE_ZP_CC65 - regbank ; Taille de l'espace alloué pour la *regbank*
.export zpspace         = TAILLE_ZP_CC65           ; Taille occupée en zeropage par le contexte C
.export zpsavespace     = zpspace - regbanksize    ; Nombre d'octets nécéssaires pour sauvegarder le contexte avant d'appeller du code C depuis une interruption.
