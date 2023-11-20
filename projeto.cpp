/*
Nomes: Gabriel Fagundes Mesquita Sousa, Gabriel Luis Moreira Cantanhede, Bruno Souza Carvalho.
Tema: Países.
*/

#include <iostream>

#include <fstream>

#include <cstring>

using namespace std;

struct info {
  int id;
  char nome[50];
  int pop;
  char idioma[50];
  char desc[300];
};

void menu(ofstream & arqOutCSV, fstream & arqBin, info * & pais, int cap);

void gravaBin(fstream & arqBin, info * & pais, int cap);

void swapID(info * & pais, int pos1, int pos2) {
  int aux = pais[pos1].id;
  pais[pos1].id = pais[pos2].id;
  pais[pos2].id = aux;
}

void swap(info * & pais, int pos1, int pos2) {
  info aux = pais[pos1];
  pais[pos1] = pais[pos2];
  pais[pos2] = aux;
  swapID(pais, pos1, pos2);
}

void importCSV(ifstream & arqInCSV, fstream & arqBin, info * & pais, int cap) {
  string lixo;
  getline(arqInCSV, lixo);

  for (int i = 0; i < cap; i++) {
    arqInCSV >> pais[i].id;
    arqInCSV.ignore();
    arqInCSV.getline(pais[i].nome, 50, ';');
    arqInCSV >> pais[i].pop;
    arqInCSV.ignore();
    arqInCSV.getline(pais[i].idioma, 50, ';');
    arqInCSV.getline(pais[i].desc, 300);
  }
  cout << "Importação do arquivo \"projetinho.csv\" para o programa concluída." << endl;
  gravaBin(arqBin, pais, cap);
}

void exportCSV(ofstream & arqOutCSV, info * & pais, int cap) {
  arqOutCSV << cap << endl;

  for (int i = 0; i < cap; i++) {
    arqOutCSV << pais[i].id << ";" <<
      pais[i].nome << ";" <<
      pais[i].pop << ";" <<
      pais[i].idioma << ";" <<
      pais[i].desc << endl;
  }

  cout << "Exportação para o arquivo \"projetinhoOUT.csv\" concluída." << endl;
}

void gravaBin(fstream & arqBin, info * & pais, int cap) {
  for (int i = 0; i < cap; i++) {
    arqBin.write((char * )( & pais[i].id), sizeof(int));
    arqBin.write(pais[i].nome, sizeof(pais[i].nome));
    arqBin.write((char * )( & pais[i].pop), sizeof(int));
    arqBin.write(pais[i].idioma, sizeof(pais[i].idioma));
    arqBin.write(pais[i].desc, sizeof(pais[i].desc));
  }
  cout << "Dados gravados no arquivo binário." << endl;
}

void insertBin(fstream & arqBin, info * & pais, int & cap) {
  cap += 1;
  info * novoPais = new info[cap];
  memcpy(novoPais, pais, sizeof(info) * cap - 1);
  delete[] pais;
  pais = novoPais;
  cout << "Inserção de novo país: " << endl;
  cout << "OBS: país será alocado na posição: " << cap << endl;
  pais[cap - 1].id = cap;
  cout << "Digite o nome do país: " << endl;
  cin.getline(pais[cap - 1].nome, sizeof(pais[cap - 1].nome));
  for (char & c: pais[cap - 1].nome) {
    c = toupper(c);
  }
  cout << "Digite o número de habitantes desse país: " << endl;
  cin >> pais[cap - 1].pop;
  cin.ignore();
  cout << "Digite o principal idioma falado nesse país: " << endl;
  cin.getline(pais[cap - 1].idioma, sizeof(pais[cap - 1].idioma));
  cout << "Digite uma breve descrição do país: " << endl;
  cin.getline(pais[cap - 1].desc, sizeof(pais[cap - 1].desc));
  cout << "País inserido." << endl;
  gravaBin(arqBin, pais, cap);
}

void leBin(fstream & arqBin, info * & pais, int cap) {
  arqBin.read(reinterpret_cast < char * > ( & pais), sizeof(info) * cap);
  cout << "Leitura dos dados do arquivo binário concluída." << endl;
}

bool teste(int & posI, int & posF, int cap) {
  cout << "O intervalo começa na posição: ";
  cin >> posI;
  if (posI < 1) {
    cout << "Posição inicial inválida." << endl;
    return false;
  }
  cout << "O intervalo termina na posição: ";
  cin >> posF;
  if (posI > posF or posF > cap) {
    cout << "Intervalo inválido." << endl;
    return false;
  } else {
    return true;
  }
}

