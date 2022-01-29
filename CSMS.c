#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
	int VIN;
	char carname[15];
	char carcolor[15];
	char fueltype[15];
	long price;
	int spid;
	int custid;
	int loanstatus;
	long loanamount;
	int status; 
	float EMI;
	int showroomno;
	struct node *left,*right;
	int ht;
}cars;

typedef struct abc
{
	char carbrand[15];
	int count;
	struct abc *next;
}cartypes;

typedef struct salper
{
	int id;
	char password[15];
	long target;
	long salesachieved;
	int showroomno;
	struct salper *left,*right;
	int ht;
}salper;

salper *s1=NULL,*s2=NULL,*s3=NULL;


cartypes *ct=NULL;

cars *sr1=NULL,*sr2=NULL,*sr3=NULL;
int custcount=0;



void display(cars *);
void buyingacar(cars *,int );
int salesid(salper *,int );
int countsp(salper *);
void salesachieved(salper *,int ,int );
void sellingprocess(cars *);
void mostpopularcar(cars *);
cartypes *createnode(cartypes *);
void popularcar(cartypes *);
void counting(cars *);
int popularsp(salper *);
void search(cars *,int );
void displayrange(cars *,cars *,cars *,int ,int );
cars * insert(cars *,int ,char *,char *,char *,long,int );
cars * delete(cars *,int );
int height(cars *);
cars * rotateright(cars *);
cars * rotateleft(cars *);
cars * RR(cars *);
cars * LL(cars *);
cars * LR(cars *);
cars * RL(cars *);
int BF(cars *);
void preorder(cars *T);
salper * insert2(salper *T,int ,char *,int );
salper * Delete2(salper *,int );
int height2(salper *);
salper * rotateright2(salper *);
salper * rotateleft2(salper *);
salper *RR2(salper *);
salper *LL2(salper *);
salper *LR2(salper *);
salper *RL2(salper *);
int BF2(salper *T);
void preorder2(salper *T);
void loanpayment(cars *T);
int salesidsearch(salper *,int,char *);
void popsalesper(salper *,int,int);














void display(cars *T)
{
	if(T!=NULL)
	{
		printf("VIN is%d(Bf=%d)\n",T->VIN,BF(T));
		printf("carname is %s\n",T->carname);
		printf("carcolor is %s\n",T->carcolor);
		printf("fueltype is %s\n",T->fueltype);
		printf("price is %ld\n",T->price);
		
		preorder(T->left);
		preorder(T->right);
	}
}

void buyingacar(cars *T,int vin)
{
	
	int a,b,c;
	float interest;
	long amount;
	if(T->VIN==vin)
	{
		
		printf("1.new customer 2.existing customer\n");
		scanf("%d",&b);
		if(b==1)
		{
			custcount++;
			T->custid=custcount;
		}
		if(b==2)
		{
			printf("enter ur customer id\n");
			scanf("%d",&c);
			T->custid=c;
		}
		T->status=1;
		
		if(T->showroomno==sr1->showroomno)
		{
			
			T->spid=salesid(s1,vin);
			salesachieved(s1,T->spid,T->price);
			sellingprocess(T);
			
		}
		if(T->showroomno==sr2->showroomno)
		{
			T->spid=salesid(s2,vin);
			salesachieved(s2,T->spid,T->price);
			sellingprocess(T);
			
		}
		if(T->showroomno==sr3->showroomno)
		{
			T->spid=salesid(s3,vin);
			salesachieved(s3,T->spid,T->price);
			sellingprocess(T);
			
		}
}
	else if(T->VIN>vin)
	{
		
		buyingacar(T->left,vin);
	}
	else if(T->VIN<vin)
	{
		buyingacar(T->right,vin);
	}

}

int salesid(salper *T,int vin)
{
	int a,i;
	
	for(i=1;i<=countsp(T);i++)
	{
		if(vin%countsp(T)==i-1)
		{
			if(T->showroomno==1)
			{
					a=10*1+i;
					break;
			}
			if(T->showroomno==2)
			{
					a=10*2+i;
					break;
			}
			if(T->showroomno==3)
			{
					a=10*3+i;
					break;
			}
		}
	}
	return a;
	
}

