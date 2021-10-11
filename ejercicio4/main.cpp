#include <windows.h>
#include <GL/glut.h>

GLfloat spinX=0.0, spinY=0.0;
GLfloat Hx = 0.0, Hy = 0.0, Hz = 0.0;  //Mueven el helicóptero

GLint Zoom = 1;
GLint Rot = 0;
GLfloat Rotacion = 0;

void drawBowl(void) { //Pin que une la cabina con la hélice
 glPushMatrix();
    glScalef(0.5,0.5,0.5);
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    glColor4ub(218, 165, 32, 0);
    glPushMatrix();
        glTranslatef(0, 0, 0); //x, y, z
        //glutSolidSphere(20,20,10);
        glRotatef(90, 1, 0, 0);
        glScalef(1,0.1,1);
        glutSolidSphere(100,360,10);
    glPopMatrix();
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
       glTranslatef(0, 0, 0); //x, y, z
        gluCylinder(Cilindro, 100, 100,10,360,5);
    glPopMatrix();
    glPushMatrix();
       gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 10); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 9, 15, 100, 360, 5);
    glPopMatrix();
    glPushMatrix();
       gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 100); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 15, 25, 20, 360, 5);
    glPopMatrix();
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 120); //x, y, z
        gluCylinder(Cilindro, 25, 25,10,360,5);
    glPopMatrix();
    glPushMatrix();
       gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 130); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 25, 7, 20, 360, 5);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, 180); //x, y, z
        GLUquadricObj *sphere=NULL;
        sphere = gluNewQuadric();
        gluQuadricDrawStyle(sphere, GLU_FILL);
        gluQuadricNormals(sphere, GLU_SMOOTH);
        gluSphere(sphere,30, 20, 20);
    glPopMatrix();
    glPushMatrix();
       gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 206); //x, y, z
        gluCylinder(Cilindro, 16, 30, 20, 360, 5);
    glPopMatrix();
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 226); //x, y, z
        gluCylinder(Cilindro, 40, 40,10,360,5);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, 226); //x, y, z
        //glutSolidSphere(20,20,10);
        glRotatef(90, 1, 0, 0);
        glScalef(1,0.1,1);
        glutSolidSphere(40,360,10);
    glPopMatrix();
    glPopMatrix();
}

void drawStem(void) {
 glPushMatrix();
    glScalef(0.5,0.5,0.5);
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    glColor4ub(218, 165, 32, 0);
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);//fill==liso, line==alambrado
        glTranslatef(0, 0, 70); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 5, 5, 80, 10, 5);
    glPopMatrix();


  glPopMatrix();
}
void drawFoot(void) {
    glPushMatrix();
        glScalef(0.5,0.5,0.5);
        GLUquadricObj *Cilindro;
        Cilindro = gluNewQuadric();
        glColor4ub(218, 165, 32, 0);

        glPushMatrix();
            gluQuadricDrawStyle(Cilindro, GLU_FILL);//fill==liso, line==alambrado
            glTranslatef(0, 0, 150); //x, y, z
           // glRotatef(90, 0, 1, 0);
            gluCylinder(Cilindro, 5, 10, 5, 10, 5);
        glPopMatrix();
        glPushMatrix();
            gluQuadricDrawStyle(Cilindro, GLU_FILL);//fill==liso, line==alambrado
            glTranslatef(0, 0, 155); //x, y, z
           // glRotatef(90, 0, 1, 0);
            gluCylinder(Cilindro, 10, 40, 20, 10, 5);
        glPopMatrix();
        glPushMatrix();
            gluQuadricDrawStyle(Cilindro, GLU_FILL);
            glColor4ub(255, 0, 0, 0);
            //glTranslatef(0, 0, 172); //x, y, z
            glRotatef(-1, 0, 1, 0);
            gluCylinder(Cilindro, 10, 40, 3, 10, 5);
        glPopMatrix();
    glPopMatrix();

}
void drawCopa(void) {
   glPushMatrix();
       drawBowl();
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
   drawCopa();
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

