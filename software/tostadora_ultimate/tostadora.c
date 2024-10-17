#include "system.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>  // Para usar la funci�n sleep()
#include "sys/alt_irq.h"


// Definir pulsadores
#define KEY3 0x08  // Start 1000
#define KEY2 0x04  // Stop 0100
#define KEY1 0x02  // Pause/Continue 0010


//#define MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE 0x10001800
volatile int filas_mtl = 29;               // N�mero de filas de texto de la MTL
volatile int columnas_mtl = 70;               // N�mero de columnas de texto de la MTL
#define caracter_espacio  ' '               // Caracter de espacio para limpiar en la MTL

//ponemos estos valores iniciales xq la TOSTADORA EMPIEZA APAGADA
bool start = false;
bool stop = true;
bool tostando = false;
bool continuar = false;
/* Prototipos de funciones */
void LCD_cursor(int, int);
void LCD_text(char *);
void LCD_cursor_off(void);
void MTL_text(int, int, char *);
void MTL_box(int, int, int, int, short);
void switches_ISR();
void pushbutton_ISR();
void temporizador_ISR();
void tiempo_display();
void limpiar_texto_mtl();
void mostrar_instrucciones();
void dibujar_tostadora();

volatile int contador_tiempo=0;// Contador de segundos para el temporizador

volatile int press = 0; //para subrutina botones
volatile int nivelTostado = 0; //para subrutina switches
volatile int nuevo_nivelTostado = 0;
int  SW_value;
volatile int tiempo_tostado =0 ;  // Variable para almacenar el tiempo de tostado
bool tostadora_activa = false;  // Indicar si la tostadora est� activa o no
volatile int nuevo_contador = 0;
//DECLARACION SENSORES
volatile int sensorError = 0;
volatile int sensorPan = 0;
volatile int sensorQuemado = 0;
volatile int sensorSobrecalentamiento = 0;

