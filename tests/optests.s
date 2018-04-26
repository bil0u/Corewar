.name		"OP Tests"
.comment	"Tu peux pas test"

ld:		ld		%0,r15
		ld		%-1,r16
		ld		0,r15
		ld		:ld,r2
lld:	lld		%0,r15
		lld		%-1,r16
		lld		0,r15
		lld		:ld,r2
lldi:	lldi	%:ld,%1,r13
fork:	fork	%:zjmp
lfork:	lfork	%:zjmp
		ld		%0,r16
zjmp:	zjmp	%:zjmp
