#include <iostream>
#include <locale.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>

#define limpa system("CLS")

using namespace std;

    int i = 0,m = 0;
    string a,missaAtual;

class Igreja {
    public:
    string nome;
    string horariosMissas[10];
    int lugaresTotais;
    Igreja(string aNome, int aLugaresTotais){
        nome=aNome;
        lugaresTotais=aLugaresTotais;
    }
};
    Igreja igreja("Dom Bosco", 200);

class lugaresDisp {
    public:
    int quantidade;
    string codigo;
    void adicionarLugares(int aQuant){
        quantidade=quantidade-aQuant;
    }
    lugaresDisp(){
        quantidade=igreja.lugaresTotais;
    }
};

    lugaresDisp disponiveis;

class lugaresOcu {
    public:
    int quantidade;
    string codigo;
    void adicionarLugares(int aQuant){
        quantidade=quantidade+aQuant;
    }
    lugaresOcu(){
        quantidade=0;
    }
};

    lugaresOcu ocupados;

class Missa{
    public:
    string celebrante[50];
    string horario[50];
    string diaSemana[50];
    string diaMes[50];
    Missa(){};
    void adicionarReserva(int quantReser){
        disponiveis.adicionarLugares(quantReser);
        ocupados.adicionarLugares(quantReser);
    }
    void novaMissa(string aCelebrante, string aHorario, string aSemana, string aMes){
        celebrante[m]=aCelebrante;
        horario[m]=aHorario;
        diaSemana[m]=aSemana;
        diaMes[m]=aMes;
        disponiveis.quantidade=igreja.lugaresTotais;
        disponiveis.quantidade=0;
    }
};

    Missa missa;

class Fiel {
    public:
    int codigo[50];
    string nome[50];
    string endereco[50];
    string telefone[50];
    int quantidadePessoas[50];


    Fiel(){
        codigo[0]=37;
    };
    void adicionarReserva(string aNome, string aEndereco, string aTelefone,int quantRes, int aCodigo){
        nome[i]=aNome;
        endereco[i]=aEndereco;
        telefone[i]=aTelefone;
        quantidadePessoas[i]=quantRes;
        codigo[i]=aCodigo;
        missa.adicionarReserva(quantRes);
    }
};

    Fiel reservas;

void inicio();
void iterarAPI();
void adicionarAPI();

void verificarAPI(){
    ifstream api_r;
    ofstream api_s;
    string teste;

    api_r.open(missaAtual);
    if(api_r.is_open()){
        getline(api_r, teste);
        if(teste.length()>0){
            api_r.close();
            iterarAPI();
        } else {
            api_r.close();
        }
    } else {
        api_s.open(missaAtual);
        api_s.close();
    }
    system("CLS");
}



int gerarCodigo(){
    int codigo;
    unsigned seed = time(NULL);
    srand(seed);
    codigo=rand() % 37 + 1;
    for (int j=0; j<i ;j++){
        if (codigo==reservas.codigo[j]){
            codigo = gerarCodigo();
        }
    }
    return codigo;

}

void criarArquivo(string arquivo){
    ofstream arq;
    arq.open(arquivo);
    missaAtual=arquivo;
}
void iterarAPI(){

    ifstream api_r;
    string qtP, code, nome, telefone, endereco;
    int quantPe, codigo;

    api_r.open(missaAtual);
    if(api_r.is_open()){
        i=0;
        for(int j=0;!api_r.eof();j++){
            getline(api_r, nome);
            getline(api_r, endereco);
            getline(api_r, telefone);
            getline(api_r, qtP);
            getline(api_r, code);
            quantPe = stoi(qtP);
            codigo = stoi(code);
            reservas.adicionarReserva(nome,endereco,telefone,quantPe,codigo);
            i++;

        }
    api_r.close();
    }
    else {
        cout << "Nao foi possivel abrir o arquivo.\n";
    }


}

void adicionarAPI(){
    ofstream api_s;

    api_s.open(missaAtual);
    if(api_s.is_open()){

        for(int j=0;j<i;j++){
            api_s << reservas.nome[j] << '\n';
            api_s << reservas.endereco[j] << '\n';
            api_s << reservas.telefone[j] << '\n';
            api_s << reservas.quantidadePessoas[j] << '\n';
            if (j==i-1){
                api_s << reservas.codigo[j];
            }else {
                api_s << reservas.codigo[j] << '\n';
            }
        }
    } else {
        cout << "Nao foi possivel abrir o arquivo.\n";
    }
}

