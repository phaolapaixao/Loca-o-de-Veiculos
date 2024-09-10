#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

// definir variaveis globais de tamanhos maximo a ser usadas em variaveis do tipo stringd
#define TAMANHO_STR 200 
#define MAX_VEICULOS 5 
#define MAX_CLIENTES 5 
#define MAX_LOCACOES 5

typedef struct {
    char marcaAutomovel[TAMANHO_STR];
} Marca; // Estrutura Marca, que contém um campo para a marca do automóvel

typedef struct {
    char descricaoModelo[TAMANHO_STR];
    Marca marca; // recebe a estrura marca
} Modelo; // Estrutura Modelo, que contém um campo para a modelo do automóvel

//Loop que lê caracteres do buffer de entrada até encontrar um '\n' (nova linha) ou EOF (fim de arquivo)
void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

typedef struct {
    // definicao de cariaveis dos tipos int, double e char para strings
    char placaAutomovel[TAMANHO_STR];
    char renavamAutomovel[TAMANHO_STR];
    char classiAutomovel[TAMANHO_STR];
    char corAutomovel[TAMANHO_STR];
    int numPortas;
    int tipoDegasolina;
    long quilometragem;
    double valorlocacao;
    Modelo modelo;
} CadastrarAutomovel; // Estrutura cadastrar modelo

CadastrarAutomovel veiculos[MAX_VEICULOS]; // Array de veiculos
int totalVeiculos = 0;  // Contador de veículos cadastrados

// função para cadastrar automoveis
void cadastrarVeiculo() {
    // condição para finalizar caso exceda o limete MAX_VEICULOS
    if (totalVeiculos >= MAX_VEICULOS) {
        printf("\nLimite de cadastro de veiculos atingido!\n");
        return;
    }

    printf("\nCadastro do Veiculo %d\n", totalVeiculos + 1);
    
    printf("Digite a placa do automovel:\n");
    fgets(veiculos[totalVeiculos].placaAutomovel, TAMANHO_STR, stdin); // recebe a placa do automovel

    printf("Digite o renavam do automovel:\n");
    fgets(veiculos[totalVeiculos].renavamAutomovel, TAMANHO_STR, stdin); //  recebe o renavam do automovel

    printf("Digite a classe do automovel:\n");
    fgets(veiculos[totalVeiculos].classiAutomovel, TAMANHO_STR, stdin);  // recebe a classe do automovel

    printf("Digite a cor do automovel:\n");
    fgets(veiculos[totalVeiculos].corAutomovel, TAMANHO_STR, stdin); // recebe a cor do automovel

    printf("Digite o numero de portas do automovel:\n");
    scanf("%d", &veiculos[totalVeiculos].numPortas); //  recebe o numero de portas do automovel
    limpaBuffer(); // chama a função para remover o ultimo caractere

    printf("Digite o tipo de gasolina.\nOpcoes:\n1.Gasolina\n2.Etanol\n3.Diesel\n"); // apresenta as opções no menu
    scanf("%d", &veiculos[totalVeiculos].tipoDegasolina); // recebe o tipo de gasolina
    limpaBuffer(); // eliminando o \n não evita bug para receber a proxima variavel

    printf("Digite a quilometragem do automovel:\n");
    scanf("%ld", &veiculos[totalVeiculos].quilometragem); //  recebe a quilometragem do automovel
    limpaBuffer();

    printf("Digite o valor da locacao do automovel:\n");
    scanf("%lf", &veiculos[totalVeiculos].valorlocacao); // recebe o valor locação do automovel
    limpaBuffer();

    printf("Qual o modelo?\n");
    fgets(veiculos[totalVeiculos].modelo.descricaoModelo, TAMANHO_STR, stdin); // recebe o modelo do automovel

    printf("Qual a marca?\n");
    fgets(veiculos[totalVeiculos].modelo.marca.marcaAutomovel, TAMANHO_STR, stdin); // recebe a marca do automovel

    totalVeiculos++; // acumulando a variavel a ser verificada na condição acima
    printf("\nVeículo cadastrado com sucesso!\n");
}

