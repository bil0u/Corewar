.name "LD 42 = * dans r3 puis ST r3 dans r2 puis ST r2 a mem pc + 2"
.comment "let's try ld op"

ld %-6, r2
sti	r1, %-70, r2
sti r2, %-40, r1
sti r1, %70, r2
sti r2, %40, r1
