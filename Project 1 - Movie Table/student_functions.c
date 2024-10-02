/* name: Noa Figenblat 
 * uw net Id: 908 198 9114
*/

/* This function takes a string as input and removes 
 * leading and trailing whitespace including spaces
 * tabs and newlines. It also removes multiple internal
 * spaces in a row. Arrays are passed by reference.
 */

#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"


void Clean_Whitespace(char str[]) {

	int size = 0;
	//finding the size of the input string
	for(int i = 0; str[i]!= '\0'; i++){
		++size;
	}

	int index = 0;

	//begin removing leading whitespace 

	//int countLead which counts the leading whitespace
	int countLead = 0;

	//int differenceLead which holds the difference between end of leading whitespace and the length of the array 
	int differenceLead = 0;
	
	//while loop to count the amount of leading whitespace indices (including newlines and tabs)
	while(str[index]== ' ' || str[index] == '\n' || str[index] == '\t'){
		countLead++;
		index++;
	}	

	differenceLead = size-countLead;
	
	//removing the whitespaces, and shifting the array down by however many whitespaces there are
	for(int j = 0; j < size; j++){
		if(str[j+countLead] != '\0'){
			str[j] = str[j+countLead];
		}
	}
	for(int k = differenceLead; k < size; k++){
		str[k] = '\0';
	}

	//end removing leading whitespaces
	

	//begin removing trailing whitespaces
	
	index = size;

	//int countTail which counts trailing whitespaces
	int countTail = 0;

	//int differenceTail which holds the difference between the beginning of the trailing whitespace and the size of the array
	int differenceTail = 0;

	//while loop to count the amount of trailing whitespace indices (including newlines and tabs)
	while(str[index]== ' ' || str[index] == '\n' || str[index] == '\t' || str[index] == '\0'){
		countTail ++;
		index--;
	}

	differenceTail = size - countTail;

	//for loop replacing all trailing whitespaces with '\0' ~ null terminator
	for(int i = size; i > differenceTail; i--){
		str[i] = '\0';
	}

	//end removing trailing whitespaces
	

	//begin removing multiple internal spaces and internal tabs/newlines 
	
	for(int i = 0; i < size; i++){
		//remove multiple spaces in a row, if they exist
		if(str[i] == ' ' && str[i+1] == ' '){
			for(int j = i+1; j < size; j++){
				str[j] = str[j+1];
				--i;
			}
		}

		//removing tabs and newlines, if they exist
		if(str[i] == '\t' || str[i] == '\n'){
                    for(int k = i; k < size; k++){
                            str[k]= str[k+1];
                            --i;
                        }
                }
                str[size] = '\0';
        }

    return;
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case
 */ 
void Fix_Case(char str[]) {

    /*
     * difference between lower/uppercase in ASCII == +/- 32 
     * add to go from upper to lowercase
     * subtract to go from lower to uppercase
     */

	int size = 0;
	for(int i = 0; str[i] != '\0'; i++){
		++size;
	}

	for(int i = 0; i < size; i++){
		//capitalizing the first letter of each word
		if(str[i-1] == ' ' || i == 0){
			if(str[i]>= 'a' && str[i]<='z'){
				str[i] = str[i]-32;
			}
		}
		//lowercasing every other letter in the string
		else{
			if(str[i]>='A' && str[i]<='Z'){
				str[i] = str[i]+32;

			}
		}
	}
	str[size] = '\0';
    return;
}

/* this function takes a string and returns the 
 * integer equivalent
 */
int String_To_Year(char str[]) {

	/*
	 * int variable which stores the int equivalent of the string 
	 * implements atoi() to convert string to int 
	 */
	int year = 0;
	year = atoi(str);

    return year;
}


/* this function takes the name of a 
 * director as a string and removes all but
 * the last name.  Example:
 * "Bucky Badger" -> "Badger"
 */
void Director_Last_Name(char str[]) {


	Clean_Whitespace(str);

	int size = 0;
	for(int i = 0; str[i] != '\0'; i++){
		++size;
	}

	//int count which keeps track of how many characters are in the last name 
	int count = 0;

	//int difference which holds the difference between the array length and the number
	//of characters in the last name
	int difference;

	//forloop counting the characters in the last name, until it hits the space character
	for(int i = size-1; i>= 0; i--){
		if(str[i] != ' '){
			count++;
		}
		if(str[i] == ' '){
			break;
		}
	}

	difference = size - count;

	//forloop reinitializing str[] to hold only the last name 
	for(int j = 0; j < size; j++){
            if(j<count){
                str[j] = str[j+difference];
            }
            if(j>=count){
                str[j] = '\0';
            }
        }
    return;
}



/* this function takes the a string and returns
 * the floating point equivalent
 */
float String_To_Rating(char str[]) {

	/*
	 * float variable rating which holds the float equivalent of the string
	 * implements atof() to convert string to float
	 */
	float rating = 0;
        rating = atof(str);

    return rating;
}


/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000 
*/
long long String_To_Dollars(char str[])  {
    /*
     * M or m == 6 zeros
     * K or k == 3 zeros
     * implements atol() to convert string to long
     * returns long dollars; the decimal equivalent of the revenue 
     */

	//size of the char array str
	int size = 0;
	for(int i = 0; str[i] != '\0'; i++){
		++size;
	}

	/*
	 * char array temp declared to size 10
	 * (assuming no movie revenue higher than the billions place ~ 1-9 billion~)
	 */
	char temp[10];

	//long dollars which is returned by String_To_Dollars()
	long long dollars = 0;

	//forloop iterating through the string
	for(int i = 0; i < size; i++){
		//checking if the char is M or m symbolizing millions
		if(str[i] == 'M' || str[i] == 'm'){
			//forloop adding 6 zeros to the end of the temp array
			for(int j = i; j<i+6; j++){
				temp[j] = '0';
			}

			break;
		}

		//checking if the char is K or k symbolizing thousands
		else if(str[i] == 'K' || str[i] == 'k'){
			//forloop adding 3 zeros to the end of the temp array
			for(int j = i; j<i+3; j++){
				temp[j] = '0';
			}
			break;
		}

		//if the index of i does not signify millions or thousands, copy the character over to the temp array
		else if(str[i] >= '0' && str[i] <= '9'){
			temp[i] = str[i];
		}
		else{
			break;
		}
	}

	//converting the string representing revenue to a long, and storing it in the long variable dollars
	dollars = atol(temp);


    return dollars;
}


/* This function takes the array of strings representing 
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {

	 //temp arrays for each function
                char tempYear[1024];
                char tempRatings[1024];
                char tempDollars[1024];

	for(int i = 0; i< num_movies; i++){

		int index = 0;
		int tempIndex = 0;

		//loop for movie data needed in titles[10][1024]

		/*
		 * loops through the movie data in csv[][] till it reaches the comma, which is used as a delimiter
		 * copies over the title (with the correct formatting) to titles[][]
		 */
	
		tempIndex = 0;
		index = 0;

		for(int j = 0; j < 1024; j++){
			index++;

			if(csv[i][j] == ','){
				index++;
				break;
			}	
			else{
				titles[i][j] = csv[i][j];
			}
		}

		//loop for movie data needed in years[]

		/*
		 * loops through the movie data in csv[][] starting from the index after the previous comma, until it reaches the next comma
		 * places the chars for the movie year into a temporary array tempYear[]
		 * calls Clean_Whitespace and String_To_Year on tempYear[]
		 * copies the correctly formatted year into years[]
		 */


		tempIndex = 0;
		for(int y = index; y < 1024; y++){
                        index++;

                        if(csv[i][y] == ','){
                                index++;
                                break;
                        }
                        else{
                                tempYear[tempIndex] = csv[i][y];
				tempIndex++;
                        }
                }

		Clean_Whitespace(tempYear);

		//calling String_To_Year and saving in an int variable
		int yearInt = 0;
	       	yearInt = String_To_Year(tempYear);
                years[i] = yearInt;

		
		//loop to skip past the movie minutes data - not needed for this project


		for(int s = index; s < 1024; s ++){
			if(csv[i][s] == ','){
				index++;
				break;
			}
			else{
				index++;
			}	
                }

		//loop for movie data needed in directors[10][1024]
		
		/*
		 * loops through movie data in csv[][], starting from the index after the previous comma, untill it reaches the next comma
		 * places the chars for the Director's name into directors[]
		 */

		tempIndex=0;

		 for(int k = index; k < 1024; k++){
                        index++;

		       	if(csv[i][k] == ','){
                                index++;
                                break;
                        }
                        else{
                                directors[i][tempIndex] = csv[i][k];
				tempIndex++;
                        }
                }
		//loop for movie data needed in ratings[10]

		/*
		 * loops through movie data in csv[][], starting from the index after the previous comma, untill it reaches the next comma
		 * places the chars for the rating into a temporary array tempRatings[]
		 * calls Clean_Whitespace and String_To_Rating on tempRatings[]
		 * copies the correctly formatted rating into ratings[] 
		 */
		tempIndex = 0;
		while(csv[i][index]){
			if(csv[i][index]==','){
				++index;
				break;
			}
			else{
				tempRatings[tempIndex] = csv[i][index];
				++tempIndex;
				++index;
			}
		}

		Clean_Whitespace(tempRatings);
		float ratingFloat = 0;
	        ratingFloat = String_To_Rating(tempRatings);

		ratings[i] = ratingFloat;
	
		//loop for movie data needed in dollars[10]

		/*
		 * loops through movie data in csv[][], starting from the index after the previous comma, untill it reaches the next comma
		 * places the chars for the revenue into a temporary array tempDollars[]
		 * calls Clean_Whitespace and String_To_Dollars on tempDollars[]
		 * copies the correctly formated revenue/dollar amount into dollars[]
		 */
		tempIndex = 0;
		while(csv[i][index]!= '\n'){
			tempDollars[tempIndex] = csv[i][index];
			++tempIndex;
			++index;
		}

		Clean_Whitespace(tempDollars);
		
		long long dollarAmount = 0;
	        dollarAmount = String_To_Dollars(tempDollars);

		dollars[i] = dollarAmount;
	}
	
    return;
}



