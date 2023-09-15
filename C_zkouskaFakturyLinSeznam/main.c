#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "faktury.h"

int main() {
	tFakturaList* prvkyListu = nactiFaktury("faktury.bin", vydana, srpen);
	vypisFaktury(prvkyListu);

	return 0;
}