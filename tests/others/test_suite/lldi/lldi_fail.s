.name "lldi fail"
.comment "ld 4294967298 in r2 and lldi %4294967298, r2, r2: RAS)"

ld %4294967298, r2
lldi %4294967298, r2, r2
