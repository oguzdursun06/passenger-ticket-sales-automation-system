#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {    //Storing operations related to flights
   char *flightName;
   int isOpen;
   struct Queue *businessClass;
   struct Queue *economyClass;
   struct Queue *standardClass;
   struct Stack *businessSeat;
   struct Stack *economySeat;
   struct Stack *standardSeat;
   char **reportBusiness,**reportEconomy,**reportStandard;
   int businessSeats,economySeats,standardSeats;
   int soldBusinessSeats,soldEconomySeats,soldStandardSeats;
} Flight;

typedef struct{      //For the info function we need to keep people's data.
	char *passengerName;
	char *flightName;
	char *wantedSeatClass;
	char *soldSeatClass;
} Person;

struct Queue{
	char *passengerName;
	int diplomaticPriority;
	struct Queue *next;
};

struct Stack{
	char *passengerName;
	struct Stack *next;
};

struct Stack *push(struct Stack *top,char *passengerName){    //We use it when adding to the seats
	struct Stack *ptr;     //temporary Stack
	ptr = (struct Stack*) malloc(sizeof(struct Stack));      //We allocate as much memory as Stack size
	ptr->passengerName = passengerName;
	if(top == NULL){       //Stack is empty?
		ptr->next = NULL;
		top = ptr;
	}
	else{
		ptr->next = top;
		top = ptr;
	}
	return top;  //return Stack
}
struct Stack *del(struct Stack *top){      //We use it when reduce to seat numbers.
	struct Stack *ptr;
	ptr = top;
if(top == NULL)       //Is empty??
	printf("\n STACK UNDERFLOW");
else
	{
		top = top -> next;
		free(ptr);     //We free the extracted stack structure for memory check.
}
	return top;
}

int stackSize(struct Stack *top){      //Return stack length!!
	struct Stack *ptr;
	ptr = top;

	int count = 0;
	if(top == NULL)      //Is empty?
		return 0;
	else{
		while(ptr != NULL){     //Hindsight in from stack
			count++;
			ptr = ptr->next;
		}
	}
	return count; 
}
struct Queue *insert(struct Queue *start,char *passengerName,int priority){    //We use it when adding to the queue
	struct Queue *ptr, *p;  //temporary 
	ptr = (struct Queue *) malloc(sizeof(struct Queue));  //Allocate memory as much as Queue size.
	ptr->passengerName = passengerName;
	ptr->diplomaticPriority = priority;   //For priority queue
	if(start == NULL){ 
		ptr->next = start;
		start = ptr;
	}
	else if(priority < start->diplomaticPriority){    //Check priority
		ptr->next = start; 
		start = ptr;
}
	else{
		p = start;
		while(p->next != NULL && p->next->diplomaticPriority <= priority)
			p = p->next;
		ptr->next = p->next;
		p->next = ptr;
}
	
	return start;
}	

void display(struct Queue *start,FILE *outputFile){
	struct Queue *ptr;
	ptr = start;
	if(start == NULL){
		printf("\nQUEUE ÝS EMPTY");
	}
	else{
		while(ptr != NULL){
			fprintf(outputFile,"waiting %s\n",ptr->passengerName); //For report function 
			ptr = ptr->next;
			
			}
	}
}
int queueSize(struct Queue *start){      //Return queue length
	struct Queue *ptr;
	ptr = start;
	int length = 0;
	if(start == NULL){
		return 0;
	}
	else{
		while(ptr != NULL){
			ptr = ptr->next;
			length++;
			}
		return length;
	}
}

//Functions to extend struct(Flight,Person) structures
Flight * reSizeFlight(Flight *flightRepository, int count){
	return realloc(flightRepository, (count + 1) * sizeof(Flight));
}
Person * reSizePerson(Person *personRepository, int count){
	return realloc(personRepository, (count + 1) * sizeof(Person));
}

int isExistFlight(Flight *flightRepository, char* commandLine,int count){   
		char * firstFound = strstr(commandLine, " " );
		char * secondFound = strstr(firstFound+1, " " );
		char * thirdFound = strstr(secondFound+1, " ");
		char *firstParameter = strtok(firstFound," ");
		char *secondParameter = strtok(secondFound+1," ");
		char *thirdParameter = strtok(thirdFound+1," \n\r");
		int search = searchIndex(flightRepository,firstParameter,count);
		return search;
}

