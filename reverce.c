//////////////////////////////////
//
// Tiedosto: reverse.c
// Tekijä: Aleksi Karhu 
// Opiskelijanumero: 0452237
// Päivämäärä: 16.04.2021
// Lähteet: C-kieli ohjelmointiopas, Kasurinen & Nikula 2012
//			https://technotip.com/8770/c-program-to-print-elements-of-array-in-reverse-order/
//			https://www.geeksforgeeks.org/c-program-to-reverse-the-content-of-the-file-and-print-it/
//			https://c-for-dummies.com/blog/?p=1112
//
//////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define BUFFER 256

//Funktio joka kysyy käyttäjältä syötettä ja tulostaa sen käänteisenä komentoriville
void reverseInTerminal() {
	int i, count = 0;	
	char *input = NULL;
	size_t size;
	char list[BUFFER][BUFFER];


	//Määritetään !end lopetuskomennoksi
	fprintf(stdout, "Type something to be reversed. End the typing by typing !end.\n\n");


	//Käytettään getlinea käyttäjä syöttämän rivin hakemiseksi
	while(getline(&input, &size, stdin) != -1) {
		if(strcmp(input, "!end\n") == 0) {
			break;
		}

		//Kopioidaan rivi listaan ja kasvatetaan laskuria
		strcpy(list[count], input);
		count++;
	}

	fprintf(stdout, "The input reversed:\n");	

	//Käytään lista n-1 kertaa läpi ja pienennetään laskuria
	for(i = count-1; i >=0; i--){

		//Tulostetaan listan alkiot
		fprintf(stdout,"%s", list[i]);	
	}

	//Muistin vapautus ja ohjelman lopetus	
	free(input);	
	exit(1);
}


//Funktio joka lukee tiedostosta ja kirjoittaa käänteisenä komentoriville
void reverseFromFile(char *filename) {
	char list[BUFFER][BUFFER];
	char *input = NULL;
	int i, count = 0;
	size_t size;	
	FILE *file = NULL; 
	
	//Määritetään tiedosto ja tehdään virheenkäsittely
	file = fopen(filename, "r");
	if(file == NULL) {
		fprintf(stderr, "Error in opening file");
		exit(1);
	}
	
	//Luetaan tällä kertaa tiedostosta ja kopioidaan listaan
	while(getline(&input, &size, file) != -1) {
		strcpy(list[count], input);
		count++;
	}
	
	//Hyödynnetään reverseInTerminal-funktion kirjoitusta
	fprintf(stdout, "The file reversed:");	
	for(i = count-1; i >=0; i--){
		fprintf(stdout,"%s", list[i]);
	}	

	//Muistin vapautus, tiedoston sulku ja ohjelman lopetus
	free(input);
	fclose(file);
	exit(1);

}

//Funktio joka lukee tiedostosta ja kirjottaa toiseen tiedostoon
void reverseToFile(char *readfile, char *writefile) {
	char list[BUFFER][BUFFER];
	char *input = NULL;
	int i, count = 0;
	size_t size;	
	FILE *read = NULL;
	FILE *write = NULL;
 

	//Määritetään luettava tiedosto ja virheenkäsittely
	read = fopen(readfile, "r");
	if(read == NULL) {
		fprintf(stderr, "Error in opening file");
		exit(1);
	}

	//Määritetään kirjoitettava tiedosto ja virheenkäsittely
	write = fopen(writefile, "w");
	if(write == NULL) {
		fprintf(stderr, "Error in opening file");
		exit(1);
	}
	
	//Hyödynnetään reverseFromFile-funktion lukemista
	while(getline(&input, &size, read) != -1) {
		strcpy(list[count], input);
		count++;
	}

	//Iteriodaan lista läpi ja kirjoitetaan tiedostoon
	for(i = count-1; i >= 0; i--){
		fprintf(write,"%s", list[i]);
	}


	//Muistin vapautus, tiedoston sulku ja ohjelman lopetus
	free(input);
	fclose(read);
	fclose(write);
	exit(1);

}  


int main(int argc, char *argv[]) {

	//First use case where ./reverse is called
	if (argc == 1){
		reverseInTerminal();
	}

	//Second use case where ./reverse input.txt is called
	if (argc == 2){
		reverseFromFile(argv[1]);
	}

	//Third use case where ./reverse input.txt output.txt is called
	if (argc == 3){
		reverseToFile(argv[1], argv[2]);
	}
    return 0;
}