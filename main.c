#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unitTest.h"

#define N 100

typedef struct Student{
    int id;
    char *name;
}student;


student *init() {
    student *temp = (student *)malloc(sizeof(student));
    temp->name = (char *)malloc(sizeof(char) * 30);
    printf("Enter Your Id:\n");
    scanf("%d", &temp->id);
    printf("Enter Your Name:\n");
    scanf("%s", temp->name);
    printf("Your Data Successfully Saved\n");
    getchar();
    return temp;
}

int compare(student *stuList, int stuListLen, int stuId) {
    int i = 0;
    for (i = 0; i < stuListLen; i++) {
        if (stuId <= stuList[i].id) {
            return i;
        }
    }
    return stuListLen;;
}


int insert(student *stuList, int *stuListLen, student *data) {
    if (*stuListLen == 0) {
        stuList[*stuListLen] = *data;
        (*stuListLen)++;
        printf("Index %d data inserted total = %d\n",0,*stuListLen);
        return 0;
    }else {
        int position = compare(stuList, *stuListLen, data->id);
        for (int i = *stuListLen; i > position; i--) {
            stuList[i] = stuList[i - 1];
        }
        stuList[position] = *data;
        (*stuListLen)++;
        printf("Index %d data inserted total = %d\n",position,*stuListLen);
        return position;
    }
}

int delete(student *stuList, int *stuListLen, char *name) {
    if (*stuListLen == 0) {
        printf("There is no student %s!\n",name);
        return 0;
    }
    for (int i = 0; i < *stuListLen; i++) {
        if (strcmp(stuList[i].name, name) == 0) {
            free(stuList[i].name);

            for (int j = i; j < *stuListLen - 1; j++) {
                stuList[j] = stuList[j + 1];
            }
            (*stuListLen)--;
            return 1;
        }
    }
    printf("There is no student %s!\n",name);
    return 0;
}

void display(student *stuList, int stuListLen) {
    for (int i = 0; i < stuListLen; i++) {
        printf("Student's Id =%d\t Student's Name=%s\n", stuList[i].id, stuList[i].name);
    }
}

student *search(student *stuList, int stuListLen, char *name) {
    for (int i = 0; i < stuListLen; i++) {
        if (strcmp(stuList[i].name, name) == 0) {
            return &stuList[i];
        }
    }
    return NULL;
}

void save(FILE *fp, int stuListLen, student *stuList) {
    for (int i = 0; i < stuListLen; i++) {
        fprintf(fp,"%d %s\n",stuList[i].id,stuList[i].name);
    }
}

void load(FILE *fp, int *stuListLen, student *stuList) {
    int id;
    char name[30 + 1];
    while (fscanf(fp, "%d %s\n", &id, name) != EOF) {
        student newStudent;
        newStudent.id = id;
        newStudent.name = (char *)malloc(sizeof(char) * (strlen(name) + 30));
        strcpy(newStudent.name, name);
        insert(stuList, stuListLen, &newStudent);
    }
}


void freeStudentList(student *stuList, int stuListLen) {
    for (int i = 0; i < stuListLen; i++) {
        free(stuList[i].name);
    }
}

void menuShow() {
    printf("---------------------------------------------------------------------------\n");
    printf("                Data    Structure   Enrollment  Program\n");
    printf("---------------------------------------------------------------------------\n");
    printf("                1. Enrollment ('1')\n");
    printf("                2. Cancel     ('2')\n");
    printf("                3. Search by name   ('3')\n");
    printf("                4. Quit       ('q')\n");
    printf("                5. Enrollment Lists   ('4')\n");
    printf("                6. Save       ('s')\n");
    printf("                7. Load       ('l')\n");
    printf("---------------------------------------------------------------------------\n");
}

void request(char choice, student *stuList, int *stuListLen, student *cache, FILE *write, FILE *read) {
    switch (choice) {
        case '1': {
            char i;
            printf("If you want to enroll by cached Data Press 'y/n'\n");
            scanf("%c", &i);
            getchar();
            if(i == 'y') {
                insert(stuList, stuListLen, cache);
            }else {
                insert(stuList, stuListLen, init());
            }
            break;
        }

        case '2':
            printf("Enter name for delete:\n");
        char *deleteName = malloc(sizeof(char)*30);
        scanf("%s", deleteName);
        getchar();
        int result=delete(stuList, stuListLen, deleteName );
        if(result == 1) {
            printf("Student = %s deleted\n", deleteName);
        }
        free(deleteName);
        break;

        case '3':
            printf("Enter name for Search:\n");
        char *searchName = malloc(sizeof(char)*30);
        scanf("%s", searchName);
        getchar();
        student *temp = search(stuList, *stuListLen, searchName);
        if(temp == NULL) {
            printf("Student not found\n");
        }
        else {
            printf("Student = %s's ID=%d\n", searchName,temp->id);
        }
        free(searchName);
        break;
        case '4':
            printf("Students List:\n");
        display(stuList, *stuListLen);
        break;
        case 's':
            printf("Saving...\n");
        write=fopen("students.txt", "w");
        save(write, *stuListLen, stuList);
        fclose(write);
        break;
        case 'l':
            printf("Loading...\n");
        read=fopen("students.txt", "r");
        load(read, stuListLen, stuList);
        fclose(read);
        break;
        default:
            printf("Check your input\n");
    }
}

