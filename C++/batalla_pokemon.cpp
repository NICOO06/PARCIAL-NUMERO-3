#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Pokemon {
    string nombre;
    int hp;
    int maxHp;
    int nivel;
};

void mostrarBarra(const Pokemon& p) {
    int totalBar = 20;
    int filled = (p.hp * totalBar) / p.maxHp;
    cout << p.nombre << " [";
    for (int i = 0; i < filled; ++i) cout << "#";
    for (int i = filled; i < totalBar; ++i) cout << " ";
    cout << "] " << p.hp << " HP" << endl;
}

int randEntre(int minV, int maxV) {
    return rand() % (maxV - minV + 1) + minV;
}

void nivelUp(Pokemon& p) {
    p.nivel++;
    p.maxHp += 10;
    p.hp = p.maxHp;
    cout << endl;
    cout << "***** LEVEL UP *****" << endl;
    cout << "Pokemon " << p.nombre << " sube a nivel " << p.nivel << "!" << endl;
    cout << "HP restaurado a " << p.hp << "." << endl;
    cout << "Ataques mejorados!" << endl;
    cout << string(22, '*') << endl << endl;
}

int elegirPokemonJugador(int n) {
    cout << "Selecciona tu pokemon " << n << ":" << endl;
    cout << "1. Pikachu" << endl;
    cout << "2. Charmander" << endl;
    cout << "3. Bulbasaur" << endl;
    cout << "4. Squirtle" << endl;
    cout << "Opcion: ";
    int op; cin >> op;
    return op;
}

Pokemon crearPokemon(int opcion) {
    switch (opcion) {
        case 1: return {"Pikachu", 100, 100, 1};
        case 2: return {"Charmander", 100, 100, 1};
        case 3: return {"Bulbasaur", 100, 100, 1};
        default: return {"Squirtle", 100, 100, 1};
    }
}

vector<int> generarIndicesRival() {
    vector<int> idx;
    while (idx.size() < 2) {
        int r = randEntre(1, 4);
        bool ok = true;
        for (int x : idx) if (x == r) ok = false;
        if (ok) idx.push_back(r);
    }
    return idx;
}

