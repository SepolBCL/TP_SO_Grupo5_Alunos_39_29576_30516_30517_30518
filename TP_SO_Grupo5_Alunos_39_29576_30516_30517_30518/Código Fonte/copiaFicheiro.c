/**
 * @file copiaFicheiro.c
 * @brief Programa para copiar o conteúdo de um ficheiro para outro.
 *
 * Este programa recebe um ficheiro como argumento e efetua uma cópia do seu conteúdo para outro ficheiro.
 * Se ocorrerem erros durante a abertura, leitura, escrita ou no fecho dos ficheiros, são retornadas mensagens de erro.
 */

#include <unistd.h>        // Funções de sistema write(), read(), close()
#include <fcntl.h>         // Função open() e definições de flags
#include <sys/stat.h>      // Permissões de ficheiros
#include <string.h>

#define BUFFER_SIZE 1024   // Tamanho do buffer usado para leitura e escrita

/**
 * @brief Função principal do programa.
 *
 * @param argc Número de argumentos passados na linha de comandos.
 * @param argv Vetor de argumentos passados na linha de comandos.
 * @return Retorna 0 em caso de sucesso, 1 em caso de erro.
 */
int main(int argc, char *argv[]) 
{
    char buffer[BUFFER_SIZE];   // Buffer para guardar os dados lidos do ficheiro
    ssize_t tam;                // Tamanho dos dados lidos
    int fdInput, fdOutput;      // Descritores de ficheiro para o ficheiro de entrada e de saída

    // Valida se o número de argumentos é o correto
    if (argc != 2) 
    {
        write(2, "Erro: Digite os argumentos: ", 29);
        write(2, argv[0], strlen(argv[0]));
        write(2, " <nome_ficheiro>\n", 18);
        return 1;
    }

    // Abre o ficheiro de entrada para leitura
    fdInput = open(argv[1], O_RDONLY);
    if (fdInput == -1) 
    {
        write(2, "Ficheiro não encontrado\n", 26);
        return 1;
    }

    // Abre ou cria o ficheiro de saída para escrita
    fdOutput = open("ficheiro.copia", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fdOutput == -1) 
    {
        write(2, "Erro na abertura ou na criação do ficheiro de saída\n", 56);
        close(fdInput); 
        return 1;
    }

    // Copia o conteúdo do ficheiro de entrada para o ficheiro de saída
    while ((tam = read(fdInput, buffer, BUFFER_SIZE)) > 0) 
    {
        if (write(fdOutput, buffer, tam) != tam) 
        {
            write(2, "Erro na escrita do ficheiro de saída\n", 39);
            close(fdInput);
            close(fdOutput);
            return 1;
        }
    }

    // Valida se ocorreu algum erro durante a leitura do ficheiro de entrada
    if (tam == -1) 
    {
        write(2, "Erro na leitura do ficheiro de entrada\n", 40);
        close(fdInput);
        close(fdOutput);
        return 1;
    }

    // Fecha os ficheiros de entrada e de saída
    close(fdInput);
    close(fdOutput);

    write(1, "Ficheiro criado com sucesso\n", 28);

    return 0;
}