void unitTest0() {
    student stuList[N];
    int stuListLen = 0;
    student s1;
    student s2;
    student s3;
    student s4;

    //given
    s1.id = 2024;
    s1.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s1.name,"Spring");
    s2.id = 2025;
    s2.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s2.name,"Lilian");
    s3.id = 2026;
    s3.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s3.name,"Woodrow");
    s4.id = 2027;
    s4.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s4.name,"Raphael");

    //when
    insert(stuList, &stuListLen, &s1);
    insert(stuList, &stuListLen, &s3);
    insert(stuList, &stuListLen, &s2);
    insert(stuList, &stuListLen, &s4);

    //then
    assertMallocIsNotNull(s1.name);
    assertEqualInt(stuListLen,4);
    assertEqualInt(stuList[0].id,2024);
    assertEqualString(stuList[0].name,"Spring");
    assertEqualString(stuList[stuListLen-1].name,"Raphael");


}

void unitTest1() {
    student stuList[N];
    int stuListLen = 0;
    student s1;
    student s2;
    student s3;
    student s4;

    //given
    s1.id = 2024;
    s1.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s1.name,"Spring");
    s2.id = 2025;
    s2.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s2.name,"Lilian");
    s3.id = 2026;
    s3.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s3.name,"Woodrow");
    s4.id = 2027;
    s4.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s4.name,"Raphael");

    insert(stuList, &stuListLen, &s1);
    insert(stuList, &stuListLen, &s3);
    insert(stuList, &stuListLen, &s2);
    insert(stuList, &stuListLen, &s4);

    //when

    delete(stuList, &stuListLen, s1.name);

    //then
    assertEqualInt(stuListLen,3);
    assertEqualString(stuList[0].name,"Lilian");
    assertMallocIsNotNull(search(stuList, stuListLen, s1.name)); // s1 has been deleted. failed is normal
    assertMallocIsNotNull(search(stuList, stuListLen, s2.name)); // search,delete test both
}

void unitTest2() {
    student stuList[N];
    int stuListLen = 0;
    student s1;
    student s2;
    student s3;
    student s4;

    //given
    s1.id = 2024;
    s1.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s1.name,"Spring");
    s2.id = 2025;
    s2.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s2.name,"Lilian");
    s3.id = 2026;
    s3.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s3.name,"Woodrow");
    s4.id = 2027;
    s4.name = (char *)malloc(sizeof(char) * 30);
    strcpy(s4.name,"Raphael");

    insert(stuList, &stuListLen, &s1);
    insert(stuList, &stuListLen, &s3);
    insert(stuList, &stuListLen, &s2);
    insert(stuList, &stuListLen, &s4);

    //when
    /**
     *  save all
     */
    FILE *write = fopen("studentTest.txt","w");
    save(write, stuListLen, stuList);
    fclose(write);

    /**
     * delete all
     */
    delete(stuList, &stuListLen, s1.name);
    delete(stuList, &stuListLen, s2.name);
    delete(stuList, &stuListLen, s3.name);
    delete(stuList, &stuListLen, s4.name);

    /**
     * load all
     */
    FILE *read = fopen("studentTest.txt","r");
    load(read,&stuListLen,stuList);
    fclose(read);


    //then

    assertEqualInt(stuListLen,4);
    assertEqualString(stuList[0].name,"Spring");

}

int main(void)
{
    unitTest0();
    unitTest1();
    unitTest2();

    FILE *write = NULL;
    FILE *read = NULL;
    student students[N];
    int studentsLen = 0;


    /***
     * Start point of the Program Caching Current Student's Data
     */
    student *cache = init();

    while(1) {
        menuShow();
        char choice;
        scanf("%c", &choice);
        getchar();
        if (choice == 'q') {
            printf("-------Exit-------\n");
            freeStudentList(students, studentsLen);
            free(cache);
            exit(0);
        }
        request(choice, students, &studentsLen, cache,write,read);
    }


}