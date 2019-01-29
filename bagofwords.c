 //Ahmet Faruk Çolak
  
 #include <stdio.h>
 #include <dirent.h>
 #include <locale.h>
 #include <stdlib.h>
 #include <string.h>
 
  struct Word{
	char wordName[30];
	int occurenceDoc;// didn't used
	int totalOccurences;
	struct Word *nextWord;
	struct wordProperty *sWordProperty;  //starting point of the other linked list
};
typedef struct Word Word; 

 struct wordProperty{
 	char docId[15];
 	int numOfOccurencesInThisDoc;
 	int docLength;
 	char categoryName[20];
 	struct wordProperty *nextWordProperty;
 };
typedef struct wordProperty wordProperty;

FILE *fp;

void discriminatingWords(Word **header){
	
	Word *word;
	word = *header;
	
	char discListForEcon[5][20];
	char discListForHealth[5][20];
	char discListForMagazin[5][20];
	
	int i = 0;
	int control;
	printf("\n\nDISCRIMINATING WORDS");
	printf("\n---------------------------------------");
	printf("\n%-13s|  %-13s|  %-13s", "ECON", "HEALTH", "MAGAZIN");
	printf("\n---------------------------------------");
	while(word != NULL){
		wordProperty *subNode = word->sWordProperty;
		control = 0;
		while(subNode != NULL){
			char categoryName[20];
			strcpy(categoryName, subNode->categoryName);
			if(strcmp(categoryName, "econ") == 0){
				control = 1;
			}
			else {
				control = 0;
				break;
			}
			subNode = subNode->nextWordProperty;
		}
		if(control == 1 && i < 5){
			strcpy(discListForEcon[i], word->wordName);
			i++;
		}
		word = word->nextWord;
	}
	i = 0;
	word = *header;
	while(word != NULL){
		wordProperty *subNode = word->sWordProperty;
		control = 0;
		while(subNode != NULL){
			char categoryName[20];
			strcpy(categoryName, subNode->categoryName);
			if(strcmp(categoryName, "health") == 0){
				control = 1;
			}
			else {
				control = 0;
				break;
			}
			subNode = subNode->nextWordProperty;
		}
		if(control == 1 && i < 5){
			strcpy(discListForHealth[i], word->wordName);
			i++;
		}
		word = word->nextWord;
	}
	i = 0;
	word = *header;
	while(word != NULL){
		wordProperty *subNode = word->sWordProperty;
		control = 0;
		while(subNode != NULL){
			char categoryName[20];
			strcpy(categoryName, subNode->categoryName);
			if(strcmp(categoryName, "magazin") == 0){
				control = 1;
			}
			else {
				control = 0;
				break;
			}
			subNode = subNode->nextWordProperty;
		}
		if(control == 1 && i < 5){
			strcpy(discListForMagazin[i], word->wordName);
			i++;
		}
		word = word->nextWord;
	}		
	for(i = 0; i < 5; i++){
		printf("\n%-13s|  %-13s|  %-15s", discListForEcon[i], discListForHealth[i], discListForMagazin[i]);
	}
}

