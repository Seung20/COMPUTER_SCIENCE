cc=g++ 
cflags = -W -Wall
target = main
objects = main.o array.o rangearray.o 

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)
%.o : %.cpp
	$(cc) $(cflags) -c -o $@ $<

.PHONY : clean
clean:
	rm $(target) $(objects)
