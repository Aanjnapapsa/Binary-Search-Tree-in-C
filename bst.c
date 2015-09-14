/* Binary-Tree-in.c
//My program create the binary Search tree for the City,read the name of the city from text file,so need to pass the name of the text file as an argument. Program will do Tree Traversal(Pre,post and In Order), Add New City, There Cordinates,Search,Delete the already Existing City(However Deletion Function is not working fullflage some time give the segmentaion fault).*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max 1000

struct node
{
	struct node *parentnode;
	struct node *lc;
	char arr[30];
	int x;
	int y;
	struct node *rc;
}*btree;;
int count=0;
char buff[max];
//struct node *btree;
struct node* bst(char * ,int ,int );
void search();
struct node* delete();
void add_city();
void print_bt(struct node *btree);
struct node * temp_node(char *,int i,int j);
void find(char city[],struct node **par,struct node **loc);
void postorder(struct node *btree);
void preorder(struct node *btree);

void main ( int argc,char * argv[])
{
	btree=NULL;
	FILE *fp;
	int i=0,j=0,k;
	char city[30],*token,s[2]=",";
	if (argc!=2)
	{
		printf("\nInvalid Argument:\n");
		exit(0);
	}
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("\n %s file not found::\n",argv[1]);
		exit(0);
	}
	printf("\nCities Stored In The File Are::");
	printf("\n__________________________________________");
	printf("\nNAME      \t |Xcordinate|Ycordinate |");
	printf("\n__________________________________________");
	while (fgets(buff,max,fp)!=NULL)
	{
		token=strtok(buff,s);
		sscanf(token,"%s",city);
		token=strtok(NULL,s);
		sscanf(token,"%d",&i);
		token=strtok(NULL,s);
		sscanf(token,"%d",&j);
		printf("\n%s     \t |\t%d  | %d\t|",city,i,j);
		bst(city,i,j);
	}
	printf("\n____________________________________________");
	printf("Num Of Cities Are:%d|\n",count);
	printf("___________________________________________________________________");
	fclose(fp);
	int p=1;
	printf("\nOPERATIONS!!!");	
	printf("\n[1].Tree Traversal [2].Add New City [3].Search [4].Delete [5].EXIT");
	while(1)
	{	printf("\n____________________________________________________________________\n");
		printf("|Enter Your Choice:::");
		scanf("%d",&k);
		switch(k)
		{	int z=0;
			case 1:
				printf("\nOPERATIONS!!!\n");
				printf("\n[1].In Order Traversal [2].Post Order [3].Pre Order [4].EXIT");
				while(z<4)
				{	printf("\n_____________________________________________________________\n");
				 	printf("\tEnter Choice:::");
				 	scanf("%d",&z);
					printf("_____________________________________________________________\n");
				 	switch(z)
					{
					case 1:
						printf(" \t[!!!IN-ORDER TRAVERS!!!]");
						printf("\n______________________________________________________________");
						printf("\nNAME      \t|X-CORD | Y-CORD|\tPARENT ");
						printf("\n______________________________________________________________\n");
						print_bt(btree);
						printf("\t\t\t\t\t\tNum Of Cities Are:%d",count);
						break;
					case 2:
                                                			printf(" \t[!!!POST-ORDER TRAVERS!!!]");
						printf("\n______________________________________________________________");
						printf("\nNAME      \t|X-CORD | Y-CORD|\tPARENT ");
						printf("\n______________________________________________________________\n");
						postorder(btree);
						printf("\t\t\t \t\t\tNum Of Cities Are:%d",count);
						break;
					case 3:
                                               			printf(" \t[!!!PRE-ORDER TRAVERS!!!]");
						printf("\n______________________________________________________________");
						printf("\nNAME      \t|X-CORD | Y-CORD|\tPARENT ");
						printf("\n______________________________________________________________\n");
						preorder(btree);
						printf("\t\t \t \t\t\tNum Of Cities Are:%d",count);
						break;
					case 4:
						break;
					default:
						printf("\n[1].In Order Traversal [2].Post Order [3].Pre Order [4].EXIT\n");
				 	}
				}
				z=0;printf("\n[1].Tree Traversal [2].Add New City [3].Search [4].Delete [5].EXIT\n");
				break;
			case 2:
				add_city();
				print_bt(btree);
				break;
			case 3:
				search();
				break;
			case 4:
				delete();
				printf("Deletion Successful\n");
				break;

			case 5:
				exit(0);
				break;
			default:
				printf("\n[1].Tree Traversal [2].Add New City [3].Search [4].Delete [5].EXIT\n");
		}
	}	
}
//create the binary tree of city
struct node* bst(char city[],int i,int j)
{
	struct node *parent,*location,*temp;count++;
	find(city,&parent,&location);//to find the location of city in the tree
	if(location!=NULL)
	{
		printf("Name Allready present\n");
		return;
	}
	if(btree==NULL)
	{
		btree=temp_node(city,i,j);
		return(btree);
	}
	else
        	if(strcmp(city,parent->arr)<0)
		{	
			parent->lc=temp_node(city,i,j);
			parent->lc->parentnode=parent;
		}
        	else
		{
            		parent->rc=temp_node(city,i,j);
			parent->rc->parentnode=parent;
		}
	return(btree);
}
//to allocate the memory to new node
struct node * temp_node(char city[],int i,int j)
{
	struct node *temp=(struct node*)malloc(sizeof (struct node));
	temp->lc=NULL;
	temp->parentnode=NULL;
	strcpy(temp->arr,city);
	temp->x=i;
	temp->y=j;
	temp->rc=NULL;	
}
//print the binary tree of city in order
void print_bt(struct node *btree)
{

	if(btree!=NULL)
	{	
		print_bt(btree->lc);
		if ( btree->parentnode !=NULL)
			{printf("%s     \t|%d  \t|%d\t|\t%s\n",btree->arr,btree->x,btree->y,btree->parentnode->arr);}
		else 
			{printf("%s     \t|%d  \t|%d\t|\t!!!!ROOT!!!!!\n",btree->arr,btree->x,btree->y);}
		print_bt(btree->rc);
	}
}
//to print post order traversal of tree
void postorder(struct node *btree)
{
	if(btree!=NULL)
	{
		postorder(btree->lc);
		postorder(btree->rc);
		if ( btree->parentnode !=NULL)
			{printf("%s     \t|%d  \t|%d\t|\t%s\n",btree->arr,btree->x,btree->y,btree->parentnode->arr);}
		else 
			{printf("%s     \t|%d  \t|%d\t|\t!!!!ROOT!!!!!\n",btree->arr,btree->x,btree->y);}
	}
}
//to print pre order traversal of tree
void preorder(struct node *btree)
{
	if(btree!=NULL)
	{
		if ( btree->parentnode !=NULL)
			{printf("%s     \t|%d  \t|%d\t|\t%s\n",btree->arr,btree->x,btree->y,btree->parentnode->arr);}
		else 
			{printf("%s     \t|%d  \t|%d\t|\t!!!!ROOT!!!!!\n",btree->arr,btree->x,btree->y);}
		preorder(btree->lc);
		preorder(btree->rc);
	}
}
//to add new city to the tree
void add_city()
{
	int a,b;char c[20];
	printf("\nEnter The Name Of The City::\n");
	scanf("%s",c);
	printf("Enter The X Dimanstion of The %s::",c);
	scanf("%d",&a);
	printf("Enter The Y Dimanstion of %s::",c);
	scanf("%d",&b);
	bst(c,a,b);
}
//to search a city name
void search ()
{
	struct node *t=btree;
	int cmp;	char city1[20];
	printf("\nEnter The Name Of City \n");
	scanf("%s",city1);
	if(btree!=NULL)
	{
		while(strcmp(t->arr,city1)!=0)
		{
			if(t->lc!=NULL || t->rc!=NULL)
			{
				if(strcmp(t->arr,city1)>0)
				{	t=t->lc;	}
				else// (cmp>0)
				{	t=t->rc;	}
			}
			else {printf("\nNo Such ::{%s} City Found\n",city1);}
		}
		if (strcmp(city1,t->arr)==0)
		{	printf("\n!!!Search Is Successful And City Details Are As!!!!!");//if(strcmp(city1,t->arr)==0)
			printf("\n_____________________________________________");
			printf("\nName \t|X-Cord|Y-Cord|LeftChild|RightChild|");
			printf("\n____________________________________________");
			if(t->lc!=NULL &&t->rc!=NULL)
				{struct node * L,*R;L=t->lc;R=t->rc;
				printf("\n%s\t|%d    |%d    |%s\t|%s\n",t->arr,t->x,t->y,L->arr,R->arr);
				t=btree;}
			else if(t->lc==NULL &&t->rc!=NULL)	
				{printf("\n%s\t|%d    |%d    |NO\t|%s\n",t->arr,t->x,t->y,t->rc->arr);
				t=btree;}
			else if(t->lc!=NULL &&t->rc==NULL)	
				{printf("\n%s\t|%d   |%d   |%s\t|NO\n",t->arr,t->x,t->y,t->lc->arr);
				t=btree;}
			else if(t->lc==NULL && t->rc==NULL)	
				{printf("\n%s   |%d   |%d   |NO\t|NO\n",t->arr,t->x,t->y);
				t=btree;}
			else
				{printf("\nNo Such {%s} City Found\n",city1);}
		}
		else 
			printf("\nNo Such ::{%s} City Found\n",city1);
	}
	else 
		printf("\nNO City In Tree !!! Tree Is Empty\n");
}
//to delete the city from the tree
struct node* delete()
{
	struct node *t=btree,*k,*p,*m;
	int cmp;
	char city1[20];
	printf("\nEnter The Name Of City To Delete\n");
	scanf("%s",city1);
	if(btree!=NULL)
	{	
		while(strcmp(t->arr,city1)!=0)
		{	printf("\nAt Node %s, StrCmpVal[%d]\n",t->arr,strcmp(t->arr,city1));
			k=t;
			if(strcmp(t->arr,city1)>0)
			{	t=t->lc;	}
			else
			{	t=t->rc;	}
		}
		if (strcmp(t->arr,city1)==0)
		{
			if (t->lc==NULL && t->rc==NULL)//when want to delete leaf node
			{count--;
				printf("\nAt Node=%s,Left child=%p,Right Child=%p\n",t->arr,t->lc,t->rc);
				if(t==k->lc)
				{		k->lc=NULL;	free(t);		}
				else
				{	k->rc=NULL;	free(t);			}
			}
			else if(t->lc!=NULL && t->rc==NULL)//when want to delete node having only left child
			{count--;
				printf("\nAt Node=%s,Left child=%s,Right Child=%p ,Parent node =%s\n",t->arr,t->lc->arr,t->rc,t->parentnode->arr);
				k->lc=t->lc;	t->lc->parentnode=k;	free(t);
			}
			else if(t->lc==NULL && t->rc!=NULL)//when want to delete node having only right child
			{count--;
				printf("\nAt Node=%s,Left child=%p,Right Child=%s ,Parent Node=%s\n",t->arr,t->lc,t->rc->arr,t->parentnode->arr);
				k->rc=t->rc;	t->rc->parentnode=k;	free(t);
			}
			else//when want to delete intermendiate node
			{	if(t->lc!=NULL && t->rc!=NULL)
				{	
					if(t->lc->rc!=NULL )
					{	p=t;	m=t->lc;//one time go to left child
						while(m->rc!=NULL && m->lc!=NULL)//chack until leaf node comes
						{	
							p=m;	m=m->rc;//then go to right most child in the tree
						}
						printf("\nAt Node=%s,Left child=%s,Right Child=%s\n,ParentNode=%s",t->arr,t->lc->arr,t->rc->arr,t->parentnode->arr);
						m->parentnode=t->parentnode;
						if(t->lc!=NULL)
							{	t->lc->parentnode=m;	}
						if(t->rc!=NULL)
							{	t->rc->parentnode=m;	}
						m->lc=t->lc;	m->rc=t->rc;	p->rc=NULL;	count--;	free(t);		//return btree;
						printf("\nAt Node=%s,Left child=%s,Right Child=%s,PerentNode=%s\n",m->arr,m->lc->arr,m->rc->arr,m->parentnode->arr);	
					}
				//else//t->lc->rc==NULL
				}		
			}
		}
		
	}
	else
		printf("\nNO Such City To Delete\n");
}
//find function
void find(char *str,struct node **par,struct node **loc)
{
	*par = NULL;
	*loc = NULL;
	struct node *ptr,*ptrsave;
	if(btree==NULL) return;
	if(!(strcmp(str,btree->arr)))
	{
		*loc=btree;
		return;
	}
	ptrsave = NULL;
	ptr = btree;
	while(ptr!=NULL) {
		if(!(strcmp(str,ptr->arr))) break;
		ptrsave = ptr;
		if(strcmp(str,ptr->arr)<0)
			ptr=ptr->lc;
		else
			ptr=ptr->rc;
	}
	*loc=ptr;
	*par=ptrsave;
}
