#include <stdio.h>
#include <string.h>

struct face{
    char * matrix[3][3];
};

struct cube{
    struct face F;
    struct face B;
    struct face L;
    struct face R;
    struct face D;
    struct face U;
};

/**    
 * fill(char * color, struct face * side) -> void
 *
 * Fills the face matrix with the given color (char).
*/
void fill(char * color, struct face * side){

    for (int i = 0 ; i<3; ++i){
        for (int j = 0; j<3; ++j){
            side->matrix[i][j] = color;
        }
    }
}

/**
 * init(struct cube * rubiks) -> void
 * 
 * Initializes a given cube struct to the default rubik's cube colors.
 * The front face will be the color yellow.
*/
void init(struct cube * rubiks){
    fill("R", &rubiks->U);
    fill("B", &rubiks->R);
    fill("G", &rubiks->L);
    fill("Y", &rubiks->F);
    fill("W", &rubiks->B);
    fill("O", &rubiks->D);
}

/**
 * print_cube(struct cube * rubiks) -> void
 * 
 * Prints the whole cube given cube struct.
 * Prints the top and bottom face vertically aligned with the front face.
 * Prints Back, Left, Front, and Right faces in order.
 * Example print of a default cube:
 * 
 * struct cube r;
 * init(&r);
 * print_cube(&r);
 * >>>
 *                R R R
 *                R R R
 *                R R R
 *  W W W  G G G  Y Y Y  B B B
 *  W W W  G G G  Y Y Y  B B B
 *  W W W  G G G  Y Y Y  B B B
 *                O O O
 *                O O O
 *                O O O
 *   
*/
void print_cube(struct cube * rubiks){
    for (int i = 0; i < 3; ++i){                        // Print top face
        for (int j = 0; j < 14; ++j){
            printf(" ");
        }
        for (int k = 0; k < 3; ++ k){
            printf("%s ", rubiks->U.matrix[i][k]);
        }
        printf("\n");
    }

    for (int i = 0; i < 3; ++i){                        // Prints Back, Left, Front, and Right faces
        for (int k = 0; k < 3; ++ k){
            printf("%s ", rubiks->B.matrix[i][k]);
        }
        printf(" ");
        for (int k = 0; k < 3; ++ k){
            printf("%s ", rubiks->L.matrix[i][k]);
        }
        printf(" ");
        for (int k = 0; k < 3; ++ k){
            printf("%s ", rubiks->F.matrix[i][k]);
        }
        printf(" ");
        for (int k = 0; k < 3; ++ k){
            printf("%s ", rubiks->R.matrix[i][k]);
        }
        printf("\n");
    }

    for (int i = 0; i < 3; ++i){                        // Prints Down (Bottom) face
        for (int j = 0; j < 14; ++j){
            printf(" ");
        }
        for (int k = 0; k < 3; ++ k){
            printf("%s ", rubiks->D.matrix[i][k]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * face_clockwise(struct face * this_face) -> void
 * 
 * Turns a face clockwise by turning the edges and corners clockwise.
 * 
 * The temporary array represents the default positions of the corner or edge.
 * (i.e for corners, the default positions are [00, 02, 22, 20])
 * The edges and corners are saved in the temporary array in clockwise order.
 * Then we reassign the corners and edges in default order using the temporary array.
 * Since the temporary array is in clockwise shift, the reassignment would
 * indicate a clockwise shift.
*/
void face_clockwise(struct face * this_face){
    char * face_corners[4];
    char * face_edges[4];

    // Rotate Corners

    face_corners[0] = this_face->matrix[2][0];
    face_corners[1] = this_face->matrix[0][0];
    face_corners[2] = this_face->matrix[0][2];
    face_corners[3] = this_face->matrix[2][2];

    this_face->matrix[0][0] = face_corners[0];
    this_face->matrix[0][2] = face_corners[1];
    this_face->matrix[2][2] = face_corners[2];
    this_face->matrix[2][0] = face_corners[3];

    // Rotate the edges

    face_edges[0] = this_face->matrix[1][0];
    face_edges[1] = this_face->matrix[0][1];
    face_edges[2] = this_face->matrix[1][2];
    face_edges[3] = this_face->matrix[2][1];

    this_face->matrix[0][1] = face_edges[0];
    this_face->matrix[1][2] = face_edges[1];
    this_face->matrix[2][1] = face_edges[2];
    this_face->matrix[1][0] = face_edges[3];
}

/**
 * face_counter_clockwise(struct face * this_face) -> void
 * 
 * Turns a face counter-clockwise by turning the edges and corners counter-clockwise.
 * 
 * The temporary array represents the default positions of the corner or edge.
 * (i.e for corners, the default positions are [00, 02, 22, 20])
 * The edges and corners are saved in the temporary array in counter-clockwise order.
 * Then we reassign the corners and edges using the temporary array.
 * Since the temporary array is in counter-clockwise shift, the reassignment would
 * indicate a counter-clockwise shift.
*/
void face_counter_clockwise(struct face * this_face){
    char * face_corners[4];
    char * face_edges[4];

    face_corners[0] = this_face->matrix[0][2];
    face_corners[1] = this_face->matrix[2][2];
    face_corners[2] = this_face->matrix[2][0];
    face_corners[3] = this_face->matrix[0][0];

    this_face->matrix[0][0] = face_corners[0];
    this_face->matrix[0][2] = face_corners[1];
    this_face->matrix[2][2] = face_corners[2];
    this_face->matrix[2][0] = face_corners[3];

    // Rotate the edges

    face_edges[0] = this_face->matrix[1][2];
    face_edges[1] = this_face->matrix[2][1];
    face_edges[2] = this_face->matrix[1][0];
    face_edges[3] = this_face->matrix[0][1];

    this_face->matrix[0][1] = face_edges[0];
    this_face->matrix[1][2] = face_edges[1];
    this_face->matrix[2][1] = face_edges[2];
    this_face->matrix[1][0] = face_edges[3];
}

/**
 * U(struct cube * rubiks) -> void
 * 
 * Moves the Up Face of the cube clockwise.
 * 
 * We do the U move by shifting the first layer clockwise.
 * This is based on how the cube is printed where the Back (B), Left (L), Front (F), and the Right (R)
 * faces are printed in that order. When executing the U move, we shift the top layer to the left (in accordance of how its printed).
 * The colors on B would be on R, R would be on F, F would be on L, and L would be on B.  
 * A temporary array is created where the index of the array is fixed to the default face.
 * i.e. [B, L, F, R]
 * 
 * We store the new order we want in this temporary array (i.e [L, F, R, B]).
 * Then we store this new order in the original cube.  
 * Lastly, the top layer would be rotated clockwise using the face_clockwise() function.
*/
void U(struct cube * rubiks){
    char * top_row_temp[4][3];
    int top_layer = 0;

    // Assign the temporary array in a clockwise rotation.
    for (int j = 0; j < 3; ++j){
        top_row_temp[0][j] = rubiks->L.matrix[top_layer][j];
        top_row_temp[1][j] = rubiks->F.matrix[top_layer][j];
        top_row_temp[2][j] = rubiks->R.matrix[top_layer][j];
        top_row_temp[3][j] = rubiks->B.matrix[top_layer][j];
    }
    
    // Reassign the default positions to the new one. 
    for (int i = 0; i < 3; ++i){
        rubiks->B.matrix[top_layer][i] = top_row_temp[0][i];
        rubiks->L.matrix[top_layer][i] = top_row_temp[1][i];
        rubiks->F.matrix[top_layer][i] = top_row_temp[2][i];
        rubiks->R.matrix[top_layer][i] = top_row_temp[3][i];
    }

    // Rotates the top face of the cube.
    face_clockwise(&rubiks->U);
}

/**
 * U_prime(struct cube * rubiks) -> void
 * 
 * Moves the Up Face of the cube counter-clockwise.
 * 
 * We do the U move by shifting the first layer counter-clockwise.
 * This is based on how the cube is printed where the Back (B), Left (L), Front (F), and the Right (R)
 * faces are printed in that order. When executing the U' move, we shift the top layer to the right (in accordance of how its printed).
 * The colors on B would be on L, L would be on F, F would be on R, and R would be on B.  
 * A temporary array is created where the index of the array is fixed to the default face.
 * i.e. [B, L, F, R]
 * 
 * We store the new order we want in this temporary array (i.e [R, B, L, F]).
 * Then we store this new order in the original cube.  
 * Lastly, the top layer would be rotated counter-clockwise using the face_counter_clockwise() function.
*/
void U_prime(struct cube * rubiks){
    char * top_row_temp[4][3];
    int top_layer = 0;

    // Assign the temporary array in a counter-clockwise rotation.
    for (int j = 0; j < 3; ++j){
        top_row_temp[0][j] = rubiks->R.matrix[top_layer][j];
        top_row_temp[1][j] = rubiks->B.matrix[top_layer][j];
        top_row_temp[2][j] = rubiks->L.matrix[top_layer][j];
        top_row_temp[3][j] = rubiks->F.matrix[top_layer][j];
    }

    // Reassign the default positions to the new one.  
    for (int i = 0; i < 3; ++i){
        rubiks->B.matrix[top_layer][i] = top_row_temp[0][i];
        rubiks->L.matrix[top_layer][i] = top_row_temp[1][i];
        rubiks->F.matrix[top_layer][i] = top_row_temp[2][i];
        rubiks->R.matrix[top_layer][i] = top_row_temp[3][i];
    }

    // Rotates the top face of the cube.
    face_counter_clockwise(&rubiks->U);
}

/**
 * D(struct cube * rubiks) -> void
 * 
 * Moves the Down Face of the cube clockwise.
 * 
 * Similar to the U_prime(struct cube * rubiks) function, we are dealing with the bottom layer
 * of the cube.
 * 
 * The moves U' and D are aligned thus the only change here is that we are using the last row of the matrix
 * and the bottom face moves clockwise rather than counter-clockwise.
*/
void D(struct cube * rubiks){
    char * bottom_row_temp[4][3];
    int bottom_layer = 2;

    // Assign the temporary array in a counter-clockwise rotation.
    for (int j = 0; j < 3; ++j){
        bottom_row_temp[0][j] = rubiks->R.matrix[bottom_layer][j];
        bottom_row_temp[1][j] = rubiks->B.matrix[bottom_layer][j];
        bottom_row_temp[2][j] = rubiks->L.matrix[bottom_layer][j];
        bottom_row_temp[3][j] = rubiks->F.matrix[bottom_layer][j];
    }

    // Reassign the default positions to the new one.  
    for (int i = 0; i < 3; ++i){
        rubiks->B.matrix[bottom_layer][i] = bottom_row_temp[0][i];
        rubiks->L.matrix[bottom_layer][i] = bottom_row_temp[1][i];
        rubiks->F.matrix[bottom_layer][i] = bottom_row_temp[2][i];
        rubiks->R.matrix[bottom_layer][i] = bottom_row_temp[3][i];
    }

    // Rotates the bottom face of the cube
    face_clockwise(&rubiks->D);
}

/**
 * D_prime(struct cube * rubiks) -> void
 * 
 * Moves the Down Face of the cube counter-clockwise.
 * 
 * Similar to the U(struct cube * rubiks) function, we are dealing with the bottom layer
 * of the cube.
 * 
 * The moves U and D' are aligned thus the only change here is that we are using the last row of the matrix
 * and the bottom face moves counter-clockwise rather than clockwise.
*/
void D_prime(struct cube * rubiks){
    char * bottom_row_temp[4][3];
    int bottom_layer = 2;

    // Assign the temporary array in a counter-clockwise rotation.
    for (int j = 0; j < 3; ++j){
        bottom_row_temp[0][j] = rubiks->L.matrix[bottom_layer][j];
        bottom_row_temp[1][j] = rubiks->F.matrix[bottom_layer][j];
        bottom_row_temp[2][j] = rubiks->R.matrix[bottom_layer][j];
        bottom_row_temp[3][j] = rubiks->B.matrix[bottom_layer][j];
    }
 
    // Reassign the default positions to the new one.
    for (int i = 0; i < 3; ++i){
        rubiks->B.matrix[bottom_layer][i] = bottom_row_temp[0][i];
        rubiks->L.matrix[bottom_layer][i] = bottom_row_temp[1][i];
        rubiks->F.matrix[bottom_layer][i] = bottom_row_temp[2][i];
        rubiks->R.matrix[bottom_layer][i] = bottom_row_temp[3][i];
    }

    // Rotates the bottom face of the cube
    face_counter_clockwise(&rubiks->D);

}

/**
 * L(struct cube * rubiks) -> void
 * 
 * Moves the Left Face of the cube clockwise.
 * 
 * Implementation is similar to that of the Up face except we are rotating the Up (U), Front (F), D (Down), and Back (B) columns.
 * However, the back face's right column is the column touching the left side of the cube. When copying the colors to the 
 * temporary array, we have to take the right column rather then the left. This is also the reason why colors entering 
 * and leaving the back face need to be inverted.
 * 
 * The default order of faces for the temporary array is [U, F, D, B].
 * 
*/
void L(struct cube * rubiks){
    char * left_rotate[4][3];
    int left_layer = 0;

    // Rotates left side of the cube. The back is mirrored so it's the right side (2) that goes through rotation.
    // left_rotate array represents the position on the cube [U, F, D, B]. When we rotate we insert the color
    // or array we want to put into the position. 

    // Assign the temporary array in a counter-clockwise rotation.
    for (int j = 0; j < 3; ++j){
        left_rotate[0][j] = rubiks->B.matrix[j][2];
        left_rotate[1][j] = rubiks->U.matrix[j][left_layer];
        left_rotate[2][j] = rubiks->F.matrix[j][left_layer];
        left_rotate[3][j] = rubiks->D.matrix[j][left_layer];
    }

    // Reassign the default positions to the new one.  
    for (int j = 0; j < 3; ++j){
        rubiks->U.matrix[j][left_layer] = left_rotate[0][-j+2];
        rubiks->F.matrix[j][left_layer] = left_rotate[1][j];
        rubiks->D.matrix[j][left_layer] = left_rotate[2][j];
        rubiks->B.matrix[j][2] = left_rotate[3][-j+2];
    }
    face_clockwise(&rubiks->L);
}

/**
 * L_prime(struct cube * rubiks) -> void
 * 
 * Moves the Left Face of the cube counter-clockwise.
 * 
 * Implementation is similar to moving the Cube clockwise except our temporary array stores the colors in counter-clockwise
 * order.
 * 
 * Any colors leaving and entering the back face are still inverted.
 * 
 * The default order of faces for the temporary array is [U, F, D, B].
*/
void L_prime(struct cube * rubiks){
    char * left_rotate[4][3];
    int left_layer = 0;

    // Assign the temporary array in a counter-clockwise rotation.
    for (int j = 0; j < 3; ++j){
        left_rotate[0][j] = rubiks->F.matrix[j][left_layer];
        left_rotate[1][j] = rubiks->D.matrix[j][left_layer];
        left_rotate[2][j] = rubiks->B.matrix[j][2];
        left_rotate[3][j] = rubiks->U.matrix[j][left_layer];
    }

    // Reassign the default positions to the new one.  
    for (int j = 0; j < 3; ++j){
        rubiks->U.matrix[j][left_layer] = left_rotate[0][j];
        rubiks->F.matrix[j][left_layer] = left_rotate[1][j];
        rubiks->D.matrix[j][left_layer] = left_rotate[2][-j+2];
        rubiks->B.matrix[j][2] = left_rotate[3][-j+2];
    }
    face_counter_clockwise(&rubiks->L);
}

/**
 * R(struct cube * rubiks) -> void
 * 
 * Moves the Right Face of the cube clockwise.
 * 
 * Similar to the L_prime(struct cube * rubiks) function, we are dealing with the right layer
 * of the cube.
 * 
 * The moves L' and R are aligned thus the only change here is that we are using the last column of the matrix.
 * 
 * The default order of faces for the temporary array is [U, F, D, B].
*/
void R(struct cube * rubiks){
    char * right_rotate[4][3];
    int right_layer = 2;

    // Rotates ride side of the cube. The back is mirrored so it's the left side (0) that goes through rotation.
    // right_rotate array represents the position on the cube [U, F, D, B]. When we rotate we insert the color
    // or array we want to put into the position. 

    // Assign the temporary array in a counter-clockwise rotation.
    for (int j = 0; j < 3; ++j){
        right_rotate[0][j] = rubiks->F.matrix[j][right_layer];
        right_rotate[1][j] = rubiks->D.matrix[j][right_layer];
        right_rotate[2][j] = rubiks->B.matrix[j][0];
        right_rotate[3][j] = rubiks->U.matrix[j][right_layer];
    }

    // Reassign the default positions to the new one.  
    for (int j = 0; j < 3; ++j){
        rubiks->U.matrix[j][right_layer] = right_rotate[0][j];
        rubiks->F.matrix[j][right_layer] = right_rotate[1][j];
        rubiks->D.matrix[j][right_layer] = right_rotate[2][-j+2];
        rubiks->B.matrix[j][0] = right_rotate[3][-j+2];
    }
    face_clockwise(&rubiks->R);
}

/**
 * R_prime(struct cube * rubiks) -> void
 * 
 * Moves the Right Face of the cube counter-clockwise.
 * 
 * Similar to the L(struct cube * rubiks) function, we are dealing with the right layer
 * of the cube.
 * 
 * The moves L and R' are aligned thus the only change here is that we are using the last column of the matrix.
 * 
 * The default order of faces for the temporary array is [U, F, D, B].
*/
void R_prime(struct cube * rubiks){
    char * right_rotate[4][3];
    int right_layer = 2;

    // Rotates ride side of the cube. The back is mirrored so it's the left side (0) that goes through rotation.
    // right_rotate array represents the position on the cube [U, F, D, B]. When we rotate we insert the color
    // or array we want to put into the position. 

    // Assign the temporary array in a counter-clockwise rotation.
    for (int j = 0; j < 3; ++j){
        right_rotate[0][j] = rubiks->B.matrix[j][0];
        right_rotate[1][j] = rubiks->U.matrix[j][right_layer];
        right_rotate[2][j] = rubiks->F.matrix[j][right_layer];
        right_rotate[3][j] = rubiks->D.matrix[j][right_layer];
    }

    // Reassign the default positions to the new one.  
    for (int j = 0; j < 3; ++j){
        rubiks->U.matrix[j][right_layer] = right_rotate[0][-j+2];
        rubiks->F.matrix[j][right_layer] = right_rotate[1][j];
        rubiks->D.matrix[j][right_layer] = right_rotate[2][j];
        rubiks->B.matrix[j][0] = right_rotate[3][-j+2];
    }
    face_counter_clockwise(&rubiks->R);
}

/**
 * F(struct cube * rubiks) -> void
 * 
 * Moves the Front Face of the cube clockwise.
 * 
 * Implementation is similar to that of the Up face except we are rotating the Up (U), Right (R), D (Down), and Left (L) rows and columns.
 * In this implementation, we are rotating the columns and rows between two faces. Thus, any colors going from column to row (colors rotating to top
 * and bottom face) of the matrices must be inverted.
 * 
 * The default order of faces for the temporary array is [U, R, D, L].
 * 
*/
void F(struct cube * rubiks){
    char * front_rotate[4][3];

    face_clockwise(&rubiks->F);

    // Assign the temporary array in a counter-clockwise rotation.
    for (int j = 0; j < 3; ++j){
        front_rotate[0][j] = rubiks->L.matrix[j][2];
        front_rotate[1][j] = rubiks->U.matrix[2][j];
        front_rotate[2][j] = rubiks->R.matrix[j][0];
        front_rotate[3][j] = rubiks->D.matrix[0][j];
    }

    // Reassign the default positions to the new one.  
    for (int j = 0; j < 3; ++j){
        rubiks->U.matrix[2][j] = front_rotate[0][-j+2];
        rubiks->R.matrix[j][0] = front_rotate[1][j];
        rubiks->D.matrix[0][j] = front_rotate[2][-j+2];
        rubiks->L.matrix[j][2] = front_rotate[3][j];
    }
}

/**
 * F_prime(struct cube * rubiks) -> void
 * 
 * Moves the Front Face of the cube counter-clockwise.
 * 
 * Implementation is similar to that of the Up face except we are rotating the Up (U), Right (R), D (Down), and Left (L) rows and columns.
 * In this implementation, we are rotating the columns and rows between two faces. Thus, any colors going from row to column (colors rotating to top
 * and bottom face) of the matrices must be inverted.
 * 
 * The default order of faces for the temporary array is [U, R, D, L].
 * 
*/
void F_prime(struct cube * rubiks){
    char * front_rotate[4][3];

    face_counter_clockwise(&rubiks->F);

    // Assign the temporary array in a counter-clockwise rotation.
    for (int j = 0; j < 3; ++j){
        front_rotate[0][j] = rubiks->R.matrix[j][0];
        front_rotate[1][j] = rubiks->D.matrix[0][j];
        front_rotate[2][j] = rubiks->L.matrix[j][2];
        front_rotate[3][j] = rubiks->U.matrix[2][j];
    }

    // Reassign the default positions to the new one.  
    for (int j = 0; j < 3; ++j){
        rubiks->U.matrix[2][j] = front_rotate[0][j];
        rubiks->R.matrix[j][0] = front_rotate[1][-j+2];
        rubiks->D.matrix[0][j] = front_rotate[2][j];
        rubiks->L.matrix[j][2] = front_rotate[3][-j+2];
    }
}

/**
 * B(struct cube * rubiks) -> void
 * 
 * Moves the Back Face of the cube clockwise.
 * 
 * Similar to the F_prime(struct cube * rubiks) function, we are dealing with the back layer
 * of the cube.
 * 
 * The moves B and F' are aligned thus the only change here is that we are using different
 * rows and columns that touch the back side.
 * 
 * Additionally, any colors going from row to column of the matrix must still be inverted.
 * 
 * The default order of faces for the temporary array is [U, R, D, L].
*/
void B(struct cube * rubiks){
    char * back_rotate[4][3];

    face_clockwise(&rubiks->B);

    // Assign the temporary array in a counter-clockwise rotation.
    for (int j = 0; j < 3; ++j){
        back_rotate[0][j] = rubiks->R.matrix[j][2];
        back_rotate[1][j] = rubiks->D.matrix[2][j];
        back_rotate[2][j] = rubiks->L.matrix[j][0];
        back_rotate[3][j] = rubiks->U.matrix[0][j];
    }

    // Reassign the default positions to the new one.  
    for (int j = 0; j < 3; ++j){
        rubiks->U.matrix[0][j] = back_rotate[0][j];
        rubiks->R.matrix[j][2] = back_rotate[1][-j+2];
        rubiks->D.matrix[2][j] = back_rotate[2][j];
        rubiks->L.matrix[j][0] = back_rotate[3][-j+2];
    }  
}

/**
 * B_prime(struct cube * rubiks) -> void
 * 
 * Moves the Back Face of the cube counter-clockwise.
 * 
 * Similar to the F(struct cube * rubiks) function, we are dealing with the back layer
 * of the cube.
 * 
 * The moves B' and F are aligned thus the only change here is that we are using different
 * rows and columns that touch the back side.
 * 
 * Additionally, any colors going from column to row of the matrix must still be inverted.
 * 
 * The default order of faces for the temporary array is [U, R, D, L].
*/
void B_prime(struct cube * rubiks){
    char * back_rotate[4][3];

    face_counter_clockwise(&rubiks->B);

    // Assign the temporary array in a counter-clockwise rotation.
    for (int j = 0; j < 3; ++j){
        back_rotate[0][j] = rubiks->L.matrix[j][0];
        back_rotate[1][j] = rubiks->U.matrix[0][j];
        back_rotate[2][j] = rubiks->R.matrix[j][2];
        back_rotate[3][j] = rubiks->D.matrix[2][j];
    }

    // Reassign the default positions to the new one.  
    for (int j = 0; j < 3; ++j){
        rubiks->U.matrix[0][j] = back_rotate[0][-j+2];
        rubiks->R.matrix[j][2] = back_rotate[1][j];
        rubiks->D.matrix[2][j] = back_rotate[2][-j+2];
        rubiks->L.matrix[j][0] = back_rotate[3][j];
    }  
}

void X(struct cube * rubiks){
    struct face * four_faces[2];
    char * temp_face[2][3][3];

    face_counter_clockwise(&rubiks->L);
    face_clockwise(&rubiks->R);

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_face[0][i][j] = rubiks->U.matrix[i][j];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_face[1][i][j] = rubiks->B.matrix[i][j];
        }
    }

    four_faces[0] = &rubiks->F;
    four_faces[1] = &rubiks->D;

    rubiks->U = *four_faces[0];
    rubiks->F = *four_faces[1];

    
    // U->B and B->D must be inverted
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->B.matrix[i][j] = temp_face[0][-i+2][-j+2];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->D.matrix[i][j] = temp_face[1][-i+2][-j+2];
        }
    }


    // Default is U,F,D,R
}

