#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){
  srand(time(NULL));

  if (argc<1)
    exit(-1);
  int n = atoi(argv[1]);
  int densite = 50; // Densité du graphe =  %age de chance qu'une arête soit présente

  FILE * fp = fopen("alea.dat", "w");

  fprintf(fp, "/* Graphe généré avec %i sommets */\n\n", n);
  fprintf(fp, "data;\n");
  fprintf(fp, "param n:=%i;\n\n", n);
  fprintf(fp, "set E :=\n");

  for(int i = 0; i < n; i++)
    for(int j = 0; j<i; j++){
      int alea = rand()%100;
      if(alea < 40){
	fprintf(fp, "\t%i\t%i\n", i+1, j+1);
	fprintf(fp, "\t%i\t%i\n", j+1, i+1);	
      }
      
    }
  fprintf(fp, "\t;\n");
  fprintf(fp, "end;\n");
  fclose(fp);
  
  return 0;
}
