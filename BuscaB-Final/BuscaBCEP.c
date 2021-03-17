#include <stdio.h>
#include <string.h> 

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char**argv)
{
	FILE *f;
    Endereco e;
    if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	f = fopen("cep_ordenado.dat","r"); 
    fseek(f,0,SEEK_END);
    long tamanhoArquivo = ftell(f); 
    rewind(f); 
    printf("Tamanho do Arquivo: %ld\n", tamanhoArquivo);
	printf("Tamanho do Registro: %ld\n", sizeof(Endereco));
	printf("Tamanho do Arquivo em Registros: %ld\n", tamanhoArquivo/sizeof(Endereco));
   
    int primeiro = 0 ; 
	int ultimo = tamanhoArquivo/sizeof(Endereco); 
	int meio;

    int c = 0;

    while(primeiro <= ultimo)
	{   
		
		meio=(primeiro+ultimo)/2;
		printf("M %d\n",meio);
        c++;
        fseek(f, meio * sizeof(Endereco), SEEK_SET);    
        fread(&e,sizeof(Endereco),1,f);
		if(strncmp(argv[1],e.cep,8)==0)
		{   
            printf("Posicao Atual: %ld\n", ftell(f));
			printf("\n%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;

		}else if(strncmp(argv[1],e.cep,8) > 0){

            primeiro = meio + 1;
			

        }else if(strncmp(argv[1],e.cep,8) < 0 ){
            
            ultimo = meio - 1;
			

        }
		
	}

    printf("\nTotal Lido: %d\n", c);

    fclose(f);
    return 0;
}