void X_prime(struct cube * rubiks){
    struct face * four_faces[2];
    char * temp_face[2][3][3];

    face_counter_clockwise(&rubiks->R);
    face_clockwise(&rubiks->L);

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_face[0][i][j] = rubiks->D.matrix[i][j];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_face[1][i][j] = rubiks->B.matrix[i][j];
        }
    }

    four_faces[0] = &rubiks->F;
    four_faces[1] = &rubiks->U;

    rubiks->D = *four_faces[0];
    rubiks->F = *four_faces[1];

    // D->B and B->U must be inverted
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->B.matrix[i][j] = temp_face[0][-i+2][-j+2];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->U.matrix[i][j] = temp_face[1][-i+2][-j+2];
        }
    }
    // Default is U,F,D,R
}

void Y(struct cube * rubiks){
    struct face * four_faces[3];
    char * temp_face[3][3];

    face_counter_clockwise(&rubiks->D);
    face_clockwise(&rubiks->U);

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_face[i][j] = rubiks->B.matrix[i][j];
        }
    }

    four_faces[0] = &rubiks->L;
    four_faces[1] = &rubiks->F;
    four_faces[2] = &rubiks->R;

    rubiks->B = *four_faces[0];
    rubiks->L = *four_faces[1];
    rubiks->F = *four_faces[2];

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->R.matrix[i][j] = temp_face[i][j];
        }
    }
}

