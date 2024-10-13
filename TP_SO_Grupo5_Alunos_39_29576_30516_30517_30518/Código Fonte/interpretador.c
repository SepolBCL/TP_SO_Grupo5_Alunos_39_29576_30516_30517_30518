/**
 * @file Interpretador.c
 * @brief Implementação de um interpretador simples que executa comandos básicos.
 *
 * Este programa implementa um interpretador que lê comandos do utilizador e executa comandos específicos ou ficheiros executáveis disponíveis no diretório atual.
 * Os comandos disponíveis incluem:
 * - mostra
 * - copia
 * - acrescenta
 * - conta
 * - apaga
 * - informa
 * - lista
 * - termina
 * - help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define MAX_LENGTH 1024 // Tamanho máximo do buffer para comandos.

/**
 * @brief Função principal do interpretador.
 *
 * Esta função implementa um loop que lê comandos do utilizador, analisa os comandos e executa-os utilizando um processo filho. 
 * Comandos reconhecidos são executados a partir de ficheiros executáveis na mesma diretoria ou são comandos internos como "help" e "termina".
 * 
 * @return int Código de retorno do programa: 0 em caso de sucesso.
 */
int main() 
{
    char comando[MAX_LENGTH];
    char *args[MAX_LENGTH / 2];
    int status;
    char prompt[] = "% ";

    while (1) 
    {
        // Exibe a linha de comandos do interpretador
        write(1, prompt, strlen(prompt));

        // Lê o comando do utilizador
        if (fgets(comando, MAX_LENGTH, stdin) == NULL) 
        {
            write(2, "Erro na leitura do comando\n", 28);
            continue;
        }

        // Remove o caractere de nova linha
        comando[strcspn(comando, "\n")] = 0;
		
		
        // Verifica se o comando está vazio
        if (comando[0] == '\0') 
        {
            continue; // Ignora e volta ao 'prompt'
        }

        // Verifica se o comando é "termina"
        if (strcmp(comando, "termina") == 0) 
        {
            break;
        }

        // Verifica se o comando é "help"
        if (strcmp(comando, "help") == 0) 
        {
            write(1, "Comandos disponíveis:\n", 24);
            write(1, "- mostra\n", 10);
            write(1, "- copia\n", 9);
            write(1, "- acrescenta\n", 14);
            write(1, "- conta\n", 9);
            write(1, "- apaga\n", 9);
            write(1, "- informa\n", 11);
            write(1, "- lista\n", 9);
            write(1, "- termina\n", 11);
            continue;
        }

        // Divide o comando em argumentos
        int i = 0;
        args[i] = strtok(comando, " ");
        while (args[i] != NULL) 
        {
            args[++i] = strtok(NULL, " ");
        }

        // Verifica se o comando é reconhecido
        if (strcmp(args[0], "mostra") != 0 &&
            strcmp(args[0], "copia") != 0 &&
            strcmp(args[0], "acrescenta") != 0 &&
            strcmp(args[0], "conta") != 0 &&
            strcmp(args[0], "apaga") != 0 &&
            strcmp(args[0], "informa") != 0 &&
            strcmp(args[0], "lista") != 0) 
        {
            write(2, "Comando não reconhecido\n", 26);
            write(1, "\nDigite 'help' para verificar comandos disponíveis\n", 53);
            continue;
        }

        // Cria um novo processo
        pid_t pid = fork();
        if (pid == -1) 
        {
            write(2, "Erro na criação de um novo processo\n", 39);
        } 
        else if (pid == 0) 
        {
            // Processo filho: executa o comando
            char path[MAX_LENGTH];
            sprintf(path, "./%s", args[0]); // Assume que o comando é um ficheiro na mesma diretoria
            if (execv(path, args) == -1) 
            {
                write(2, "Erro na execução do comando\n", 31);
                exit(EXIT_FAILURE);
            }
        } 
        else 
        {
            // Processo pai: espera que o processo filho termine
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) 
            {
                char output[MAX_LENGTH];
                sprintf(output, "Terminou o comando %s com código %d\n", args[0], WEXITSTATUS(status));
                write(1, output, strlen(output));
            }
        }
    }

    return 0;
}