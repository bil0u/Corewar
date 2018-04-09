.name    "Joelopezdu63"
.comment "Le sang d'tes morts"

start:	and     r16, r16, r16
	sti	r1, %:fk1, %1	

fk1:	live	%1
	fork	%:child
	live	%-1
	zjmp	%:fk1

child:	live	%-1
	sti	r1, %:lv1, %1
	zjmp	%:lv1

lv1:	live	%1
	zjmp	%:lv1
               
 
	
