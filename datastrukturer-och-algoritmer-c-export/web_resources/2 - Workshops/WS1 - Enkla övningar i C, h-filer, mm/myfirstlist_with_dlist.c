#include <stdio.h>
#include <stdlib.h>

// Uppgift 2 B1
#include "dlist.h"

int main(int argc, char **argv)
{
	int tal;

	// Uppgift 2 B2 
	dlist *myList = dlist_empty(free); // Pekare till en ny tom lista.
	
	int i;
	i = 0;
	do {
		scanf("%d", &tal);
		i++;

		// Uppgift 2 B2
		int *ptrInt = (int*)malloc(sizeof(int));	//  Allokerar en minnesposition för ett heltal
		*ptrInt = tal;					// Kopierar in det inlästa heltalet dit
		 dlist_insert(myList, ptrInt, dlist_first(myList));	// Adderar denna position till vår lista
	}
	while ((i < 100) && (tal >= 0));

	// Uppgift 2 B3
	// Loopar igenom alla element i listan från start, går till nästa och hela tiden kollar så den är vid slut
	for(dlist_pos dpos = dlist_first(myList); !dlist_is_end(myList, dpos); dpos = dlist_next(myList, dpos))
	{
		// Läser talet på den positionen med dlist_inspect och skriver ut det
		int tmpTal;
		tmpTal = *(int *)dlist_inspect(myList, dpos);
		printf("%d\n", tmpTal);
	} 

	// Uppgift 2 B4
	// Gör samma sak som i B3 men istället för att skriva ut dem en och en så summerar vi ihop dem och
	// skriver sedan ut resultatet
	int summa = 0;
	for(dlist_pos dpos = dlist_first(myList); !dlist_is_end(myList, dpos); dpos = dlist_next(myList, dpos))
	{
		int tmpTal;
		tmpTal = *(int *)dlist_inspect(myList, dpos);
		summa = summa + tmpTal;
	} 
	printf("%d\n", summa);

	// Uppgift 2 B5
	// Ungefär som ovan men man kollar om det aktuella talet är jämnt och tar i så fallbort de från listan.
	for(dlist_pos dpos = dlist_first(myList); !dlist_is_end(myList, dpos); dpos = dlist_next(myList, dpos))
	{
		int tmpTal;
		int *ptrTal;
		ptrTal = (int *)dlist_inspect(myList, dpos);
		tmpTal = *ptrTal;
		if (tmpTal % 2 == 0)
		{
			dpos = dlist_remove(myList, dpos);
		}
	} 

	// Uppgift 2 B6
	// Exakt samma som  vi gjort ovan, loopar igenon till slutet och skriver ut talen som finns kvar 
	// och summerar dessa.
	int uddaSumma = 0;
	for(dlist_pos dpos = dlist_first(myList); !dlist_is_end(myList, dpos); dpos = dlist_next(myList, dpos))
	{
		// Läser talet på den positionen med dlist_inspect och skriver ut det
		int tmpTal;
		tmpTal = *(int *)dlist_inspect(myList, dpos);
		printf("%d\n", tmpTal);
		uddaSumma += tmpTal;
	} 
	printf("%d\n", uddaSumma);


	// Uppgift 2 B7
	// Här loopar vi igenom resterande och tar bort dem också.
	for(dlist_pos dpos = dlist_first(myList); !dlist_is_empty(myList) && !dlist_is_end(myList, dpos); dpos = dlist_next(myList, dpos))
	{
		int *ptrTal;
		ptrTal = (int *)dlist_inspect(myList, dpos);
		dpos = dlist_remove(myList, dpos);
	}

	// Uppgift 2 B8
	// Här använder vi den av interfacet definerade funktionen för att ta bort den nu tomma listan.

	dlist_kill(myList);






	return 0;
}
