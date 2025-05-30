import pygame
import time
from datetime import datetime

# Inicializar mixer para sonido
pygame.mixer.init()

def reproducir_sonido(archivo):
    try:
        pygame.mixer.music.load(archivo)
        pygame.mixer.music.play()
    except Exception as e:
        print("Error sonido:", e)

# Parámetros del lote
FILAS, COLS = 10, 12
TAM_CELDA = 50
ANCHO = COLS * TAM_CELDA
ALTO = FILAS * TAM_CELDA + 40
PRECIO_HORA = 2000

# Colores
C_VIA = (100,100,100)
C_LIBRE = (0,180,0)
C_FONDO = (230,230,230)

# Mapa y ocupados\mapa = []
ocupados = {}

def crear_mapa():
    global mapa, ocupados
    # Layout: carriles y bloques separados
    mapa = [[ 'V' if (r in [2,5] or c in [3,8]) else 'P'
               for c in range(COLS)]
             for r in range(FILAS)]
    # Definir carriles exteriores
    for c in range(COLS):
        mapa[0][c] = 'V'
        mapa[FILAS-1][c] = 'V'
    for r in range(FILAS):
        mapa[r][0] = 'V'
        mapa[r][COLS-1] = 'V'
    # Definir entrada y salida
    mapa[0][1] = 'E'
    mapa[FILAS-1][COLS-2] = 'S'

    # Ocupados por defecto
    ocupados = {
        "ABC123": (datetime.now(), (3, 1)),
        "XYZ789": (datetime.now(), (6, 2)),
        "JKL456": (datetime.now(), (4, 6)),
    }
    for placa, (_, (r, c)) in ocupados.items():
        mapa[r][c] = 'O'

# Función para dibujar todo
def dibujar(pantalla, carro_img, font):
    pantalla.fill(C_FONDO)
    # Mostrar hora
    hora = datetime.now().strftime("%H:%M:%S")
    pantalla.blit(font.render(f"Hora: {hora}", True, (0,0,0)), (ANCHO-150, 10))
    # Mostrar tarifa
    pantalla.blit(font.render(f"Precio: ${PRECIO_HORA}/h", True, (0,0,0)), (10, ALTO-30))

    for r in range(FILAS):
        for c in range(COLS):
            x, y = c*TAM_CELDA, r*TAM_CELDA + 30
            tipo = mapa[r][c]
            if tipo == 'V':
                pygame.draw.rect(pantalla, C_VIA, (x, y, TAM_CELDA, TAM_CELDA))
            elif tipo == 'P':
                pygame.draw.rect(pantalla, C_LIBRE, (x, y, TAM_CELDA, TAM_CELDA))
            elif tipo == 'O':
                pantalla.blit(carro_img, (x + 5, y + 5))
            elif tipo == 'E':
                pygame.draw.rect(pantalla, (0,0,200), (x, y, TAM_CELDA, TAM_CELDA))
                pantalla.blit(font.render("Entrada", True, (255,255,255)), (x+5, y+5))
            elif tipo == 'S':
                pygame.draw.rect(pantalla, (200,200,0), (x, y, TAM_CELDA, TAM_CELDA))
                pantalla.blit(font.render("Salida", True, (0,0,0)), (x+5, y+5))
            pygame.draw.rect(pantalla, (0,0,0), (x, y, TAM_CELDA, TAM_CELDA), 1)
    pygame.display.flip()

# Animación en consola
def animar(tipo, placa):
    for i in range(5):
        print(f"Vehículo {placa} {tipo}ndo" + "." * (i+1))
        time.sleep(0.2)
    print()

# Buscar lugar libre
def buscar_libre():
    for r in range(FILAS):
        for c in range(COLS):
            if mapa[r][c] == 'P':
                return r, c
    return None, None

# Ingresar vehículo
def ingresar():
    placa = input("Placa: ").upper()
    if placa in ocupados:
        print("Ya registrado.")
        return
    r, c = buscar_libre()
    if r is None:
        print("Parqueadero lleno.")
        return
    animar("entra", placa)
    reproducir_sonido("entrada.mp3")
    mapa[r][c] = 'O'
    ocupados[placa] = (datetime.now(), (r, c))
    print(f"{placa} ingresó a las {datetime.now().strftime('%H:%M:%S')}")

# Retirar vehículo
def retirar():
    placa = input("Placa a retirar: ").upper()
    if placa not in ocupados:
        print("No existe.")
        return
    animar("sal", placa)
    reproducir_sonido("salida.mp3")
    hora_ent, (r, c) = ocupados.pop(placa)
    horas = int((datetime.now() - hora_ent).total_seconds()/3600) + 1
    print(f"Pago: ${horas * PRECIO_HORA}")
    mapa[r][c] = 'P'

# Ver disponibilidad
def dispon():
    lib = sum(mapa[r][c] == 'P' for r in range(FILAS) for c in range(COLS))
    occ = sum(mapa[r][c] == 'O' for r in range(FILAS) for c in range(COLS))
    print(f"Libres: {lib} | Ocupados: {occ}")

# Menú principal
def menu():
    crear_mapa()
    pygame.init()
    pantalla = pygame.display.set_mode((ANCHO, ALTO))
    pygame.display.set_caption("Parqueadero Realista")

    try:
        carro_img = pygame.image.load("carro.png")
        carro_img = pygame.transform.scale(carro_img, (TAM_CELDA-10, TAM_CELDA-10))
    except:
        carro_img = pygame.Surface((TAM_CELDA-10, TAM_CELDA-10))
        carro_img.fill((200,0,0))

    font = pygame.font.SysFont(None, 24)
    run = True
    while run:
        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                run = False
        dibujar(pantalla, carro_img, font)
        pygame.event.pump()

        print("\n1. Ver mapa")
        print("2. Ingresar vehículo")
        print("3. Retirar vehículo")
        print("4. Ver disponibilidad")
        print("5. Salir")
        o = input("Opción: ")
        if o == '1':
            pass
        elif o == '2':
            ingresar()
        elif o == '3':
            retirar()
        elif o == '4':
            dispon()
        elif o == '5':
            run = False
        else:
            print("Opción inválida.")

    pygame.quit()

if __name__ == "__main__":
    menu()