int addSeat(Flight *flightRepository, char* commandLine,int count,FILE *outputFile,int search){      
		char * firstFound = strstr(commandLine, " " );
		char * secondFound = strstr(firstFound+1, " " );
		char * thirdFound = strstr(secondFound+1, " ");
		char *firstParameter = strtok(firstFound," ");
		char *secondParameter = strtok(secondFound+1," ");	
		char *thirdParameter = strtok(thirdFound+1," \n\r");
		if(search == -1){    //The first time such a flight is created
			(flightRepository+count)->flightName = firstParameter;
			(flightRepository+count)->isOpen = 1;     //Flight is open
			(flightRepository+count)->businessClass = NULL;
			(flightRepository+count)->economyClass = NULL;   //EMPTY
			(flightRepository+count)->standardClass = NULL;
			(flightRepository+count)->businessSeat = NULL;
			(flightRepository+count)->economySeat = NULL;
			(flightRepository+count)->standardSeat = NULL;
			(flightRepository+count)->reportBusiness = (char **) malloc(1*sizeof(char *));         
			(flightRepository+count)->reportEconomy = (char  **) malloc(1*sizeof(char *));
			(flightRepository+count)->reportStandard = (char **) malloc(1*sizeof(char *));
			(flightRepository+count)->soldBusinessSeats = 0; (flightRepository+count)->soldEconomySeats = 0; (flightRepository+count)->soldStandardSeats = 0;
			int i;
			if(strcmp(secondParameter,"business") == 0){
				(flightRepository+count)->businessSeats = atoi(thirdParameter);
				for(i = 0; i < atoi(thirdParameter);i++){
					(flightRepository+count)->businessSeat = push((flightRepository+count)->businessSeat,(flightRepository+count)->flightName);  //Add business seats
				}
				(flightRepository+count)->economySeats = 0;
				(flightRepository+count)->standardSeats = 0;
			}
			else if(strcmp(secondParameter,"economy") == 0){
				(flightRepository+count)->businessSeats = 0;
				(flightRepository+count)->economySeats = atoi(thirdParameter);
				for(i = 0; i < atoi(thirdParameter);i++){
					(flightRepository+count)->economySeat = push((flightRepository+count)->economySeat,(flightRepository+count)->flightName);  //Add business seats
				}
				(flightRepository+count)->standardSeats = 0;
			}
			else if(strcmp(secondParameter,"standard") == 0){
				(flightRepository+count)->businessSeats = 0;
				(flightRepository+count)->economySeats = 0;
				(flightRepository+count)->standardSeats = atoi(thirdParameter);
				for(i = 0; i < atoi(thirdParameter);i++){
					(flightRepository+count)->standardSeat = push((flightRepository+count)->standardSeat,(flightRepository+count)->flightName); //Add standard seats
				}
			}
			else{
				fprintf(outputFile,"error\n");
				return count;
			}
			fprintf(outputFile,"addseats %s %d %d %d\n",(flightRepository+count)->flightName,stackSize((flightRepository+count)->businessSeat),stackSize((flightRepository+count)->economySeat),stackSize((flightRepository+count)->standardSeat));
			return count+1;
	}
		else{
			if((flightRepository+search)->isOpen != 1)
				fprintf(outputFile,"error\n");
			
			else{
			int i;
			if(strcmp(secondParameter,"business") == 0){
				(flightRepository+search)->businessSeats += atoi(thirdParameter);
				for(i = 0; i < atoi(thirdParameter);i++){
					(flightRepository+search)->businessSeat = push((flightRepository+search)->businessSeat,(flightRepository+search)->flightName);
				}
		}
			else if(strcmp(secondParameter,"economy") == 0)
				{
				(flightRepository+search)->economySeats += atoi(thirdParameter);
				for(i = 0; i < atoi(thirdParameter);i++){
					(flightRepository+search)->economySeat = push((flightRepository+search)->economySeat,(flightRepository+search)->flightName);
				}
		}
			else if(strcmp(secondParameter,"standard") == 0)
				{
				(flightRepository+search)->standardSeats += atoi(thirdParameter);
				for(i = 0; i < atoi(thirdParameter);i++){
					(flightRepository+search)->standardSeat = push((flightRepository+search)->standardSeat,(flightRepository+search)->flightName);
				}
		}
			else{
				fprintf(outputFile,"error\n");
				return count;
			}
			fprintf(outputFile,"addseats %s %d %d %d\n",(flightRepository+search)->flightName,stackSize((flightRepository+search)->businessSeat),stackSize((flightRepository+search)->economySeat),stackSize((flightRepository+search)->standardSeat));
			return count;
		}
		}
		
}

