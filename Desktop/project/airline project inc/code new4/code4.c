#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Passenger info to be on ticket
struct info 
{
  char name[30];
  int age;
  char sex[1];
  int seat;
  int otp;
};

//OTP generator to avoid unauthorised access
int pass() 
{
  int rnum;    
  srand(time(0));
  rnum = (rand() % (1000000-100000+1)) + 100000;    
  return (rnum);
};

//Display the seat arrangement
void seatDisplay(int i)
{
  int j;
  printf("Pick a seat:\n");
  for (j=0; j<5; j++)
  {printf("\t\t%2d\t\t", i);i++;}
  printf("\n");
  for (j=0; j<5; j++)
  {printf("\t\t%2d\t\t", i);i++;}
};

//Get user details and Display it on the ticket
void ticket(int p, int s)
{
  struct info table[30];
  printf("\nEnter your Name (as First name_Last name):\t");
  scanf("%s", table[p].name);
  printf("\nEnter your Age:\t");
  scanf("%d", &table[p].age);
  printf("\nEnter your Gender(M or F or T):\t");
  scanf("%s", table[p].sex);
  table[p].seat = s;
  
  printf("\n\n----------------------------------\n");
  printf("           Garuda Airlines\n\n");
  printf("   Name: %s\n", table[p].name);
  printf("   Age: %2d            Sex: %s    \n", table[p].age, table[p].sex);
  printf("   Seat no : %d                   \n", table[p].seat);
  printf("   Thank You!                    \n");
  printf("  We wish You a Happy Journey!!! \n");
  printf("----------------------------------\n");
};

//Search if the entered seat is reserved or not?
int searchSeat(int rs[], int p, int s) 
{
  int q; 
  for (q=0; q<p; q++)
  {
    if (rs[q] == s) 
    {  return q;  }
    else
    {  return -1;  }
  }
};

//If the OTP matches correctly, delete the entry
int cancelSeat(int rs[], struct info table[],int p, int q)
{
  if (q < p) 
  {  
    p = p - 1;
    for (int j=q; j<p; j++) 
    {  
      rs[j] = rs[j+1];
      table[j] = table[j+1];
    }
  }
  return p;
};


int main()
{
  int o, c;               //For input of Menu options
  unsigned int s;         //Seat no.
  int q;                  //General counter
  static int p = 0;       //Passenger counter
  static int i;           //Seat display counter
  int rs[30] = {};        //Reserved Seats 
  struct info table[30];  //Passenger Info
  char cabin[][15] = {"First Class", "Business Class", "Economy Class"};
  
  mainMenu:
  printf("\n\t\t\t\t\t***Welcome to Garuda Airlines***\n\n");
  printf("Choose an option: \n1. Book a Seat\n2. Cancel Reservation\n");
  printf("\t\t\t\t\t\t\tPress 0 to exit...\n");
  scanf("%d", &o);

  
  switch (o)
  {
    case 0:  
      exit(0);
 
    
    case 1:
      printf ("\nChoose Cabin Class: \n");
      for (q=0; q<3; q++)
      {
        printf("%1d %s\n", q+1, cabin[q]);
      }
      scanf("%d\n", &c);
      printf("\nYou chose:\n%1d. %s\n\n", c, cabin[c-1]);
      
      if (c==1)
      {  
        i=1;  seatDisplay(i);
        cselect1: printf("\nChoose a seat: ");
        scanf("%2d", &s);
        
        if (s>10)
        {  printf("Wrong Number!");goto cselect1;  }
        else
        {
          for (q=0; q<=p; q++)
          {
            if (rs[q] == s)
            {  printf("\nSeat Taken");goto cselect1;  }        
            else
            {
              rs[p] = s;
              ticket(p, s);
              table[p].otp = pass();
              printf("%d is your OTP.\nPlease save it for future reference.\n DO NOT SHARE IT WITH ANYONE.\n", table[p].otp);
            }
          }
        }
      }
      
      else if (c==2)
      {  
        i=11; seatDisplay(i);
        cselect2: printf("\nChoose a seat: ");
        scanf("%2d", &s);
        
        if (s>20 && s<11)
        {  printf("Wrong Number!");goto cselect2;  }
        else
        {
          for (q=0; q<=p; q++)
          {
            if (rs[q] == s)
            {  printf("\nSeat Taken");goto cselect2;  }        
            else
            {
              rs[p] = s;
              ticket(p, s);
              table[p].otp = pass();
              printf("%d is your OTP.\nPlease save it for future reference.\n DO NOT SHARE IT WITH ANYONE.\n", table[p].otp);
            }
          }
        } 
      }
      
      else
      {
        i=21; seatDisplay(i);
        cselect3: printf("\nChoose a seat: ");
        scanf("%2d", &s);
        
        if (s>30 && s<21)
        {  printf("Wrong Number!");goto cselect3;  }
        else
        {
          for (q=0; q<=p; q++)
          {
            if (rs[q] == s)
            {  printf("\nSeat Taken");goto cselect3;  }        
            else
            {
              rs[p] = s;
              ticket(p, s);
              table[p].otp = pass();
              printf("%d is your OTP.\nPlease save it for future reference.\n DO NOT SHARE IT WITH ANYONE.\n", table[p].otp);
              p++;
            }
          }
        }
      }
      goto mainMenu;     
      break;
 
      
    case 2:
    
      printf("\nSeat Cancellation");
      tryAgain: printf("\nEnter the the seat number: ");
      scanf("%d", &s);
      q = searchSeat(rs, p, s);
      
      if (q != -1)
      {
        int w, b;
        printf("\n Enter OTP: ");
        scanf("%d", &w);
        if (w == table[q].otp)
        {
          b = cancelSeat(rs, table, p, q);
          p = b;
          goto mainMenu;
        }
        else
        {  printf("Wrong OTP!");  goto mainMenu;  }
      }
      
      else
      {  
        printf("\nInvalid entry.\nThe seat is not reserved.");
        goto tryAgain;
      }
      break; 
  }
}

