.name		"L'enfant restera-t-il en vie ?"
.comment	"wallah je c pa"

start:	sti	r1,%:live,%1
	fork	%:palive	
live:	live	%1	
	ld	%0,r16
	zjmp	%:live
palive:	ld	%0,r16
	zjmp	%:palive
