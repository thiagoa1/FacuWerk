	/* Faça um programa que armazene num arquivo binário uma estrutura contendo os resultados dos jogos de cada time do campeonato brasileiro
(data, adversário, placar e pontos adquiridos). E implemente o seguinte menu:
Escolha:

1) Adicionar um time
2) Eliminar um time
3) Entrar com novo jogo para um time
4) Apagar um jogo de um time
5) Ver todos os resultados de um time
6) Calcular os percentuais de vitória, empate e derrota de um time
7) Imprimir a lista de times ordenada decrescentemente pelos pontos adquiridos */

#include <stdio.h>
#include <string.h>

const int opcaoAdicionarTime = 49; // Caractere 1
const int opcaoEliminarTime = 50; // Caractere 2
const int opcaoAdicionarJogo = 51; // Caractere 3
const int opcaoApagarJogo = 52; // Caractere 4
const int opcaoVerResultados = 53; // Caractere 5
const int opcaoPercentuais = 54; // Caractere 6
const int opcaoImprimir = 55; // Caractere 7
const int opcaoSair = 56; // Caractere 8

const int teclaEnter = 10;

#define TAM 60

struct time {
    char nome[TAM];
    int ativo;
};

struct jogo {
    char mandante[TAM];
    char visitante[TAM];
    int gols_mandante;
    int gols_visitante;
    char data[TAM];
    int ativo;
};

