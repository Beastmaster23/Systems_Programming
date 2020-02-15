#include "assign7.h"

#define MAX_BUFFER 32

int main(int argc, char const *argv[])
{
    create_file(F_str);

    char buffer[MAX_BUFFER];
    //show_menu();

    /*while(fgets(c, 2, stdin)!=NULL){
        printf("%s\n", c);
        int n=0;
        Apartment *apt;
        Apartment *found;
        switch (c[0])
        {
        case 'c':
            apt=prompt_create_apartment(&n);
            found=find_apt(n, F_str);
            if(found!=NULL){
                //show_apartment(apt, n);
                printf("ERROR: apartment already exists\n");
            }
            else{
                insert_apt(n, apt, F_str);
                //show_apartment(apt);
            }
            free_apartment(found);
            free_apartment(apt);
            break;
        /*case 'r':
            prompt_apartment_number(&n);
            found=find_apt(n, F_str);
            if(found==NULL){
                //show_apartment(apt, n);
                printf("ERROR: apartment not found\n");
                break;
            }
            show_apartment(found, n);
            free_apartment(found);
            break;
        case 'u':
            apt=prompt_create_apartment_with_balance(&n);
            found=find_apt(n, F_str);
            if(found==NULL){
                //show_apartment(apt, n);
                printf("ERROR: apartment not found\n");
                break;
            }
            //show_apartment(apt, n);
            update_apartment(apt, found);
            //show_apartment(apt, n);
            free_apartment(found);
            free_apartment(apt);
            break;
        case 'd':
            prompt_apartment_number(&n);
            
            if(delete_apartment(n, F_str)==1){
                printf("Record %d was successfully deleted.\n", n);
            }else
            {
                printf("ERROR: apartment not found\n");
            }
            break;
        default:
            printf("ERROR: invalid option");
            printf("\n");
            break;
        }

        //show_menu();
    };*/
    
    while(scanf("%32s", buffer)>0){
        printf("%s\n", buffer);

        int n=0;
        Apartment *apt;
        Apartment *found;

        switch (buffer[0])
        {
        
        case 'u':
            apt=prompt_create_apartment_with_balance(&n);
            
            free_apartment(apt);
            break;
        default:
            break;
        }
    }

    return 0;
}
