.name    "Test de fork"
.comment "Testt"

	fork	%:child
start:	live	%-1
	fork	%0
	ld	%0,r2
	zjmp	%:start

child:	live	%-1
	fork	%0
	ld	%0,r2
	zjmp	%:child
