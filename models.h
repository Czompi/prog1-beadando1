#pragma once
#include <stdlib.h>
typedef struct verado {
	int id;
	char nev[128];
	char vercsoport[16];
	char email[256];
	int hanyszor;
	char legutolso[11];
}verado;

typedef enum verado_enum {
	verado_id,
	verado_nev,
	verado_vercsoport,
	verado_email,
	verado_hanyszor,
	verado_legutolso
} verado_enum;