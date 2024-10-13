/**
 * @file mostraFicheiro.c
 * @brief Programa para ler o conteúdo de um ficheiro e imprimir no stdout.
 *
 * Abre um ficheiro inserido como arguento, efetua a leitura do seu conteúdo em blocos e escreve os mesmos no stdout.
 * Caso ocorra algum erro durante a leitura, escrita ou no fecho do ficheiro, é retornada uma mensagem de erro.
 */

#include <unistd.h>    // Funções de sistema write(), read(), close()
#include <fcntl.h>     // Função open() e definições de flags
#include <string.h>

#define BUFFER_SIZE 1024  // Tamanho do buffer usado para leitura

/**
 * @brief Função principal do programa.
 *
 * @param argc Número de argumentos passados na linha de comandos.
 * @param argv Vetor de argumentos passados na linha de comandos.
 * @return Retorna 0 em caso de sucesso, 1 em caso de erro.
 */
int main(int argc, char *argv[]) 
{
    char buffer[BUFFER_SIZE]; // Buffer para guardar os dados lidos do ficheiro
    ssize_t tam;              // Tamanho dos dados lidos
    int fd;                   // Descritor de ficheiro

    // Verifica se o número de argumentos é o correto
    if (argc != 2) 
    {
        write(2, "Erro: Digite os argumentos: ", 28);
        write(2, argv[0], strlen(argv[0]));
        write(2, " <nome_ficheiro>\n", 18);
        return 1;
    }

    // Abre o ficheiro para leitura
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        write(2, "Erro na abertura do ficheiro\n", 30);
        return 1;
    }

    // Lê e mostra a informação do ficheiro
    while ((tam = read(fd, buffer, BUFFER_SIZE)) > 0) 
    {
        // Escreve os dados lidos no stdout
        if (write(1, buffer, tam) != tam) 
        {
            write(2, "Erro na escrita no stdout\n", 27);
            close(fd);
            return 1;
        }
    }

    // Valida se ocorreu algum erro durante a leitura do ficheiro
    if (tam == -1) {
        write(2, "Erro na leitura do ficheiro\n", 29);
        close(fd);
        return 1; 
    }

    // Valida se ocorreu algum erro no fecho do ficheiro
    if (close(fd) == -1) 
    {
        write(2, "Erro no fecho do ficheiro\n", 27);
        return 1;
    }

    return 0;  // Sucesso
}
