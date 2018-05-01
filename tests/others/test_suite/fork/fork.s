.name "LD 42 = * dans r3 puis 58 = : dqns r2"
.comment "let's try ld op"

and %0, %0, r3
fork	%12
fork	%12
fork	%12
ld	%58, r2
