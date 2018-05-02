.name "LD 42 = * dans r3 puis ST r3 dans r2 puis ST r2 a mem pc + 2"
.comment "let's try ld op"

ld	%42, r3
aff r3
st	r3, r2
aff r2
st	r2, 2