// função para consultar automoveis
void consultarVeiculos() {
    // condição para verificar se nenhum veiculo foi cadastrado
    if (totalVeiculos == 0) {
        printf("\nNenhum veículo cadastrado!\n");
        return;
    }
    // condicao for para imprimir os cadastrados dos automoveis até alcançar a quantidade de automoveis cadastrados
    for (int i = 0; i < totalVeiculos; i++) {
        printf("Automovel: %d\n", i + 1);
        printf("Placa do Automovel: %s", veiculos[i].placaAutomovel);
        printf("Renavam do Automovel: %s", veiculos[i].renavamAutomovel);
        printf("Classe do Automovel: %s", veiculos[i].classiAutomovel);
        printf("Cor do Automovel: %s", veiculos[i].corAutomovel);
        printf("Numero de portas do Automovel: %d\n", veiculos[i].numPortas);
        printf("Tipo de Combustivel do Automovel: ");
        // condicao que a depender da opcao escolhida imprime na tela 
        switch (veiculos[i].tipoDegasolina) {  // Lê o tipo de gasolina corretamente
            case 1: printf("Gasolina\n"); break; // ao ser escolhida a opcao finaliza e pula para imprimi a variavel quilometragem
            case 2: printf("Etanol\n"); break;
            case 3: printf("Diesel\n"); break;
            default: printf("Desconhecido\n"); break;
        }
        printf("Quilometragem do Automovel: %ld KM\n", veiculos[i].quilometragem);
        printf("Valor da locacao do Automovel: R$ %.2lf\n", veiculos[i].valorlocacao);
        printf("Modelo: %s", veiculos[i].modelo.descricaoModelo);
        printf("Marca: %s\n", veiculos[i].modelo.marca.marcaAutomovel);
    }
}

// função para salvar cadastro do automovel em um arquivo
 void salvarCasdastroAutomovelArquivo(){
    for(int i = 0; i < totalVeiculos; i++){
        FILE *arq = fopen("cadastrosAutomoveis.txt","a"); // Abre o arquivo "cadastrosAutomoveis.txt" no modo de adição ("a")
        if(arq){     // Verifica se o arquivo foi aberto corretamente
            fprintf(arq,"\n%d\n", i + 1);
            fprintf(arq, "%s", veiculos[i].placaAutomovel);
            fprintf(arq, "%s", veiculos[i].renavamAutomovel);
            fprintf(arq, "%s", veiculos[i].classiAutomovel);
            fprintf(arq, "%s", veiculos[i].corAutomovel);
            fprintf(arq, "%d\n", veiculos[i].numPortas);
            fprintf(arq, "%d ", veiculos[i].tipoDegasolina);
            switch (veiculos[i].tipoDegasolina) {
                case 1: fprintf(arq,"Gasolina\n"); break;
                case 2: fprintf(arq,"Etanol\n"); break;
                case 3: fprintf(arq,"Diesel\n"); break;
                default: fprintf(arq,"Desconhecido\n"); break; }
            fprintf(arq, "%ld KM\n",veiculos[i].quilometragem);
            fprintf(arq, "R$ %.2lf\n",veiculos[i].valorlocacao);
            fclose(arq); // Fecha o arquivo
            printf("Salvo com sucesso.\n"); // Informa ao usuário que o cadastro foi salvo com sucesso
        }
        else{
            printf("ERROR: nao foi possivel abrir o arquivo.\n\n");  // Informa ao usuário que houve um erro ao abrir o arquivo
        }
    }
 }
 // função para ler do arquivo o cadastro dos automoveis
     void lerDoarquivoCadastroAutomovel(){
    FILE *arq = fopen("cadastrosAutomoveis.txt", "r"); // Abre o arquivo uma vez
    if (arq) {
        totalVeiculos = 0; // Reinicia a contagem de veículos antes da leitura
        while (fscanf(arq, "\n%d\n", &totalVeiculos + 1) != EOF) {   // Loop para ler os dados de todos os veículos do arquivo
            fgets(veiculos[totalVeiculos].placaAutomovel, TAMANHO_STR, arq);
            fgets(veiculos[totalVeiculos].renavamAutomovel, TAMANHO_STR, arq);
            fgets(veiculos[totalVeiculos].classiAutomovel, TAMANHO_STR, arq);
            fgets(veiculos[totalVeiculos].corAutomovel, TAMANHO_STR, arq);
            fscanf(arq, "%d\n", &veiculos[totalVeiculos].numPortas);
            fscanf(arq, "%d\n", &veiculos[totalVeiculos].tipoDegasolina);
            switch (veiculos[totalVeiculos].tipoDegasolina) {
                case 1: fscanf(arq, "Gasolina\n"); break;
                case 2: fscanf(arq, "Etanol\n"); break;
                case 3: fscanf(arq, "Diesel\n"); break;
                default: fscanf(arq, "Desconhecido\n"); break;
            }

            fscanf(arq, "%ld KM\n", &veiculos[totalVeiculos].quilometragem);
            fscanf(arq, "R$ %lf\n", &veiculos[totalVeiculos].valorlocacao);

            totalVeiculos++; 
        }
        fclose(arq); // fecha arquivo
        printf("Leitura realizada com sucesso.\n");
    } else {
        printf("ERROR: nao foi possivel abrir o arquivo.\n\n");
    }
}
// funcao para consultar modelo
  void consultarModelo(){
    for(int i = 0; i < totalVeiculos; i ++){
         printf("Modelo: %d\n", i + 1);
         printf("Descricao do Modelo: %s",veiculos[i].modelo.descricaoModelo); // imprime todos os modelos de veiculos cadastrados
    }
    }
