.macro func label
    .global \label
    .ent \label
    .balign 4
    \label:
.endm

.macro glabel label
    .global \label
    \label:
.endm

.macro endlabel label
    .end \label
.endm
