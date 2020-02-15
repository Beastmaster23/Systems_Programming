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

void create_file(char *str){
    FILE *fp=fopen(str, "r");
    if(fp==NULL)fp=fopen(str, "w");
    fclose(fp);
}

bool is_empty(Apartment *apt){
    if(apt->firstName[0]=='\0'){
        return true;
    }
    if(apt->lastName[0]=='\0'){
        return true;
    }
    if(apt->leaseStart[0]=='\0'){
        return true;
    }
    if(apt->leaseEnd[0]=='\0'){
        return true;
    }
    return false;
}

int read_line(char *line, int max){
    int i=0;
    for(;i<max;i++){
        char c=getc(stdin);
        if(c==-1||c=='\n'||c=='\r'||c=='\0')return i;
        line[i]=c;
    }
    return max;
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

void free_apartment(Apartment* apt){
    free(apt);
}

void insert_apt(int n, Apartment* apt, char *name){
    FILE *fp=fopen(name, "r+b");
    
    int i=fseek(fp, (n-1)*sizeof(Apartment), SEEK_SET);
    if(i!=0)printf("Error\n");
    long nums=fwrite(apt, sizeof(Apartment), 1L, fp);

    fclose(fp);
}

int cmp_apt(Apartment *apt){
    
    return 0;
}

Apartment* find_apt(int n, char *name){
    Apartment* apt=(Apartment*)malloc(sizeof(Apartment));
    FILE* fp=fopen(name, "rb");
    if(fp==NULL){
        free_apartment(apt);
        return NULL;
    }
    
    fseek(fp, (n-1)*sizeof(Apartment), SEEK_SET);
    long nums=fread(apt, sizeof(Apartment), 1L, fp);
    fclose(fp);
    if(nums==0){
        free_apartment(apt);
        apt=NULL;
    }
    return apt;
}

void prompt_balance(int *n){
    printf("Balance: \n");
    char num_buffer[32];
    fgets(num_buffer, 32, stdin);
    *n=atoi(num_buffer);
    //printf("%d\n", *n);
}

Apartment* prompt_create_apartment(int*ip){
    Apartment*apt=(Apartment*)malloc(sizeof(Apartment));
    char num_buffer[32];
    printf("Apartment number: \n");
    fgets(num_buffer, 32, stdin);
    *ip=atoi(num_buffer);
    //printf("%d\n", *ip);
    printf("First name: \n");
    fgets(apt->firstName, 32, stdin);
    //puts(apt->firstName);
    printf("Last name: \n");
    fgets(apt->lastName, 32, stdin);
    //puts(apt->lastName);
    printf("Lease start: \n");
    fgets(apt->leaseStart, 32, stdin);
    //puts(apt->leaseStart);
    printf("Lease end: \n");
    fgets(apt->leaseEnd, 32, stdin);
    //puts(apt->leaseEnd);
    apt->balance=900;
    return apt;
}

Apartment* prompt_create_apartment_with_balance(int*ip){
    Apartment*apt=prompt_create_apartment(ip);
    prompt_balance(&apt->balance);
    return apt;
}

void prompt_apartment_number(int *n){
    printf("Enter an apartment number: \n");
    char num_buffer[32];
    fgets(num_buffer, 32, stdin);
    *n=atoi(num_buffer);
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
    if(newApt->firstName[0]!='\n'&&newApt->firstName[0]!='\0')
        swap_strings(newApt->firstName, apt->firstName);
    if(newApt->lastName[0]!='\n'&&newApt->lastName[0]!='\0')
        swap_strings(newApt->lastName, apt->lastName);
    if(newApt->leaseEnd[0]!='\n'&&newApt->leaseEnd[0]!='\0')
        swap_strings(newApt->leaseEnd, apt->leaseEnd);
    if(newApt->leaseStart[0]!='\n'&&newApt->leaseStart[0]!='\0')
        swap_strings(newApt->leaseStart, apt->leaseStart);
    swap_int(&(apt->balance), &(newApt->balance));
}

int delete_apartment(int n, char* name){
    Apartment* found=find_apt(n, name), *apt;
    if(found==NULL||is_empty(found)){
        return -1;
    }
    free_apartment(found);
    apt=(Apartment*)calloc(1, sizeof(Apartment));
    //show_apartment(found, n);
    insert_apt(n, found, name);
    return 1;
}