//funcao para salvar modelo no arquivo
    void salvarNoAquirvoModelo(){
        for(int i = 0; i < totalVeiculos; i++){
            FILE *arq = fopen("ModeloDoautomovel.txt","a"); // O tipo "a" acrescenta mais de um arquivo
            if(arq){
                fprintf(arq,"%s", veiculos[i].modelo.descricaoModelo);  // salvar todos os modelos de veiculos cadastrado no arquivo
                fclose(arq);
                printf("Salvo com sucesso.\n");
        }
        else{
            printf("ERROR: nao foi possivel abrir o arquivo.\n\n");
        }
        }
    }
   
    // função para consultar marcca
    void consultarMarca(){
        for(int i = 0; i < totalVeiculos; i++){
            printf("Marca: %d\n", i + 1);
            printf("Descricao do Marca: %s",veiculos[i].modelo.marca.marcaAutomovel); // imprime todos as marcas de veiculos cadastrados
        }
    }
    //funcao para salvar marca no arquivo
     void salvarNoAquirvoMarca(){
        for(int i = 0; i < totalVeiculos; i++){
            FILE *arq = fopen("MarcaDoautomovel.txt","a");
            if(arq){
                fprintf(arq, "%s",veiculos[i].modelo.marca.marcaAutomovel); // salva todos as marcas de veiculos cadastrados no arquivo
                fclose(arq);
                printf("Salvo com sucesso.\n");
    }
        else{
            printf("ERROR: nao foi possivel abrir o arquivo.\n\n");
        }
    }
    }

typedef struct {
    int dia, mes, ano;
}data; // estrutura data

typedef struct {
    int hor, min;
}hora; // estrutura hora

typedef struct{
    data dataLocacao;
    hora horaLocacao;
    data dataDevolucao;
    hora horaDevolucao;
    long quilometragem;
    long quilometragemDevolucao;
    double valorCaucao;
    double valorLocacao;
    bool locacaoDevolvida;
}LocacaoRegistra; // estrutura locacao de veiculos

LocacaoRegistra registro[MAX_LOCACOES]; // Array de locacao
int numLocacoes = 0;

