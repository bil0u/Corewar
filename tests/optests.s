.name		"OP Tests"
.comment	"Tu peux pas test"

main:	sti	r1,%:test,%1
		live	%1
		live	%0
		live	%-1
test:	live	%1
