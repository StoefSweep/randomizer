//Author: Aidan Stoeffler
//Randomizer
//A basic RNG that can be used for general-purpose random choice. When you want a surprise.

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "rbtree.h"

int main(int argc, char*argv[]){

	srand(time(NULL));

	//Initialize the values that will be shared across both versions of the call. They will be min, max, numTimes, diff, and noDupes.
	int min;
	int max;
	int numTimes;
	char noDupes;
	int diff;

	//To acommodate for the Bash version, two different methods of gathering the input will be used. If the Bash script executes this function
	// (that is, there are at least 2 arguments, first check if 6 arguments are passed in. otherwise, gather data as
	// usual.
	if(argc >= 2){
		// First, check if there are 6 arguments passed in, which is the amount of arguments that should be passed in by the Bash script. Uf there
		// are not 6 arguments, display an error message, and return. Otherwise, assign min, max, and numTimes to their respective values, and check for
		// inconsistencies.
		if(argc != 6){
			printf("ERROR: INVALID NUMBER OF ARGUMENTS PASSED IN. PLEASE ENTER IN 4 NON-EMPTY VALUES IN THE BASH SCRIPT.\n");
			return 2;
		}
	       //Begin assigning the variables to min, max, and numTimes
	       min = atoi(argv[2]);
	       max = atoi(argv[3]);
	       numTimes = atoi(argv[4]);
	       //Then, check if the preconditions are correct. If they are not correct, then simply print an error message and exit.
	       //PRECONDITION 1: Min is less than or equal to max. If this fails: Print the respective error message and return.
	       if(min > max){
		       printf("ERROR: THE MINIMUM CANNOT BE GREATER THAN THE MAXIMUM.\n");
		       return 2;
	       }
	       //PRECONDITION 2: numTimes must be greater than zero. If this fails: Print the respective error message and return.
	       if(numTimes <= 0){
		       printf("ERROR: THE NUMBER OF RANDOM NUMBERS CANNOT BE LESS THAN 1.\n");
		       return 2;
	       }
	       //If the code has reached this point: Assign noDupes to its respective variable, and set diff to max - min + 1.
	       noDupes= ((char) *argv[5]);
	       diff = max - min + 1;
	       printf("Here are your %d random numbers: \n", numTimes);
	}else{	
		//The Bash script was not used to call this function. Proceed to normal mode.
		min = 0;
		max = -1;
		//A character that represents the user's consent to a dependently-random search, named noDupes.
		noDupes = 0;
		char buff = 0;
		scanf("%s", &buff);
		while(min > max){
			printf("Select the minimum number: ");
			scanf("%d", &min);
			printf("Select the maximum number: ");
			scanf("%d", &max);
			if(min > max){
				printf("ERROR: THE MINIMUM CANNOT BE GREATER THAN THE MAXIMUM. PLEASE TRY AGAIN.\n");
			}
		}
		numTimes = 0;
		while(numTimes <= 0){
			printf("How many randomly-generated numbers do you want: ");
			scanf("%d", &numTimes);
			if(numTimes <= 0){
				printf("ERROR: THE NUMBER OF TIMES MUST BE GREATER THAN 0. PLEASE TRY AGAIN. \n");
			}
		}
		diff = max - min + 1;
		//If the number of times requested is less than or equal to the difference, then it is possible to perform a dependent randomization without any
		//duplicates. Prompt the user if they would like a dependent search.
		if(numTimes <= diff && diff >= 2){
			printf("Based on your inputs, it is possible to eliminate duplicates from your search. Would you like to? (y/n)\n");
			//Clean the buffers.
			char buff = 0;
			scanf("%c", &buff);
			scanf("%c", &noDupes);

		}
	}
	int i;
	//If noDupes equals y, then perform a no-duplicates search.
	if(noDupes == 'y'){
		//Dynamixally create an array of size num_times.
		int* storedVals = (int*) malloc(sizeof(int) * numTimes);
		//Create a rbTree pointer, named extraVals.
		rbTree* extraVals = NULL;
		//Loop and assign incremental values in storedVals.
		int inc;
		for(inc = 0; inc < numTimes; inc++){
			storedVals[inc] = inc + min;
		}
		//Proceed with an altered version of the randomized search.
		for(i = 0; i < numTimes; i++){
			//Tree-based version: Assign a random value to randVal.
			int randVal = rand() % diff + min;
			//Branch off for the following cases:
			// Case 1a: randVal - min is less than numTimes. In this case, just simply swap between the
			// corresponding array positions.
			// Case 1b: randVal - min is greater than or equal to numTimes. In this case, use a tree to store these
			// values.
			if(randVal - min < numTimes){
				//Initialize a placeholder value, named mid.
				int mid;
				//Set mid to storedVals[randVal - min]
				mid = storedVals[randVal - min];
				// Set storedVals[randVal - min] to storedVals[i]
				storedVals[randVal - min] = storedVals[i];
				// Set storedVals[i] to mid.
				storedVals[i] = mid;

			}else{
				//In this case, the index to access is beyond the array's limits. Use a binary search
				//tree to store these temporary values. The tree may or may not be created already.
				//Branch off for the following cases:
				// Case 2a: A tree has not yet been created.
				// Case 2b: A tree has been created.
				if(extraVals == NULL){
					//Case 2a
					// Initialize a new node, called newNode. Then, swap its values with
					// storedVals[i]
					treeNode* newNode = createNode((randVal - min), randVal);
					int mid = storedVals[i];
					storedVals[i] = newNode->value;
					newNode-> value = mid;

					//Then, set extraVals to a createTree call, using newNode as the parameter
					extraVals = createTree(newNode);
				}else{
					//Case 2b
					// In this case, extraVals already exists. Use the search function to find
					// a potential node, and store the results in matchNode.
					treeNode* matchNode = searchTree(extraVals, (randVal - min));

					// Then, branch off for the following conditions:
					// Case 3a: matchNode != NULL
					// Case 3b: matchNode == NULL
					if(matchNode != NULL){
						//Case 3a. In this case, a match has been found. Swap the values
						// of matchNode->value and storedVals[i]
						int mid = storedVals[i];
						storedVals[i] = matchNode->value;
						matchNode->value = mid;

					}else{
						//Case 3b.
						//In this case, no match has been found.
						// Use the createNode function, with randVal - min and randVal passed
						// as parameters.
						matchNode = createNode((randVal - min), randVal);

						//Swap the values of matchNode->value and storedVals[i]
						int mid = storedVals[i];
						storedVals[i] = matchNode->value;
						matchNode->value = mid;

						//Call the insert function, using extraVals and matchNode as parameters
						rbInsert(extraVals, matchNode);

					}

				}

			}
			

		}
		//Loop for numTimes times, and print the random variables.
		for(i =0; i < numTimes; i++){
			printf("Random Number #%d: %d\n", (i + 1), storedVals[i]);

		}
		//Free storedVals after the randomization.
		free(storedVals);
		//Free extraVals using deleteTree.
		if(extraVals != NULL){
			deleteRBTree(extraVals);
		}
	}else{
		for(i = 0; i < numTimes; i++){
			// Improved randomizer function: Uses the modulus operator to narrow the options
			// to the difference.
			int randVal = rand() % diff + min;
			printf("Random number #%d: %d\n", (i + 1), randVal);
		}
	}


}
