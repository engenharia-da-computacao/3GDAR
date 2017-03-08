/**  Usando "#pragma once" para não precisar incluir as bibliotecas do main.c novamente */
#pragma once

/*********************************************************************
****************** Criando contantes do sistema **********************
**********************************************************************/
// Constantes de validação do sistema
#define IDADE_MIN 16
#define PESO_MIN 50
#define CHAR_NULL "PN"

// Contantes de usuarios do sistema
#define ID_DOADOR 1
#define ID_ORGANIZACAO 2
#define ID_ADM 3
// Constante (nome do aplicativo)
#define NOME_APLICATIVO "#GDAR"
// Nomes de arquivos
#define MENU_PRINCIPAL "res/menus/Menu_Principal.txt"
#define MENU_LOGIN_CADASTRO "res/menus/Menu_Login_Cadastro.txt"
#define MENU_LOGIN_ADM "res/menus/Menu_Login_Adm.txt"

#define ID_MENU_LOGIN_CADASTRO 1
#define ID_MENU_LOGIN_ADM 2

#define MENU_DESKTOP_DOADOR "res/menus/Menu_Desktop_Doador.txt"
#define MENU_DESKTOP_ORG "res/menus/Menu_Desktop_Org.txt"
#define MENU_DESKTOP_ADM "res/menus/Menu_Desktop_Adm.txt"

#define BD_DOADORES "res/Bd_Doadores.data"
#define BD_ORGS "res/Bd_Orgs.data"
#define BD_REQUERIMENTOS "res/Bd_Requerimentos.data"

#define RES_LOG "res/logs.txt"

/*********************************************************************
******************** Criando Tipos de Dados **************************
**********************************************************************/
// Criando o tipo de dado Boolean (bool)
enum boolean {true = 1, false = 0};
typedef enum boolean bool;

// Criando o tipo de dados/estrutura de uma Login
typedef struct
{
    char login[100];
    char senha[100];
} Login ;

// Criando o tipo de dados/estrutura de um Doador
typedef struct
{
    char nome[100];
    int idade;
    float peso;
    int tipoSanguineo;
    Login login;
} Doador;

// Criando o tipo de dados/estrutura de uma Organizacao
typedef struct
{
    char nome[100];
    Login login;
} Organizacao;

// Criando o tipo de dados/estrutura de um Requerimento
typedef struct
{
    char org[100];
    int tipoSangue;
    char localRecolhimento[100];
    char maisInfos[500];
} Requerimento;

// Variaveis para controlar sistema
bool erro = false;
char tiposDeSangue[] = "1 - A+\n2 - A-\n3 - B+\n4 - B-\n5 - AB+\n6 - AB-\n7 - O+\n8 - O-";


/*********************************************************************
******************** Prototipos das funções **************************
**********************************************************************/


void goMenuPrincipal();
void goMenuLoginCadastro(int idUser);
void goUserLogin(int idUser);
void goUserCadastro(int idUser);
void goUserDesktop(int idUser, bool primeiroLogin, char nomeUser[100]);

bool salvarDoador(Doador d);
bool salvarOrg(Organizacao o);
bool salvarRequerimento(Requerimento o);
void novoDoador();
void novaOrg();
void novoRequerimento(char login[100]);
void verRequerimentos(int tipoSangue, char login[100]);
void verRequerimentosDoador(char login[100]);

bool validarLogin(int idUser, Login l);
bool validarDoador(int idade, float peso);
bool validarTipoSanguineo(int tipoSanguineoDoador, int tipoSanguineoRequerimento);

void renderizarMenu();
void listarTiposDeSangue();
void log(char strings[]);
void clean(bool buffer);
void verLogs();
void backup (char arqEntradaString[], char arqSaidaString[]);
void verificaArquivo(char arquivo[]);

void goMenu(int idMenu, int data);

/*********************************************************************
******************** Funções do Sistema **************************
**********************************************************************/

/** Função para controlar os vários menus do sistema */
void goMenu(int idMenu, int data)
{
    if(idMenu == ID_MENU_LOGIN_CADASTRO)
    {
        goMenuLoginCadastro(data);
    }
    else if(idMenu == ID_MENU_LOGIN_ADM)
    {
        goUserLogin(ID_ADM);
    }
}

