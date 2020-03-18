CC = g++
CFLAGS = -std=c++11 -O3 -march=native

.PHONY = all clean

all: genRandom.x bubble_sort.x insertion_sort.x counting_sort.x selection_sort.x std_sort.x radix_sort.x merge_sort_rec.x quick_sort_iter.x quick_sort_rec.x

%.x: %.cxx
	$(CC) $(CFLAGS) -o $@ $<

clean:
	-rm *.x *.txt
