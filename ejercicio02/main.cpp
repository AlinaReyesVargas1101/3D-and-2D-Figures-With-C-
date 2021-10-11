#include <windows.h>
#include <GL/glut.h>

GLint spinX, spinY; //Para rotar la escena
GLfloat Rotacion = 0;
GLfloat Rotacion1 = 0;

void DibujaObjetos (void) {
glPushMatrix();
        glColor4ub(160, 160, 160, 0);   //Gris
        glRotatef(Rotacion1, 0, 1, 0);
        glScalef(10, 10, 10);
        glTranslatef(-8, 0, 0);
        glRotatef(Rotacion1*10, 1, 1, 1);
        glutSolidIcosahedron();
     glPopMatrix();

     glPushMatrix();
         glScalef(0.5, 0.5, 0.5);
         //glTranslatef(50, 0, 0);
         glPushMatrix();
            glColor4ub(255, 255, 0, 0);   //Amarillo
            glTranslatef(0, 30, 0);
            glRotatef(90, 1, 0, 0);
            glutWireTorus(5, 10, 10, 20); //Dona
         glPopMatrix();

         glPushMatrix();
            glColor4ub(255, 0, 0, 0);   //Rojo
            glRotatef(Rotacion, 0, -1, 0);
            glRotatef(90, 1, 0, 0);
            glutWireSphere(50, 30, 10);
         glPopMatrix();

         glColor4ub(0, 255, 0, 0);   //Verde
         glutWireCube (100.0);       //Se ve un cuadrado

         glPushMatrix();
            glColor4ub(0, 0, 255, 0);
            glRotatef(Rotacion, 1, 1, 1);
            glutSolidTeapot(25);  //Tetera
         glPopMatrix();
     glPopMatrix();

}


void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   //Rota la escena
   glRotatef(spinX, 1, 0, 0);
   glRotatef(spinY, 0, 1, 0);

   DibujaObjetos();

   glutSwapBuffers();
}
void spinDisplay(void)
{
  Rotacion += 0.1;
   Rotacion1 += 0.2;
   glutPostRedisplay(); //Vuelve a dibujar
}

void init(void) {
  glClearColor (0.0, 0.0, 0.0, 0.0); //Colores para iniciar la ventana (Fondo)
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
}

void reshape(int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(-100.0, 100.0, -100.0, 100.0, -500.0, 500.0); //Izq, Der, Abajo, Arriba, Cerca, lejos
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluPerspective(45.0, (float)w / (float)h, 100.0, 100.0);
}

void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {
    case 27: //Escape key
         exit(0);
    break;
  }
}

void mouseMotion(int x, int y)
{
     spinX = y;
     spinY = x;
}

void mouse(int button, int state, int x, int y)
{
switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
         break;

      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;

      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);   //Inicializa la librería GLUT y negocia una sesión
                            //con el sistema de ventanas
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Activa el modo inicial de despliegue
                            //GLUT_DOUBLE doble buffer  GLUT_RGB = GLUT_RGBA
   glutInitWindowSize (600, 600); //Tamaño de la ventana 500 x 500
   glutInitWindowPosition (100, 100); //Posición de la ventana en la pantalla
   glutCreateWindow ("Esfera - Cubo"); //Crea la ventana y le pone la etiqueta

   init ();  //Ejecuta el método "init"

   glutDisplayFunc(display);  //Ejecuta el método "display"
   glutKeyboardFunc(handleKeypress);
   glutReshapeFunc(reshape); //Ejecuta el método "reshape"
   glutMouseFunc(mouse); //Activa los controles del mouse
   glutMotionFunc(mouseMotion);
   glutMainLoop(); //Repite el main indefinidamente (¡Animación!)
    return 0;   /* ANSI C requires main to return int. */
}
//Ejercicio 02_ 09-Agosto-2021
// Cuadrado con una telearaña con animación
