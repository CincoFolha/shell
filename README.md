# 🐚 LSH — Little Shell

Uma implementação educacional de um shell minimalista em **C**, desenvolvida para demonstrar conceitos fundamentais de interpretadores de linha de comando e gerenciamento de processos em sistemas Unix/Linux.

## 📖 Sobre o Projeto

**LSH (Little SHell)** é um shell simples desenvolvido em C com propósito educacional. O projeto busca apresentar, de forma prática, como funciona a estrutura básica de um interpretador de comandos e como ele interage com o sistema operacional.

Entre os principais conceitos abordados estão:

* 📝 Leitura e parsing da entrada do usuário
* 🔧 Execução de comandos built-in
* ⚙️ Criação e gerenciamento de processos com `fork()`
* 🚀 Execução de programas com `execvp()`
* ⏳ Sincronização de processos com `waitpid()`
* 📂 Manipulação do diretório de trabalho com `chdir()`
* 🔗 Interação com o sistema operacional por meio de system calls
* 💾 Gerenciamento dinâmico de memória

O código foi mantido propositalmente simples e organizado para facilitar o estudo e a compreensão dos conceitos envolvidos na implementação de shells como **Bash**, **Zsh** e **Fish**.

## ✨ Funcionalidades

Atualmente, o LSH oferece:

* Execução de programas externos disponíveis no `PATH`
* Comando `cd`
* Comando `pwd`
* Comando `help`
* Comando `exit`
* Suporte a `Ctrl+D` para encerrar o shell
* Suporte a `Ctrl+C` para interromper programas em execução
* Parsing de argumentos separados por espaços e tabs

### Comandos built-in

| Comando          | Descrição                           |
| ---------------- | ----------------------------------- |
| `cd [diretório]` | Altera o diretório atual            |
| `pwd`            | Exibe o diretório de trabalho atual |
| `help`           | Exibe os comandos disponíveis       |
| `exit`           | Encerra o shell                     |

## 🛠️ Requisitos

Para compilar e executar o projeto, você precisará de:

* Linux ou outro sistema Unix-like
* GCC
* GNU Make

Verifique as ferramentas instaladas:

```bash
gcc --version
make --version
```

## 📦 Instalação

Clone o repositório:

```bash
git clone https://github.com/CincoFolha/shell.git
cd shell
```

## 🔨 Compilação

O projeto utiliza um `Makefile` para automatizar o processo de compilação.

Compile o projeto com:

```bash
make
```

Ou:

```bash
make all
```

Para recompilar completamente:

```bash
make rebuild
```

Para remover os arquivos gerados:

```bash
make clean
```

Após a compilação, o executável `lsh` estará disponível no diretório do projeto.

## 🚀 Uso

Execute o shell com:

```bash
./lsh
```

Exemplo:

```text
LSH Shell v1.0 - Simple Shell Implementation
Type 'help' for available commands.

> help
> pwd
/home/user
> cd /tmp
> pwd
/tmp
> ls
> exit

Goodbye!
```

Também é possível executar programas externos diretamente:

```text
> ls -la
> echo "Hello, World!"
> gcc --version
```

## 🧪 Exemplo de fluxo

```bash
$ ./lsh

> pwd
/home/user/shell

> cd /tmp

> pwd
/tmp

> ls
...

> exit

Goodbye!
```

## 📚 Objetivo Educacional

Este projeto não pretende substituir shells completos como Bash ou Zsh. Seu objetivo é servir como uma implementação pequena e compreensível para estudar conceitos fundamentais de sistemas operacionais e programação em C.

Possíveis conceitos para explorar a partir deste projeto:

* Processos e processos filhos
* `fork()` e `exec()`
* Comunicação com o sistema operacional
* File descriptors
* Signals
* Parsing de comandos
* Redirecionamento de entrada e saída
* Pipes
* Gerenciamento de memória
* Variáveis de ambiente

## 🗺️ Próximos Passos

Algumas funcionalidades que podem ser implementadas futuramente:

* [ ] Validação dos argumentos dos comandos built-in
* [ ] Melhor tratamento de erros de `waitpid()`
* [ ] Redirecionamento de entrada e saída (`>`, `<`, `>>`)
* [ ] Pipes (`|`)
* [ ] Background processes (`&`)
* [ ] Tratamento de sinais
* [ ] Histórico de comandos
* [ ] Suporte a aspas e argumentos mais complexos
* [ ] Testes automatizados

## 📄 Licença

Este projeto está disponível para fins educacionais.
