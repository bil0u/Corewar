.name "LD 42 = * dans r3 puis 58 = : dqns r2"
.comment "let's try ld op"

and 0, %1, r3
zjmp	%2
ld	%58, r2
