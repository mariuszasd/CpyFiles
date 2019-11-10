#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define MAX 47

int main(int argc, char* argv[]){
	char* buf;
	int desc_zrod, desc_cel;
	int lbajt;
	int  rozm;

	if (argc<3){
		fprintf(stderr, "Za malo argumentow. Uzyj: \n");
		fprintf(stderr, "%s <plik zrodlowy> <plik docelowy>\n", argv[0]);
		exit(1);
	}

	desc_zrod = open(argv[1], O_RDONLY);
	if(desc_zrod == -1){
		perror("Blad otwarcia pliku zrodlowego");
		exit(1);
	}

	rozm = lseek(desc_zrod, 0, SEEK_END);
	if (rozm == -1){
		perror("Blad lseek");
		exit(1);
	}

	lseek(desc_zrod, 0, SEEK_SET);
        
	desc_cel = creat(argv[2], 0640);
	if (desc_cel == -1){
		perror("Blad otwarcia pliku docelowego.");
		exit(1);
	}
	
	buf = (char*) malloc(rozm);
	printf("Rozmiar pliku  zrodlowego : %ld \n", rozm);

	while ((lbajt = read(desc_zrod, buf, rozm)) > 0){
		if (write(desc_cel, buf, lbajt) == -1){
			perror("Blad zapisu pliku docelowego.");
			exit(1);
		}
	}
	
	if (lbajt == -1){
		perror("Blad odczytu pliku zrodlowego.");
		exit(1);
	}

	if (close(desc_zrod) == -1 || close(desc_cel) ==-1){
		perror("Blad zamkniecia pliku.");
		exit(1);
	}
	free(buf);
	exit(1);
}