int main() {

    // Declarar punteros a registros de I/O como volatile
	volatile int * red_LED_ptr = (int *) RED_LEDS_BASE; 	// dirección LED rojos
    volatile int * SW_switch_ptr = (int *) SWITCHES_BASE; 	// dirección SW
    volatile int *KEY_ptr = (int *)PUSHBUTTONS_BASE;// Direcci�n de pulsadores KEY
    volatile int * interval_timer_ptr = (int *) TIMER_BASE; // direccion temporizador
    volatile int * HEX3_HEX0 = (int *) HEX3_HEX0_BASE; // direccion temporizador

    volatile char* text_buffer = (char*)  MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE; // puntero para acceder a la memoria del buffer de texto MTL

    // Mensaje a visualizar en la VGA y en el LCD
    char text_top_row[40] = "Tostadora CHS   \0";
    char text_bottom_row[40] = "Martin Y Jandro                \0";




    // Escribe el texto en el LCD
    LCD_cursor(0, 0); // Fija el cursor del LCD en la fila superior
    LCD_text(text_top_row);
    LCD_cursor(0, 1); // Fija el cursor del LCD en la fila inferior
    LCD_text(text_bottom_row);
    LCD_cursor_off(); // Apaga el cursor del LCD

    *(SW_switch_ptr + 2) = 0xFFFFF; /* Mascara de los pulsadores (bit 0 es reset) */
    *(SW_switch_ptr + 3) = 0;
    SW_value = *(SW_switch_ptr);
    alt_irq_register(SWITCHES_IRQ, NULL, switches_ISR); //INTERRUPCION SWITCHES

    *(KEY_ptr + 2) = 0xE; /* Mascara de los pulsadores (bit 0 es reset) */
    *(KEY_ptr + 3) = 0;
    alt_irq_register(PUSHBUTTONS_IRQ, NULL, pushbutton_ISR); // INTERUPCION BOTONES

    int contador = 50000000;
    *(interval_timer_ptr + 0x2) = (contador & 0xFFFF); //parte baja temporizador
    *(interval_timer_ptr + 0x3) = (contador >> 16) & 0xFFFF; //parte alta temporizador
    *(interval_timer_ptr + 1) = 0x7; //iniciar el temporizador
    alt_irq_register(TIMER_IRQ, NULL, temporizador_ISR); // INTERRUPCION TEMPORIZADOR

    *(red_LED_ptr)&=~0x1;
    *(red_LED_ptr)&=~0x2;
    MTL_box(0, 0, 50 * 8 - 1, 30 * 8 - 1, 0x0000);//limpiar de negro la pantalla pixeles antes de pintar la tostadora

    mostrar_instrucciones();

    while (1) {

			if (press == KEY3  ) {
				press=0;
				MTL_box(0, 0, 50 * 8 - 1, 30 * 8 - 1, 0x0000);//limpiar de negro la pantalla pixeles antes de pintar la tostadora
				dibujar_tostadora();
				if (sensorPan && !sensorError && nivelTostado > 0 && !sensorSobrecalentamiento) {


							// Iniciar tostado
								start = true;
								stop = false;
								tostando = true;
								nuevo_contador= tiempo_tostado;
								dibujar_tostadora();

								contador_tiempo = tiempo_tostado;
								char text_top_row[40] = "Tostadora CHS   \0";
								char text_bottom_row[40] = "Tostando               \0";
								LCD_cursor(0, 0); // Fija el cursor del LCD en la fila superior
								LCD_text(text_top_row);
								LCD_cursor(0, 1); // Fija el cursor del LCD en la fila inferior
								LCD_text(text_bottom_row);
								LCD_cursor_off(); // Apaga el cursor del LCD

								// Encender LED rojo 0, Resistencia calefactora (indicando que el tostado ha empezado)
								*(red_LED_ptr) |= 0x1;
								//AQUI APAGAREMOS EL LED DE EXPULSAR EL PAN// Encender LED rojo 1
								*(red_LED_ptr) &=~0x2;
				}

				} else if (press == KEY2) {
								// Detener tostado
								start = false;
								stop = true;
								tostando = false;
								dibujar_tostadora();
								contador_tiempo = 0;
								press=0;
								char text_top_row[40] = "Tostadora CHS   \0";
								  char text_bottom_row[40] = "Parada                \0";
								  LCD_cursor(0, 0); // Fija el cursor del LCD en la fila superior
								  LCD_text(text_top_row);
								  LCD_cursor(0, 1); // Fija el cursor del LCD en la fila inferior
								  LCD_text(text_bottom_row);
								  LCD_cursor_off(); // Apaga el cursor del LCD

								  // Apagar LED rojo 0, Resistencia calefactora (indicando que el tostado ha acabado)
								  *(red_LED_ptr) &=~0x1;
								  // Encender LED rojo 1, Motor Expulsion Pan (indicando que el tostado ha acabado)
								  *(red_LED_ptr) |=0x2;
							} else if (press == KEY1) {
					 			// Pausar/Continuar tostado
								if (tostando) { // Si tostando = true, se hace el if. BUCLE PAUSAR
										start = true;
										stop = false;
										tostando = false;
										continuar = false;
										dibujar_tostadora();
										press=0;
										char text_top_row[40] = "Tostadora CHS   \0";
										char text_bottom_row[40] = "Pausa            \0";
										LCD_cursor(0, 0); // Fija el cursor del LCD en la fila superior
										LCD_text(text_top_row);
										LCD_cursor(0, 1); // Fija el cursor del LCD en la fila inferior
										LCD_text(text_bottom_row);
										LCD_cursor_off(); // Apaga el cursor del LCD
										// Apagar LED rojo 0, Resistencia calefactora (indicando que el tostado ha acabado)
										*(red_LED_ptr) &=~0x1;
									} else {// Si tostando = false, se hace el else. BUCLE CONTINUE
										start = true;
										stop = false;
										tostando = true;
										continuar = true;
										dibujar_tostadora();
										press=0;
										char text_top_row[40] = "Tostadora CHS   \0";
										char text_bottom_row[40] = "Tostando               \0";
										LCD_cursor(0, 0); // Fija el cursor del LCD en la fila superior
										LCD_text(text_top_row);
										LCD_cursor(0, 1); // Fija el cursor del LCD en la fila inferior
										LCD_text(text_bottom_row);
										LCD_cursor_off(); // Apaga el cursor del LCD
										// Apagar LED rojo 0, Resistencia calefactora (indicando que el tostado ha acabado)
										*(red_LED_ptr) |= 0x1;
								}
							}


			if (tostando && contador_tiempo > 0) {
			    if (contador_tiempo < nuevo_contador) { 
			        nuevo_contador = contador_tiempo;    // Actualiza el nuevo contador al valor actual
			        printf("contador actualizado: %d\n", contador_tiempo);  

			        dibujar_tostadora();  // Llama a la funcion de dibujo cuando el tiempo cambia

			    }
			}



			// Condiciones para detener el tostado en cualquier momento
			if(start){
			    if (sensorPan == 0 || sensorError || sensorQuemado || sensorSobrecalentamiento ) {


			    	start = false;
			        stop = true;
			        tostando = false;
			        dibujar_tostadora();
			        // Apagar LED rojo 0, Resistencia calefactora (indicando que el tostado ha acabado)
			        *(red_LED_ptr) &=~0x1;
			        //AQUI ENCENDEREMOS EL LED DE EXPULSAR EL PAN// Encender LED rojo 1
					  *(red_LED_ptr) |=0x2;
			        // Mensaje de error o sobrecalentamiento en el LCD
			        if (sensorQuemado) {

			        	char text_top_row[40] = "Tostadora CHS   \0";
			            char text_bottom_row[40] = "Pan quemado\0";
			            LCD_cursor(0, 0);
			            LCD_text(text_top_row);
			            LCD_cursor(0, 1);
			            LCD_text(text_bottom_row);
			        } else if (sensorSobrecalentamiento) {
			        	char text_top_row[40] = "Tostadora CHS   \0";
			            char text_bottom_row[40] = "Sobrecalentada                \0";
			            LCD_cursor(0, 0);
			            LCD_text(text_top_row);
			            LCD_cursor(0, 1);
			            LCD_text(text_bottom_row);
			        } else if (sensorError) {
			        	char text_top_row[40] = "Tostadora CHS   \0";
			            char text_bottom_row[40] = "Error                \0";
			            LCD_cursor(0, 0);
			            LCD_text(text_top_row);
			            LCD_cursor(0, 1);
			            LCD_text(text_bottom_row);
			        } else if (sensorPan == 0) {
			        	char text_top_row[40] = "Tostadora CHS   \0";
			            char text_bottom_row[40] = "Sin pan                \0";
			            LCD_cursor(0, 0);
			            LCD_text(text_top_row);
			            LCD_cursor(0, 1);
			            LCD_text(text_bottom_row);
			        }
			    }else if (contador_tiempo == 0 && tiempo_tostado!=-1 ){//cuando se acabe el tiempo
			    	start = false;
			    	stop = true;
			    	tostando=false;
			    	dibujar_tostadora();
			    	char text_top_row[40] = "Tostadora CHS   \0";
					char text_bottom_row[40] = "Finalizada                \0";
					LCD_cursor(0, 0);
					LCD_text(text_top_row);
					LCD_cursor(0, 1);
					LCD_text(text_bottom_row);
			    }
			}

			// Actualizar el display con el tiempo
			tiempo_display(contador_tiempo);

			// L�gica de selecci�n del nivel de tostado
			if(nuevo_nivelTostado!=nivelTostado){
				     if (nivelTostado == 0) {
				         // Si el valor es 0, la tostadora no funciona
				         tostadora_activa = false;
				         tiempo_tostado = 0;
				        // printf("La tostadora est� apagada.\n");
				     } else if (nivelTostado ==6 || nivelTostado == 7) {
				         // Si el valor es 6 o 7, la tostadora funciona continuamente
				         tostadora_activa = true;
				         tiempo_tostado = -1;  // Uso de -1 para indicar funcionamiento continuo
				         printf("La tostadora est� funcionando de manera continua.\n");
				     } else {
				         // Para valores entre 1 y 5, se asignan tiempos
				         tostadora_activa = true;
				         switch (nivelTostado) {
				             case 1:
				                 tiempo_tostado = 12;
				                 nuevo_contador=tiempo_tostado;
				                 printf("%d\n", nuevo_contador);
				                 printf("Tostado a 12 segundos.\n");
				                 break;
				             case 2:
				                 tiempo_tostado = 25;
				                 nuevo_contador=tiempo_tostado;
				                 printf("Tostado a 25 segundos.\n");

				                 break;
				             case 3:
				                 tiempo_tostado = 40;
				                 nuevo_contador=tiempo_tostado;
				                 printf("Tostado a 40 segundos.\n");
				                 break;
				             case 4:
				                 tiempo_tostado = 60;
				                 nuevo_contador=tiempo_tostado;
				                 printf("Tostado a 60 segundos.\n");
				                 break;
				             case 5:
				                 tiempo_tostado = 70;
				                 nuevo_contador=tiempo_tostado;
				                 printf("Tostado a 70 segundos.\n");
				                 break;

				             default:
				                 tostadora_activa = false;  
				                 printf("Valor no v�lido de nivel de tostado.\n");
				                 break;
				         }
				     }
				     nuevo_nivelTostado=nivelTostado;
				     nuevo_contador = tiempo_tostado+1;

    		}
    	}

    }

