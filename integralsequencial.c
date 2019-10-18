/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho 1 - Implementação Sequencial */
/*Desenvolvido por : Matheus Abrantes e Paloma Calado*/
/*Turma 2019.2*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Função quadratura adaptativa auxiliar*/
double quadAdaptativaAux(double (*f)(double),double a, double b,double eMax,
                         double area,double fa,double fb, double altura){

  double m, m1,m2;
  double area2, area3 ;
  double fd,fe, erro;
  /*Cálculo do ponto médio no intervalo [a,b]*/
  m = (a+b)/2;
  /*Cálculo da altura do retâgulo maior*/
  altura = f(m);

  /*ponto médio dos retângulos menores*/
  m1 = (a+m)/2;
  m2 = (m+b)/2;

  /*altura dos retângulos menores*/
  fd = f(m1);
  fe = f(m2);


  /*calcula a área do retângulo à esquerda*/
  area2 = (m-a)*fd;
  /*Calcula a área do retângulo à direita*/
  area3 = (b-m)*fe;

  /*calcula o erro pela diferença da área do trianjgulo grande e a soma dos triandulos menores*/
  erro = area - (area2+area3);

  /*caso o erro seja menor que o erro máximo, retorna o valor da integral*/
  if(fabs(erro) <= eMax)
    return area + area3;
  /*Caso contrário chama a mesma função para os triangulos menores*/
  else
   return quadAdaptativaAux(f,a,m,eMax/2,area2,fa,altura,fd) +
          quadAdaptativaAux(f,a,m,eMax/2,area3,altura,fb,fe);

}

double quadAdaptativa (double (*f)(double), double a, double b, double erro){

  double m, altura;
  double fa,fb;
  double area;

  /*calcula o ponto médio do retângulo maior*/
  m = (a+b)/2;
  /*calcula os valores de f nos pontos a e b*/
  fa = f(a);
  fb = f(b);
  /**/
  altura = f(m);
  /*Calcula a área do retângulo grande*/
  area = (b-a)*altura;

   return quadAdaptativaAux(f,a,b,erro,area,fa,fb,altura);
}

int main(int argc, char const *argv[]) {


  double I = quadAdaptativa(sin, 0, 1, 0.000000001); // calcular a integral de sin(x)
                                                          // de 0 a 1 e armazenar na
                                                          // nova variável I
 printf("I = %lf\n",I); // print the result
 return 0;
}
