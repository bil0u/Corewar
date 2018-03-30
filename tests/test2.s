.name "test2"
.comment "zissizeuteste"

start:	ld	%1,r1

loop:	add	r1,r2,r2
	and	%3,r2,r3
	sub	r2,r2,r4
	sti	r2,%7,%3
	zjmp	%:loop