int enqueue(Flight *flightRepository,int count,char* flightName,char* commandLine,FILE *outputFile,Person *personRepository,int personCount){ 
	*(commandLine+strlen(commandLine)) = ' ';
	int parameterCount = 1;
	parameterCount += findSpaceNumber(commandLine);   
	if(parameterCount != 2 && parameterCount != 3){      
		fprintf(outputFile,"error\n");
		return personCount;
	}
	else{
		
		if(parameterCount == 2){       //non-priority transactions
			char * firstFound = strstr(commandLine, " " );
			char * firstParameter = strtok(commandLine," ");
			char * secondParameter = strtok(firstFound+1," \n\r");
			int search = searchIndex(flightRepository,flightName,count);
			if(search == -1){     
				fprintf(outputFile,"error\n");
				return personCount;
			}
			else{
				if((flightRepository+search)->isOpen != 1){
				fprintf(outputFile,"error\n");
				return personCount;
				}
				else{
				if(strcmp(firstParameter,"business") == 0){
					(flightRepository+search)->businessClass = insert((flightRepository+search)->businessClass,secondParameter,2);
					(personRepository+personCount)->passengerName = secondParameter;
					(personRepository+personCount)->flightName = flightName;
					(personRepository+personCount)->wantedSeatClass = "business";
					fprintf(outputFile,"queue %s %s %s %d\n",flightName,secondParameter,firstParameter,queueSize((flightRepository+search)->businessClass));
					return personCount+1;
				}	
				else if(strcmp(firstParameter,"economy") == 0){
					(flightRepository+search)->economyClass = insert((flightRepository+search)->economyClass,secondParameter,2);
					(personRepository+personCount)->passengerName = secondParameter;
					(personRepository+personCount)->flightName = flightName;
					(personRepository+personCount)->wantedSeatClass = "economy";
					fprintf(outputFile,"queue %s %s %s %d\n",flightName,secondParameter,firstParameter,queueSize((flightRepository+search)->economyClass));
			 		return personCount+1;
				 }
			 	else if(strcmp(firstParameter,"standard") == 0){
					(flightRepository+search)->standardClass = insert((flightRepository+search)->standardClass,secondParameter,2);
					(personRepository+personCount)->passengerName = secondParameter;
					(personRepository+personCount)->flightName = flightName;
					(personRepository+personCount)->wantedSeatClass = "standard";
					fprintf(outputFile,"queue %s %s %s %d\n",flightName,secondParameter,firstParameter,queueSize((flightRepository+search)->standardClass));
					return personCount+1;
				}
				else{
					fprintf(outputFile,"error\n");
					return personCount;
					}			
			}
				}
		}
		if(parameterCount == 3){
			char *firstFound = strstr(commandLine, " " );
			char *secondFound = strstr(firstFound+1, " " );
			char *firstParameter = strtok(commandLine," ");
			char *secondParameter = strtok(firstFound+1," ");
			char *thirdParameter = strtok(secondFound+1," \n\r");    
			int search = searchIndex(flightRepository,flightName,count);
			if(search == -1){
				fprintf(outputFile,"error\n");
				return personCount;
			}
			else{
				if((flightRepository+search)->isOpen != 1){
				fprintf(outputFile,"error\n");
				return personCount;
				}
				else{
				
				if(strcmp(firstParameter,"business") == 0){
					if(strcmp(thirdParameter,"diplomat") == 0){
						(flightRepository+search)->businessClass = insert((flightRepository+search)->businessClass,secondParameter,1);
						(personRepository+personCount)->passengerName = secondParameter;
						(personRepository+personCount)->flightName = flightName;
						(personRepository+personCount)->wantedSeatClass = "business";
						fprintf(outputFile,"queue %s %s %s %d\n",flightName,secondParameter,firstParameter,queueSize((flightRepository+search)->businessClass));
						return personCount+1;
					}
					else{
						fprintf(outputFile,"error\n");
						return personCount;
						}
				}
				else if(strcmp(firstParameter,"economy") == 0){
					if(strcmp(thirdParameter,"veteran") == 0){
						(flightRepository+search)->economyClass = insert((flightRepository+search)->economyClass,secondParameter,1);
						(personRepository+personCount)->passengerName = secondParameter;
						(personRepository+personCount)->flightName = flightName;
						(personRepository+personCount)->wantedSeatClass = "economy";
						fprintf(outputFile,"queue %s %s %s %d\n",flightName,secondParameter,firstParameter,queueSize((flightRepository+search)->economyClass));
						return personCount+1;
					}
					else{
						fprintf(outputFile,"error\n");
						return personCount;
						}		 
 }
				
				else{
					fprintf(outputFile,"error\n");
					return personCount;
				}
		}
			 }
		}
		
	}
	return count;
}

