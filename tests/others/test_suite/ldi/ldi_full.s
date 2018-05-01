.name "LD 42 = * dans r3 puis ST r3 dans r2 puis ST r2 a mem pc + 2"
.comment "let's try ld op"

ldi	r1, %58368, r2
ldi	r1, r2, r3
ldi %58368, %58368, r4
ldi %58368, r4, r5
ldi 1, %58368, r6
ldi 1, r6, r7
ldi	r5, %58368, r2

