#include <windows.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>

#include <math.h>
#include "TGATextura.h" //Archivo para las texturas

// Con "p" cambia el diseño del trompo

GLfloat LIGHT_POS = 50.0f; //The length of each side of the cube
GLfloat BOX_HEIGHT = 7.0f; //The height of the box off of the ground
GLint Lados = 30;
GLint isRightKeyPressed = false;
GLint isLeftKeyPressed  = false;
GLint isUpKeyPressed    = false;
GLint isDownKeyPressed  = false;
GLint ArrowColor;
GLfloat aZh = 0;
GLfloat _angle = 0;
//Dirección
GLint dx = 0; GLint dy = -1; GLint dz = 0;
//Dirección helicoptero
//GLint dx2 = 0; GLint dy2 = -1; GLint dz2 = 0;
//Posición
GLfloat rX = -10; GLfloat rY = 6.7; GLfloat rZ = 0;
//-----------------------------------------------
GLfloat FLOOR_SIZE = 25.0f; //The length of each side of the floor

GLfloat Zoom = 1;
GLint Trompo = 1; //Con la letra "p" cambia el diseño de la tapa del trompo

//Variables para controlar la actividad de los trompo

    GLint Control = 1;
    GLfloat tx = 0;      //Posición en x
    GLfloat ty = -7.6;   //Posición en y
    GLfloat tz = 0;      //Posición en z
    GLfloat Angulo = 0;

    GLfloat AnguloH = 0;

    GLfloat Hx = 10;      //Posición en x
    GLfloat Hy = -5;   //Posición en y
    GLfloat Hz = 12;      //Posición en z

    GLfloat Rotacion = 0;
    GLfloat VelocRotacion = 0.01;
    GLfloat Inclinacion = 0;
    GLfloat VelocInclinacion = 0.002;
    GLfloat Desaceleracion;
    //GLfloat Estado; //0 Inactivo y 1 Activo

    GLfloat RotEscene = 0;
    GLfloat RotBall = 0;
    GLfloat RotB = 0;
    GLfloat TranslateBall = 0;
    GLfloat RotacionH = 0;
    GLfloat RotH = 0;
    GLfloat roteT = 0;
     GLfloat TransH = 0;
    GLint direccionBall=1;
    GLint laserContol=0;

    GLfloat RebBall=0;
    GLfloat NumRebBall=4;
    GLfloat TranslateBall2 = 0;

GLfloat Luz = 0.5;
GLint Transparencia = 150; // reflejo del piso

GLint spinX = 0, spinY = 0;

GLint Rot = 0;

GLfloat Rot_Scene = 0;// <---Varibale para la rotación
GLfloat rotateB;
GLfloat translateB;
//GLint RotB = 1;
GLfloat bounce = 0;
//--------------------------------------------------------------------------------------------------------------
GLint Meridianos = 0;
GLfloat cerca = 0;
//---------------------------------------------------------------------------------------------------------------
//                               variables para el movimiento del helicoptero
//---------------------------------------------------------------------------------------------------------------
GLfloat rX2 = -5; GLfloat rY2 = -5; GLfloat rZ2 = 5;
//glTranslatef(-5,0.2,-3); //x, y, z
GLint dx2 = 0; GLint dy2 = -1; GLint dz2 = 0;
float incremental2=0.00001;
GLfloat incrementalH2=2;
bool animacion2=false;
bool animationround2=false;
float angle2=70.5;
GLfloat RotacionH2 = 0;
GLboolean aterrizar2 = false;
GLfloat laserBola = 0.0;
GLfloat anglerot2 = 0;
GLboolean girarH2 = false;
void drawFloor(void){
    GLfloat Lado = 12;
    GLfloat Brick = Lado/8;
    GLint Cuadros = 18;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texturas[0].ID);

    glPushMatrix();
    glTranslatef(-Brick, 0, 0);
    glBegin(GL_QUADS);
    for(int i=0;i<Cuadros;i++){
       for(int j=0;j<Cuadros;j++){
            if((i+j)%2==0){
                glColor4ub(240, 128, 128,Transparencia);
            }else{
                glColor4ub(112, 112, 112,Transparencia);
            }
                glTexCoord2f(0, 0); glVertex3f(-Lado+(i*Brick), 0, -Lado+(j*Brick));
                glTexCoord2f(1, 0); glVertex3f(-(Lado-Brick)+(i*Brick), 0, -Lado+(j*Brick));
                glTexCoord2f(1, 1); glVertex3f(-(Lado-Brick)+(i*Brick), 0, -(Lado-Brick)+(j*Brick));
                glTexCoord2f(0, 1); glVertex3f(-Lado+(i*Brick), 0, -(Lado-Brick)+(j*Brick));
        }
    }
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
void drawTeaPot (void) {  //Dibuja tetera
    glColor4ub(32, 178, 170, 0); //

    glPushMatrix();
      glTranslatef(10, -6.2, 0);
      glutSolidTeapot(1);
    glPopMatrix();
}
void drawTrompo (void) {

   GLint Lados = 30;

   GLUquadricObj *qobj; //Define el objeto
   qobj = gluNewQuadric();
   gluQuadricDrawStyle(qobj, GLU_FILL);
    GLfloat ambient[]   = { 0.20, 0.05, 0.05, 1.0 };
    GLfloat diffuse[]   = { 0.89, 0.64, 0.14, 1.0 };
    GLfloat specular[]  = { 0.00, 0.00, 0.00, 1.0 };
    GLfloat emission[]  = { 0.00, 0.00, 0.00, 1.0 };
    GLfloat shininess[] = { 128.0 };

    glMaterialfv( GL_FRONT, GL_AMBIENT,   ambient );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,   diffuse );
    glMaterialfv( GL_FRONT, GL_SPECULAR,  specular );
    glMaterialfv( GL_FRONT, GL_EMISSION,  emission );
    glMaterialfv( GL_FRONT, GL_SHININESS, shininess );

   glPushMatrix();
     glTranslatef(tx, ty, tz);
     //glTranslatef(0, -7.6, 0);
     glScalef(0.1, 0.1, 0.1); //Escala el trompo para hacerlo más pequeño

     glRotatef(Rotacion, 0, -1, 0); //Gira sobre el eje
     glRotatef(Inclinacion, 1, 0, 0);  //Inclinación

