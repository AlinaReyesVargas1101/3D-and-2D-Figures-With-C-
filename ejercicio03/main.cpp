#include <windows.h>
#include <GL/glut.h>

GLfloat spinX=0.0, spinY=0.0;
GLfloat Hx = 0.0, Hy = 0.0, Hz = 0.0;  //Mueven el helicóptero

GLint Zoom = 1;
GLint Rot = 0;
GLfloat Rotacion = 0;

void DibujaCabina (void) {
   glPushMatrix();
     glColor4ub(255, 0, 0, 0);   //Rojo
     glRotatef(90, 0, 1, 0);
     glScalef(0.8, 0.8, 1);
     //glutSolidSphere(15, 40, 10);
     glutWireSphere(15, 40, 10);
   glPopMatrix();
}

void drawPin1(void) { //Pin que une la cabina con la hélice
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();

    //Cilindro relleno
    glPushMatrix();
        glColor4ub(255, 0, 0, 0);   //Rojo
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 15, 0); //x, y, z
        glRotatef(90, 1, 0, 0);
        gluCylinder(Cilindro, 1, 1, 3, 10, 1); //Dibuja el pin
        gluCylinder(Cilindro, 0, 1, 0.2, 10, 1); //Dibuja la tapa
    glPopMatrix();
}

void drawPin2(void) { //Pin que une la cabina con la hélice
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();

    //Cilindro relleno
    glPushMatrix();
        glColor4ub(255, 0, 0, 0);   //Rojo
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(-62, 0, 1); //x, y, z
        glRotatef(90, 0, 0, 1);
        gluCylinder(Cilindro, 1, 1, 3, 10, 1); //Dibuja el pin
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-62, 0, 4); //x, y, z
        glRotatef(90, 0, 0, 1);
        gluCylinder(Cilindro, 1, 0, 0.2, 10, 1); //Dibuja la tapa
    glPopMatrix();
}

void DibujaHelices(void) {
    glColor4ub(0, 255, 0, 0);   //Verde
    //Hélice delantera
    glPushMatrix();
        glTranslatef(0, 13, 0);
        glPushMatrix();
         glRotatef(Rotacion, 0, -1, 0),
         glPushMatrix();
           glScalef(5, 0.5, 50);
           glutSolidCube (1);
         glPopMatrix();

         glPushMatrix();
           glScalef(50, 0.5, 5);
           glutSolidCube (1);
         glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    //Hélice trasera
    glPushMatrix();
        glTranslatef(-62, 0, 3); //Mueve la hélice trasera
        glPushMatrix();
         glRotatef(Rotacion, 0, 0, -1),
         glPushMatrix();
           glScalef(20, 3, 0.5);
           glutSolidCube (1);
         glPopMatrix();

         glPushMatrix();
           glScalef(3, 20, 0.5);
           glutSolidCube (1);
         glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    drawPin1();
    drawPin2();
}

void drawAxis(void) {
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();

    glColor4ub(0, 0, 255, 0);   //Blue
    //Cilindro relleno
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(-64, 0, 0); //x, y, z
        glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 2, 4, 50, 10, 5);
    glPopMatrix();
}

