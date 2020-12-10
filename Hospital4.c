#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char GlobalFileName[30];

typedef struct S_Patient
{
  char name[20];
  int triageRank;
  char hospital[20];
  char nurse[20];
  char insuranceInfo[20];
  char doctorSeen[20];
  char diagnosis[20];
  float procedureCost;

  struct S_Patient *next;
} Patient; // Patient = struct S_Patient

int CountNodes(Patient *start) {
	Patient *currentPatient = start;
	int count = 0;
	while(currentPatient != NULL) {
		count++;
		currentPatient = currentPatient->next;
  }	
  //printf("Number of nodes: %d\n", count); 
  return count;
}

/*========================================================*
 * C O N V E N I E N C E  and L I S T   F U N C T I O N S 
 * Functions : showOptions(), CleanUp(), swap(), getTail(), getPrevious()
 * Purpose : Functionality that is used repeatedly at various points in the program;
 *           CleanUp clears the memory, swap() swaps two given nodes, etc.
 * 
 *  *========================================================*/

void showOptions()
{

  printf("\n\nPlease choose a number from the following options (10 to exit):\n\n");
  printf("1. ADD a patient entry\n"); 
  printf("2. LIST all entries\n"); 
  printf("3. BROWSE entries one at a time\n"); 
  printf("4. EDIT a patient entry\n");
  printf("5. DELETE a patient entry\n");
  printf("6. SAVE Database\n");
  printf("7. ORDER and display entries according to triage rankings\n");
  printf("8. SEARCH for a record by patient name\n");
  printf("9. TALLY up procedure earnings\n");
  printf("10.EXIT Program\n");
  
}

void CleanUp(Patient *start)
{
	
	Patient *freeMe = start;
	Patient *holdMe = NULL;	
	while(freeMe != NULL) {
		holdMe = freeMe->next;
		printf("Freeing... Name:%s Triage Ranking:%d\n",
			freeMe->name,
			freeMe->triageRank);
		free(freeMe);
		freeMe = holdMe;
	}	
}
/*Function to swap the nodes */
Patient* swap(Patient* ptr1, Patient* ptr2) 
{ 
    Patient* tmp = ptr2->next; //save the element after ptr2 because ptr two will be overwritten
    ptr2->next = ptr1; // set ptr next to ptr 1 (moving ptr1 before ptr2)
    ptr1->next = tmp; // set ptr1's (now second pointer) to be old ptr2's next; now all nexts point to the right elements and the list is maintatined
    return ptr2; //return ptr2 which now preceds ptr1
} 

Patient *getTail(Patient *start)
{
	Patient *lastPatient = start;
	int count = 0;
  while(lastPatient->next != NULL)
  {
    count++;

		lastPatient = lastPatient->next;
  }	
  return lastPatient;
}

Patient *getPrevious(Patient *start, Patient *target)
/* return the node before a given node */
{
  Patient *currentPatient = start;
  Patient *targetPatient = target;
	Patient *previousPatient = NULL;
	int count = 0;
  while(currentPatient != NULL) 
  {
    if(currentPatient == targetPatient) {
      /* puts("currentPatient equals the desired target in getPrev(), return target->previous\n"); */
      if(currentPatient == start)
      {
        /* puts("getting previous before start; returning NULL"); */
        return NULL;
      }
      break;
    } // if you're at the correct node -- (previous is same as input)
    count++;
    previousPatient = currentPatient;
    currentPatient = currentPatient->next;
  }	
  return previousPatient;
}

/*========================================================*
 * C R U D  and  D A T A  M A N I P U L A T I O N 
 * Functions : PrintList(), AddPatient(), Edit(), Delete(), BubbleSort(), Search(), Browse()
 * Purpose : Functionality used to create, read, update and delete contents of the program's list
 * 
 *  *========================================================*/