void listarReservas(){
    cout << "Lugares disponíveis: " << disponiveis.quantidade << endl;
    cout << "Lugares ocupados: " << ocupados.quantidade << endl << endl;
    for(int j=0; j<i;j++){
        cout << "Reserva número " << j+1 << endl << endl;
        cout << "Nome responsável da reserva: \n    " << reservas.nome[j] << endl << endl;
        cout << "Endereço: \n    " << reservas.endereco[j] << endl << endl;
        cout << "Telefone: \n    "<< reservas.telefone[j] << endl << endl;
        cout << "Quantidade de Pessoas: \n    " << reservas.quantidadePessoas[j] << endl << endl;
        cout << "Codigo da Reserva: \n    " << reservas.codigo[j] << endl << endl;
        cout << endl << endl;
    }
    cout << "Pressione enter para voltar à tela inicial" << endl;
    system("pause");
    inicio();

}
void escolherMissa(){
    int escolha;
    cout << "VOCÊ DESEJA ACESSAR QUAL MISSA?" << endl;
    for (int j=0;j<m;j++){
        cout << j+1 << " - Padre: " << missa.celebrante[j] << "missa de " << missa.diaSemana[j] << "  dia " << missa.diaMes[j] << " ás " << missa.horario[j] << endl;
    }
    cin >> escolha;
    escolha=escolha-1;
    missaAtual=missa.diaMes[escolha]+"_"+missa.diaSemana[escolha]+"_"+missa.horario[escolha];
}
void criarReserva(){
    string nome, endereco, telefone;
    int quantRes, codigo;

    limpa;
    codigo=gerarCodigo();
    cout << "LUGARES DISPONÍVEIS: " << disponiveis.quantidade << "\n\n\n";
    cout << "RESPONSÁVEL PELA RESERVA" << endl;
    cout << "NOME:" << endl;
    while(getline(cin, nome))
        if(nome != ""){
          break;
    }
    cout << "ENDEREÇO:" << endl;
    getline(cin,endereco);
    while (endereco==""){
        cout << "Endereco não pode ser vazio" << endl;
        getline(cin,endereco);
    }
    cout << "TELEFONE:" << endl;
    getline(cin,telefone);
    while (telefone==""){
        cout << "Telefone não pode ser vazio" << endl;
        getline(cin,telefone);
    }
    cout << "NÚMERO DE PESSOAS:" << endl;
    cin >> quantRes;

    reservas.adicionarReserva(nome, endereco ,telefone ,quantRes, codigo);
    cout << "Reserva feita com sucesso! Código da reserva: " << codigo << endl;
    cout << "PRESSIONE ENTER PARA VOLTAR A TELA INICIAL" << endl;
    system ("pause");
    i++;
    adicionarAPI();
    inicio();
}

void limparReservas(){
    for (int j=0; j<=i;j++){
        reservas.nome[j]='\0';
        reservas.endereco[j]='\0';
        reservas.codigo[j]=NULL;
        reservas.telefone[j]='\0';
        reservas.quantidadePessoas[j]=NULL;
    }
    i=0;
    disponiveis.quantidade=igreja.lugaresTotais;
    ocupados.quantidade=0;
    inicio();
}

void criarNovaMissa(){
    string padre, horario, arquivo, diaSemana, diaMes;
    limpa;

    cout << "INSIRA O NOME DO PADRE QUE CELEBRARÁ A MISSA" << endl;
    cin >> padre;
    cout << "INSIRA O DIA DA SEMANA DA MISSA" << endl;
    cin >> diaSemana;
    cout << "INSIRA O DIA DO MÊS DA MISSA" << endl;
    cin >> diaMes;
    cout <<  "\n INSIRA O HORÁRIO DA MISSA NO FORMATO 24H" << endl;
    cin >> horario;

    missa.novaMissa(padre, horario, diaSemana, diaMes);
    arquivo=diaMes+"_"+diaSemana+"_"+horario;
    criarArquivo(arquivo);
    m++;
    inicio();

}
void validarCodigo(){
    limpa;
    int codigo;
    cout << "Insira um código para conferir se ele é válido" << endl;
    cin >> codigo;
    for (int j=0;j<i;j++){
        if (codigo==reservas.codigo[j]){
            cout << "Código válido!" << endl << "Pertencente a reserva número " << j+1 << endl << endl;
            cout << "Nome responsável da reserva: \n    " << reservas.nome[j] << endl << endl;
            cout << "Endereço: \n    " << reservas.endereco[j] << endl << endl;
            cout << "Telefone: \n    "<< reservas.telefone[j] << endl << endl;
            cout << "Quantidade de Pessoas: \n    " << reservas.quantidadePessoas[j] << endl << endl;
            cout << "Codigo da Reserva: \n    " << reservas.codigo[j] << endl << endl;
            cout << endl << endl;
            break;
        } else if(j==i-1){
            cout << "Código inválido" << endl;
        }
    }
    cout << "Pressione enter para continuar" << endl;
    system("pause");
    inicio();
}
void inicio(){
    int esc;
    limpa;
    cout << "O que você deseja fazer?"<< endl;
    cout << "1 - LIMPAR RESERVAS" << endl;
    cout << "2 - CADASTRAR RESERVA" << endl;
    cout << "3 - LISTAR RESERVAS" << endl;
    cout << "4 - CRIAR NOVA MISSA" << endl;
    cout << "5 - VALIDAR CÓDIGO" << endl;
    cin >> esc;
    switch(esc){
    case(1):
        limparReservas();
    break;
    case(2):
        criarReserva();
    break;
    case(3):
        listarReservas();
    break;
    case(4):
        criarNovaMissa();
    break;
    case(5):
        validarCodigo();
    break;
    default:
        cout << "Opção inválida, pressione Enter para voltar" << endl;
        system("pause");
        inicio();

    }
}

int main(){

    setlocale(LC_ALL,"");
    verificarAPI();
    inicio();

return 0;
}