//Se dibuja de arriba hacia abajo, son 14 dibujos

   glColor4ub(255, 0, 0, 0); //Rojo
   glPushMatrix(); //Objeto 13
     glTranslatef(0, 31, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 0, 2, 1, Lados, 1);
   glPopMatrix();

   glColor4ub(255, 255, 0, 0); //Amarillo
   glPushMatrix(); //Objeto 13
     glTranslatef(0, 30, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 2, 2, 2, Lados, 1);
   glPopMatrix();

   glColor4ub(255, 255, 0, 0); //Amarillo
   glPushMatrix();
     glTranslatef(0, 28, 0);
     glRotatef(-90, 1, 0, 0);
     if (Trompo == 1) { //Tapa con textura
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texturas[1].ID);
        gluQuadricTexture(qobj, GL_TRUE);
        gluDisk(qobj, 0, 6, Lados, 1);
        glDisable(GL_TEXTURE_2D);
     }
     else {
        glColor4ub(255, 0, 0, 0); //Rojo
        gluQuadricDrawStyle(qobj, GLU_LINE);
        gluCylinder(qobj, 6, 2, 1, Lados, 1);
     }
   glPopMatrix();

   gluQuadricDrawStyle(qobj, GLU_FILL);
   glColor4ub(255, 255, 0, 0); //Amarillo
   glPushMatrix(); //Objeto 13
     glTranslatef(0, 28, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 6, 8, 2, Lados, 1);
   glPopMatrix();

   glColor4ub(255, 0, 0, 0); //Rojo
   glPushMatrix(); //Objeto 1
     glTranslatef(0, 26, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 8, 8.5, 2, Lados, 1);
   glPopMatrix();

   glColor4ub(255, 255, 0, 0); //Amarillo
   glPushMatrix(); //Objeto 2
     glTranslatef(0, 24, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 8.5, 8.5, 2, Lados, 1);
   glPopMatrix();

   glColor4ub(255, 0, 0, 0); //Rojo
   glPushMatrix(); //Objeto 3
     glTranslatef(0, 22, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 8.5, 8, 2, Lados, 1);
   glPopMatrix();

   glColor4ub(255, 255, 0, 0); //Amarillo
   glPushMatrix(); //Objeto 4
     glTranslatef(0, 20, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 8, 7, 2, Lados, 1);
   glPopMatrix();

   glColor4ub(255, 0, 0, 0); //Rojo
   glPushMatrix(); //Objeto 3
     glTranslatef(0, 22, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 8.5, 8, 2, Lados, 1);
   glPopMatrix();

   glColor4ub(255, 255, 0, 0); //Amarillo
   glPushMatrix(); //Objeto 5
     glTranslatef(0, 18, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 7, 6, 2, Lados, 1);
   glPopMatrix();

   glColor4ub(255, 0, 0, 0); //rojo
   glPushMatrix(); //Objeto 6
     glTranslatef(0, 16, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 6, 4, 2, Lados, 1);
   glPopMatrix();

   glColor4ub(255, 255, 0, 0); //Amarillo
   glPushMatrix(); //Objeto 7
     glTranslatef(0, 14, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 4, 2, 2, Lados, 1);
   glPopMatrix();

   glPushMatrix(); //Objeto 8
     glTranslatef(0, 12, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 2, 0.6, 2, Lados, 1);
   glPopMatrix();

