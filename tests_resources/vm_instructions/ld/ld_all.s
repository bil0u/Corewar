.name "LD 42 = * dans r3 puis 58 = : dqns r2"
.comment "let's try ld op"

ld		%-63, r2
ld		-63, r2
ld		%63, r2
ld		63, r2
add		r1, r2, r3
sub		r1, r2, r3
and		r1, r2, r3
and		r1, %65, r3
and		r1, 65, r3
and		%1, %65, r3
and		%1, r2, r3
and		1, r2, r3
and		%1, 65, r3
and		1, 65, r3
and		1, %65, r3
or		r1, r2, r3
or		r3, %65, r3
or		r1, 65, r3
or		%1, %65, r3
or		%1, r2, r3
or		1, r2, r3
or		%1, 65, r3
or		1, 65, r3
or		1, %65, r3
xor		r1, r2, r3
xor		r1, %65, r3
xor		r1, 65, r3
xor		%1, %65, r3
xor		%1, r2, r3
xor		1, r2, r3
xor		%1, 65, r3
xor		1, 65, r3
xor		1, %65, r3
zjmp	%0
ldi		r2, r4, r5
ldi		%2, r4, r5
ldi		2, r4, r5
ldi		r2, %4, r5
ldi		%2, %4, r5
ldi		2, %4, r5
sti		r6, 7, r7
sti		r6, %7, r7
sti		r6, r7, r7
sti		r6, 7, %7
sti		r6, %7, %7
sti		r6, r7, %7
fork	%55
lld		%23, r8
lld		63, r8
lldi		r2, r4, r5
lldi		%2, r4, r5
lldi		2, r4, r5
lldi		r2, %4, r5
lldi		%2, %4, r5
lldi		2, %4, r5
lfork %-65744
