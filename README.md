# Innovaciones de los Proyectos

- **Nicolás Vargas**
- **Sergio Prieto**

---

## Proyecto 1: Batalla de Pokémon (C++)

- **Sistema de niveles dinámico**: Cada vez que un Pokémon derrota a otro, sube de nivel, aumenta su HP máximo y restaura su vida al 100%.  
- **Rangos de daño escalables**: Los ataques (básico, especial, crítico) ajustan su daño según el nivel actual.  
- **Curación estratégica**: Opción para recuperar puntos de vida durante el combate, con límite al HP máximo.  
- **Frases de victoria/derrota localizadas**: Mensajes finales con expresiones coloquiales para mayor inmersión.  
- **Selección de equipo y rival aleatoria**: El jugador elige dos Pokémon y el rival los elige de forma única y aleatoria, garantizando variedad.

### Ejecución desde consola

1. Abre la terminal o consola.  
2. Navega al directorio donde está el archivo `batalla_pokemon.cpp`:  
   ```bash
   cd /ruta/al/proyecto1
3. Compila el código con g++ (u otro compilador de C++):
   `g++ batalla_pokemon.cpp -o batalla_pokemon`
5. Ejecuta el programa compilado:
   `./batalla_pokemon`

   
## Proyecto 2: Sistema de Parqueadero (Python + Pygame)

- **Mapa gráfico interactivo**: Generación automática de un layout de 10×12 celdas que distingue vías, espacios libres, carros, entrada y salida.  
- **Animación en consola**: Secuencias breves con puntos suspensivos para simular el movimiento de vehículos al entrar y salir.  
- **Efectos de sonido**: Sonidos diferenciados para eventos de entrada y salida, mejorando la experiencia de usuario.  
- **Sprite de vehículo escalado**: Carga de imagen externa (`carro.png`) y ajuste dinámico al tamaño de celda.  
- **Cálculo de tarifa por hora**: Cómputo automático del monto a pagar, redondeando horas parciales al próximo entero.

### Ejecución desde consola

1. Abre otra ventana de la terminal.  
2. Navega al directorio donde están `parqueadero.py` y `carro.png`:
   ```bash
   cd /ruta/al/proyecto2
3. (Opcional) Crea un entorno virtual e instala `pygame`:
##### Crear y activar entorno virtual
`python3 -m venv venv`
##### Linux / macOS:
`source venv/bin/activate`
##### Windows:
`venv\Scripts\activate`

##### Instalar Pygame
`pip install pygame`

4. Ejecuta el script:
   `python parqueadero.py`