int countsp(salper *T)
{
	
    if (T == NULL) 
       return 0; 
   
    int res = 0; 
    if  (T->left && T->right)  
       res++; 
   
    res += (countsp(T->left) +  
            countsp(T->right)); 
    return res; 
 
}

void salesachieved(salper *T,int id,int cost)
{
	
	if(T->id==id)
	{
		T->salesachieved= T->salesachieved+cost;
		
	}
	else if(T->id>id)
	{
		salesachieved(T->left,id,cost);
	}
	else if(T->id<id)
	{
		salesachieved(T->right,id,cost);
	}
}

void sellingprocess(cars *T)
{
			int a,b,c;
			float interest;
			long amount;
			printf("1.cash 2.loan\n");
			scanf("%d",&a);
			T->loanstatus=a;
			printf("9% rate of interest for 84 months EMI\n");
			printf("8.75% rate of interest for 60 months EMI\n");
			printf("8.50% rate of interest for 36 months EMI\n");
			printf("enter the interest amount\n");
			scanf("%f",&interest);
			printf("how much u want to pay\n");
			scanf("%ld",&amount);
			T->loanamount=T->price-amount+(interest*T->price);
			if(interest==9.00)
			{
				T->EMI=(9*T->price)/8400;
				printf("emi is %f",T->EMI);
			}
			if(interest==8.75)
			{
				T->EMI=(8.75*T->price)/6000;
			}
			if(interest==8.50)
			{
				T->EMI=(8.50*T->price)/3600;
			}
}

void mostpopularcar(cars *T)
{
	cartypes *nptr,*ptr;
	if(T!=NULL)
	{
		if(ct==NULL)
		{
			ct=createnode(ct);
			strcpy(ct->carbrand,T->carname);
	
			
		}
		else
		{
			
			
			ptr=ct;
			while(ptr!=NULL)
			{
				if(strcmp(ptr->carbrand,T->carname)==0)
				{
					ptr=ptr->next;
				}
				else
				{
					nptr=createnode(ct);
					nptr->next=ct;
					ct=nptr;
					strcpy(ct->carbrand,T->carname);
				}
			}
			
		}
		
		mostpopularcar(T->left);
		mostpopularcar(T->right);
	}
}

cartypes *createnode(cartypes *T)
{
	cartypes *nptr;
	nptr=(cartypes*)malloc(sizeof(cartypes));
	nptr->next=NULL;
	nptr->count=0;
	return nptr;
}

void popularcar(cartypes *T)
{
	int max=0;
	char car[15];
	cartypes *ptr;
	
	counting(sr1);
	counting(sr2);
	counting(sr3);	
	ptr=T;
	while(ptr!=NULL)
	{
		if(max<=ptr->count)
		{
			max=ptr->count;
			strcpy(car,T->carbrand);
		}
		ptr=ptr->next;
	}
	printf("most popular car is %s",car);
}
void counting(cars *T)
{
	cartypes *ptr;
	if(T!=NULL)
	{
		ptr=ct;
		while(ptr!=NULL)
		{
			if((strcmp(ptr->carbrand,T->carname)==0)&&T->status==1)
			{
				ptr->count++;
			}
			else
			{
				ptr=ptr->next;
			}
		}
		
		counting(T->left);
		counting(T->right);
	}
}

int popularsp(salper *root)
{ 
int id;
    if (root == NULL) 
      return -1; 
  
    
    int res = root->salesachieved; 
    int lres = popularsp(root->left); 
    int rres = popularsp(root->right); 
    if (lres > res) 
    {
    	res = lres; 
      id=root->id;
	}
      
    if (rres > res) 
    {
    	res = rres;
	  id=root->id; 
	}
	
    return res; 
} 

void popsalesper(salper* T, int key,int a) 
{ 
    if (T == NULL) 
         
  
    if (T->salesachieved == key) 
        printf("most popular sales person in showroom %d is %d",a,T->id); 
  
    
    popsalesper(T->left, key,a); 
  
    
  
    
     popsalesper(T->right, key,a); 
  
     
} 

