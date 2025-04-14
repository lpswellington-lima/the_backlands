#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>

// Defina VERBOSITY para 1 para ativar as mensagens de depuração
#define VERBOSITY 1
#define SCREEN_WIDTH 800
#define SCREEN_HIGHT 600
#define TITLE_FONT "Assets/Fonts/Oswald-Regular.ttf"

// Macro para impressão de depuração
#if VERBOSITY
    #define PRINT(msg) std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " << msg << std::endl
#else
    #define PRINT(msg) // Desabilita a saída
#endif

// Macro para impressão de erros (sempre habilitado)
#define PRINT_ERROR(msg) std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] ERROR: " << msg << std::endl

#endif // CONFIG_H