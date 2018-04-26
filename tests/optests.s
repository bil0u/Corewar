.name		"OP Tests"
.comment	"Tu peux pas test"

lld:	lld	6,r15
	lld	:lld,r2
lldi:	lldi	%:lld,%1,r13
	live	%-1
fork:	fork	%:zjmp
lfork:	lfork	%:zjmp
	ld	%0,r16
zjmp:	zjmp	%:zjmp
