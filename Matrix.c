#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

float Ga[5][5];

void scan(float a[5][5],int *ma,int *na);
void display(float a[5][5],int m,int n);
void save(float a[5][5],int m,int n,char flag);
float determinant(float a[5][5],int m,int n,char *error);
void transpose(float a[5][5],int *m,int *n);
void inverse(float a[5][5], int m,int n, char *error);
void interchange(float a[5][5],int m,int n, char flag);
void multiplyK(float a[5][5],int m,int n, char flag);
void multiplyRC(float a[5][5],int m,int n, char flag);
void elementary(float a[5][5],int m,int n);

void main()
{
	float a[5][5],d=0;
	int m,n,ch;
	char error='n';
	
	printf("\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MATRIX OPERATIONS PROGRAM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
	printf("\nTaking input for primary matrix...\n");
	scan(a,&m,&n);
	while(1)
	{
		printf("\n1:Edit matrix\t 2:Display matrix\t 3:Transpose\n4:Determinant\t 5:Inverse\n6:Elementary transformations\t 7:Exit\n\nEnter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: scan(a,&m,&n);
			        break;
			
			case 2: printf("Current matrix is:\n");
					display(a,m,n);
			        break;
			
			case 3: save(a,m,n,'a');
					transpose(a,&m,&n);
					
					printf("\nThe transpose is:\n");	
					display(a,m,n);

					save(a,m,n,'b');
			        break;
			
			case 4: d=determinant(a,m,n,&error);
					if(error=='n')
					{
						printf("The determinant is: %g\n\n",d);
					}
					
					else
						error='n';
			        break;
			
			case 5: inverse(a,m,n,&error);
			        break;
			
			case 6: elementary(a,m,n);
			        break;
			
			case 7: exit(0);
			
			default: printf("\nInvalid choice. Try again.\n");
					 break;
						
		}
	}
	getch();
}

void scan(float a[5][5],int *mp,int *np)
{
	int m,n,i,j;
	printf("Enter the order of the matrix:");
	scanf("%d%d",&m,&n);
	*mp=m; *np=n;
	printf("Enter the matrix elements:\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%f",&a[i][j]);
		}
	}
			
}

void display(float a[5][5],int m,int n)
{
	int i,j;
	printf("\n");
	for(i=0;i<m;i++)
		{for(j=0;j<n;j++)
			{
				if(a[i][j]>=0)
					printf("\t %.3g",a[i][j]);
				
				else
					printf("\t%.3g",a[i][j]);	
			}
		 printf("\n");
		}
}

void save(float a[5][5],int m,int n,char flag)
{
	int i,j;
	char choice;
	if(flag=='a')
	{
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				Ga[i][j]=a[i][j];
			}
		}
	}
	
	else if(flag=='b')
	{
		while(1)
		{
			printf("\nDo you want to save the resultant matrix as primary matrix (Y/N)?");
			scanf(" %ch",&choice);
			if(choice=='y')
			{				
				printf("Resultant matrix saved successfully.\n");
				break;
			}
			
			else if(choice=='n')
				 {
				 	for(i=0;i<m;i++)
					{
						for(j=0;j<n;j++)
						{
							a[i][j]=Ga[i][j];
						}
					}
				
					printf("Resultant matrix discarded.\n");
					break;
				 }
			
			else
				printf("Invalid choice. Try again.\n");
		}
	}
	
}

float determinant(float a[5][5],int m,int n,char *error)
{
	float d=0.0, c=1.0, b[5][5];
	int x,y,z,p,q;
	*error='n';
	
	if(m!=n)
	{
		printf("\nError: The matrix should be a square matrix of order nXn.\n\n");
		*error='y';
	}
	
	else if(m==1)
	{
		return(a[0][0]);
	}
	
	else
	{
		d=0;
		
		for(x=0;x<m;x++)
		{
			p=0;
			q=0;
		
			for(y=0;y<m;y++)
			{
				for(z=0;z<m;z++)
				{
					b[y][z]=0;
					if((y!=0)&&(z!=x))
					{
						b[p][q]=a[y][z];
						if(q<(m-2))
							q++;
						else
						{
							q=0;
							p++;
						}
					}
				}
			}
		d+=c*(a[0][x]*determinant(b,m-1,n-1,error));
		c=-c;
		}
	}
	
	return(d);
}

void transpose(float a[5][5],int *m,int *n)
{
	int i,j;
	float res[5][5];
	for(i=0;i<*m;i++)
	{
		for(j=0;j<*n;j++)
		{
			res[j][i]=a[i][j];
		}
	}
	
	i=*m;
	*m=*n;
	*n=i;
	
	for(i=0;i<*m;i++)
	{
		for(j=0;j<*n;j++)
		{
			a[i][j]=res[i][j];
		}
	}
	
}

void inverse(float a[5][5], int m,int n, char *error)
{
	float b[5][5],c[5][5],d;
	int p,q,r,s,x,y,i,j;

	d=determinant(a,m,n,error);
	if(*error=='y')
	{
		*error='n';
		return;
	}
	
	else if(d==0)
	{
		printf("\nError: The determinant of the matrix is zero.\n");
		return;
	}

	else if(m==1)
	{
		save(a,m,n,'a');
		
		a[0][0]=(1/a[0][0]);
		printf("\nThe inverse matrix is:\n%.3g\n\n",a[0][0]);
		
		save(a,m,n,'b');
		return;
	}
	
	else
	{
		save(a,m,n,'a');
		for(r=0;r<m;r++)
		{
			for(s=0; s<m; s++)
			{
				x=0;
				y=0;
				
				for(p=0;p<m;p++)
				{
					for(q=0;q<m;q++)
					{
						if(p!=r && q!=s)
						{
							b[x][y]=a[p][q];
							
							if(y<(m-2))
								y++;
							else
							{
								y=0;
								x++;
							}
						}
					}
				}
			
				c[r][s]=pow(-1,r+s)*determinant(b,m-1,m-1,error);
			}
		}
		
		transpose(c,&m,&n);
		
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				a[i][j]=c[i][j]/d;
			}
		}
	
		printf("\nThe inverse matrix is:\n");
		display(a,m,n);
		
		save(a,m,n,'b');
		return;	
			
	}
}