/****************************************************************************************
 * Subrutina para dibujar tostadora
****************************************************************************************/
void dibujar_tostadora() {
    // Limpiar el texto de la mtl antes de mostrar instrucciones
    limpiar_texto_mtl();

    short color_tostadora = 0xA9A9A9;  // Color gris para el cuerpo
    short color_pan = 0xFFFF09;         // Color marr�n claro para la abertura
    short color_blanco = 0xFFFF; // Color blanco para el bot�n
    short color_amarillo = 0xFFFF00; // Color amarillo para el nivel
    short color_verde = 0x07E0; // start
    short color_rojo = 0xF800; // stop
    short color_azul = 0x001F; // Continue
    short color_naranja = 0xFD20; // Pause
    short color_grisOscuro = 0x6666;
    short color_Negro = 0x000000;
    short color_marron_oscuro =0x7B3F00;


    // Cuerpo de la tostadora (rect�ngulo)
    MTL_box(90, 80, 310, 170, color_tostadora);  // Cuerpo de la tostadora

    //cambiar a negro el pan cuando este activo el sensor quemado
    if(sensorQuemado ){

    MTL_box(135, 30, 265, 80, color_grisOscuro); // Pan
    } else {
    	MTL_box(135, 30, 265, 80, color_pan);  // Pan
    }
    if(sensorPan ){

    	MTL_box(135, 30, 265, 80, color_pan);  // Pan
       } else {
       	MTL_box(135, 30, 265, 80, color_Negro);  // No Pan
       }
    //boton start
    if(start == true ){

    	MTL_box(160, 106 , 174 , 120 , color_verde);
    } else {
    	MTL_box(160, 106 , 174 , 120 , color_blanco);
    }

    //boton stop
    if(start == false && stop == true && tostando == false){
    	MTL_box( 188, 106 , 202 ,120  , color_rojo);
    } else {
    	MTL_box( 188, 106 , 202 ,120  , color_blanco);
    }
    //boton PAUSE/ CONTINUE
    if(continuar==true && tostando == true){//continue
    	MTL_box( 216, 106 , 230 , 120 , color_azul);
    } else if(start==true && continuar==false && tostando == false){//pause
    	MTL_box( 216, 106 , 230 , 120 , color_naranja);
    }else {MTL_box( 216, 106 , 230 , 120 , color_blanco);}



    //Marco barra de carga del tiempo
       MTL_box(50, 195, 350, 196, color_blanco);
       MTL_box(50, 214, 350, 215, color_blanco);
       MTL_box(48, 197, 49, 213, color_blanco);
       MTL_box(351, 197, 352, 213, color_blanco);
    // Barra de carga del tiempo
   if (contador_tiempo > 0 && start) {
        // Calcula en cuantos cuadrados se divide la barra
        int ancho = 300 / tiempo_tostado; 

        if (contador_tiempo < 0) {
            contador_tiempo = 0; 
        } else if (contador_tiempo > tiempo_tostado) {
            contador_tiempo = tiempo_tostado; 
        }

        int i = (tiempo_tostado+1) - contador_tiempo; 
        // Dibuja el segmento de la barra que corresponde al tiempo actual.
        if (contador_tiempo > 0) { // Solo dibuja si hay tiempo restante
            MTL_box(50, 197, 50 + ancho * i, 213, color_verde); 
        }

   }
    // Nivel 1
    if (nivelTostado >= 1) {
        MTL_box(104, 145, 118, 159, color_amarillo);
    } else {
        MTL_box(104, 145, 118, 159, color_blanco);
    }

    // Nivel 2
    if (nivelTostado >= 2) {
        MTL_box(132, 145, 146, 159, color_amarillo);
    } else {
        MTL_box(132, 145, 146, 159, color_blanco);
    }

    // Nivel 3
    if (nivelTostado >= 3) {
        MTL_box(160, 145, 174, 159, color_amarillo);
    } else {
        MTL_box(160, 145, 174, 159, color_blanco);
    }

    // Nivel 4
    if (nivelTostado >= 4) {
        MTL_box(188, 145, 202, 159, color_amarillo);
    } else {
        MTL_box(188, 145, 202, 159, color_blanco);
    }

    // Nivel 5
    if (nivelTostado >= 5) {
        MTL_box(216, 145, 230, 159, color_amarillo);
    } else {
        MTL_box(216, 145, 230, 159, color_blanco);
    }

    // Nivel 6
    if (nivelTostado >= 6) {
        MTL_box(244, 145, 258, 159, color_amarillo);
    } else {
        MTL_box(244, 145, 258, 159, color_blanco);
    }

    // Nivel 7
    if (nivelTostado >= 7) {
        MTL_box(272, 145, 286, 159, color_amarillo);
    } else {
        MTL_box(272, 145, 286, 159, color_blanco);
    }

    //con los demas sensores de error, una exclamacion a cada lado de la tostadora
    if (sensorError || sensorSobrecalentamiento || sensorQuemado ) {
            MTL_box(30, 35, 60, 50, color_rojo);
            MTL_box(30, 58, 60, 170, color_rojo);
            MTL_box(340, 35, 370, 147, color_rojo);
            MTL_box(340, 155, 370, 170, color_rojo);
        }else{
        	MTL_box(15, 35, 75, 50, color_Negro);
        	MTL_box(15, 58, 75, 170, color_Negro);
        	MTL_box(325, 35, 385, 147, color_Negro);
        	MTL_box(325, 155, 385, 170, color_Negro);
        }

}


