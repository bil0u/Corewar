.name "add_overf"
.comment "ld 4294967298 in r2 and ld 43 in r3, then add r2, r2, r3 RAS"

ld %4294967298, r2
ld %43, r3
add r2, r3, r3
st r3, 42
aff r3