int main() {
    srand((unsigned)time(0));
    cout << "====================================" << endl;
    cout << "  Bienvenido a la Batalla Pokemon!" << endl;
    cout << "====================================" << endl << endl;

    vector<string> frasesVictoria = {
        "¡Chimba, que gano perro!",
        "¡Nos rompimos el bochinche, parcero!",
        "¡Duro, esa victoria estuvo berraca!"
    };
    vector<string> frasesDerrota = {
        "Que hueva, no le puedo ganar, mk...",
        "Ay, parce, me dejaron en la lona...",
        "No joda, me faltó power, cagada..."
    };

    int op1 = elegirPokemonJugador(1);
    int op2 = elegirPokemonJugador(2);
    Pokemon jugador1 = crearPokemon(op1);
    Pokemon jugador2 = crearPokemon(op2);
    vector<Pokemon> equipo = { jugador1, jugador2 };

    vector<int> rivales = generarIndicesRival();
    Pokemon rival1 = crearPokemon(rivales[0]);
    Pokemon rival2 = crearPokemon(rivales[1]);
    vector<Pokemon> rival = { rival1, rival2 };

    int idxJugador = 0, idxRival = 0;
    cout << endl << "Comienza la batalla por turnos!" << endl << endl;

    while (idxJugador < 2 && idxRival < 2) {
        Pokemon& pj = equipo[idxJugador];
        Pokemon& pr = rival[idxRival];

        mostrarBarra(pj);
        mostrarBarra(pr);
        cout << endl;

        // Menu con rangos
        int minB = 8 + pj.nivel, maxB = 12 + pj.nivel;
        int minE = 14 + pj.nivel, maxE = 18 + pj.nivel;
        int minC = 20 + pj.nivel, maxC = 25 + pj.nivel;
        cout << "Turno de " << pj.nombre << ". Elige una accion:" << endl;
        cout << "1. Ataque basico (" << minB << "-" << maxB << ")" << endl;
        cout << "2. Ataque especial (" << minE << "-" << maxE << ")" << endl;
        cout << "3. Ataque critico (" << minC << "-" << maxC << ")" << endl;
        cout << "4. Curarse (5-20)" << endl;
        cout << "Opcion: ";
        int op; cin >> op;
        int dano = 0;
        int cura = 0;
        switch (op) {
            case 1:
                dano = randEntre(minB, maxB);
                cout << pj.nombre << " usa ataque basico! (" << dano << " dano)" << endl;
                break;
            case 2:
                dano = randEntre(minE, maxE);
                cout << pj.nombre << " usa ataque especial! (" << dano << " dano)" << endl;
                break;
            case 3:
                dano = randEntre(minC, maxC);
                cout << pj.nombre << " usa ataque critico! (" << dano << " dano)" << endl;
                break;
            case 4:
                cura = randEntre(5, 20);
                pj.hp += cura;
                if (pj.hp > pj.maxHp) pj.hp = pj.maxHp;
                cout << pj.nombre << " se cura y recupera " << cura << " HP (" << pj.hp << " totales)" << endl;
                break;
            default:
                cout << "Opcion invalida, pierdes el turno." << endl;
        }
        if (dano > 0) {
            pr.hp -= dano;
            cout << pr.nombre << " recibe " << dano << " dano." << endl;
            if (pr.hp < 0) pr.hp = 0;
        }
        cout << endl;

        if (pr.hp == 0) {
            cout << pr.nombre << " ha sido derrotado!" << endl;
            nivelUp(pj);
            idxRival++;
            if (idxRival < 2) cout << "El rival elige a su siguiente pokemon..." << endl << endl;
            continue;
        }

        // Turno rival
        int minBR = 8 + pr.nivel, maxBR = 12 + pr.nivel;
        int minER = 12 + pr.nivel, maxER = 16 + pr.nivel;
        int minCR = 18 + pr.nivel, maxCR = 22 + pr.nivel;
        int opR = randEntre(1, 4);
        int danoR = 0, curaR = 0;
        switch (opR) {
            case 1:
                danoR = randEntre(minBR, maxBR);
                cout << pr.nombre << " usa ataque basico! (" << danoR << " dano)" << endl;
                break;
            case 2:
                danoR = randEntre(minER, maxER);
                cout << pr.nombre << " usa ataque especial! (" << danoR << " dano)" << endl;
                break;
            case 3:
                danoR = randEntre(minCR, maxCR);
                cout << pr.nombre << " usa ataque critico! (" << danoR << " dano)" << endl;
                break;
            case 4:
                curaR = randEntre(5, 20);
                pr.hp += curaR;
                if (pr.hp > pr.maxHp) pr.hp = pr.maxHp;
                cout << pr.nombre << " se cura y recupera " << curaR << " HP (" << pr.hp << " totales)" << endl;
                break;
        }
        if (danoR > 0) {
            pj.hp -= danoR;
            cout << pj.nombre << " recibe " << danoR << " dano." << endl;
            if (pj.hp < 0) pj.hp = 0;
        }
        cout << endl;

        if (pj.hp == 0) {
            cout << pj.nombre << " ha sido derrotado..." << endl;
            nivelUp(pr);
            idxJugador++;
            if (idxJugador < 2) cout << "Cambia a tu siguiente pokemon!" << endl << endl;
        }
    }

    if (idxJugador == 2) {
        int i = randEntre(0, frasesDerrota.size()-1);
        cout << frasesDerrota[i] << endl;
    } else {
        int i = randEntre(0, frasesVictoria.size()-1);
        cout << frasesVictoria[i] << endl;
    }

    return 0;
}