/****************************************************************************************
 * Subrutina para para limpiar el buffer de texto MTL
****************************************************************************************/
void limpiar_texto_mtl() {
	volatile char* text_buffer = (char*)  MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE;
    for (int fila = 0; fila < filas_mtl; fila++) {
        for (int col = 0; col < columnas_mtl; col++) {
        	text_buffer[fila * columnas_mtl + col] = caracter_espacio; // Limpia con espacios
        }
    }
}


/****************************************************************************************
 * Subrutina para mostrar las instrucciones de uso en la pantalla MTL
****************************************************************************************/
void mostrar_instrucciones() {

	// Limpiar el texto de la mtl antes de mostrar instrucciones
	limpiar_texto_mtl();

	// Pinta de negro toda la mtl (pixeles)
    MTL_box(0, 0, 50 * 8 - 1, 30 * 8 - 1, 0x0000);

    // Mostrar las instrucciones en la pantalla MTL
    MTL_text(5, 1, "TOSTADORA CHS MARTIN Y JANDRO");
    MTL_text(5, 3, "INSTRUCCIONES:");
    MTL_text(5, 5, "1. Coloca el pan en la ranura.");
    MTL_text(5, 7, "2. Ajusta el nivel de tostado.");
    MTL_text(5, 9, "3. Pulsa START (KEY3) para comenzar.");
    MTL_text(5, 11, "4. Pulsa STOP (KEY2) para detener.");
    MTL_text(5, 13, "5. Pulsa PAUSE/CONTINUE (KEY1) para ");
    MTL_text(5, 14, "   pausar/continuar.");

    MTL_text(5, 16, "Indicadores de la tostadora:");
    MTL_text(5, 18, " - LED 0: Tostando en progreso.");
    MTL_text(5, 19, " - LED 1: Pan expulsado.");

    MTL_text(5, 21, "Sensores:");
    MTL_text(5, 23, " - SW17: Sin pan: Inserte el pan.");
    MTL_text(5, 25, " - SW16: Pan quemado.");
    MTL_text(5, 27, " - SW15: Sobrecalentamiento: Deja enfriar.");
    MTL_text(5, 29, " - SW14: Error de funcionamiento.");
}


