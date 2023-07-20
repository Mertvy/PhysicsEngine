//
// Created by Alex on 7/20/2023.
//

#include <GL/glut.h>


int main(int argc, char**argv){
    //initialize
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(500,500);
    glutInitWindowSize(500,500);

    glutCreateWindow("New Window");

    //callback

    //loop
    glutMainLoop();
}