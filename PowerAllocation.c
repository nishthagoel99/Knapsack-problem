
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   PowerAllocation.c
 * Author: Nishtha
 *
 * Created on April 15, 2019, 5:24 PM
 */



#include<stdio.h>
//#include<conio.h>

int knpsk ( int ,int ,int[], int[], int[][100]);
void optn ( int ,int,int[],int[],int[][100],int[]);
int remainpower(int,int,int,int[],int[]);

int max(int, int);
int max_wt,ppwatt[20],remain=0,u,value,sum=0;


int main(){

int w[20],p[20],n,i,j,v[10][100],othervalue,totalprofit;


printf("Enter the no. of categories\n");
scanf("%d",&n);

printf("Enter the capacity of the generator in kiloWatts\n");
scanf("%d",&max_wt);


for(i=1;i<=n;i++){
printf("Enter category %d : power in kW \n",i);
  scanf("%d",&w[i]);

printf("Enter the price per kWatt for category %d\n",i);
  scanf("%d",&ppwatt[i]);
  p[i]=ppwatt[i]*w[i]; //category 1 costs total amount is in price[i]
  
}
value=knpsk(n,max_wt,w,p,v);


printf("Solution of the KNAPSACK problem is \n");
for(i=0;i<=n;i++){
  for(j=0;j<=max_wt;j++){
    printf("%d\t",v[i][j]);
     }
     printf("\n");
   }

printf("The option selected are :\n");
optn(n,max_wt,w,p,v,ppwatt);


 printf("Profit for the supplier is %d\n",value);
 
 //if the maxwt>the total sum of the combined categories then remaining power!=0
if(remain!=0){
   othervalue=remainpower(n,max_wt,remain,w,ppwatt);
   totalprofit=othervalue+value;
   printf("\n\n Total profit now is %d",totalprofit);
}



getchar();
return 0;

}

int knpsk (int n, int max_wt, int w[], int p[], int v[10][100])
{
 int i,j;
 for(i=0;i<=n;i++)
{
  for(j=0;j<=max_wt;j++)
  {
    //if there is no item or capacity of Knapsack is zero
    if(i==0 || j==0)
      v[i][j]=0;
    //if weight of ith item is greater than the capacity of knapsack
    else if(w[i]>j)
       v[i][j]= v[i-1][j];
    else
     v[i][j]=max(v[i-1][j],p[i]+v[i-1][j-w[i]]);
  }

 }
 return (v[n][max_wt]);
}

void optn (int n,int max_wt,int w[],int p[],int v[10][100],int ppwatt[])
{
  int i,j;
  i=n;
  j=max_wt;
  while((i!=0)&& (j!=0))
  {
   if( v[i][j]!= v[i-1][j] )
   {
    printf("Category %d :Power in kWs %d : Price per kW %d :Total price %d\n",i,w[i],ppwatt[i],p[i]);
    j=j-w[i];
    sum+=w[i];
   }
   i--;
  }
   remain=max_wt-sum;
}


int remainpower(int n,int max_wt,int remain,int w[],int ppwatt[]){
    int i,high,pos,total;
    high=ppwatt[0];
    
    //calculate the highest price per watt in all the categories
    for(i=1;i<=n;i++){
        if(high<ppwatt[i]){
            high=ppwatt[i];
            pos=i;
        }
    }
    total=ppwatt[pos]*remain;
    printf(" Remaining %d kW is provided by %d category with %d kWs:Price per kW %d :Total price offering %d:\n",remain,pos,w[pos],ppwatt[pos],total);
    return total;
}

int max ( int a, int b)
{
 return ( (a>b)?a:b);
}