void search(cars *T,int VIN)
{
	
	
   while(T->VIN != VIN)
   {
	
      if(T != NULL)
	   {
         
			
         
         if(T->VIN > VIN)
		 {
            T = T->left;
         }  
         else
		  {                
            T = T->right;
         }
			
         //not found
         
      }	
	  else
		 {
            printf("there is no car with that number\n");
         }		
   }
   
   printf("car name is %s\n",T->carname);
         printf("car color is %s\n",T->carcolor);
         printf("car status is %d\n",T->status);
         printf("car sold by sales person  %d\n",T->spid);
         printf("car sold to customer id  %d\n",T->custid);
   
   
}

int salesidsearch(salper *T,int id,char *pass)
{
	
	
   while(T->id != id)
   {
	
      
         
			
         
        if(T->id > id)
		 {
            T = T->left;
         }  
         else if(T->id < id)
		{                
            T = T->right;
         }
	
			
         //not found
         else
		 {
            printf("incorrect id");
            return 0;
         }
      			
   }
   if(strcmp(pass,T->password)==0)
	   	{
	   		return 1;
		  }
		  else
		  {
		  	printf("enter correct password\n");
		  	return 0;
		  }
   
   
   
}

void displayrange(cars *p,cars *q,cars *r,int max,int min)
{
	if(p!=NULL)
	{
		if(p->VIN>=min&&p->VIN<=max)
		printf("VIN is%d\n",p->VIN);
		printf("carname is %s\n",p->carname);
		printf("carcolor is %s\n",p->carcolor);
		printf("fueltype is %s\n",p->fueltype);
		printf("price is %ld\n",p->price);
		
		displayrange(p->left,q,r,max,min);
		displayrange(p->right,q,r,max,min);
	}
	if(q!=NULL)
	{
		if(q->VIN>=min&&q->VIN<=max)
		printf("VIN is%d\n",q->VIN);
		printf("carname is %s\n",q->carname);
		printf("carcolor is %s\n",q->carcolor);
		printf("fueltype is %s\n",q->fueltype);
		printf("price is %ld\n",q->price);
		
		displayrange(p,q->left,r,max,min);
		displayrange(p,q->right,r,max,min);
	}
	if(r!=NULL)
	{
		if(r->VIN>=min&&r->VIN<=max)
		printf("VIN is%d\n",r->VIN);
		printf("carname is %s\n",r->carname);
		printf("carcolor is %s\n",r->carcolor);
		printf("fueltype is %s\n",r->fueltype);
		printf("price is %ld\n",r->price);
		
		displayrange(p,q,r->left,max,min);
		displayrange(p,q,r->right,max,min);
	}
}




//cars creation
cars * insert(cars *T,int VIN,char *carname,char *carcolor,char *fueltype,long price,int a)
{
	if(T==NULL)
	{
		T=(cars*)malloc(sizeof(cars));
		T->VIN=VIN;
		strcpy(T->carname,carname);
		strcpy(T->carcolor,carcolor);
		strcpy(T->fueltype,fueltype);
		T->price=price;
		T->left=NULL;
		T->right=NULL;
		T->showroomno=a;
	}
	else
		if(VIN > T->VIN)		// insert in right subtree
		{
			T->right=insert(T->right,VIN,carname,carcolor,fueltype,price,a);
			if(BF(T)==-2)
				if(VIN>(T->right)->VIN)
					T=RR(T);
				else
					T=RL(T);
		}
		else
			if(VIN<T->VIN)
			{
				T->left=insert(T->left,VIN,carname,carcolor,fueltype,price,a);
				if(BF(T)==2)
					if(VIN < T->left->VIN)
						T=LL(T);
					else
						T=LR(T);
			}
		
		T->ht=height(T);
		
		return(T);
}
 
