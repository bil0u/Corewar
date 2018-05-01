.name "lld fail"
.comment "lld 4294967295 et check le result: RAS"

lld %4294967297, r2
st r2, 42
aff r2