void stopWords(Word **header){
	
	Word *word;
	word = *header;
	 	
	int  first, second, third, fourth, fifth;
	first = second = third = fourth = fifth = -1;
	char stopWordList[5][20];
	
	while(word != NULL){
		
		if(word->totalOccurences > first){
			fifth = fourth;
			fourth = third;
			third = second;
			second = first;
			first = word->totalOccurences;
			
			strcpy(stopWordList[4], stopWordList[3]);
			strcpy(stopWordList[3], stopWordList[2]);
			strcpy(stopWordList[2], stopWordList[1]);
			strcpy(stopWordList[1], stopWordList[0]);
			strcpy(stopWordList[0], word->wordName);
		}
		else if(word->totalOccurences > second && word->totalOccurences != first){
			fifth = fourth;
			fourth = third;
			third = second;
			second = word->totalOccurences;
			
			strcpy(stopWordList[4], stopWordList[3]);
			strcpy(stopWordList[3], stopWordList[2]);
			strcpy(stopWordList[2], stopWordList[1]);
			strcpy(stopWordList[1], word->wordName);
		}
		else if(word->totalOccurences > third && word->totalOccurences != second){
			fifth = fourth;
			fourth = third;
			third = word->totalOccurences;
			
			strcpy(stopWordList[4], stopWordList[3]);
			strcpy(stopWordList[3], stopWordList[2]);
			strcpy(stopWordList[2], word->wordName);
		}
		else if(word->totalOccurences > fourth && word->totalOccurences != third){
			fifth = fourth;
			fourth = word->totalOccurences;
				strcpy(stopWordList[4], stopWordList[3]);
			strcpy(stopWordList[3], word->wordName);
		}
		else if(word->totalOccurences > fifth && word->totalOccurences != fourth){
			fifth = word->totalOccurences;
			strcpy(stopWordList[4], word->wordName);
		}
		word = word->nextWord;
	}	
	int nums[5] = {first, second, third, fourth, fifth};
	int i, j;
	
	//Sorted fashion for stop words
	for(i = 0; i < 5; i++){
		for(j = i; j < 5; j++){
			if(strcmp(stopWordList[i], stopWordList[j])>0){
				char temp[20];
				strcpy(temp,stopWordList[i]);
				strcpy(stopWordList[i], stopWordList[j]);
				strcpy(stopWordList[j], temp);
				
				int tempNum;
				tempNum = nums[i];
				nums[i] = nums[j];
				nums[j] = tempNum;
			}
 		}
	}
	printf("\n\n\n%-18s\n","STOP WORDS");
	printf("-------------------------------\n");
	for(i = 0; i < 5; i++){
		printf("%d-> %s(%d)\n",i+1, stopWordList[i],nums[i]);
	}
}

int insert(Word ** header, char word[20], char categoryName[20], char fileName[20], int wordCounter ){ 
  
   Word *newWord,*currentWord,*previousWord;
   wordProperty *newWordProperty;
   
   // create node to insert and assign values to its fields
   newWord = malloc(sizeof(Word));
   strcpy(newWord->wordName,word);
   newWord->nextWord = NULL;
   
     
   newWord->totalOccurences++;
	
   // if LL empty
   if (*header == NULL){
   		//create node of second structure to insert and assign values to its fields
   		newWordProperty = malloc(sizeof(wordProperty));
   		strcpy(newWordProperty->docId, fileName);
   		strcpy(newWordProperty->categoryName, categoryName);
		newWordProperty->numOfOccurencesInThisDoc++;
		newWordProperty->docLength = wordCounter;
   		newWordProperty->nextWordProperty = NULL;
   		//connects linked lists. (MLL)
   		newWord->sWordProperty = newWordProperty;
   		
		*header=newWord;
   }
   
   // if LL not empty
   else {  
   		//Current is head of the list now 		
    	currentWord = *header;
    	
    	//loop to find the correct location in the list
    	while (currentWord != NULL && (strcmp(currentWord->wordName,newWord->wordName)<0)) {
    		previousWord = currentWord;
			currentWord = currentWord->nextWord;
	 	}
	 	
	 	//If same word comes..
		if (currentWord!=NULL && (strcmp(currentWord->wordName,newWord->wordName)==0)) {
			
			currentWord->totalOccurences++;
			wordProperty *iter = currentWord->sWordProperty; //Current word's linked list's first node
		
			int control = 0;	
			
			char tempDocAndFileName[50];
			char tempFileName[20];
			strcpy(tempDocAndFileName, categoryName);
			strcpy(tempFileName, fileName);
			strcat(tempDocAndFileName, tempFileName);
				
			do{ //Checks whether current word exists in a document that already inserted to the list
				
				if(control == 1){ //to make iter = iter->nextWordProperty;
					iter = iter->nextWordProperty;
				}
				control = 1;
				
				char iterDocAndFileName[50];
				char iterFileName[20];
				strcpy(iterDocAndFileName, iter->categoryName);
				strcpy(iterFileName, iter->docId);
				strcat(iterDocAndFileName, iterFileName);
				
				if(strcmp(iterDocAndFileName, tempDocAndFileName) == 0){ //If a word occurs in a document multiple times
					iter->docLength = wordCounter;
					iter->numOfOccurencesInThisDoc++;
					return 0; //We don't need the rest, we incremented the numOfOccurencesInThisDoc field.
				}
			}
			while(iter->nextWordProperty != NULL);
			
			//create node of second structure to insert and assign values to its fields
			newWordProperty = malloc(sizeof(wordProperty));
   			strcpy(newWordProperty->docId, fileName);
   			strcpy(newWordProperty->categoryName, categoryName);
   			newWordProperty->docLength = wordCounter;
			newWordProperty->numOfOccurencesInThisDoc++;
			newWordProperty->nextWordProperty = NULL;
			
			//iter is the last node added to the list
			iter->nextWordProperty = newWordProperty;
			
			return 0; //We don't need the rest, we added a new node under the current(same) word.
		} 
		else{ //For the non-existent word
			//create node of second structure to insert and assign values to its fields
			newWordProperty = malloc(sizeof(wordProperty));
   			strcpy(newWordProperty->docId, fileName);
   			strcpy(newWordProperty->categoryName, categoryName);
   			newWordProperty->docLength = wordCounter;
			newWordProperty->numOfOccurencesInThisDoc++;
   			newWordProperty->nextWordProperty = NULL;
   		
   			newWord->sWordProperty = newWordProperty; 	
		}
	 	// insert node in a sorted fashion
	 	if (currentWord != NULL) 
			newWord->nextWord=currentWord;
	 	// if value to insert is the least in LL then have header point to node
     	if (currentWord == *header) 
		 	*header=newWord;
	 	// otherwise insert node in correct position
		else 
		 	previousWord->nextWord = newWord;	 
   }
   return 1;
 }  