/* This function prints a well formatted table of
 * the movie data 
 * Row 1: Header - use name and field width as below
 * Column 1: Id, field width = 3, left justified
 * Column 2: Title, field width = lenth of longest movie + 2 or 7 which ever is larger, left justified, first letter of each word upper case, remaining letters lower case, one space between words
 * Column 3: Year, field with = 6, left justified
 * Column 4: Director, field width = length of longest director last name + 2 or 10 (which ever is longer), left justified, only last name, first letter upper case, remaining letters lower case
 * column 5: Rating, field width = 6, precision 1 decimal place (e.g. 8.9, or 10.0), right justified
 * column 6: Revenue, field width = 11, right justified
 */
void Print_Table(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
	
	/*
	 * begin finding longest movie title length
	 * loops through the char array titles, counts the chars in each title, and compares it to the previous longest length 
	 */
	int longestTitle = 7;
	int titleCount;
	int j;

	for(int i = 0; i < num_movies; i++){
		titleCount = 0;
		j = 0;
		while(titles[i][j]){ 
			++titleCount;
			++j;	
		}

		titleCount = titleCount + 2;

		if (titleCount > longestTitle){
			longestTitle = titleCount;
		}
	}
	//end finding longest movie title length
	


	/*
	 * begin finding length of longest director last name 
	 * loops through char array directors[][], counts the chars in each director's last name, and compares it to the previous longest length
	 */
	int longestDirector = 10;
        int directorCount;
        int k;

        for(int i = 0; i < num_movies; i++){
                directorCount = 0;
                k = 0;
                while(directors[i][k]){
                        ++directorCount;
                        ++k;
                }

                directorCount = directorCount + 2;

                if (directorCount > longestDirector){
                        longestDirector = directorCount;
                }
        }

	//end finding longest director last name

       
	
	
	//header print statements for the table

	//coloumn #1 - Id 
	printf("%-3s", "Id");

	//column #2 - Title
	printf("%-*s", longestTitle, "Title" );

	//column #3 - Year
	printf("%-6s", "Year" );

	//column #4 - Director
	printf("%-*s", longestDirector, "Director");

	//column #5 - Rating
	printf("%6s", "Rating" );

	//column #6 = Revenue
	printf("%*s", 11, "Revenue" );

	printf("\n");

	
	//forloop to fill in the rest of the table
	

	char tempTitle[longestTitle];
	char tempDirector[longestDirector];
	tempTitle[0] = '\0';
	tempDirector[0]='\0';

	for(int i = 0; i<num_movies; i++){

		// id column
		printf("%-3d", i+1);
	
		
		for(int j = 0; j < longestTitle; j++){
			tempTitle[j] = titles[i][j];
		}

		Clean_Whitespace(tempTitle);
		Fix_Case(tempTitle);

		//title column
		printf("%-*s", longestTitle, tempTitle);


		//year column
		printf("%-6d", years[i]);


		for(int k = 0; k < longestDirector; k ++){
			tempDirector[k] = directors[i][k];
		}

		Clean_Whitespace(tempDirector);
		Fix_Case(tempDirector);
		Director_Last_Name(tempDirector);

		//director column
		printf("%-*s",longestDirector, tempDirector);

		
		//rating column
		printf("%*.1f", 6, ratings[i] );

		//revenue column
		printf("%*llu", 11, dollars[i]);

		

		printf("\n");

	}

    return;
}


