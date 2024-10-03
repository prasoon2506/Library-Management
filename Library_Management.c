#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
    char name[30];
    char author[30];
    int id;
    struct book *next;
};

struct student {
    char name[30];
    char email[20];
    char book[20];
    char a[30];
    int id;
    struct student *next;
};

struct book *start_lib = NULL;
struct student *start = NULL;

struct book *initialize_lib(struct book *);
struct student *book_issue(struct student *);
struct student *book_return(struct student *);
struct book *display_lib(struct book *);
struct book *delete_book(int);
struct book *add_book(char[], char[], int);
void display(struct student *);
void greetings();
void main_menu();

int main() {
    start_lib = initialize_lib(start_lib);
    greetings();
    main_menu();
    return 0;
}

void greetings() {
    printf("\n\n");
    printf("\t\t\t     ****************************************\n");
    printf("\t\t\t     *                                      *\n");
    printf("\t\t\t     *     WELCOME TO STUDENT LIBRARY       *\n");
    printf("\t\t\t     ****************************************\n");
    printf("\t\t\t     *     Ghaziabad, Uttar Pradesh, India  *\n");
    printf("\t\t\t     *    Email: prasoongupta2004@gmail.com *\n");
    printf("\t\t\t     *     Contact: 8604486518              *\n");
    printf("\t\t\t     ****************************************\n");
    printf("\n\n\t\t\t             Press Enter to continue: ");
    getchar(); // Using getchar() instead of getch()
}

