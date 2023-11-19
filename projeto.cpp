/*
Nomes: Gabriel Fagundes Mesquita Sousa, Gabriel Luis Moreira Cantanhede, Bruno Souza Carvalho.
Tema: Países.
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct info{
    int id;
    char nome[50];
    int pop;
    char idioma[50];
    char desc[300];
};

void gravaBin(fstream& arqBin, info*&pais, int cap);

void importCSV(ifstream& arqCSV, fstream& arqBin, info*& pais, int cap){
    string lixo;
    getline(arqCSV, lixo);

    for(int i=0; i<cap; i++){
        arqCSV >> pais[i].id;
        arqCSV.ignore();
        arqCSV.getline(pais[i].nome, 50, ';');
        arqCSV >> pais[i].pop;
        arqCSV.ignore();
        arqCSV.getline(pais[i].idioma, 50, ';');
        arqCSV.getline(pais[i].desc, 300);
    }
    cout << "Importação concluída." << endl;
    gravaBin(arqBin, pais, cap);
}

void gravaBin(fstream& arqBin, info*&pais, int cap){
        for(int i = 0; i < cap; i++){
        arqBin.write((char*)(&pais[i].id), sizeof(int));
        arqBin.write(pais[i].nome, sizeof(pais[i].nome));
        arqBin.write((char*)(&pais[i].pop), sizeof(int));
        arqBin.write(pais[i].idioma, sizeof(pais[i].idioma));
        arqBin.write(pais[i].desc, sizeof(pais[i].desc));
    }
    cout << "Dados gravados no arquivo binário." << endl;
}

void insertBin(fstream& arqBin, info*& pais, int& cap){
    cap+=1;
    info* novoPais = new info[cap];
    memcpy(novoPais, pais, sizeof(info)*cap-1);
    delete[] pais;
    pais = novoPais;
    cout << "Inserção de novo país: " << endl;
    cout << "OBS: país será alocado na posição: " << cap << endl;
    pais[cap-1].id = cap;
    cout << "Digite o nome do país: " << endl;
    cin.getline(pais[cap-1].nome, sizeof(pais[cap-1].nome));
    for (char& c : pais[cap-1].nome) {
    c = toupper(c);
    }
    cout << "Digite o número de habitantes desse país: " << endl;
    cin >> pais[cap-1].pop;
    cin.ignore();
    cout << "Digite o principal idioma falado nesse país: " << endl;
    cin.getline(pais[cap-1].idioma, sizeof(pais[cap-1].idioma));
    cout << "Digite uma breve descrição do país: " << endl;
    cin.getline(pais[cap-1].desc, sizeof(pais[cap-1].desc));
    cout << "País inserido." << endl;
    gravaBin(arqBin, pais, cap);
}

void leBin(fstream& arqBin, info*& pais, int cap){
    arqBin.read(reinterpret_cast<char*>(&pais), sizeof(info)*cap);
    cout << "Leitura dos dados do arquivo binário concluída." << endl;
}

void printBin(fstream& arqBin, info*& pais, int cap){
    for(int i = 0; i<cap; i++){
    char nomeAux[51];
    strncpy(nomeAux, pais[i].nome, 50);
    char idiomaAux[51];
    strncpy(idiomaAux, pais[i].idioma, 50);
    char descAux[301];
    strncpy(descAux, pais[i].desc, 300);

    nomeAux[50] = '\0';
    idiomaAux[50] = '\0';
    descAux[300] = '\0';

    cout << "ID: " << pais[i].id << endl << "Nome: " << nomeAux << endl << "População: "
    << pais[i].pop << endl << "Idioma: " << idiomaAux << endl << "Descrição: " << descAux << endl;

    cout << "--------" << endl;
    }
}

void shellSortName(fstream& arqBin, info*& pais, int cap){ 
    const int ciuraGaps[] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int pos_gap = 8;

    while (ciuraGaps[pos_gap] > cap){
        pos_gap--;
    }

    int* idsOriginais = new int[cap];
    for (int i = 0; i < cap; ++i) {
        idsOriginais[i] = pais[i].id;
    }

    while (pos_gap >= 0) {
        int gap = ciuraGaps[pos_gap];

        for (int i = gap; i < cap; i++) {
            info temp = pais[i];
            int j = i;
            while (j >= gap && strcmp(pais[j - gap].nome, temp.nome) > 0) {
                pais[j] = pais[j - gap];
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

    arqBin.seekg(0, ios::beg);

    gravaBin(arqBin, pais, cap);
}

void buscaPorNome(info* pais, int cap, const char* nomeProcurado) {
    bool encontrado = false;

    for (int i = 0; i < cap; ++i) {
        if (strcmp(pais[i].nome, nomeProcurado) == 0 and not encontrado) {
            cout << "ID: " << pais[i].id << endl
                 << "Nome: " << pais[i].nome << endl
                 << "População: " << pais[i].pop << endl
                 << "Idioma: " << pais[i].idioma << endl
                 << "Descrição: " << pais[i].desc << endl;

            encontrado = true;
        }
    }

    if (not encontrado) {
        cout << "País não listado." << endl;
    }
}

bool buscaBinariaPorId(info* pais, int cap, int idBusca, info& resultado) {
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

void menu(fstream& arqBin, info*& pais, int cap) {
    int opcao;
    do {
        cout << "\nMenu:\n"
             << "1. Listar todos os países\n"
             << "2. Inserir país\n"
             << "3. Buscar país\n"
             << "4. Ordenar alfabeticamente\n"
             << "0. Sair\n"
             << "Escolha uma opção: ";
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
            if(resp == 1){
            char nomeProcurado[50];
            cout << "Digite o país a ser procurado: ";
            cin.getline(nomeProcurado, sizeof(nomeProcurado));
            for (char& c : nomeProcurado) {
                c = toupper(c);
            }
            buscaPorNome(pais, cap, nomeProcurado);
            break;
            } else if (resp == 2){
                int idBusca;
                cout << "Digite o ID a ser buscado: ";
                cin >> idBusca;

                cin.ignore();

                info resultado;
                if (buscaBinariaPorId(pais, cap, idBusca, resultado)) {
                    cout << "Registro encontrado:\n";
                    cout << "ID: " << resultado.id << "\nNome: " << resultado.nome << "\nPopulação: "
                         << resultado.pop << "\nIdioma: " << resultado.idioma << "\nDescrição: " << resultado.desc << "\n";
                } else {
                    cout << "Registro com ID " << idBusca << " não encontrado.\n";
                }
            buscaBinariaPorId(pais, cap, idBusca, resultado);
            break;
            } else{
                cout << "Opção inválida." << endl;
                break;
            }
        }
        case 4:
            shellSortName(arqBin, pais, cap);
            cout << "Países ordenados por nome.\n";
            printBin(arqBin, pais, cap);
            break;
        case 0:
            cout << "Saindo do programa.\n";
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
        }

    } while (opcao != 0);
}

int main(){
    ifstream arqCSV;
    arqCSV.open("projetinho.csv");
    if (not arqCSV){
        cout << "Erro ao abrir o arquivo CSV na função principal." << endl;
    }
    fstream arqBin;
    arqBin.open("projetinho.dat", ios::binary | ios::in | ios::out);
    if (not arqBin){
        cout << "Erro ao abrir o arquivo DAT na função principal." << endl;
    }

    int cabecalho;
    arqCSV >> cabecalho;
    int cap = cabecalho;
    info* pais = new info[cap];

    importCSV(arqCSV, arqBin, pais, cap);
    menu(arqBin, pais, cap);

    delete[] pais;
    arqBin.close();
    arqCSV.close();
    return 0;
}