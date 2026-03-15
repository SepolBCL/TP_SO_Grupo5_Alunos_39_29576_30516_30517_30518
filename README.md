Interpretador de Comandos - Sistemas Operativos (TP_SO) 🖥️⚙️
Este repositório contém a resolução do Trabalho Prático da Unidade Curricular de Sistemas Operativos.
O projeto consiste no desenvolvimento de um Interpretador de Comandos (uma shell personalizada) em linguagem C, projetado para interagir com o sistema operativo e realizar operações fundamentais de gestão de ficheiros e diretorias através de chamadas ao sistema (system calls).

👥 Equipa de Desenvolvimento - Grupo 5
Aluno nº 39

Aluno nº 29576

Aluno nº 30516

Aluno nº 30517

Aluno nº 30518

✨ Funcionalidades Suportadas
O interpretador permite executar os seguintes comandos (mapeados nos respetivos módulos em C):

📖 Mostrar Ficheiro (mostraFicheiro.c): Lê e apresenta o conteúdo de um ficheiro de texto no terminal.

📋 Copiar Ficheiro (copiaFicheiro.c): Duplica ficheiros de uma origem para um destino.

➕ Acrescentar Conteúdo (acrescentaOrigemDestino.c): Anexa (append) o conteúdo de um ficheiro de origem ao final de um ficheiro de destino.

🔢 Contar Ficheiro (contaFicheiro.c): Efetua a contagem de elementos (como linhas, palavras ou bytes) presentes num ficheiro.

🗑️ Apagar Ficheiro (apagaFicheiro.c): Elimina um ficheiro do sistema de ficheiros.

ℹ️ Informação de Ficheiro (informaFicheiro.c): Apresenta os metadados e as propriedades (tamanho, permissões, etc.) de um ficheiro.

📂 Listar Diretoria (listaDiretoria.c): Lista os ficheiros e subdiretorias presentes num determinado caminho.

📁 Estrutura do Projeto
O repositório está organizado nas seguintes pastas principais:

/Código Fonte/: Contém todo o código C desenvolvido para o projeto, dividido em módulos por cada comando suportado, além do ficheiro principal (interpretador.c) que processa a entrada do utilizador.

Inclui também a Makefile para facilitar e automatizar a compilação do projeto.

/Relatório/: Contém a documentação técnica do projeto (Relatório_TP_SO_Grupo5.pdf), detalhando as decisões de arquitetura, utilização de chamadas ao sistema operativo e manuais de utilização.

🛠️ Tecnologias Utilizadas
Linguagem: C (Standard POSIX / Linux)

Compilador: GCC

Ferramenta de Build: Make

🚀 Como Compilar e Executar Localmente
Para testares este interpretador de comandos na tua máquina (idealmente num ambiente Linux ou WSL), segue os seguintes passos:

Aceder à diretoria do código fonte:

Bash
cd "Código Fonte"
Compilar o projeto:
Utiliza a Makefile disponibilizada para gerar o executável automaticamente:

Bash
make
Executar o interpretador:

Bash
./interpretador
A partir deste momento, estarás dentro da shell do projeto e poderás testar os comandos implementados interagindo diretamente com a linha de comandos.

Limpar ficheiros de compilação:
Se precisares de remover os ficheiros objeto (.o) e o executável gerados, podes correr:

Bash
make clean
Para mais detalhes sobre as restrições, system calls utilizadas e formatação esperada dos argumentos de cada comando, consulta o documento na pasta Relatório.
