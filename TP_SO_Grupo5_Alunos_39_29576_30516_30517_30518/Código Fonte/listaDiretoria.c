/**
 * @file listaDiretoria.c
 * @brief Programa para listar o conteúdo de uma diretoria.
 *
 * Este programa recebe o caminho de um diretório como argumento da linha de comandos e lista o conteúdo desse diretório, incluindo ficheiros e subdiretórios.
 * Se nenhum caminho for fornecido, o programa lista o conteúdo do diretório atual.
 * O programa exibe o tipo de cada item listado (diretório ou ficheiro) e o seu nome.
 * Se existirem erros durante a abertura ou leitura do diretório, são devolvidas mensagens de erro.
 */

#include <unistd.h>     // Função write() e ao descritor de ficheiro STDERR
#include <dirent.h>     // Funções relacionadas a diretórios
#include <stdio.h>      // Função printf()
#include <string.h>     // Funções relacionadas a strings
#include <sys/stat.h>   // Struct stat e às funções relacionadas a atributos de ficheiros

#define PATH_MAX_LEN 1024  // Tamanho máximo do caminho de um ficheiro

/**
 * @brief Função principal do programa.
 *
 * @param argc Número de argumentos passados na linha de comandos.
 * @param argv Vetor de argumentos passados na linha de comandos.
 * @return Retorna 0 em caso de sucesso, 1 em caso de erro.
 */
int main(int argc, char *argv[]) 
{
    const char *path;   // Caminho do diretório que será listado

    // Verifica se o número de argumentos é correto
    if (argc == 2) 
    {
        path = argv[1];  // Se fornecido um caminho como argumento, usa esse caminho
    } else if (argc == 1) 
    {
        path = ".";      // Se nenhum caminho for fornecido, usa o diretório atual
    } else {
        // Se o número de argumentos for inválido, devolve uma mensagem para passar os argumentos corretos
        write(2, "Erro: Digite os argumentos: ", 29);
        write(2, argv[0], strlen(argv[0]));
        write(2, "\n", 1);
        return 1;
    }

    // Abre o diretório especificado
    DIR *dir = opendir(path);
    if (!dir) 
    {
        // Se ocorrer um erro ao abrir o diretório, imprime uma mensagem de erro
        write(2, "Erro ao abrir diretoria\n", 25);
        return 1;
    }

    struct dirent *entry;  // Estrutura para guardar informações sobre os itens do diretório
    while ((entry = readdir(dir))) 
    {
        // Ignora as entradas '.' e '..'
        if (entry->d_name[0] == '.' && (entry->d_name[1] == '\0' || entry->d_name[1] == '.'))
            continue;

        char full_path[PATH_MAX_LEN];    // Caminho completo para o item do diretório
        size_t path_len = strlen(path);  // Comprimento do caminho do diretório
        size_t name_len = strlen(entry->d_name);  // Comprimento do nome do item do diretório
        if (path_len + name_len + 2 > PATH_MAX_LEN) 
        {
            // Se o caminho for muito extenso, imprime uma mensagem de erro
            write(2, "Caminho muito extenso\n", 20);
            closedir(dir);
            return 1;
        }
        strcpy(full_path, path);                // Copia o caminho do diretório para o caminho completo
        full_path[path_len] = '/';              // Insere uma barra no final do caminho
        strcpy(full_path + path_len + 1, entry->d_name);  // Insere o nome do item do diretório no final do caminho
        full_path[path_len + name_len + 1] = '\0';       // Insere um terminador de string no final do caminho completo

        struct stat file_stat;  // Estrutura para guardar informações sobre o item do diretório
        if (lstat(full_path, &file_stat) == -1) return 1;  // Determina as informações do item do diretório

        // Determina o tipo do item (diretório ou ficheiro) e exibe-o juntamente com o nome
        const char *type = S_ISDIR(file_stat.st_mode) ? "[diretoria]" : "[ficheiro]";
        write(1, type, strlen(type));
        write(1, " ", 1);
        write(1, entry->d_name, strlen(entry->d_name));
        write(1, S_ISDIR(file_stat.st_mode) ? "/" : "", S_ISDIR(file_stat.st_mode) ? 1 : 0);
        write(1, "\n", 1);
    }

    closedir(dir);
    return 0;
}
