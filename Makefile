NONSOURCE := int2table.o IsPoset.o main.o symmetries3.o\
			filter.o fillPermBlock.o dyckCheck.o IsCompat.o \
			mainDyck.o filterDyck.o filterRawCount.o \
			mainRawCount.o

.PHONY : execs
execs : printAllIsoPoz3 printAllIsoPozDyck3 printRawCount

printAllIsoPoz3 : int2table.o IsPoset.o main.o symmetries3.o filter.o
	cc  $^ -o $@ $(COVERAGE)
printAllIsoPozDyck3 : int2table.o IsPoset.o mainDyck.o symmetries3.o filterDyck.o \
						fillPermBlock.o dyckCheck.o IsCompat.o 
	cc $^ -o $@ $(COVERAGE)
printRawCount : int2table.o IsPoset.o mainRawCount.o symmetries3.o filterRawCount.o \
						fillPermBlock.o dyckCheck.o IsCompat.o 
	cc $^ -o $@ $(COVERAGE)

IsCompat.o : IsCompat.c headers.h
	cc $(CFLAGS) -c $< $(COVERAGE)
dyckCheck.o : dyckCheck.c headers.h
	cc $(CFLAGS) -c $< $(COVERAGE)
fillPermBlock.o : fillPermBlock.c headers.h
	cc $(CFLAGS) -c $< $(COVERAGE)
int2table.o : int2table.c headers.h
	cc  $(CFLAGS) -c $< $(COVERAGE)

ifeq ($(POSET1),)
POSET_C = IsPoset.c
else
POSET_C = IsPoset1.c
endif

IsPoset.o : $(POSET_C) headers.h
	cc  $(CFLAGS) -c $< -o $@ $(COVERAGE)
	$(info Compiling $(POSET_C))

main.o : main.c headers.h
	cc  $(CFLAGS) -c $<  $(COVERAGE)
mainDyck.o : main.c headers.h
	cc  -DDYCK $(CFLAGS) -c $< -o $@ $(COVERAGE)
mainRawCount.o : main.c headers.h
	cc -DRAW_POSET_COUNT $(CFLAGS) -c $< -o $@ $(COVERAGE)
symmetries3.o : symmetries3.c headers.h
	cc  $(CFLAGS) -c $< $(COVERAGE)
filter.o : filter.c headers.h
	cc $(CFLAGS) -c $< $(COVERAGE)
filterDyck.o : filter.c headers.h
	cc -DDYCK $(CFLAGS) -c $< -o $@ $(COVERAGE)
filterRawCount.o : filter.c headers.h
	cc -DRAW_POSET_COUNT $(CFLAGS) -c $< -o $@ $(COVERAGE)

clean : 
	rm -f $(NONSOURCE)
