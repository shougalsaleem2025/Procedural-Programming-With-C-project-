#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 struct Taxi{
 int id;
 char driver[20];
 char category[20];
 char plate[7];
 char color[20];
 float rate;
 float minCharge;
 char state;
 struct Taxi *next;
 };
 
 struct Taxi *list=NULL;
 
 void addTripCar(){
struct Taxi *head = NULL , *current ; 

FILE* fp;

fp = fopen("Taxies.txt", "r");

if( fp == NULL)
return ;

int numOfLines = 0 ;
int c;
while ((c = getc(fp)) != EOF) 
if( c == '\n' )
numOfLines++;

fclose(fp);


FILE* fp2;

fp2 = fopen("Taxies.txt", "r");
if( fp2 == NULL)
return ;

int cc;
while ((cc = getc(fp2)) != '\n');

int i ;
for( i=1 ; i<numOfLines ; i++){
struct Taxi *temp = (struct Taxi *) malloc(sizeof(struct Taxi));

fscanf(fp2, "%d %s %s %s %s %f %f ", &(temp->id) , temp->driver , temp->category , 
temp->plate , temp->color , &(temp->rate) , &(temp->minCharge) );

temp->state = 'A' ;
temp->next = NULL;

if( head == NULL){

head = temp ;
current = head ;
}
else{

current->next = temp ; 
current = current->next ; 
}

}//end for

list = head ;
fclose(fp2);
}


void setTripCar(char *category , float *rate) {
if( list == NULL){

printf("empty list\n"); 
return ;
}

struct Taxi *temp ;
temp = list ;

while( temp != NULL){
if( strcmp( temp->category , category ) == 0 
     && temp->rate == *rate) {
     
temp->state = 'R' ;
return ;
}
temp = temp->next ;
}


}

void writeCarsInRide (char* fileName){
if( list == NULL){
printf("empty list \n");
return ; 
}
FILE *file;
file = fopen(fileName, "a");
if (file == NULL){
printf("Error opening file \n");

return;
}
fprintf(file ,"----------------------------------------------------------------------------------------------\n");
fprintf(file ,"The Cars in Ride: \n");
fprintf(file , "%-15s %-15s %-20s %-20s %-15s %-20s \n" , "id","driver","category", "plate","rate" , "state");
struct Taxi *temp = list ;
while(temp != NULL){
if( temp->state == 'R')
fprintf(file , "%-15d %-15s %-20s %-20s %-15.1f %c \n", temp->id , temp->driver , temp->category
 , temp->plate , temp->rate , temp->state );
temp = temp->next ;
}
fclose(file);
}


void printList()
{
if( list == NULL)
{
printf("empty list \n"); 
return ;
}
struct Taxi * temp  ;
temp = list;

while( temp != NULL){
printf( "%-20d %-20s %-20s %-20s %-20.1f %-20.2f %c \n",
(temp->id) , temp->driver , temp->category , temp->plate ,
(temp->rate) , (temp->minCharge) ,temp->state );

temp = temp->next ;
} 
}

//main

int main() {


addTripCar();

printf("The Available Cars:\n");

printList();

char *str1 = "Business" ; 
float f1 = 4.5 ; 

char *str2= "Family" ; 
float f2 = 5.0 ; 

char *str3= "Family" ; 
float f3 = 4.0 ; 

char *str4= "standard" ; 
float f4 = 3.4 ; 

char *str5= "standard" ; 
float f5 = 5.0 ;

setTripCar( str1 , &f1 );
setTripCar( str2 , &f2 );
setTripCar( str3 , &f3 );
setTripCar( str4 , &f4 );
setTripCar( str5 , &f5 );

printf("\n----------------------------------------------------\n"); 
printf("The Cars in Ride :\n");


char *fileName = "Taxies.txt" ;
writeCarsInRide(fileName);


printList();

return 0;
}//end main
