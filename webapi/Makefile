all: server mdata

clean:
	@rm -rf *.o
	@rm -rf server
	@rm -rf mdata

server: main.o httpd.o
	gcc -o server $^

main.o: main.c httpd.h
	gcc -c -o main.o main.c

httpd.o: httpd.c httpd.h
	gcc -c -o httpd.o httpd.c

mdata: mdata.c mdata.h
	gcc -o mdata mdata.c `mysql_config --cflags --libs`

