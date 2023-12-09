# Projeto Prático: Aplicação de Manipulação de Dados em Arquivo Binário

Este repositório contém uma aplicação desenvolvida como projeto prático da disciplina de Introdução a Algoritmos da Universidade Federal de Lavras (UFLA). A aplicação tem como objetivo a manipulação de dados armazenados em arquivo binário com diversas funcionalidades.

## Funcionalidades Implementadas

### Armazenamento de Dados

Os dados são armazenados em um arquivo binário tipado, permitindo a importação e exportação para o formato CSV.

### Ordenação de Dados

A aplicação permite a ordenação dos registros por dois campos diferentes do registro. Para isso, utiliza um dos métodos eficientes de ordenação: quick sort, merge sort ou shell sort. A ordenação é realizada em memória, onde todos os dados do arquivo são lidos em um vetor, ordenados e gravados novamente no disco.

### Remoção Lógica de Dados

É possível remover dados existentes no arquivo de forma lógica. Isso significa que o objeto não é apagado diretamente do arquivo, mas marcado (por exemplo, com uma chave negativa). O espaço pode ser utilizado em futuras inserções. A remoção é concluída quando o arquivo é reordenado.

### Inserção de Novos Elementos

A aplicação permite a inserção de novos elementos. A inserção pode ser realizada no final do arquivo ou substituindo dados marcados como removidos. Uma opção adicional é a inserção ordenada para facilitar a busca binária, mantendo os dados ordenados.

### Busca de Registros

A busca de registros pode ser feita por pelo menos dois campos diferentes, como nome, idade ou endereço. A busca pode ser realizada de forma binária ou sequencial diretamente no arquivo binário. É importante notar que a busca binária requer dados ordenados.

### Impressão de Dados

É possível imprimir tanto o arquivo inteiro quanto um trecho específico definido pelo usuário. A impressão é realizada na ordem em que os dados estão armazenados. Para uma impressão ordenada, é necessário ordenar o arquivo primeiro.

## Como Utilizar o Projeto

1. **Clone o Repositório:**
   git clone https://github.com/seu-usuario/nome-do-repositorio.git
2. **Compile e execute o código**
3. **Utilize as Funcionalidades da Aplicação:**
Siga as instruções apresentadas para realizar operações como inserção, remoção, ordenação, busca e impressão de dados.
