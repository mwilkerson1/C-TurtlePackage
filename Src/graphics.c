#include "graphics.h"
#include "sprite.h"
#include "text.h"
#include "utilities.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

// Constants
#define IMG_W 50.0f
#define IMG_H 50.0f

// Texture IDs
GLuint spriteTextureID = 0;

// Lines array
typedef struct {
    GLfloat x1, y1, x2, y2;   // Coordinates of the line
    GLfloat r, g, b;          // Color of the line (RGB components)
} Line;

Line* lines = NULL;
int lineCapacity = 50;
int lineCount = 0;

void setup_opengl(int windowWidth, int windowHeight) {
    // Set the viewport
    glViewport(0, 0, windowWidth, windowHeight);

    // Set up the projection matrix for orthographic 2D rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, windowHeight, 0.0);

    // Set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the clear color to white background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Allocate memory for lines array
    lines = malloc(lineCapacity * sizeof(Line));
    if (!lines) {
        printf("Error allocating memory for lines!\n");
        exit(1);
    }
}

bool load_sprite(const char* bmp) {
    // Load the image using SDL_image
    SDL_Surface* tempSurface = IMG_Load(bmp);
    if (!tempSurface) {
        printf("Error loading image %s: %s\n", bmp, IMG_GetError());
        return false;
    }

    // Convert the surface to a format suitable for OpenGL texture
    SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(tempSurface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(tempSurface);

    if (!formattedSurface) {
        printf("Error converting surface: %s\n", SDL_GetError());
        return false;
    }

    // Generate a texture ID and bind it
    glGenTextures(1, &spriteTextureID);
    glBindTexture(GL_TEXTURE_2D, spriteTextureID);

    // Set pixel storage mode
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Set texture parameters after binding the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload the texture data to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formattedSurface->w, formattedSurface->h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, formattedSurface->pixels);
    checkOpenGLError("glTexImage2D");

    // Free the surface as we no longer need it
    SDL_FreeSurface(formattedSurface);

    return true;
}

void render_scene(int windowWidth, int windowHeight) {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    checkOpenGLError("glClear");

    // Reset OpenGL state before rendering
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // **Line Rendering**

    // Disable texturing for line rendering
    glDisable(GL_TEXTURE_2D);

    // Draw all previously drawn lines
    if (lineCount > 0) {
        glBegin(GL_LINES);
        for (int i = 0; i < lineCount; i++) {
            glColor3f(lines[i].r, lines[i].g, lines[i].b);  // Set line color
            glVertex2f(lines[i].x1, lines[i].y1);           // Start point
            glVertex2f(lines[i].x2, lines[i].y2);           // End point
        }
        glEnd();
        checkOpenGLError("Drawing lines");
    }

    // **Sprite Rendering**

    // Enable texturing for sprite rendering
    glEnable(GL_TEXTURE_2D);

    // Reset color to white to avoid tinting the sprite
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    // Bind the texture before drawing
    glBindTexture(GL_TEXTURE_2D, spriteTextureID);

    // Calculate sprite corners
    float halfWidth = IMG_W / 2.0f;
    float halfHeight = IMG_H / 2.0f;

    float x = sprite.x;
    float y = sprite.y;

    // Set up vertices
    GLfloat vertices[] = {
        x - halfWidth, y - halfHeight,
        x + halfWidth, y - halfHeight,
        x + halfWidth, y + halfHeight,
        x - halfWidth, y + halfHeight
    };

    // Standard texture coordinates without flipping
    GLfloat texCoords[] = {
        0.0f, 0.0f,  // Bottom-left
        1.0f, 0.0f,  // Bottom-right
        1.0f, 1.0f,  // Top-right
        0.0f, 1.0f   // Top-left
    };

    // Apply rotation around the sprite's center
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(-sprite.angle, 0, 0, 1);  // Negative because OpenGL rotates counterclockwise
    glTranslatef(-x, -y, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    glDrawArrays(GL_QUADS, 0, 4);
    checkOpenGLError("glDrawArrays for sprite");

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();

    // **Text Rendering**

    // Construct the status string
    char statusText[256];
    sprintf(
        statusText,
        "Position: (%.1f, %.1f)\nAngle: %.1f degrees\nPen: %s\nLine Color: %s",
        sprite.x, sprite.y, sprite.angle,
        sprite.pen ? "Down" : "Up",
        (sprite.r == 0.0f && sprite.g == 0.0f && sprite.b == 0.0f) ? "Black" :
        (sprite.r == 0.0f && sprite.g == 0.0f && sprite.b == 1.0f) ? "Blue" :
        (sprite.r == 1.0f && sprite.g == 0.0f && sprite.b == 0.0f) ? "Red" :
        (sprite.r == 0.0f && sprite.g == 1.0f && sprite.b == 0.0f) ? "Green" :
        (sprite.r == 1.0f && sprite.g == 1.0f && sprite.b == 0.0f) ? "Yellow" :
        "Custom"
    );

    // Split the statusText into lines
    char* linesText[10];
    int lineCountText = 0;

    char* token = strtok(statusText, "\n");
    while (token != NULL && lineCountText < 10) {
        linesText[lineCountText++] = token;
        token = strtok(NULL, "\n");
    }

    // Set text color (black)
    SDL_Color textColor = {0, 0, 0, 255};

    // Variables for text position
    float textX = 10.0f;
    float textY = 10.0f;

    // Set up orthographic projection for text rendering
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, windowHeight, 0); // Top-left corner is (0,0)

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Enable blending and texturing
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    // Render each line
    for (int i = 0; i < lineCountText; i++) {
        int lineWidth = 0, lineHeight = 0;
        GLuint lineTextureID = render_text(linesText[i], textColor, &lineWidth, &lineHeight);

        if (lineTextureID != 0) {
            // Bind the text texture
            glBindTexture(GL_TEXTURE_2D, lineTextureID);

            // Set up vertices and texture coordinates
            GLfloat textVertices[] = {
                textX, textY + lineHeight,
                textX + lineWidth, textY + lineHeight,
                textX + lineWidth, textY,
                textX, textY
            };

            GLfloat textTexCoords[] = {
                0.0f, 1.0f,  // Bottom-left
                1.0f, 1.0f,  // Bottom-right
                1.0f, 0.0f,  // Top-right
                0.0f, 0.0f   // Top-left
            };

            // Render the textured quad
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glVertexPointer(2, GL_FLOAT, 0, textVertices);
            glTexCoordPointer(2, GL_FLOAT, 0, textTexCoords);

            glDrawArrays(GL_QUADS, 0, 4);

            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);

            // Update textY for the next line
            textY += lineHeight + 2; // Add some spacing between lines

            // Delete the texture after rendering
            glDeleteTextures(1, &lineTextureID);
        }
    }

    // Restore matrices
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// Function to add a line to the lines array
void add_line(float x1, float y1, float x2, float y2) {
    if (lineCount >= lineCapacity) {
        lineCapacity *= 2;
        lines = realloc(lines, lineCapacity * sizeof(Line));
        if (!lines) {
            printf("Error reallocating memory for lines!\n");
            exit(1);
        }
    }

    // Set line coordinates
    lines[lineCount].x1 = x1;
    lines[lineCount].y1 = y1;
    lines[lineCount].x2 = x2;
    lines[lineCount].y2 = y2;

    // Set line color from current sprite color
    lines[lineCount].r = sprite.r;
    lines[lineCount].g = sprite.g;
    lines[lineCount].b = sprite.b;

    lineCount++;
}