void printBin(fstream & arqBin, info * & pais, int cap) {
  int posI, posF;
  cout << "Deseja fazer a impressão de todos os elementos ou apenas de um intervalo específico? " << endl;
  cout << "1. Impressão de todos os elementos\n" << "2. Impressão de um intervalo\n";
  int resp;
  cin >> resp;
  cin.ignore();

  if (resp == 1) {
    for (int i = 0; i < cap; i++) {
      char nomeAux[51];
      strncpy(nomeAux, pais[i].nome, 50);
      char idiomaAux[51];
      strncpy(idiomaAux, pais[i].idioma, 50);
      char descAux[301];
      strncpy(descAux, pais[i].desc, 300);

      nomeAux[50] = '\0';
      idiomaAux[50] = '\0';
      descAux[300] = '\0';

      cout << "ID: " << pais[i].id << endl << "Nome: " << nomeAux << endl << "População: " <<
        pais[i].pop << endl << "Idioma: " << idiomaAux << endl << "Descrição: " << descAux << endl;

      cout << "--------" << endl;
    }
  } else if (resp == 2) {
    cout << "OBS: Os intervalos são apenas crescentes." << endl;
    if (teste(posI, posF, cap)) {
      for (int i = posI - 1; i < posF; i++) {
        char nomeAux[51];
        strncpy(nomeAux, pais[i].nome, 50);
        char idiomaAux[51];
        strncpy(idiomaAux, pais[i].idioma, 50);
        char descAux[301];
        strncpy(descAux, pais[i].desc, 300);

        nomeAux[50] = '\0';
        idiomaAux[50] = '\0';
        descAux[300] = '\0';

        cout << "ID: " << pais[i].id << endl << "Nome: " << nomeAux << endl << "População: " <<
          pais[i].pop << endl << "Idioma: " << idiomaAux << endl << "Descrição: " << descAux << endl;

        cout << "--------" << endl;
      }
    }
  } else {
    cout << "Opção inválida." << endl;
  }
}

void shellSortName(fstream & arqBin, info * & pais, int cap) {
  const int ciuraGaps[] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
  int pos_gap = 8;

  while (ciuraGaps[pos_gap] > cap) {
    pos_gap--;
  }

  int * idsOriginais = new int[cap];
  for (int i = 0; i < cap; ++i) {
    idsOriginais[i] = pais[i].id;
  }

  while (pos_gap >= 0) {
    int gap = ciuraGaps[pos_gap];

    for (int i = gap; i < cap; i++) {
      info temp = pais[i];
      int j = i;
      while (j >= gap and strcmp(pais[j - gap].nome, temp.nome) > 0) {
        swap(pais, j, j - gap);
        j -= gap;
      }
      pais[j] = temp;
    }

    pos_gap--;
  }

  for (int i = 0; i < cap; ++i) {
    pais[i].id = idsOriginais[i];
  }

  delete[] idsOriginais;

  cout << "Ordenação eficiente por nome concluída." << endl;

  arqBin.seekp(0, ios::beg);

  gravaBin(arqBin, pais, cap);
}

void shellSortPop(fstream & arqBin, info * & pais, int cap) {
  const int ciuraGaps[] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
  int pos_gap = 8;

  while (ciuraGaps[pos_gap] > cap) {
    pos_gap--;
  }

  int * idsOriginais = new int[cap];
  for (int i = 0; i < cap; ++i) {
    idsOriginais[i] = pais[i].id;
  }

  while (pos_gap >= 0) {
    int gap = ciuraGaps[pos_gap];

    for (int i = gap; i < cap; i++) {
      info temp = pais[i];
      int j = i;
      while (j >= gap and pais[j - gap].pop > temp.pop) {
        swap(pais, j, j - gap);
        j -= gap;
      }
      pais[j] = temp;
    }

    pos_gap--;
  }

  for (int i = 0; i < cap; ++i) {
    pais[i].id = idsOriginais[i];
  }

  delete[] idsOriginais;

  cout << "Ordenação eficiente por número de habitantes concluída." << endl;

  arqBin.seekp(0, ios::beg);

  gravaBin(arqBin, pais, cap);
}

void buscaPorNome(fstream & arqBin, info * pais, int cap,
  const char * nomeProcurado) {
  shellSortName(arqBin, pais, cap);
  bool encontrado = false;

  for (int i = 0; i < cap; ++i) {
    if (strcmp(pais[i].nome, nomeProcurado) == 0 and not encontrado) {
      cout << "ID: " << pais[i].id << endl <<
        "Nome: " << pais[i].nome << endl <<
        "População: " << pais[i].pop << endl <<
        "Idioma: " << pais[i].idioma << endl <<
        "Descrição: " << pais[i].desc << endl;

      encontrado = true;
    }
  }

  if (not encontrado) {
    cout << "País não listado." << endl;
  }
}

bool buscaBinariaPorId(info * pais, int cap, int idBusca, info & resultado) {
  int inicio = 0;
  int fim = cap - 1;

  while (inicio <= fim) {
    int meio = (inicio + fim) / 2;

    if (pais[meio].id == idBusca) {
      resultado = pais[meio];
      return true;
    } else if (pais[meio].id < idBusca) {
      inicio = meio + 1;
    } else {
      fim = meio - 1;
    }
  }

  return false;
}

void removePais(fstream & arqBin, info * & pais, int & cap, int posRemover) {
  for (int i = posRemover; i < cap - 1; ++i) {
    pais[i] = pais[i + 1];
  }

  cap--;
  cout << "País removido com sucesso.\n";
  gravaBin(arqBin, pais, cap);
}