cars * delete(cars *T,int x)
{
	cars *p;
	
	if(T==NULL)
	{
		return NULL;
	}
	else
		if(x > T->VIN)		// insert in right subtree
		{
			T->right=delete(T->right,x);
			if(BF(T)==2)
				if(BF(T->left)>=0)
					T=LL(T);
				else
					T=LR(T);
		}
		else
			if(x<T->VIN)
			{
				T->left=delete(T->left,x);
				if(BF(T)==-2)	//Rebalance during windup
					if(BF(T->right)<=0)
						T=RR(T);
					else
						T=RL(T);
			}
			else
			{
				//data to be deleted is found
				if(T->right!=NULL)
				{	//delete its inorder succesor
					p=T->right;
					
					while(p->left!= NULL)
						p=p->left;
					
					T->VIN=p->VIN;
					T->right=delete(T->right,p->VIN);
					
					if(BF(T)==2)//Rebalance during windup
						if(BF(T->left)>=0)
							T=LL(T);
						else
							T=LR(T);\
				}
				else
					return(T->left);
			}
	T->ht=height(T);
	return(T);
}
 
int height(cars *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
	
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
		
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
	
	if(lh>rh)
		return(lh);
	
	return(rh);
}
 
cars * rotateright(cars *x)
{
	cars *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}
 
cars * rotateleft(cars *x)
{
	cars *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->ht=height(x);
	y->ht=height(y);
	
	return(y);
}
 
cars * RR(cars *T)
{
	T=rotateleft(T);
	return(T);
}
 
cars * LL(cars *T)
{
	T=rotateright(T);
	return(T);
}
 
cars * LR(cars *T)
{
	T->left=rotateleft(T->left);
	T=rotateright(T);
	
	return(T);
}
 
cars * RL(cars *T)
{
	T->right=rotateright(T->right);
	T=rotateleft(T);
	return(T);
}
 
int BF(cars *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
 
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
 
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
 
	return(lh-rh);
}
 
void preorder(cars *T)
{
	if(T!=NULL)
	{
		printf("\nVIN is%d\n",T->VIN,BF(T));
		printf("carname is %s\n",T->carname);
		printf("carcolor is %s\n",T->carcolor);
		printf("fueltype is %s\n",T->fueltype);
		printf("price is %ld\n",T->price);
		
		preorder(T->left);
		preorder(T->right);
	}
}
 




//salesperson creation

salper * insert2(salper *T,int id,char *password,int a)
{
	if(T==NULL)
	{
		T=(salper*)malloc(sizeof(salper));
		T->id=id;
		strcpy(T->password,password);
		T->left=NULL;
		T->right=NULL;
		T->target=20000000;
		T->salesachieved=0;
		T->showroomno=a;
	}
	else
		if(id > T->id)		// insert in right subtree
		{
			T->right=insert2(T->right,id,password,a);
			if(BF2(T)==-2)
				if(id>T->right->id)
					T=RR2(T);
				else
					T=RL2(T);
		}
		else
			if(id<T->id)
			{
				T->left=insert2(T->left,id,password,a);
				if(BF2(T)==2)
					if(id < T->left->id)
						T=LL2(T);
					else
						T=LR2(T);
			}
		
		T->ht=height2(T);
		
		return(T);
}
 
salper * Delete2(salper *T,int id)
{
	salper *p;
	
	if(T==NULL)
	{
		return NULL;
	}
	else
		if(id > T->id)		// insert in right subtree
		{
			T->right=Delete2(T->right,id);
			if(BF2(T)==2)
				if(BF2(T->left)>=0)
					T=LL2(T);
				else
					T=LR2(T);
		}
		else
			if(id<T->id)
			{
				T->left=Delete2(T->left,id);
				if(BF2(T)==-2)	//Rebalance during windup
					if(BF2(T->right)<=0)
						T=RR2(T);
					else
						T=RL2(T);
			}
			else
			{
				//data to be deleted is found
				if(T->right!=NULL)
				{	//delete its inorder succesor
					p=T->right;
					
					while(p->left!= NULL)
						p=p->left;
					
					T->id=p->id;
					T->right=Delete2(T->right,p->id);
					
					if(BF2(T)==2)//Rebalance during windup
						if(BF2(T->left)>=0)
							T=LL2(T);
						else
							T=LR2(T);\
				}
				else
					return(T->left);
			}
	T->ht=height2(T);
	return(T);
}
 