void Y_prime(struct cube * rubiks){
    struct face * four_faces[3];
    char * temp_face[3][3];

    face_counter_clockwise(&rubiks->U);
    face_clockwise(&rubiks->D);

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_face[i][j] = rubiks->R.matrix[i][j];
        }
    }

    four_faces[0] = &rubiks->B;
    four_faces[1] = &rubiks->L;
    four_faces[2] = &rubiks->F;


    rubiks->R = *four_faces[2];
    rubiks->F = *four_faces[1];
    rubiks->L = *four_faces[0];
    
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->B.matrix[i][j] = temp_face[i][j];
        }
    }
}

void Z(struct cube * rubiks){
    char * temp_faces[4][3][3];

    face_clockwise(&rubiks->F);
    face_counter_clockwise(&rubiks->B);

    // Copy 4 faces state, invert, and transpose
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_faces[0][i][j] = rubiks->L.matrix[-j+2][i];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_faces[1][i][j] = rubiks->U.matrix[-j+2][i];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_faces[2][i][j] = rubiks->R.matrix[-j+2][i];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_faces[3][i][j] = rubiks->D.matrix[-j+2][i];
        }
    }

    // Update the faces
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->U.matrix[i][j] = temp_faces[0][i][j];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->R.matrix[i][j] = temp_faces[1][i][j];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->D.matrix[i][j] = temp_faces[2][i][j];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->L.matrix[i][j] = temp_faces[3][i][j];
        }
    }
    
}