void RegistrarLocacao(){
       if (numLocacoes < MAX_LOCACOES) {
        // recebe a data, usando a estrutura data 
        printf("Digite a data de locacao em formato dd mm aaaa\n");
        scanf("%d %d %d",&registro[numLocacoes].dataLocacao.dia, &registro[numLocacoes].dataLocacao.mes, &registro[numLocacoes].dataLocacao.ano);
        // recebe a hora, usando a struct hora 
        printf("Digite a hora de locacao em formato hh mm\n");
        scanf("%d %d",&registro[numLocacoes].horaLocacao.hor, &registro[numLocacoes].horaLocacao.min);

        printf("Digite a data de devolucao da locacao em formato dd mm aaaa\n");
        scanf("%d %d %d",&registro[numLocacoes].dataDevolucao.dia, &registro[numLocacoes].dataDevolucao.mes, &registro[numLocacoes].dataDevolucao.ano);

        printf("Digite a hora de devolucaoo da locacao em formato hh mm\n");
        scanf("%d %d",&registro[numLocacoes].horaDevolucao.hor, &registro[numLocacoes].horaDevolucao.min);

        printf("Qual a quilometragem Locacao?\n");
        scanf("%ld",&registro[numLocacoes].quilometragem); // recebe a quilometragem de locação 

        printf("Qual a quilometragem Devolucao?\n");
        scanf("%ld",&registro[numLocacoes].quilometragemDevolucao); // recebe a quilometragem de devolução

        printf("Qual o valor caucao?\n");
        scanf("%lf",&registro[numLocacoes].valorCaucao); // recebe o valor caução
        limpaBuffer();
    
        printf("Qual o valor locacao?\n");
        scanf("%lf",&registro[numLocacoes].valorLocacao); // recebe o valor de locação 
        limpaBuffer();

        int VouF;
        printf("Locacao devolvida? Digite 0 para NAO e 1 para SIM.\n");
        scanf("%d",&VouF); // recebe um inteiro 1 ou 0, para verificar se a locação foi devolvida

        registro[numLocacoes].locacaoDevolvida = (VouF != 0);  // se for diferente de 0, é verdadeiro

        numLocacoes++; // imcremeta
        printf("Locacao registrado com sucesso!\n\n");
    } else {
        printf("Limite de locacao atingido. Não é possível registrar mais locacoes.\n\n");
    }
    
    }
    typedef struct{
    char cpfCliente[TAMANHO_STR];
    char nomeCliente[TAMANHO_STR];
    char enderecoCliente[TAMANHO_STR];
    char telefoneCliente[TAMANHO_STR];
    char emailCliente[TAMANHO_STR];
} Cliente;// estrutura cliente

Cliente clientes[MAX_CLIENTES]; // Array de clientes
int totalClientes = 0; 

