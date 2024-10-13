/**
 * @file apagaFicheiro.c
 * @brief Programa para eliminar um ficheiro.
 *
 * Este programa recebe o nome de um ficheiro como argumento e procede à sua eliminação.
 * Se o ficheiro for eliminado com sucesso, é retornada uma mensagem de sucesso. Caso contrário, retorna uma mensagem de erro.
 */

#include <unistd.h>   // Função write() e descritor de ficheiro STDERR
#include <stdio.h>    // Acesso à função remove() e descritor de ficheiro STDOUT
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
    // Verifica se o número de argumentos é correto
    if (argc != 2) 
    {
        write(2, "Erro: Digite os argumentos: ", 29);
        write(2, argv[0], strlen(argv[0]));
        write(2, " <nome_ficheiro>\n", 18);
        return 1;
    }

    // Elimina o ficheiro passado como argumento
    if (unlink(argv[1]) == -1) 
    {
        write(2, "Erro na eliminação do ficheiro\n", 34);
        return 1;
    }

    write(1, "Eliminação do ficheiro efetuada com sucesso\n", 47);

    return 0;
}
