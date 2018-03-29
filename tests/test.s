.name "test"
.comment "champion de test - upopee"

main:	ld		%-1,r1
		ld		%1,r2
		add		r1,r2,r3
live:	live	%1
		zjmp	%:live