void PrintList(Patient *start) 
{
	Patient *currentPatient = start;
  int count = 0;

	puts("\n    PATIENT LIST\n    ------------");
	while(currentPatient != NULL) {
		count++;
		printf("\nPatient#: %d\nName: %s\nTriage Rank: %d\nHospital: %s\nNurse: %s\nInsurance Info: %s\nDoctor: %s\nDiagnosis: %s\nProcedure Cost: $%.2f\n----------------------\n",count,
    currentPatient->name,
    currentPatient->triageRank,
    currentPatient->hospital,
    currentPatient->nurse,
    currentPatient->insuranceInfo,
    currentPatient->doctorSeen,
    currentPatient->diagnosis,
    currentPatient->procedureCost);

		currentPatient = currentPatient->next;
	}	
  printf("Total Patients: %d\n",count);
  puts("\nPress Enter to show options");
  getchar();
}

Patient *AddPatient(Patient *previous) {

  Patient *newPatient = malloc(sizeof(Patient));
  int triageRangeGood = 0; // to make sure numeric input is valid

  printf("Enter Patient Details.\n ");

  // INPUT #1
	char nameInput[40];
  puts("Enter a name: ");
  fgets( nameInput, 39, stdin); 

  // INPUT #2
  puts("Enter a triage ranking between 1 and 5, inclusive: ");
  char triageInput[40];
  
  while(triageRangeGood == 0)
  {
    fgets( triageInput, 39, stdin);

    if(strcmp(triageInput, "1\n") == 0)
    {
      triageRangeGood = 1;
    } 
    else if (strcmp(triageInput, "2\n") == 0)
    {
      triageRangeGood = 1;
    }
    else if (strcmp(triageInput, "3\n") == 0)
    {
      triageRangeGood = 1;
    }
    else if (strcmp(triageInput, "4\n") == 0)
    {
      triageRangeGood = 1;
    }
    else if (strcmp(triageInput, "5\n") == 0)
    {
      triageRangeGood = 1;
    }
    else
    {
      puts("Try again! Not a valid number.");
    }
    
  }
  // INPUT #3
  char hospitalInput[40];
  puts("Enter a hospital: ");
  fgets( hospitalInput, 40, stdin); 
  printf("Hospital string: %s \n",hospitalInput);

  // INPUT #4
  char nurseInput[40];
  puts("Enter the admitting nurse: ");
  fgets( nurseInput, 39, stdin); 

  // INPUT #5
  char insuranceInput[40];
  puts("Enter the patient's insurance info: ");
  fgets( insuranceInput, 39, stdin); 

   // INPUT #6
   char doctorInput[40];
   puts("Enter the patient's doctor: ");
   fgets( doctorInput, 39, stdin); 
  
   // INPUT #7
   char diagnosisInput[40];
   puts("Enter patient diagnosis: ");
   fgets( diagnosisInput, 39, stdin); 

   // INPUT #8
   char costInput[20];
   puts("Enter patient procedure costs(without the dollar sign): ");
   fgets( costInput, 19, stdin);

  sscanf(nameInput, "%[^\t\n]", newPatient->name);
  sscanf(triageInput, "%d", &newPatient->triageRank);

  sscanf(hospitalInput, "%[^\t\n]", newPatient->hospital);
  sscanf(nurseInput, "%[^\t\n]", newPatient->nurse);
  sscanf(insuranceInput, "%[^\t\n]", newPatient->insuranceInfo);
  sscanf(doctorInput, "%[^\t\n]", newPatient->doctorSeen);
  sscanf(diagnosisInput, "%[^\t\n]", newPatient->diagnosis);
  sscanf(costInput, "%f", &newPatient->procedureCost);

  printf("\nADDED PATIENT: %s,  Triage Ranking: %d\n",newPatient->name,newPatient->triageRank);
  printf("Hospital: %s,  Admitting Nurse: %s\n",newPatient->hospital,newPatient->nurse);
  printf("Insurance Info: %s,  Doctor: %s\n",newPatient->insuranceInfo,newPatient->doctorSeen);
  printf("Diagnosis: %s,  Procedure Cost: $%.2f\n",newPatient->diagnosis,newPatient->procedureCost);
  
  newPatient->next = NULL;

	if(previous != NULL) {
		previous->next = newPatient;
	} 
	return newPatient;
}  
/* Function to sort the list */
void bubbleSort(Patient** start, int count) 
{ 
    Patient** h; 
    int i, j, swapped; 
  
    for (i = 0; i <= count; i++) // for as many nodes as are in the list 
    { 
  
        h = start; 
        swapped = 0; 
  
        for (j = 0; j < count - i - 1; j++) 
        { 
  
          Patient* p1 = *h; 
          Patient* p2 = p1->next; 
  
            if (p1->triageRank < p2->triageRank) 
            {  
                /* update the link after swapping */
                *h = swap(p1, p2); 
                swapped = 1; 
            } 
  
            h = &(*h)->next; 
        } 
  
        // break if the loop ended without any swap 
        if (swapped == 0) 
            break; 
    } 
    puts("\nSuccesfully sorted patients in order of severity of triage assessment!\n");
    puts("\nPress Enter to show options and then 2 to list results.");
    getchar();
} 

