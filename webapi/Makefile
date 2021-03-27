all: server mdata

clean:
	@rm -rf *.o
	@rm -rf server
	@rm -f mdata

server: main.o httpd.o
	gcc -o server $^

main.o: main.c httpd.h
	gcc -c -o main.o main.c

httpd.o: httpd.c httpd.h
	gcc -c -o httpd.o httpd.c

mdata:
	gcc -o mdata mdata.c `mysql_config --cflags --libs`

