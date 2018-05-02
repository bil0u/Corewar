.name "sti_1.s"
.comment "sti r3 r7 %58368"

ldi	r1, %58368, r2
ldi	r1, r2, r3
ldi %58368, %58368, r4
ldi %58368, r4, r5
ldi 58368, %58368, r6
ldi 58368, r6, r7
ldi	r5, %58368, r8

sti	r1, r1, %58368
sti	r2, r2, r3
sti r3, %58368, %58368
sti r4, %58368, r4
sti r5, 58368, %58368
sti r6, 58368, r6
