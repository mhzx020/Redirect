#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *link_list[10];

void print_menu();
int get_choice();
void add_paper();
void delete_paper();
void secret();
void get_input(char *buffer, int size, int no_should_fill_full);
int get_num();
void gg();

int main()
{
    setvbuf(stdout, 0, 2, 0);
    int choice;
    while (1){
        print_menu();
        choice = get_num();
        switch (choice){
            case 1:
                add_paper();
                break;
            case 2:
                delete_paper();
                break;
            case 3:
                secret();
            default:
                break;
        }
    }
    printf("thank you\n");
}

void gg()
{
    system("/bin/sh\x00");
}

void secret()
{
    long luck_num;
    printf("enter your luck number:");
    scanf("%ld", &luck_num);
    puts("Maybe you want continue manage paper?");
    int choice;
    while (1){
        print_menu();
        choice = get_num();
        switch (choice){
            case 1:
                add_paper();
                break;
            case 2:
                delete_paper();
                break;
            default:
                return;
        }
    }
    printf("thank you!");
}

void delete_paper()
{
    int index;
    printf("which paper you want to delete,please enter it's index(0-9):");
    scanf("%d", &index);
    if (index < 0 || index > 9)
        exit(1);
    free(link_list[index]);
    puts("delete success !");
}

void add_paper()
{
    int index;
    int length;
    printf("Input the index you want to store(0-9):");
    scanf("%d", &index);
    if (index < 0 || index > 9)
        exit(1);
    printf("How long you will enter:");
    scanf("%d", &length);
    if (length < 0 || length > 1024)
        exit(1);
    link_list[index] = malloc(length);
    if (link_list[index] == NULL)
        exit(1);
    printf("please enter your content:");
    get_input(link_list[index], length, 1);
    printf("add success!\n");
}

void print_menu()
{
    puts("Welcome to use the paper management system!");
    puts("1 add paper");
    puts("2 delete paper");
}

void get_input(char *buffer, int size, int no_should_fill_full)
{
    int index = 0;
    char *current_location;
    int current_input_size;
    while (1){
        current_location = buffer+index;
        current_input_size = fread(buffer+index, 1, 1, stdin);
        if (current_input_size <= 0)
            break;
        if (*current_location == '\n' && no_should_fill_full){
            if (index){
                *current_location = 0;
                return;
            }        
        }else{
            index++;
            if (index >= size)
                break;
        }
    }
}

int get_num()
{
    int result;
    char input[48];
    char *end_ptr;
    
    get_input(input, 48, 1);
    result = strtol(input, &end_ptr, 0);
    if (input == end_ptr){
        printf("%s input is not start with number!\n", input);
        result = get_num();
    }
    return result;
}