void interchange(float a[5][5],int m,int n, char flag)
{
	int i,p,q;
	float temp;
	
	if(flag=='r')
	{
		printf("\nEnter the two row numbers to interchange:");
		scanf("%d%d",&p,&q);
	
		if((--p<m)&&(--q<m))
		{
			save(a,m,n,'a');
			for(i=0;i<n;i++)
			{
				temp=a[p][i];
				a[p][i]=a[q][i];
				a[q][i]=temp;
				
			}
		}
		
		else
		{
			printf("Row numbers must be less than matrix order.\n");
			return;
		}
	}
	
	else if(flag=='c')
	{
		printf("\nEnter the two column numbers to interchange:");
		scanf("%d%d",&p,&q);
	
		if((--p<n)&&(--q<n))
		{
			save(a,m,n,'a');
			for(i=0;i<m;i++)
			{
				temp=a[i][p];
				a[i][p]=a[i][q];
				a[i][q]=temp;
				
			}
		}
		
		else
		{
			printf("Column numbers must be less than matrix order.\n");
			return;
		}
			
	}
	
	printf("\nResultant matrix is:\n");
	display(a,m,n);
	
	save(a,m,n,'b');
}

void multiplyK(float a[5][5],int m,int n, char flag)
{
	int i,p;
	float k;
	
	if(flag=='r')
	{
		printf("\nEnter the row number:");
		scanf("%d",&p);
		printf("Enter the multiplier:");
		scanf("%f",&k);
	
		if(k)
		{
			if(--p<m)
			{
				save(a,m,n,'a');
				for(i=0;i<n;i++)
				{
					a[p][i]*=k;
				}
			}
			
			else
			{
				printf("Row number must be less than matrix order.\n");
				return;
			}
		}
		
		else
		{
			printf("Multiplier constant must not be zero.\n");
			return;
		}
	}
		
	else if(flag=='c')
	{
		printf("\nEnter the column number:");
		scanf("%d",&p);
		printf("Enter the multiplier:");
		scanf("%f",&k);
		
		if(k)
		{
			if(--p<n)
			{
				save(a,m,n,'a');
				for(i=0;i<m;i++)
				{
					a[i][p]*=k;
				}
			}
			
			else
			{
				printf("Column number must be less than matrix order.\n");
				return;
			}
			
		}
		
		else
		{
			printf("Multiplier constant must not be zero.\n");
			return;
		}
	}
	
	printf("\nResultant matrix is:\n");
	display(a,m,n);
	
	save(a,m,n,'b');
}

void multiplyRC(float a[5][5],int m,int n, char flag)
{
	int i,p,q;
	float k;
	
	if(flag=='r')
	{
		printf("\nEnter the two row numbers to add:");
		scanf("%d%d",&p,&q);
		printf("Enter the multiplier:");
		scanf("%f",&k);
	
		if(k)
		{
			if((--p<m)&&(--q<m))
			{
				save(a,m,n,'a');
				for(i=0;i<n;i++)
				{
					a[p][i]+=a[q][i]*k;
				}
			}
			
			else
			{
				printf("Row numbers must be less than matrix order.\n");
				return;
			}
		}
		
		else
		{
			printf("Multiplier constant must not be zero.\n");
			return;
		}
	}
	
	else if(flag=='c')
	{
		printf("\nEnter the two column numbers to add:");
		scanf("%d%d",&p,&q);
		printf("Enter the multiplier:");
		scanf("%f",&k);
	
		if(k)
		{
			if((--p<n)&&(--q<n))
			{
				save(a,m,n,'a');
				for(i=0;i<m;i++)
				{
					a[i][p]+=a[i][q]*k;
				}
			}
			
			else
			{
				printf("Column numbers must be less than matrix order.\n");
				return;
			}
			
		}
		
		else
		{
			printf("Multiplier constant must not be zero.\n");
			return;
		}
	}
	
	printf("\nResultant matrix is:\n");
	display(a,m,n);
	
	save(a,m,n,'b');
}

void elementary(float a[5][5],int m,int n)
{
	int ch=0;
	
	while(ch!=7)
	{
		printf("\n1:Rm<->Rn\t 2:Rm->kRm\t 3:Rm->Rm+kRn");
		printf("\n4:Cm<->Cn\t 5:Cm->kCm\t 6:Cm->Cm+kCn");
		printf("\n7:Exit elementary transformations\n\nEnter the choice:");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1: interchange(a,m,n,'r');
					break;
			
			case 2: multiplyK(a,m,n,'r');
					break;
			
			case 3: multiplyRC(a,m,n,'r');
					break;
			
			case 4: interchange(a,m,n,'c');
					break;
			
			case 5: multiplyK(a,m,n,'c');
					break;
			
			case 6: multiplyRC(a,m,n,'c');
					break;
			
			case 7: printf("\nExiting elementary transformations.\n");
					break;
			
			default: printf("\nInvalid choice. Try again.\n");
					 break;
			
		}
		
	}
	
}

