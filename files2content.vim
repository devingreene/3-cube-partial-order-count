let i=1
while i<=line("$")
	if search("inputlisting","",i)
		s/.*{\(.*\)}.*/\1/
		normal dd
		exe ".-1r ".getreg("")
	endif
	let i = i+1
endwhile
		
		
