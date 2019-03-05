

test: src/test.c src/data_types/bit_array.c src/data_types/bit_array.h src/data_types/linked_list.c src/data_types/linked_list.h src/data_types/string.c src/data_types/string.h src/data_types/tensor.c src/data_types/tensor.h
	gcc -o test src/*.c src/*/*.c