void menu(ofstream & arqOutCSV, fstream & arqBin, info * & pais, int cap) {
  int opcao;
  int idRemover;
  int posRemover = -1;
  bool achou = false;

  do {
    cout << "\nMenu:\n" <<
      "1. Listar países\n" <<
      "2. Inserir país\n" <<
      "3. Buscar país\n" <<
      "4. Ordenar países\n" <<
      "5. Trocar a posição de dois países\n" <<
      "6. Exportar para o arquivo CSV\n" <<
      "7. Remover um país da lista\n" <<
      "0. Sair\n" <<
      "Escolha uma opção: ";
    cin >> opcao;
    cin.ignore();

    switch (opcao) {
    case 1:
      leBin(arqBin, pais, cap);
      printBin(arqBin, pais, cap);
      break;
    case 2:
      insertBin(arqBin, pais, cap);
      break;
    case 3: {
      cout << "1. Buscar por nome\n" << "2. Buscar por ID\n";
      int resp;
      cin >> resp;
      cin.ignore();
      if (resp == 1) {
        cout << "OBS: O arquivo será automaticamente ordenado alfabeticamente antes da busca." << endl;
        char nomeProcurado[50];
        cout << "Digite o país a ser procurado: ";
        cin.getline(nomeProcurado, sizeof(nomeProcurado));
        for (char & c: nomeProcurado) {
          c = toupper(c);
        }
        buscaPorNome(arqBin, pais, cap, nomeProcurado);
        break;
      } else if (resp == 2) {
        int idBusca;
        cout << "Digite o ID a ser buscado: ";
        cin >> idBusca;
        cin.ignore();
        info resultado;
        if (buscaBinariaPorId(pais, cap, idBusca, resultado)) {
          cout << "Registro encontrado:\n";
          cout << "ID: " << resultado.id << "\nNome: " << resultado.nome << "\nPopulação: " <<
            resultado.pop << "\nIdioma: " << resultado.idioma << "\nDescrição: " << resultado.desc << "\n";
        } else {
          cout << "Registro com ID " << idBusca << " não encontrado.\n";
        }
        break;
      } else {
        cout << "Opção inválida." << endl;
        break;
      }
    }
    case 4:
      cout << "1. Ordenar alfabeticamente\n" << "2. Ordenar por número de habitantes\n";
      int resp;
      cin >> resp;
      cin.ignore();
      if (resp == 1) {
        shellSortName(arqBin, pais, cap);
        printBin(arqBin, pais, cap);
        break;
      } else if (resp == 2) {
        shellSortPop(arqBin, pais, cap);
        printBin(arqBin, pais, cap);
        break;
      } else {
        cout << "Opção inválida." << endl;
        break;
      }
    case 5:
      int pos1, pos2;
      cout << "Digite o ID do primeiro país: " << endl;
      cin >> pos1;
      cout << "Digite o ID do segundo país: " << endl;
      cin >> pos2;
      swap(pais, pos1 - 1, pos2 - 1);
      gravaBin(arqBin, pais, cap);
      break;
    case 6:
      exportCSV(arqOutCSV, pais, cap);
      cout << "Dados exportados para o arquivo \"projetinhoOUT.csv\"" << endl;
      break;
    case 7:
      cout << "Digite o ID do país a ser removido: ";
      cin >> idRemover;

      for (int i = 0; i < cap; ++i) {
        if (pais[i].id == idRemover and not achou) {
          posRemover = i;
          achou = true;
        }
      }
      if (posRemover == -1) {
        cout << "País com ID " << idRemover << " não encontrado.\n";
      } else {
        removePais(arqBin, pais, cap, posRemover);
      }
      break;

    case 0:
      cout << "Saindo do programa.\n";
      break;

    default:
      cout << "Opção inválida. Tente novamente.\n";
      break;

    }
  }

  while (opcao != 0);
}

int main() {
  ifstream arqInCSV;
  ofstream arqOutCSV;
  fstream arqBin;
  arqInCSV.open("projetinho.csv");
  arqOutCSV.open("projetinhoOUT.csv");
  arqBin.open("projetinho.dat", ios::binary | ios::in | ios::out);
  if (not arqInCSV) {
    cout << "Erro ao abrir o arquivo CSV com os dados de entrada na função principal." << endl;
  }
  if (not arqOutCSV) {
    cout << "Erro ao abrir o arquivo CSV com o potencial de exportação na função principal." << endl;
  }
  if (not arqBin) {
    cout << "Erro ao abrir o arquivo DAT na função principal." << endl;
  }

  int cabecalho;
  arqInCSV >> cabecalho;
  int cap = cabecalho;
  info * pais = new info[cap];

  importCSV(arqInCSV, arqBin, pais, cap);
  menu(arqOutCSV, arqBin, pais, cap);

  delete[] pais;
  arqInCSV.close();
  arqBin.close();
  arqOutCSV.close();
  return 0;
}