/** Função da página inicial (Menu Principal) */
void goMenuPrincipal()
{
    int opcaoSelecionada;
    do
    {
        clean(false);


        if(erro == true)
        {
            printf("\n\tOcorreu um erro! Um log de erro foi gerado e analisaremos em breve. :)\n\n");
            erro = false;
        }


        printf("\nBem Vindo ao %s!\n\n", NOME_APLICATIVO);
        renderizarMenu(MENU_PRINCIPAL);

        scanf("%d", &opcaoSelecionada);
        clean(false);

        if(opcaoSelecionada == 1 || opcaoSelecionada == 2)
        {
            goMenu(ID_MENU_LOGIN_CADASTRO, opcaoSelecionada);
        }
        else if(opcaoSelecionada == 3)
        {
            goUserLogin(ID_ADM);
        }
        else if(opcaoSelecionada == 4)
        {
            verRequerimentos(0, CHAR_NULL);
        }
        else if (opcaoSelecionada != 5)
        {
            log("Opção inválida - Menu Principal");
        }

    }
    while(opcaoSelecionada != 5);
    printf("Obrigado por utilizar nosso sistema! =D");

}



/** Função que controla as opções de cadastro/login dos usuários normais */
void goMenuLoginCadastro(int idUser)
{
    int opcaoSelecionada;
    do
    {
        if(idUser == ID_DOADOR)
        {
            printf("\nDoador");
        }
        else
        {
            printf("\nOrganização");
        }
        printf(" - Login|Cadastro\n\n");

        renderizarMenu(MENU_LOGIN_CADASTRO);
        scanf("%d", &opcaoSelecionada);

        if(opcaoSelecionada == 1)
        {
            goUserLogin(idUser);
        }
        else if(opcaoSelecionada == 2)
        {
            goUserCadastro(idUser);
        }
        else if (opcaoSelecionada != 3)
        {
            log("Opção inválida - Menu login/cadastro do usuário normal");
        }

    }
    while(opcaoSelecionada != 3  && erro == false);

}


/** Função que controla o logins dos users */
void goUserLogin(int idUser)
{
    clean(true);
    printf("\nDigite seus dados cadastrados!\n\n");

    Login l;

    printf("Login: ");
    scanf("%s", &l.login);

    printf("Senha: ");
    scanf("%s", &l.senha);

    // Chamando a função que verifica se o login informado existe
    if(validarLogin(idUser, l) == true)
    {
        goUserDesktop(idUser, false, l.login);
    }
    else
    {
        log("Erro, login informado incorreto.");
    }
}

/** Função que mando o user para o form de casdastro referente ao #idUser **/
void goUserCadastro(int idUser)
{
    clean(true);
    if(idUser == ID_DOADOR)
    {
        novoDoador();
    }
    else if (idUser == ID_ORGANIZACAO)
    {
        novaOrg();
    }
}

/** Função que controla os dados de login informados, afim de verificar
* se os mesmos existem no BD, referente ao #idUser
**/
bool validarLogin(int idUser, Login l)
{
    bool ok = false;
    if(idUser == ID_DOADOR)
    {
        FILE *arq = fopen(BD_DOADORES, "rb");
        Doador d;

        fread(&d, sizeof(Doador), 1, arq);
        while(!feof(arq))
        {
            if(strcmp(d.login.login, l.login) == 0 && strcmp(d.login.senha, l.senha) == 0)
            {
                ok = true;
                break;
            }
            fread(&d, sizeof(Doador), 1, arq);
        }
        fclose(arq);
    }
    else if (idUser == ID_ORGANIZACAO)
    {
        FILE *arq = fopen(BD_ORGS, "r");
        Organizacao o;

        fread(&o, sizeof(Organizacao), 1, arq);
        while(!feof(arq))
        {
            if(strcmp(o.login.login, l.login) == 0 && strcmp(o.login.senha, l.senha) == 0)
            {
                ok = true;
                break;
            }
            fread(&o, sizeof(Organizacao), 1, arq);
        }
        fclose(arq);
    }
    else if (idUser == ID_ADM)
    {
        if(strcmp("3gdar", l.login) == 0 && strcmp("3gdar", l.senha) == 0)
        {
            ok = true;
        }
    }

    return ok;
}


