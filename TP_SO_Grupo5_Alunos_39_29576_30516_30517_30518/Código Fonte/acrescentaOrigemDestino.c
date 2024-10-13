/**
 * @file acrescentaOrigemDestino.c
 * @brief Programa para copiar o conteúdo de um ficheiro de origem para um ficheiro de destino, com opção de append.
 *
 * Este programa abre um ficheiro de origem para leitura e um ficheiro de destino para escrita (com opção de append).
 * Lê o conteúdo do ficheiro de origem em blocos de 1024 bytes e escreve no ficheiro de destino.
 */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024  // Tamanho do buffer para leitura e escrita

/**
 * @brief Função principal do programa.
 *
 * @param argc Número de argumentos passados para o programa.
 * @param argv Array de strings contendo os argumentos.
 * @return int Código de retorno do programa: 0 em caso de sucesso, 1 em caso de erro.
 */
int main(int argc, char *argv[]) 
{
    // Verifica se o número de argumentos é correto
    if (argc != 3) 
    {
        write(2, "Erro: Digite os argumentos: ", 29);
        write(2, argv[0], strlen(argv[0]));
        write(2, " nome_ficheiro_origem nome_ficheiro_destino\n", 45);
        return 1;
    }

    int fdInput, fdOutput;
    ssize_t tamLeitura, tamEscrita;
    char buffer[BUFFER_SIZE];

    // Abertura do ficheiro de entrada para leitura
    fdInput = open(argv[1], O_RDONLY);
    if (fdInput == -1) 
    {
        write(2, "Erro na abertura do ficheiro de entrada\n", 41);
        return 1;
    }

    // Abertura ou criação do ficheiro de saída para escrita (opção O_APPEND)
    fdOutput = open(argv[2], O_WRONLY | O_APPEND);
    if (fdOutput == -1) 
    {
        write(2, "Erro na abertura ou na criação do ficheiro de saída\n", 56);
        close(fdInput); 
        return 1;
    }

    // Leitura do conteúdo do ficheiro de entrada e escreve no ficheiro de saída
    while ((tamLeitura = read(fdInput, buffer, BUFFER_SIZE)) > 0) 
    {
        tamEscrita = write(fdOutput, buffer, tamLeitura);
        if (tamEscrita != tamLeitura) 
        {
            write(2, "Erro na escrita do ficheiro de saída\n", 39);
            close(fdInput);
            close(fdOutput);
            return 1;
        }
    }

    // Valida se ocorreu algum erro durante a leitura do ficheiro de entrada
    if (tamLeitura == -1) 
    {
        write(2, "Erro na leitura do ficheiro de entrada\n", 40);
        close(fdInput);
        close(fdOutput);
        return 1;
    }

    // Fecho dos ficheiros de entrada e saída
    if (close(fdInput) == -1) 
    {
        write(2, "Erro no fecho do ficheiro de entrada\n", 38);
        return 1;
    }

    if (close(fdOutput) == -1) 
    {
        write(2, "Erro no fecho do ficheiro de saída\n", 37);
        return 1;
    }

    // Caso não existam erros, indica que os dados foram inseridos com sucesso
    write(1, "Dados inseridos com sucesso\n", 29);

    return 0;  // Sucesso
}