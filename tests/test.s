.name "test"
.comment "champion de test - upopee"

main:	sti	r1,%:live,%1
	and	r2,r2,r2
live:	live	%1
	zjmp	%:live
