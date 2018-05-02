.name "lld 42 = * dans r3 puis ST r3 dans r2 puis ST r2 a mem pc + 2"
.comment "let's try lld op"

lld	%58368, r2
st r2, 200
lld 0, r3
st r3, 400
lld	%-58368, r4
st r4, 500
lld 1, r5
st r5, 600