Patient *Edit(Patient *start) 
{
  printf("Enter the name of the patient to edit: ");
  char input[16];
  fgets(input, 15, stdin);

  Patient *patientCursor = start;
  Patient *patientPrevious = NULL;
  Patient *patientToEdit = NULL;

  while (patientCursor != NULL)
  {
    if(strncmp(input, patientCursor->name, strlen(patientCursor->name)) == 0)
    {
      patientToEdit = patientCursor; // now ready to edit
      break;
    }
    patientPrevious = patientCursor; // this isn't a doubly linked list so I need a connection to previous
    patientCursor = patientCursor->next; // loop through the whole list
  }
  //variable input
  int triageRangeGood = 0; // to make sure numeric input is valid

  printf("Enter Patient Details.\n ");

  // INPUT #1
	char nameInput[40];
  puts("Enter a name: ");
  fgets( nameInput, 39, stdin); 

  // INPUT #2
  puts("Enter a triage ranking between 1 and 5, inclusive: ");
  char triageInput[40];
  
  while(triageRangeGood == 0)
  {
    fgets( triageInput, 39, stdin);

    if(strcmp(triageInput, "1\n") == 0)
    {
      triageRangeGood = 1;
    } 
    else if (strcmp(triageInput, "2\n") == 0)
    {
      triageRangeGood = 1;
    }
    else if (strcmp(triageInput, "3\n") == 0)
    {
      triageRangeGood = 1;
    }
    else if (strcmp(triageInput, "4\n") == 0)
    {
      triageRangeGood = 1;
    }
    else if (strcmp(triageInput, "5\n") == 0)
    {
      triageRangeGood = 1;
    }
    else
    {
      puts("Try again! Not a valid number.");
    }
    
  }
  // INPUT #3
  char hospitalInput[40];
  puts("Enter a hospital: ");
  fgets( hospitalInput, 40, stdin); 
  printf("Hospital string: %s \n",hospitalInput);

  // INPUT #4
  char nurseInput[40];
  puts("Enter the admitting nurse: ");
  fgets( nurseInput, 39, stdin); 

  // INPUT #5
  char insuranceInput[40];
  puts("Enter the patient's insurance info: ");
  fgets( insuranceInput, 39, stdin); 

   // INPUT #6
   char doctorInput[40];
   puts("Enter the patient's doctor: ");
   fgets( doctorInput, 39, stdin); 
  
   // INPUT #7
   char diagnosisInput[40];
   puts("Enter patient diagnosis: ");
   fgets( diagnosisInput, 39, stdin); 

   // INPUT #8
   char costInput[20];
   puts("Enter patient procedure costs(without the dollar sign): ");
   fgets( costInput, 19, stdin);

  sscanf(nameInput, "%[^\t\n]", patientToEdit->name);
  sscanf(triageInput, "%d", &patientToEdit->triageRank);

  sscanf(hospitalInput, "%[^\t\n]", patientToEdit->hospital);
  sscanf(nurseInput, "%[^\t\n]", patientToEdit->nurse);
  sscanf(insuranceInput, "%[^\t\n]", patientToEdit->insuranceInfo);
  sscanf(doctorInput, "%[^\t\n]", patientToEdit->doctorSeen);
  sscanf(diagnosisInput, "%[^\t\n]", patientToEdit->diagnosis);
  sscanf(costInput, "%f", &patientToEdit->procedureCost);

  printf("\nEDITED PATIENT: %s,  Triage Ranking: %d\n",patientToEdit->name,patientToEdit->triageRank);
  printf("Hospital: %s,  Admitting Nurse: %s\n",patientToEdit->hospital,patientToEdit->nurse);
  printf("Insurance Info: %s,  Doctor: %s\n",patientToEdit->insuranceInfo,patientToEdit->doctorSeen);
  printf("Diagnosis: %s,  Procedure Cost: $%.2f\n",patientToEdit->diagnosis,patientToEdit->procedureCost);

  return start;
}

