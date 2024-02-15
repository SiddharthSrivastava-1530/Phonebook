#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct record
    {
        char name[100];
        long int number;
        char address[100];
        struct record *next;
    }
;
typedef struct record node;
// Text color codes
#define RESET   "\033[0m"     // Reset to default color
#define RED     "\033[31m"    // Red color
#define GREEN   "\033[32m"    // Green color
#define YELLOW  "\e[1;33m"    // Yellow color
#define BLUE    "\033[34m"    // Blue color
#define LBLUE "\033[1;94m"
#define ORANGE "\033[38;5;208m"
#define cyan "\e[0;36m"

void add_record(node **head, node *p)
{
   
    if (strcmp(p->name, (*head)->name) < 0)
    {   
        p->next = *head;
        *head = p;
    }
    else
    {
        node *dummy = *head;
        node *q = *head;

        while (dummy->next != NULL && strcmp(p->name, dummy->next->name) > 0)
        {
            dummy = dummy->next;
        }

        p->next = dummy->next;
        dummy->next = p;
    }
}

node *delete_record(node *head,char *s)
{

    if(strcmp(s,(*head).name)==0)
    {
        node *x=head;
        head=(*head).next;
        free(x);
        return head;
    }
    else
    {
        node *dummy=head;
        node *q=head;
        head=(*head).next;
        while((*q).next!=NULL)
        {
            if(strcmp(s,(*head).name)==0)
            {
                (*q).next=(*head).next;
                free(head);
                break;
            }
            else
            {
                q=head;
                head=(*head).next;
            }
        }
        if((*q).next==NULL)
        printf("no element matched with your query \n");
        return dummy;
    }
}
void display(node *head)
{ 
    FILE *fptr;
    fptr=fopen("Phonebook.txt","w");
    printf("The phonebook is as follows- \n");
    while(head!=NULL)
    {
        printf("%s %ld %s \n",(*head).name,(*head).number,(*head).address);
        fprintf(fptr,"%s %ld %s \n",(*head).name,(*head).number,(*head).address);
        head=(*head).next;
    }
    fclose(fptr);
}
node *search(node *head,char *A)
{
    node *p,*pos;
    int c=0;
    p=head;
    while(p!=NULL)
    {
        if((strcmp(A,p->name))==0)
        {
            c++;
            return p;
        }
        p=p->next;
    }
    if(c==0)
    {
        printf("No such element found \n");
        return head;
    }
}
void edit_record(node* head,char *A)
{  node*p;
   int t=0;
   char s[100];
   long int num;
   p=search(head,A);
   int key;
   printf("1: Edit number[PRESS 1]\n");
   printf("2: Edit address[PRESS 2]\n");
   printf("Enter the value: ");
   scanf("%d",&key);
   
   if(key==1)
   {
       scanf("%lld",&num);
       p->number=num;
   }
   
  else if(key==2)
   {
       scanf("%s",s);
       strcpy((*p).address,s);
   }
   else{
       printf("Name not found!!!\n");
       
   }
   
   display(head);
    
}
int main()
{
    int c=0;
    FILE *fp;
    char file_name[100];
    char m[10];
    int check;
    node *head;
    while(1){
        /* The password of the phonebook is the name of the text file. Eg: if the text file
        saved is "Hello.txt", the password will be "Hello" */
        printf("Enter password: \t");
        scanf("%s",file_name);
        strcat(file_name,".txt");
        fp = fopen(file_name,"r");  
        if(fp==NULL) {
            fclose(fp);
            printf("No phonebook exists for this password. Would you like to create a new File? \t");
            scanf("%s",m);
            if(strcmp(m,"Yes")==0 || strcmp(m,"Y")==0 || strcmp(m,"yes")==0 || strcmp(m,"y")==0  ){
                fp=fopen(file_name,"w");
                break;
            }
            else if(strcmp(m,"No")==0 || strcmp(m,"N")==0 || strcmp(m,"no")==0 || strcmp(m,"n")==0  )   
                continue;
        }
        else {
            printf("Successfully opened file:\n");
            head=(node *)malloc(sizeof(node));
            check=fscanf(fp, "%s %d %s",(*head).name,&(*head).number,(*head).address);
            (*head).next=NULL;
            while(1){
                node *p;
                p=(node *)malloc(sizeof(node));
                check=fscanf(fp, "%s %d %s",(*p).name,&(*p).number,(*p).address);
                if(check== EOF)
                    break;
                add_record(&head,p);
            }
            display(head);
            c=1;
            break;
        }
    }  
    fclose(fp);
    printf(YELLOW"  -Welcome to the PhoneBook-\n");
    while(1){
    
        int n;
        printf(ORANGE"\t\tMENU \n");
        printf(LBLUE"1. Add a new number [Press 1]\n");
        printf(GREEN"2. Delete a number  [Press 2] \n");
        printf(LBLUE"3. Search a number  [Press 3] \n");
        printf(GREEN"4. Edit a number    [Press 4] \n");
        printf(LBLUE"5. Contact List     [Press 5] \n");
        printf("\n");
        printf(YELLOW"Enter key : ");
        scanf("%d",&n);
        if(n==-1)
            break;
        switch(n){

            case 1:
            printf(ORANGE"   Enter Details-\n");
            if(c==0)
            {
                fp=fopen(file_name,"w");
                head=(node *)malloc(sizeof(node));
                scanf("%s",(*head).name);
                scanf("%ld",&(*head).number);
                scanf("%s",(*head).address);
                fprintf(fp, "%s %d %s",(*head).name,(*head).number,(*head).address);
                (*head).next=NULL;
                fclose(fp);
                //head=p;
                c=1;
            }
            else
            {
                node *p=(node *)malloc(sizeof(node));
                scanf("%s",(*p).name);
                scanf("%ld",&(*p).number);
                scanf("%s",(*p).address);
                //(*p).next=NULL;
                add_record(&head,p);
            }

   
            display(head);
            break;
            case 2:
            printf("enter element to delete \n");
            char nn[100];
            scanf("%s",nn);
            head=delete_record(head,nn);
            display(head);
            break;
            case 3:
            printf("enter element to be searched \n");
            char mm[100];
            scanf("%s",mm);
            node *xx=search(head,mm);
            printf("%s %ld %s\n",(*xx).name,(*xx).number,(*xx).address);
            break;
            case 4:
            printf("enter the contact name to be edited- \n");
            char ss[100];
            scanf("%s",ss);
            edit_record(head,ss);
            break;
            case 5:
            display(head);
            break;
        }
    }
   
}