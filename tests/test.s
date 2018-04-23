.name "test"
.comment "champion de test - upopee"

main:	ld	%-10,r2
	ld	-10,r3
live:	ld	%0,r16
	zjmp	%:live
