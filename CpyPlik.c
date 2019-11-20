#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define L_BYTE 1

int main(int argc, char* argv[]){

	char buf;
	int desc_zrod, desc_cel;
	int odczytane_bajt;

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
        
	desc_cel = creat(argv[2], 0640);
	if (desc_cel == -1){
		perror("Blad otwarcia pliku docelowego.");
		exit(1);
	}
		
	while ((odczytane_bajt = read(desc_zrod, &buf, L_BYTE)) != 0){
		if (write(desc_cel, &buf, odczytane_bajt) == -1){
			perror("Blad zapisu pliku docelowego.");
			exit(1);
		}
	}

	if (odczytane_bajt == -1){
		perror("Blad odczytu pliku zrodlowego.");
		exit(1);
	}

	if (close(desc_zrod) == -1 || close(desc_cel) ==-1){
		perror("Blad zamkniecia pliku.");
		exit(1);
	}

	exit(1);
}
