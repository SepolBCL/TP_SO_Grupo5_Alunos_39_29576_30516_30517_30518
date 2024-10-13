/**
 * @file contaficheiro.c
 * @brief Programa para contar o número de linhas de um ficheiro.
 *
 * Este programa recebe o nome de um ficheiro como argumento e conta o número de linhas que consta no ficheiro.
 * O programa imprime o número total de linhas no ficheiro no stdout.
 * Se existirem erros durante a abertura, leitura ou fecho do ficheiro, são devolvidas mensagens de erro.
 */

#include <unistd.h>   // Função write() e descritor de ficheiro STDERR
#include <fcntl.h>    // Função open() e definições de flags
#include <string.h>

/**
 * @brief Função principal do programa.
 *
 * @param argc Número de argumentos passados na linha de comandos.
 * @param argv Vetor de argumentos passados na linha de comandos.
 * @return Retorna 0 em caso de sucesso, 1 em caso de erro.
 */
int main(int argc, char *argv[]) 
{
    // Verifica se o número de argumentos é o correto
    if (argc != 2) {
        write(2, "Erro: Digite os argumentos: ", 29);
        write(2, argv[0], strlen(argv[0]));
        write(2, " <nome_ficheiro>\n", 18);
        return 1;
    }

    int fd, temp;
    char ch;
    int numLinhas = 0;

    // Abertura do ficheiro para leitura
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) 
    {
        write(2, "Erro na abertura do ficheiro\n", 30); 
        return 1;
    }

    // Ciclo para a leitura do ficheiro caractere a caractere e para contar o número de linhas
    while (read(fd, &ch, 1) == 1) 
    {
        if (ch == '\n') 
        {
            numLinhas++;
        }
    }

    // Fecho do ficheiro
    if (close(fd) == -1) 
    {
        write(2, "Erro no fecho do ficheiro\n", 27);
        return 1;
    }

    // Adiciona linha extra
    numLinhas++;

    // Converte o número de linhas para uma string
    char linhaString[20];
    int len = 0;
    temp = numLinhas;
    do 
    {
        linhaString[len++] = temp % 10 + '0';
        temp /= 10;
    } while (temp);

    // Escreve a string relativa ao número de linhas, invertida no terminal
    for (int i = len - 1; i >= 0; i--) 
    {
        write(1, &linhaString[i], 1);
    }
    write(1, "\n", 1);

    return 0;
}
