.name "add r1 et r2 dans r3 et r3 a ladresse 6"
.comment "let's try add op"

xor %58368, %58368, r2

xor %58368, 58368, r3

xor %58368, r2, r4

xor 58368, %58368, r5

xor 58368, 58368, r6

xor 58368, r5, r7

xor r3, %58368, r8

xor r4, 58368, r9

xor r6, r5, r10

st	r2, -10
st	r3, -10
st	r4, -10
st	r5, -10
st	r6, -10
st	r7, -10
st	r8, -10
st	r9, -10
st	r10, -10