void main_menu() {
    int choice;
    do {
        printf("\n\t\t\t************* MAIN MENU **************\n");
        printf("\t\t\t\t1. ISSUE BOOKS\n");
        printf("\t\t\t\t2. RETURN BOOKS\n");
        printf("\t\t\t\t3. DISPLAY STUDENT DETAILS\n");
        printf("\t\t\t\t4. EXIT\n");
        printf("\n\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline after input
        switch (choice) {
            case 1: 
                start = book_issue(start); 
                break;
            case 2: 
                start = book_return(start); 
                break;
            case 3: 
                display(start); 
                break;
            case 4: 
                exit(0); // Proper exit with status 0
            default:
                printf("\n\t\tInvalid option! Press Enter to try again.\n");
                getchar(); // Replacing getch() with getchar()
        }
    } while (choice != 4);
}

struct book *initialize_lib(struct book *start) {
    struct book *ptr, *new_book1, *new_book2, *new_book3, *new_book4, *new_book5;

    new_book1 = (struct book *)malloc(sizeof(struct book));
    new_book1->next = NULL;
    start_lib = new_book1;
    strcpy(new_book1->name, "The Kite Runner");
    strcpy(new_book1->author, "Khaled Hosseini");
    new_book1->id = 101;
    ptr = new_book1;

    new_book2 = (struct book *)malloc(sizeof(struct book));
    new_book2->next = NULL;
    strcpy(new_book2->name, "To Kill A Mockingbird");
    strcpy(new_book2->author, "Harper Lee");
    new_book2->id = 102;
    ptr->next = new_book2;
    ptr = new_book2;

    new_book3 = (struct book *)malloc(sizeof(struct book));
    new_book3->next = NULL;
    strcpy(new_book3->name, "The Alchemist");
    strcpy(new_book3->author, "Paulo Coelho");
    new_book3->id = 103;
    ptr->next = new_book3;
    ptr = new_book3;

    new_book4 = (struct book *)malloc(sizeof(struct book));
    new_book4->next = NULL;
    strcpy(new_book4->name, "Pride And Prejudice");
    strcpy(new_book4->author, "Jane Austen");
    new_book4->id = 104;
    ptr->next = new_book4;
    ptr = new_book4;

    new_book5 = (struct book *)malloc(sizeof(struct book));
    new_book5->next = NULL;
    strcpy(new_book5->name, "A Tale Of Two Cities");
    strcpy(new_book5->author, "Charles Dickens");
    new_book5->id = 105;
    ptr->next = new_book5;

    return start_lib;
}

struct student *book_issue(struct student *start) {
    struct book *ptr;
    struct student *ptr2, *new_student;
    int i = 1, id, flag = 0;

    if (start_lib == NULL) {
        printf("\n\t\tNo books left in the library to issue!\n");
    } else {
        ptr = start_lib;
        printf("\n\t*************** Books Available: ****************\n");
        while (ptr != NULL) {
            printf("\n\t Book %d\n", i);
            printf("\t Book Title: %s\n", ptr->name);
            printf("\t Name of Author: %s\n", ptr->author);
            printf("\t Book ID: %d\n", ptr->id);
            ptr = ptr->next;
            i++;
        }

        printf("\n\n\t Enter the Book ID: ");
        scanf("%d", &id);
        ptr = start_lib;

        while (ptr != NULL) {
            if (ptr->id == id) {
                flag = 1;
                break;
            }
            ptr = ptr->next;
        }

        if (flag == 1) {
            ptr = start_lib;
            while (ptr->id != id) {
                ptr = ptr->next;
            }

            new_student = (struct student *)malloc(sizeof(struct student));
            printf("\n\t Enter Student Details:\n");
            printf("\n\t Enter your Name: ");
            scanf("%29s", new_student->name);  // Avoiding buffer overflow
            printf("\n\t Enter your Email: ");
            scanf("%19s", new_student->email);  // Avoiding buffer overflow
            strcpy(new_student->book, ptr->name);
            strcpy(new_student->a, ptr->author);
            new_student->id = ptr->id;
            new_student->next = NULL;

            if (start == NULL) {
                start = new_student;
            } else {
                ptr2 = start;
                while (ptr2->next != NULL) {
                    ptr2 = ptr2->next;
                }
                ptr2->next = new_student;
            }

            start_lib = delete_book(new_student->id);
        } else {
            printf("\n\tInvalid Book ID!\n");
        }
    }

    return start;
}

struct student *book_return(struct student *start) {
    struct student *ptr, *preptr;
    char bookname[30], authorname[30];
    int flag = 0, identity;

    printf("\n\n\t*************** Books Submission: ****************\n");
    printf("\n\n\t Enter your Book ID: ");
    scanf("%d", &identity);
    ptr = start;

    while (ptr != NULL) {
        if (ptr->id == identity) {
            flag = 1;
            break;
        }
        ptr = ptr->next;
    }

    if (flag == 1) {
        ptr = start;
        if (ptr->id == identity) {
            strcpy(bookname, start->book);
            strcpy(authorname, start->a);
            start = start->next;
            free(ptr);
            add_book(bookname, authorname, identity);
        } else {
            while (ptr->id != identity) {
                preptr = ptr;
                ptr = ptr->next;
            }
            strcpy(bookname, ptr->book);
            strcpy(authorname, ptr->a);
            preptr->next = ptr->next;
            free(ptr);
            add_book(bookname, authorname, identity);
        }
        printf("\n\tBook returned successfully!\n");
    } else {
        printf("\n\tInvalid Book ID!\n");
    }

    return start;
}

void display(struct student *start) {
    struct student *ptr = start;
    if (ptr == NULL) {
        printf("\n\tNo student records to display!\n");
    } else {
        while (ptr != NULL) {
            printf("\n\t************* Student Details: **************\n");
            printf("\t Student Name: %s\n", ptr->name);
            printf("\t Student Email: %s\n", ptr->email);
            printf("\t Name of Book Issued: %s\n", ptr->book);
            printf("\t Book ID: %d\n", ptr->id);
            ptr = ptr->next;
        }
    }
}

struct book *delete_book(int id) {
    struct book *ptr, *preptr;
    ptr = start_lib;

    if (ptr == NULL) {
        return NULL;
    }

    if (ptr->id == id) {
        start_lib = ptr->next;
        free(ptr);
    } else {
        while (ptr->id != id) {
            preptr = ptr;
            ptr = ptr->next;
        }
        preptr->next = ptr->next;
        free(ptr);
    }

    return start_lib;
}

struct book *add_book(char name[], char author[], int id) {
    struct book *new_book, *ptr;

    new_book = (struct book *)malloc(sizeof(struct book));
    strcpy(new_book->name, name);
    strcpy(new_book->author, author);
    new_book->id = id;
    new_book->next = NULL;

    if (start_lib == NULL) {
        start_lib = new_book;
    } else {
        ptr = start_lib;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = new_book;
    }

    return start_lib;
}
