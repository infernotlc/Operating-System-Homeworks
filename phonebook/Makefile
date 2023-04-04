CC = gcc
CFLAGS = -Wall -Wextra -pedantic -pthread -lrt

all: phonebook phonebook_add phonebook_delete phonebook_printout phonebook_search phonebook_close

phonebook: phonebook.c
	$(CC) $(CFLAGS) -o $@ $<

phonebook_add: phonebook_add.c
	$(CC) $(CFLAGS) -o $@ $<

phonebook_delete: phonebook_delete.c
	$(CC) $(CFLAGS) -o $@ $<

phonebook_printout: phonebook_printout.c
	$(CC) $(CFLAGS) -o $@ $<

phonebook_search: phonebook_search.c
	$(CC) $(CFLAGS) -o $@ $<

phonebook_close: phonebook_close.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f phonebook phonebook_add phonebook_delete phonebook_printout phonebook_search phonebook_close
