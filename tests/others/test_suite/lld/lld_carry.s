.name "LD 42 = * dans r3 puis 58 = : dqns r2"
.comment "let's try ld op"

zjmp %3
add r2, r3, r4
zjmp %3
lld	%9999999999, r1
zjmp %3
st r1, 6