Patient *Delete(Patient *start) 
{
  printf("Enter the name of the patient to delete: ");
  char input[16];
  fgets(input, 15, stdin);

  Patient *patientCursor = start;
  Patient *patientPrevious = NULL;
  Patient *patientToDelete = NULL;

  while (patientCursor != NULL)
  {
    if(strncmp(input, patientCursor->name, strlen(patientCursor->name)) == 0)
    {
      patientToDelete = patientCursor;
      break;
    }
    patientPrevious = patientCursor; // this isn't a doubly linked list so I need a reference to previous
    patientCursor = patientCursor->next; // loop through the whole list
  }

  // REMOVING NODE
  if(start != NULL && patientToDelete == start) //case 1: delete the head
  {
      if(patientToDelete->next != NULL) // the head has a next element (at least two nodes in the list)
      {
        //printf("\n\nHead should be deleted 1 \n");
        start = patientToDelete->next;
      }
      else // i.e. if there is only one element in the list
      {
        //printf("\n\nHead should be deleted 2 \n");
        start = NULL;
      }     
  }
  else
  {
    if(patientToDelete != NULL)
    {
      patientPrevious->next = patientToDelete->next;
      patientToDelete->next = patientPrevious;
    }
  }
  return start;
}

void Search(Patient *start) 
{
  printf("Enter the name of the patient you want to view: ");
  char input[16];
  fgets(input, 15, stdin);

  Patient *patientCursor = start;
  Patient *patientPrevious = NULL;
  Patient *patientToView = NULL;

  while (patientCursor != NULL)
  {
    if(strncmp(input, patientCursor->name, strlen(patientCursor->name)) == 0)
    {
      patientToView = patientCursor; // now ready to edit
      break;
    }
    patientPrevious = patientCursor; // this isn't a doubly linked list so I need a connection to previous
    patientCursor = patientCursor->next; // loop through the whole list
  }
  printf("\n    PATIENT   ");
  printf("\nName: %s\nTriage Rank: %d\nHospital: %s\nNurse: %s\nInsurance Info: %s\nDoctor: %s\nDiagnosis: %s\nProcedure Cost: $%.2f\n----------------------\n",
  patientToView->name,
  patientToView->triageRank,
  patientToView->hospital,
  patientToView->nurse,
  patientToView->insuranceInfo,
  patientToView->doctorSeen,
  patientToView->diagnosis,
  patientToView->procedureCost);

  puts("\nPress Enter to show options");
  getchar();

}