//Palito !!
   glColor4ub(112, 112, 112, 0); //line color gris
   glPushMatrix(); //Objeto 9
     glTranslatef(0, 10, 0);
     glRotatef(90, 1, 0, 0);
     gluCylinder(qobj, 0.6, 0.6, 3, Lados, 1);
   glPopMatrix();

   glPushMatrix(); //Punta cónica o esférica
   //glColor4ub(255, 255, 0, 0); //line color gris
     glTranslatef(0, 7, 0);
     glutSolidSphere(0.9, 50, 10);
   glPopMatrix();

   glPopMatrix();

   gluDeleteQuadric(qobj);
}
//************************************************** Dibuja el HELICOPTERO ************************************************
// ejercicio 03
void DibujaCabina (void) {
   glPushMatrix();
     glColor4ub(70,130,180,0);
     glRotatef(90, 0, 1, 0);
     glScalef(0.8, 0.8, 1);
     //glutSolidSphere(15, 40, 10);
     glutSolidSphere(15, 40, 10);
   glPopMatrix();
}
void drawPin1(void) { //Pin que une la cabina con la hélice
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();

    //Cilindro relleno
    glPushMatrix();
        glColor4ub(70,130,180,0);
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
        glColor4ub(70,130,180,0);
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
    glColor4ub(255,99,71,0);
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

    glColor4ub(70,130,180,0);
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

   glColor4ub(255,99,71,0);
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

    glColor4ub(255,99,71,0);  //green
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

    glColor4ub(70,130,180,0);   //Blue
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
void shootBalls(){
    glPushMatrix();
        glColor4ub(255, 0, 0, 0);;
        glRotatef(90, 0, 1, 0);
        glTranslatef(-20, -5, 30); //x, y, z
        glutSolidSphere(3,20,10);
    glPopMatrix();
    glPushMatrix();
        glColor4ub(255, 0, 0, 0);;
        glRotatef(90, 0, 1, 0);
        glTranslatef(20, -5, 30); //x, y, z
        glutSolidSphere(3,20,10);
    glPopMatrix();
}
void drawHelicopter(void) {
   glPushMatrix();
        //glTranslatef(10,-5, 12); //x, y, z
        //glScalef(0.1,0.1,0.1);
        //glRotatef(RotacionH, 0, 1, 0);
        //glTranslatef(0,TransH, 0);
        glTranslatef(rX2,rY2,rZ2);
        //glTranslatef(10,-5, 12); //x, y, z
        //glTranslatef(-5,0.2,-3); //x, y, z
        //Activa y desactiva el rayo láser
        if (laserContol == 1) {
            glPushMatrix();
                glTranslatef(1.5, 1, 0);
                //GLfloat rX2 = -5; GLfloat rY2 = -5; GLfloat rZ2 = 5;
                glScaled(0.1,0.1,0.1);
                glBegin(GL_LINES);
                glColor4ub(255, 31, 31, 0);
                glVertex3f( -30.0f, -30.0f, -12.0f ); glVertex3f( 350.0f, -30.0f, -12.0f ); //Línea Norte a Sur
                glVertex3f( -30.0f, -30.0f, 12.0f ); glVertex3f( 350.0f, -30.0f, 12.0f ); //Línea Norte a Sur
                glEnd ();
            glPopMatrix();
        }
       glPushMatrix();
           //glTranslatef(Hx, Hy, Hz); //Mueve el helicóptero
           //glTranslatef(10,-5, 12); //x, y, z
           glScalef(0.1,0.1,0.1);
           DibujaHelices();
           DibujaCabina();
           drawAxis();
           drawLandingSkids();
           drawPaletas();
       glPopMatrix();
    /*
       glPushMatrix();
            glScaled(0.1,0.1,0.1);
            glTranslatef(laserBola,0,0);
            shootBalls();
       glPopMatrix();
*/
   glPopMatrix();
}
void animacionH(){
    if(animacion2){
        if(rY2<4){
            rY2+=incremental2;
            incremental2+=0.00001;
        }else if( rZ2<5.5){
            rZ2+=incremental2;
        }
        if(rZ2>5.5){
            animationround2=true;
            animacion2=false;
        }
    }else if(animationround2){
        anglerot2 += 0.1;
        rX2 = -2 + 15 * cos(angle2);
        rZ2 = 0 + 15 * sin(angle2);
        angle2+=0.003;
        //RotacionH+=incrementalH;
        if(angle2>=76.8){
            animationround2=false;
            aterrizar2=true;
        }
    }else if(aterrizar2){
        if( rZ2<=16){
            rZ2-=incremental2;
        }
        if( rY2<=5){
            rY2-=incremental2;
        }
        /*if(rY>0){//ok
            rY-=incremental;
            incremental-=0.00001;
        }*/
        if(rY2<= -5){
            aterrizar2=false;
            girarH2 = false;
            animacion2 = false;
            angle2 = 70.5;
        }
        RotacionH2-=incrementalH2;
    }
}
//************************************************** Dibuja el mi versión de trompo ************************************************
//los nombres raros es porque yo habia usado la tarea de la copa como base
void auxTrompo(void) { //Pin que une la cabina con la hélice
 glPushMatrix();
    glScalef(0.5,0.5,0.5);
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    glColor4ub(0, 0, 255, 0);
    //glRotatef(Rotacion, 0, -1, 0),

    glPushMatrix();
        glTranslatef(0, 0, -30); //x, y, z
        glRotatef(180, 0, 1, 0);
        gluCylinder(Cilindro, 10, 0,10 ,10 , 1);
    glPopMatrix();
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);//fill==liso, line==alambrado
        glTranslatef(0, 0, -30); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 10, 10, 10, 10, 5);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, -20); //x, y, z
        glRotatef(180, 1, 0, 0);
        gluDisk(Cilindro, 0, 36, 40, 5);
    glPopMatrix();
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, -20); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro,36, 42, 10, 10, 5);
    glPopMatrix();
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, -10); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 42, 46, 10, 10, 5);
    glPopMatrix();
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, -10); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 46, 48, 10, 10, 5);
    glPopMatrix();

    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, -10); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 48, 50, 10, 10, 5);
    glPopMatrix();

    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
       // glTranslatef(-64, 0, 0); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 50, 48, 10, 10, 5);
    glPopMatrix();

    //-
    glPushMatrix();
       gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 10); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 48, 46, 10, 10, 5);
    glPopMatrix();
    //-
    glPushMatrix();
     gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 20); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 46, 42, 10, 10, 5);
    glPopMatrix();

     glPushMatrix();
     gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 30); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 42, 36, 10, 10, 5);
    glPopMatrix();

     glPushMatrix();
     gluQuadricDrawStyle(Cilindro, GLU_FILL);//fill==liso, line==alambrado
        glTranslatef(0, 0, 40); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 36, 30, 10, 10, 5);
    glPopMatrix();

     glPushMatrix();
     gluQuadricDrawStyle(Cilindro, GLU_FILL);//fill==liso, line==alambrado
        glTranslatef(0, 0, 50); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 30, 20, 10, 10, 5);
    glPopMatrix();

    glPushMatrix();
     gluQuadricDrawStyle(Cilindro, GLU_FILL);//fill==liso, line==alambrado
        glTranslatef(0, 0, 60); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 20, 5, 10, 10, 5);
    glPopMatrix();
    glPopMatrix();
}
void auxTrompo2(void) {
 glPushMatrix();
    glScalef(0.5,0.5,0.5);
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    glColor4ub(0, 255, 0, 0);
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);//fill==liso, line==alambrado
        glTranslatef(0, 0, 70); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 5, 5, 10, 10, 5);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, 80); //x, y, z
        //glRotatef(180, 0, 1, 0);
        gluCylinder(Cilindro, 5, 0,10 ,10 , 1);
    glPopMatrix();

  glPopMatrix();
}
void drawTrompo2(void) {
    /*
   glPushMatrix();
        glRotatef(90, 1, 0, 0);
       //glTranslatef(Hx, Hy, Hz); //Mueve el helicóptero
       glTranslatef(10,8, 12); //x, y, z
       glScalef(0.05,0.05,0.05);
       glRotatef(Rotacion, 0, 0, 1),
       glRotatef(30, 0, 1, 0),
       glPushMatrix();
           glRotatef(90, 0, 0, 1),
           auxTrompo();
           auxTrompo2();
           //drawFloor();
       glPopMatrix();
       //drawFloor();
   glPopMatrix();*/
}
//************************************************** Dibuja la copa ************************************************
void drawBowl(void) {
 glPushMatrix();
    glScalef(0.5,0.5,0.5);
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    //glColor4ub(218, 165, 32, 0);
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
       // glTranslatef(-64, 0, 0); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 50, 48, 10, 10, 5);
    glPopMatrix();

    //-
    glPushMatrix();
       gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 10); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 48, 46, 10, 10, 5);
    glPopMatrix();
    //-
    glPushMatrix();
     gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 20); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 46, 42, 10, 10, 5);
    glPopMatrix();

     glPushMatrix();
     gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(0, 0, 30); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 42, 36, 10, 10, 5);
    glPopMatrix();

     glPushMatrix();
     gluQuadricDrawStyle(Cilindro, GLU_FILL);//fill==liso, line==alambrado
        glTranslatef(0, 0, 40); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 36, 30, 10, 10, 5);
    glPopMatrix();

     glPushMatrix();
     gluQuadricDrawStyle(Cilindro, GLU_FILL);//fill==liso, line==alambrado
        glTranslatef(0, 0, 50); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 30, 20, 10, 10, 5);
    glPopMatrix();

    glPushMatrix();
     gluQuadricDrawStyle(Cilindro, GLU_FILL);//fill==liso, line==alambrado
        glTranslatef(0, 0, 60); //x, y, z
       // glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 20, 5, 10, 10, 5);
    glPopMatrix();
    glPopMatrix();
}
void drawStem(void) {
 glPushMatrix();
    glScalef(0.5,0.5,0.5);
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    //glColor4ub(218, 165, 32, 0);
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
        //glColor4ub(218, 165, 32, 0);

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
            glTranslatef(0, 0, 172); //x, y, z
            glRotatef(-1, 0, 1, 0);
            gluCylinder(Cilindro, 10, 40, 3, 10, 5);
        glPopMatrix();
    glPopMatrix();

}
void drawCopa(void) {
   glPushMatrix();
        glColor4ub(218, 165, 32, 0);
        glTranslatef(-10,-6.3, 12);
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 1, 0);
        glScalef(0.03,0.03,0.03);
        drawBowl();
        drawStem();
        drawFoot();
   glPopMatrix();
}
//************************************************** Dibuja la bola ************************************************
void drawBall(void) {
    glPushMatrix();
        glTranslatef(TranslateBall, 0, 0);
        glTranslatef(0, TranslateBall2, 0);
        glTranslatef(-10,-6, 12); //x, y, z
        glScalef(0.3,0.3,0.3);
      glPushMatrix();
          glTranslatef(0, 0, -16);
          glRotatef(90, 1, 0, 0);
          glRotatef(RotBall, 0, -1, 0);
          //glRotatef(Rotacion, 0, 0, 1);
          //glRotatef(rotateB, 0, 0, 1);
          //glTranslatef(0, translateB, 0);
          //glTranslatef(0, 0, bounce);

          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D,texturas[2].ID);
          GLUquadricObj *sphere=NULL;
          sphere = gluNewQuadric();
          gluQuadricDrawStyle(sphere, GLU_FILL);
          gluQuadricTexture(sphere, TRUE);
          gluQuadricNormals(sphere, GLU_SMOOTH);
          glColor4ub(255, 255, 255, 0);
          gluSphere(sphere, 3+cerca, 24, 24);
          if (Meridianos == 1) {
              glColor4ub(25, 112, 112, 255);
              glutWireSphere(3.01+cerca, 24, 24);
          }
          glColor4ub(255, 255, 255, 0);
      glPopMatrix();
    glPopMatrix();
  gluDeleteQuadric(sphere);
  glDisable(GL_TEXTURE_2D);
}
void update(int value){
    rotateB+=0.5f;
    if(rotateB>360.f){
        rotateB-=360;
    }
    glutPostRedisplay();
    glutTimerFunc(25,update,0);
}
//************************************************** Dibuja la sombrilla ************************************************
void drawSombrilla(void){
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    gluQuadricDrawStyle(Cilindro, GLU_FILL);
    glPushMatrix();
        glScaled(0.06, 0.06, 0.06);
        //glTranslated(-80,-8,-35);
        glTranslated(-80,-55,-35);
        glRotatef(50.5, 0, 0, 1);
        glPushMatrix();
            glTranslated(0,7,0);
            glColor4ub(72,209,204, 0);
            glRotatef(90, 1, 0, 0);
            gluCylinder(Cilindro,0.8, 0.8, 105, 10, 3);
        glPopMatrix();
        glPushMatrix();
            glEnable(GL_BLEND);
            glColor4ub(176,224,230,150);
            glRotatef(90, 1, 0, 0);
            gluCylinder(Cilindro,0, 60, 25, 10, 3);
            glDisable(GL_BLEND);
        glPopMatrix();
            gluQuadricDrawStyle(Cilindro, GLU_LINE);
        glPushMatrix();
            glTranslated(0,-0.2,0);
            glColor4ub(224, 224, 224, 0);
            glRotatef(90, 1, 0, 0);
            gluCylinder(Cilindro,0, 60, 25, 10, 3);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0,-13,0);
            glRotatef(90, 1, 0, 0);
            gluCylinder(Cilindro,30, 0, 25, 10, 3);
        glPopMatrix();
    glPopMatrix();
    gluDeleteQuadric(Cilindro);
}
//************************************************** Dibuja el banco ************************************************
void dibujaPatasBanco(void){
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    gluQuadricDrawStyle(Cilindro, GLU_FILL);
     //glColor4ub(255,163,0, 0);
    //Pata 1
    glPushMatrix();
        glTranslatef(6, 4, 1); //x, y, z
        glRotatef(85, 1, 0, 0);
        gluCylinder(Cilindro, 0.1, 0.1, 4, 15, 15);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(4, 4, 1); //x, y, z
        glRotatef(85, 1, 0, 0);
        gluCylinder(Cilindro, 0.1, 0.1, 4, 15, 15);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(6, 4, -1); //x, y, z
        glRotatef(95, 1, 0, 0);
        gluCylinder(Cilindro, 0.1, 0.1, 4, 15, 15);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(4, 4, -1); //x, y, z
        glRotatef(95, 1, 0, 0);
        gluCylinder(Cilindro, 0.1, 0.1, 4, 15, 15);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(4, 1.5, 1.2); //x, y, z
        glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 0.1, 0.1, 2, 15, 15);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(4, 1.5, -1.2); //x, y, z
        glRotatef(90, 0, 1, 0);
        gluCylinder(Cilindro, 0.1, 0.1, 2, 15, 15);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(4, 1.5, -1.2); //x, y, z
        glRotatef(90, 0, 0, 1);
        gluCylinder(Cilindro, 0.1, 0.1, 2.4, 15, 15);
    glPopMatrix();
     glPushMatrix();
        glTranslatef(6, 1.5, -1.2); //x, y, z
        glRotatef(90, 0, 0, 1);
        gluCylinder(Cilindro, 0.1, 0.1, 2.4, 15, 15);
    glPopMatrix();

}
void banco(void){
    GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
     glColor4ub(128, 64, 0, 0);
     glPushMatrix();
        glScalef(1,0.1,1);
       glutSolidSphere(20,20,10);
     glPopMatrix();
     glPushMatrix(); /*patas HORIZONTALES*/
         gluQuadricDrawStyle(Cilindro, GLU_FILL);
         glRotatef(100,1,0,0);
         glTranslatef(-10,-10,1);
         glRotatef(-5,0,1,0);
         gluCylinder(Cilindro, 2, 2,60, 10, 5); /*Base radio, top radio, largo o alto del cilindro de base a top*/
     glPopMatrix();
     glPushMatrix(); /*patas HORIZONTALES*/
         gluQuadricDrawStyle(Cilindro, GLU_FILL);
         glRotatef(80,1,0,0);
         glTranslatef(10,10,1);
         glRotatef(5,0,1,0);
         gluCylinder(Cilindro, 2, 2,60, 10, 5); /*Base radio, top radio, largo o alto del cilindro de base a top*/
     glPopMatrix();
     glPushMatrix(); /*patas HORIZONTALES*/
         gluQuadricDrawStyle(Cilindro, GLU_FILL);
         glRotatef(80,1,0,0);
         glTranslatef(-10,10,1);
         glRotatef(-5,0,1,0);
         gluCylinder(Cilindro, 2, 2,60, 10, 5); /*Base radio, top radio, largo o alto del cilindro de base a top*/
     glPopMatrix();
     glPushMatrix(); /*patas HORIZONTALES*/
         gluQuadricDrawStyle(Cilindro, GLU_FILL);
         glRotatef(100,1,0,0);
         glTranslatef(10,-10,1);
         glRotatef(5,0,1,0);
         gluCylinder(Cilindro, 2, 2,60, 10, 5); /*Base radio, top radio, largo o alto del cilindro de base a top*/
     glPopMatrix();
     glPushMatrix(); /*patas HORIZONTALES*/
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(12,-25,-14);
        gluCylinder(Cilindro, 2, 2,30, 10, 5); /*Base radio, top radio, largo o alto del cilindro de base a top*/
     glPopMatrix();
     glPushMatrix(); /*patas HORIZONTALES*/
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(-12,-25,-14);
        gluCylinder(Cilindro, 2, 2,30, 10, 5); /*Base radio, top radio, largo o alto del cilindro de base a top*/
     glPopMatrix();
     glPushMatrix(); /*patas HORIZONTALES*/
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glRotatef(90,0,1,0);
        glTranslatef(-16,-30,-13);
        gluCylinder(Cilindro, 2, 2,25, 10, 5); /*Base radio, top radio, largo o alto del cilindro de base a top*/
     glPopMatrix();
     glPushMatrix(); /*patas HORIZONTALES*/
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glRotatef(90,0,1,0);
        glTranslatef(16,-30,-13);
        gluCylinder(Cilindro, 2, 2,25, 10, 5); /*Base radio, top radio, largo o alto del cilindro de base a top*/
     glPopMatrix();
}
void drawBanco(void){
    glPushMatrix();
        glScalef(0.1,0.1,0.1);
        glTranslatef(110,-11,-90);
        banco(),
    glPopMatrix();
}
void drawCopa2(void) {
   glPushMatrix();
        glEnable(GL_BLEND);
        //glColor4ub(185, 201, 241, 150);
        glColor4ub(176,224,230,100);
        glTranslatef(11,1.7,-9);
        glRotatef(90, 1, 0, 0);
        glScalef(0.03,0.03,0.03);
        drawBowl();
        drawStem();
        drawFoot();
        glDisable(GL_BLEND);
   glPopMatrix();
}
//************************************************** Dibuja la mesa ************************************************
//TAREA:copa sobre el banco y hacer la mesa
//sobre la mesa va la foto
void Mesa(void){
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
void drawMesa(void){
    glPushMatrix();
        glTranslatef(-10,-1, -8);
        glRotatef(90, 1, 0, 0);
        //glRotatef(90, 0, 1, 0);
        glScalef(0.05,0.05,0.05);
        Mesa();
    glPopMatrix();
}
//************************************************** Dibuja la fotografia ************************************************
void Imagen(void){
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texturas[3].ID);
        glColor4ub(112, 112, 112, 0); //El color afecta la imagen
        glBegin(GL_QUADS);
            /*
            glTexCoord2f(0, 0); glVertex2f(-1, -1);  // Bottom Left Of The Texture and Quad
            glTexCoord2f(1, 0); glVertex2f( 1, -1);  // Bottom Right Of The Texture and Quad
            glTexCoord2f(1, 1); glVertex2f( 1,  1);  // Top Right Of The Texture and Quad
            glTexCoord2f(0, 1); glVertex2f(-1,  1);  // Top Left Of The Texture and Quad
            */
            glTexCoord2f(0, 0); glVertex2f(1, 1); // Bottom Left Of The Texture and Quad
            glTexCoord2f(1, 0); glVertex2f(-1, 1); // Bottom Right Of The Texture and Quad
            glTexCoord2f(1, 1); glVertex2f(-1, -1); // Top Right Of The Texture and Quad
            glTexCoord2f(0, 1); glVertex2f(1, -1); // Top Left Of The Texture and Quad
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void marco(void){
    glPushMatrix();
    glRotatef(-65,0,0,1);
        glScalef(23,1,23);
        glutSolidCube(1);
     glPopMatrix();
}
void soporte(void){
     glPushMatrix();
     glColor4ub(51,25 , 0, 0);
     glRotatef(65,0,0,1);
        glScalef(12.5,1,7);
        glutSolidCube(1);
     glPopMatrix();
}
void Foto(void){
    glPushMatrix();
        glScalef(0.1,0.1,0.1);
        glTranslatef(-194.5,33.8,60);
        soporte();
    glPopMatrix();
    glPushMatrix();
        glScalef(0.1,0.1,0.1);
        glTranslatef(-192,38.8,60);
        marco();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-19.1,3.9,6);
        glRotatef(90,0,1,0);
        glRotatef(-25,1,0,0);
        Imagen();
    glPopMatrix();
}
void drawFoto(void){
    glPushMatrix();
        //glScalef(0.1,0.1,0.1);
        glTranslatef(9,-3.6, -14);
        Foto();
    glPopMatrix();
}

