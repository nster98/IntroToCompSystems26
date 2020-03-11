all:
	$(error You must specify "generate" or a question number: "q1" or "q2" or "q3")

q1:
	gcc search_1.c -std=c99 -o search_1
	./search_1

q2:
	gcc search_2.c -std=c99 -o search_2
	./search_2

q3:
	gcc search_3.c -std=c99 -o search_3
	./search_3

generate:
	gcc generate.c -std=c99 -o generate

clean:
	rm -f search_1 search_2 search_3 generate