Patient *Browse(Patient *start) // returns patient start pointer in case they decide to edit
{
  //command input vars
  char command[16];
  char input[16];
  int count = 0;

  int NodeCount = CountNodes(start);
  printf("\nYou have %d patient records to browse.\n", NodeCount);

  Patient *currentPatient = start;
  Patient *previous = NULL;
  Patient *previousPrevious = NULL;

  printf("\nBrowse entries from the start of the database.\nKey Commands:\n'n' = next record,\n'p' = previous,\n'q' = quit browser\n");
  while( fgets( input, 15, stdin) ) 
  {
    
    sscanf(input,"%s",command);	
    
    if ( strncmp(command, "q", 1) == 0) 
    // fetch and display next record
    {
			printf("\nQuitting browser, returning to main()...\n\n");
			break;		
    }
    else if ( strncmp(command, "n", 1) == 0) // this should never create a state that 'p' can't handle... 
    {
      if(currentPatient != NULL) { // Resulting state: CURRENT = start->next+n; PREVIOUS = start+n
        count++;

        printf("\nPatient#: %d\nName: %s\nTriage Rank: %d\nHospital: %s\nNurse: %s\nInsurance Info: %s\nDoctor: %s\nDiagnosis: %s\nProcedure Cost: $%.2f\n----------------------\n",count,
        currentPatient->name,
        currentPatient->triageRank,
        currentPatient->hospital,
        currentPatient->nurse,
        currentPatient->insuranceInfo,
        currentPatient->doctorSeen,
        currentPatient->diagnosis,
        currentPatient->procedureCost);
        printf("'n' = next record,'p' = previous,'q' = quit browser\n");

        previous = currentPatient;
        previousPrevious = getPrevious(start, previous); 
        currentPatient = currentPatient->next;
      }	
      else // Resulting state: CURRENT = start->next; PREVIOUS = start
      {
        count = 1;

        printf("\nPatient#: %d\nName: %s\nTriage Rank: %d\nHospital: %s\nNurse: %s\nInsurance Info: %s\nDoctor: %s\nDiagnosis: %s\nProcedure Cost: $%.2f\n----------------------\n",count,
        start->name,
        start->triageRank,
        start->hospital,
        start->nurse,
        start->insuranceInfo,
        start->doctorSeen,
        start->diagnosis,
        start->procedureCost);
        printf("'n' = next record,'p' = previous,'q' = quit browser\n");

        currentPatient = start->next; 
        previous = start;
        previousPrevious = NULL;
      }
      
    }
    else if ( strncmp(command, "p", 1) == 0) 
    {

      if(previousPrevious != NULL) {

        count--;
        if(count < 1) count = NodeCount;

        printf("\nPatient#: %d\nName: %s\nTriage Rank: %d\nHospital: %s\nNurse: %s\nInsurance Info: %s\nDoctor: %s\nDiagnosis: %s\nProcedure Cost: $%.2f\n----------------------\n",count,
        previousPrevious->name,
        previousPrevious->triageRank,
        previousPrevious->hospital,
        previousPrevious->nurse,
        previousPrevious->insuranceInfo,
        previousPrevious->doctorSeen,
        previousPrevious->diagnosis,
        previousPrevious->procedureCost);
        printf("'n' = next record,'p' = previous,'q' = quit browser\n");

        currentPatient = previous;
        previous = getPrevious(start, currentPatient);
        previousPrevious = getPrevious(start, previous);

      }	
      else
      {

        //previous is null so set current to Tail
        currentPatient = getTail(start); //tail needs a record of the previous node // getPrevious() function?

        previous = getPrevious(start, currentPatient);

        count = NodeCount; // set number to maximum

        printf("\nPatient#: %d\nName: %s\nTriage Rank: %d\nHospital: %s\nNurse: %s\nInsurance Info: %s\nDoctor: %s\nDiagnosis: %s\nProcedure Cost: $%.2f\n----------------------\n",count,
        currentPatient->name,
        currentPatient->triageRank,
        currentPatient->hospital,
        currentPatient->nurse,
        currentPatient->insuranceInfo,
        currentPatient->doctorSeen,
        currentPatient->diagnosis,
        currentPatient->procedureCost);
        printf("'n' = next record,'p' = previous,'q' = quit browser\n");
        
        currentPatient = start; 

        previous = getTail(start);

        previousPrevious = getPrevious(start, previous);

      }
    }
    else if ( strncmp(command, "e", 1) == 0) 
    {
      //TODO: this unfortunaley can't be easily 
      puts("Editing...");
    }
    else {
      puts("That's not a valid browser command!");
    }

  }

  return start;
}