int closeFlight(Flight *flightRepository,int count,char* commandLine,FILE *outputFile){
	char * firstFound = strstr(commandLine, " " );
	char * secondFound = strtok(firstFound+1," \n\r");
	int search = searchIndex(flightRepository,secondFound,count);
	if(search == -1 || (flightRepository+search)->isOpen == 0){   //If there is no such flight or if it is closed
		fprintf(outputFile,"error\n");
	}
	else{
	(flightRepository+search)->isOpen = 0;
	int total = ((flightRepository+search)->soldBusinessSeats+(flightRepository+search)->soldEconomySeats+(flightRepository+search)->soldStandardSeats);
	int waiting = (queueSize((flightRepository+search)->businessClass)+queueSize((flightRepository+search)->economyClass)+queueSize((flightRepository+search)->standardClass));
	fprintf(outputFile,"closed %s %d %d\n",secondFound,total,waiting);
		//Show people in queue
		if(queueSize((flightRepository+search)->businessClass) != 0)
			display((flightRepository+search)->businessClass,outputFile);       
		if(queueSize((flightRepository+search)->economyClass) != 0)
			display((flightRepository+search)->economyClass,outputFile);
		if(queueSize((flightRepository+search)->standardClass) != 0)
			display((flightRepository+search)->standardClass,outputFile);
	}
	return count;
}

int report(Flight *flightRepository,int count,char* commandLine,FILE *outputFile){
	char * firstFound = strstr(commandLine, " " );
	char * secondFound = strtok(firstFound+1," \n\r");
	int search = searchIndex(flightRepository,secondFound,count);
	int i;
	int parameterCount = 1;
	parameterCount += findSpaceNumber(commandLine);
	if(search == -1 || parameterCount != 2){
		fprintf(outputFile,"error\n");
	}
	else{
	
	fprintf(outputFile,"report %s\n",secondFound);
	fprintf(outputFile,"business %d\n",(flightRepository+search)->soldBusinessSeats);
	for(i = 0; i< (flightRepository+search)->soldBusinessSeats;i++){
		fprintf(outputFile,"%s\n",(flightRepository+search)->reportBusiness[i]);
	}
	fprintf(outputFile,"economy %d\n",(flightRepository+search)->soldEconomySeats);
	for(i = 0; i< (flightRepository+search)->soldEconomySeats;i++){
		fprintf(outputFile,"%s\n",(flightRepository+search)->reportEconomy[i]);
	}
	fprintf(outputFile,"standard %d\n",(flightRepository+search)->soldStandardSeats);
	for(i = 0; i< (flightRepository+search)->soldStandardSeats;i++){
		fprintf(outputFile,"%s\n",(flightRepository+search)->reportStandard[i]);
	}
	fprintf(outputFile,"end of report %s\n",secondFound);
}
	return count;
		
}
char *takePassengerName(struct Queue *start){       //For report function -- Send to a report arrays
	struct Queue *ptr;
	ptr = start;
	start = start->next;
	return ptr->passengerName;
}
struct Queue *pop(struct Queue *start){    // We have to get it out of the queue for the sellticket.
	struct Queue *ptr;
	if(start == NULL){      //Is empty??
		printf("UNDERFLOW\n");
	}
	else{
		ptr = start;
		start = start->next;
		free(ptr);
	}
	return start;
}