/****************************************************************************************
 * Subrutina para DISPLAY
****************************************************************************************/
void tiempo_display(int contador_tiempo) {
    // Punteros a los registros de los displays
    volatile int * HEX3_HEX0 = (int *) HEX3_HEX0_BASE;
    volatile int * HEX7_HEX4 = (int *) HEX7_HEX4_BASE;

    // Mapa de bits para los n�meros del 0 al 9 en un display de 7 segmentos
    int num_a_7seg[10] = {
        0x3F, // 0
        0x06, // 1
        0x5B, // 2
        0x4F, // 3
        0x66, // 4
        0x6D, // 5
        0x7D, // 6
        0x07, // 7
        0x7F, // 8
        0x67  // 9
    };

    if (contador_tiempo == -1) {
    	contador_tiempo = 0;
       }


    // Convertir el contador de tiempo a un formato de 6 d�gitos
    int unidades = contador_tiempo % 10;
    int decenas = (contador_tiempo / 10) % 10;
    int centenas = (contador_tiempo / 100) % 10;
    int millares = (contador_tiempo / 1000) % 10;

    // Cargar los valores a los registros de los displays de 7 segmentos
    *HEX3_HEX0 = (num_a_7seg[unidades] << 0) | (num_a_7seg[decenas] << 8) |
                 (num_a_7seg[centenas] << 16) | (num_a_7seg[millares] << 24);
}