/** Função que manda o usuário para sua página privada */
void goUserDesktop(int idUser, bool primeiroLogin, char nomeUser[100])
{
    if(primeiroLogin == true)
    {
        printf("\nCadastro realizado com sucesso!\nAperte ENTER para fazer login...\n\n");
        system("pause");
    }

    int opcaoSelecionada;
    do
    {
        clean(true);
        if(idUser == ID_ORGANIZACAO)
        {
            printf("\nOpções da Organização - %s\n\n", nomeUser);
            renderizarMenu(MENU_DESKTOP_ORG);
        }
        else if(idUser == ID_DOADOR)
        {
            printf("\nOpções do Doador - %s\n\n", nomeUser);
            renderizarMenu(MENU_DESKTOP_DOADOR);
        }
        else if(idUser == ID_ADM)
        {
            printf("\nOpções do Administrador - %s\n\n", nomeUser);
            renderizarMenu(MENU_DESKTOP_ADM);
        }

        scanf("%d", &opcaoSelecionada);
        clean(false);

        if(opcaoSelecionada == 1)
        {
            if(idUser == ID_ORGANIZACAO)
            {
                novoRequerimento(nomeUser);
            }
            else if(idUser == ID_DOADOR)
            {
                verRequerimentosDoador(nomeUser);
            }
            else
            {
                backup(BD_DOADORES, "backup/backupDoadores.backup");
                backup(BD_ORGS, "backup/backupOrg.backup");
                backup(BD_REQUERIMENTOS, "backup/backupRequerimentos.backup");

                printf("\nBackup realizado com sucesso!\n");
                system("pause");
            }
        }
        else if (opcaoSelecionada == 2)
        {
            if(idUser == ID_ORGANIZACAO)
            {
                verRequerimentos(0, nomeUser);
            }
            else if(idUser == ID_DOADOR)
            {
                verRequerimentos(0, CHAR_NULL);
            }
            else
            {
                verLogs();
            }
        }
        else if (opcaoSelecionada != 3)
        {
            log("Opção inválida - Menu Desktop");
        }

    }
    while(opcaoSelecionada != 3 && erro == false);
}

/** Função que salva um Doador no BD */
bool salvarDoador(Doador doa)
{
    // Verificando se exite o login já cadastrado
    Doador d;
    bool ok = false;
    FILE *arq;
    arq = fopen(BD_DOADORES, "rb");
    fread(&d, sizeof(Doador), 1, arq);
    while(!feof(arq))
    {
        if(strcmp(d.login.login, doa.login.login) == 0)
        {
            ok = true;
            break;
        }
        fread(&d, sizeof(Doador), 1, arq);
    }

    if(ok == true)
    {
        log("Login de Doador já cadastrado.");
    }
    else
    {
        // Salvando
        FILE *f = fopen(BD_DOADORES, "ab");
        fwrite(&doa, sizeof(Doador), 1, f);
        fclose(f);
    }
    return ok;

}
/** Função que salva um Org no BD */
bool salvarOrg(Organizacao o)
{
    // Verificando se exite o login já cadastrado
    Organizacao org;
    bool ok = false;
    FILE *arq = fopen(BD_ORGS, "rb");
    fread(&org, sizeof(Organizacao), 1, arq);
    while(!feof(arq))
    {
        if(strcmp(org.login.login, o.login.login) == 0)
        {
            ok = true;
            break;
        }
        fread(&org, sizeof(Organizacao), 1, arq);
    }
    if(ok == true)
    {
        log("Login de Doador já cadastrado.");
    }
    else
    {
        // Salvando
        FILE *f = fopen(BD_ORGS, "ab");
        fwrite(&o, sizeof(Organizacao), 1, f);
        fclose(f);
    }

    return ok;
}

/** Função que salva um Requerimento no BD */
bool salvarRequerimento(Requerimento o)
{
    // Salvando
    FILE *f = fopen(BD_REQUERIMENTOS, "ab");
    fwrite(&o, sizeof(Requerimento), 1, f);
    fclose(f);

    return true;
}


