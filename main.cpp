#include <iostream>
#include <stdlib.h> //Needed for "exit" function

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;
/*
 * Serpinski_rec_2.c
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>	// OpenGL Graphics Utility Library

// Number of step
int CurrentNum = 0;
const int MaxNum = 10;

// These variables set the dimensions of the rectanglar region we wish to view.
const double Xmin = -0.1, Xmax = 1.1;
const double Ymin = -0.1, Ymax = 1.1;

// glutKeyboardFunc is called below to set this function to handle
//		all "normal" ascii key presses.
// Only space bar and escape key have an effect.
void myKeyboardFunc( unsigned char key, int x, int y )
{
        switch ( key ) {

        case ' ':									// Space bar
                // Increment the current step number, and tell operating system screen needs redrawing
                CurrentNum = (CurrentNum+1)%MaxNum;
                glutPostRedisplay();
                break;

        case 27:									// "27" is theEscape key
                exit(1);

        }
}


void drawFractal(int num)
{
 switch(num) {
   case 0:
                glBegin( GL_QUADS );
                glVertex3f( 1.0, 0.0, 0.0 );
                glVertex3f( 1.0, 0.2, 0.0 );
                glVertex3f( 0.0, 0.2, 0.0 );
                glVertex3f( 0.0, 0.0, 0.0 );
                glEnd();
                glBegin( GL_QUADS );
                glVertex3f( 0.5, 0.0, 0.0 );
                glVertex3f( 0.5, 1.0, 0.0 );
                glVertex3f( 0.0, 1.0, 0.0 );
                glVertex3f( 0.0, 0.0, 0.0 );
                glEnd();
        break;
   default:
        //Draw four L's
        //1|2
        //3|4
        glPushMatrix();
        glPushMatrix();
        glPushMatrix();
        //First L
        glColor3f(1,0,0);
        glTranslatef(0.5,1.0,0.0);
        glRotatef(90,0,0,1);
        glScalef(-0.5,0.5,1.0);
        drawFractal(num - 1);
        glPopMatrix();
        //Second L
        glColor3f(0,1,0);
        glTranslatef(0.5,0.5,0.0);
        glRotatef(-90,0,0,1);
        glScalef(-0.5,0.5,0.5);
        drawFractal(num - 1);
        glPopMatrix();
        //Third L
        glColor3f(1,1,0);
        glTranslatef(0.5,0.5,0.0);
        glRotatef(180,0,0,1);
        glScalef(0.25,0.25,0.25);
        drawFractal(num - 1);
        //Fourth L
        glColor3f(0,0,1);
        glPopMatrix ();
        glTranslatef(0.5,0.0,0.0);
        glScalef(0.5,0.5,0.5);
        drawFractal(num - 1);
        break;
 }
}

/*
 * drawScene() handles the animation and the redrawing of the
 *		graphics window contents.
 */
void drawScene(void)
{
        // Clear the rendering window

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor (1.0,1.0,1.0,0.0);

        // Set drawing color to white
        glColor3f(0.0, 0.0, 0.0 );

    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    drawFractal(CurrentNum);

 // Flush the pipeline.  (Not usually necessary.)
        glFlush();
}

// Initialize OpenGL's rendering modes
void initRendering()
{

        glEnable ( GL_DEPTH_TEST );
        glClearColor (1.0,1.0,1.0,0.0);

        // Uncomment out the first block of code below, and then the second block,
        //		to see how they affect line and point drawing.
/*
        // The following commands should cause points and line to be drawn larger
        //	than a single pixel width.
        glPointSize(8);
        glLineWidth(5);
*/

/*
        // The following commands should induce OpenGL to create round points and
        //	antialias points and lines.  (This is implementation dependent unfortunately).
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// Make round points, not square points
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialias the lines
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/

}

// Called when the window is resized
//		w, h - width and height of the window in pixels.
void resizeWindow(int w, int h)
{
        double scale, center;
        double windowXmin, windowXmax, windowYmin, windowYmax;

        // Define the portion of the window used for OpenGL rendering.
        glViewport( 0, 0, w, h );	// View port uses whole window

        // Set up the projection view matrix: orthographic projection
        // Determine the min and max values for x and y that should appear in the window.
        // The complication is that the aspect ratio of the window may not match the
        //		aspect ratio of the scene we want to view.
        w = (w==0) ? 1 : w;
        h = (h==0) ? 1 : h;
        if ( (Xmax-Xmin)/w < (Ymax-Ymin)/h ) {
                scale = ((Ymax-Ymin)/h)/((Xmax-Xmin)/w);
                center = (Xmax+Xmin)/2;
                windowXmin = center - (center-Xmin)*scale;
                windowXmax = center + (Xmax-center)*scale;
                windowYmin = Ymin;
                windowYmax = Ymax;
        }
        else {
                scale = ((Xmax-Xmin)/w)/((Ymax-Ymin)/h);
                center = (Ymax+Ymin)/2;
                windowYmin = center - (center-Ymin)*scale;
                windowYmax = center + (Ymax-center)*scale;
                windowXmin = Xmin;
                windowXmax = Xmax;
        }

        // Now that we know the max & min values for x & y that should be visible in the window,
        //		we set up the orthographic projection.
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( windowXmin, windowXmax, windowYmin, windowYmax, -1, 1 );

}


// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
        glutInit(&argc,argv);

        // The image is not animated so single buffering is OK.
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );

        // Window position (from top corner), and size (width and hieght)
        glutInitWindowPosition( 20, 60 );
        glutInitWindowSize( 500, 500 );
        glutCreateWindow( "SimpleDraw - Press space bar to toggle images" );

        // Initialize OpenGL as we like it..
        initRendering();

        // Set up callback functions for key presses
        glutKeyboardFunc( myKeyboardFunc );			// Handles "normal" ascii symbols
        // glutSpecialFunc( mySpecialKeyFunc );		// Handles "special" keyboard keys

        // Set up the callback function for resizing windows
        glutReshapeFunc( resizeWindow );

        // Call this for background processing
        // glutIdleFunc( myIdleFunction );

        // call this whenever window needs redrawing
        glutDisplayFunc( drawScene );

        fprintf(stdout, "Press space bar for the next step; escape button to quit.\n");

        // Start the main loop.  glutMainLoop never returns.
        glutMainLoop(  );

        return(0);	// This line is never reached.
}