void Z_prime(struct cube * rubiks){
    char * temp_faces[4][3][3];

    face_clockwise(&rubiks->B);
    face_counter_clockwise(&rubiks->F);

    // Copy 4 faces state, invert, and transpose
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_faces[0][i][j] = rubiks->R.matrix[j][-i+2];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_faces[1][i][j] = rubiks->D.matrix[j][-i+2];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_faces[2][i][j] = rubiks->L.matrix[j][-i+2];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            temp_faces[3][i][j] = rubiks->U.matrix[j][-i+2];
        }
    }

    // Update the faces
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->U.matrix[i][j] = temp_faces[0][i][j];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->R.matrix[i][j] = temp_faces[1][i][j];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->D.matrix[i][j] = temp_faces[2][i][j];
        }
    }

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            rubiks->L.matrix[i][j] = temp_faces[3][i][j];
        }
    }
    
}

void make_moves(struct cube * rubiks){
    char move[2];
    printf("Enter your move: \n");
    scanf("%s", move);
    
    if(!(strcmp(move, "R"))){R(rubiks); print_cube(rubiks);}
    else if(!(strcmp(move, "R'"))){R_prime(rubiks); print_cube(rubiks);}
    else if(!(strcmp(move, "L"))){L(rubiks); print_cube(rubiks);}
    else if(!(strcmp(move, "L'"))){L_prime(rubiks); print_cube(rubiks);}
    else if(!(strcmp(move, "U"))){U(rubiks); print_cube(rubiks);}
    else if(!(strcmp(move, "U'"))){U_prime(rubiks); print_cube(rubiks);}
    else if(!(strcmp(move, "D"))){D(rubiks); print_cube(rubiks);}
    else if(!(strcmp(move, "D'"))){D_prime(rubiks); print_cube(rubiks);}
    else if(!(strcmp(move, "B"))){B(rubiks); print_cube(rubiks);}
    else if(!(strcmp(move, "B'"))){B_prime(rubiks); print_cube(rubiks);}
    else if(!(strcmp(move, "F"))){F(rubiks); print_cube(rubiks);}
    else if(!(strcmp(move, "F'"))){F_prime(rubiks); print_cube(rubiks);}
    else{printf("That's not a valid move!\n");}
}

int main(){
    struct cube r;
    init(&r);
    print_cube(&r);
    while(1){make_moves(&r);}
    return 0;
}