void drawLandingSkids(void) { //*********************TAREA***********************************
    //Lado izquierdo
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    gluQuadricDrawStyle(Cilindro, GLU_FILL);

    /*GLUquadricObj *Cilindro2;
    Cilindro2 = gluNewQuadric();
    gluQuadricDrawStyle(Cilindro2, GLU_FILL);*/

    glColor4ub(0, 255, 0, 0);  //Green
    glPushMatrix();
        glTranslatef(-15, -20, 12); //x, y, z
        glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 0.8, 0.8, 30, 10, 5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-8, -20, 12); //x, y, z
        glRotatef(-120, 1, 0, 0);
        gluCylinder(Cilindro, 0.8, 0.8, 13, 10, 5);
    glPopMatrix();

     glPushMatrix();
        glTranslatef(8, -20, 12); //x, y, z
        glRotatef(-120, 1, 0, 0);
        gluCylinder(Cilindro, 0.8, 0.8, 13, 10, 5);
    glPopMatrix();

    //Lado derecho

    GLUquadricObj *Cilindro2;
    Cilindro2 = gluNewQuadric();
    gluQuadricDrawStyle(Cilindro2, GLU_FILL);

    glColor4ub(0, 255, 0, 0);   //green
    glPushMatrix();
        glTranslatef(-15, -20, -12); //x, y, z
        glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro2, 0.8, 0.8, 30, 10, 5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-8, -20, -12); //x, y, z
        glRotatef(-70, 1, 0, 0);
        gluCylinder(Cilindro2, 0.8, 0.8, 13, 10, 5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(8, -20, -12); //x, y, z
        glRotatef(-70, 1, 0, 0);
        gluCylinder(Cilindro2, 0.8, 0.8, 13, 10, 5);
    glPopMatrix();

    //----------------TAPONES DE LAS PATAS-----------------------------------
    //derecha atras
    glPushMatrix();
     glColor4ub(221, 0, 0, 0);   //Rojo
     glTranslatef(-15, -20, -12); //x, y, z
     glutSolidSphere(1,10,10);
   glPopMatrix();
   //derecha adelante
    glPushMatrix();
     glColor4ub(221, 0, 0, 0);   //Rojo
     glTranslatef(15, -20, -12); //x, y, z
     glutSolidSphere(1,10,10);
   glPopMatrix();
    //Izquierda atras
    glPushMatrix();
     glColor4ub(221, 0, 0, 0);   //Rojo
     glTranslatef(-15, -20, 12); //x, y, z
     glutSolidSphere(1,10,10);
   glPopMatrix();
   //Izquierda adelante
    glPushMatrix();
     glColor4ub(221, 0, 0, 0);   //Rojo
     glTranslatef(15, -20, 12); //x, y, z
     glutSolidSphere(1,10,10);
   glPopMatrix();
}
void drawPaletas(void) {
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();

    glColor4ub(0, 0, 255, 0);   //Blue
//Cilindro relleno--- horizontal
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glScalef(1, 0.2 , 1);
        glTranslatef(-60, 0, -12); //x, y, z
        glRotatef(90, 0, 0, 1);
        gluCylinder(Cilindro, 2, 4, 15, 10, 5);
    glPopMatrix();

//Cilindro relleno--- SUPERIOR
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(-60, 12, 0); //x, y, z
        glRotatef(90, 1, 0, 0);
        glScalef(1, 0.2, 1);
        gluCylinder(Cilindro, 2, 4, 15, 10,5);
    glPopMatrix();


//Cilindro relleno--- INFERIOR
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(-60, -12, 0); //x, y, z
        glRotatef(-90, 1, 0, 0);
        glScalef(1, 0.2, 1);
        gluCylinder(Cilindro, 2, 4, 15, 10, 5);
    glPopMatrix();
}
void drawHelicopter(void) {
   glPushMatrix();
   /*
       glRotatef(AnguloX,1,0,0);
       glRotatef(AnguloY,1,0,0);
       glRotatef(AnguloZ,1,0,0);
       */
       glTranslatef(Hx, Hy, Hz); //Mueve el helicóptero
       DibujaHelices();
       DibujaCabina();
       drawAxis();
       drawLandingSkids();
       drawPaletas();
   glPopMatrix();
}

void draw_scene(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glRotatef(spinX, 1, 0, 0);
   glRotatef(spinY, 0, 1, 0);
   glScalef(Zoom, Zoom, Zoom); //Escala toda la escena
   drawHelicopter();
   glutSwapBuffers();
}

void spinDisplay(void)
{
   if (Rot == 1)
       Rotacion += 1;
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

void handleKeypress(unsigned char key, int x, int y) {//Eventos con el teclado
  switch (key) {
    case 27: //Escape key
         exit(0);
    break;

    case 'r': //La hélice gira
    case 'R':
         if (Rot == 1)
             Rot = 0;
         else
             Rot = 1;
    break;

    case 'a':
         --Zoom;
    break;

    case 'A':
         ++Zoom;
    break;
 //--------------------------------- EJE X-------------------------------------
    case 'x':
         --Hx;
    break;

    case 'X':
         ++Hx;
    break;
//--------------------------------- EJE Y-------------------------------------
    case 'y':
         --Hy;
    break;

    case 'Y':
         ++Hy;
    break;
//--------------------------------- EJE Z-------------------------------------
    case 'z':
         --Hz;
    break;

    case 'Z':
         ++Hz;
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
   glutCreateWindow ("Esfera"); //Crea la ventana y le pone la etiqueta

   init ();  //Ejecuta el método "init"

   glutDisplayFunc(draw_scene);  //Ejecuta el método "display"
   glutKeyboardFunc(handleKeypress);
   glutReshapeFunc(reshape); //Ejecuta el método "reshape"
   glutMouseFunc(mouse); //Activa los controles del mouse
   glutMotionFunc(mouseMotion);
   glutMainLoop(); //Repite el main indefinidamente (¡Animación!)
   return 0;   /* ANSI C requires main to return int. */
}

