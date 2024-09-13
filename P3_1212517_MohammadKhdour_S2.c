//Name:Mohammad Barhom Harbe Khdour
//ID:1212517
//Section:2

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef struct node* BST;
typedef BST ptr;
struct node{
    char name[20];
    char city[20];
    char date[20];
    int id;
    int class;
    struct node* left;
    struct node* right;
};
BST Reader(BST T);
void selectOperation(BST T);
void menu();
BST makeNULL();
BST insert(BST T,int id,int class,char name[],char city[],char data[]);
BST insertByNAME(BST T,int id,int class,char name[],char city[],char data[]);
BST insertionMethod(BST T);
BST delete(BST T,int id);
BST findByID(BST T,int id);
BST update(BST T,int id);
void listByName(BST T);
void listByID(BST T);
void listByClassInLexicographic(BST T,int class);
void listByClass(BST,int class);
void listByCityInLexicographic(BST T,char city[]);
void listByCity(BST T,char city[]);
void print(BST T);
BST sortByNAME(BST T,BST T2);
BST max(BST T);
BST min(BST T);
void saveInFile(BST T);
void printInFile(BST T,FILE *file);
FILE *students;
int main() {
    BST student=makeNULL();
    student=Reader(student);
    selectOperation(student);
    return 0;
}
//////////////////////////////////////////////////
BST Reader(BST T){//read from file and add a student by their ids
    students= fopen("students.data","r");
    if(students==NULL){
        printf("file doesn't exist!!");
        exit(-1);
    }
    int id;
    int class;
    char name [20];
    char city [20];
    char date [20];
    while (fscanf(students,"%[^|]|%d|%d|%[^|]|%s\n",name,&id,&class,city,date)!=EOF)
        T= insert(T,id,class,name,city,date);

    fclose(students);
    return T;
};
/////////////////////////////////////////////////////////////
void selectOperation(BST T){
    int x;//to select operation;
    int id;
    int class;
    char city[20];
    do{
        menu();
        scanf("%d",&x);
        system("cls");
        switch (x) {
            case 1:
                T=insertionMethod(T);
                printf("student added successful");
                sleep(2);
                break;
            case 2:
                printf("Enter ID for student you want to find");
                scanf("%d",&id);
                findByID(T, id);
                sleep(5);
                break;
            case 3: printf("Enter ID for student to update");
                scanf("%d",&id);
                update(T,id);
                sleep(1);
                break;
            case 4:
                listByName(T);
                sleep(12);
                break;
            case 5:
                printf("Enter City name");
                scanf("%s",city);
                listByCityInLexicographic(T,city);
                sleep(10);
                break;
            case 6:
                printf("Enter class number");
                scanf("%d",&class);
                listByClassInLexicographic(T,class);
                sleep(10);
                break;
            case 7:
                printf("Enter ID for student to delete");
                scanf("%d",&id);
                delete(T,id);
                sleep(1);
                break;
            case 8:
                saveInFile(T);
                sleep(1);
                break;
            case 9:
                printf("System will close. Good bye");
                exit(0);
        }
    } while (x);
}
///////////////////////////////////////////////////////////
void menu(){// menu to print operation can system used for
    system("cls");
    printf("\nSelect operation:");
    printf("\n1_ADD new student");
    printf("\n2_Find student by ID");
    printf("\n3_Update info for student");
    printf("\n4_List all students in lexicographic order of their names");
    printf("\n5_List all students from city name in lexicographic");
    printf("\n6_List all students by their class in lexicographic");
    printf("\n7_Delete a student given his/her student ID");
    printf("\n8_Save in File");
    printf("\n9_Exit\n");
}
///////////////////////////////////////////////////////
BST makeNULL(){//return NULL
    return NULL;
}
//////////////////////////////////////////////////////
BST insert(BST T,int id,int class,char name[],char city[],char data[]) {//insert a new student and add him by his ID number
    if (T == NULL) {
        T = (BST) malloc(sizeof(struct node));
        if (T == NULL) {
            printf("out of memory!!");
            exit(-1);
        }
        T->id = id;
        T->class = class;
        strcpy(T->city, city);
        strcpy(T->name, name);
        strcpy(T->date,data);
        T->left = T->right = NULL;
    } else if (id < T->id) {
        T->left = insert(T->left, id, class, name, city,data);
    } else if (id > T->id) {
        T->right = insert(T->right, id, class, name, city,data);
    }else if(id==T->id){
        printf("\nThis id for student: ");
        findByID(T,id);
        sleep(4);
    }

        return T;
}
////////////////////////////////////////////////////////////////////////////////
BST insertByNAME(BST T,int id,int class,char name[],char city[],char data[]){//insert by lexicography order if name is equal will insert by ID

    if (T == NULL) {
        T = (BST) malloc(sizeof(struct node));
        if (T == NULL) {
            printf("out of memory!!");
            exit(-1);
        }
        T->id = id;
        T->class = class;
        strcpy(T->city, city);
        strcpy(T->name, name);
        strcpy(T->date,data);
        T->left = T->right = NULL;
    }
    else if(strcmp(name,T->name)==-1){
        T->left= insertByNAME(T->left,id,class,name,city,data);
    }
    else if(strcmp(name,T->name)==1){
        T->right= insertByNAME(T->right,id,class,name,city,data);
    }
    else if(id < T->id){
        T->left= insertByNAME(T->left,id,class,name,city,data);
    }
    else if(id> T->id){
        T->right= insertByNAME(T->right,id,class,name,city,data);
    }
    return T;
}
////////////////////////////////////////////////////////////////
BST insertionMethod(BST T){//function used with root parameter to insert a student from a user
    char name[20];
    char city[20];
    char date [20];
    int id;
    int class;
    printf("Enter Name\n");
    scanf("%s",name);
    printf("Enter ID\n");
    scanf("%d",&id);
    printf("Enter class\n");
    scanf("%d",&class);
    printf("Enter City\n");
    scanf("%s",city);
    printf("Enter Date\n");
    scanf("%s",date);
    T=insert(T,id,class,name,city,date);
    return T;
}
/////////////////////////////////////////////////////////////////////////////
BST delete(BST T,int id){//delete a student by his ID
    ptr child1=NULL;
    ptr root;
    if(T==NULL) {
        printf("not found to delete");
        return NULL;
    }
    else if(id< T->id)
        T->left= delete(T->left,id);
    else if(id> T->id)
        T->right= delete(T->right,id);
    else if(T->left!=NULL &&T->right!=NULL){//if a student found and have lift and right nodes, we copy data from a minimum right id
        root= min(T->right);
        T->id=root->id;
        T->class=root->class;
        strcpy(T->name,root->name);
        strcpy(T->city,root->city);
        strcpy(T->date,root->date);
        T->right= delete(T->right,T->id);
    }
    else{//if a student found to delete and have one node either lift or right
        if(T->left==NULL)
            child1=T->right;
        if(T->right==NULL)
            child1=T->left;
        T=NULL;
        free(T);
        return child1;
    }
    return T;
}
//////////////////////////////////////////////////////////////////////////////
BST findByID(BST T,int id){//find a student and print his/her data by id
    if(T==NULL){
        printf("isn't found!!\n");
        return NULL;
    }
    else if(id< T->id)
        return findByID(T->left,id);
    else if (id> T->id)
        return findByID(T->right,id);
    else {
        print(T);
        return T;
    }
}
////////////////////////////////////////////////////////////////////////
BST update(BST T,int id){//update info for student
 ptr upd= findByID(T,id);

 if(upd==NULL){
     return NULL;
 }
    printf("To update info for student enter yes: ");
    char yes[10];
    scanf("%s",yes);
if(strcmp(yes,"yes")==0){//to confirm for updating
    delete(T,upd->id);
    char name[20];
    char city[20];
    char date[20];
    int x;
    int y;
            printf("enter name: ");
            scanf("%s", name);
            printf("enter id: ");
            scanf("%d",&x);
            printf("enter class: ");
            scanf("%d", &y);
            printf("enter city: ");
            scanf("%s", city);
            printf("enter Date: ");
            scanf("%s", date);
    insert(T,x,y,name,city,date);
    printf("update student info successful");
    }
else{
    return T;
}
    return upd;
}
///////////////////////////////////////////////////////////////////
void print(BST T){//print all data for student
    if(T==NULL){
        printf("there is no student to print\n");
    }
    else{
        printf("\n%s\t",T->name);
        printf("%d\t",T->id);
        printf("%d\t",T->class);
        printf("%s\t",T->city);
        printf("%s\n",T->date);
    }
}
/////////////////////////////////////////////////////////////////
void listByName(BST T){//sort student by their name and print them
    BST T2=makeNULL();
    if (T) {
       T2= sortByNAME(T,T2);
    }
    listByID(T2);
}
/////////////////////////////////////////////////////////////////
BST sortByNAME(BST T,BST T2){//insert to new tree all student sorted by their id to tree sort by their name
    if(T) {
        T2=insertByNAME(T2,T->id,T->class,T->name,T->city,T->date);
        sortByNAME(T->left,T2);
        sortByNAME(T->right,T2);
    }
   return T2;
}
////////////////////////////////////////////////////////////
void listByID(BST T){//print all student data sorted by their ID
    if (T) {
        listByID(T->left);
        print(T);
        listByID(T->right);
    }
}
///////////////////////////////////////////////////////////
void listByClassInLexicographic(BST T,int class){//list student's data sorted by their name from the same class which we choose
    if(T){
        BST T2=makeNULL();
        T2= sortByNAME(T,T2);
        listByClass(T2,class);
    }
}
////////////////////////////////////////////////////////////
void listByClass(BST T,int class){//list student's data by their ID from the same class
    if (T) {
        listByClass(T->left,class);
        if(class==T->class)
        print(T);
        listByClass(T->right,class);
    }
}
/////////////////////////////////////////////////////////////
void listByCityInLexicographic(BST T,char city[]){// list students' data by their name from the same city
        if(T){
            BST T2=makeNULL();
            T2= sortByNAME(T,T2);
            listByCity(T2,city);
        }
}
/////////////////////////////////////////////////////////////
void listByCity(BST T,char city[]){//list students' data by their ID from the same city
    if (T) {
        listByCity(T->left,city);
        if(strcmp(city,T->city)==0)
            print(T);
        listByCity(T->right,city);
    }
}
/////////////////////////////////////////////////////////////
BST max(BST T){//return maximum ID from tree which sorted by ID or return maximum name from tree which sorted by name
    if ( T != NULL )
        while ( T->right != NULL )
            T = T->right;
    return T;
}
///////////////////////////////////////////////////////////////
BST min(BST T){//return minimum ID from tree which sorted by ID or return minimum name from tree which sorted by name
    if ( T != NULL )
        while ( T->left != NULL )
            T = T->left;
    return T;
}
////////////////////////////////////////////////////////////////
void saveInFile(BST T){//save data to file and use it next time
    students= fopen("students.data","w");
    if(students==NULL) {
        printf("error couldn't open file");
        return;
    }
    BST sort=makeNULL();
    sort= sortByNAME(T,sort);
    printInFile(sort,students);
    fclose(students);
}
//////////////////////////////////////////////////////////////////
void printInFile(BST T,FILE *file){//print info for a student in file
    if (T)
    {
        printInFile(T->left,file);
        fprintf(file,"%s|%d|%d|%s|%s\n",T->name,T->id,T->class,T->city,T->date);
        printInFile(T->right,file);
    }
}