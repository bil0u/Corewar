.name "LD 42 = * dans r3 puis ST r3 dans r2 puis ST r2 a mem pc + 2"
.comment "let's try ld op"

ld	%58368, r2
ld 58368, r3
ld	%-58368, r4
ld 1, r5
st r2, 100
st r3, 100
st r4, 100
st r5, 100
