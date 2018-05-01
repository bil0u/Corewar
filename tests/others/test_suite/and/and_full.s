.name "add r1 et r2 dans r3 et r3 a ladresse 6"
.comment "let's try add op"

and %58368, %58368, r2
st	r2, 200
and %58368, 58368, r3
st	r3, 200
and %58368, r2, r4
st	r4, 200
and 58368, %58368, r5
st	r5, 200
and 58368, 58368, r6
st	r6, 200
and 58368, r5, r7
st	r7, 200
and r3, %58368, r8
st	r8, 200
and r4, 58368, r9
st	r9, 200
and r6, r5, r10
st	r10, 200
