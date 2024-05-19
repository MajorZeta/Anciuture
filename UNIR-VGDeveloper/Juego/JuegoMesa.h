// proyecto: Grupal/Juego
// arhivo:   JuegoMesa.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace juego {


    class JuegoMesa : public JuegoMesaBase {
    public:

        JuegoMesa ();

    private:

        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Segunda parte

        En esta sección se configuran los personajes del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen a los personajes. 

        El nombre de cada variable es similar al nombre del personaje correspondiente. Las variables 
        son de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de personajes diseñados para el juego.

        *******************************************************************************************/
        //ActorPersonaje * Aristo {};       //LUCASGG
        ActorPersonaje * TecMed{};          //LUCASGG
        ActorPersonaje * Franco{};          //Manuel
        //ActorPersonaje * Hunter {};
        ActorPersonaje * Makhan{};          //lucasgm
        ActorPersonaje * Thief {};
        //ActorPersonaje * Miner {};        //LUCASGG
        ActorPersonaje * Amazona{};          //LUCASGG
        ActorPersonaje * Samurai{};         //Manuel
        //ActorPersonaje * Patrek {};
        ActorPersonaje * Alquimis {};       //lucasgm
        ActorPersonaje * Pirate {};
        ActorPersonaje * Shaolin {};
        ActorPersonaje * PilotoMecha {};
        /*******************************************************************************************
        /******************************************************************************************/
 

        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Quinta sección - Las habilidades - Primera parte

        En esta sección se configuran las habilidades compartidas por los personajes del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen a las habilidades. 

        El nombre de cada variable es similar al de la habilidad correspondiente. Las variables son 
        de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de habilidades diseñadas para el juego.

        *******************************************************************************************/
        Habilidad * ataqueEspadaNormal {}; 
        Habilidad * ataqueArco {};
        Habilidad * ataqueEspadaPoderoso {};
        Habilidad * defensaFerrea {};
        Habilidad * curacionSimple {};
        Habilidad * curacionGrupo {};
        Habilidad * proyectilMagico {};
        Habilidad * bolaFuego {};
        Habilidad * palmaChi {};
        Habilidad * pocionVenenosa {};
        Habilidad * rezo {};
        Habilidad * microGranada {};
        Habilidad * misil {};
        Habilidad * lanzaLaser {};
        Habilidad * barricadaRetractil{};

        Habilidad * campoDeCuracion{};             //LUCASGG
        Habilidad * drogaDeCombate{};              //LUCASGG
        Habilidad * ataqueBisturi{};               //LUCASGG
        Habilidad * ataqueArcoConVeneno{};         //LUCASGG
        Habilidad * ataqueCabalgado{};             //LUCASGG
        Habilidad * defensaConEscudo{};            //LUCASGG

        Habilidad * polvoraNegra{};                 //lucasgm
        Habilidad * fuegoLiquido{};                 //lucasgm
        Habilidad * bombasAceite{};                 //lucasgm
        Habilidad * ojosLaser{};                    //lucasgm
        Habilidad * mordiscoSierra{};               //lucasgm
        Habilidad * corteZigzag{};                  //lucasgm

        Habilidad * cortePreciso{};                 //Manuel
        Habilidad * arremetida{};                 //Manuel
        Habilidad * voluntadFerrea{};                 //Manuel
        Habilidad * headShot{};                    //Manuel
        Habilidad * balaPrecisa{};               //Manuel
        Habilidad * balaFragmentada{};                  //Manuel
        /*******************************************************************************************
        /******************************************************************************************/


        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Sexta sección - Los tipos de ataque, defensa y daño (estadísticas) - Primera parte

        En esta sección se configuran los tipos de ataque, defensa y daño del juego, que son usados
        por los personajes y las habilidades del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen los tipos de ataque, defensa y daño. 

        El nombre de cada variable identifica el tipo correspondiente. Las variables son de 
        tipo puntero. El nombre de la clase (por ejemplo 'TipoAtaque' para los ataques) 
        establece si es un tipo de ataque, de defensa o de daño.

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de tipos de ataque, defensa y daño diseñados para el juego.

        *******************************************************************************************/
        TipoAtaque *  ataqueCuerpoACuerpo {};
        TipoAtaque *  ataqueADistancia {};
        TipoAtaque *  ataqueMagico {};
        TipoDefensa * defensaCuerpoACuerpo {};
        TipoDefensa * defensaADistancia {};
        TipoDefensa * defensaMagica {};
        TipoDano *    danoFisico {};
        TipoDano *    danoMagico {};

        TipoAtaque* ataqueQuirurgico{};              //LUCASGG
        TipoAtaque* ataqueArcoVenenoso{};            //LUCASGG
        TipoAtaque* ataqueTajoCabalgado{};           //LUCASGG
        TipoDefensa* defensaQuirurgica{};            //LUCASGG
        TipoDefensa* defensaArcoVenenoso{};          //LUCASGG
        TipoDefensa* defensaTajoCabalgado{};         //LUCASGG

        /*******************************************************************************************
        /******************************************************************************************/


        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Séptima sección - Los grados de efectividad - Primera parte

        En esta sección se configuran los grados de efectividad de los ataques del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen los grados de efectividad de los ataques. 

        Cada variable tiene un nombre similar al nombre del grados de efectividad correspondiente. 
        Las variables son de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de grados de efectividad diseñados para el juego.

        *******************************************************************************************/
        GradoEfectividad * fallo {};
        GradoEfectividad * roce {};
        GradoEfectividad * impacto {};
        GradoEfectividad * critico {};
        /*******************************************************************************************
        /******************************************************************************************/

    private:

        static string carpeta_activos_juego;
        static string carpeta_retratos_juego;
        static string carpeta_habilids_juego;
        static string carpeta_sonidos_juego;


        const std::wstring tituloVentana () const override;

        void preparaTablero () override;
        void preparaPersonajes () override;
        void preparaHabilidades () override;
        void preparaTiposEstadisticas () override;
        void agregaHabilidadesPersonajes () override;
        void agregaEstadisticasHabilidades () override;
        void agregaEstadisticasPersonajes () override;
        void preparaSistemaAtaque () override;
        void configuraJuego () override;
        void termina () override;

    };


}


