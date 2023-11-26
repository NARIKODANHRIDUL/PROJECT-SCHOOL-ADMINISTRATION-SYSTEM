#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gotoxy(int x, int y);
void add_data();
void viewall();
void searchadmno();
void delete_();
void modify();
void details();
void sc();
int disp(int bl);
void screen1();
void pass();
void adscreen();
void userscreen();
void user(int ch);
void adm(char ch);
void exi();
int count();
void screen1();

struct Student {
    int admno;
    char name[30];
    int age;
    char sex[6];
    char phone[12];
};

FILE *f;
struct Student a;

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

int last_member() {
    int count = 1000;
    int admno = 1000;

    FILE *file;
    file = fopen("student.txt", "rb");
    if (file == NULL) {
        // Handle file opening error
        printf("Error opening file!\n");
        return -1; // Indicate an error
    }

    fseek(file, 0, SEEK_SET);
    while (fread(&admno, sizeof(int), 1, file) == 1) {
        count = a.admno;
    }


    fclose(file);
    return count;
}

void enter() {
    system("cls");
    sc();
    printf("\n\n                           STUDENT REGISTRATION           \n");
    printf("                       -=************************=-            ");

    a.admno = last_member();
    a.admno++;

    printf("\n\n\t Enter name \t             :                      (press ! to go back)");
    gotoxy(40, 10);
    scanf("%s", a.name);

    if (strcmp(a.name, "!") == 0) {
        adscreen();
    }

    printf("\t Enter Age                   : ");
    scanf("%d", &a.age);
    printf("\t Enter sex                   : ");
    scanf("%s", a.sex);
    printf("\t Enter phone number          : ");
    scanf("%s", a.phone);

    printf("\n\n\t\tYour admission no is %d", a.admno);
}

void add_data() {
    f = fopen("student.txt", "ab");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    enter();
    fwrite(&a, sizeof(struct Student), 1, f);
    fclose(f);

    gotoxy(20, 24);
    printf("press ENTER to go back!!!!!!!!");
    getchar();
}

void display(struct Student *student) {
    printf("\n");
    printf("\tDetails of the searched student\n");
    printf("------------------------------------------------------------------------------\n");
    printf("\n         Admission Number     : %d\n", student->admno);

    // Convert name to uppercase
    printf("         Name                 : ");
    for (int i = 0; student->name[i] != '\0'; i++)
        printf("%c", toupper(student->name[i]));

    printf("\n         Age                  : %d\n", student->age);
    printf("         Sex                  : %s\n", student->sex);
    printf("         Phone                : %s\n", student->phone);
    printf("_______________________________________________________________________________\n");
    printf("_______________________________________________________________________________\n");
}
void viewall() {
    system("cls");  // Use "clear" for Unix-based systems; use "cls" for Windows
    sc();
    printf("\n\t-=SCHOOL REGISTER=-           \n");
    printf("_______________________________________________________________________________\n");
    printf("_______________________________________________________________________________\n");
    printf("_______________________________________________________________________________\n");
    int i = 1;
    FILE *file;
    file = fopen("student.txt", "rb");
    if (file == NULL) {
        // Handle file opening error
        printf("Error opening file!\n");
        printf("No Data!\n");
        getchar();
        return;
    }
    struct Student a;
    while (fread(&a, sizeof(struct Student), 1, file) == 1) {
        printf("Sno.:%d", i);
        display(&a);
        i++;
        printf("_______________________________________________________________________________\n");
    }
    fclose(file);
    printf("\n\t\tpress ENTER to go back!!!!!!!!!!!!");
    getchar();
}

int retadmno() {
    return a.admno;
}

void searchadmno() {
    int n;
    system("cls");  // Use "cls" for Windows
    sc();
    int flag = 0;
    gotoxy(20, 13);
    printf("## Enter the student admission no to search: ");
    scanf("%d", &n);

    f = fopen("student.txt", "rb");
    if (f == NULL) {
        // Handle file opening error
        printf("Error opening file!\n");
        return;
    }

    while (fread(&a, sizeof(struct Student), 1, f) == 1) {
        if (retadmno() == n) {
            system("cls");  // Use "cls" for Windows
            sc();
            display(&a);
            flag = 1;
        }
    }

    fclose(f);

    if (flag == 0) {
        system("cls");  // Use "cls" for Windows
        sc();
        gotoxy(28, 13);
        printf("Oops!! Record not found!!");
        gotoxy(25, 20);
        printf("press ENTER to go back!!!!!!!");
    } else {
        gotoxy(25, 20);
        printf("press ENTER to go back!!!!!!!");
    }
    getchar();
}