//************************************************** Dibuja la mesa con vidrio ************************************************
void drawPatas(void){
     glPushMatrix();
        glTranslatef(-2, 1.25, 14);
        glScalef(0.4, 2.5, 0.4);
        glutSolidCube (1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-2, 1.25, 10);
        glScalef(0.4, 2.5, 0.4);
        glutSolidCube (1);
    glPopMatrix();
    //Cambio X
    glPushMatrix();
        glTranslatef(-8, 1.25, 14);
        glScalef(0.4, 2.5, 0.4);
        glutSolidCube (1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-8, 1.25, 10);
        glScalef(0.4, 2.5, 0.4);
        glutSolidCube (1);
    glPopMatrix();

}
void drawVidrio(void){
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(-2,12,-2.5);
        glScalef(0.4, 4.4, 0.4);
        glutSolidCube (1);
    glPopMatrix();
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(-8,12,-2.5);
        glScalef(0.4, 4.4, 0.4);
        glutSolidCube (1);
    glPopMatrix();
    glPushMatrix();
        glRotatef(90, 0, 0, 1);
        glTranslatef(2.5,5,10);
        glScalef(0.4, 6, 0.4);
        glutSolidCube (1);
    glPopMatrix();
     glPushMatrix();
        glRotatef(90, 0, 0, 1);
        glTranslatef(2.5,5,14);
        glScalef(0.4, 6, 0.4);
        glutSolidCube (1);
    glPopMatrix();
     glPushMatrix();
        glEnable(GL_BLEND);
        glColor4ub(240,240,240, 170);
        glTranslatef(-5,2.6,12);
        glScalef(6, 0.1, 4);
        glutSolidCube (1);
        glDisable(GL_BLEND);
    glPopMatrix();
}
void drawMesaConTransparencia(void){
    glPushMatrix();
        glColor4ub(219,112,147,0);
        glTranslatef(15, -7, -12);
        //glRotatef(180, 0, 0, 1);
        drawPatas();
        drawVidrio();
    glPopMatrix();
}

