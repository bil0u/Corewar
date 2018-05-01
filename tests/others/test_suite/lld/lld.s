.name "LD 42 = * dans r2 puis 58 = : dqns r2"
.comment "let's try ld op"

lld 10, r3
st r3, 2400
lld	-58368, r4
st r4, 2500
lld 1, r5
st r5, 2600
lld	42, r2
st r2, 200
lld	58, r3
st r3, 250
lld	-58, r2
st r2, 300
lld	58567, r2
st r2, 350
lld	-58657, r2
st r2, 400
lld	0, r2
st r2, 450
lld	-512, r2
st r2, 500
lld	512, r2
st r2, 550
