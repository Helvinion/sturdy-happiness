.segment        "HEADER"
    .byte $4e,$45,$53,$1a   ; "NES"^Z
    .byte 2                 ; 2 pages de 16Kio pour la PRG-ROM
    .byte 1                 ; 1 page de 8Kio pour la CHR-ROM
    .byte %00000001         ; Miroir Horizontal
    .byte %00000000         ; Rien de sp�cial
    .byte 0,0,0,0,0,0,0,0   ; 8 z�ros

; Adresse   |Taille |Contenu
;   |   |
; 0 | 3 | Contient les 3 caract�res ASCII 'NES'
;   |   |
; 3 | 1 | Contient la valeur $1A
;   |   |
; 4 | 1 | Nombre de pages de PRG-ROM de 16 ko dans la rom
;   |   |
; 5 | 1 | Nombre de pages de CHR-ROM de 8 ko dans la rom
;   |   |
; 6 | 1 | Octet de controle de la ROM #1:
;   |   | masque: %mmmmvtsm
;   |   |         |||||||+-- Miroir utilis� en VRAM (0=horizontal,1=vertical)
;   |   |         ||||||+--- utilisation de SRAM ou non pour les sauvegardes (1=oui)
;   |   |         |||||+---- presence d'un trainer de 512 octets
;   |   |         ||||+----- Possibilit� d'utiliser 4 Name Table ind�pendantes en VRAM
;   |   |         +--------- 4 bits de poids faible du mapper utilis�
;   |   |
; 7 | 1 |Octet de controle de la ROM #2:
;   |   |masque: %mmmm0000
;   |   |     ||||+------ ces 4 bits sont toujours � 0
;   |   |     +---------- 4 bits de poids faible du mapper utilis�
;   |   |
;   |   |
;   |   |Remarque: les octets suivants sont ignor�s par la plupart des �mulateurs et doivent rester � 0
;-------------------------------------------------------------------------------------------------------
