#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define MAX_NAME_LENGTH 100
#define MAX_SURNAME_LENGTH 100
#define MAX_TEL_NUMBER_LENGTH 30

struct PhonebookEntry {
    char name[MAX_NAME_LENGTH];
    char surname[MAX_SURNAME_LENGTH];
    char tel_number[MAX_TEL_NUMBER_LENGTH];
};

struct PhonebookEntry phonebook[1000];
int phonebook_size = 0;

void add_entry(char* name, char* surname, char* tel_number) {
    for (int i = 0; i < phonebook_size; i++) {
        if (strcmp(phonebook[i].tel_number, tel_number) == 0) {
            printf("add unsuccessful\n");
            return;
        }
    }
    struct PhonebookEntry new_entry;
    strcpy(new_entry.name, name);
    strcpy(new_entry.surname, surname);
    strcpy(new_entry.tel_number, tel_number);
    phonebook[phonebook_size++] = new_entry;
    printf("add successful\n");
}

void delete_entry(char* tel_number) {
    for (int i = 0; i < phonebook_size; i++) {
        if (strcmp(phonebook[i].tel_number, tel_number) == 0) {
            for (int j = i; j < phonebook_size-1; j++) {
                phonebook[j] = phonebook[j+1];
            }
            phonebook_size--;
            printf("delete successful\n");
            return;
        }
    }
    printf("delete unsuccessful\n");
}

void print_entry(char* tel_number) {
    for (int i = 0; i < phonebook_size; i++) {
        if (strcmp(phonebook[i].tel_number, tel_number) == 0) {
            printf("%s %s : %s\n", phonebook[i].name, phonebook[i].surname, phonebook[i].tel_number);
            return;
        }
    }
    printf("telephone number does not exist\n");
}

int search_entries(char* search_query, char** result) {
    int result_size = 0;
    for (int i = 0; i < phonebook_size; i++) {
        if (strstr(phonebook[i].name, search_query) != NULL || strstr(phonebook[i].surname, search_query) != NULL) {
            sprintf(result[result_size], "%s %s : %s", phonebook[i].name, phonebook[i].surname, phonebook[i].tel_number);
            result_size++;
        }
    }
    return result_size;
}

void close_phonebook() {
    printf("close\n");
}

int main() {
    // Initialize socket
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char* response;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
       
