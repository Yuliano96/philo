# Philosophers

• Uno o más filósofos se sientan en una mesa redonda. En el centro de la mesa se encuentra un gran bol de espaguetis.

• Los filósofos solo pueden comer, pensar, o dormir.
  Mientras están comiendo, no pueden pensar ni dormir;
  Mientras están pensando, no pueden dormir ni comer;
  Y, por supuesto, mientras están durmiendo, no pueden comer ni pensar.
  
• También hay tenedores en la mesa, tantos tenedores como filósofos.

• Porque coger y comer espaguetis con un solo tenedor puede ser incomodo, los filósofos deben tomar el tenedor de la derecha y el de la izquierda, uno en cada mano.

• Cuándo un filósofo termine de comer, dejará los tenedores en la mesa e inmediatamente empezará a dormir. Una vez se despierte, empezará a pensar nuevamente.
  La simulación se detendrá cuando un filósofo muere por inanición.
  
• Todos los filósofos necesitan comer y nunca deben morir de hambre.

• Los filósofos no hablan entre ellos.

• Los filósofos no saben si otro filósofo va a morir.

• ¡No debería hacer falta decir que todos deben evitar morir!

En este proyecto, aprenderé los principios básico de hilar un proceso, a como crear hilos y descubriré los mutex.

Este proyecto, lo divideré en varias sesiones:


# 📚 sesión 1: Entorno base y repaso de herramientas
Preparar tu carpeta philo/.

Crear tu Makefile básico y el archivo philo.h.

Hacer mini pruebas:

Crear un hilo simple (pthread_create y pthread_join).

Usar un mutex simple (pthread_mutex_init, lock, unlock, destroy).

Practicar con gettimeofday y usleep.

# Objetivo final de la sesión:
Saber crear hilos, mutexes, y medir tiempo de forma básica.

# ⚙️ Sesión 2: Diseño de estructuras
Definir tus structs:

t_philo (un filósofo).

t_data (datos generales de la simulación).

¿Qué debería tener cada struct? (IDs, mutexes, tiempos, punteros a forks...).

Planear cómo los hilos recibirán la información (por punteros, no globals).

# Objetivo final de la sesión:
Tener philo.h completo y las estructuras bien pensadas para poder trabajar.

# 🍝 Sesión 3: Inicialización de la simulación
Inicializar los datos:

Parsear argumentos del programa.

Crear e inicializar los mutexes (tenedores).

Crear e inicializar los filósofos (cada uno con su ID, tiempos, punteros a forks).

Lanzar todos los hilos de filósofos (pthread_create en bucle).

Objetivo final de la sesión:
Que todos los filósofos existan, estén vivos y puedan hacer printf("Soy el filosofo X").

# 🧠 Sesión 4: Lógica de vida del filósofo
Dentro del hilo:

think → take forks → eat → sleep → repeat.

Implementar:

Tomar el mutex izquierdo y derecho.

Comer (usleep el tiempo de comer).

Dejar los tenedores (unlock los mutexes).

Dormir (usleep el tiempo de dormir).

Pensar.

# Objetivo final de la sesión:
Ver un bucle de los filósofos comiendo, durmiendo y pensando en orden.

# 💀 Sesión 5: Detección de muerte
Crear un hilo monitor o función dentro de cada filósofo:

Controlar si un filósofo supera su time_to_die sin comer.

Cuando un filósofo muere, imprimirlo (timestamp X died) y terminar la simulación.

Asegurarse de que:

El primer filósofo que muere se detecta en menos de 10ms.

Después de una muerte, todo debe terminar ordenadamente.

# Objetivo final de la sesión:
Control de muerte funcionando correctamente.

# 🍽️ Sesión 6: Argumento opcional — número de comidas
Manejar el quinto argumento (number_of_times_each_philosopher_must_eat).

Contar cuántas veces ha comido cada filósofo.

Terminar la simulación si todos han comido suficiente.

# Objetivo final de la sesión:
Parar la simulación correctamente si todos comen las veces requeridas.

# 🧹 Sesión 7: Limpieza y validaciones
Liberar toda la memoria.

Destruir todos los mutexes.

Manejar errores si los argumentos de entrada están mal.

Probar todo usando valgrind (sin memory leaks).

Ajustar el Makefile si es necesario.

Objetivo final de la sesión:
Proyecto funcionando limpio, sin leaks, sin errores.

# 🎉 Sesión 8: Pruebas fuertes
Hacer tests brutales:

Muchos filósofos (100, 200...).

Tiempos muy bajos.

Simulaciones largas.

Buscar condiciones de carrera o deadlocks (forzar errores para ver si aparecen).

Afinar detalles de logs (printf) para que no se mezclen.

# Objetivo final de la sesión:
Estar listo para defensa.