int sellTicket(Flight *flightRepository,int count,char* commandLine,FILE *outputFile,Person *personRepository, int personCount){   
	char * firstFound = strstr(commandLine, " " );
	char * secondFound = strtok(firstFound+1," \n\r");
	char *temp;
	int personNo;
	int search = searchIndex(flightRepository,secondFound,count);
	if(search == -1 || (flightRepository+search)->isOpen != 1){
				fprintf(outputFile,"error\n");
				return count;
			}
	else{			
	//First business class
	for((flightRepository+search)->businessSeats; (flightRepository+search)->businessSeats != 0 && (flightRepository+search)->businessClass != NULL ; (flightRepository+search)->businessSeats--){
		temp = takePassengerName((flightRepository+search)->businessClass);
		personNo = searchPerson(personRepository,temp,personCount); //Search in person repository.
		(personRepository+personNo)->soldSeatClass = "business";   //For info function
		(flightRepository+search)->soldBusinessSeats++;
		(flightRepository+search)->reportBusiness = realloc((flightRepository+search)->reportBusiness,(flightRepository+search)->soldBusinessSeats*sizeof(char *));
		(flightRepository+search)->reportBusiness[(flightRepository+search)->soldBusinessSeats-1] = temp;
		(flightRepository+search)->businessClass = pop((flightRepository+search)->businessClass);
		
	}
	//Second economy class
	for((flightRepository+search)->economySeats; (flightRepository+search)->economySeats != 0 && (flightRepository+search)->economyClass != NULL; (flightRepository+search)->economySeats--){
		temp = takePassengerName((flightRepository+search)->economyClass);  //For report arrays
		personNo = searchPerson(personRepository,temp,personCount);   //Search in person repository.
		(personRepository+personNo)->soldSeatClass = "economy";   //For info function
		(flightRepository+search)->soldEconomySeats++;
		(flightRepository+search)->reportEconomy = realloc((flightRepository+search)->reportEconomy,(flightRepository+search)->soldEconomySeats*sizeof(char *));
		(flightRepository+search)->reportEconomy[(flightRepository+search)->soldEconomySeats-1] = temp;
		(flightRepository+search)->economyClass = pop((flightRepository+search)->economyClass);
		
	}
	//Third economy class
	for((flightRepository+search)->standardSeats; (flightRepository+search)->standardSeats != 0 && (flightRepository+search)->standardClass != NULL; (flightRepository+search)->standardSeats--){
		temp = takePassengerName((flightRepository+search)->standardClass); //For report arrays
		personNo = searchPerson(personRepository,temp,personCount);
		(personRepository+personNo)->soldSeatClass = "standard";  //For info function
		(flightRepository+search)->soldStandardSeats++;
		(flightRepository+search)->reportStandard = realloc((flightRepository+search)->reportStandard,(flightRepository+search)->soldStandardSeats*sizeof(char *));
		(flightRepository+search)->reportStandard[(flightRepository+search)->soldStandardSeats-1] = temp;
		(flightRepository+search)->standardClass = pop((flightRepository+search)->standardClass);
		
	}
	//If you have seat in standard class, sell from business class
	for((flightRepository+search)->standardSeats; (flightRepository+search)->standardSeats != 0 && (flightRepository+search)->businessClass != NULL; (flightRepository+search)->standardSeats--){
		temp = takePassengerName((flightRepository+search)->businessClass);
		personNo = searchPerson(personRepository,temp,personCount);
		(personRepository+personNo)->soldSeatClass = "standard";
		(flightRepository+search)->soldStandardSeats++;
		(flightRepository+search)->reportStandard = realloc((flightRepository+search)->reportStandard,(flightRepository+search)->soldStandardSeats*sizeof(char *));
		(flightRepository+search)->reportStandard[(flightRepository+search)->soldStandardSeats-1] = temp;
		(flightRepository+search)->businessClass = pop((flightRepository+search)->businessClass);
	}
	//If you have seat in standard class, sell from economy class
	for((flightRepository+search)->standardSeats; (flightRepository+search)->standardSeats != 0 && (flightRepository+search)->economyClass != NULL; (flightRepository+search)->standardSeats--){
		temp = takePassengerName((flightRepository+search)->economyClass);
		personNo = searchPerson(personRepository,temp,personCount);
		(personRepository+personNo)->soldSeatClass = "standard";
		(flightRepository+search)->soldStandardSeats++;
		(flightRepository+search)->reportStandard = realloc((flightRepository+search)->reportStandard,(flightRepository+search)->soldStandardSeats*sizeof(char *));	
		(flightRepository+search)->reportStandard[(flightRepository+search)->soldStandardSeats-1] = temp;
		(flightRepository+search)->economyClass = pop((flightRepository+search)->economyClass);	
	}
	fprintf(outputFile,"sold %s %d %d %d\n",secondFound,(flightRepository+search)->soldBusinessSeats,(flightRepository+search)->soldEconomySeats,(flightRepository+search)->soldStandardSeats);
}
	return count;
}

