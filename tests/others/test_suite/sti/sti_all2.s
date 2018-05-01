.name "LD 42 = * dans r3 puis 58 = : dqns r2"
.comment "let's try ld op"


ld      %77, r6
ld      %8732, r7
sti		r6, 7, r7
sti		r6, -7, r7
sti		r6, 7878430, r7
sti		r6, -7878430, r7
sti		r6, %7, r7
sti		r6, %-7, r7
sti		r6, %7754895748, r7
sti		r6, %-7754895748, r7
sti		r6, r7, r7
sti		r6, 7, %7
sti		r6, -7, %-7
sti		r6, 433656367, %754354353
sti		r6, -53665637, %-63665557
sti		r6, %7, %7
sti		r6, %9589438907, %8576837037
sti		r6, %-348606807, %-89738967
sti		r6, %8457, %7453
sti		r6, %-8457, %-7453
sti		r6, -8457, %-7453
sti		r6, 8457, %7453
sti		r6, r7, %5647
sti		r6, r7, %-5647
