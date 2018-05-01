.name "LD 42 = * dans r3 puis 58 = : dqns r2"
.comment "let's try ld op"

lld	%42, r3
lld	58, r2
st r2, 16
st r3, 16