int disp(int bl) {
    system("cls");
    sc();
    int flag = 1;

    FILE *f;
    f = fopen("student.txt", "rb");
    if (f == NULL) {
        // Handle file opening error
        printf("Error opening file!\n");
        return flag; // Indicate an error
    }

    struct Student a;

    while (fread(&a, sizeof(struct Student), 1, f) == 1) {
        if (a.admno == bl) {
            // Assuming display() is a function you've implemented
            display(&a);
            flag = 0;
        }
    }

    fclose(f);

    if (flag == 1) {
        system("cls");
        sc();
        gotoxy(28, 13);
        printf("Oops!! Record not found!!");
        gotoxy(25, 20);
        printf("press any key to go back!!!!!!!");
    }

    return flag;
}
void modify_data(struct Student *a) {
    char nm[20] = " ", sx[20] = " ", ph[20] = " ";
    int ag;

    printf("ENTER NAME     :                       (enter  .  to retain old one)\n");
    printf("ENTER AGE      :                       (enter  1  to retain old one)\n");
    printf("ENTER SEX      :                       (enter  .  to retain old one)\n");
    printf("ENTER PHONE NO :                       (enter  .  to retain old one)\n");

    gotoxy(17, 17);
    fflush(stdin);
    fgets(nm, sizeof(nm), stdin);
    nm[strcspn(nm, "\n")] = 0;

    gotoxy(17, 18);
    scanf("%d", &ag);

    gotoxy(17, 19);
    scanf("%s", sx);

    gotoxy(17, 20);
    scanf("%s", ph);

    if (strcmp(nm, ".") != 0)
        strcpy(a->name, nm);

    if (ag != 1)
        a->age = ag;

    if (strcmp(sx, ".") != 0)
        strcpy(a->sex, sx);

    if (strcmp(ph, ".") != 0)
        strcpy(a->phone, ph);

    printf("\n\n\n\t\tRecord modified successfully");
    gotoxy(25, 25);
    printf("press any key to go back!!!!!!!!");
    getchar();
}
void modify() {
    system("cls");
    sc();

    int bl, t;
    char ch;
    long pos;

    printf("## Please Enter the admission no to be modified: ");
    scanf("%d", &bl);
    t = disp(bl);

    if (t == 0) {
        FILE *f = fopen("student.txt", "r+");
        if (f == NULL) {
            printf("Error opening file!\n");
            return;
        }

        printf("\t\t\tDo you want to modify it(Y/N)???: ");
        scanf(" %c", &ch);

        if (ch == 'y' || ch == 'Y') {
            while (fread(&a, sizeof(struct Student), 1, f) == 1) {
                pos = ftell(f);
                if (a.admno == bl) {
                    modify_data(&a);
                    fseek(f, pos - sizeof(struct Student), SEEK_SET);
                    fwrite(&a, sizeof(struct Student), 1, f);
                    break;
                }
            }
        } else {
            gotoxy(25, 25);
            printf("press any key to go back!!!!!!!");
        }

        fclose(f);
    }
    getchar();
}

void delete_() {
    int no, t;
    char ch;
    system("cls");
    sc();
    gotoxy(22, 13);
    printf("## Enter the admission no to delete: ");
    scanf("%d", &no);
    t = disp(no);

    if (t == 0) {
        gotoxy(21, 18);
        printf("DO YOU WANT TO DELETE IT ? (Y/N) : ");
        scanf(" %c", &ch);

        if (ch == 'y' || ch == 'Y') {
            FILE *f, *f2;
            f = fopen("student.txt", "rb");
            f2 = fopen("tem.txt", "wb");

            if (f == NULL || f2 == NULL) {
                // Handle file opening error
                printf("Error opening file!\n");
                return;
            }

            struct Student a;

            while (fread(&a, sizeof(struct Student), 1, f) == 1) {
                if (a.admno != no) {
                    fwrite(&a, sizeof(struct Student), 1, f2);
                }
            }
            fclose(f);
            fclose(f2);
            remove("student.txt");
            rename("tem.txt", "student.txt");
            system("cls");
            sc();
            gotoxy(27, 13);
            printf("Record Deleted Successfully");
            gotoxy(25, 20);
            printf("press any key to go back!!!!!!!");
        } else {
            gotoxy(25, 25);
            printf("press any key to go back!!!!!!!");
        }
    }
    else{
        printf("Record not found!!!\n");
    }
    getchar();
}