//************************************************** Dibuja la flor dentro de la copa ************************************************
void drawCentro(void){
    glPushMatrix();
            glColor4ub(255, 163, 0, 0);
            glRotatef(90, 1, 0, 0);
            glScalef(1,0.6,1);
            glutSolidSphere(18, 30, 10);
        glPopMatrix();
}
void drawPetalos(void){
    glPushMatrix();
        glScalef(0.8,0.8,0.3);
        glColor4ub(247,170,172, 0);

        glPushMatrix();
            glTranslatef(30, 0 , 0);
            glRotatef(90, 1, 0, 0);
            glutSolidSphere(15, 30, 10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(15, 24 , 0);
            glRotatef(90, 1, 0, 0);
            glutSolidSphere(15, 30, 10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-12, 25, 0);
            glRotatef(90, 1, 0, 0);
            glutSolidSphere(15, 30, 10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-30, 5, 0);
            glRotatef(90, 1, 0, 0);
            glutSolidSphere(15, 30, 10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-23, -20, 0);
            glRotatef(90, 1, 0, 0);
            glutSolidSphere(15, 30, 10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0, -30, 0);
            glRotatef(90, 1, 0, 0);
            glutSolidSphere(15, 30, 10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(21, -24, 0);
            glRotatef(90, 1, 0, 0);
            glutSolidSphere(15, 30, 10);
        glPopMatrix();
    glPopMatrix();
}
void drawTallo(void){
   GLUquadricObj *Cilindro;
    Cilindro = gluNewQuadric();
    glColor4ub(0, 255, 0, 0); //Verde
    //Cilindro relleno
    glPushMatrix();
        gluQuadricDrawStyle(Cilindro, GLU_FILL);
        glTranslatef(1, -20, 0); //x, y, z
        glRotatef(90, 1, 0, 0);
        gluCylinder(Cilindro, 2, 2, 70, 20, 10);

    glPopMatrix();
}
void drawFlower(void){
    glPushMatrix();
        glTranslatef(11, 3, -9);
        glScalef(0.02,0.02,0.02);
        glPushMatrix();
            glRotatef(180, 1, 0, 0);
            drawCentro();
            drawPetalos();
         glPopMatrix();
         drawTallo();
     glPopMatrix();
}
//************************************************** Dibuja la lampara ************************************************
void drawBombillo(){
    glPushMatrix(); //Bombillo
    glColor4ub(255, 255, 0, 1);
    glTranslatef(rX, rY, rZ);
    glutSolidSphere(0.3, 50, 50);
  glPopMatrix();
}
void drawEstructura(){
    glColor4ub(173, 216, 230, 0);
    GLUquadricObj *qobj; //Define el objeto
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);

   glPushMatrix();

     glPushMatrix();
       glTranslatef(0, 1.3, 0);
       glRotatef(90, 1, 0, 0);
       gluCylinder(qobj, 0.2, 1, 1.5, 8, 1);
     glPopMatrix();

     gluQuadricDrawStyle(qobj, GLU_LINE);
     glPushMatrix();
       glTranslatef(0, -0.2, 0);
       glRotatef(90, 1, 0, 0);
       gluCylinder(qobj, 1, 0.2, 0.5, 8, 1);
     glPopMatrix();

     gluQuadricDrawStyle(qobj, GLU_FILL);

     glPushMatrix();
       glTranslatef(0, -0.5, 0);
       glRotatef(90, 1, 0, 0);
       gluCylinder(qobj, 0.2, 0.2, 5.5, 30, 1);
     glPopMatrix();

     glPushMatrix();
       glTranslatef(0, -5.5, 0);
       glRotatef(90, 1, 0, 0);
       gluCylinder(qobj, 0.2, 0.8, 1.5, 8, 1);
     glPopMatrix();

   glPopMatrix();

   gluDeleteQuadric(qobj);
//glutWireCube (4);
}
void drawLampara(){
    glPushMatrix();
        glTranslatef(-10,0,0);
        //glRotatef(90, 1, 0, 0);
        //glRotatef(90, 0, 1, 0);
        //glScalef(0.05,0.05,0.05);
        //drawBombillo();
        drawEstructura();
     glPopMatrix();
}
//**************************************************************************************************
void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//-------------------------------elementos del spot---------------------------------------------------------------------
  GLfloat mat_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat diffuseMaterial1[] = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat lmodel_ambient1[] = { Luz, Luz, Luz, Luz };

  GLfloat lightColor1[] = {1, 1, 0, 0}; //Blanca

  GLfloat lightPos1[] = {rX, rY, rZ, 1};

  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
  glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial1);
  //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
  glMaterialf(GL_FRONT, GL_SHININESS, 65.0f);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient1);

   GLfloat spot_direction[] = { dx, dy, dz };
   glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0); //Grados
   glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
   glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
   //printf("dx=%d dy=%d dz=%d \n", dx, dy, dz);
   // ============= LUZ

