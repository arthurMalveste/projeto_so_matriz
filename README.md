# Projeto: Rotaciona Matriz (Multi-threading)

[cite_start]Este projeto foi desenvolvido como requisito de avaliação da disciplina TT304 - Sistemas Operacionais[cite: 4]. [cite_start]O objetivo principal é consolidar conhecimentos sobre programação paralela utilizando múltiplas threads[cite: 5]. 

[cite_start]O programa, escrito em linguagem C pura, lê uma matriz de tamanho NxN a partir de um arquivo de texto e utiliza a biblioteca POSIX Threads (pthreads) para rotacioná-la em 90 graus no sentido horário[cite: 8, 11, 14, 15]. [cite_start]Todo o desenvolvimento foi focado em ambiente Linux[cite: 8].

## 🚀 Funcionalidades e Requisitos

* [cite_start]**Alocação Dinâmica Eficiente:** A matriz é alocada dinamicamente na memória em uma única etapa[cite: 85].
* [cite_start]**Processamento Paralelo:** Divisão da carga de trabalho entre um número configurável de threads (ex: 1, 2, 4 ou 8)[cite: 18, 24].
* [cite_start]**Medição de Desempenho:** Cálculo preciso do tempo de execução individual de cada thread e do tempo total de processamento (ignorando o tempo de I/O de leitura/escrita dos arquivos) utilizando a primitiva `clock_gettime`[cite: 49, 61, 64].

## 🛠️ Pré-requisitos

Para compilar e executar este projeto, você precisará de um ambiente Linux com:
* Compilador GCC.
* Ferramenta GNU Make.

## ⚙️ Como Compilar

[cite_start]O projeto inclui um `Makefile` para facilitar a compilação[cite: 89]. No terminal, dentro da pasta do projeto, basta digitar:

```bash
make