/****************************************************************************************
 * Subrutina para TEMPORIZADOR
****************************************************************************************/
void temporizador_ISR (){


	volatile int * interval_timer_ptr = (int *) TIMER_BASE; 	// direccion temporizador
	*(interval_timer_ptr) = 0; //limpia la peticion de interrupcion
	// Incrementar el contador de tiempo cada segundo
	    if (tostando && tiempo_tostado != -1) {  // Solo contar si estamos tostando
	        contador_tiempo--;  // Incrementar el contador de tiempo (segundos)

	        printf("tiempo de Tostado: %d\n", contador_tiempo);
	    }
}


/****************************************************************************************
 * Subrutina para tiempo de tostado
****************************************************************************************/
 void switches_ISR() {

	 	volatile int * SW_switch_ptr = (int *) SWITCHES_BASE; 	// dirección SW
	 	SW_value = *(SW_switch_ptr);
	 	*(SW_switch_ptr + 3) = 0; //limpia la peticion de interrupcion

	 	nivelTostado = (SW_value) & 0x7;

	 	sensorPan = (SW_value >> 17) & 0x1;
	 	sensorError = (SW_value >> 14) & 0x1;
	 	sensorSobrecalentamiento = (SW_value >> 15) & 0x1;
	 	sensorQuemado = (SW_value >> 16) & 0x1;

	    printf("Nivel de Tostado: %d\n", nivelTostado);
	    printf("sensorError: %d\n", sensorError);
	    printf("sensorSobrecalentamiento: %d\n", sensorSobrecalentamiento);
	    printf("sensorQuemado: %d\n", sensorQuemado);
	    printf("sensorPan: %d\n", sensorPan);

 }