int main(){
	
	DIR *dir;
    char folderName[15];
    
	struct dirent *ent;
	
	setlocale(LC_ALL, "Turkish");  //türkçe karakter
	
	char word[20];
	int wordCounter;
	
	Word *hdr, *iter;
	hdr=NULL;
	
	if ((dir = opendir (".\\dataset")) != NULL) {
		
    /* print all the files and directories within directory */
 
    	while ((ent = readdir (dir)) != NULL) {
    		
			char directory[30] = {".\\dataset\\"}; 
    	 
    		if (!strcmp (ent->d_name, "."))
           	 	continue;
            
      	  	if (!strcmp (ent->d_name, ".."))
           	 	continue; 
   		
   		 	strcpy(folderName, ent->d_name);
   			strcat(directory, folderName);
   			
   			DIR *dir2;
   			char fileName[15];
   		 
   		 	struct dirent *ent2;
   		 
   		 	if ((dir2 = opendir (directory)) != NULL) {
   		 	
   		 		while ((ent2 = readdir (dir2)) != NULL) {
    	
					char directory2[30];
					strcpy(directory2, directory);
    		    	strcat(directory2, "\\");
    		    	
    		    	if (!strcmp (ent2->d_name, "."))
       		    		continue;
       				if (!strcmp (ent2->d_name, ".."))
            			continue; 
    	
   					strcpy(fileName, ent2->d_name);
   					strcat(directory2, fileName);
	
					fp = fopen(directory2,"r");
					
					wordCounter = 0;
					while (!feof(fp)) { 
    					fscanf(fp,"%s",word); 
						wordCounter++;
					}
					
					fp = fopen(directory2,"r");
			
					while (!feof(fp)) { 
    					fscanf(fp,"%s",word); 
						insert(&hdr,word, folderName, fileName, wordCounter);
					}
  				}
  			}			
  		}
  			fclose(fp);
	}
	iter = hdr;
	printf("\n%-18s  %-5s      %5s ","WORDS", "TOTAL NUMBER", "PROPERTIES(Category Name-Document Name-Number Of Occurences In This Document, Document Length, Total Number Of Documents This Term Occur)");
	printf("\n-----------------------------------------------------------------");
 	while (iter != NULL) {
   		printf("\n%-20s%-5d         ||",iter->wordName, iter->totalOccurences);
   		wordProperty *iterWP = iter->sWordProperty;
   		
		int control = 0;
		int counterOfDocument = 0;
		do{
			counterOfDocument++;
			if(control == 1){
				iterWP = iterWP->nextWordProperty;
			}
			control = 1;
			printf("  %s  **  %s  **  %d  **  %d||",iterWP->categoryName, iterWP->docId, iterWP->numOfOccurencesInThisDoc, iterWP->docLength);
		}	
   		while(iterWP->nextWordProperty != NULL);
   		printf("  %d",counterOfDocument);
		iter = iter->nextWord;
	}
	stopWords(&hdr);
	discriminatingWords(&hdr);
}
/* References:
--> https://www.geeksforgeeks.org/to-find-smallest-and-second-smallest-element-in-an-array/
--> https://stackoverflow.com/questions/11736060/how-to-read-all-files-in-a-folder-using-c */