/** Função obtem os dados de um novo Doador */
void novoDoador()
{
    Doador d;
    printf("\nDigite seus dados\n\n");

    printf("Nome: ");
    gets(d.nome);

    fflush(stdin);

    printf("Login: ");
    gets(d.login.login);

    fflush(stdin);

    printf("Senha: ");
    gets(d.login.senha);

    fflush(stdin);

    printf("Idade: ");
    scanf("%d", &d.idade);

    printf("Peso: ");
    scanf("%f", &d.peso);

    getchar();

    listarTiposDeSangue();
    fflush(stdin);
    printf("Tipo Sanguineo: ");
    scanf("%d", &d.tipoSanguineo);

    fflush(stdin);
    clean(true);


    // Se os dados informados forem validos, salva o Doador no BD.
    // Caso não, mostra um erro e volta para página anterior
    if(validarDoador(d.idade, d.peso) == true)
    {
        // Se o Doador for salvo com sucesso, manda para sua aréa de trabalho.
        // Caso não, mostra um erro e volta para página anterior
        if(salvarDoador(d) == false)
        {
            goUserDesktop(ID_DOADOR, true, d.login.login);
        }
        else
        {
            log("Ocorreu um erro ao tentar salvar um novo usuário (Doador)");
        }

    }
    else
    {
        log("Dados de novo usuário (Doador) não válidos");
    }
}


/** Função obtem os dados de uma nova Org */
void novaOrg()
{
    Organizacao o;
    printf("\nDigite seus dados\n\n");

    printf("Nome: ");
    gets(o.nome);

    printf("Login: ");
    gets(o.login.login);

    printf("Senha: ");
    gets(o.login.senha);

    clean(true);

    if(salvarOrg(o) == false)
    {
        goUserDesktop(ID_ORGANIZACAO, true, o.login.login);
    }
    else
    {
        log("Ocorreu um erro ao tentar salvar um novo usuário (Org)");
    }
}

void novoRequerimento(char login[])
{
    clean(true);
    Requerimento o;
    printf("\nDigite seus dados\n\n");

    // Salvando o login
    strcpy(o.org, login);

    printf("Local de Recolhimento: ");
    gets(o.localRecolhimento);

    listarTiposDeSangue();
    printf("Tipo sanguineo: ");
    scanf("%d", &o.tipoSangue);

    fflush(stdin);

    printf("Mais Informações: ");
    gets(o.maisInfos);

    clean(true);

    if(salvarRequerimento(o) == true)
    {
        printf("\nRequerimento salvo com sucesso!\n");
        system("pause");
    }
    else
    {
        log("Ocorreu um erro ao tentar salvar um novo requerimento");
    }
}

void verRequerimentos(int tipoSangue, char login[100])
{
    printf("\nRelação de Requerimentos\n\n");

    listarTiposDeSangue();

    Requerimento r;
    FILE *arq = fopen(BD_REQUERIMENTOS, "rb");

    fread(&r, sizeof(Requerimento), 1, arq);

    while(!feof(arq))
    {
        if( tipoSangue != 0)
        {
            if(validarTipoSanguineo(tipoSangue, r.tipoSangue) == true)
            {
                // Doador
                printf("\n\nLocal: %s", r.localRecolhimento);
                printf("\nTipo sanguineo: %d", r.tipoSangue);
                printf("\nMais Informações: %s", r.maisInfos);
            }
        }
        else if(strcmp(CHAR_NULL, login) != 0)
        {
            if(strcmp(r.org, login) == 0)
            {
                // Org
                printf("\n\nLocal: %s", r.localRecolhimento);
                printf("\nTipo sanguineo: %d", r.tipoSangue);
                printf("\nMais Informações: %s", r.maisInfos);
            }
        }
        else
        {
            // Doador, ver todos
            printf("\n\nLocal: %s", r.localRecolhimento);
            printf("\nTipo sanguineo: %d", r.tipoSangue);
            printf("\nMais Informações: %s", r.maisInfos);
        }

        fread(&r, sizeof(Requerimento), 1, arq);
    }

    printf("\n\n\nAperte ENTER para voltar ao menu anterior...\n");
    system("pause");
}

void verRequerimentosDoador(char login[100])
{
    // Buscando tipo de sangue
    Doador d;
    FILE *arq = fopen(BD_DOADORES, "r");
    fread(&d, sizeof(Doador), 1, arq);
    int tipoDeSangue;
    while(!feof(arq))
    {
        if(strcmp(d.login.login, login) == 0)
        {
           tipoDeSangue = d.tipoSanguineo;
            break;
        }
        fread(&d, sizeof(Doador), 1, arq);
    }

    fclose(arq);

    verRequerimentos(tipoDeSangue, CHAR_NULL);
}


/**
* Função que valida os dados do Doador, afim de verificar
* se ele está apto a realizar a doação.
* Validado peso e idade.
*/
bool validarDoador(int idade, float peso)
{
    if (idade < IDADE_MIN || peso < PESO_MIN )
    {
        return false;
    }
    else
    {
        return true;
    }
}