/****************************************************************************************
 * Subrutina para atart, stop, pause
****************************************************************************************/

void pushbutton_ISR() {
	 volatile int *KEY_ptr = (int *)PUSHBUTTONS_BASE;// Direcci�n de pulsadores KEY
	  press = *(KEY_ptr + 3);
	  *(KEY_ptr + 3)=0; //limpia la peticion de interrupcion



}

/****************************************************************************************
 * Subrutina para mover el cursor del LCD
****************************************************************************************/
void LCD_cursor(int x, int y) {
    volatile char *LCD_display_ptr = (char *)CHAR_LCD_BASE;  // 16x2 character display
    char instruction = x;

    if (y != 0) instruction |= 0x40;     // Activar bit 6 para la fila inferior
    instruction |= 0x80;                 // Activar bit 7 para indicar la posici�n
    *(LCD_display_ptr) = instruction;    // Escribir en el registro de instrucciones del LCD
}

/****************************************************************************************
 * Subrutina para enviar una cadena de texto al LCD
****************************************************************************************/
void LCD_text(char *text_ptr) {
    volatile char *LCD_display_ptr = (char *)CHAR_LCD_BASE;  // 16x2 character display

    while (*(text_ptr)) {
        *(LCD_display_ptr + 1) = *(text_ptr);  // Escribir los datos en el LCD
        ++text_ptr;
    }
}

/****************************************************************************************
 * Subrutina para apagar el cursor del LCD
****************************************************************************************/
void LCD_cursor_off(void) {
    volatile char *LCD_display_ptr = (char *)CHAR_LCD_BASE;  // 16x2 character display
    *(LCD_display_ptr) = 0x0C;  // Desactivar el cursor del LCD
}

/****************************************************************************************
 * Subrutina para enviar una cadena de texto a la pantalla MTL
****************************************************************************************/
void MTL_text(int x, int y, char *text_ptr) {
    int offset = (y << 6) + x;
    volatile char *character_buffer = (char *)MTL_CHAR_BUFFER_AVALON_CHAR_BUFFER_SLAVE_BASE;  // MTL character buffer

    while (*(text_ptr)) {
        *(character_buffer + offset) = *(text_ptr);  // Escribir en el buffer de caracteres
        ++text_ptr;
        ++offset;
    }
}

/****************************************************************************************
 * Dibujar un rect�ngulo en la pantalla MTL
****************************************************************************************/
void MTL_box(int x1, int y1, int x2, int y2, short pixel_color) {
    int offset, row, col;
    int SRAM_BASE_SIN_CACHE = (SRAM_BASE + 0x080000000);  // Eludir la cach� de datos
    volatile short *pixel_buffer = (short *)SRAM_BASE_SIN_CACHE;  // MTL pixel buffer

    // Se asume que las coordenadas del rect�ngulo son correctas
    for (row = y1; row <= y2; row++) {
        for (col = x1; col <= x2; col++) {
            offset = (row << 9) + col;
            *(pixel_buffer + offset) = pixel_color;  // Dibujar el p�xel
        }
    }
}