void sc() {
    printf("\n===============================================================================\n");
    printf("---------------------=+#INDIRA GANDHI PUBLIC SCHOOL#+=-------------------------\n");
    printf("===============================================================================\n");
}



void pass() {
    char c[20];
    char user[20];
    loop:
    gotoxy(30, 12);
    printf("USER NAME:");
    gotoxy(30, 13);
    printf("PIN      :");
    gotoxy(41, 12);
    scanf("%s", user);
    getchar();
    printf("\n\n");
    gotoxy(41, 13);
    for (int i = 0; i < 9; i++) {
        c[i] = getchar();
    }
    c[9] = '\0';
    getchar();

    if (((strcmp(user, "user") == 0) || (strcmp(user, "USER") == 0)) && (strcmp(c, "narikodan") == 0)) {
        system("cls");
        sc();
        gotoxy(37, 13);
        printf("WELCOME");
    } else if ((strcmp(user, "user") != 0) && (strcmp(user, "USER") != 0)) {
        system("cls");
        sc();
        gotoxy(25, 13);
        printf("Oops!!! ADMINISTRATION NOT RESPONDING\n\t\t\t (user name is wrong!!!!!)");
        getchar();
        system("cls");
        pass();
    } else if (strcmp(c, "narikodan") != 0) {
        system("cls");
        sc();
        gotoxy(25, 13);
        printf("Oops!!! ADMINISTRATION NOT RESPONDING\n\t\t\t (password is wrong!!!!!)");
        getchar();
        system("cls");
        pass();
    }
}

void adscreen() {
    char ch;
    system("cls");
    sc();
    printf("\n\t[1] STUDENT REGISTRATION      \n\n");
    printf("\t[2] SHOW WHOLE ENTRIES      \n\n");
    printf("\t[3] SEARCH FOR STUDENT BY ADMISSION NO    \n\n");
    printf("\t[4] MODIFY A STUDENT'S DETAILS        \n\n ");
    printf("\t[5] DELETE A STUDENT'S DETAILS         \n\n");
    printf("\t[6] Back                    \n\n");
    printf("\n\t\t## Enter your choice : ");
    scanf(" %c", &ch);
    adm(ch);
    getchar();
}

void exi() {
    system("cls");
    sc();
    printf("\n\n THANKS FOR USING :).............\n\nDeveloped by NARIKODAN HRIDUL\n\n");
printf("      ____      ___     ___     ___         ___         ____\n");
printf("     /    \\    /   \\   /   \\   |   \\       |   \\  \\  / |        |  |  |\n");
printf("    |         |     | |     |  |    \\      |___/   \\/  |___     |  |  |\n");
printf("    |     _   |     | |     |  |    /      |   \\   /   |        |  |  |\n");
printf("     \\___/ |   \\___/   \\___/   |___/       |___/  /    |____    o  o  o\n");

printf("\n\n                              \\(=_= ) (=_=)/\n");
printf("\n           *_*  *_*  *_*  *_*  *_*  *_*  *_*  *_*  *_*  *_*  *_*  \n\n");

exit(0);
}

int main() {
    screen1();
    return 0;
}

void adm(char ch) {
    switch(ch) {
        case '1':
            add_data();
            break;
        case '2':
            viewall();
            break;
        case '3':
            searchadmno();
            break;
        case '4':
            modify();
            break;
        case '5':
            delete_();
            break;
        case '6':
            screen1();
            break;
        default:
            printf("So Sorry!!! Unknown Choice\n TRY AGAIN....");
    }
}

void screen1() {
    char ch;
    start:
    system("cls");
    sc();
    printf("\n\n");
    printf("\t\t[A].ADMINISTRATOR\n");
    printf("\n");
    printf("\t\t[E].EXIT\n\n");
    printf("SELECT YOUR OPTION: ");
    scanf(" %c", &ch);
    switch(ch) {
        case 'A':
        case 'a':
            system("cls");
            pass();
            adm:
            adscreen();
            goto adm;
        case 'E':
        case 'e':
            exi();
        default:
            printf("So Sorry!!! Unknown Choice");
            getchar();
            goto start;
    }
}

