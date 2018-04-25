.name		"Crash des registres"
.comment	"Ca va marcher ?"

load:	ld	%1415602272,r2
	sti	r2,%:crash,%1
crash:	add	r1,r2,r3
	ld	%0,r16
	zjmp	%:crash
