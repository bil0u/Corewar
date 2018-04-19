.name    "Joelopez aka Stagnette"
.comment "Le sang d'tes morts"

bagar:	sti		r1,%:lecouz,%1
		sti		r1,%:jessy,%1
		sti		r1,%:bambin,%1
		sti		r1,%:gamin,%1
		sti		r1,%:sony,%1
		ld		%16,r2
		ld		%3,r3
		ld		%4,r6
		ld		%589824,r12
		ld		%110,r13
		ld		%63,r14
		ld		%2047,r15

lejoe:	fork	%:lecouz
		st		r1,6
		live	%1
		add		r2,r3,r4
		fork	%:sony
		st		r1,6
		live	%1
		fork	%:jessy
		st		r1,6
		live	%1
		ld		%0,r16
		zjmp	%:lejoe

lecouz:	live	%1
		sti		r1,%:lecouz,%1
		sti		r1,%:sony,%1
		sti		r1,%:jessy,%1
		ld		%0,r16
		zjmp	%:lecouz

jessy:	live	%1
		sti		r1,%:lecouz,%1
		sti		r1,%:sony,%1
		sti		r1,%:jessy,%1
		ld		%0,r16
		zjmp	%:jessy

sony:   live	%1
		sti		r1,%:vago,r4
		sub		r4,r3,r5
		and		r5,r14,r5
		zjmp	%:bambin
		add		r2,r4,r4
		ld		%0,r16
		zjmp	%:sony
		# Size : 37

bambin:	live	%1
		ldi		%:sony,r5,r10
		sti		r10,r4,r5
		xor		r5,r14,r5
		zjmp	%:gamin
		add		r5,r6,r5
		ld		%0,r16
		zjmp	%:bambin
		# Size : 39

gamin:	live	%1
		st		r4,20
		ld		%0,r4
		ld		%0,r5
		zjmp	%1
		# Size : 27

vago:	zjmp	%:sony
		# Size : 3