//----------------------------------------------------------------------------------------------------------------------
//-------------------------------elementos del spot del helicoptero---------------------------------------------------------------------
  GLfloat mat_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat diffuseMaterial2[] = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat lmodel_ambient2[] = { Luz, Luz, Luz, Luz };

  GLfloat lightColor2[] = {1, 1, 0, 0}; //Blanca

  GLfloat lightPos2[] = {rX2, rY2, rZ2 , 1};
  //GLfloat lightPos2[] = {RotacionH, TransH, Hz, 1};
        //glRotatef(RotacionH, 0, 1, 0);
        //glTranslatef(0,TransH, 0);

  glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
  glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial2);
  //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
  glMaterialf(GL_FRONT, GL_SHININESS, 65.0f);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient1);

   GLfloat spot_direction2[] = { dx2, dy2, dz2 };
   glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0); //Grados
   glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);
   glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
   //printf("dx=%d dy=%d dz=%d \n", dx, dy, dz);
   // ============= LUZ

//----------------------------------------------------------------------------------------------------------------------
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat diffuseMaterial[] = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat lmodel_ambient[] = { Luz, Luz, Luz, Luz };

  GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
//  GLfloat lightPos[] = {-2 * LIGHT_POS , LIGHT_POS , 4 * LIGHT_POS , 1.0f};
  GLfloat lightPos[] = {LIGHT_POS/2, LIGHT_POS, LIGHT_POS/2, 0};

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(0, 0, -40); //Aleja la imagen hacia atrás
  glRotatef(30, 1, 0, 0);

  glScalef(Zoom, Zoom, Zoom);

  glRotatef(spinX, 1, 0, 0);
  glRotatef(spinY, 0, 1, 0);

  glRotatef(RotEscene, 0, -1, 0);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

  glPushMatrix();
    glColor4ub(255, 255, 0, 0);
    glTranslatef(0, LIGHT_POS, 0);
    glutSolidSphere(0.3, 50, 50);
  glPopMatrix();

  //-----------------
  glPushMatrix(); //Bombillo
    glColor4ub(255, 255, 0, 1);
    glTranslatef(rX, rY, rZ);
    glutSolidSphere(0.3, 50, 50);
  glPopMatrix();
  //----------------------

  //-----------------
  /*
  glPushMatrix(); //Helicoptero
        glRotatef(RotacionH, 0, 1, 0);
        glTranslatef(0,TransH, 0);
        glTranslatef(-5,0.2,-3); //x, y, z

        glTranslatef(rX2, rY2, rZ2);
        //glTranslatef(10,-5, 12);//coordenadas del helicoptero linea 534
        glColor4ub(226, 192, 236, 1);
        //glTranslatef(RotacionH, TransH, 0);
        glutSolidSphere(0.3, 50, 50);
  glPopMatrix();
  */
  //----------------------
  glPushMatrix();
    glTranslatef(0, BOX_HEIGHT, 0);
    //Aquí debe llamar a los objetos
    drawTrompo();
    drawTeaPot();
    //new
    //drawTrompo2();
    drawHelicopter();
    drawBall();
    drawCopa();
    drawSombrilla();
    drawBanco();
    drawCopa2();
    drawMesa();
    drawFoto();
    drawMesaConTransparencia();
    drawFlower();
    drawLampara();
  glPopMatrix();

  glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
  glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
  glDisable(GL_DEPTH_TEST); //Disable depth testing
  glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass

  //Make pixels in the stencil buffer be set to 1 when the stencil test passes
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

  //Aquí se dibuja el piso
  drawFloor();

  glColorMask(1, 1, 1, 1);
  glEnable(GL_DEPTH_TEST);

  //Make the stencil test pass only when the pixel is 1 in the stencil buffer
  glStencilFunc(GL_EQUAL, 1, 1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change

  glPushMatrix();
    glScalef(1, -1, 1);
    glTranslatef(0, BOX_HEIGHT, 0);
    //Aquí se dibujan los objetos que se van a reflejar
    drawTrompo();
    drawTeaPot();
    drawHelicopter();
    //drawTrompo2();
    drawBall();
    drawCopa();
    drawSombrilla();
    drawBanco();
    drawCopa2();
    drawMesa();
    drawFoto();
    drawMesaConTransparencia();
    drawFlower();
    drawLampara();
    //----------- lampara
    glPushMatrix();
        glColor4ub(255, 255, 0, 1);
        glTranslatef(rX, rY-7.5, rZ);
        glutSolidSphere(0.3, 50, 50);
    glPopMatrix();
    //---------------------------------
    //----------- helicoptero
     /*
     glPushMatrix(); //Helicoptero
        /*
        glRotatef(RotacionH, 0, 1, 0);
        glTranslatef(0,TransH, 0);
        glTranslatef(-5,0.2 - 7.5,-3); //x, y, z
        glTranslatef(Hx, Hy, Hz);

        //glTranslatef(rX2, rY2-7.5, rZ2);
        glTranslatef(rX2, rY2, rZ2);
        //glTranslatef(10,-5, 12);//coordenadas del helicoptero linea 534
        glColor4ub(226, 192, 236, 1);
        //glTranslatef(RotacionH, TransH, 0);
        glutSolidSphere(0.3, 50, 50);
    glPopMatrix();
    */
    /* original
    glPushMatrix();
        glColor4ub(226, 192, 236, 1);
        glTranslatef(Hx, Hy-7.5, Hz);
        glutSolidSphere(0.3, 50, 50);
    glPopMatrix();
    */
    //---------------------------------
  glPopMatrix();
  glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
  //Blend the floor onto the screen
  glEnable(GL_BLEND);
  //Aquí se dibuja el piso que refleja
  drawFloor();
  glDisable(GL_BLEND);

  glutSwapBuffers();
}
void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {
    case 27: //Escape key
         exit(0);
    break;
    case 'x': //Posición de la luz
         Inclinacion = 30;
         Control = 1;
    break;

    case 'F': //Posición de la luz
        ++LIGHT_POS;
    break;
    case 'f': //Posición de la luz
        --LIGHT_POS;
    break;
    case 'r': //La esfera gira
         if (Rot == 1)
             Rot = 0;
         else
             Rot = 1;
    break;
    case 'l': //Luz
         Luz -= 0.01;
         if (Luz < 0)
             Luz = 1;
    break;
    case 'z':
        if (Zoom > 0)
            Zoom -= 0.01;
    break;
    case 'Z':
        if (Zoom < 10)
            Zoom += 0.01;
    break;
    //----------------------Movimientos en la bola------------------------------------------
    case 'b':
        if (RotB == 1)
            RotB = 0;
        else
            RotB = 1;
    break;
    case 'B':
        if (RebBall == 1){
            TranslateBall2 = 0;
            RebBall = 0;
            NumRebBall=4;
            direccionBall=1;
        }
        else
            RebBall = 1;
    break;
    //---------------------- FIN Movimientos en la bola------------------------------------------
    //----------------------Movimientos en el helicotero------------------------------------------
    case 'h':
        /*
        if (RotH == 1){
            RotH=0;
        }

        else
            RotH = 1;
        */
        animacion2 = true;
        girarH2 = true;
    break;
    case 's':
        if (laserContol == 1){
            laserContol=0;
        }
        else
            laserContol = 1;
    break;
    case 'd':
        //metodo de disparo bolas
    break;
    //---------------------- FIN Movimientos en el helicoptero------------------------------------------
    case 'p':
        if (Trompo == 0)
            Trompo = 1;
        else
            Trompo = 0;
    break;

    case 't': //Sube
         if (++Transparencia > 255)
             Transparencia = 0;
    break;
    case 'j':
        if (roteT == 1){
            roteT=0;
        }
        else
            roteT = 1;
    break;
  }
}
void handleSpecialKeypress(int key, int x, int y) {
 switch (key) {
    case GLUT_KEY_LEFT:
         isLeftKeyPressed = true;
         if (!isRightKeyPressed) {
             if(rX > -25)
                --rX;
         }
    break;
    case GLUT_KEY_RIGHT:
         isRightKeyPressed = true;
         if (!isLeftKeyPressed) {
             if (rX < 25)
                ++rX;
         }
    break;
    case GLUT_KEY_UP:
         isUpKeyPressed = true;
         if (!isDownKeyPressed) {
             if (rY < 25)
                ++rY;
         }
    break;
    case GLUT_KEY_DOWN:
         isDownKeyPressed = true;
         if (!isUpKeyPressed) {
             if (rY > 0)
                --rY;
         }
    break;
 }
}
void handleSpecialKeyReleased(int key, int x, int y) {
 switch (key) {
     case GLUT_KEY_LEFT:
          isLeftKeyPressed = false;
     break;
     case GLUT_KEY_RIGHT:
          isRightKeyPressed = false;
     break;
     case GLUT_KEY_UP:
          isUpKeyPressed = false;
     break;
     case GLUT_KEY_DOWN:
          isDownKeyPressed = false;
     break;
 }
}
void init() {
  glClearColor(0, 0, 0, 0); //Fondo negro en toda la escena
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //Carga los archivos con las texturas
  //Cambio de dirección
  //D:\OneDrive\Escritorio\GraficosPorComputadora\ejercicio06
  if(!cargarTGA("D:/OneDrive/Escritorio/GraficosPorComputadora/ejercicio06/piso3.tga", &texturas[0]) ||
     !cargarTGA("D:/OneDrive/Escritorio/GraficosPorComputadora/ejercicio06/Star.tga", &texturas[1])||
     !cargarTGA("D:/OneDrive/Escritorio/GraficosPorComputadora/ejercicio06/Bola.tga", &texturas[2]) ||
     !cargarTGA("D:/OneDrive/Escritorio/GraficosPorComputadora/ejercicio06/alina2.tga", &texturas[3])
     ) {
              printf("Error cargando texturas\n");
     exit(0); // Cargamos las texturas y chequeamos por errores
	}
}
void handleResize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}
void spinDisplay(void) {
    GLfloat r;
    GLfloat h;
   // Movimiento de translación sobre el piso en espira
   if(roteT==1){
        if (Angulo < 25) {
           Angulo += 0.002;
        }
           //Espiral de Bernoulli (logaritmica)
           r = 12 - pow (2.7182, 0.1 * Angulo);
           if (0 < r) {
               tx = r * cos (Angulo);
               tz = r * sin (Angulo);
               //printf("r = %6.4f ang = %5.2f x=%5.2f z=%5.2f\n", r, Angulo, x, z);
           }
   }
   //Controla la rotación del trompo sobre su eje
   //if (Inclinacion > 0){
           Rotacion += 0.5;
           if (Rotacion >= 360) {
               Rotacion = 0;
           }
   //}
   //VelocRotacion -= 0.1;
   if (Control == 1) {
       Inclinacion -= VelocInclinacion;
       if (Inclinacion <= 0) {
           Control = 0;
           //VelocInclinacion = -1 * VelocInclinacion;
           Inclinacion = 0;
       }
   }
    if (Rot == 1) {
        RotEscene += 0.05;
    }
    if (RotB == 1) {
        if(direccionBall == 1){
            RotBall += 0.5;
            TranslateBall += 0.01;
            if(TranslateBall >= 9){
                TranslateBall=9;
                direccionBall=2;
            }
        }
        if(direccionBall == 2){
            RotBall -= 0.5;
            TranslateBall -= 0.01;
            if(TranslateBall <= 0){
                TranslateBall=0;
                direccionBall=1;
            }
        }
    }
    if(RebBall == 1){
        if(NumRebBall == 4){
             if(direccionBall == 1){
                TranslateBall2 += 0.05;
                if(TranslateBall2 >= 10){
                    direccionBall=2;
                }
             }
             if(direccionBall == 2){
                TranslateBall2 -= 0.05;
                if(TranslateBall2 <= 0){
                    direccionBall=1;
                    NumRebBall=3;
                }
             }
        }
        if(NumRebBall == 3){
             if(direccionBall == 1){
                TranslateBall2 += 0.05;
                if(TranslateBall2 >= 8){
                    direccionBall=2;
                }
             }
             if(direccionBall == 2){
                TranslateBall2 -= 0.05;
                if(TranslateBall2 <= 0){
                    direccionBall=1;
                    NumRebBall=2;
                }
             }
        }
        if(NumRebBall == 2){
             if(direccionBall == 1){
                TranslateBall2 += 0.05;
                if(TranslateBall2 >= 6){
                    direccionBall=2;
                }
             }
             if(direccionBall == 2){
                TranslateBall2 -= 0.05;
                if(TranslateBall2 <= 0){
                    direccionBall=1;
                    NumRebBall=1;
                }
             }
        }
        if(NumRebBall == 1){
             if(direccionBall == 1){
                TranslateBall2 += 0.05;
                if(TranslateBall2 >= 4){
                    direccionBall=2;
                }
             }
             if(direccionBall == 2){
                TranslateBall2 -= 0.05;
                if(TranslateBall2 <= 0){
                    direccionBall=1;
                    NumRebBall=0;
                }
             }
        }
        if(NumRebBall == 0){
            RebBall=0;
            NumRebBall=4;
        }
    }
    if (RotH == 1) {
        if(TransH >= 8){
            RotacionH+=0.2;
        }else{
            TransH+=0.1;
        }

    }
    if (RotH == 0 && TransH > 0) {
            RotacionH+=0.06;
            TransH-=0.01;
    }
    animacionH();
   glutPostRedisplay(); //Vuelve a dibujar
}
void mouse(int button, int state, int x, int y) {
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN) {
            glutIdleFunc(spinDisplay);
            Inclinacion = 30;
         }
         break;
      case GLUT_RIGHT_BUTTON:
      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}
void mouseMotion(int x, int y) {
     spinX = y;
     spinY = x;
     //printf("X %5.2f Y %5.2f\n", spinX, spinY);
}
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowSize(600, 600);

  glutCreateWindow("Sala de Juegos -> Alina Reyes Vargas");
  init();

  glutDisplayFunc(drawScene);
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);
  glutMouseFunc(mouse); //Activa los controles del mouse
  glutMotionFunc(mouseMotion);
  glutSpecialFunc(handleSpecialKeypress);
  glutSpecialUpFunc(handleSpecialKeyReleased);
  glutMainLoop();

  return 0;
}
