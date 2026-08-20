#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// Variáveis globais
IDirect3DDevice9* pDevice = NULL;
ID3DXFont* pFont = NULL;
bool menuAberto = false;

// Função para desenhar texto
void DrawText(int x, int y, const char* text, D3DCOLOR color) {
    if (!pFont) return;
    
    RECT rect = { x, y, x + 500, y + 50 };
    pFont->DrawTextA(NULL, text, -1, &rect, DT_LEFT, color);
}

// Função para detectar tecla F11
void CheckInput() {
    if (GetAsyncKeyState(VK_F11) & 0x8000) {
        menuAberto = !menuAberto;
        Sleep(200); // Debounce
    }
}

// Função para renderizar o menu
void RenderMenu() {
    if (!menuAberto) return;
    
    // Background
    DrawText(100, 100, "====== MENU F11 ======", D3DCOLOR_XRGB(0, 255, 0));
    DrawText(100, 130, "1 - Opcao 1", D3DCOLOR_XRGB(255, 255, 255));
    DrawText(100, 160, "2 - Opcao 2", D3DCOLOR_XRGB(255, 255, 255));
    DrawText(100, 190, "3 - Opcao 3", D3DCOLOR_XRGB(255, 255, 255));
    DrawText(100, 220, "ESC - Fechar Menu", D3DCOLOR_XRGB(255, 0, 0));
    
    // Fechar com ESC
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        menuAberto = false;
        Sleep(200);
    }
}

// Hook para EndScene
typedef HRESULT(WINAPI* tEndScene)(IDirect3DDevice9*);
tEndScene oEndScene = NULL;

HRESULT WINAPI hEndScene(IDirect3DDevice9* pD3DDevice) {
    pDevice = pD3DDevice;
    
    // Criar font se não existir
    if (!pFont) {
        D3DXCreateFont(pDevice, 14, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET,
                       OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                       "Arial", &pFont);
    }
    
    CheckInput();
    RenderMenu();
    
    return oEndScene(pD3DDevice);
}

// DLL Entry Point
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        // Aqui você faria o hook do DirectX
        // Este é um exemplo básico
        MessageBoxA(NULL, "ASI Menu F11 Carregado!", "Info", MB_OK);
    }
    return TRUE;
}
