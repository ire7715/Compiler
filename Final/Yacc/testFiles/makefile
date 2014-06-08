filename = helloWorld

$(filename).class: $(filename).jasm
	../../javaa/javaa $(filename).jasm
$(filename).jasm:
	../scanner $(filename).sf

clean: 
	rm -f *.jasm *.class
