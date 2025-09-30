# LSH - Simple Shell Implementation

Este projeto é uma implementação simples de um **shell em C**, chamada **LSH (Little SHell)**.  
O objetivo é fornecer um exemplo educacional de como um interpretador de linha de comando pode ser implementado a partir do zero, lidando com entrada do usuário, parsing de argumentos, execução de comandos internos e externos, além de manipulação de processos com `fork` e `exec`.

---

## ✨ Funcionalidades

- **Prompt interativo** (`> `).
- **Comandos internos (built-ins):**
  - `cd <diretório>` → Muda o diretório atual.
  - `pwd` → Mostra o diretório atual.
  - `help` → Lista os comandos internos disponíveis.
  - `exit` → Encerra o shell.
- **Execução de programas externos** (exemplo: `ls`, `echo`, `cat`, etc).
- **Tratamento de erros** para comandos inválidos, falhas de alocação e execução.
- **Gerenciamento de processos** usando `fork()`, `execvp()` e `waitpid()`.

## Installation

1. clone this repository
```bash
git clone https://github.com/CincoFolha/shell.git
cd shell
```
2. compilation
```bash
gcc shell.c -o shell
```
## Usage

```bash
./shell
>help
```
