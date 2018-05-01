.name "champ.s"
.comment "let's make it"

sti  r1, %8, %0
live    %0
sti r1, %43, %0
ld %1, r2
sti r2, %29, %-4
ldi -16, %0, r3
sti r3, %-23, %33
fork %-47