// função para cadastrar clientes
void CadastrarClientes() {
    if (totalClientes < MAX_CLIENTES) {
        printf("Digite o CPF do Cliente:\n");
        fgets(clientes[totalClientes].cpfCliente, TAMANHO_STR, stdin); // recebe o cpf do cliente
        clientes[totalClientes].cpfCliente[strcspn(clientes[totalClientes].cpfCliente, "\n")] = '\0'; // Remove o \n

        printf("Digite o Nome do Cliente:\n");
        fgets(clientes[totalClientes].nomeCliente, TAMANHO_STR, stdin);  // recebe o nome do cliente
        clientes[totalClientes].nomeCliente[strcspn(clientes[totalClientes].nomeCliente, "\n")] = '\0'; 

        printf("Digite o Endereço do Cliente:\n");
        fgets(clientes[totalClientes].enderecoCliente, TAMANHO_STR, stdin);  // recebe o endereco do cliente
        clientes[totalClientes].enderecoCliente[strcspn(clientes[totalClientes].enderecoCliente, "\n")] = '\0'; 

        printf("Digite o Telefone do Cliente:\n");
        fgets(clientes[totalClientes].telefoneCliente, TAMANHO_STR, stdin);  // recebe o telefone do cliente
        clientes[totalClientes].telefoneCliente[strcspn(clientes[totalClientes].telefoneCliente, "\n")] = '\0'; 

        printf("Digite o E-mail do Cliente:\n");
        fgets(clientes[totalClientes].emailCliente, TAMANHO_STR, stdin);  // recebe o email do cliente
        clientes[totalClientes].emailCliente[strcspn(clientes[totalClientes].emailCliente, "\n")] = '\0';

        totalClientes++; 
        printf("Cliente registrado com sucesso!\n\n");
    } else {
        printf("Limite de clientes atingido. Não é possível registrar mais clientes.\n\n");
    }
}
// função consultar registro 
void consultarRegistro(){
    if (numLocacoes > 0) {
    for (int i = 0; i < numLocacoes; i++) { // imprimir os registros de todos os clientes 
        printf("\nLocacao realizada pelo(a) cliente %s\n",clientes[i].nomeCliente);
        printf("Data: %d/%d/%d\n",registro[i].dataLocacao.dia, registro[i].dataLocacao.mes, registro[i].dataLocacao.ano);
        printf("Hora Locacao do automovel: %d:%d\n",registro[i].horaLocacao.hor,registro[i].horaLocacao.min);
        printf("Data de devolucao: %d/%d/%d\n",registro[i].dataDevolucao.dia, registro[i].dataDevolucao.mes, registro[i].dataDevolucao.ano);
        printf("Hora de Devolucao: %d:%d\n",registro[i].horaDevolucao.hor, registro[i].horaDevolucao.min);
        printf("Quilometragem: %.2ld KM\n",registro[i].quilometragem);
        printf("Quilometragem de Devolucao: %.2ld KM\n",registro[i].quilometragemDevolucao);
        printf("Valor Caucao: R$ %.2lf\n",registro[i].valorCaucao);
        printf("Valor Locacao: R$ %.2lf\n",registro[i].valorLocacao);
        printf("Locacao devolvida? %d ",registro[i].locacaoDevolvida); 
            if (registro[i].locacaoDevolvida) { // condição para imprimir sim, caso o usuario digite 1, e não para 1
                printf("Sim.\n\n");
            } else {
                printf("Nao.\n\n");
            }
    }   } else {
        printf("Nenhum veiculo registrado até o momento.\n\n");
    }
}
// função consultar clientes
void ConsultarClientes() {
    if (totalClientes > 0) {
        printf("Lista de Clientes Registrados:\n");
        for (int i = 0; i < totalClientes; i++) { // imprimi todos os clientes registrados
            printf("Cliente %d:\n", i + 1);
            printf("CPF: %s\n", clientes[i].cpfCliente);
            printf("Nome: %s\n", clientes[i].nomeCliente);
            printf("Endereço: %s\n", clientes[i].enderecoCliente);
            printf("Telefone: %s\n", clientes[i].telefoneCliente);
            printf("E-mail: %s\n\n", clientes[i].emailCliente);

            consultarRegistro(); // chama a função consultar registro para ser impresso também junto os registros dos clientes
       }
    } else {
        printf("Nenhum cliente registrado ate o momento.\n\n");
    }
}
// fução principal
int main() {

    int opcoes;
    do {
        printf("\n\t\t\tOpcoes\n\n"); // Mostra aos úsuarios o menu de opções
            // posição que cada um deve ficar
            printf("%-35s%-35s\n", "0 - Sair", "4 - Consultar Automoveis"); 
            printf("%-35s%-35s\n", "1 - Cadastrar Automoveis", "5 - Consultar Modelo");
            printf("%-35s%-35s\n", "2 - Registrar Locacao", "6 - Consultar Marca");
            printf("%-35s%-35s\n", "3 - Cadastrar Cliente", "7 - Consultar Cliente");
    
            printf("\n%-35s%-35s\n", "8 - Salvar Cadastro de automovel", "11 - Ler do arquivo cadastro do automovel");
            printf("%-35s\n", "9 - Salvar Modelo em arquivo");
            printf("%-35s\n\n", "10 - Salvar marca em arquivo");
            printf("Digite uma opcao: "); // receber opação

        scanf("%d", &opcoes);
        limpaBuffer(); // chama a função limpar buffer para limpar a memoria 
        // compara opcoes
        switch (opcoes) {
            // caso digite uma das opcoes sera direciondo para a função escolhida
            case 1:
                cadastrarVeiculo(); 
                break;
            case 2:
                RegistrarLocacao();
                break;
            case 3:
                CadastrarClientes();
                break;

            case 4:
                consultarVeiculos();
                break;
            
            case 5:
                consultarModelo();
                break;
            case 6:
                consultarMarca();
                break;

            case 7:
                ConsultarClientes();
                break;

            case 8:
                salvarCasdastroAutomovelArquivo();
                break;

            case 9:
                salvarNoAquirvoModelo();
                break;
            case 10:
                salvarNoAquirvoMarca();
                break;

            case 11:
                lerDoarquivoCadastroAutomovel();
                break;

            case 0:
                printf("Saindo...\n"); // se digitar 0 é imoresso na tela
                break; // finaliza
            default:
                printf("Opção inválida!\n");
        }
    } while (opcoes != 0); // o loop continua enquanto for diferente de zero

    return 0;
}

