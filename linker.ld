ENTRY(_start)

SECTIONS
{
    /* QEMU charge généralement les OS à cette adresse magique en mémoire RAM */
    . = 1M;

    /* On commence par mettre le code (Assembleur + C) */
    .text :
    {
        *(.multiboot) /* Le badge de sécurité en premier ! */
        *(.text)
    }

    /* Ensuite on met les variables globales */
    .data :
    {
        *(.data)
    }

    /* Et enfin l'espace pour la pile mémoire */
    .bss :
    {
        *(.bss)
    }
}
