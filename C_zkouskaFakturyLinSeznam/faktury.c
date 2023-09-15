#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "faktury.h"

enum mesicEnum dejMesic(char* datum) {
	char mesic[3] = { datum[5], datum[6], '\0' };
	int cisloMesice = atoi(mesic);
	return cisloMesice;
}

tFakturaList* nactiFaktury(char* jmSoub, enum fakturaEnum typFaktury, enum mesicEnum mesic)
{
	tFakturaList* prvni = NULL;
	tFakturaList* posledni = NULL;

	FILE* soubor = fopen(jmSoub, "rb");
	if (soubor != NULL)
	{
		fseek(soubor, 0, SEEK_END); //nastavení pozice v souboru na konec
		long fileLength = ftell(soubor); //vrátí aktuální pozici v souboru v bajtech
		int pocetPolozek = fileLength / sizeof(tFaktura);
		rewind(soubor);
		tFaktura* poleFaktur = calloc(pocetPolozek, sizeof(tFaktura));
		fread(poleFaktur, sizeof(tFaktura), pocetPolozek, soubor);

		for (int i = 0; i < pocetPolozek; i++)
		{
			if (poleFaktur[i].typ == typFaktury && dejMesic(poleFaktur[i].datum) == mesic)
			{
				tFakturaList* novyPrvek = calloc(1, sizeof(tFakturaList));
				novyPrvek->faktura = poleFaktur[i];
				novyPrvek->dalsi = NULL;

				if (prvni == NULL)
				{
					prvni = novyPrvek;
					posledni = novyPrvek;
				}
				else {
					posledni->dalsi = novyPrvek;
					posledni = novyPrvek;
				}
			}
		}
		free(poleFaktur);
		poleFaktur = NULL;
		fclose(soubor);
	}
	return prvni;
}

void vypisFaktury(tFakturaList* fakturaList)
{
	tFakturaList* aktualni = fakturaList;
	while (aktualni != NULL)
	{
		printf("%s %c %s %d\n", aktualni->faktura.datum, aktualni->faktura.typ, aktualni->faktura.faktura, aktualni->faktura.castka);
		aktualni = aktualni->dalsi;
	}
}

void dealokujFaktury(tFakturaList* fakturaList) {
	tFakturaList* aktualni = fakturaList;
	while (aktualni != NULL)
	{
		tFakturaList* dalsiVPoradi = aktualni->dalsi;
		free(aktualni);
		aktualni = dalsiVPoradi;
	}
}
