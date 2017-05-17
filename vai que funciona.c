#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

volatile int exit_program = FALSE;

void fechar_programa()
{
    exit_program = TRUE;
}
END_OF_FUNCTION(fechar_programa);

int main()
{
    int caret = 0;

  int NUM_ITENS = 20;

  char animal[20][12] = { "CAVALO", "BORBOLETA", "CARANGUEJO",
      "GATO", "CROCODILO", "ESCARAVELHO", "ROUXINOL", "JABUTI",
      "GAFANHOTO", "RINOCERONTE", "GORILA", "LEOPARDO", "COTIA",
      "ARARA", "OSTRA", "CAPIVARA", "EQUIDNA", "CARNEIRO", "GOLFINHO",
      "SUCURI" };

  char comida[20][12] = { "EMPADA", "COOKIE", "FEIJOADA", "COXINHA",
      "BRIGADEIRO", "CHURRASCO", "LASANHA", "MACARRONADA", "TORTA",
      "TORRADA", "PIZZA", "PANQUECA", "PIPOCA", "PAMONHA", "OVO",
      "CREPE", "CROISSANT", "PICLES", "BISCOITO", "BOLO" };

  char fruta[20][12] = { "ABACATE", "BANANA", "CARAMBOLA", "DAMASCO", "ACEROLA",
      "GOIABA", "JABUTICABA", "KIWI", "LARANJA", "MELANCIA", "MANGA",
      "GRAVIOLA", "PINHA", "PITOMBA", "CAJU", "TANGERINA", "TOMATE",
      "TAMARINDO", "UVA", "UMBU" };

  char objeto[20][12] = { "ABAJUR", "MOCHILA", "BICICLETA",
      "COMPUTADOR", "GUITARRA", "COTOVELEIRA", "AMORTECEDOR", "ESCAPAMENTO",
      "NEBULIZADOR", "SABONETEIRA", "GARGANTILHA", "DESPERTADOR", "DESODORANTE",
      "PENTEADEIRA", "ESPARADRAPO", "MOSQUITEIRO", "CORTINAS", "ESPELHO",
      "ESCORREDOR", "CASTANHOLAS" };

  char tv[20][12] = { "SENSE8", "VIKINGS", "ARROW", "GOTHAM",
      "LUCIFER", "SUPERGIRL", "FRIENDS", "SCANDAL", "BLINDSPOT", "WESTWORLD",
      "REIGN", "OUTLANDER", "IZOMBIE", "DEMOLIDOR", "SCREAM", "NARCOS",
      "GRIMM", "DEXTER", "FRONTIER", "SHERLOCK" };


  int i = 0;

  char voltarMenu;
  char *palavra;
  char *dica;
  char acertos[20];
  char palpite;

  dica = (char*)malloc(sizeof(char)*20);
  memset(dica,(char)0,sizeof(char)*20);

  palavra = (char*)malloc(sizeof(char)*12);
  memset(palavra,(char)0,sizeof(char)*12);

  char essa_dica[20];
  char essa_palavra[12];
  int leitura, leitura_dica, leitura_palp;
  int botao, botao_dica;

  int contemPalpite = 0;
  int opc = 0;
  int tema = 0;
  char *letrasUsadas;
  int numLetrasUsadas = 0;
  int usada;
  int erros = 0;
  int tam;

  letrasUsadas = (char*)malloc(sizeof(char)*26);
  memset(letrasUsadas,(char)0,sizeof(char)*26);


   allegro_init();
   install_timer();
   install_keyboard();
   set_color_depth(32);
   set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
   set_window_title("Jogo da Forca 1.0");
   LOCK_VARIABLE(exit_program);
   LOCK_FUNCTION(fechar_programa);
   set_close_button_callback(fechar_programa);


   FONT* fontizinha = load_font("minha_fonte1.pcx", NULL, NULL);
   FONT* menuzinho = load_font("menu.pcx", NULL, NULL);
   FONT* ari = load_font("arial.pcx", NULL, NULL);
   FONT* nova = load_font("nova_fonte.pcx", NULL, NULL);
   FONT* titulo = load_font("titulo.pcx", NULL, NULL);
   FONT* body = load_font("corpo.pcx", NULL, NULL);
   FONT* avisos = load_font("avisos.pcx", NULL, NULL);
   FONT* esc1 = load_font("esc.pcx", NULL, NULL);
   FONT* dicat = load_font("dica.pcx", NULL, NULL);
   FONT* palavra1 = load_font("palavra.pcx", NULL, NULL);
   FONT* perdeu = load_font("perdeu.pcx", NULL, NULL);


   BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
   BITMAP* fundinho = load_bitmap("fundo_2.bmp", NULL);
   BITMAP* arvorezinha = load_bitmap("arvoreajeitada_1.bmp", NULL);
   BITMAP* boneco = load_bitmap("Boneco_c.bmp", NULL);
   BITMAP* cabeca = load_bitmap("Boneco_cabeca.bmp", NULL);
   BITMAP* corpo = load_bitmap("Boneco_corpo.bmp", NULL);
   BITMAP* braco_um = load_bitmap("Boneco_um_b.bmp", NULL);
   BITMAP* braco_dois = load_bitmap("Boneco_dois_b.bmp", NULL);
   BITMAP* perna = load_bitmap("Boneco_perna.bmp", NULL);

   memset(acertos,(char)0,sizeof(char)*12);


   while(!key[KEY_ESC])
   {

       draw_sprite(buffer, fundinho, 0, 0);
       textout_centre_ex(buffer, titulo, "JOGO DA FORCA", SCREEN_W/2, 100, makecol(0, 0, 0), -1);
       textout_centre_ex(buffer, nova, "Escolha o modo do jogo:", SCREEN_W/2, 200, makecol(0, 0, 0), -1);
       textout_centre_ex(buffer, body, "[1] - Palavras Sorteadas (1 Jogador)", SCREEN_W/2, 240, makecol(0, 0, 0), -1);
       textout_centre_ex(buffer, body, "[2] - Palavra Personalizada (2 Jogadores)", SCREEN_W/2, 280, makecol(0, 0, 0), -1);
       textout_centre_ex(buffer, esc1, "Pressione [ESC] para sair", SCREEN_W/2, 550, makecol(0, 0, 0), -1);
       textout_centre_ex(buffer, avisos, "Controle do Jogo: Teclado.", SCREEN_W/2, 360, makecol(0, 0, 0), -1);
       textout_centre_ex(buffer, avisos, "OBS: Uso de palavras sem acentos.", SCREEN_W/2, 400, makecol(0, 0, 0), -1);

       draw_sprite(screen, buffer, 0, 0);

       leitura = readkey();
       botao = leitura >> 8;

  if(botao == KEY_1 || botao == KEY_1_PAD)
  {
    clear(screen);
    while(botao_dica != KEY_ESC && botao_dica != KEY_1 && botao_dica != KEY_2 && botao_dica != KEY_3 && botao_dica != KEY_4 && botao_dica != KEY_5)
    {
        draw_sprite(buffer, fundinho, 0, 0);
        textprintf_centre_ex(buffer, nova, SCREEN_W/2, 100, makecol(0, 0, 0), -1, "Escolha o tema para jogar:");
        textprintf_centre_ex(buffer, avisos, 300, 200, makecol(0, 0, 0), -1, "[1] - Animais");
        textprintf_centre_ex(buffer, avisos, 298, 240, makecol(0, 0, 0), -1, "[2] - Comida");
        textprintf_centre_ex(buffer, avisos, 290, 280, makecol(0, 0, 0), -1, "[3] - Frutas");
        textprintf_centre_ex(buffer, avisos, 295, 320, makecol(0, 0, 0), -1, "[4] - Objetos");
        textprintf_centre_ex(buffer, avisos, 351, 360, makecol(0, 0, 02), -1, "[5] - Seriados");
        textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
        draw_sprite(screen, buffer, 0, 0);
        leitura_dica = readkey();
        botao_dica = leitura_dica >> 8;
    }

        if(botao_dica == KEY_1 || botao_dica == KEY_1_PAD)
        {
            strcpy(dica, "Animal");
            srand(time(NULL));
            strcpy(palavra, animal[rand() % NUM_ITENS]);
            tam = strlen(palavra);

            for (i = 0; i < strlen(palavra); i++)
            {
                acertos[i] = '_';
            }

            while(!key[KEY_ESC])
            {
                  int conter = 0;
                  int tamanho_palavra = strlen(palavra);
                  draw_sprite(buffer, fundinho, 0, 0);
                  draw_sprite(buffer, arvorezinha, 20, 25);
                  textprintf_ex(buffer, dicat, 40, 20, makecol(0, 0, 0), -1, "Tema: %s", dica);
                  textprintf_ex(buffer, dicat, 50, 390, makecol(0, 0, 0), -1, "Digite uma Letra");
                  textprintf_ex(buffer, dicat, 40, 40, makecol(0, 0, 0), -1, "Quantidade de Letras da Palavra: %d", tam);

                  acertos[strlen(palavra)] = '\0';

                  textprintf_ex(buffer, palavra1, 50, 480, makecol(0, 0, 0), -1, "%s", acertos);

                  textprintf_ex(buffer, dicat, 40, 60, makecol(0, 0, 0), -1, "Letras Usadas: %s", letrasUsadas);

                  if(erros == 1)
                  {
                    draw_sprite(buffer, cabeca, 403, 295);
                  }
                  if(erros == 2)
                  {
                    draw_sprite(buffer, corpo, 403, 295);
                  }

                  if(erros == 3)
                  {
                    draw_sprite(buffer, braco_um, 403, 295);
                  }

                  if(erros == 4)
                  {
                    draw_sprite(buffer, braco_dois, 403, 295);
                  }

                  if(erros == 5)
                  {
                    draw_sprite(buffer, perna, 403, 295);
                  }

                  if(erros == 6)
                  {
                    clear(buffer);
                    while(!key[KEY_ESC])
                    {
                        draw_sprite(buffer, boneco, 403, 295);
                        draw_sprite(buffer, fundinho, 0, 0);
                        textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(0, 0, 0), -1, "PERDEU!");
                        textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                        textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Palavra Correta: %s", palavra);
                        draw_sprite(screen, buffer, 0, 0);
                    }
                  }

                  if (strncmp(palavra, acertos, 12) == 0)
                  {
                    clear(buffer);
                    while(!key[KEY_ESC])
                    {
                        draw_sprite(buffer, boneco, 403, 295);
                        draw_sprite(buffer, fundinho, 0, 0);
                        textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(0, 0, 0), -1, "GANHOU!");
                        textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Palavra Correta: %s", palavra);
                        textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                        draw_sprite(screen, buffer, 0, 0);
                    }
                  }

                  draw_sprite(screen, buffer, 0, 0);

                  if (strcmp(palavra, acertos) != 0 && erros != 6)
                  {
                    usada = 0;
                    leitura_palp = readkey();
                    palpite = leitura_palp & 0xff;
                    palpite = toupper(palpite);

                    for(i = 0; i < 26; i++)
                    {
                        if(letrasUsadas[i] == palpite)
                        {
                            usada = 1;
                        }
                    }

                    if(usada == 0)
                    {
                        letrasUsadas[numLetrasUsadas] = palpite;
                        numLetrasUsadas++;
                        contemPalpite = 0;

                        for(i = 0; i < tamanho_palavra; i++)
                        {
                            if(palpite == palavra[i])
                            {
                                acertos[i] = palpite;
                                contemPalpite = 1;
                            }
                        }

                        if(contemPalpite == 0)
                        {
                            erros++;
                        }
                    }
                }
            }
        }

        if(botao_dica == KEY_2 || botao_dica == KEY_2_PAD)
        {
            strcpy(dica, "Comida");
            srand(time(NULL));
            strcpy(palavra, comida[rand() % NUM_ITENS]);
            tam = strlen(palavra);

            for (i = 0; i < strlen(palavra); i++)
            {
                acertos[i] = '_';
            }

            while(!key[KEY_ESC])
            {
                int conter = 0;
                int tamanho_palavra = strlen(palavra);
                draw_sprite(buffer, fundinho, 0, 0);
                draw_sprite(buffer, arvorezinha, 20, 25);
                textprintf_ex(buffer, dicat, 40, 20, makecol(0, 0, 0), -1, "Tema: %s", dica);
                textprintf_ex(buffer, dicat, 50, 390, makecol(0, 0, 0), -1, "Digite uma Letra");
                textprintf_ex(buffer, dicat, 40, 40, makecol(0, 0, 0), -1, "Quantidade de Letras da Palavra: %d", tam);

                acertos[strlen(palavra)] = '\0';

                textprintf_ex(buffer, palavra1, 50, 480, makecol(0, 0, 0), -1, "%s", acertos);

                textprintf_ex(buffer, dicat, 40, 60, makecol(0, 0, 0), -1, "Letras Usadas: %s", letrasUsadas);

                if(erros == 1)
                {
                    draw_sprite(buffer, cabeca, 403, 295);
                }

                if(erros == 2)
                {
                    draw_sprite(buffer, corpo, 403, 295);
                }

                if(erros == 3)
                {
                    draw_sprite(buffer, braco_um, 403, 295);
                }

                if(erros == 4)
                {
                    draw_sprite(buffer, braco_dois, 403, 295);
                }

                if(erros == 5)
                {
                    draw_sprite(buffer, perna, 403, 295);
                }

                if(erros == 6)
                {
                    clear(buffer);
                    while(!key[KEY_ESC])
                    {
                        draw_sprite(buffer, boneco, 403, 295);
                        draw_sprite(buffer, fundinho, 0, 0);
                        textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(0, 0, 0), -1, "PERDEU!");
                        textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                        textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Palavra Correta: %s", palavra);
                        draw_sprite(screen, buffer, 0, 0);
                    }
                }

                if (strncmp(palavra, acertos, 12) == 0)
                {
                    clear(buffer);
                    while(!key[KEY_ESC])
                    {
                        draw_sprite(buffer, boneco, 403, 295);
                        draw_sprite(buffer, fundinho, 0, 0);
                        textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(102, 38, 40), -1, "GANHOU!");
                        textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(102, 38, 40), -1, "Palavra Correta: %s", palavra);
                        textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                        draw_sprite(screen, buffer, 0, 0);
                    }
                }

                draw_sprite(screen, buffer, 0, 0);

                if (strcmp(palavra, acertos) != 0 && erros != 6)
                {
                    usada = 0;
                    leitura_palp = readkey();
                    palpite = leitura_palp & 0xff;
                    palpite = toupper(palpite);

                    for(i = 0; i < 26; i++)
                    {
                        if(letrasUsadas[i] == palpite)
                        {
                            usada = 1;
                        }
                    }

                    if(usada == 0)
                    {
                        letrasUsadas[numLetrasUsadas] = palpite;
                        numLetrasUsadas++;
                        contemPalpite = 0;

                        for(i = 0; i < tamanho_palavra; i++)
                        {
                            if(palpite == palavra[i])
                            {
                                acertos[i] = palpite;
                                contemPalpite = 1;
                            }
                        }

                        if(contemPalpite == 0)
                        {
                            erros++;
                        }
                    }
                }
            }
        }

        if(botao_dica == KEY_3 || botao_dica == KEY_3_PAD)
        {
            strcpy(dica, "Fruta");
            srand(time(NULL));
            strcpy(palavra, fruta[rand() % NUM_ITENS]);
            tam = strlen(palavra);

            for (i = 0; i < strlen(palavra); i++)
            {
                acertos[i] = '_';
            }

            while(!key[KEY_ESC])
            {
                int conter = 0;
                int tamanho_palavra = strlen(palavra);
                draw_sprite(buffer, fundinho, 0, 0);
                draw_sprite(buffer, arvorezinha, 20, 25);
                textprintf_ex(buffer, dicat, 40, 20, makecol(0, 0, 0), -1, "Tema: %s", dica);
                textprintf_ex(buffer, dicat, 50, 390, makecol(0, 0, 0), -1, "Digite uma Letra");
                textprintf_ex(buffer, dicat, 40, 40, makecol(0, 0, 0), -1, "Quantidade de Letras da Palavra: %d", tam);

                acertos[strlen(palavra)] = '\0';

                textprintf_ex(buffer, palavra1, 50, 480, makecol(0, 0, 0), -1, "%s", acertos);

                textprintf_ex(buffer, dicat, 40, 60, makecol(0, 0, 0), -1, "Letras Usadas: %s", letrasUsadas);

                if(erros == 1)
                {
                    draw_sprite(buffer, cabeca, 403, 295);
                }

                if(erros == 2)
                {
                    draw_sprite(buffer, corpo, 403, 295);
                }

                if(erros == 3)
                {
                    draw_sprite(buffer, braco_um, 403, 295);
                }

                if(erros == 4)
                {
                    draw_sprite(buffer, braco_dois, 403, 295);
                }

                if(erros == 5)
                {
                    draw_sprite(buffer, perna, 403, 295);
                }

                if(erros == 6)
                {
                    clear(buffer);
                    while(!key[KEY_ESC])
                    {
                        draw_sprite(buffer, boneco, 403, 295);
                        draw_sprite(buffer, fundinho, 0, 0);
                        textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(0, 0, 0), -1, "PERDEU!");
                        textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                        textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Palavra Correta: %s", palavra);
                        draw_sprite(screen, buffer, 0, 0);
                    }
                }

                if (strncmp(palavra, acertos, 12) == 0)
                {
                    clear(buffer);
                    while(!key[KEY_ESC])
                    {
                        draw_sprite(buffer, boneco, 403, 295);
                        draw_sprite(buffer, fundinho, 0, 0);
                        textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(0, 0, 0), -1, "GANHOU!");
                        textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Palavra Correta: %s", palavra);
                        textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                        draw_sprite(screen, buffer, 0, 0);
                    }
                }

                draw_sprite(screen, buffer, 0, 0);

                if (strcmp(palavra, acertos) != 0 && erros != 6)
                {
                    usada = 0;
                    leitura_palp = readkey();
                    palpite = leitura_palp & 0xff;
                    palpite = toupper(palpite);

                    for(i = 0; i < 26; i++)
                    {
                        if(letrasUsadas[i] == palpite)
                        {
                            usada = 1;
                        }
                    }

                    if(usada == 0)
                    {
                        letrasUsadas[numLetrasUsadas] = palpite;
                        numLetrasUsadas++;
                        contemPalpite = 0;

                        for(i = 0; i < tamanho_palavra; i++)
                        {
                            if(palpite == palavra[i])
                            {
                            acertos[i] = palpite;
                            contemPalpite = 1;
                            }
                        }

                        if(contemPalpite == 0)
                        {
                            erros++;
                        }
                    }
                }
}

        }
        if(botao_dica == KEY_4 || botao_dica == KEY_4_PAD)
        {
            strcpy(dica, "Objeto");
            srand(time(NULL));
            strcpy(palavra, objeto[rand() % NUM_ITENS]);
            tam = strlen(palavra);

            for (i = 0; i < strlen(palavra); i++)
                            {
                              acertos[i] = '_';
                            }

            while(!key[KEY_ESC])
                            {
                              int conter = 0;
                              int tamanho_palavra = strlen(palavra);
                              draw_sprite(buffer, fundinho, 0, 0);
                              draw_sprite(buffer, arvorezinha, 20, 25);
                              textprintf_ex(buffer, dicat, 40, 20, makecol(0, 0, 0), -1, "Dica: %s", dica);
                              textprintf_ex(buffer, dicat, 50, 390, makecol(0, 0, 0), -1, "Digite uma Letra");
                              textprintf_ex(buffer, dicat, 40, 40, makecol(0, 0, 0), -1, "Quantidade de Letras da Palavra: %d", tam);

                              acertos[strlen(palavra)] = '\0';

                              textprintf_ex(buffer, palavra1, 50, 480, makecol(0, 0, 0), -1, "%s", acertos);

                              textprintf_ex(buffer, dicat, 40, 60, makecol(0, 0, 0), -1, "Letras Usadas: %s", letrasUsadas);

                              if(erros == 1)
                                {
                                    draw_sprite(buffer, cabeca, 403, 295);
                                }
                                if(erros == 2)
                                {
                                    draw_sprite(buffer, corpo, 403, 295);
                                }
                                if(erros == 3)
                                {
                                    draw_sprite(buffer, braco_um, 403, 295);
                                }
                                if(erros == 4)
                                {
                                    draw_sprite(buffer, braco_dois, 403, 295);
                                }
                                if(erros == 5)
                                {
                                    draw_sprite(buffer, perna, 403, 295);
                                }
                                if(erros == 6)
                                {
                                  clear(buffer);
                                  while(!key[KEY_ESC])
                                  {
                                    draw_sprite(buffer, boneco, 403, 295);
                                    draw_sprite(buffer, fundinho, 0, 0);
                                    textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(0, 0, 0), -1, "PERDEU!");
                                    textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                                    textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Palavra Correta: %s", palavra);
                                    draw_sprite(screen, buffer, 0, 0);
                                  }
                                }
                                if (strncmp(palavra, acertos, 12) == 0)
                                {
                                  clear(buffer);
                                  while(!key[KEY_ESC])
                                  {
                                    draw_sprite(buffer, boneco, 403, 295);
                                    draw_sprite(buffer, fundinho, 0, 0);
                                    textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(0, 0, 0), -1, "GANHOU!");
                                    textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Palavra Correta: %s", palavra);
                                    textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                                    draw_sprite(screen, buffer, 0, 0);
                                  }
                                }

                                draw_sprite(screen, buffer, 0, 0);

                              if (strcmp(palavra, acertos) != 0 && erros != 6)
                              {
                                usada = 0;
                                leitura_palp = readkey();
                                palpite = leitura_palp & 0xff;
                                palpite = toupper(palpite);

                                for(i = 0; i < 26; i++)
                                {
                                  if(letrasUsadas[i] == palpite)
                                  {
                                    usada = 1;
                                  }
                                }

                                if(usada == 0)
                                {
                                  letrasUsadas[numLetrasUsadas] = palpite;
                                  numLetrasUsadas++;
                                  contemPalpite = 0;

                                    for(i = 0; i < tamanho_palavra; i++)
                                    {
                                      if(palpite == palavra[i]) {
                                        acertos[i] = palpite;
                                        contemPalpite = 1;
                                      }
                                    }

                                    if(contemPalpite == 0)
                                    {
                                      erros++;
                                    }
                                  }

                                }

                            }

        }

        if(botao_dica == KEY_5 || botao_dica == KEY_5_PAD)
        {
            strcpy(dica, "Programs de TV:");
            srand(time(NULL));
            strcpy(palavra, tv[rand() % NUM_ITENS]);
            tam = strlen(palavra);

            for (i = 0; i < strlen(palavra); i++)
            {
                acertos[i] = '_';
            }

            while(!key[KEY_ESC])
            {
                int conter = 0;
                int tamanho_palavra = strlen(palavra);
                draw_sprite(buffer, fundinho, 0, 0);
                draw_sprite(buffer, arvorezinha, 20, 25);
                textprintf_ex(buffer, dicat, 40, 20, makecol(0, 0, 0), -1, "Dica: %s", dica);
                textprintf_ex(buffer, dicat, 50, 390, makecol(0, 0, 0), -1, "Digite uma Letra");
                textprintf_ex(buffer, dicat, 40, 40, makecol(0, 0, 0), -1, "Quantidade de Letras da Palavra: %d", tam);

                acertos[strlen(palavra)] = '\0';

                textprintf_ex(buffer, palavra1, 50, 480, makecol(0, 0, 0), -1, "%s", acertos);

                textprintf_ex(buffer, dicat, 40, 60, makecol(0, 0, 0), -1, "Letras Usadas: %s", letrasUsadas);

                if(erros == 1)
                {
                    draw_sprite(buffer, cabeca, 403, 295);
                }

                if(erros == 2)
                {
                    draw_sprite(buffer, corpo, 403, 295);
                }

                if(erros == 3)
                {
                    draw_sprite(buffer, braco_um, 403, 295);
                }

                if(erros == 4)
                {
                    draw_sprite(buffer, braco_dois, 403, 295);
                }

                if(erros == 5)
                {
                    draw_sprite(buffer, perna, 403, 295);
                }

                if(erros == 6)
                {
                    clear(buffer);
                    while(!key[KEY_ESC])
                    {
                        draw_sprite(buffer, boneco, 403, 295);
                        draw_sprite(buffer, fundinho, 0, 0);
                        textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(0, 0, 0), -1, "PERDEU!");
                        textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                        textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Palavra Correta: %s", palavra);
                        draw_sprite(screen, buffer, 0, 0);
                    }
                }

                    if (strncmp(palavra, acertos, 12) == 0)
                    {
                        clear(buffer);
                        while(!key[KEY_ESC])
                        {
                            draw_sprite(buffer, boneco, 403, 295);
                            draw_sprite(buffer, fundinho, 0, 0);
                            textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(0, 0, 0), -1, " GANHOU!");
                            textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Palavra Correta: %s", palavra);
                            textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                            draw_sprite(screen, buffer, 0, 0);
                        }
                    }

                    draw_sprite(screen, buffer, 0, 0);

                    if (strcmp(palavra, acertos) != 0 && erros != 6)
                    {
                        usada = 0;
                        leitura_palp = readkey();
                        palpite = leitura_palp & 0xff;
                        palpite = toupper(palpite);

                        for(i = 0; i < 26; i++)
                        {
                            if(letrasUsadas[i] == palpite)
                            {
                                usada = 1;
                            }
                        }

                        if(usada == 0)
                        {
                            letrasUsadas[numLetrasUsadas] = palpite;
                            numLetrasUsadas++;
                            contemPalpite = 0;

                            for(i = 0; i < tamanho_palavra; i++)
                            {
                                if(palpite == palavra[i])
                                {
                                    acertos[i] = palpite;
                                    contemPalpite = 1;
                                }
                            }

                            if(contemPalpite == 0)
                            {
                                erros++;
                            }
                        }
                    }
                }
        }

        clear(buffer);
        clear(screen);
        while(!key[KEY_ESC])
        {
            draw_sprite(buffer, fundinho, 0, 0);
            draw_sprite(buffer, arvorezinha, 20, 25);
            textprintf_ex(buffer, dicat, 40, 20, makecol(0, 0, 0), -1, "Dica: %s", dica);
            textprintf_ex(buffer, dicat, 40, 40, makecol(0, 0, 0), -1, "Palavra: %s", palavra);
            draw_sprite(screen, buffer, 0, 0);
        }

  }

       if(botao == KEY_2 || botao == KEY_2_PAD)
       {
           clear(screen);
           clear(buffer);
           leitura = '\0';

           while(!key[KEY_ESC])
           {
                draw_sprite(buffer, fundinho, 0, 0);
                textprintf_centre_ex(buffer, dicat, SCREEN_W/2, 250, makecol(0, 0, 0), -1, "%s", dica);
                textprintf_centre_ex(buffer, dicat, SCREEN_W/2, 200, makecol(0, 0, 0), -1, "Digite a dica: ");
                textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");

                draw_sprite(screen, buffer, 0, 0);
                clear(buffer);

                leitura = readkey();
                char letra = leitura & 0xff;
                char apaga = leitura >> 8;
                if(apaga == KEY_BACKSPACE)
                {
                    dica[i-1] = ' ';
                    i--;
                }
                if(letra >= 32 && letra <= 126)
                {
                    dica[i] = letra;
                    i++;
                }

                if(apaga == KEY_ENTER || apaga == KEY_ENTER_PAD)
                {
                    clear(screen);
                    clear(buffer);
                    leitura = '\0';
                    i = 0;

                    while(!key[KEY_ESC])
                    {
                        draw_sprite(buffer, fundinho, 0, 0);
                        textprintf_centre_ex(buffer, dicat, SCREEN_W/2, 250, makecol(0, 0, 0), -1, "%s", palavra);
                        textprintf_centre_ex(buffer, dicat, SCREEN_W/2, 200, makecol(0, 0, 0), -1, "Digite a palavra a ser adivinhada: ");
                        textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");

                        draw_sprite(screen, buffer, 0, 0);
                        clear(buffer);

                        int leitura = readkey();
                        char letra = leitura & 0xff;
                        char apaga = leitura >> 8;
                        if(apaga == KEY_BACKSPACE)
                        {
                            palavra[i-1] = ' ';
                            i--;
                        }
                        if(letra >= 32 && letra <= 126)
                        {
                            palavra[i] = letra;
                            i++;
                        }

                        if(key[KEY_ENTER] || apaga == KEY_ENTER_PAD)
                        {
                            clear(screen);
                            clear(buffer);

                            for (i = 0; i < strlen(palavra); i++)
                            {
                              acertos[i] = '_';
                            }

                            for (i = 0; i < strlen(palavra); i++)
                            {
                              palavra[i] = toupper(palavra[i]);
                            }

                            tam = strlen(palavra);

                            while(!key[KEY_ESC])
                            {
                              int conter = 0;
                              int tamanho_palavra = strlen(palavra);
                              draw_sprite(buffer, fundinho, 0, 0);
                              draw_sprite(buffer, arvorezinha, 20, 25);

                              textprintf_ex(buffer, dicat, 40, 20, makecol(0, 0, 0), -1, "Dica: %s", dica);
                              textprintf_ex(buffer, dicat, 50, 390, makecol(0, 0, 0), -1, "Digite uma Letra");
                              textprintf_ex(buffer, dicat, 40, 40, makecol(0, 0, 0), -1, "Quantidade de Letras da Palavra: %d", tam);

                              acertos[strlen(palavra)] = '\0';

                              textprintf_ex(buffer, palavra1, 50, 480, makecol(0, 0, 0), -1, "%s", acertos);

                              textprintf_ex(buffer, dicat, 40, 60, makecol(0, 0, 0), -1, "Letras Usadas: %s", letrasUsadas);

                              if(erros == 1)
                                {
                                    draw_sprite(buffer, cabeca, 403, 295);
                                }
                                if(erros == 2)
                                {
                                    draw_sprite(buffer, corpo, 403, 295);
                                }
                                if(erros == 3)
                                {
                                    draw_sprite(buffer, braco_um, 403, 295);
                                }
                                if(erros == 4)
                                {
                                    draw_sprite(buffer, braco_dois, 403, 295);
                                }
                                if(erros == 5)
                                {
                                    draw_sprite(buffer, perna, 403, 295);
                                }
                                if(erros == 6)
                                {
                                  clear(buffer);
                                  while(!key[KEY_ESC])
                                  {
                                    draw_sprite(buffer, boneco, 403, 295);
                                    draw_sprite(buffer, fundinho, 0, 0);
                                    textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(0, 0, 0), -1, "PERDEU!");
                                    textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Palavra Correta: %s", palavra);
                                    textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                                    draw_sprite(screen, buffer, 0, 0);
                                  }
                                }
                                if (strncmp(palavra, acertos, 12) == 0)
                                {
                                  clear(buffer);
                                  while(!key[KEY_ESC])
                                  {
                                    draw_sprite(buffer, boneco, 403, 295);
                                    draw_sprite(buffer, fundinho, 0, 0);
                                    textprintf_centre_ex(buffer, perdeu, SCREEN_W/2, SCREEN_H/2-100, makecol(0, 0, 0), -1, "GANHOU!");
                                    textprintf_centre_ex(buffer, body, SCREEN_W/2, SCREEN_H/2, makecol(0, 0, 0), -1, "Palavra Correta: %s", palavra);
                                    textprintf_centre_ex(buffer, esc1, SCREEN_W/2, 550, makecol(0, 0, 0), -1, "Pressione ESC para sair");
                                    draw_sprite(screen, buffer, 0, 0);
                                  }
                                }

                                draw_sprite(screen, buffer, 0, 0);

                              if (strcmp(palavra, acertos) != 0 && erros != 6)
                              {
                                usada = 0;
                                leitura_palp = readkey();
                                palpite = leitura_palp & 0xff;
                                palpite = toupper(palpite);

                                for(i = 0; i < 26; i++)
                                {
                                  if(letrasUsadas[i] == palpite)
                                  {
                                    usada = 1;
                                  }
                                }

                                if(usada == 0)
                                {
                                  letrasUsadas[numLetrasUsadas] = palpite;
                                  numLetrasUsadas++;
                                  contemPalpite = 0;

                                    for(i = 0; i < tamanho_palavra; i++)
                                    {
                                      if(palpite == palavra[i]) {
                                        acertos[i] = palpite;
                                        contemPalpite = 1;
                                      }
                                    }

                                    if(contemPalpite == 0)
                                    {
                                      erros++;
                                    }
                                  }
                                }
                            }
                        }
                   }
               }
            }
       }
   }

   destroy_bitmap(buffer);
   destroy_bitmap(arvorezinha);
   destroy_bitmap(fundinho);
   destroy_bitmap(boneco);
   destroy_bitmap(cabeca);
   destroy_bitmap(corpo);
   destroy_bitmap(braco_um);
   destroy_bitmap(braco_dois);
   destroy_bitmap(perna);

   destroy_font(fontizinha);
   destroy_font(menuzinho);
   destroy_font(ari);
   destroy_font(nova);

   free(dica);
   free(palavra);
   free(letrasUsadas);


   return 0;
}
END_OF_MAIN();