int height2(salper *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
	
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
		
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
	
	if(lh>rh)
		return(lh);
	
	return(rh);
}
 
salper * rotateright2(salper *x)
{
	salper *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->ht=height2(x);
	y->ht=height2(y);
	return(y);
}
 
salper * rotateleft2(salper *x)
{
	salper *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->ht=height2(x);
	y->ht=height2(y);
	
	return(y);
}
 
salper * RR2(salper *T)
{
	T=rotateleft2(T);
	return(T);
}
 
salper * LL2(salper *T)
{
	T=rotateright2(T);
	return(T);
}
 
salper * LR2(salper *T)
{
	T->left=rotateleft2(T->left);
	T=rotateright2(T);
	
	return(T);
}
 
salper * RL2(salper *T)
{
	T->right=rotateright2(T->right);
	T=rotateleft2(T);
	return(T);
}
 
int BF2(salper *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
 
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
 
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
 
	return(lh-rh);
}
 
void preorder2(salper *T)
{
	if(T!=NULL)
	{
		printf("\n%d\n",T->id,BF2(T));
		preorder2(T->left);
		preorder2(T->right);
	}
}

void loanpayment(cars *T)
	{
		if(T!=NULL)
		{
			if(T->loanamount<T->EMI)
			{
				T->loanamount=T->loanamount-T->EMI;
			}
		
		loanpayment(T->left);
		loanpayment(T->right);
		}
	}


	
	