/*========================================================*
 * F I L E   I / O
 * Functions : SaveListToFile(), LoadNextFromFile(), LoadList()
 * Purpose : Reads list list data into a file for external saving OR 
 *           reads data from a file into the program's list.
 *           LoadList makes use of LoadNextFromFile()
 * 
 *  *========================================================*/

void SaveListToFile(Patient *start)
{
  FILE *fp;

  printf("Enter the name of the file you want to save to.\n If you just want to save to the file you loaded the program from, press 's' to skip this step: ");
  char input[30];
  fgets(input, 29, stdin);
  strtok(input, "\n");

  if(strcmp(input, "s") == 0)
  {
    if(strcmp(GlobalFileName, "n") == 0)
    //if the user didn't enter a name for the file at program outset
    {
      strcpy(GlobalFileName, "defaultPatients.txt");
    }
    printf("Load filename: %s", GlobalFileName);
    fp = fopen(GlobalFileName, "wb");
  }
  else
  {
    fp = fopen(input, "wb");
  }

  if(fp != NULL)
  {
    Patient *patientCursor = start;
    Patient *holdNext = NULL;

    while(patientCursor != NULL)
    {
      // the only purpose of holdNext is to not write the next value to the file; in the file the next field should be null
      holdNext = patientCursor->next;

      patientCursor->next = NULL;

      fseek(fp, 0, SEEK_END); //point file pointer to end of file
      fwrite(patientCursor, sizeof(Patient), 1, fp);
      
      printf("Saving patient %s to file\n", patientCursor->name);
      
      patientCursor->next = holdNext;

      holdNext = NULL;

      patientCursor = patientCursor->next;
    }
    fclose(fp);
    fp = NULL;
  }
  else
  {
    printf("FILE OPEN ERROR\n");
  }
  
}

Patient *LoadNextFromFile(Patient *start, FILE *fp)
{
  size_t returnValue; //size_t is a type that accuarately stores a number of bytes
  if(start == NULL) // if the list is empty
  {
    start = malloc(sizeof(Patient)); 
    returnValue = fread(start, sizeof(Patient), 1, fp); //read one patient from fp into start(the linked list)
    start->next = NULL;
  }
  else { //if list already has nodes, go to the end of the list and add the new patient to the end of the list
    Patient *cursorPatient = start;
    Patient *newPatient = malloc(sizeof(Patient));
    
    while(cursorPatient->next != NULL) {
      cursorPatient = cursorPatient->next;
    }
    returnValue = fread(newPatient, sizeof(Patient), 1, fp);
    cursorPatient->next = newPatient;
    newPatient->next = NULL;
}
return start;
}

Patient *LoadList(Patient *start)
{
  FILE *fp;
  printf("\nEnter the name of the file you want to load.\n(press 'n' to start fresh and save list as a new file later.): ");
 
  fgets(GlobalFileName, 29, stdin);

  strtok(GlobalFileName, "\n");//remove newline character from fgets
  //in case they don't want to load a file
  if(strcmp(GlobalFileName, "n") == 0)
  {
    return NULL;
  }
  else
  {
    fp = fopen(GlobalFileName, "rb");
  }

  if(fp != NULL)
  {

    CleanUp(start);
    start = NULL;

    fseek(fp, 0, SEEK_END); //set file pointer at the end of the file
    long fileSize = ftell(fp);// get file size with ftell
    rewind(fp);//move file pointer back to beginning of file

    int numEntries = (int)(fileSize / (sizeof(Patient))); //number of entries is fileSize / the byte size of a single Pztient struct
    printf("number of entries: %d\n", numEntries); 

    int loop = 0;
    for(loop = 0; loop < numEntries; ++loop) //while 'loop' is less than number of entries
    {
     // set the file position to be an offset equal to patient struct size * current 'loop' int 
     fseek(fp, (sizeof(Patient) * loop), SEEK_SET);
     start = LoadNextFromFile(start, fp); //call function that will ad the node to the master start pointer/ linked list
    }

  } else
  {
    printf("FILE OPEN ERROR FOR READ\n");
  }

  fclose(fp);

  return start;

}

