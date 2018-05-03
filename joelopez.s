.name    "Joelopez aka Stagnette"
.comment "Le sang d'tes morts"

baston:	sti		r1,%:lejoe,%1
		sti		r1,%:l1,%1
		sti		r1,%:l2,%1
		sti		r1,%:l3,%1
		sti		r1,%:l4,%1
		%live	%42
		ld		%0,r16
		fork	%:lejoe
		zjmp	%:baston
lejoe:	live	%42
l1:		live	%42
l2:		live	%42
l3:		live	%42
l4:		live	%42
		zjmp	%:lejoe