void info(Flight *flightRepository,int count,char* commandLine,FILE *outputFile,Person *personRepository, int personCount){
	char * firstFound = strstr(commandLine, " " );
	char * secondFound = strtok(firstFound+1," \n\r");
	int search = searchPerson(personRepository,secondFound,personCount);
	int parameterCount = 1;
	parameterCount += findSpaceNumber(commandLine);
	if(search == -1 || parameterCount != 2){
			fprintf(outputFile,"error\n");	
	} 
	else{
		if((personRepository+search)->soldSeatClass == NULL)   //If a person cannot get any seats, print none
			fprintf(outputFile,"info %s %s %s none\n",secondFound,(personRepository+search)->flightName,(personRepository+search)->wantedSeatClass);	
		else{
			if(strcmp("business",(personRepository+search)->soldSeatClass) == 0)	
				fprintf(outputFile,"info %s %s %s %s\n",secondFound,(personRepository+search)->flightName,(personRepository+search)->wantedSeatClass,(personRepository+search)->soldSeatClass);
			if(strcmp("economy",(personRepository+search)->soldSeatClass) == 0)	
				fprintf(outputFile,"info %s %s %s %s\n",secondFound,(personRepository+search)->flightName,(personRepository+search)->wantedSeatClass,(personRepository+search)->soldSeatClass);
			if(strcmp("standard",(personRepository+search)->soldSeatClass) == 0)	
				fprintf(outputFile,"info %s %s %s %s\n",secondFound,(personRepository+search)->flightName,(personRepository+search)->wantedSeatClass,(personRepository+search)->soldSeatClass);
		}
	}  
	
}
bool stringIsOnlyWhitespace(const char * line) {    //For read command from inputs.txt
    int i;
    for (i=0; line[i] != '\0'; ++i)
        if (!isspace(line[i]))
            return false;
    return true;
}
int findSpaceNumber(char* str){     //To count the number of parameters, we need to look at the space.
	 int count = 0;
	 int i;
	 for(i=0;str[i];i++){
	                if(str[i] == ' ')
                           count++;
 }
	 return count;
}

