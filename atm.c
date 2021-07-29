#include <stdio.h>
#include<string.h>
int pos(int b)
{
 	char c,ch[7];
     int z,i=0,turn=1;
     FILE *fp1;
     fp1= fopen ("account.txt", "r");
     while(1)
     {
     	
        c = fgetc(fp1);
        if (c=='*'){break;}
        if (c=='\n'){
        	i=0;  	
            sscanf(ch,"%d",&z);
        	if (z==b){return turn;}
        	turn++;
        }
         ch[i]=c;
         i++;
     }
     fclose(fp1);
     return -1;
}
int pinamount(char fil[10],int turn)
{
 	int i=0,z,turn1=1;
     FILE *fp1;
     char c,ch[8];
     fp1= fopen (fil, "r");
     
     while(1)
     {
        c = fgetc(fp1);
        if (c=='*'){break;}
        if (c=='\n'){
        	if (turn==turn1){
        		char pr[i];
        		for (int j=0;j<i;j++)
        		{ pr[j]=ch[j];}
            sscanf(pr,"%d",&z);
            return z;
        	}
        	i=0;  	
            turn1++;
            continue;
        }
         ch[i]=c;
         i++; 
     }
     fclose(fp1);
}
void fix(int no,int turn)
{
	char na[10];
	sprintf(na, "%d", no);
     FILE *fp1,*fp2;
     fp1= fopen ("balance.txt", "r");
     char s1[50],c;     
     int i=0,j,turn1=1;
     while(1)
     {
         c = fgetc(fp1);
         s1[i]=c;  
         if (c=='\n' || turn1==1)
         {
         	if (turn==turn1)
         	{
         	if (c=='\n')
         	{
         		i++;
         		}
         		for ( j=0;j<strlen(na);j++,i++)
         		{
         			s1[i]=na[j];
         		}
         		while (1)
         		{
         			if (fgetc(fp1)=='\n')
         			{
         		      s1[i]='\n';
         				break;}
         		}
         	}
         	turn1++;
         }
         i++;
         
        if (c=='*')
        {break;}
     }
     char s[i];
     for ( int k=0;k<i;k++)
     {
     	s[k]=s1[k];
     }
     fclose(fp1);
     
     fp2= fopen ("balance.txt", "w");
     fputs(s,fp2);
     fclose(fp2);
	
}
void mini_write(int account,int state,int amount,int change)
 {
 	char account_name[8];
 	sprintf(account_name,"%d.txt", account);
 	FILE *file;
 	char intro[40];
    file=fopen(account_name,"a+");
	sprintf(intro,"your opening balance is %d\n", amount);
 	char sent[50];
    
   if(fgetc(file)==EOF)
     {
       fprintf(file,"%s",intro);
     }
     
    if (state==1)
    { 
	sprintf(sent,"%d is credited to your account.Your balance is %d\n", change,amount);}
    else
    {
	sprintf(sent,"%d is debited from your account.Your balance is %d\n", change,amount-change);
	}
    fprintf(file,"%s",sent);
    fclose(file);
 }
  void print_mini(int account)
{
 	char account_name[8];
 	sprintf(account_name,"%d.txt", account);
 	FILE *file;
 	char ch;
    file=fopen(account_name,"r");
while(1)
{
if ((ch=getc(file))==EOF)
{break;}
else
{printf("%c",ch);}

}
}
int main()
{
	
	int amount,deposit,withdrawal;
	int select,choice,pin,b,k,turn;
	
	 	int c,d,w,e;
	printf("\n\n===================================================================================\n*******************************Welcome to ATM service******************************\n===================================================================================");
	printf("\n1.FROM CURRENT\n2.FROM SAVINGS\n");
	printf("select\t:");
	scanf("%d",&select);
	if(select>2)
	printf("INVALID");
	else
	{
	if(select=1||2)
	{   while(1)
	   {
	     printf("\nenter account number\t: ");
	     scanf("%d",&b);
	     c=pos(b);
	     if (c== -1)
	     {printf("\nInvalid account number ");
	     printf("\n\n");
	     }
	     else 
	     break;
	   }
	 	printf("enter your pin\t: ");
	 	scanf("%d",&pin);
	 	
	 	k=pinamount("pin.txt",c);
    	 if(pin==k)
	 {
	 	printf("1.Deposit\n\n2.Cash withdrawal\n\n3.Balance Enquiry\n\n4.Mini statement\n\n5.Quit\n\n");
	 	printf("Enter your choice\t:");
	 	scanf("%d",&choice);
	 	switch(choice)
	 	{
	     case 1:while(1)
		{printf("Enter amount in multiples of 100\n");
             printf("Enter the Amount to deposit\t:");
	 		scanf("%d",&deposit);
               if(deposit%100==0)
                break;
                 }

	 	   d=pinamount("balance.txt",c);
	 	   fix(d+deposit,c);
	 	   d=pinamount("balance.txt",c);
	 		printf("Amount %d is successfully deposited into your account.\nAvailable amount is %d.\n",deposit,d);
			mini_write(b,1,d,deposit);
	 		break;
	 	 case 2:printf("Enter amount in multiples of 100\n");
                  printf("Enter the Amount to withdrawal\t:");
	 		    scanf("%d",&withdrawal);
	 		    d=pinamount("balance.txt",c);
                  if(withdrawal%100!=0)
                   printf("Enter amount in multiples of 100");
 		   else if(d-withdrawal<2000)
	 		printf("Exceeds minimum balance.");
	 		else
	 		{
	 		    printf("Please collect your cash %lu\n",withdrawal);
	 		    printf("Transaction successful\n");
	 		    fix(d-withdrawal,c);
				mini_write(b,2,d,withdrawal);
	 		
	 		printf("Available amount=%d.",d-withdrawal);
	 		}
	 		break;
	 	 case 3:
	 	 e=pinamount("balance.txt",c);
	 	 printf("Available amount is %d.",e);
	 		break;
	 	 case 4: print_mini(b);
	 		break;
	 	 case 5:printf("\t");
	 		break;
	 	default:
	 		printf("INVALID");
	 		break;
	 	 }
	 	 }
	 	 else
	 	 printf("The entered pin is invalid");
	
	 	 }
	 	 }
printf("\n###################################################################################\n~~~~~~~~~~~~~~~~~~~~~~Thank you for using our atm service~~~~~~~~~~~~~~~~~~~~~~~~~~\n###################################################################################\n");	 
 
}