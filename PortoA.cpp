#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// ================= CLASSES =================

class Motorista {
public:
    int id;
    string nome;
    string apelido;
    string documento;
    string matricula;

    bool documentoValido() {
        return documento.length() >= 8;
    }
};

class Carga {
public:
    string referencia;
    string categoria;
    string destino;
    string estado;
};

class Movimento {
public:
    int idMotorista;
    string referenciaCarga;
    string tipoMovimento;
    string data;
    string hora;
};

// ================= DADOS =================

vector<Motorista> motoristas;
vector<Carga> cargas;
vector<Movimento> movimentos;

// ================= FUNÇÕES =================

bool motoristaExiste(int id) {

    for (auto &m : motoristas) {
        if (m.id == id) {
            return true;
        }
    }

    return false;
}

// Cadastrar motorista
void cadastrarMotorista() {

    Motorista m;

    cout << "\nID do motorista: ";
    cin >> m.id;

    cin.ignore();

    cout << "Nome: ";
    getline(cin, m.nome);

    cout << "Apelido: ";
    getline(cin, m.apelido);

    cout << "BI ou Passaporte: ";
    getline(cin, m.documento);

    cout << "Matricula do camiao: ";
    getline(cin, m.matricula);

    motoristas.push_back(m);

    cout << "\nMotorista cadastrado com sucesso!\n";
}

// Cadastrar carga
void cadastrarCarga() {

    Carga c;

    cin.ignore();

    cout << "\nReferencia da carga: ";
    getline(cin, c.referencia);

    cout << "Categoria da carga: ";
    getline(cin, c.categoria);

    cout << "Destino da carga: ";
    getline(cin, c.destino);

    cout << "Estado da carga: ";
    getline(cin, c.estado);

    cargas.push_back(c);

    cout << "\nCarga cadastrada com sucesso!\n";
}

// Entrada
void registrarEntrada() {

    Movimento mov;

    cout << "\nID do motorista: ";
    cin >> mov.idMotorista;

    if (!motoristaExiste(mov.idMotorista)) {

        cout << "\nERRO: Motorista nao cadastrado!\n";
        return;
    }

    cin.ignore();

    cout << "Referencia da carga: ";
    getline(cin, mov.referenciaCarga);

    cout << "Data (dd/mm/aaaa): ";
    getline(cin, mov.data);

    cout << "Hora (hh:mm): ";
    getline(cin, mov.hora);

    mov.tipoMovimento = "Entrada";

    movimentos.push_back(mov);

    cout << "\nEntrada registada com sucesso!\n";
}

// Saída
void registrarSaida() {

    Movimento mov;

    cout << "\nID do motorista: ";
    cin >> mov.idMotorista;

    if (!motoristaExiste(mov.idMotorista)) {

        cout << "\nERRO: Motorista nao cadastrado!\n";
        return;
    }

    cin.ignore();

    cout << "Referencia da carga: ";
    getline(cin, mov.referenciaCarga);

    cout << "Data (dd/mm/aaaa): ";
    getline(cin, mov.data);

    cout << "Hora (hh:mm): ";
    getline(cin, mov.hora);

    mov.tipoMovimento = "Saida";

    movimentos.push_back(mov);

    cout << "\nSaida registada com sucesso!\n";
}

// Pesquisar carga
void pesquisarCarga() {

    string ref;

    cin.ignore();

    cout << "\nReferencia da carga: ";
    getline(cin, ref);

    bool encontrou = false;

    for (auto &c : cargas) {

        if (c.referencia == ref) {

            cout << "\n=== CARGA ENCONTRADA ===\n";
            cout << "Referencia: " << c.referencia << endl;
            cout << "Categoria: " << c.categoria << endl;
            cout << "Destino: " << c.destino << endl;
            cout << "Estado: " << c.estado << endl;

            encontrou = true;
        }
    }

    if (!encontrou)
        cout << "\nCarga nao encontrada!\n";
}