int main(int argc, char** argv) {
    printf("Bem vindo a Tabela do Brasileirao!\n");

    FILE *arquivo_times;
    FILE *arquivo_jogos;

    struct time time_atual;
    struct jogo jogo_atual;

    arquivo_times = fopen("times.dat", "r+b");
    arquivo_jogos = fopen("jogos.dat", "r+b");

    char lista_de_times[TAM][TAM];

    int i, j, k;

    if (arquivo_times == NULL) {
        printf("Erro ao abrir o arquivo de dados!\n");
    } else {
        unsigned int ch;
        do {
            printf("\nSelecione uma opcao:\n");

            printf("1 - Adicionar um time\n");
            printf("2 - Eliminar um time\n");
            printf("3 - Entrar com um novo jogo para um time\n");
            printf("4 - Apagar um jogo de um time\n");
            printf("5 - Ver todos os resultados de um time\n");
            printf("6 - Calcular os percentuais de vitoria, empate e derrota de um time\n");
            printf("7 - Imprimir a lista dos times\n");
            printf("8 - Sair\n");

            if (ch == opcaoAdicionarTime) {
                printf("Adicionando Time\n");
                time_atual.ativo = 1;
                printf("Digite o nome do time a adicionar:\n");
                scanf("%s", time_atual.nome);
                fseek(arquivo_times, sizeof(struct time), SEEK_END);
                fwrite(&time_atual, sizeof(struct time), 1, arquivo_times);

            } else if (ch == opcaoEliminarTime) {
                printf("Eliminando Time\n");
                i = 0;
                rewind(arquivo_times);
                while (fread(&time_atual, sizeof(struct time), 1, arquivo_times) != NULL) {
                    if (time_atual.ativo == 1) {
                        printf("%d - %s\n", i, time_atual.nome);
                        i++;
                    }
                }
                j = 0;

                printf("Digite o numero do time a ser eliminado:\n");
                scanf("%i", &j);
                getchar();

                i = 0;
                k = 0;
                rewind(arquivo_times);
                while (fread(&time_atual, sizeof(struct time), 1, arquivo_times) != NULL) {
                    if (time_atual.ativo == 1) {
                        if (i == j) {
                            fseek(arquivo_times, sizeof(struct time) * k, SEEK_SET);
                            time_atual.ativo = 0;
                            fwrite(&time_atual, sizeof(struct time), 1, arquivo_times);

                            if(ferror(arquivo_times)) {
                                printf("erro");
                            }
                            break;
                        }
                        i++;
                    }
                    k++;
                }
            } else if (ch == opcaoAdicionarJogo) {
                printf("Entrando com um novo jogo\n");
                i = 0;
                rewind(arquivo_times);
                while (fread(&time_atual, sizeof(struct time), 1, arquivo_times) != NULL) {
                    if (time_atual.ativo == 1) {
                        printf("%d - %s\n", i, time_atual.nome);
                        strcpy(lista_de_times[i], time_atual.nome);
                        i++;
                    }
                }

                printf("Digite o numero do time mandante:\n");
                scanf("%i", &i);
                getchar();
                strcpy(jogo_atual.mandante, lista_de_times[i]);

                printf("Digite a quantidade de gols do time mandante:\n");
                scanf("%i", &i);
                getchar();
                jogo_atual.gols_mandante = i;

                printf("Digite o numero do time visitante:\n");
                scanf("%i", &i);
                getchar();
                strcpy(jogo_atual.visitante, lista_de_times[i]);

                printf("Digite a quantidade de gols do time visitante:\n");
                scanf("%i", &i);
                getchar();
                jogo_atual.gols_visitante = i;

                printf("Digite a data do jogo:\n");
                scanf("%s", jogo_atual.data);

                jogo_atual.ativo = 1;

                fseek(arquivo_jogos, sizeof(struct jogo), SEEK_END);
                fwrite(&jogo_atual, sizeof(struct jogo), 1, arquivo_jogos);
            } else if (ch == opcaoApagarJogo) {
                printf("Apagando um jogo\n");
                i = 0;
                rewind(arquivo_jogos);
                while (fread(&jogo_atual, sizeof(struct jogo), 1, arquivo_jogos) != NULL) {
                    if (jogo_atual.ativo == 1) {
                        printf("%d - %s %d x %d %s \n", i, jogo_atual.mandante, jogo_atual.gols_mandante, jogo_atual.gols_visitante, jogo_atual.visitante);
                        i++;
                    }
                }

                printf("Digite o numero do jogo a ser apagado:\n");
                scanf("%i", &j);
                getchar();

                i = 0;
                k = 0;
                rewind(arquivo_jogos);
                while (fread(&jogo_atual, sizeof(struct jogo), 1, arquivo_jogos) != NULL) {
                    if (jogo_atual.ativo == 1) {
                        if (i == j) {
                            fseek(arquivo_jogos, sizeof(struct jogo) * k, SEEK_SET);
                            jogo_atual.ativo = 0;
                            fwrite(&jogo_atual, sizeof(struct jogo), 1, arquivo_jogos);

                            if(ferror(arquivo_times)) {
                                printf("erro");
                            }

                            break;
                        }
                        i++;
                    }
                    k++;
                }
            } else if (ch == opcaoVerResultados) {
                printf("Resultado dos jogos\n");

                i = 0;
                rewind(arquivo_times);
                while (fread(&time_atual, sizeof(struct time), 1, arquivo_times) != NULL) {
                    if (time_atual.ativo == 1) {
                        printf("%d - %s\n", i, time_atual.nome);
                        strcpy(lista_de_times[i], time_atual.nome);
                        i++;
                    }
                }

                j = 0;
                printf("Digite o numero do time:\n");
                scanf("%i", &j);
                getchar();

                rewind(arquivo_jogos);
                while (fread(&jogo_atual, sizeof(struct jogo), 1, arquivo_jogos) != NULL) {
                    if (jogo_atual.ativo == 1 && (strcmp(lista_de_times[j], jogo_atual.mandante) == 0 || strcmp(lista_de_times[j], jogo_atual.visitante) == 0)) {
                        printf("%d - %s %d x %d %s \n", i, jogo_atual.mandante, jogo_atual.gols_mandante, jogo_atual.gols_visitante, jogo_atual.visitante);
                    }
                }

            } else if (ch == opcaoPercentuais) {
                printf("Percentuais de vitorias, empates e derrotas\n");

                i = 0;
                rewind(arquivo_times);
                while (fread(&time_atual, sizeof(struct time), 1, arquivo_times) != NULL) {
                    if (time_atual.ativo == 1) {
                        printf("%d - %s\n", i, time_atual.nome);
                        strcpy(lista_de_times[i], time_atual.nome);
                        i++;
                    }
                }

                j = 0;
                printf("Digite o numero do time:\n");
                scanf("%i", &j);
                getchar();

                rewind(arquivo_jogos);
                int vitorias = 0;
                int derrotas = 0;
                int empates = 0;
                while (fread(&jogo_atual, sizeof(struct jogo), 1, arquivo_jogos) != NULL) {
                    if (jogo_atual.ativo == 1) {
                        if (strcmp(lista_de_times[j], jogo_atual.mandante) == 0) {
                            if (jogo_atual.gols_mandante > jogo_atual.gols_visitante) {
                                vitorias++;
                            }
                            if (jogo_atual.gols_mandante < jogo_atual.gols_visitante) {
                                derrotas++;
                            }
                            if (jogo_atual.gols_mandante == jogo_atual.gols_visitante) {
                                empates++;
                            }
                        }
                        if (strcmp(lista_de_times[j], jogo_atual.visitante) == 0) {
                            if (jogo_atual.gols_visitante > jogo_atual.gols_mandante) {
                                vitorias++;
                            }
                            if (jogo_atual.gols_visitante < jogo_atual.gols_mandante) {
                                derrotas++;
                            }
                            if (jogo_atual.gols_visitante == jogo_atual.gols_mandante) {
                                empates++;
                            }
                        }
                    }
                }
                int total_de_jogos = vitorias + empates + derrotas;

                float per_vitorias = 0;
                float per_derrotas = 0;
                float per_empates = 0;

                if (total_de_jogos > 0) {
                    per_vitorias = 100 * vitorias / total_de_jogos;
                    per_derrotas = 100 * derrotas / total_de_jogos;
                    per_empates = 100 * empates / total_de_jogos;
                }

                printf("Total de jogos: %i\n", total_de_jogos);
                printf("Percentual de vitorias: %.2f\n", per_vitorias);
                printf("Percentual de derrotas: %.2f\n", per_derrotas);
                printf("Percentual de empates: %.2f\n", per_empates);
            } else if (ch == opcaoImprimir) {
                printf("Lista dos times\n");

                /*
                i = 0;

                
                rewind(arquivo_times);
                while (fread(&time_atual, sizeof(struct time), 1, arquivo_times) != NULL) {
                    if (time_atual.ativo == 1) {
                        printf("%d - %s\n", i, time_atual.nome);
                        i++;
                    }
                }*/
                i = 0;
                rewind(arquivo_times);
                while (fread(&time_atual, sizeof(struct time), 1, arquivo_times) != NULL) {
                    if (time_atual.ativo == 1) {
                        strcpy(lista_de_times[i], time_atual.nome);
                        i++;
                    }
                }

                int pontos[i];
                for (j = 0; j < i; j++) {
                    pontos[j] = 0;
                }

                rewind(arquivo_jogos);
                while (fread(&jogo_atual, sizeof(struct jogo), 1, arquivo_jogos) != NULL) {
                    if (jogo_atual.ativo == 1) {
                        for (j = 0; j < i; j++) {
                            if (strcmp(lista_de_times[j], jogo_atual.mandante) == 0) {
                                if (jogo_atual.gols_mandante > jogo_atual.gols_visitante) {
                                    pontos[j] += 3;
                                }
                                if (jogo_atual.gols_mandante == jogo_atual.gols_visitante) {
                                    pontos[j] += 1;
                                }
                            } else if (strcmp(lista_de_times[j], jogo_atual.visitante) == 0) {
                                if (jogo_atual.gols_visitante > jogo_atual.gols_mandante) {
                                    pontos[j] += 3;
                                }
                                if (jogo_atual.gols_visitante == jogo_atual.gols_mandante) {
                                    pontos[j] += 1;
                                }
                            }
                        }
                    }
                }

                int swap_pontos;
                char swap_time[TAM];

                for (j = 0 ; j < i - 1; j++) {
                    for (k = 0 ; k < i - j - 1; k++) {
                        if (pontos[k] < pontos[k + 1]) {
                            swap_pontos  = pontos[k];
                            strcpy(swap_time, lista_de_times[k]);

                            pontos[k] = pontos[k + 1];
                            strcpy(lista_de_times[k], lista_de_times[k + 1]);

                            pontos[k + 1] = swap_pontos;
                            strcpy(lista_de_times[k + 1], swap_time);
                        }
                    }
                }

                for (j = 0; j < i; j++) {
                    printf("%d - %s - %d\n", j, lista_de_times[j], pontos[j]);
                }

            } else if (ch == opcaoSair) {
                printf("Obrigado por utilizar a Tabela do Brasileirao\n");
                break;
            } else if (ch == teclaEnter) {
                // Faz nada
            } else {
                printf("Opcao Inexistente\n");
            }
            fflush(NULL);
        } while((ch = getchar()) != EOF);
    }

    return (0);
}
