#include <stdio.h>

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

void fill(char * color, struct face * side){
    for (int i = 0 ; i<3; ++i){
        for (int j = 0; j<3; ++j){
            side->matrix[i][j] = color;
        }
    }
}


void init(struct cube * rubiks){
    fill("R", &rubiks->U);
    fill("B", &rubiks->R);
    fill("G", &rubiks->L);
    fill("Y", &rubiks->F);
    fill("W", &rubiks->B);
    fill("O", &rubiks->D);
}

void print_cube(struct cube * rubiks){
    for (int i = 0; i < 3; ++i){    
        for (int j = 0; j < 14; ++j){
            printf(" ");
        }
        for (int k = 0; k < 3; ++ k){
            printf("%s ", rubiks->U.matrix[i][k]);
        }
        printf("\n");
    }

    for (int i = 0; i < 3; ++i){
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

    for (int i = 0; i < 3; ++i){    
        for (int j = 0; j < 14; ++j){
            printf(" ");
        }
        for (int k = 0; k < 3; ++ k){
            printf("%s ", rubiks->D.matrix[i][k]);
        }
        printf("\n");
    }
}

void U_move(struct cube * rubiks){
    char * temp[3];
    for (int i = 0; int ){

    }
}

int main(){
    struct cube Rubiks;
    // struct face test;
    init(&Rubiks);
    print_cube(&Rubiks);

    /*
    fill("Y", &test);
    
    for (int i = 0; i < 3 ; ++i){
        for (int j = 0; j < 3; ++j){
            test.matrix[i][j] = "Y";
        }
    }
    
    for (int i = 0; i < 3 ; ++i){
        for (int j = 0; j < 3; ++j){
            printf("%s", Rubiks.R.matrix[i][j]);
            printf(" ");
        }
        printf("\n");
    }
    */
    return 0;

}