// Pesquisar motorista por BI
void pesquisarBI() {

    string bi;

    cin.ignore();

    cout << "\nDigite o BI/Passaporte: ";
    getline(cin, bi);

    bool encontrou = false;

    for (auto &m : motoristas) {

        if (m.documento == bi) {

            cout << "\n=== MOTORISTA ENCONTRADO ===\n";
            cout << "Nome: " << m.nome << " " << m.apelido << endl;
            cout << "Matricula: " << m.matricula << endl;

            encontrou = true;
        }
    }

    if (!encontrou)
        cout << "\nMotorista nao encontrado!\n";
}

// Aprovação
void verificarAprovacao() {

    cout << "\n=== APROVACAO ===\n";

    for (auto &m : motoristas) {

        cout << m.nome << " " << m.apelido << " -> ";

        if (m.documentoValido())
            cout << "APROVADO";
        else
            cout << "REJEITADO";

        cout << endl;
    }
}

// Salvar ficheiro
void salvarDados() {

    ofstream arquivo("porto_beira.txt");

    for (auto &m : motoristas) {

        arquivo
            << m.id << ";"
            << m.nome << ";"
            << m.apelido << ";"
            << m.documento << ";"
            << m.matricula << endl;
    }

    arquivo.close();

    cout << "\nDados guardados com sucesso!\n";
}

// Ler ficheiro
void lerDados() {

    ifstream arquivo("porto_beira.txt");

    string linha;

    cout << "\n=== DADOS DO ARQUIVO ===\n";

    while (getline(arquivo, linha)) {

        cout << linha << endl;
    }

    arquivo.close();
}

// Relatório
void relatorio() {

    cout << "\n=========== RELATORIO ===========\n";

    cout << "Total de Motoristas: "
         << motoristas.size() << endl;

    cout << "Total de Cargas: "
         << cargas.size() << endl;

    cout << "Total de Movimentos: "
         << movimentos.size() << endl;

    cout << "\n=== HISTORICO ===\n";

    for (auto &m : movimentos) {

        cout << "\nMotorista ID: "
             << m.idMotorista;

        cout << "\nCarga: "
             << m.referenciaCarga;

        cout << "\nMovimento: "
             << m.tipoMovimento;

        cout << "\nData: "
             << m.data;

        cout << "\nHora: "
             << m.hora;

        cout << "\n----------------------";
    }

    cout << endl;
}

// ================= MAIN =================

int main() {

    int opcao;

    do {

        cout << "\n====================================";
        cout << "\nPORTO DA BEIRA";
        cout << "\nSISTEMA DE CONTROLO";
        cout << "\n====================================";

        cout << "\n1. Cadastrar Motorista";
        cout << "\n2. Cadastrar Carga";
        cout << "\n3. Registar Entrada";
        cout << "\n4. Registar Saida";
        cout << "\n5. Pesquisar Carga";
        cout << "\n6. Pesquisar Motorista por BI";
        cout << "\n7. Verificar Aprovacao";
        cout << "\n8. Salvar Dados";
        cout << "\n9. Ler Dados";
        cout << "\n10. Relatorio";
        cout << "\n0. Sair";

        cout << "\n\nOpcao: ";
        cin >> opcao;

        switch (opcao) {

            case 1:
                cadastrarMotorista();
                break;

            case 2:
                cadastrarCarga();
                break;

            case 3:
                registrarEntrada();
                break;

            case 4:
                registrarSaida();
                break;

            case 5:
                pesquisarCarga();
                break;

            case 6:
                pesquisarBI();
                break;

            case 7:
                verificarAprovacao();
                break;

            case 8:
                salvarDados();
                break;

            case 9:
                lerDados();
                break;

            case 10:
                relatorio();
                break;

            case 0:
                cout << "\nSistema encerrado.\n";
                break;

            default:
                cout << "\nOpcao invalida!\n";
        }

    } while (opcao != 0);

    return 0;
}