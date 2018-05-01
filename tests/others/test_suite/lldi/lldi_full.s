.name "LD 42 = * dans r3 puis ST r3 dans r2 puis ST r2 a mem pc + 2"
.comment "let's try ld op"

lldi	r1, %58368, r2
lldi	r1, r2, r3
lldi %58368, %58368, r4
lldi %58368, r4, r5
lldi 1, %58368, r6
lldi 1, r6, r7
st r2, 100
st r3, 100
st r4, 100
st r5, 100
st r6, 100
st r7, 100
