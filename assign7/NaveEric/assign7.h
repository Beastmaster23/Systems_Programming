#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define F_str "apartments.dat"

typedef struct{
    char firstName [32];
    char lastName [32];
    char leaseStart [16];
    char leaseEnd [16];
    int balance;
} Apartment;

void free_apartment(Apartment* apt){
    free(apt);
}

void show_menu(){
    printf("Enter one of the following actions or press CTRL-D to exit.\n");
    printf("C - create a new apartment record\n");
    printf("R - read an existing apartment record\n");
    printf("U - update an existing apartment record\n");
    printf("D - delete an existing apartment record\n");
}

void show_apartment(Apartment* apt, int n){
    printf("Apartment: %d\n", n);
    printf("Tenant name: %s, %s\n", apt->lastName, apt->firstName);
    printf("Lease start: %s \n", apt->leaseStart);
    printf("Lease end: %s\n", apt->leaseEnd);
    printf("Balance: %d\n", apt->balance);
}

void create_file(char *str){
    FILE *fp=fopen(str, "r");
    if(fp==NULL)fp=fopen(str, "w");
    fclose(fp);
}
/*
int empty_string(char* str){
    if(str[0]=='\0'||str[0]=='\n'||str[0]=='\r')return 1;
    return 0;
}

int contains(char c, char* chars, int max_len){

}

void clean_string(char*str, char* chars, int max_c){
    int i=0, j=-1, len=strlen(str);
    char* s=(char *)malloc((len+1) * sizeof(char));
    for(i=0; i<len;i++){
        if(str[i]=='\0')break;
        if(contains(str[i], chars, max_c)<0){
            j++;
            s[j]=str[i];
        }
    }
    j++;
    s[j]='\0';
    swap_strings(str, s);
    free(s);
}
*/
void insert_apt(int n, Apartment* apt, char *name){
    FILE *fp=fopen(name, "r+b");
    int i=fseek(fp, (n-1)*sizeof(Apartment), SEEK_SET);
    if(i!=0)printf("Error\n");
    long nums=fwrite(apt, sizeof(Apartment), 1L, fp);
    fclose(fp);
}

Apartment* find_apt(int n, char *name){
    Apartment* apt=(Apartment*)malloc(sizeof(Apartment));;
    FILE* fp=fopen(name, "rb");

    fseek(fp, (n-1)*sizeof(Apartment), SEEK_SET);
    long nums=fread(apt, sizeof(Apartment), 1L, fp);
    fclose(fp);
    if(nums==0)apt=NULL;
    return apt;
}

Apartment* prompt_create_apartment(int*ip){
    Apartment*apt=(Apartment*)malloc(sizeof(Apartment));
    printf("Apartment number: \n");
    scanf("%d\n", ip);
    //printf("%d\n", *ip);
    printf("First name: \n");
    fgets(apt->firstName, 32, stdin);
    
    //puts(apt->firstName);
    printf("Last name: \n");
    fgets(apt->lastName, 32, stdin);
    //puts(apt->lastName);
    printf("Lease start: \n");
    fgets(apt->leaseStart, 16, stdin);
    //puts(apt->leaseStart);
    printf("Lease end: \n");
    fgets(apt->leaseEnd, 16, stdin);
    //puts(apt->leaseEnd);
    apt->balance=900;
    return apt;
}

Apartment* prompt_create_apartment_with_balance(int*ip){
    Apartment*apt=(Apartment*)malloc(sizeof(Apartment));
    char*num=(char*)malloc(sizeof(char)*32);
    num[31]='\0';
    printf("Apartment number: \n");
    scanf("%32s", num);
    
    *ip=atoi(num);
    printf("%d\n", *ip);
    printf("First name: \n");
    scanf("%32s", apt->firstName);
    FILE *f= fopen("dout.txt", "w");
    fprintf(f, "%s", apt->firstName);
    fclose(f);
    printf("%s\n", apt->firstName);
    printf("Last name: \n");
    fgets(apt->lastName, 32, stdin);
    printf("%s\n", apt->lastName);
    printf("Lease start: \n");
    fgets(apt->leaseStart, 32, stdin);
    printf("%s\n", apt->leaseStart);
    printf("Lease end: \n");
    fgets(apt->leaseEnd, 32, stdin);
    printf("Balance: \n");
    fgets(num, 32, stdin);
    apt->balance=atoi(num);

    return apt;
}

void prompt_apartment_number(int *n){
    printf("Enter an apartment number: \n");
    scanf("%d\n", n);
    //printf("%d\n", *n);
}

void swap_strings(char* str, char* str2){
    char *temp = (char *)malloc((strlen(str) + 1) * sizeof(char));

    strcpy(temp, str2);
    strcpy(str2, str);
    strcpy(str, temp);
    free(temp);
}
void swap_int(int* n, int* n2){
    int temp = *n2;
    *n2=*n;
    *n=temp;
}
void update_apartment(Apartment* apt, Apartment* newApt){
    if(*newApt->firstName!='\0')
        swap_strings(newApt->firstName, apt->firstName);
    if(*newApt->lastName!='\0')
        swap_strings(newApt->lastName, apt->lastName);
    if(*newApt->leaseEnd!='\0')
        swap_strings(newApt->leaseEnd, apt->leaseEnd);
    if(*newApt->leaseStart!='\0')
        swap_strings(newApt->leaseStart, apt->leaseStart);
    swap_int(&(apt->balance), &(newApt->balance));
}

int delete_apartment(int n, char* name){
    Apartment* found=find_apt(n, name), *apt;
    if(found==NULL){
        return -1;
    }
    free_apartment(found);
    apt=(Apartment*)calloc(1, sizeof(Apartment));

    insert_apt(n, apt, name);
    return 1;
}

