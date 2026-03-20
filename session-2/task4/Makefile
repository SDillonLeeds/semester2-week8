
student: student.o main.o
	gcc obj/student.o obj/main.o -o prgm

main.o: src/main.c include/student.h include/structure.h
	gcc -c src/main.c -o obj/main.o

student.o: src/student.c include/student.h include/structure.h
	gcc -c src/student.c -o obj/student.o

clean:
	rm obj/student.o obj/main.o prgm
	