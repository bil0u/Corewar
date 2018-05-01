.name		"R1 Test"
.comment	"Test du registre 1 en forkant"

father:	st	r1,60
	ld	%0,r1
	fork	%:child
stop:	zjmp	%:stop
child:	st	r1,60
