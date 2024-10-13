/**
 * @file informaFicheiro.c
 * @brief Programa para imprimir as informações detalhadas sobre um ficheiro.
 *
 * Imprime o tipo, inode, proprietário e datas relevantes (criação, última leitura e última modificação) de um ficheiro.
 */

#include <unistd.h>    // Funções de sistema write() e outras chamadas do sistema UNIX
#include <fcntl.h>     // Definições de controlo de ficheiros
#include <sys/stat.h>  // Estrutura stat e as definições de modo de ficheiro
#include <sys/types.h> // Tipos de dados específicos do sistema
#include <pwd.h>       // Função getpwuid() e a estrutura passwd
#include <time.h>      // Função ctime() e a estrutura time_t
#include <stdlib.h>    // Função exit()
#include <string.h>    // Função strlen()

/**
 * @brief Função principal do programa.
 *
 * @param argc Número de argumentos passados na linha de comando.
 * @param argv Vetor de argumentos passados na linha de comando.
 * @return Retorna 0 em caso de sucesso, 1 em caso de erro.
 */
int main(int argc, char *argv[]) 
{
    // Verifica se o argumento do ficheiro foi passado
    if (argc < 2) 
    {
        write(2, "Erro: Digite os argumentos: ", 29);
        write(2, argv[0], strlen(argv[0]));
        write(2, " nome_ficheiro\n", 16);
        return 1;
    }

    char *filename = argv[1];
    struct stat file_info;

    // Informações sobre o ficheiro
    if (stat(filename, &file_info) == -1) 
    {
        const char *error = "Erro na leitura das informações do ficheiro\n";
        write(2, error, 47);
        return 1;
    }

    // Determina e imprime o tipo do ficheiro
    if (S_ISREG(file_info.st_mode))
        write(1, "Tipo de ficheiro: Ficheiro regular\n", 36);
    else if (S_ISDIR(file_info.st_mode))
        write(1, "Tipo de ficheiro: Diretoria\n", 29);
    else if (S_ISLNK(file_info.st_mode))
        write(1, "Tipo de ficheiro: Link\n", 24);
    else if (S_ISCHR(file_info.st_mode))
        write(1, "Tipo de ficheiro: Ficheiro especial de caracteres\n", 51);
    else if (S_ISBLK(file_info.st_mode))
        write(1, "Tipo de ficheiro: Ficheiro especial de blocos\n", 47);
    else
        write(1, "Tipo de ficheiro: Outro\n", 25);

    // Converte e imprime o inode do ficheiro
    write(1, "Inode do ficheiro: ", 20);
    char inode_str[20];
    int inode_length = 0;
    int temp_inode = file_info.st_ino;
    if (temp_inode == 0) 
    {
        inode_str[0] = '0';
        inode_length = 1;
    } else 
    {
        while (temp_inode != 0) 
        {
            inode_str[inode_length++] = (temp_inode % 10) + '0';
            temp_inode /= 10;
        }
    }
    for (int i = inode_length - 1; i >= 0; i--) 
    {
        write(1, &inode_str[i], 1);
    }
    write(1, "\n", 1);

    // Determina e imprime o Proprietário do ficheiro
    struct passwd *pw = getpwuid(file_info.st_uid);
    if (pw != NULL) 
    {
        const char *owner = "Proprietário do ficheiro: ";
        write(1, owner, 28);
        write(1, pw->pw_name, strlen(pw->pw_name));
        write(1, "\n", 1);
    } else {
        char uid_str[20];
        int uid_length = 0;
        int temp_uid = file_info.st_uid;
        if (temp_uid == 0) 
        {
            uid_str[0] = '0';
            uid_length = 1;
        } else 
        {
            while (temp_uid != 0) 
            {
                uid_str[uid_length++] = (temp_uid % 10) + '0';
                temp_uid /= 10;
            }
        }
        for (int i = uid_length - 1; i >= 0; i--) 
        {
            write(1, &uid_str[i], 1);
        }
        write(1, "\n", 1);
    }

    // Imprime a data de criação do ficheiro
    const char *creation = "Data da criação do ficheiro: ";
    write(1, creation, 32);
    write(1, ctime(&file_info.st_ctime), 24);

    // Imprime a data da última leitura do ficheiro
    const char *access = "\nData da última leitura do ficheiro: ";
    write(1, access, 39);
    write(1, ctime(&file_info.st_atime), 24);

    // Imprime a data da última modificação do ficheiro
    const char *modification = "\nData da última modificação do ficheiro: ";
    write(1, modification, 45);
    write(1, ctime(&file_info.st_mtime), 24);
    write(1, "\n", 1);
    
    return 0;
}