/** Função que cria um log de erro em um arquivo */
void log(char strings[])
{
    // Salvando log vindo do parametro (char strings[])
    FILE *arq = fopen(RES_LOG, "a");
    fprintf(arq, "%s\n", strings);
    fclose(arq);
    // Setando erro igual a true para mostrar mensagem de erro no Menu Principal
    erro = true;
}

/** Função que limpa a tela e/ou o buffer de mémoria **/
void clean(bool buffer)
{
    // Limpa a tela
    system("cls");
    if(buffer == true)
    {
        // Limpa o buffer de mémoria
        fflush(stdin);
    }
}

/** Função que configura o console **/
void configConsole()
{
    // Texto configurado para Portugues
    setlocale(LC_ALL, "Portuguese");
    // Modo de abertura do console
    system ("mode con:cols=100 lines=30");
    // Cor da tela e fonte do console
    system ("color 47");
    // Titulo do console
    system ("title #GDAR - Ctrl + S a life");
}

/** Função que controla os menus para renderizá-los **/
void renderizarMenu(char menu[])
{
    FILE *arq = fopen(menu, "r");
    if(arq == NULL)
    {
        log("Erro, nao foi possivel abrir o arquivo");
    }
    else
    {
        char ch;
        while( (ch = fgetc(arq))!= EOF )
        {
            putchar(ch);
        }

    }
    fclose(arq);
}


void backup (char arqEntradaString[], char arqSaidaString[])
{
    int ch;

    FILE *arqEntrada = fopen(arqEntradaString, "r");
    FILE *arqSaida = fopen(arqSaidaString, "w");

    while ((ch = fgetc (arqEntrada)) != EOF)
    {
        fputc (ch, arqSaida);
    }

    fclose(arqEntrada);
    fclose(arqSaida);

}

void verLogs()
{
    FILE *arq = fopen(RES_LOG, "r");

    char ch;
    while( (ch = fgetc(arq))!= EOF )
    {
        putchar(ch);
    }

    fclose(arq);

    printf("\n\nAperte ENTER para voltar ao menu anterior...\n");
    system("pause");
}

/** Validando o tipo de sangue do doador, afim de saber se ele poderá doar para o tipo do requerimento **/
bool validarTipoSanguineo(int tipoSanguineoDoador,int tipoSanguineoRequerimento)
{
    bool ok = false;
    if(tipoSanguineoDoador == 1)
    {
        if(tipoSanguineoRequerimento == 1 || tipoSanguineoRequerimento == 5)
        {
            ok = true;
        }
    }
    else if (tipoSanguineoDoador == 2)
    {
        if(tipoSanguineoRequerimento == 1 || tipoSanguineoRequerimento == 2 || tipoSanguineoRequerimento == 5 || tipoSanguineoRequerimento == 6)
        {
            ok = true;
        }
    }
    else if (tipoSanguineoDoador == 3)
    {
        if(tipoSanguineoRequerimento == 3 || tipoSanguineoRequerimento == 5)
        {
            ok = true;
        }
    }
    else if (tipoSanguineoDoador == 4)
    {
        if(tipoSanguineoRequerimento == 3 || tipoSanguineoRequerimento == 4 || tipoSanguineoRequerimento == 5 || tipoSanguineoRequerimento == 6)
        {
            ok = true;
        }

    }
    else if (tipoSanguineoDoador == 5)
    {
        if(tipoSanguineoRequerimento == 5)
        {
            ok = true;
        }

    }
    else if(tipoSanguineoDoador == 6)
    {
        if(tipoSanguineoRequerimento == 5 || tipoSanguineoRequerimento == 6 )
        {
            ok = true;
        }

    }
    else if (tipoSanguineoDoador == 7)
    {
        if(tipoSanguineoRequerimento == 1 || tipoSanguineoRequerimento == 3 || tipoSanguineoRequerimento == 7 || tipoSanguineoRequerimento == 5)
        {
            ok = true;
        }
    }
    else if (tipoSanguineoDoador == 8)
    {
        ok = true;
    }
    return ok;
}

void listarTiposDeSangue()
{
    printf("\n%s\n", tiposDeSangue);
}

void verificaArquivo(char arquivo[]){
   if(fopen(arquivo,"rb") == NULL){
        FILE *arqCria = fopen(arquivo, "wb");
        fclose(arqCria);
    }
}
