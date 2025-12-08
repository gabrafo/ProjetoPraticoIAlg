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

1. **Clone o Repositório:**`
```bash
   git clone https://github.com/gabrafo/projetopraticoialg.git
```
2. **Compile e execute o código**
3. **Utilize as Funcionalidades da Aplicação:**
Siga as instruções apresentadas para realizar operações como inserção, remoção, ordenação, busca e impressão de dados.

## Licença
Este projeto está sob a licença MIT. Consulte o arquivo LICENSE para mais detalhes.

---

# Practical Project: Binary File Data Manipulation Application

This repository contains an application developed as a practical project for the *Introduction to Algorithms* course at the Federal University of Lavras (UFLA). The goal of this application is to manipulate data stored in a binary file while supporting a variety of operations.

## Implemented Features

### Data Storage

Records are stored in a typed binary file, with built-in support for importing and exporting data in CSV format.

### Data Sorting

The application allows sorting records by two different fields. To accomplish this, it uses one of the efficient sorting algorithms: quick sort, merge sort, or shell sort. Sorting is performed in memory: all data is loaded from the file into an array, sorted, and then written back to disk.

### Logical Deletion of Records

Existing records can be logically deleted. Instead of being physically removed from the file, records are marked (e.g., with a negative key). The marked space can later be reused for new insertions. Logical deletions are fully resolved when the file is reordered.

### Insertion of New Elements

The application supports the insertion of new elements. New entries can be added at the end of the file or inserted into positions previously marked as deleted. There is also an option for sorted insertion, which helps maintain order and allows binary search to be used efficiently.

### Record Search

Records can be searched using at least two different fields, such as name, age, or address. Searches may be performed either sequentially or using binary search directly on the binary file. Note that binary search requires the data to be sorted.

### Data Printing

The application can print either the entire file or a specific segment defined by the user. Printing follows the physical order of the stored data. For ordered printing, the file must be sorted first.

## How to Use the Project

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/gabrafo/projetopraticoialg.git
   ```
2. **Compile and run the code.**
3. **Use the Application Features:**
   Follow the on-screen instructions to perform operations such as insertion, deletion, sorting, searching, and printing of records.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.