float Tally(Patient *start) //Tally total cost
{
  Patient *currentPatient = start;
  int count = 0;
  float tally = 0;
	while(currentPatient != NULL) {
    count++;
    tally += currentPatient->procedureCost;
		printf("\nPatient#: %d\nName: %s\nProcedure Cost: $%.2f\n-------------------\n",count,
    currentPatient->name,
    currentPatient->procedureCost);
		currentPatient = currentPatient->next;
	}	
  printf("\nTotal Earnings from procedures: $%.2f\n",tally);
  puts("\nPress Enter to show options");
  getchar();
  return tally; // not actually using this return value but it makes sense to return the result 
}

// M A I N // 

int main() {	
  /* File pointer to refer to chosen input/output file or newly created file. 
  * A function will prompt the user to choose a file and return a pointer to said file
  */
  FILE *fp; 

	char command[16];
  char input[16];	
  int didLoad = 0;
	
	Patient *start = NULL;
  Patient *newest = NULL;
  
  // some instructions
  printf("\nINSTRUCTIONS:\n");  
  printf("\nIf you choose to start with new data, make sure you save the data to a file before quitting.\n");
  printf("\nIf you select 'Save' and press enter without providing a filename, your data will be saved to 'defaultPatients.txt'.\n");
  printf("\nYou may think of 'defaultPatients.txt' as the default data store unless other input is given.\n");
  
  start = LoadList(start); 
  
  if(start != NULL)
  {
    puts("\n\nDid load data from file\n");
    didLoad = 1; //loaded program from a data file
  }
 
  showOptions();
	
	while( fgets( input, 15, stdin) ) {
    
		sscanf(input,"%s",command);	
		
		if ( strncmp(command, "10", 2) == 0) {
			printf("\n\nCleaning up and quitting...\n\n");
			break;		
    }
    else if ( strncmp(command, "2", 1) == 0) 
    {
			PrintList(start);
    }
    else if ( strncmp(command, "3", 1) == 0) 
    {
			start = Browse(start);
    }
    else if ( strncmp(command, "4", 1) == 0) 
    {
			start = Edit(start); 
    }
    else if ( strncmp(command, "5", 1) == 0) 
    {
      start = Delete(start);
    }
    else if ( strncmp(command, "6", 1) == 0) 
    {
      SaveListToFile(start);
    }
    else if ( strncmp(command, "7", 1) == 0) 
    {
      int numOfNodesToSort = CountNodes(start);
      bubbleSort(&start,numOfNodesToSort);
    }
    else if ( strncmp(command, "8", 1) == 0) 
    {
			Search(start);
    }
    else if ( strncmp(command, "9", 1) == 0) 
    {
			Tally(start);
    }
    else if ( strncmp(command, "1", 1) == 0) 
    {
			if(start == NULL) {
				start = AddPatient(NULL);
				newest = start;
			} else {
        //needs adapting if file is loaded
        if(didLoad == 1){  
          puts("\n\nData was loaded, recalculate newest\n\n");      
          newest = start;
          newest = getTail(newest); //make newest the latest/last element
        }
        //if file is loaded, newest isn't being updated to be the last node
        newest = getTail(newest); //make newest the latest/last element
				newest = AddPatient(newest); // doesn't work if a file is loaded and didLoad isn't tested
			} 
    }
    showOptions();
	}
	
	CleanUp(start);
	
	return 0;

}


