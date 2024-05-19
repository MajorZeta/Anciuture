// proyecto: Grupal/Juego
// arhivo:   JuegoMesa.cpp
// versión:  1.1  (9-Ene-2023)


#include "juego.h"


namespace juego {


    /*******************************************************************************************
    /*******************************************************************************************
        
    CONFIGURACIÓN DEL JUEGO
    Primera sección - Los recursos

    En esta sección se establecen las carpetas en las que aparecen los recursos usados por el 
    juego, incluyendo las imágenes que aparecen en pantalla y los sonidos que se escuchan. Hay 
    una carpeta separada para los retratos de los personajes y otra para las imágenes de las 
    habilidades.

    Las carpetas están situadas en la carpeta donde están los archivos de código fuente del 
    proyecto.

    En principio no es necesario hacer ningún cambio en esta sección, si los recursos que se 
    cambian se sitúan en las mismas carpetas.

    *******************************************************************************************/
    string JuegoMesa::carpeta_activos_juego  {"./activos/"};
    string JuegoMesa::carpeta_retratos_juego {"./retratos/"};
    string JuegoMesa::carpeta_habilids_juego {"./habilidades/"};
    string JuegoMesa::carpeta_sonidos_juego  {"./sonidos/"};
    /*******************************************************************************************
    /******************************************************************************************/


    const std::wstring JuegoMesa::tituloVentana () const {
        return L"UNIR-2D :: Juego de Mesa";
    }


    JuegoMesa::JuegoMesa () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Segunda sección - El modo del juego

        En esta sección se configura el modo general del juego, es decir como se suceden las 
        jugadas, los turnos y las rondas. Y como se establece el personaje que realiza cada jugada.  

        La configuración del modo del juego se realiza mediante la elección de alguno de los
        modos preestablecidos. Es la única forma de configurar el modo del juego.

        Hay tres modos de juego preestablecidos:

            1) Modo de juego por pares
            2) Modo de juego por equipos
            3) Modo de juego libre de doble jugada

        Las siguientes definiciones se aplican a todos los modos de juego:

        Jugada:   
            Es una acción realizada con uno de los personajes. Puede ser un desplazamiento o la
            aplicación de una habilidad.

        Turno:
            Es una secuencia de jugadas realizadas por un grupo de personajes, normalmente 
            alternando a los dos equipos. los turnos se inician con la elección de los personajes 
            que van a participar en el turno, aunque en algunos modos de juego estos están 
            preestablecidos.

        Ronda:
            Es una secuencia de turnos en las que intervienen todos los personajes y que se 
            prolongan hasta que los personajes no pueden continuar, por haber perdido sus puntos de 
            acción o por haber perdido su vitalidad. Al inicio de la ronda, se recuperan los puntos 
            de acción de todos los personajes.

        Partida:
            Está formada por una secuencia de rondas. La partida termina cuando todos los personajes 
            de un equipo pierden su vitalidad. El otro equipo es el ganador.


        Modo de juego por pares
        --------------------------
        
        En este modo debe haber el mismo número de personajes en cada equipo.

        los turnos comienzan con los jugadores eligiendo un personaje de cada equipo. El primer 
        personaje en jugar es el que tiene más iniciativa, y en caso de tener la misma, se elige al 
        azar. A continuación se suceden las jugadas, alternando los dos personajes. 

        Cuando un personaje pierde sus puntos de acción o su vitalidad, el turno continua solo con 
        el otro. Y cuando lo pierden los dos, el turno termina.

        En el nuevo turno los jugador elige de nuevo a los dos personajes, evitando a los que han
        perdido sus puntos de acción o vitalidad.

        Cuando todos los personajes han perdido sus puntos de acción o su vitalidad, termina la 
        ronda.


        Modo de juego por equipos
        ----------------------------

        En este modo debe haber el mismo número de personajes en cada equipo.

        Al principio de la partida se establece un orden de juego para los personajes. Se toman los 
        personajes según aparecen en el tablero, de arriba a abajo, alternando los dos equipos. El 
        primero de los personajes será el que tenga más iniciativa de los dos primeros, eligiéndolos 
        al azar si coinciden. 
        
        Un turno consiste en una jugada de cada personaje, tomándolos en el orden de la lista y se 
        prolonga hasta que juega el último de los personajes de la lista. Si un personaje ha perdido 
        sus puntos de acción o su vitalidad, la jugada es nula y se pasa al siguiente personaje de 
        la lista. 
        
        Los turnos se suceden hasta que todos los personajes han perdido sus puntos de acción o su 
        vitalidad, momento en que se inicia el siguiente ronda.


        Modo de juego libre de doble jugada
        --------------------------------------

        En este modo debe haber el mismo número de personajes en cada equipo.

        Al principio de la partida se establece un equipo inicial, tomando el que tiene el personaje 
        con más iniciativa o eligiéndolo al azar si coinciden. A continuación se alternan turnos de 
        uno y otro equipo. 
        
        Al principio de cada turno, el jugador elije un personaje del equipo correspondiente. El 
        turno consiste en dos jugadas seguidas del mismo personaje, tras las cuales se pasa a el 
        siguiente turno, en la que el jugador elige un personaje del otro equipo. Si un personaje 
        ha perdido sus puntos de acción o su vitalidad, no puede ser elegido.

        Cuando todos los personajes de un equipo han perdido sus puntos de acción o vitalidad, 
        termina el turno (a pesar de que el otro equipo si pueda continuar).


        Programación
        ------------

        Para cambiar el modo del juego es suficiente con cambiar los identificadores usados en 
        las dos líneas de código siguientes. Debe aparecer una de estas tres parejas:

            · ModoJuegoPares       SucesosJuegoPares       
            · ModoJuegoEquipo      SucesosJuegoEquipo    
            · ModoJuegoLibreDoble  SucesosJuegoLibreDoble

        *******************************************************************************************/
        ModoJuegoPares    * modo    = new ModoJuegoPares {this};
        SucesosJuegoPares * sucesos = new SucesosJuegoPares {this, modo};
        /*******************************************************************************************
        /******************************************************************************************/
        //
        JuegoMesaBase::configura (sucesos, modo);
    }


    /*******************************************************************************************
    /*******************************************************************************************
        
    CONFIGURACIÓN DEL JUEGO
    Tercera sección - El tablero - Primera parte

    En esta sección se preparan los muros que aparecen en el tablero de juego.

    En el juego aparecen imágenes que muestran muros que ocupan algunas casillas hexagonales
    del tablero. Los jugadores no pueden situar a los personajes sobre los muros, ni 
    atravesarlos. Tampoco pueden realizar ataque a través de los muros (excepto si están 
    marcados como ataques indirectos).  

    Existen muchas posibilidades de diseño para los muros. Es posible que los muros se usen solo
    para delimitar un área del tablero, como ocurre con el ejemplo que aparece a continuación,
    llamado 'grafico_muros_area_central'. Otra posibilidad es diseñar una especie de laberinto
    con pasillos y cámaras, como en el ejemplo: 'grafico_muros_pasillos'. Aunque, lo más 
    aconsejable es crear unos muros que sean simplemente obstáculos para los ataques entre los 
    personajes.

    Especificación de los muros
    ---------------------------

    Para especificar los muros del tablero se debe crear un array similar al que aparece en los 
    ejemplos. Es preferible crear uno nuevo y mantener los ejemplos, en ese caso , la variable 
    debe tener un nombre diferente.

    El array está formado por 51 cadenas de caracteres, cada una de ellas de 145 caracteres de 
    longitud (mas el carácter \0 final, que no es visible). La mayor parte de los caracteres de 
    la cadena son espacios en blanco. En determinadas posiciones, y solo en ellas, puede haber: 
    o bien un guion, o bien la letra O mayúscula. 
        
    Esta disposición está pensada para indicar las posiciones de las celdas de la rejilla del 
    tablero. Al ser celdas hexagonales, no es posible usar una tabla formada por filas y 
    columnas, que, además, no daría una representación visual clara del tablero.

    Si se quiere que en una celda del tablero no aparezca un fragmento del muro, se debe 
    escribir un guion en la posición correspondiente del array. Si, por el contrario, se quiere 
    que si aparezca, se debe escribir la letra o mayúscula.

    El programa es muy sensible a la colocación de los caracteres en el array. Si uno de ellos
    está desplazado (por poco que sea), se producirá una excepción y el programa no se podrá 
    ejecutar.

    Programación
    ------------

    Véase la tercera parte de esta sección.
        
    *******************************************************************************************/
    static ActorTablero::GraficoMuros grafico_muros_vacio { 
//                                      1  1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3  3  4  4  4  4  4  4  4  4  4  4
//           1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
//                                                                                                                11111111111111111111111111111111111111111111
//                     111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999000000000011111111112222222222333333333344444  
//           0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",  
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -"};


    static ActorTablero::GraficoMuros grafico_muros_area_central { 
//                                      1  1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3  3  4  4  4  4  4  4  4  4  4  4
//           1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
//                                                                                                                11111111111111111111111111111111111111111111
//                     111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999000000000011111111112222222222333333333344444  
//           0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234
            "-     -     -     -     -     -     -     -     O     O     O     O     -     O     O     O     O     -     -     -     -     -     -     -     -",  
            "   -     -     -     -     -     -     -     O     O     O     O     -     -     O     O     O     O     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     O     O     O     O     -     -     -     O     O     O     O     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     O     O     O     O     -     -     -     -     O     O     O     O     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     O     O     O     O     -     -     -     -     -     O     O     O     O     -     -     -     -     -     -",
            "   -     -     -     -     -     O     O     O     O     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -   ",
            "-     -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -",
            "   -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -   ",
            "-     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -",
            "   -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -   ",
            "-     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -",
            "   -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -   ",
            "-     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -",
            "   -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -   ",
            "-     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -",
            "   -     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -",
            "   -     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     -   ",
            "-     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     -     -     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     -     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -",
            "   -     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     -   ",
            "-     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -",
            "   -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -   ",
            "-     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -",
            "   -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -   ",
            "-     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -",
            "   -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -   ",
            "-     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -",
            "   -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -   ",
            "-     -     -     -     -     O     O     O     O     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -",
            "   -     -     -     -     -     O     O     O     O     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -   ",
            "-     -     -     -     -     -     O     O     O     O     -     -     -     -     -     O     O     O     O     -     -     -     -     -     -",
            "   -     -     -     -     -     -     O     O     O     O     -     -     -     -     O     O     O     O     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     O     O     O     O     -     -     -     O     O     O     O     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     O     O     O     O     -     -     O     O     O     O     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     O     O     O     O     -     O     O     O     O     -     -     -     -     -     -     -     -"};


    static ActorTablero::GraficoMuros grafico_muros_pasillos { 
            "-     O     -     -     -     -     -     O     -     -     -     -     -     -     -     -     O     -     -     -     O     -     -     -     -",
            "   O     O     -     -     -     -     O     O     -     -     -     -     -     -     -     O     O     -     -     O     O     -     -     -   ",
            "O     -     O     -     -     -     O     -     O     -     -     -     -     -     -     O     -     O     -     O     -     O     -     -     -",
            "   -     -     O     -     -     O     -     -     O     -     -     -     -     -     O     -     -     O     -     O     -     O     -     -   ",
            "O     -     -     O     -     O     -     O     -     O     -     -     -     -     O     -     O     -     O     -     O     -     O     -     -",
            "   -     -     -     O     O     -     O     O     -     O     -     -     -     O     -     O     O     -     O     -     O     -     O     -   ",
            "O     -     -     -     O     -     O     -     O     -     O     -     -     O     -     O     -     O     -     O     -     O     -     O     -",
            "   -     -     -     -     O     O     O     -     O     -     O     -     O     -     O     -     -     O     -     O     -     O     -     O   ",
            "O     -     -     -     -     -     -     O     -     O     -     O     O     -     O     -     -     -     O     -     O     -     O     -     O",
            "   -     -     -     -     O     O     -     O     -     O     -     O     -     O     -     -     O     -     O     -     O     -     O     O   ",
            "O     -     -     -     -     -     -     O     O     -     O     -     -     O     -     -     O     O     -     O     -     O     -     O     -",
            "   -     -     -     -     O     O     O     -     O     -     O     -     O     -     -     O     -     O     -     O     -     O     -     -   ",
            "O     -     -     -     -     -     O     -     -     O     -     O     -     O     -     O     -     -     O     -     O     -     O     -     -",
            "   -     -     -     -     -     O     -     O     -     O     -     O     -     O     O     -     -     -     O     -     O     -     O     -   ",
            "O     -     -     -     -     -     -     O     O     -     O     -     O     -     O     -     -     -     -     O     -     O     -     O     -",
            "   -     -     -     -     O     O     -     -     O     -     O     -     O     -     -     -     -     -     -     O     -     O     -     -   ",
            "O     -     -     -     -     -     -     O     -     O     -     O     -     O     -     -     -     -     -     -     O     -     O     -     -",
            "   -     -     -     -     O     O     -     O     -     O     -     O     -     O     -     -     -     -     -     -     O     -     O     -   ",
            "O     -     -     -     O     -     O     -     O     -     O     -     O     -     O     -     -     -     -     -     O     O     -     O     -",
            "   O     -     -     O     -     O     O     -     O     -     O     -     O     -     -     -     -     -     -     -     -     O     -     -   ",
            "-     O     -     O     -     O     -     O     -     O     -     O     -     O     -     -     -     -     -     -     O     -     O     O     -",
            "   -     -     O     -     O     -     -     O     -     O     -     O     -     O     -     -     -     -     -     -     O     -     -     -   ",
            "-     O     O     -     O     -     -     -     O     -     O     -     O     -     O     -     -     -     -     -     -     O     O     O     -",
            "   -     O     -     O     -     -     -     -     O     -     O     -     O     -     -     -     -     -     -     -     -     O     -     -   ",
            "-     -     -     O     -     -     -     -     -     -     -     O     -     O     -     -     -     -     -     -     O     -     O     -     -",
            "   -     -     O     -     -     -     -     -     -     -     O     O     O     O     -     -     -     -     -     -     O     -     O     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     -     O     -     O     -",
            "   -     -     -     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     O     -     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     O     O     -     -",
            "   -     -     -     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     O     O     O     -",
            "   -     -     -     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     -     -     O   ",
            "-     O     O     O     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     O     O     O     O",
            "   -     -     O     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     O     -     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     O     O     O     O",
            "   -     O     -     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     O     -     -     -     -     -     -     -     -     -     -     -     O     -     -     -     -     -     O     O     O     O     O",
            "   -     -     O     -     -     -     -     -     -     -     O     O     O     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     O     -     O     -     -     -     -     -     -     -     O     -     O     O     -     -     -     -     -     O     O     O     O     O",
            "   -     O     -     O     -     -     -     -     -     -     O     -     -     O     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     O     -     O     -     -     -     -     -     O     -     O     -     O     -     -     -     -     -     O     O     O     O     O",
            "   -     -     O     -     O     -     -     -     -     O     -     O     O     -     O     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     O     -     O     -     -     -     O     -     O     -     O     -     O     -     -     -     -     O     O     O     O     O",
            "   -     -     -     O     -     O     -     -     O     -     O     -     -     O     -     O     -     O     -     O     -     O     -     -   ",
            "-     -     -     -     O     -     O     -     O     -     O     -     O     -     O     -     O     O     O     O     -     -     O     O     O",
            "   -     -     -     -     O     -     O     O     -     O     -     O     O     -     O     -     O     -     O     -     O     -     -     -   ",
            "-     -     -     -     -     O     -     O     -     O     -     O     -     O     -     O     -     -     -     -     O     O     -     O     O",
            "   -     -     -     -     -     O     -     -     -     -     O     -     -     O     -     O     -     O     -     O     -     O     O     -   ",
            "-     -     -     -     -     -     O     -     O     -     O     -     -     -     O     -     O     O     O     O     -     -     O     O     O",
            "   -     -     -     -     -     -     O     O     O     O     -     -     -     -     O     O     O     -     O     -     -     -     -     O   ",
            "-     -     -     -     -     -     -     O     -     O     -     -     -     -     -     O     -     -     -     -     -     -     -     -     -"};
    /*******************************************************************************************
    /******************************************************************************************/


    void JuegoMesa::preparaTablero () {
        agregaTablero (new ActorTablero (this));
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Tercera sección - El tablero - Segunda parte

        En esta sección se configura el fondo del tablero. Para rellenar el fondo del tablero se usa
        un conjunto de imágenes colocadas en una rejilla (en filas y columnas), que ocupan toda la 
        superficie de la ventana.
        
        La imagen usada para rellenar el fondo del tablero no se usa directamente, se divide en 16
        partes, con 4 filas y 4 columnas, y continuación se colocan en el fondo del tablero, 
        seleccionado las partes de manera aleatoria. La razón de este funcionamiento es que se 
        consiguen evitar los patrones visuales que pueden aparecer si se colocan de forma uniforme.

        El tamaño de la imagen usada es de 128x128 px (y cada parte es de 32x32 px). 
        
        Programación
        ------------

        Para cambiar la imagen del fondo es suficiente con situar la imagen nueva en la carpeta de 
        activos del juego y cambiar el nombre en la línea de código siguiente. 
        
        Es conveniente usar un archivo de tipo PNG. Además se deben respetar las medidas indicadas
        previamente.

        *******************************************************************************************/
        tablero ()->ponArchivoBaldosas (carpeta_activos_juego + "Arena.png");
        /*******************************************************************************************
        /******************************************************************************************/
        //
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Primera parte

        En esta sección se configuran los equipos del juego. 

        Cada equipo tiene un nombre y un escudo que aparece sobre la bandera en la parte superior de
        los paneles laterales del juego. En escudo se superpone a la bandera, sin taparla. El tamaño
        de las dos imágenes es de 40x40 px.
        
        Programación
        ------------

        Para cambiar los nombres de los equipos, se deben cambiar las dos líneas de código 
        siguientes. 
        
        Para cambiar las imágenes de los escudos es suficiente con situar las imágenes nuevas en la 
        carpeta de activos del juego y cambiar los nombres en las líneas de código siguiente. 
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        tablero ()->equipa (LadoTablero::Izquierda, L"Devils", carpeta_activos_juego + "escudo_devils.png");
        tablero ()->equipa (LadoTablero::Derecha,   L"Tusk",   carpeta_activos_juego + "escudo_tusk.png");
        /*******************************************************************************************
        /******************************************************************************************/
        //
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Tercera sección - El tablero - Tercera parte

        En esta sección se preparan los muros que aparecen en el tablero de juego. En la primera
        parte de la sección se preparan los muros que aparecen en el tablero, en esta tercera parte 
        se establecen los muros que usará el juego.

        Programación
        ------------

        Para cambiar los muros que aparecen en el tablero de juego es suficiente con cambiar el 
        nombre de la variable que contiene el array que los especifica en la línea de código que 
        aparece a continuación.
        
        *******************************************************************************************/
        tablero ()->situaMuros (grafico_muros_area_central);
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaPersonajes () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Tercera parte

        En esta sección se configuran los personajes del juego. En la segunda parte se establecen
        las variables destinadas a almacenar las instancias que definen los personajes. En esta 
        parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre del personaje correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los personajes:

             a) Nombre: Asignado en la creación de la instancia en una cadena de caracteres. Deben 
                ser evitados los nombres compuestos y los nombres largos.

             b) Equipo: Se establece indicando si el personaje aparece en el panel de la izquierda o 
                en el panel de la derecha en el tablero de juego.

             c) Orden en equipo: Debe ser un índice a partir de 0 y consecutivo.

             d) Iniciativa: Establece que personaje actúa en primer lugar en algunas de las 
                circunstancias del juego. Debe ser positivo.

        Imágenes
        --------

        Cada personaje tiene un retrato con el que aparece en la pantalla del juego. El tamaño de la
        imagen usada es de 75x75 px. La imagen puede tener zonas transparentes, en cuyo caso aparece 
        sobre un fondo gris oscuro. El retrato se especifica en la creación de la instancia.

        De la misma forma, cada personaje tiene una imagen para la ficha con la que aparece en el 
        tablero. El tamaño de la imagen usada es de 31x31 px.

        Programación
        ------------

        Se deben modificar las lineas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias y las listas de llamadas a los 
        métodos por listas similares, obtenidas a partir de la lista de personajes diseñados para el 
        juego.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        personaje en el diseño del juego.

        Para cambiar las imágenes de los retratos de los personajes es suficiente con situar las 
        imágenes nuevas en la carpeta de retratos del juego y cambiar los nombres de los archivos en 
        las llamadas al método correspondientes. Lo mismo ocurre con las imágenes de las fichas.
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        //
        //Miner  = new ActorPersonaje {this, LadoTablero::Izquierda, 0, L"Miner"};              //LUCASGG
        Amazona = new ActorPersonaje{ this, LadoTablero::Izquierda, 0, L"Amazona" };            //LUCASGG
        Samurai = new ActorPersonaje {this, LadoTablero::Izquierda, 1, L"Samurai"};             //Manuel
        //Patrek = new ActorPersonaje {this, LadoTablero::Izquierda, 2, L"Patrek"};
        //Alquimis = new ActorPersonaje {this, LadoTablero::Izquierda, 2, L"Alquimis"};           //lucasgm
        //Pirate = new ActorPersonaje {this, LadoTablero::Izquierda, 3, L"Pirate"};
        Shaolin= new ActorPersonaje { this, LadoTablero::Izquierda,3, L"Shaolin" };
        //Aristo = new ActorPersonaje {this, LadoTablero::Derecha,   0, L"Aristo"};             //LUCASGG
        TecMed = new ActorPersonaje{ this, LadoTablero::Derecha,   0, L"TecMed" };              //LUCASGG
        Franco  = new ActorPersonaje {this, LadoTablero::Derecha,   1, L"Franco"};              //Manuel
        //Hunter = new ActorPersonaje {this, LadoTablero::Derecha,   2, L"Hunter"};
        //Makhan = new ActorPersonaje{ this, LadoTablero::Derecha,   1, L"Makhan" };              //lucasgm
        //Thief  = new ActorPersonaje {this, LadoTablero::Derecha,   3, L"Thief"};
        PilotoMecha = new ActorPersonaje { this, LadoTablero::Derecha,  3, L"Piloto"};
        //
        //Miner ->ponArchivoRetrato (carpeta_retratos_juego + "miner1_75.png");                 //LUCASGG
        Amazona->ponArchivoRetrato(carpeta_retratos_juego + "Amazona.png");                     //LUCASGG
        Samurai->ponArchivoRetrato (carpeta_retratos_juego + "Samurai.png");                    //Manuel
        //Patrek->ponArchivoRetrato (carpeta_retratos_juego + "patrek_75.png");
        //Alquimis->ponArchivoRetrato (carpeta_retratos_juego + "Alquimista.png");                 //lucasgm
        //Pirate->ponArchivoRetrato (carpeta_retratos_juego + "pirate1_75.png");
        Shaolin->ponArchivoRetrato (carpeta_retratos_juego + "Shaolin.png");
        //Aristo->ponArchivoRetrato (carpeta_retratos_juego + "aristocrat_75.png");             //LUCASGG
        TecMed->ponArchivoRetrato(carpeta_retratos_juego + "TecnoMedico.png");                  //LUCASGG
        Franco->ponArchivoRetrato (carpeta_retratos_juego + "Francotirador.png");               //Manuel
        //Hunter->ponArchivoRetrato (carpeta_retratos_juego + "Hunter_75.png");
        //Makhan->ponArchivoFicha (carpeta_retratos_juego + "Makhanadeinos.png");                     //lucasgm
        //Thief ->ponArchivoRetrato (carpeta_retratos_juego + "thief2_75.png");
        PilotoMecha->ponArchivoRetrato(carpeta_retratos_juego + "PilotoMecha.png");
        //
        //Miner ->ponArchivoFicha (carpeta_retratos_juego + "FichaPasado.png");                 //LUCASGG
        Amazona->ponArchivoFicha(carpeta_retratos_juego + "FichaPasado.png");                   //LUCASGG
        Samurai->ponArchivoFicha (carpeta_retratos_juego + "FichaPasado.png");                  //Manuel
        //Patrek->ponArchivoFicha (carpeta_retratos_juego + "FichaPasado.png");
        //Alquimis->ponArchivoFicha (carpeta_retratos_juego + "ficha_roja.png");                   //lucasgm
        //Pirate->ponArchivoFicha (carpeta_retratos_juego + "FichaPasado.png");
        Shaolin->ponArchivoFicha (carpeta_retratos_juego + "FichaPasado.png");
        //Aristo->ponArchivoFicha (carpeta_retratos_juego + "FichaFuturo.png");                 //LUCASGG
        TecMed->ponArchivoFicha(carpeta_retratos_juego + "FichaFuturo.png");                    //LUCASGG
        Franco->ponArchivoFicha (carpeta_retratos_juego + "FichaFuturo.png");                   //Manuel
        //Hunter->ponArchivoFicha (carpeta_retratos_juego + "FichaFuturo.png");
        //Makhan->ponArchivoFicha(carpeta_retratos_juego + "ficha_azul.png");                     //lucasgm
        //Thief ->ponArchivoFicha (carpeta_retratos_juego + "FichaFuturo.png");
        PilotoMecha->ponArchivoFicha(carpeta_retratos_juego + "FichaFuturo.png");
        //
        //Miner ->ponIniciativa (20);           //LUCASGG
        Amazona->ponIniciativa(20);             //LUCASGG
        Samurai->ponIniciativa (19);            //Manuel
        //Patrek->ponIniciativa (18);
        //Alquimis->ponIniciativa(18);            //lucasgm
        //Pirate->ponIniciativa (17);
        Shaolin->ponIniciativa(17);
        //Aristo->ponIniciativa (20);           //LUCASGG
        TecMed->ponIniciativa(20);              //LUCASGG
        Franco->ponIniciativa (19);             //Manuel
        //Hunter->ponIniciativa (18);
        //Makhan->ponIniciativa(19);              //lucasgm
        //Thief ->ponIniciativa (17);
        PilotoMecha->ponIniciativa (17);
        //
        //agregaPersonaje (Miner);              //LUCASGG
        agregaPersonaje (Amazona);              //LUCASGG
        agregaPersonaje (Samurai);              //Manuel
        //agregaPersonaje (Patrek);
        //agregaPersonaje(Alquimis);              //lucasgm
        //agregaPersonaje (Pirate);
        agregaPersonaje (Shaolin);
        //agregaPersonaje (Aristo);             //LUCASGG
        agregaPersonaje (TecMed);               //LUCASGG
        agregaPersonaje (Franco);               //Manuel
        //agregaPersonaje (Hunter);
        //agregaPersonaje(Makhan);                //lucasgm
        agregaPersonaje (Thief);
        agregaPersonaje (PilotoMecha);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaHabilidades () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Quinta sección - Las habilidades - Segunda parte

        En esta sección se configuran las habilidades compartidas por los personajes del juego. En 
        la primera parte se establecen las variables destinadas a almacenar las instancias que 
        definen las habilidades. En esta segunda parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre de la habilidad correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a las habilidades:

             a) Nombre: Asignado en la creación de la instancia en una cadena de caracteres. 

             b) Enfoque: Indica a que esta enfocada la habilidad. Puede ser a un personaje, a un 
                área formada por varias celdas del tablero o hacia el mismo personaje que usa la 
                habilidad. 

             c) Acceso: Indica si el efecto de la habilidad puede atravesar muros. Puede ser directo,
                indirecto o ninguno.

             d) Antagonista: Indica a que grupo de personajes se dirige la habilidad. Puede ser a un
                oponente, a un aliado o a sí mismo.

             e) Descripción: Es un texto largo que describe la habilidad.

        Imágenes
        --------

        Cada habilidad tiene una imagen con el que aparece en la pantalla del juego. El tamaño de la
        imagen usada es de 50x50 px. La imagen puede tener zonas transparentes, en cuyo caso aparece 
        sobre una imagen de fondo, que puede ser distinta para cada habilidad o la misma para todas. 
        Las dos imágenes de cada habilidad se especifican la misma llamada a un método.

        Sonidos
        -------

        Cada habilidad tiene un sonido que suena cuando el personaje la usa. El sonido se carga de 
        un archivo de tipo 'wav', 'ogg' o 'flac', pero no 'mp3'. El tiempo de emisión del sonido
        debe ser corto (escasos segundos).

        Programación
        ------------

        Se deben modificar las lineas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias y las listas de llamadas a los 
        métodos por listas similares, obtenidas a partir de la lista de habilidades diseñadas para 
        el juego.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        habilidad en el diseño del juego.

        Para cambiar las imágenes de las habilidad es suficiente con situar las imágenes nuevas en 
        la carpeta de habilidades del juego y cambiar los nombres en las llamadas al método 
        correspondiente. 
        
        Para cambiar los sonidos de las habilidad es suficiente con situar los sonidos nuevos en 
        la carpeta de sonidos del juego y cambiar los nombres en las llamadas al método 
        correspondiente. 
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        //
        ataqueEspadaNormal   = new Habilidad {
                L"Ataque cuerpo a cuerpo normal", 
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        ataqueArco           = new Habilidad {
                L"Ataque a distancia normal",     
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        ataqueEspadaPoderoso = new Habilidad {
                L"Ataque poderoso",               
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        defensaFerrea        = new Habilidad {
                L"Defensa férrea",                
                EnfoqueHabilidad::si_mismo,  AccesoHabilidad::ninguno,   Antagonista::si_mismo};
        curacionSimple       = new Habilidad {
                L"Curación",                      
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::aliado};
        curacionGrupo        = new Habilidad {
                L"Curación en grupo",             
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::aliado};
        proyectilMagico      = new Habilidad {
                L"Proyectil mágico",              
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::oponente};
        bolaFuego            = new Habilidad {
                L"Bola de fuego",                 
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::oponente};
        palmaChi             = new Habilidad {
                L"Palma de Chi",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        pocionVenenosa       = new Habilidad {
                L"Poción Venenosa",
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::oponente};
        rezo                 = new Habilidad {
                L"Rezo",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::aliado};
        microGranada         = new Habilidad {
                L"Micro Granada",
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::oponente};
        misil                = new Habilidad {
                L"Misil",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        lanzaLaser           = new Habilidad {
                L"Lanza Láser",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        barricadaRetractil   = new Habilidad{
                L"Barricada Retráctil",
                EnfoqueHabilidad::si_mismo,  AccesoHabilidad::ninguno,   Antagonista::si_mismo };

        campoDeCuracion = new Habilidad{
                L"Campo de curacion",
                EnfoqueHabilidad::area,      AccesoHabilidad::directo, Antagonista::aliado };               //LUCASGG
        ataqueBisturi = new Habilidad{
                L"Ataque cuerpo a cuerpo con bisturí",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente };           //LUCASGG
        drogaDeCombate = new Habilidad{
                L"Curación",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::aliado };             //LUCASGG
        ataqueArcoConVeneno = new Habilidad{
                L"Ataque a distancia con veneno",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente };           //LUCASGG
        ataqueCabalgado = new Habilidad{
                L"Ataque cabaldago",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente };           //LUCASGG
        defensaConEscudo = new Habilidad{
                L"Defensa con escudo",
                EnfoqueHabilidad::si_mismo,  AccesoHabilidad::ninguno,   Antagonista::si_mismo };            //LUCASGG
        //polvoraNegra = new Habilidad{
        //        L"polvora Negra",
        //        EnfoqueHabilidad::area,      AccesoHabilidad::indirecto,   Antagonista::aliado };              //lucasgm
        //fuegoLiquido = new Habilidad{
        //        L"fuego Liquido",
        //        EnfoqueHabilidad::area,      AccesoHabilidad::indirecto,   Antagonista::oponente };            //lucasgm
        //bombasAceite = new Habilidad{
        //        L"bombas de Aceite",
        //        EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::oponente };            //lucasgm
        //ojosLaser = new Habilidad{
        //        L"ojos Laser",
        //        EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::oponente };            //lucasgm
        //mordiscoSierra = new Habilidad{
        //        L"mordisco de Sierra",
        //        EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente };            //lucasgm
        //corteZigzag = new Habilidad{
        //        L"corte Zigzag",
        //        EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente };            //lucasgm
        cortePreciso = new Habilidad{
                L"Corte Preciso",
                EnfoqueHabilidad::personaje,      AccesoHabilidad::directo,   Antagonista::oponente };              //Manuel
        arremetida = new Habilidad{
                L"Arremetida",
                EnfoqueHabilidad::personaje,      AccesoHabilidad::directo,   Antagonista::oponente };            //Manuel
        voluntadFerrea = new Habilidad{
                L"Voluntad Férrea",
                EnfoqueHabilidad::si_mismo,      AccesoHabilidad::ninguno,   Antagonista::si_mismo };            //Manuel
        headShot = new Habilidad{
                L"HeadShot",
                EnfoqueHabilidad::personaje,      AccesoHabilidad::directo,   Antagonista::oponente };            //Manuel
        balaPrecisa = new Habilidad{
                L"Bala Paralizante",
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente };            //Manuel
        balaFragmentada = new Habilidad{
                L"Bala Fragmentada",
                EnfoqueHabilidad::area, AccesoHabilidad::directo,   Antagonista::oponente };            //Manuel

        //
        ataqueEspadaNormal  ->ponDescripcion (
                L"El personaje usa su espada para atacar a un enemigo que se encuentra en una casilla próxima.");
        ataqueArco          ->ponDescripcion (
                L"El personaje usa su arco para atacar a un enemigo que se encuentra en una casilla próxima.");
        ataqueEspadaPoderoso->ponDescripcion (
                L"El personaje blande su espada con fuerza para atacar a un enemigo que se encuentra en una casilla próxima.");
        defensaFerrea       ->ponDescripcion (
                L"El personaje aumenta su defensa hasta su próximo ronda.");
        curacionSimple      ->ponDescripcion (
                L"El personaje canaliza poder divino para sanar a un aliado.");
        curacionGrupo       ->ponDescripcion (
                L"El personaje canaliza poder divino para sanar a todos los personajes en un área.");
        proyectilMagico     ->ponDescripcion (
                L"El personaje acumula energía mágica y la lanza contra un enemigo.");
        bolaFuego           ->ponDescripcion (
                L"El personaje acumula energía mágica y la lanza contra un grupo de enemigos.");
        palmaChi            ->ponDescripcion (
                L"El personaje concentra energía en la palma de su mano y la desprende contra un enemigo que se encuentra en una casilla próxima.");
        pocionVenenosa      ->ponDescripcion (
                L"El personaje lanza una poción que envenena a los enemigos que se encuentren en un área.");
        rezo                ->ponDescripcion (
                L"El personaje se pone a rezar para sanar a un aliado que se encuentre dentro de su alcance.");
        microGranada        ->ponDescripcion(
                L"El personaje lanza una micro granada que daña a los enemigos que se encunetren en un área.");
        misil               ->ponDescripcion(
                L"El personaje usa un misil teledirigido para atacar a un enemigo que se encuentra en una casilla próxima.");
        lanzaLaser          ->ponDescripcion(
                L"El personaje usa una lanza láser para atacar a un enemigo que se encuentra en una casilla próxima.");
        barricadaRetractil  ->ponDescripcion(
                L"El personaje usa una barricada retráctil invisible que aumenta considerablemente su defensa hasta su próximo ronda.");

        campoDeCuracion->ponDescripcion(
            L"El personaje usa un campo de curacion para recuperar la salud de alidos y oponentes dentro de la region.");       //LUCASGG                                                                                  //LUCAS
        ataqueBisturi->ponDescripcion(
            L"El personaje usa su bistuí de operación para atacar a un enemigo que se encuentra en una casilla próxima.");      //LUCASGG
        drogaDeCombate->ponDescripcion(
            L"El personaje usa su jeringa para inyectar adrenalina a un aliado.");                                              //LUCASGG
        ataqueArcoConVeneno->ponDescripcion(
            L"El personaje usa su arco con veneno para atacar a un enemigo.");                                                  //LUCASGG
        ataqueCabalgado->ponDescripcion(
            L"El personaje monta su caballo con una lanza para atacar al enemigo.");                                            //LUCASGG
        defensaConEscudo->ponDescripcion(
            L"El personaje aumenta su defensa hasta su próximo ronda.");                                                        //LUCASGG

        //polvoraNegra->ponDescripcion(
        //    L"El personaje deja un rastro de polvora que confunde a los enemigos.");                                            //lucasgm
        //fuegoLiquido->ponDescripcion(
        //    L"El personaje deja un rastro de aceite inflamable y resbaladizo.");                                                //lucasgm
        //bombasAceite->ponDescripcion(
        //    L"El personaje prepara aceite hirviendo que la lanza contra un grupo de enemigos.");                                //lucasgm
        //ojosLaser->ponDescripcion(
        //    L"El personaje usa sus ojos laser para quemar a los enemigos.");                                                    //lucasgm
        //mordiscoSierra->ponDescripcion(
        //    L"El personaje hace un corte en area que daña a los enemigos.");                                                    //lucasgm
        //corteZigzag->ponDescripcion(
        //    L"El personaje daña a los enemigos saltando sobre ellos con cuchillas.");                                           //lucasgm

        cortePreciso->ponDescripcion(
            L"El personaje utiliza su katana para realizar un corte con una gran cantidad de daño.");                           //Manuel
        arremetida->ponDescripcion(
            L"El personaje hace una ráfaga de tajos rápidos con baja probabilidad de dar todos.");                              //Manuel
        voluntadFerrea->ponDescripcion(
            L"El personaje prepara utiliza un buffo a si mismo que impide que su vida baje de 1 en el siguiente turno.");       //Manuel
        headShot->ponDescripcion(
            L"El personaje usa su francotirador para realizar un preciso tiro en la cabeza del enemigo.");                      //Manuel
        balaPrecisa->ponDescripcion(
            L"El personaje utiliza una bala paralizante para dejar a un enemigo sin poder moverse durante 2 turnos.");          //Manuel
        balaFragmentada->ponDescripcion(
            L"El personaje utiliza su bala fragmentada para atacar en un area del escenario.");                                 //Manuel

        //
        ataqueEspadaNormal  ->ponArchivosImagenes (
                carpeta_habilids_juego + "espada.png",          carpeta_habilids_juego + "fondo_5.png");
        ataqueArco          ->ponArchivosImagenes (
                carpeta_habilids_juego + "arco_flecha.png",     carpeta_habilids_juego + "fondo_5.png");
        ataqueEspadaPoderoso->ponArchivosImagenes (
                carpeta_habilids_juego + "espada_poderosa.png", carpeta_habilids_juego + "fondo_5.png");
        defensaFerrea       ->ponArchivosImagenes (
                carpeta_habilids_juego + "escudo.png",          carpeta_habilids_juego + "fondo_5.png");
        curacionSimple      ->ponArchivosImagenes (
                carpeta_habilids_juego + "vela.png",            carpeta_habilids_juego + "fondo_5.png");
        curacionGrupo       ->ponArchivosImagenes (
                carpeta_habilids_juego + "vela_triple.png",     carpeta_habilids_juego + "fondo_5.png");
        proyectilMagico     ->ponArchivosImagenes (
                carpeta_habilids_juego + "cristales.png",       carpeta_habilids_juego + "fondo_5.png");
        bolaFuego           ->ponArchivosImagenes (
                carpeta_habilids_juego + "bola_fuego.png",      carpeta_habilids_juego + "fondo_5.png");
        palmaChi            ->ponArchivosImagenes (
                carpeta_habilids_juego + "palma_chi.png",       carpeta_habilids_juego + "fondo_5.png");
        pocionVenenosa      ->ponArchivosImagenes (
                carpeta_habilids_juego + "pocion_venenosa.png", carpeta_habilids_juego + "fondo_5.png");
        rezo                ->ponArchivosImagenes (
                carpeta_habilids_juego + "rezo.png",      carpeta_habilids_juego + "fondo_5.png");
        microGranada        ->ponArchivosImagenes (
                carpeta_habilids_juego + "micro_granada.png", carpeta_habilids_juego + "fondo_5.png");
        misil               ->ponArchivosImagenes (
                carpeta_habilids_juego + "misil.png", carpeta_habilids_juego + "fondo_5.png");
        lanzaLaser          ->ponArchivosImagenes(
                carpeta_habilids_juego + "lanza_laser.png", carpeta_habilids_juego + "fondo_5.png");
        barricadaRetractil  ->ponArchivosImagenes(
                carpeta_habilids_juego + "barricada_retractil.png", carpeta_habilids_juego + "fondo_5.png");

        campoDeCuracion->ponArchivosImagenes(
            carpeta_habilids_juego + "espada.png", carpeta_habilids_juego + "fondo_5.png");         //LUCASGG
        ataqueBisturi->ponArchivosImagenes(
            carpeta_habilids_juego + "espada.png", carpeta_habilids_juego + "fondo_5.png");         //LUCASGG
        drogaDeCombate->ponArchivosImagenes(
            carpeta_habilids_juego + "espada.png", carpeta_habilids_juego + "fondo_5.png");         //LUCASGG
        ataqueArcoConVeneno->ponArchivosImagenes(
            carpeta_habilids_juego + "arco_flecha.png", carpeta_habilids_juego + "fondo_5.png");    //LUCASGG
        ataqueCabalgado->ponArchivosImagenes(
            carpeta_habilids_juego + "espada.png", carpeta_habilids_juego + "fondo_5.png");         //LUCASGG
        defensaConEscudo->ponArchivosImagenes(
            carpeta_habilids_juego + "escudo.png", carpeta_habilids_juego + "fondo_5.png");         //LUCASGG

        //polvoraNegra->ponArchivosImagenes(
        //    carpeta_habilids_juego + "polvora_negra.png", carpeta_habilids_juego + "fondo_5.png");  //lucasgm
        //fuegoLiquido->ponArchivosImagenes(
        //    carpeta_habilids_juego + "fuego_liquido.png", carpeta_habilids_juego + "fondo_5.png");  //lucasgm
        //bombasAceite->ponArchivosImagenes(
        //    carpeta_habilids_juego + "bombas_aceite.png", carpeta_habilids_juego + "fondo_5.png");  //lucasgm
        //ojosLaser->ponArchivosImagenes(
        //    carpeta_habilids_juego + "ojos_laser.png", carpeta_habilids_juego + "fondo_5.png");     //lucasgm
        //mordiscoSierra->ponArchivosImagenes(
        //    carpeta_habilids_juego + "mordisco_sierra.png", carpeta_habilids_juego + "fondo_5.png");//lucasgm
        //corteZigzag->ponArchivosImagenes(
        //    carpeta_habilids_juego + "corte_zigzag.png", carpeta_habilids_juego + "fondo_5.png");   //lucasgm

        cortePreciso->ponArchivosImagenes(
            carpeta_habilids_juego + "corte_preciso.png", carpeta_habilids_juego + "fondo_5.png");  //Manuel
        arremetida->ponArchivosImagenes(
            carpeta_habilids_juego + "arremetida.png", carpeta_habilids_juego + "fondo_5.png");  //Manuel
        voluntadFerrea->ponArchivosImagenes(
            carpeta_habilids_juego + "defensa_ferrea.png", carpeta_habilids_juego + "fondo_5.png");  //Manuel
        headShot->ponArchivosImagenes(
            carpeta_habilids_juego + "headShot.png", carpeta_habilids_juego + "fondo_5.png");     //Manuel
        balaPrecisa->ponArchivosImagenes(
            carpeta_habilids_juego + "balaPrecisa.png", carpeta_habilids_juego + "fondo_5.png");//Manuel
        balaFragmentada->ponArchivosImagenes(
            carpeta_habilids_juego + "fragmented.png", carpeta_habilids_juego + "fondo_5.png");   //Manuel

        //
        ataqueEspadaNormal  ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        ataqueArco          ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        ataqueEspadaPoderoso->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        defensaFerrea       ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        curacionSimple      ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        curacionGrupo       ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        proyectilMagico     ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        bolaFuego           ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        palmaChi            ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        pocionVenenosa      ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        rezo                ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        microGranada        ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        misil               ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        lanzaLaser          ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");
        barricadaRetractil  ->ponArchivoSonido (carpeta_sonidos_juego + "Magic Missiles.wav");

        campoDeCuracion->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");            //LUCASGG
        ataqueBisturi->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");              //LUCASGG
        drogaDeCombate->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");             //LUCASGG
        ataqueArcoConVeneno->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");        //LUCASGG
        ataqueCabalgado->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");            //LUCASGG
        defensaConEscudo->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");           //LUCASGG

        //polvoraNegra->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");               //lucasgm
        //fuegoLiquido->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");               //lucasgm
        //bombasAceite->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");               //lucasgm
        //ojosLaser->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");                  //lucasgm
        //mordiscoSierra->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");             //lucasgm
        //corteZigzag->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");                //lucasgm

        cortePreciso->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");               //Manuel
        arremetida->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");                 //Manuel
        voluntadFerrea->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");             //Manuel
        headShot->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");                   //Manuel
        balaPrecisa->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");            //Manuel
        balaFragmentada->ponArchivoSonido(carpeta_sonidos_juego + "Magic Missiles.wav");            //Manuel
        //
        agregaHabilidad (ataqueEspadaNormal);
        agregaHabilidad (ataqueArco);
        agregaHabilidad (ataqueEspadaPoderoso);
        agregaHabilidad (defensaFerrea );
        agregaHabilidad (curacionSimple);
        agregaHabilidad (curacionGrupo );
        agregaHabilidad (proyectilMagico );
        agregaHabilidad (bolaFuego );
        agregaHabilidad (palmaChi );
        agregaHabilidad (pocionVenenosa );
        agregaHabilidad (rezo );
        agregaHabilidad (microGranada );
        agregaHabilidad (misil );
        agregaHabilidad (lanzaLaser );
        agregaHabilidad (barricadaRetractil );

        agregaHabilidad(drogaDeCombate);                                                            //LUCASGG
        agregaHabilidad(campoDeCuracion);                                                           //LUCASGG
        agregaHabilidad(ataqueBisturi);                                                             //LUCASGG
        agregaHabilidad(ataqueArcoConVeneno);                                                       //LUCASGG
        agregaHabilidad(ataqueCabalgado);                                                           //LUCASGG
        agregaHabilidad(defensaConEscudo);                                                          //LUCASGG

        //agregaHabilidad(polvoraNegra);                                                              //lucasgm
        //agregaHabilidad(fuegoLiquido);                                                              //lucasgm
        //agregaHabilidad(bombasAceite);                                                              //lucasgm
        //agregaHabilidad(ojosLaser);                                                                 //lucasgm
        //agregaHabilidad(mordiscoSierra);                                                            //lucasgm
        //agregaHabilidad(corteZigzag);                                                               //lucasgm

        agregaHabilidad(cortePreciso);                                                              //Manuel
        agregaHabilidad(arremetida);                                                                //Manuel
        agregaHabilidad(defensaFerrea);                                                             //Manuel
        agregaHabilidad(headShot);                                                                  //Manuel
        agregaHabilidad(balaPrecisa);                                                               //Manuel
        agregaHabilidad(balaFragmentada);                                                           //Manuel
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaTiposEstadisticas () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Sexta sección - Los tipos de ataque, defensa y daño (estadísticas) - Segunda parte

        En esta sección se configuran los tipos de ataque, defensa y daño del juego. Estos tipos  
        son usados para establecer las estadisticas del juego en los personajes y en las habilidades. 
        En la primera parte se establecen las variables destinadas a almacenar las instancias que 
        definen los tipos de ataque, defensa y daño. En esta parte se crean las instancias y se 
        configuran.

        Las variable usan un nombre similar al nombre de los tipos correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los tipos:

             a) Descripción: Asignado en la creación de la instancia en una cadena de caracteres. 
                Deben ser cortos y deben comenzar con la palabra 'Ataque', 'Defensa' o 'Daño'.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias por listas similares, obtenidas a 
        partir de la lista de tipos diseñados para el juego. El nombre de la clase (por ejemplo 
        'TipoAtaque' para los ataques) establece si es un tipo de ataque, de defensa o de daño.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        tipo en el diseño del juego.

        *******************************************************************************************/
        //
        ataqueCuerpoACuerpo  = new TipoAtaque  {L"Ataque cuerpo a cuerpo"};
        ataqueADistancia     = new TipoAtaque  {L"Ataque a distancia"};
        ataqueMagico         = new TipoAtaque  {L"Ataque mágico"};
        defensaCuerpoACuerpo = new TipoDefensa {L"Defensa cuerpo a cuerpo"};
        defensaADistancia    = new TipoDefensa {L"Defensa a distancia"};
        defensaMagica        = new TipoDefensa {L"Defensa mágica"};
        danoFisico           = new TipoDano    {L"Daño físico"};
        danoMagico           = new TipoDano    {L"Daño mágico"};

        ataqueQuirurgico = new TipoAtaque{ L"Ataque quirurgico" };                      //LUCASGG
        ataqueArcoVenenoso = new TipoAtaque{ L"Ataque venenoso" };                      //LUCASGG
        ataqueTajoCabalgado = new TipoAtaque{ L"Ataque cabalgado" };                    //LUCASGG
        defensaQuirurgica = new TipoDefensa{ L"Defensa quirurgica" };                   //LUCASGG
        defensaArcoVenenoso = new TipoDefensa{ L"Defensa venenosa" };                   //LUCASGG
        defensaTajoCabalgado = new TipoDefensa{ L"Defensa contra ataque cabalgado" };   //LUCASGG



        //
        agregaAtaque  (ataqueCuerpoACuerpo );
        agregaAtaque  (ataqueADistancia);
        agregaAtaque  (ataqueMagico);
        agregaDefensa (defensaCuerpoACuerpo);
        agregaDefensa (defensaADistancia );
        agregaDefensa (defensaMagica );
        agregaDano    (danoFisico);
        agregaDano    (danoMagico);

        agregaAtaque(ataqueQuirurgico);                                                 //LUCASGG
        agregaAtaque(ataqueArcoVenenoso);                                               //LUCASGG
        agregaAtaque(ataqueTajoCabalgado);                                              //LUCASGG
        agregaDefensa(defensaQuirurgica);                                               //LUCASGG
        agregaDefensa(defensaArcoVenenoso);                                             //LUCASGG
        agregaDefensa(defensaTajoCabalgado);                                            //LUCASGG

        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaHabilidadesPersonajes () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Octava sección - Las habilidades de los personajes

        En esta sección se establecen que habilidades que tiene cada personajes del juego.

        Cada personaje debe tener entre 1 y 10 habilidades.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de habilidades de cada personaje por listas similares, 
        obtenidas a partir del diseño del juego.

        *******************************************************************************************/
        //
        //Miner ->agregaHabilidad (ataqueEspadaNormal);                     //LUCASGG
        //Miner ->agregaHabilidad (ataqueArco);                             //LUCASGG
        //Miner ->agregaHabilidad (ataqueEspadaPoderoso);                   //LUCASGG
        //Miner ->agregaHabilidad (defensaFerrea);                          //LUCASGG
        Amazona->agregaHabilidad(ataqueArcoConVeneno);                      //LUCASGG
        Amazona->agregaHabilidad(ataqueCabalgado);                          //LUCASGG
        Amazona->agregaHabilidad(defensaConEscudo);                         //LUCASGG
        //
        Samurai->agregaHabilidad (cortePreciso);                            //Manuel
        Samurai->agregaHabilidad (arremetida);                              //Manuel
        Samurai->agregaHabilidad (defensaFerrea);                           //Manuel
        //
        //Alquimis->agregaHabilidad(polvoraNegra);                            //lucasgm
        //Alquimis->agregaHabilidad(fuegoLiquido);                            //lucasgm
        //Alquimis->agregaHabilidad(bombasAceite);                            //lucasgm   
        //
        //Patrek->agregaHabilidad (ataqueEspadaNormal);
        //Patrek->agregaHabilidad (proyectilMagico);
        //Patrek->agregaHabilidad (bolaFuego);
        //
        /*Pirate->agregaHabilidad (ataqueEspadaNormal);
        Pirate->agregaHabilidad (ataqueArco);
        Pirate->agregaHabilidad (ataqueEspadaPoderoso);*/
        //
        Shaolin->agregaHabilidad (palmaChi);
        Shaolin->agregaHabilidad (pocionVenenosa);
        Shaolin->agregaHabilidad (rezo);
        //
        //Aristo->agregaHabilidad (ataqueEspadaNormal);                     //LUCASGG
        //Aristo->agregaHabilidad (ataqueArco);                             //LUCASGG
        //Aristo->agregaHabilidad (ataqueEspadaPoderoso);                   //LUCASGG
        //Aristo->agregaHabilidad (defensaFerrea);                          //LUCASGG
        TecMed->agregaHabilidad(ataqueBisturi);                             //LUCASGG
        TecMed->agregaHabilidad(campoDeCuracion);                           //LUCASGG
        TecMed->agregaHabilidad(drogaDeCombate);                            //LUCASGG
        //
        Franco->agregaHabilidad (headShot);                                 //Manuel
        Franco->agregaHabilidad (balaPrecisa);                          //Manuel
        Franco->agregaHabilidad (balaFragmentada);                          //Manuel
        //
        //Hunter->agregaHabilidad (ataqueEspadaNormal);
        //Hunter->agregaHabilidad (proyectilMagico);
        //Hunter->agregaHabilidad (bolaFuego);
        //Makhan->agregaHabilidad(ojosLaser);                                 //lucasgm
        //Makhan->agregaHabilidad(mordiscoSierra);                            //lucasgm
        //Makhan->agregaHabilidad(corteZigzag);                               //lucasgm
        //
        /*Thief ->agregaHabilidad (ataqueEspadaNormal);
        Thief ->agregaHabilidad (ataqueArco);
        Thief ->agregaHabilidad (ataqueEspadaPoderoso);*/
        //
        PilotoMecha->agregaHabilidad(microGranada);
        PilotoMecha->agregaHabilidad(misil);
        PilotoMecha->agregaHabilidad(lanzaLaser);
        PilotoMecha->agregaHabilidad(barricadaRetractil);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaEstadisticasHabilidades () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Novena sección - Las estadísticas de las habilidades

        En esta sección se establecen diversos atributos y valores para las habilidades del juego,
        incluyendo las estadisticas del juego.

        Estadísticas
        ------------

        Las habilidades se clasifican en habilidades de ataque, de curación y auto-aplicada. Esta 
        clasificación se establece mediante el atributo 'Antagonista' de la habilidad. 

            - Si 'Antagonista' es 'oponente' la habilidad es de ataque. El ataque puede afectar a un 
              personaje o a los personajes de un área del tablero.
            - Si 'Antagonista' es 'aliado' la habilidad es de curación. La curación puede afectar a 
              un personaje o a los personajes de un área del tablero.
            - Si 'Antagonista' es 'si_mismo' la habilidad es auto-aplicada.

        Los valores que se establecen para las habilidades son:

             a) Coste: Es el número de puntos de acción que se gastan al usar la habilidad.

             b) Alcance: En las habilidades de ataque y curación debe estar establecido el alcance 
                de la habilidad. La habilidad solo se puede usar si el alcance lo permite. Es un 
                valor que indica un número de casillas del tablero y debe ser positivo.

             c) Radio de ara de alcance: En las habilidades de ataque y curación que afectan a un 
                área del tablero, debe estar establecido el radio del área. Es un valor que indica 
                un número de casillas del tablero y debe ser positivo. 

             d) Tipo de ataque: Cuando una habilidad es de ataque, debe tener establecido un tipo de 
                ataque. El tipo de ataque se usa en el personaje atacante.

             e) Tipo de defensa: Cuando una habilidad es de ataque, debe tener establecido un tipo 
                de defensa. El tipo de defensa se usa en el personaje atacado.

             f) Tipo de daño: Cuando una habilidad es de ataque, debe tener establecido un tipo de 
                daño. El tipo de daño se usa en el personaje atacado.

             g) Valor del daño: Cuando una habilidad es de ataque, debe tener establecido un valor 
                para el daño en puntos de vitalidad. El valor del daño se usa con el personaje 
                atacado.

             h) Curación: Cuando una habilidad es de curación, debe tener establecido un valor de 
                curación en puntos.

             i) Efecto en ataque: Cuando una habilidad es auto-aplicada, puede tener establecido uno 
                o más tipos de ataque, asignado como tipo de efecto en ataque. Alternativamente 
                (y excluyentemente) puede tener establecido un efecto en defensa (véase k).

             j) Valor del efecto en ataque: Cuando una habilidad es auto-aplicada, para cada tipo de 
                efecto en ataque establecido (véase i), debe tener establecido un valor del efecto
                en ataque en puntos de vitalidad.

             k) Efecto en defensa: Cuando una habilidad es auto-aplicada, puede tener establecido 
                uno o más tipos de defensa, asignado como tipo de efecto en defensa. Alternativamente 
                (excluyentemente) puede tener establecido un efecto en ataque (véase i).

             l) Valor del efecto en defensa: Cuando una habilidad es auto-aplicada, para cada tipo de 
                efecto en defensa establecido (véase k), debe tener establecido un valor del efecto
                en defensa en puntos de vitalidad.


        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las asignaciones de valores por asignaciones similares, obtenidas a 
        partir del diseño del juego.

        Los métodos usados en las líneas de código siguientes establecen si se debe usar un tipo de 
        ataque, de defensa o de daño. Por ejemplo, el método 'asignaAtaque' debe ser llamado con un 
        parámetro del tipo (puntero) 'TipoAtaque'.  

        *******************************************************************************************/
        //
        ataqueEspadaNormal->ponCoste (3);                                       
        ataqueEspadaNormal->ponAlcance (1);
        ataqueEspadaNormal->asignaAtaque  (ataqueCuerpoACuerpo); 
        ataqueEspadaNormal->asignaDefensa (defensaCuerpoACuerpo); 
        ataqueEspadaNormal->asignaDano    (danoFisico, 20); 
        //
        ataqueArco->ponCoste (5);
        ataqueArco->ponAlcance (15);
        ataqueArco->asignaAtaque  (ataqueADistancia);
        ataqueArco->asignaDefensa (defensaADistancia);
        ataqueArco->asignaDano    (danoFisico, 20);
        //
        ataqueEspadaPoderoso->ponCoste (5);
        ataqueEspadaPoderoso->ponAlcance (1);
        ataqueEspadaPoderoso->asignaAtaque  (ataqueCuerpoACuerpo);
        ataqueEspadaPoderoso->asignaDefensa (defensaCuerpoACuerpo);
        ataqueEspadaPoderoso->asignaDano    (danoFisico, 50);
        //
        defensaFerrea->ponCoste (3);
        defensaFerrea->agregaEfectoDefensa (defensaCuerpoACuerpo, 30);
        defensaFerrea->agregaEfectoDefensa (defensaADistancia,    30);
        //
        curacionSimple->ponCoste (5);
        curacionSimple->ponAlcance (3);  
        curacionSimple->asignaCuracion (40);
        //
        curacionGrupo->ponCoste (10);
        curacionGrupo->ponAlcance (3);  
        curacionGrupo->ponRadioAlcance (3);
        curacionGrupo->asignaCuracion (40);
        //
        proyectilMagico->ponCoste (7);
        proyectilMagico->ponAlcance (15);                                            
        proyectilMagico->asignaAtaque  (ataqueMagico);
        proyectilMagico->asignaDefensa (defensaMagica);
        proyectilMagico->asignaDano    (danoMagico, 30);
        //
        bolaFuego->ponCoste (10);
        bolaFuego->ponAlcance (8);
        bolaFuego->ponRadioAlcance (3);
        bolaFuego->asignaAtaque  (ataqueMagico);
        bolaFuego->asignaDefensa (defensaMagica);
        bolaFuego->asignaDano    (danoMagico, 50);
        //
        palmaChi->ponCoste (1);
        palmaChi->ponAlcance (1);
        palmaChi->asignaAtaque (ataqueCuerpoACuerpo);
        palmaChi->asignaDefensa(defensaCuerpoACuerpo);
        palmaChi->asignaDano   (danoFisico, 40);
        //
        pocionVenenosa->ponCoste (3);
        pocionVenenosa->ponAlcance (7);
        pocionVenenosa->ponRadioAlcance (2);
        pocionVenenosa->asignaAtaque (ataqueMagico);
        pocionVenenosa->asignaDefensa (defensaMagica);
        pocionVenenosa->asignaDano (danoMagico, 30);
        //
        rezo->ponCoste (4);
        rezo->ponAlcance (3);
        rezo->asignaCuracion (30);
        //
        microGranada->ponCoste(3);
        microGranada->ponAlcance(8);
        microGranada->ponRadioAlcance(1);
        microGranada->asignaAtaque(ataqueMagico);
        microGranada->asignaDefensa(defensaMagica);
        microGranada->asignaDano(danoMagico, 30);
        //
        misil->ponCoste(4);
        misil->ponAlcance(15);
        misil->asignaAtaque(ataqueADistancia);
        misil->asignaDefensa(defensaADistancia);
        misil->asignaDano(danoFisico, 40);
        //
        lanzaLaser->ponCoste(1);
        lanzaLaser->ponAlcance(2);
        lanzaLaser->asignaAtaque(ataqueCuerpoACuerpo);
        lanzaLaser->asignaDefensa(defensaCuerpoACuerpo);
        lanzaLaser->asignaDano(danoFisico, 30);
        //
        barricadaRetractil->ponCoste(3);
        barricadaRetractil->agregaEfectoDefensa(defensaCuerpoACuerpo, 50);
        barricadaRetractil->agregaEfectoDefensa(defensaADistancia, 50);

        //
        ataqueBisturi->ponCoste(3);                                         //LUCASGG
        ataqueBisturi->ponAlcance(1);                                       //LUCASGG
        ataqueBisturi->asignaAtaque(ataqueQuirurgico);                      //LUCASGG
        ataqueBisturi->asignaDefensa(defensaQuirurgica);                    //LUCASGG
        ataqueBisturi->asignaDano(danoFisico, 10);                          //LUCASGG
        //
        ataqueArcoConVeneno->ponCoste(5);                                   //LUCASGG
        ataqueArcoConVeneno->ponAlcance(15);                                //LUCASGG
        ataqueArcoConVeneno->asignaAtaque(ataqueArcoVenenoso);              //LUCASGG
        ataqueArcoConVeneno->asignaDefensa(defensaArcoVenenoso);            //LUCASGG
        ataqueArcoConVeneno->asignaDano(danoFisico, 20);                    //LUCASGG
        //
        ataqueCabalgado->ponCoste(5);                                       //LUCASGG
        ataqueCabalgado->ponAlcance(1);                                     //LUCASGG
        ataqueCabalgado->asignaAtaque(ataqueTajoCabalgado);                 //LUCASGG
        ataqueCabalgado->asignaDefensa(defensaTajoCabalgado);               //LUCASGG
        ataqueCabalgado->asignaDano(danoFisico, 50);                        //LUCASGG
        //
        defensaConEscudo->ponCoste(3);
        defensaConEscudo->agregaEfectoDefensa(defensaQuirurgica, 30);       //LUCASGG
        defensaConEscudo->agregaEfectoDefensa(defensaArcoVenenoso, 30);     //LUCASGG
        defensaConEscudo->agregaEfectoDefensa(defensaTajoCabalgado, 30);    //LUCASGG
        defensaConEscudo->agregaEfectoDefensa(defensaCuerpoACuerpo, 30);    //LUCASGG
        defensaConEscudo->agregaEfectoDefensa(defensaADistancia, 30);       //LUCASGG
        //
        campoDeCuracion->ponCoste(10);                                      //LUCASGG
        campoDeCuracion->ponAlcance(10);                                    //LUCASGG
        campoDeCuracion->ponRadioAlcance(2);                                //LUCASGG
        campoDeCuracion->asignaCuracion(30);                                //LUCASGG
        //
        drogaDeCombate->ponCoste(5);                                        //LUCASGG
        drogaDeCombate->ponAlcance(3);                                      //LUCASGG
        drogaDeCombate->asignaCuracion(40);                                 //LUCASGG
        //
        //ojosLaser->ponCoste(9);                                             //lucasgm
        //ojosLaser->ponAlcance(4);
        //ojosLaser->ponRadioAlcance(2);
        //ojosLaser->asignaAtaque(ataqueCuerpoACuerpo);
        //ojosLaser->asignaDefensa(defensaCuerpoACuerpo);
        //ojosLaser->asignaDano(danoMagico, 50);
        ////
        //mordiscoSierra->ponCoste(6);
        //mordiscoSierra->ponAlcance(2);
        //mordiscoSierra->asignaAtaque(ataqueCuerpoACuerpo);
        //mordiscoSierra->asignaDefensa(defensaCuerpoACuerpo);
        //mordiscoSierra->asignaDano(danoFisico, 45);
        ////
        //corteZigzag->ponCoste(10);
        //corteZigzag->ponAlcance(3);
        //corteZigzag->asignaAtaque(ataqueCuerpoACuerpo);
        //corteZigzag->asignaDefensa(defensaCuerpoACuerpo);
        //corteZigzag->asignaDano(danoFisico, 70);
        ////
        //bombasAceite->ponCoste(9);
        //bombasAceite->ponAlcance(12);
        //bombasAceite->ponRadioAlcance(4);
        //bombasAceite->asignaAtaque(ataqueMagico);
        //bombasAceite->asignaDefensa(defensaMagica);
        //bombasAceite->asignaDano(danoMagico, 37.5);
        ////
        //polvoraNegra->ponCoste(8);
        //polvoraNegra->ponAlcance(5);
        //polvoraNegra->ponRadioAlcance(3.4);
        //polvoraNegra->asignaCuracion(38);
        ////
        //fuegoLiquido->ponCoste(9);
        //fuegoLiquido->ponAlcance(14);
        //fuegoLiquido->ponRadioAlcance(7);
        //fuegoLiquido->asignaAtaque(ataqueMagico);
        //fuegoLiquido->asignaDefensa(defensaMagica);
        //fuegoLiquido->asignaDano(danoMagico, 17);                           //lucasgm
        /*******************************************************************************************
        /******************************************************************************************/
        cortePreciso->ponCoste(6);                                             //Manuel
        cortePreciso->ponAlcance(1);
        cortePreciso->asignaAtaque(ataqueCuerpoACuerpo);
        cortePreciso->asignaDefensa(defensaCuerpoACuerpo);
        cortePreciso->asignaDano(danoFisico, 65);
        //
        arremetida->ponCoste(8);
        arremetida->ponAlcance(2);
        arremetida->asignaAtaque(ataqueCuerpoACuerpo);
        arremetida->asignaDefensa(defensaCuerpoACuerpo);
        arremetida->asignaDano(danoFisico, 50);
        //
        voluntadFerrea->ponCoste(4);
        voluntadFerrea->agregaEfectoDefensa(defensaCuerpoACuerpo, 30);
        voluntadFerrea->agregaEfectoDefensa(defensaADistancia, 30);
        //
        headShot->ponCoste(9);
        headShot->ponAlcance(14);
        headShot->asignaAtaque(ataqueADistancia);
        headShot->asignaDefensa(defensaADistancia);
        headShot->asignaDano(danoFisico, 40);
        //
        balaPrecisa->ponCoste(4);
        balaPrecisa->ponAlcance(20);
        balaPrecisa->asignaAtaque(ataqueADistancia);
        balaPrecisa->asignaDefensa(defensaADistancia);
        balaPrecisa->asignaDano(danoFisico, 10);
        //
        balaFragmentada->ponCoste(9);
        balaFragmentada->ponAlcance(14);
        balaFragmentada->ponRadioAlcance(7);
        balaFragmentada->asignaAtaque(ataqueADistancia);
        balaFragmentada->asignaDefensa(defensaADistancia);
        balaFragmentada->asignaDano(danoFisico, 15);                           //Manuel
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaEstadisticasPersonajes () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Décima sección - Los tipos de ataque, defensa y reducción de daño de los personajes

        En esta sección se establecen que tipos de ataque, defensa y reducción de daño tiene cada 
        personajes del juego, junto con la correspondiente puntuación.

        Configuración
        -------------

        La configuración de los tipos se debe realizar de la siguiente forma:

             a) Si un personaje tiene una habilidad y esta habilidad tiene un tipo de ataque, el 
                personaje debe tener ese tipo de ataque.

             b) Cada personaje debe tener todos los tipos de defensa.

             c) Cada personaje debe tener todos los tipos de daño, en forma de reducción de daño.

             d) Si un personaje tiene una habilidad y esta habilidad tiene un efecto en ataque,
                que está definido usando un tipo de ataque, el personaje debe tener dicho tipo de 
                ataque.

             e) Si un personaje tiene una habilidad y esta habilidad tiene un efecto en defensa,
                que está definido usando un tipo de defensa, el personaje debe tener dicho tipo de 
                defensa. Esta propiedad está establecida previamente mediante el punto (b)

             f) Cada tipo de ataque, defensa y reducción de daño del personaje debe tener una 
                puntuación. La puntuación no puede ser negativa.        

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de tipos de ataque, defensa y reducción de daño de cada 
        personaje por listas similares, obtenidas a partir del diseño del juego.

        Los métodos usados en las líneas de código siguientes establecen si el tipo es ataque, 
        defensa o daño. Por ejemplo, el método 'agregaReduceDano' debe ser llamado con un parámetro 
        del tipo (puntero) 'TipoDano'.  

        *******************************************************************************************/
        //
        //Miner ->agregaAtaque     (ataqueCuerpoACuerpo,  70);
        //Miner ->agregaAtaque     (ataqueADistancia,     50);
        //Miner ->agregaDefensa    (defensaCuerpoACuerpo, 70);
        //Miner ->agregaDefensa    (defensaADistancia,    70);
        //Miner ->agregaDefensa    (defensaMagica,        20);
        //Miner ->agregaReduceDano (danoFisico,           10);
        //Miner ->agregaReduceDano (danoMagico,            5);
        Amazona ->agregaAtaque     (ataqueArcoVenenoso,   50);         //LUCASGG
        Amazona ->agregaAtaque     (ataqueTajoCabalgado,  50);         //LUCASGG
        Amazona ->agregaDefensa    (defensaTajoCabalgado, 30);         //LUCASGG
        Amazona ->agregaDefensa    (defensaArcoVenenoso,  70);         //LUCASGG
        Amazona ->agregaDefensa    (defensaQuirurgica,     5);         //LUCASGG
        Amazona ->agregaDefensa    (defensaCuerpoACuerpo, 70);         //LUCASGG
        Amazona ->agregaDefensa    (defensaADistancia,    70);         //LUCASGG 
        Amazona ->agregaDefensa    (defensaMagica,        20);         //LUCASGG
        Amazona ->agregaReduceDano (danoFisico,           10);         //LUCASGG
        Amazona ->agregaReduceDano (danoMagico,            5);         //LUCASGG
        //
        Samurai->agregaAtaque     (ataqueCuerpoACuerpo,  50);                       //Manuel
      //Samurai  ->agregaAtaque     (ataqueADistancia,     50);  No se usa             //Manuel
        Samurai->agregaAtaque     (ataqueMagico,         0);                       //Manuel
        Samurai->agregaDefensa    (defensaCuerpoACuerpo, 60);                       //Manuel
        Samurai->agregaDefensa    (defensaADistancia,    70);                       //Manuel
        Samurai->agregaDefensa    (defensaMagica,        30);                       //Manuel
        Samurai->agregaReduceDano (danoFisico,            10);                       //Manuel
        Samurai->agregaReduceDano (danoMagico,           5);                       //Manuel
        Samurai->agregaDefensa    (defensaTajoCabalgado, 30);            //LUCASGG        
        Samurai->agregaDefensa    (defensaArcoVenenoso,  50);            //LUCASGG
        Samurai->agregaDefensa    (defensaQuirurgica,     5);            //LUCASGG
        //                       
        //Patrek->agregaAtaque     (ataqueCuerpoACuerpo,  50);
        //Patrek->agregaAtaque     (ataqueADistancia,     50);  No se usa
        //Patrek->agregaAtaque     (ataqueMagico,         70);        
        //Patrek->agregaDefensa    (defensaCuerpoACuerpo, 40);
        //Patrek->agregaDefensa    (defensaADistancia,    40);
        //Patrek->agregaDefensa    (defensaMagica,        30);
        //Patrek->agregaReduceDano (danoFisico,            0);
        //Patrek->agregaReduceDano (danoMagico,           15);
        //Patrek->agregaDefensa    (defensaTajoCabalgado, 30);           //LUCASGG        
        //Patrek->agregaDefensa    (defensaArcoVenenoso,  40);           //LUCASGG
        //Patrek->agregaDefensa    (defensaQuirurgica,     5);           //LUCASGG
        //Alquimis->agregaAtaque     (ataqueCuerpoACuerpo,  20);           //lucasgm
        //Alquimis->agregaAtaque     (ataqueADistancia,     68);           //lucasgm
        //Alquimis->agregaDefensa    (defensaCuerpoACuerpo, 30);           //lucasgm
        //Alquimis->agregaDefensa    (defensaADistancia,    40);           //lucasgm
        //Alquimis->agregaDefensa    (defensaMagica,        60);           //lucasgm
        //Alquimis->agregaReduceDano (danoFisico,            3);           //lucasgm
        //Alquimis->agregaReduceDano (danoMagico,           13);           //lucasgm
        //Alquimis->agregaDefensa    (defensaTajoCabalgado, 30);           //lucasgm        
        //Alquimis->agregaDefensa    (defensaArcoVenenoso,  50);           //lucasgm
        //Alquimis->agregaDefensa    (defensaQuirurgica,     5);           //lucasgm
        //                       
        /*Pirate->agregaAtaque     (ataqueCuerpoACuerpo,  60);
        Pirate->agregaAtaque     (ataqueADistancia,     70);        
        Pirate->agregaDefensa    (defensaCuerpoACuerpo, 50);
        Pirate->agregaDefensa    (defensaADistancia,    50);
        Pirate->agregaDefensa    (defensaMagica,        50);
        Pirate->agregaReduceDano (danoFisico,            7);
        Pirate->agregaReduceDano (danoMagico,            7);*/
        //                       
        Shaolin->agregaAtaque    (ataqueCuerpoACuerpo,  30);
      //Shaolin->agregaAtaque    (ataqueADistancia,     30);
        Shaolin->agregaAtaque    (ataqueMagico,         40);
        Shaolin->agregaDefensa   (defensaCuerpoACuerpo, 30);
        Shaolin->agregaDefensa   (defensaADistancia,    30);
        Shaolin->agregaDefensa   (defensaMagica,        40);
        Shaolin->agregaReduceDano(danoFisico,           10);
        Shaolin->agregaReduceDano(danoMagico,            5);
        Shaolin->agregaDefensa   (defensaTajoCabalgado, 30);           //LUCASGG        
        Shaolin->agregaDefensa   (defensaArcoVenenoso,  50);           //LUCASGG
        Shaolin->agregaDefensa   (defensaQuirurgica,     5);           //LUCASGG
        //                       
        //Aristo->agregaAtaque     (ataqueCuerpoACuerpo,  70);          //LUCASGG 
        //Aristo->agregaAtaque     (ataqueADistancia,     50);          //LUCASGG 
        //Aristo->agregaDefensa    (defensaCuerpoACuerpo, 70);          //LUCASGG 
        //Aristo->agregaDefensa    (defensaADistancia,    70);          //LUCASGG 
        //Aristo->agregaDefensa    (defensaMagica,        20);          //LUCASGG 
        //Aristo->agregaReduceDano (danoFisico,           10);          //LUCASGG 
        //Aristo->agregaReduceDano (danoMagico,            5);          //LUCASGG 
        TecMed->agregaAtaque       (ataqueQuirurgico,     20);          //LUCASGG
        TecMed->agregaDefensa      (defensaTajoCabalgado, 30);          //LUCASGG        
        TecMed->agregaDefensa      (defensaArcoVenenoso,  70);          //LUCASGG
        TecMed->agregaDefensa      (defensaQuirurgica,     5);          //LUCASGG
        TecMed->agregaDefensa      (defensaCuerpoACuerpo, 70);          //LUCASGG
        TecMed->agregaDefensa      (defensaADistancia,    70);          //LUCASGG
        TecMed->agregaDefensa      (defensaMagica,        20);          //LUCASGG
        TecMed->agregaReduceDano   (danoFisico,           10);          //LUCASGG
        TecMed->agregaReduceDano   (danoMagico,            5);          //LUCASGG
        //                       
        //Franco->agregaAtaque     (ataqueCuerpoACuerpo,  50);                    //Manuel
        Franco ->agregaAtaque     (ataqueADistancia,     50);                     //Manuel
        Franco->agregaAtaque     (ataqueMagico,         0);                      //Manuel
        Franco->agregaDefensa    (defensaCuerpoACuerpo, 30);                      //Manuel
        Franco->agregaDefensa    (defensaADistancia,    55);                      //Manuel
        Franco->agregaDefensa    (defensaMagica,        40);                      //Manuel
        Franco->agregaReduceDano (danoFisico,            10);                      //Manuel
        Franco->agregaReduceDano (danoMagico,           5);                      //Manuel
        Franco->agregaDefensa    (defensaTajoCabalgado, 30);           //LUCASGG        
        Franco->agregaDefensa    (defensaArcoVenenoso,  50);           //LUCASGG
        Franco->agregaDefensa    (defensaQuirurgica,     5);           //LUCASGG
        //                       
        //Hunter->agregaAtaque     (ataqueCuerpoACuerpo,  50);
        //Hunter->agregaAtaque     (ataqueADistancia,     50);  No se usa
        // Hunter->agregaAtaque     (ataqueMagico,         70);        
        //Hunter->agregaDefensa    (defensaCuerpoACuerpo, 40);
        //Hunter->agregaDefensa    (defensaADistancia,    40);
        //Hunter->agregaDefensa    (defensaMagica,        30);
        //Hunter->agregaReduceDano (danoFisico,            0);
        //Hunter->agregaReduceDano (danoMagico,           15);
        //Hunter->agregaDefensa    (defensaTajoCabalgado, 30);           //LUCASGG        
        //Hunter->agregaDefensa    (defensaArcoVenenoso,  40);           //LUCASGG
        //Hunter->agregaDefensa    (defensaQuirurgica,     5);           //LUCASGG
        //
        //Makhan->agregaAtaque     (ataqueCuerpoACuerpo,  85);           //lucasgm
        //Makhan->agregaAtaque     (ataqueADistancia,     40);           //lucasgm
        //Makhan->agregaDefensa    (defensaCuerpoACuerpo, 55);           //lucasgm
        //Makhan->agregaDefensa    (defensaADistancia,    55);           //lucasgm
        //Makhan->agregaDefensa    (defensaMagica,        20);           //lucasgm
        //Makhan->agregaReduceDano (danoFisico,           10);           //lucasgm
        //Makhan->agregaReduceDano (danoMagico,            5);           //lucasgm
        //Makhan->agregaDefensa    (defensaTajoCabalgado, 30);           //lucasgm        
        //Makhan->agregaDefensa    (defensaArcoVenenoso,  50);           //lucasgm
        //Makhan->agregaDefensa    (defensaQuirurgica,    5);            //lucasgm
        //                       
        /*Thief ->agregaAtaque     (ataqueCuerpoACuerpo,  60);
        Thief ->agregaAtaque     (ataqueADistancia,     70);        
        Thief ->agregaDefensa    (defensaCuerpoACuerpo, 50);
        Thief ->agregaDefensa    (defensaADistancia,    50);
        Thief ->agregaDefensa    (defensaMagica,        50);
        Thief ->agregaReduceDano (danoFisico,            7);
        Thief ->agregaReduceDano (danoMagico,            7);*/
        //                      
        PilotoMecha->agregaAtaque (ataqueCuerpoACuerpo,  35);
        PilotoMecha->agregaAtaque (ataqueADistancia,     65);
        PilotoMecha->agregaAtaque (ataqueMagico,         60);
        PilotoMecha->agregaDefensa(defensaCuerpoACuerpo, 20);
        PilotoMecha->agregaDefensa(defensaADistancia,    30);
        PilotoMecha->agregaDefensa(defensaMagica,        30);
        PilotoMecha->agregaReduceDano (danoFisico,       5);
        PilotoMecha->agregaReduceDano (danoMagico,       10);
        PilotoMecha->agregaDefensa(defensaTajoCabalgado, 30);           //LUCASGG        
        PilotoMecha->agregaDefensa(defensaArcoVenenoso,  50);           //LUCASGG
        PilotoMecha->agregaDefensa(defensaQuirurgica,     5);           //LUCASGG
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaSistemaAtaque () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Séptima sección - Los grados de efectividad - Segunda parte

        En esta sección se configuran los grados de efectividad de los ataques del juego. En la 
        primera parte se establecen las variables destinadas a almacenar las instancias que definen 
        los grados de efectividad. En esta parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre de los tipos correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los tipos:

             a) Descripción: Asignado en la creación de la instancia en una cadena de caracteres. 
                Deben ser cortos.

             b) Intervalo de puntos: Es el intervalo de puntos al que se aplica la efectividad. 
                Se establece con un valor mínimo y uno máximo. En el primer intervalo el valor 
                mínimo es el número entero mínimo y en el último intervalo, el valor máximo es 
                el número entero máximo.

             c) Efectividad: Es un porcentaje que se aplica a una puntuación para modificar su 
                valor cuando dicha puntuación esta en el intervalo definido por el intervalo
                correspondiente. 
            
        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias por listas similares, obtenidas a 
        partir de la lista de grados de efectividad diseñados para el juego. 

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        grados de efectividad en el diseño del juego.

        *******************************************************************************************/
        //
        GradoEfectividad * fallo   = new GradoEfectividad {L"Fallo"};
        GradoEfectividad * roce    = new GradoEfectividad {L"Roce"};
        GradoEfectividad * impacto = new GradoEfectividad {L"Impacto"};
        GradoEfectividad * critico = new GradoEfectividad {L"Impacto crítico"};
        //
        fallo  ->estableceRango (INT_MIN,       9,    0);
        roce   ->estableceRango (     10,      49,   50);
        impacto->estableceRango (     50,      89,  100);
        critico->estableceRango (     90, INT_MAX,  150);
        //
        agregaEfectividad (fallo);
        agregaEfectividad (roce);
        agregaEfectividad (impacto);
        agregaEfectividad (critico);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::configuraJuego () {
        agregaMusica (new ActorMusica {this});
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Undécima sección - Configuración miscelánea del juego.

        En esta sección se establecen varios valores de configuración que no tienen sitio en otras 
        secciones.

        Configuración
        -------------

        La configuración tiene los siguientes aspectos:

                 a) Se establece el consumo de puntos de acción de los desplazamientos de los 
                    personajes. Para ello se indica el número píxeles de desplazamiento que 
                    originan el consumo de un punto de acción.

                 b) Se establece la posición inicial de las fichas de los personajes en el tablero 
                    de juego.
         
                 c) Se establecen los archivos de sonido, que se escuchan en momentos concretos del
                    juego. Se deben especificar los sonidos:

                      - Sonido de una pulsación con el ratón (clic)
                      - Sonido de desplazamiento de una ficha.

                 d) Se establece la música que se escucha con el juego. En un fragmento musical que 
                    se repite en bucle.

                 e) Se almacenan los nombres de los alumnos diseñadores del juego. Estos nombres
                    aparecen en la ayuda del juego.

                 f) Se almacena el curso académico durante el que los alumnos han elaborado el 
                    diseño del juego.

        Sonidos y música
        ----------------

        Los sonidos se cargan de archivos de tipo 'wav', 'ogg' o 'flac', pero no 'mp3'. El tiempo de
        emisión del sonido debe ser corto (escasos segundos).
        
        Los sonidos y la música se han tomado de:
                https://opengameart.org/content/metal-click
                https://opengameart.org/content/walking-on-snow-sound
        La licencia aparece en esas mismas páginas.

        La música que suena en momentos determinados del juego también se carga de un archivo. Sin 
        embargo, no es necesario que sea corta, por que se atenúa a los pocos segundos.

        La música se han tomado de:
                https://opengameart.org/content/unused-music
        La licencia aparece en esa misma página.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de personajes por listas similares, obtenidas a partir del 
        diseño del juego.

        *******************************************************************************************/
        //
        modo ()->configuraDesplaza (RejillaTablero::distanciaCeldas);
        //
        //Miner ->ponSitioFicha (Coord {23, 15});       //LUCASGG
        Amazona->ponSitioFicha(Coord{ 23, 15 });        //LUCASGG
        Samurai->ponSitioFicha (Coord {17, 15});        //Manuel
        //Patrek->ponSitioFicha (Coord {29, 15});
        //Alquimis->ponSitioFicha(Coord{ 29, 15 });       //lucasgm
        //Pirate->ponSitioFicha (Coord {35, 15});
        Shaolin->ponSitioFicha(Coord {35, 15});
        //Aristo->ponSitioFicha (Coord {23, 35});       //LUCASGG
        TecMed->ponSitioFicha(Coord{ 23, 35 });         //LUCASGG
        Franco->ponSitioFicha (Coord {17, 35});         //Manuel
        //Hunter->ponSitioFicha (Coord {29, 35});
        //Makhan->ponSitioFicha(Coord{ 29, 35 });         //lucasgm
        //Thief ->ponSitioFicha (Coord {35, 35});
        PilotoMecha->ponSitioFicha (Coord {35, 35});
        //
        tablero ()->asignaSonidoEstablece (carpeta_sonidos_juego + "Metal Click.wav", 100);
        tablero ()->asignaSonidoDesplaza  (carpeta_sonidos_juego + "SnowWalk.ogg",    100);
        musica  ()->asignaMusica          (carpeta_sonidos_juego + "Track_1.ogg",     0);
        //
        agregaNombreAlumno (L"Joan Mayor Heredia");
        agregaNombreAlumno (L"Celia Serrano Chaparro");
        agregaNombreAlumno (L"Sasha López Coto");
        agregaNombreAlumno (L"Manuel Alonso Plaza");
        agregaNombreAlumno (L"Lucas García Madrigal");
        agregaNombreAlumno (L"Lucas García Giobellina");
        indicaCursoAcademico (L"2024 - 2025");
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::termina () {
        //
        JuegoMesaBase::termina ();
        //
        //Aristo   = nullptr;                       //LUCASGG
        TecMed   = nullptr;                         //LUCASGG
        Franco = nullptr;                           //Manuel
        //Hunter   = nullptr;
        //Alquimis = nullptr;                         //lucasgm
        //Thief    = nullptr;
        PilotoMecha = nullptr;
        //Miner    = nullptr;
        Amazona = nullptr;                          //LUCASGG
        Samurai = nullptr;                          //Manuel
        //Patrek   = nullptr;
        //Makhan = nullptr;                           //lucasgm
        //Pirate   = nullptr;
        Shaolin  = nullptr;
        //
        ataqueEspadaNormal   = nullptr;
        ataqueArco           = nullptr;
        ataqueEspadaPoderoso = nullptr;
        defensaFerrea        = nullptr;
        curacionSimple       = nullptr;
        curacionGrupo        = nullptr;
        proyectilMagico      = nullptr;
        bolaFuego            = nullptr;
        
        palmaChi             = nullptr;
        pocionVenenosa       = nullptr;
        rezo                 = nullptr;
        microGranada         = nullptr;
        misil                = nullptr;
        lanzaLaser           = nullptr;
        barricadaRetractil   = nullptr;

        drogaDeCombate       = nullptr;             //LUCASGG
        campoDeCuracion      = nullptr;             //LUCASGG
        ataqueBisturi        = nullptr;             //LUCASGG
        ataqueArcoConVeneno  = nullptr;             //LUCASGG
        ataqueCabalgado      = nullptr;             //LUCASGG
        defensaConEscudo     = nullptr;             //LUCASGG 

        //polvoraNegra         = nullptr;             //lucasgm
        //fuegoLiquido         = nullptr;             //lucasgm
        //bombasAceite         = nullptr;             //lucasgm
        //ojosLaser            = nullptr;             //lucasgm
        //mordiscoSierra       = nullptr;             //lucasgm
        //corteZigzag          = nullptr;             //lucasgm

        cortePreciso = nullptr;                     //Manuel
        arremetida = nullptr;                       //Manuel
        voluntadFerrea = nullptr;                   //Manuel
        headShot = nullptr;                         //Manuel
        balaPrecisa = nullptr;                      //Manuel
        balaFragmentada = nullptr;                  //Manuel

        //
        ataqueCuerpoACuerpo  = nullptr;
        ataqueADistancia     = nullptr;
        ataqueMagico         = nullptr;
        defensaCuerpoACuerpo = nullptr;
        defensaADistancia    = nullptr;
        defensaMagica        = nullptr;
        danoFisico           = nullptr;
        danoMagico           = nullptr;

        ataqueQuirurgico     = nullptr;             //LUCASGG
        ataqueArcoVenenoso   = nullptr;             //LUCASGG
        ataqueTajoCabalgado  = nullptr;             //LUCASGG
        defensaQuirurgica    = nullptr;             //LUCASGG
        defensaArcoVenenoso  = nullptr;             //LUCASGG
        defensaTajoCabalgado = nullptr;             //LUCASGG
    }


}