//
//  main.c
//  elections
//
//  Created by TCHASSE ODJAC on 07.11.18.
//  Copyright © 2018 TCHASSE ODJAC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define N 10

/** STRUCTURES **/
typedef struct date{
    unsigned day;
    unsigned month;
    unsigned year;
}Date;

typedef struct party{
    char name[20];
    char chairman[20];
    int members;
    float votes;
    unsigned id;
    Date founded;
}Party;

/** GLOBAL VARIABLES **/
unsigned noOfParties = 0;
Party election[N] = {};

/** PROTOTYPES **/
Date inputDate(Date);
void addParty(Party);
void addPartyToElection(Party);
void printParty(Party);
void listParties(Party[]);
void deletePartyFromElection(Party[]);
int partyWithMostVotes(Party[]);
int findOldestParty(Party[]);
int compareStrings(char[], char[]);

/** MAIN **/
int main()
{
    Party party;
    int index = 0;
    int choose = 0;
    int i = 0;
    
    do{
        printf("\n\t\t\tELECTIONS 2017\n\n");
        
        printf("Choose the action you want to perform:\n");
        printf("(1) Input New Party\n");
        printf("(2) Show Parties in Election\n");
        printf("(3) Delete Party from Election\n");
        printf("(4) Find the Oldest Party\n");
        printf("(5) Find the Party with Most Votes\n");
        printf("(6) Exit the Program\n");
        printf("\n\nYour option: ");
        scanf("%i",&choose);
        getchar();
        printf("\n=======================================\n\n");
        
        switch(choose){
            case 1:
                addParty(party);
                break;
            case 2:
                listParties(election);
                break;
            case 3:
                deletePartyFromElection(election);
                break;
            case 4:
                index = findOldestParty(election);
                printParty(election[index]);
                break;
            case 5:
                index = partyWithMostVotes(election);
                printParty(election[index]);
                break;
            case 6:
                printf("Good-Bye!\n\n");
                break;
            default:
                printf("No valid input!");
        }
        
    }while(choose != 6);
    return 0;
}

/** INPUT STRING **/
void inputString(char text[20]){
    int i = -1;
    do{
        i++;
        text[i] = getchar();
    }while(text[i] != '\n' && i < 20);
    text[i] = '\0';
}

/** INPUT DATE **/
Date inputDate(Date date){
    printf("(day/month/year)\n");
    scanf("%i/%i/%i",&date.day, &date.month, &date.year);
    return date;
}

/** INPUT PARTY **/
void addParty(Party p){
    static int i = 1;
    printf("Name: ");
    //scanf("%s", p.name);
    inputString(p.name);
    //printf("%s", p.name);
    printf("Leader: ");
    //scanf("%s", p.chairman);
    inputString(p.chairman);
    //printf("%s", p.chairman);
    printf("Members: ");
    scanf("%i", &p.members);
    printf("Previous Votes: ");
    scanf("%f", &p.votes);
    printf("Founded ");
    p.founded = inputDate(p.founded);
    p.id = i;
    i++;
    printf("ID = %i", p.id);
    addPartyToElection(p);
    //printParty(p);
    //return p;
}

/** ADD PARTY TO ELECTION **/
void addPartyToElection(Party p){
    election[noOfParties] = p;
    noOfParties++;
    printf("\n%s has been added to the election!\n", p.name);
    printf("(%i parties currently in election)\n", noOfParties);
    printf("=====================================\n\n");
}

/** PRINT ONE PARTY **/
void printParty(Party p){
    if(p.members != -1){
        printf("\n*** %s ***\n", p.name);
        printf("Chairman: %s\n", p.chairman);
        printf("Members: %i\n", p.members);
        printf("Founded: %i/%i/%i\n", p.founded.day, p.founded.month, p.founded.year);
        printf("Votes at last election: %.2f %% \n", p.votes);
        printf("=====================================");
    }
}

/** PRINT ALL PARTIES**/
void listParties(Party election[]){
    printf("+++++ List of Parties up for Election +++++\n");
    int i;
    for(i = 0; i <= N; i++){
        if(election[i].id != 0){
            printParty(election[i]);
        }
    }
}

/** MOST VOTES **/
int partyWithMostVotes(Party election[]){
    int i;
    int max = 0;
    int index = 0;
    for(i = 0; i < N; i++){
        if(election[i].votes > max)
        {
            max = (election[i].votes);
            index = i;
        }
    }
    return index;
}

/** DELETE PARTY **/
void deletePartyFromElection(Party election[]){
    Party p;
    printf("Please input the name of the party you would like to delete: ");
    inputString(p.name);
    int res = 0;
    int i;
    for(i = 0; i < N; i++){
        if(election[i].id != 0){
            res = compareStrings(p.name, election[i].name);
            if(res == 1){
                election[i].id = 0;
                noOfParties--;
                printf("%s has been deleted from the election!\n\n", p.name);
            }
        }
    }
}

/** FIND OLDEST PARTY **/
int findOldestParty(Party election[]){
    int i = 0;
    Date maxDate= {};
    maxDate = election[i].founded;
    int found = 0;
    for(i = 0; i < N; i++){
        if(election[i].id != 0){
            if((maxDate.year > election[i].founded.year) ||
               ((maxDate.year == election[i].founded.year) && (maxDate.month > election[i].founded.month)) ||
               ((maxDate.year == election[i].founded.year) && (maxDate.month == election[i].founded.month) && (maxDate.day > election[i].founded.day))){
                maxDate = election[i].founded;
                found = i;
            }
        }
    }
    return found;
}

/** STRING COMPARE **/
int compareStrings(char a[], char b[]){
    int c = 0;
    while(a[c] == b[c]){
        if(a[c] == '\0' || b[c] == '\0')
            break;
        c++;
    }
    
    if (a[c] == '\0' && b[c] == '\0')
        return 1;
    else
        return -1;
}


