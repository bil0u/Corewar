.name		"Crash LLD"
.comment	"Ca va marcher ?"

start:	ld		:start,r1
		st		r1,30
		lld		:start,r2
		st		r2,30
