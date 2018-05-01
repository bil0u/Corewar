.name "add r1 et r2 dans r3 et r3 a ladresse 6"
.comment "let's try add op"

ldi	r1, %2, r3
ldi	r12, %2345, r4
ldi	r5, %2, r7
ldi	r0, %2, r12
sti r1, %2, %12
sti r12, %45, %12
sti r5, %123, %12
sti r0, %6546872, %12