//These functions(searchIndex,searchPerson) search for the desired items in struct arrays.
int searchIndex(Flight *flightRepository, char *search,int flightCount){    
	int count;
	if(flightCount == 0){
		return -1;
	}
	for(count = 0; count < flightCount; count++){
		if(strcmp((flightRepository+count)->flightName,search) == 0){
			return count;
		}		
	}
	if(count == flightCount){
		return -1;
	}
}
int searchPerson(Person *personRepository, char *search,int personCount){
	int count;
	if(personCount == 0){
		return -1;
	}
	for(count = 0; count < personCount; count++){
		if(strcmp((personRepository+count)->passengerName,search) == 0){
			return count;
		}		
	}
	if(count == personCount){
		return -1;
	}
}
int main(int argc,char* argv[]){
	int lineCount=1;
	int count = 0;
	FILE *file;
    FILE *outputFile;
    file = fopen(argv[1],"r");
    outputFile = fopen(argv[2],"w");
	outputFile;
	int c=0;
	int last = '\n';

	while (EOF != (c = fgetc(file)))
	 {
    	if (c == '\n' && last != '\n') {
      	++lineCount;
    	}
    last = c;
  	}
    fclose(file);


	file = fopen(argv[1],"r");
	char** lines = (char**) malloc(lineCount*sizeof(char *));
    	char* line = (char*) malloc((sizeof(line)*sizeof(lines))*sizeof(char));


	int i,j=0,nonEmptyLine = 0;
    	while(fgets(line, sizeof(line)*sizeof(lines),file)!=NULL) {
		if (! (stringIsOnlyWhitespace(line))){
			lines[i]= strdup(line);
			i++;
			nonEmptyLine++;
		}

    }
	fclose(file);

	int flightCount = 0;
	Flight *flightRepository = malloc((flightCount + 1) * sizeof(Flight));
	int personCount = 0;
	Person *personRepository = malloc((personCount+1)*sizeof(Person));
	for (i=0 ; i<nonEmptyLine; i++) {
	
	char* command = strtok(lines[i]," ");    //Just take first parameters and control all line with loop.
	
		if(strcmp(command, "addseat") == 0){
			lines[i][strlen(lines[i])] = ' ';
			int parameterCount = 1;
			parameterCount += findSpaceNumber(lines[i]);
			if(parameterCount != 4){
				fprintf(outputFile,"error\n");
			}
			else{
		
			int search = isExistFlight(flightRepository,lines[i],flightCount);
			lines[i][strlen(lines[i])] = ' ';
			lines[i][strlen(lines[i])] = ' ';
			if(search == -1){
				flightRepository = reSizeFlight(flightRepository, flightCount);
	}
			
			flightCount = addSeat(flightRepository, lines[i], flightCount,outputFile,search);
		}
		}
		else if(strcmp(command, "enqueue") == 0){
			lines[i][strlen(lines[i])] = ' ';
			char * firstFound = strstr(lines[i], " " );
			char * secondFound = strstr(firstFound+1, " " );
			char *firstParameter = strtok(firstFound," ");
			char *secondParameter = strtok(secondFound+1," ");
			personRepository = reSizePerson(personRepository,personCount*sizeof(Person));
			if(strcmp(secondParameter,"business") == 0)
				personCount = enqueue(flightRepository,flightCount,firstParameter,secondParameter,outputFile,personRepository,personCount);
			if(strcmp(secondParameter,"economy") == 0)
				personCount = enqueue(flightRepository,flightCount,firstParameter,secondParameter,outputFile,personRepository,personCount);
			if(strcmp(secondParameter,"standard") == 0)
				personCount = enqueue(flightRepository,flightCount,firstParameter,secondParameter,outputFile,personRepository,personCount);
		
				
		}
		else if(strcmp(command, "sell") == 0){
			lines[i][strlen(lines[i])] = ' ';
			flightCount = sellTicket(flightRepository,flightCount,lines[i],outputFile,personRepository,personCount);
		}
		else if(strcmp(command, "close") == 0){
			lines[i][strlen(lines[i])] = ' ';
			flightCount = closeFlight(flightRepository,flightCount,lines[i],outputFile);
			
		}
		else if(strcmp(command, "report") == 0){
			lines[i][strlen(lines[i])] = ' ';
			flightCount = report(flightRepository,flightCount,lines[i],outputFile);
			
		}
		else if(strcmp(command, "info") == 0){
			lines[i][strlen(lines[i])] = ' ';
			info(flightRepository,flightCount,lines[i],outputFile,personRepository,personCount);
		}
		else{
			fprintf(outputFile,"error\n");
		}
	}

		free(line);
		for(i = 0; i < flightCount; i++){
			
			
           //Free all remaining contacts in the queue
			for(j = queueSize((flightRepository+i)->businessClass); j != 0; j--){
				(flightRepository+i)->businessClass = pop((flightRepository+i)->businessClass);
			}
			for(j = queueSize((flightRepository+i)->economyClass); j != 0; j--){
				(flightRepository+i)->economyClass = pop((flightRepository+i)->economyClass);
			}
			for(j = queueSize((flightRepository+i)->standardClass); j != 0; j--){
				(flightRepository+i)->standardClass = pop((flightRepository+i)->standardClass);
			}
			for(j = stackSize((flightRepository+i)->businessSeat); j != 0; j--){
				(flightRepository+i)->businessSeat = del((flightRepository+i)->businessSeat);
			}
			for(j = stackSize((flightRepository+i)->economySeat); j != 0; j--){
				(flightRepository+i)->economySeat = del((flightRepository+i)->economySeat);
			}
			for(j = stackSize((flightRepository+i)->standardSeat); j != 0; j--){
				(flightRepository+i)->standardSeat = del((flightRepository+i)->standardSeat);
			}
			
			
			free((flightRepository+i)->reportBusiness);
			free((flightRepository+i)->reportEconomy);
			free((flightRepository+i)->reportStandard);
			
		}
		for(i = 0; i < nonEmptyLine; i++){
			free(lines[i]);
		}
		free(lines);
		free(flightRepository);
		free(personRepository);
		fclose(outputFile);
}


