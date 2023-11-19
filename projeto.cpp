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
        arqCSV.getline(pais[i].nome, 15, ';');
        arqCSV >> pais[i].pop;
        arqCSV.ignore();
        arqCSV.getline(pais[i].idioma, 15, ';');
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
    cout << "Inseração de novo país: " << endl;
    cout << "OBS: país será alocado na posição: " << cap << endl;
    pais[cap-1].id = cap;
    cout << "Digite o nome do país: " << endl;
    cin.getline(pais[cap-1].nome, sizeof(pais[cap-1].nome));
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
    insertBin(arqBin, pais, cap);
    leBin(arqBin, pais, cap);
    printBin(arqBin, pais, cap);
    arqBin.close();
    arqCSV.close();
    return 0;
}