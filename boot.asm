; =================================================================
; BOTTLEOS - CODE DE DÉMARRAGE STANDARD (MULTIBOOT)
; =================================================================

; --- SECTION MULTIBOOT (Pour que QEMU reconnaisse l'OS) ---
section .multiboot
align 4
    dd 0x1BADB002            ; Magic number obligatoire
    dd 0x00                  ; Flags par défaut
    dd - (0x1BADB002 + 0x00)  ; Checksum de vérification

; --- SECTION DE LA PILE MÉMOIRE (Pour le langage C) ---
section .bss
align 16
stack_bottom:
    resb 16384               ; Aloue 16 Ko de RAM pour les variables du C
stack_top:

; --- SECTION DU CODE ---
section .text
global _start
extern kernel_main           ; Indique que la suite est dans kernel.c

_start:
    mov esp, stack_top       ; Initialise le pointeur de pile mémoire
    call kernel_main         ; Saute direct dans le code en C !

.halt:
    cli                      ; Sécurité : si le C s'arrête, on éteint le CPU
    hlt
    jmp .halt
