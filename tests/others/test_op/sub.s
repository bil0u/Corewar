.name "LD 65 dans r2 LD 23 dans r3 SUB r2 et r3 dans r4 et ST r4 a ladresse 6"
.comment "let's try add op"

ld %65, r2
ld %23, r3
sub	r2, r3, r4
aff r4
st	r4, 6
