#include <windows.h>
#include <GL/glut.h>

//Aquí dibuja dos objetos
void MisObjetos (void) {
     glColor4ub(255, 0, 0, 0);//Rojo
     glutWireSphere(30, 10, 10); //Se ve una telaraña
     glColor4ub(0, 255, 0, 0);   //Verde
     glutWireCube (100.0);       //Se ve un cuadrado
}

void display(void) {
   glClear(GL_COLOR_BUFFER_BIT); //Limpia la ventana

   MisObjetos(); //Llama al método que dibuja los dos objetos

   glutSwapBuffers();
}

void init(void)  {
  glClearColor (0, 0, 0, 0); //Limpia la ventana con el color negro en el fondo
}

void reshape(int w, int h) {
   //Define la dimensión del cubo donde vamos a dibujar todos los objetos
   glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0); //Izq, Der, Abajo, Arriba, Cerca, lejos
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);   //Inicializa la librería GLUT y negocia una sesión
                            //con el sistema de ventanas
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Activa el modo inicial de despliegue
                            //GLUT_DOUBLE doble buffer  GLUT_RGB = GLUT_RGBA
   glutInitWindowSize (600, 600); //Tamaño de la ventana 500 x 500
   glutInitWindowPosition (100, 100); //Posición de la ventana en la pantalla
   glutCreateWindow ("Cubo y esfera"); //Crea la ventana y le pone la etiqueta

   init ();  //Ejecuta el método "init"

   glutDisplayFunc(display);  //Ejecuta el método "display"
   glutReshapeFunc(reshape);  //Ejecuta el método "reshape"
   glutMainLoop();            //Repite el main indefinidamente (¡Animación!)
   return 0;   /* ANSI C requires main to return int. */
}
//Ejercicio 01_ 09-Agosto-2021
// Cuadrado con una telearaña
