NONSOURCE := int2table.o IsPoset.o main.o symmetries3.o\
			filter.o fillPermBlock.o dyckCheck.o IsCompat.o \
			mainDyck.o filterDyck.o

.PHONY : execs
execs : printAllIsoPoz3 printAllIsoPozDyck3

printAllIsoPoz3 : int2table.o IsPoset.o main.o symmetries3.o filter.o
	cc  $^ -o $@
printAllIsoPozDyck3 : int2table.o IsPoset.o mainDyck.o symmetries3.o filterDyck.o \
						fillPermBlock.o dyckCheck.o IsCompat.o 
	cc $^ -o $@
IsCompat.o : IsCompat.c headers.h
	cc $(CFLAGS) -c $<
dyckCheck.o : dyckCheck.c headers.h
	cc $(CFLAGS) -c $<
fillPermBlock.o : fillPermBlock.c headers.h
	cc $(CFLAGS) -c $<
int2table.o : int2table.c headers.h
	cc  $(CFLAGS) -c $<

ifeq ($(POSET1),)
POSET_C = IsPoset.c
else
POSET_C = IsPoset1.c
endif

IsPoset.o : $(POSET_C) headers.h
	cc  $(CFLAGS) -c $< -o $@
	$(info Compiling $(POSET_C))

main.o : main.c headers.h
	cc  $(CFLAGS) -c $< 
mainDyck.o : main.c headers.h
	cc  -DDYCK $(CFLAGS) -c $< -o $@
symmetries3.o : symmetries3.c headers.h
	cc  $(CFLAGS) -c $<
filter.o : filter.c headers.h
	cc $(CFLAGS) -c $<
filterDyck.o : filter.c headers.h
	cc -DDYCK $(CFLAGS) -c $< -o $@

clean : 
	rm -f $(NONSOURCE)