int main()
{
	int op,person,s,no,d,a,min,max,e;
	int x,n,i,op1,sr,z,y;
						int VIN;
						char carname[15];
						char carcolor[15];
						char fueltype[15];
						long price;
	int x1,n1,i1,op2,s11,id1,months=0;
	char password[15],passs[15],pass1[15],pass2[15],pass3[15];
	int idpop1,idpop2,idpop3;
	int bc=0,abc,cd;
	
	FILE* fp=fopen("abc.txt","r");
	//FILE* fp1=fopen("abc.txt","w");
	FILE* fp2=fopen("pqr.txt","r");
	//FILE* fp3=fopen("pqr.txt","w");
	
	while(months<1000)
	{
	
	while(e!=4)
	{
	
		printf("welcome\n");
		printf("1.car creation\n");
		printf("2.sales person creation\n");
		printf("3.accessing\n");
		printf("4.exit\n");
		scanf("%d",&e);
		
		switch(e)
		{
			case 1 :    
						
						do
						{
							printf("\n1)Create:");
							printf("\n2)Insert:");
							printf("\n3)Delete:");
							printf("\n4)Print:");
							printf("\n5)Quit:");
							printf("\n\nEnter Your Choice:");
							scanf("%d",&op1);
							
							switch(op1)
							{
								case 1: printf("\nEnter no. of elements:");
										fscanf(fp,"%d",&n);
										printf("%d",n);
										printf("\nEnter tree data:\n");
										sr1=NULL;
										sr2=NULL;
										sr3=NULL;
										for(i=0;i<n;i++)
										{
											
											fscanf(fp,"%d",&VIN);
											//printf(" vin is %d\n",VIN);
										//	pr//intf("enter carname\n");
											fscanf(fp,"%s",carname);
										//	printf("enter carcolor\n");
											fscanf(fp,"%s",carcolor);
										//	printf("enter fueltype\n");
											fscanf(fp,"%s",fueltype);
										//	printf("enter price\n");
											fscanf(fp,"%ld",&price);
										//	printf("enter the showroom no\n");
											fscanf(fp,"%d",&sr);
											if(sr==1)
											{
												sr1=insert(sr1,VIN,carname,carcolor,fueltype,price,1);
											}
											else if(sr==2)
											{
												sr2=insert(sr2,VIN,carname,carcolor,fueltype,price,2);
											}
											else if(sr==3)
											{
												sr3=insert(sr3,VIN,carname,carcolor,fueltype,price,3);
											}
											
										}
										break;
										
										
								
								case 2:/* printf("\nEnter a data:");
										printf("enter vin\n");
											fscanf(fp1,"%d",&VIN);
											printf("enter carname\n");
											fscanf(fp1,"%s",carname);
											printf("enter carcolor\n");
											fscanf(fp1,"%s",carcolor);
											printf("enter fueltype\n");
											fscanf(fp1,"%s",fueltype);
											printf("enter price\n");
											fscanf(fp1,"%ld",&price);
											printf("enter the showroom no\n");
											fscanf(fp1,"%d",&sr);
											if(sr==1)
											{
												sr1=insert(sr1,VIN,carname,carcolor,fueltype,price,1);
											}
											else if(sr==2)
											{
												sr2=insert(sr2,VIN,carname,carcolor,fueltype,price,2);
											}
											else if(sr==3)
											{
												sr3=insert(sr3,VIN,carname,carcolor,fueltype,price,3);
											}
										break;*/
										
								case 3: printf("\nEnter a data:");
										scanf("%d",&x);
										printf("enter the showroom no\n");
											scanf("%d",&sr);
											printf("enter the showroom no\n");
											scanf("%d",&sr);
											if(sr==1)
											{
												sr1=delete(sr1,x);
											}
											else if(sr==2)
											{
												sr2=delete(sr2,x);
											}
											else if(sr==3)
											{
												sr3=delete(sr3,x);
											}
										break;
								
								case 4: printf("\nPreorder sequence:\n");
										printf("enter the showroom no\n");
											scanf("%d",&sr);
											if(sr==1)
											{
												preorder(sr1);
											}
											else if(sr==2)
											{
												preorder(sr2);
											}
											else if(sr==3)
											{
												preorder(sr3);
											}
										
										break;			
							}
						}while(op1!=5);
						break;
						
						
						
			case 2 :        
							
							do
							{
								printf("\n1)Create:");
								printf("\n2)Insert:");
								printf("\n3)Delete:");
								printf("\n4)Print:");
								printf("\n5)Quit:");
								printf("\n\nEnter Your Choice:");
								scanf("%d",&op2);
								
								switch(op2)
								{
									case 1: printf("\nEnter no. of elements:");
											fscanf(fp2,"%d",&n1);
											printf("\nEnter tree data:\n");
											s1=NULL;
											s2=NULL;
											s3=NULL;
											for(i=0;i<n1;i++)
											{
												//printf("enter the id\n");
												fscanf(fp2,"%d",&id1);
												//printf("enter pasword\n");
												fscanf(fp2,"%s",password);
												
											//	printf("enter the showroom no\n");
												fscanf(fp2,"%d",&s11);
												if(s11==1)
												{
													s1=insert2(s1,id1,password,1);
												}
												else if(s11==2)
												{
													s2=insert2(s2,id1,password,2);
												}
												else if(s11==3)
												{
													s3=insert2(s3,id1,password,3);
												}
											}
											break;
											
											
									case 2: /*printf("\nEnter a data:\n");
											printf("enter the id\n");
												fscanf(fp3,"%d",&id1);
												printf("enter pasword\n");
												fscanf(fp3,"%s",password);
												printf("enter the showroom no\n");
												fscanf(fp3,"%d",&s1);
												if(s11==1)
												{
													s1=insert2(s1,id1,password,1);
												}
												else if(s11==2)
												{
													s2=insert2(s2,id1,password,2);
												}
												else if(s11==3)
												{
													s3=insert2(s3,id1,password,3);
												}
											break;*/
											
											
									case 3: printf("\nEnter a data:");
											scanf("%d",&id1);
											
											printf("enter the showroom no\n");
												scanf("%d",&s1);
												if(s11==1)
												{
													s1=Delete2(s1,id1);
												}
												else if(s11==2)
												{
													s2=Delete2(s2,id1);
												}
												else if(s11==3)
												{
													s3=Delete2(s3,id1);
												}
											break;
									
									case 4: printf("\nPreorder sequence:\n");
											printf("enter the showroom no\n");
												scanf("%d",&s11);
												if(s11==1)
												{
													preorder2(s1);
												}
												else if(s11==2)
												{
													preorder2(s2);
												}
												else if(s11==3)
												{
													preorder2(s3);
												}
											
											break;			
								}
							}while(op2!=5);
							break;
				
				
			case 3 : printf("who are you?\n");
					printf("1.salesperson  2.customer\n");
					scanf("%d",&person);
					switch(person)
					{
						case 1:  while(bc!=1)
								{
									printf("enter the sales person id and showroomno and password\n");
									 scanf("%d%d%s",&z,&y,&passs);
									 if(y==1)
									 {
									 	abc=salesidsearch(s1,z,passs);
									 	if(abc==1)
									 	{
									 		preorder(sr1);
									 		bc=1;
									 		
										}
										else
										{
											bc=0;
										}
									 }
									 if(y==2)
									 {
									 	abc=salesidsearch(s2,z,passs);
									 	if(abc==1)
									 	{
									 		preorder(sr2);
									 		bc=1;
									 		
										}
										else
										{
											bc=0;
										}
									 }
									 if(y==3)
									 {
									 	abc=salesidsearch(s3,z,passs);
									 	if(abc==1)
									 	{
									 		preorder(sr3);
									 		
										}
										else
										{
											bc=1;
										}
									 }
									 
								}break;
								 
								
						case 2: printf("select any option\n");
								printf("1.want to buy acar??\n");
								scanf("%d",&op);
								switch(op)
								{
									case 1: printf("select the showroom name u want to buy\n");
											printf("1.ABC 2.PQR  3.XYZ\n");
											scanf("%d",&s);
											if(s==1)
											{
												display(sr1);
												printf("enter the vin number of car u want to buy\n");
												scanf("%d",&no);
												buyingacar(sr1,no);
											}
											if(s==2)
											{
												display(sr2);
												printf("enter the vin number of car u want to buy\n");
												scanf("%d",&no);
												buyingacar(sr2,no);
											}
											if(s==3)
											{
												display(sr3);
												printf("enter the vin number of car u want to buy\n");
												scanf("%d",&no);
												buyingacar(sr3,no);
											}
											
								
					
					//printf("hii12\n");
					
						
					//	break;
						
					//	
											
								}break;
				}
						
						
						
		}
	}
	
	
	



						int st=0;
						while(st!=1)
						{
						printf("1.most popular car\n");
						printf("2.most succesful sales person\n");
						printf("3.sell function with input details of sales person and customer\n");
						printf("4.sales prediction of next month\n");
						printf("5.enter vin to print all the related details\n");
						printf("6.give 2 vin numbers and print details of their range\n");
						
						scanf("%d",&d);
						
							switch(d)
							{
							case 1: mostpopularcar(sr1);
									mostpopularcar(sr2);
									mostpopularcar(sr3);
									popularcar(ct);
									break;
									
							case 2 : idpop1=popularsp(s1);
									 popsalesper(s1,idpop1,1);
									 idpop1=popularsp(s2);
									 popsalesper(s2,idpop2,2);
									 idpop1=popularsp(s3);
									 popsalesper(s3,idpop3,3);
									 break;
									 
							case 3 : 
							
							case 4: 
							
							case 5: printf("enter vin to print all related details\n");
									scanf("%d",&a);
									search(sr1,a);
									search(sr2,a);
									search(sr3,a);
									break;
									
							case 6: printf("enter the range of vin \n");
									scanf("%d %d",&min,&max);
									displayrange(sr1,sr2,sr3,min,max);
									break;
									 
							}
							printf("do u want to continue press '0' else press 1\n");
							scanf("%d",&st);
						}
						








}
loanpayment(sr1);
	loanpayment(sr2);
	loanpayment(sr3);
	months++;
	fclose(fp);
//fclose(fp1);
fclose(fp2);
//fclose(fp3);
}

	
	
	

	

