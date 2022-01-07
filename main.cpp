#include <iostream>
#include <stdlib.h>
using namespace std;

struct node_t{
    int value;
    struct node_t* parent;
    struct node_t* sibling;
    struct node_t* son;
    int level;
    int label;
};

typedef struct node_t Tree_leaf;

int CountLeaves(char* tab, int* number_nodes){
    int i=0;
    int numbers=0;
    while(tab[i]!=';'){
        if(tab[i] == ','){
            numbers++;
        }
        if(tab[i] == '('){
            (*number_nodes)++;
        }
        i++;
    }

    tab[i+1] = '\0';
    return numbers;
}

void CreateRelations(Tree_leaf**array, int index, int j){
    if (array[index][j].level > array[index][j-1].level){
        array[index][j-1].son = (Tree_leaf*)malloc(sizeof(Tree_leaf));
        array[index][j-1].son = &array[index][j];
        array[index][j-1].sibling = nullptr;
        array[index][j].parent = (Tree_leaf*)malloc(sizeof(Tree_leaf));
        array[index][j].parent = &array[index][j-1];
    } else {
        for (int z=j-1; z>=0; z--){
            if (array[index][z].level == array[index][j].level){
                if(array[index][z].parent != nullptr){
                    array[index][j].parent = (Tree_leaf*)malloc(sizeof(Tree_leaf));
                    array[index][j].parent = array[index][z].parent;
                }
                array[index][z].sibling = (Tree_leaf *) malloc(sizeof(Tree_leaf));
                array[index][z].sibling = &array[index][j];
                break;
            }
        }
        array[index][j].sibling = nullptr;
    }
}

int CreateTree(Tree_leaf**array, char*temp, int index) {
    int i=0, ii=0;
    int start_value = -1;
    int j=0;
    int level=-1;
    int max_level = -1;

    while(temp[i]!=';') {
        if (temp[i] == '(') {
            level++;
            if(level > max_level){
                max_level = level;
            }
            array[index][j].value = start_value;
            array[index][j].level = level-1;

            if(j!=0) {
                CreateRelations(array,index,j);
            } else{
                array[index][j].parent = nullptr;
            }
            start_value--;
            j++;
        } else if(temp[i] == ')'){
            level--;
        } else if (temp[i] >=49 && temp[i] <= 57){
            ii=i;
            ii++;
            while(temp[ii] != ',' && temp[ii] != ')' && temp[ii] != '('){
                ii++;
            }

            if (ii != i + 1) {
                int decimal=1;
                int sum=0;
                for(int a=ii-1; a>=i; a--){
                    sum += (temp[a] - '0') * decimal;
                    decimal *= 10;
                }
                array[index][j].value = sum;
                array[index][j].level = level;

            } else {
                array[index][j].value = temp[i] - '0';
                array[index][j].level = level;
            }
            CreateRelations(array,index,j);
            j++;
        }
        i++;
    }

    return max_level;
}

int FindLabel(Tree_leaf*array, int to_find, int size, int sign){
    for(int i=0; i<size; i++){
        if (sign == 1) {
            if (array[i].value > 0) {
                if (array[i].value == to_find) {
                    return array[i].label;
                }
            }
        } else{
            if (array[i].value < 0) {
                if (array[i].value == to_find) {
                    return array[i].label;
                }
            }
        }
    }
    return 0;
}

int Traverse(Tree_leaf*array, int to_find, int size, int sign){
    int j=0;
    for(int i=0; i<size; i++){
        if (sign == 1) {
            if (array[i].value > 0) {
                if (array[i].value == to_find) {
                    return j;
                }
                j++;
            }
        } else{
            if (array[i].value < 0) {
                if (array[i].value == to_find) {
                    return i;
                }
                j++;
            }
        }
    }
    return 0;
}

void Permute(int* arr, int left, int right, int* max, int col, int row, int**a, int row_start){
    int sum = 0;
    int temp;

    if(left==right){
        sum=0;

        for(int ii=row_start; ii <right+1; ii++){
            sum += a[ii][arr[ii]];
        }

        if(sum > *max){
            *max = sum;
        }

    } else{
        for(int i=left; i<=right; i++){

            temp = arr[left];
            arr[left] = arr[i];
            arr[i] = temp;
            Permute(arr, left+1, right, max, col, row, a, row_start);
            temp = arr[left];
            arr[left] = arr[i];
            arr[i] = temp;
        }
    }
}

int FindMax(int cols, int rows, int**b){

    int *arr;

    int col_tmp = cols;
    int col = rows;
    int row = col_tmp;

    int ** a;
    int new_col=col;
    int new_row=row;
    int max = 0;

    if (row>col){

        new_col=row;

        a = (int**)malloc((row)* sizeof(int*));
        for(int ii=0; ii<row; ii++){
            a[ii] = (int*)malloc((new_col)* sizeof(int));
        }
        for(int ii=0;ii<row;ii++){
            for(int jj=0;jj<new_col;jj++){
                if(jj<(col)){
                    a[ii][jj] = b[ii+1][jj+1];
                }else {
                    a[ii][jj] = 0;
                }

            }
        }
        arr = (int*)malloc((new_col)* sizeof(int));

        for(int i=0; i<new_col; i++){
            arr[i]=i;
        }

        max = 0;
        Permute(arr, 0, new_col - 1, &max, new_col, new_row, a, 0);


        for(int i=0; i<new_row; i++) {
            free(a[i]);
        }
        free(a);


    } else

    if (col>row){
        new_row=col;

        a = (int**)malloc((new_row)* sizeof(int*));
        for(int ii=0; ii<new_row; ii++){
            a[ii] = (int*)malloc((col)* sizeof(int));
        }
        for(int ii=0;ii<new_row;ii++){
            for(int jj=0;jj<col;jj++){
                if(ii<(row)){
                    a[ii][jj] = b[ii+1][jj+1];
                }else {
                    a[ii][jj] = 0;
                }

            }
        }

        arr = (int*)malloc((new_col)* sizeof(int));

        for(int i=0; i<new_col; i++){
            arr[i]=i;
        }

        max = 0;
        Permute(arr, 0, new_col - 1, &max, new_col, new_row, a, 0);


        for(int i=0; i<new_row; i++) {
            free(a[i]);
        }
        free(a);


    } else {

        arr = (int*)malloc((new_col+1)* sizeof(int));

        for(int i=0; i<new_col+1; i++){
            arr[i]=i;
        }

        max = 0;

        Permute(arr, 1, new_col , &max, new_col, new_row, b, 1);

    }

    free(arr);
    return max;
}



void FillIn(Tree_leaf** tab, int size_row, int size_column, int** matrix,int n_col, int n_row, int*sizes, int y, int z, int first, int second){
    int row = FindLabel(tab[second], -n_row, size_row, 0);
    int col = FindLabel(tab[first], -n_col, size_column, 0);
    int** tempp;
    tempp = (int**)malloc((col+1)* sizeof(int*));
    for(int ii=0; ii<col+1; ii++){
        tempp[ii] = (int*)malloc((row+1)* sizeof(int));
    }

    int a =1;
    int index = Traverse(tab[first], -n_col, size_column, 0);
    int is_bigger=0;
    Tree_leaf *curr = &tab[first][index];
    int check=1;
    while (a <= col) {
        if (curr->son != nullptr && check == 1) {
            tempp[a][0] = curr->son->value;
            curr = curr->son;
            check = 0;
        } else {
            if(curr->sibling != nullptr) {
                tempp[a][0] = curr->sibling->value;
                curr = curr->sibling;
            }
        }

        if(tempp[a][0]<0){
            if(matrix[sizes[first]+abs(tempp[a][0])-1][y] > is_bigger) {
                is_bigger = matrix[sizes[first]+abs(tempp[a][0])-1][y];
            }
        }
        a++;
    }

    a =1;
    index = Traverse(tab[second], -n_row, size_row, 0);
    Tree_leaf *curr2 = &tab[second][index];
    check=1;
    while (a <= row) {
        if (curr2->son != nullptr && check == 1) {
            tempp[0][a] = curr2->son->value;
            curr2 = curr2->son;
            check = 0;
        } else {
            if(curr2->sibling != nullptr) {
                tempp[0][a] = curr2->sibling->value;
                curr2 = curr2->sibling;
            }
        }

        if(tempp[0][a]<0){
            if(matrix[z][sizes[second]+abs(tempp[0][a])-1] > is_bigger) {
                is_bigger = matrix[z][sizes[second]+abs(tempp[0][a])-1];
            }
        }

        a++;
    }


    tempp[0][0] = 0;
    for(int ii = 1; ii<=row; ii++){
        for(int jj = 1; jj<=col; jj++){
            if(tempp[jj][0] > 0 && tempp[0][ii] > 0) {
                if (tempp[jj][0] == tempp[0][ii]) {
                    tempp[jj][ii] = 1;
                } else {
                    tempp[jj][ii] = 0;
                }
            } else if (tempp[jj][0] * tempp[0][ii] < 0){
                int index1=0;
                if(tempp[jj][0] > 0){
                    index1=Traverse(tab[first], tempp[jj][0], size_column, 1);
                    tempp[jj][ii] = matrix[index1][sizes[second]+abs(tempp[0][ii])-1];
                } else{
                    index1=Traverse(tab[second], tempp[0][ii], size_row, 1);
                    tempp[jj][ii] = matrix[sizes[first]+abs(tempp[jj][0])-1][index1];
                }

            } else {
                tempp[jj][ii] = matrix[sizes[second]+abs(tempp[jj][0])-1][sizes[first]+abs(tempp[0][ii])-1];
            }
        }
    }

    if(is_bigger > FindMax(col, row, tempp)){
        matrix[z][y] = is_bigger;
    } else {
        matrix[z][y] = FindMax(col, row, tempp);
    }

    for(int ii=0; ii<col+1; ii++){
        free(tempp[ii]);
    }
    free(tempp);

}

void Label(Tree_leaf** tab, int size, int* max_levels, int index){
    for (int i = 0; i < size; i++) {
        if (tab[index][i].level == max_levels[index]) {
            tab[index][i].label = 0;
        }
    }
    max_levels[index]--;
    int lab = 0;
    int jj = 0;
    Tree_leaf* curr1;
    while(max_levels[index] > -2) {
        for (int i = 0; i < size; i++) {
            if (tab[index][i].level == max_levels[index]) {
                lab= 0;


                if(tab[index][i].son != nullptr) {
                    if (i < size - 1) {


                        jj = i + 1;
                        lab++;

                        if (tab[index][jj].sibling != nullptr) {
                            curr1 = tab[index][jj].sibling;

                            if(curr1 != 0){

                                for(;;){
                                    if(curr1 == nullptr){
                                        break;
                                    } else{
                                        lab++;
                                        if(curr1->sibling !=0  && curr1->sibling != nullptr) {
                                            curr1 = curr1->sibling;
                                        }else{
                                            break;
                                        }
                                    }
                                }
                            }




                        }

                    }

                }
                tab[index][i].label = lab;
            }
        }
        max_levels[index]--;
    }
}


int main() {
    int number_of_trees;
    char temp[41];
    Tree_leaf** tab;
    int nr_nodes=0;

    scanf("%d", &number_of_trees);

    int* sizes = (int*)malloc(number_of_trees* sizeof(int));
    int* node = (int*)malloc(number_of_trees* sizeof(int));
    int* max_levels = (int*)malloc(number_of_trees* sizeof(int));

    tab = (Tree_leaf**)malloc(number_of_trees* sizeof(Tree_leaf*));

    for(int i=0; i<number_of_trees; i++){
        scanf(" %40s", temp);
        nr_nodes=0;
        sizes[i] = CountLeaves(temp, &nr_nodes)+1;;
        node[i] = nr_nodes;
        tab[i] = (Tree_leaf*)malloc((sizes[i] + nr_nodes)* sizeof(Tree_leaf));
        max_levels[i] = CreateTree(tab, temp, i);
    }


    for(int first = 0; first<number_of_trees; first++){
        for(int second = 1+first; second<number_of_trees; second++){
            int size_row = sizes[second] + node[second];
            int size_column = sizes[first] + node[first];

            int**matrix;
            matrix = (int**)malloc(size_column*sizeof(int*));
            for(int a=0; a<size_column; a++){
                matrix[a] = (int*)malloc(size_row*sizeof(int));
            }

            int z=0,y=0;
            for(int j=0; j<size_column; j++){
                if (tab[first][j].value > 0) {
                    y=0;
                    for (int k = 0; k < size_row; k++) {
                        if (tab[second][k].value > 0) {
                            if (tab[first][j].value == tab[second][k].value) {
                                matrix[z][y] = 1;
                            } else {
                                matrix[z][y] = 0;
                            }
                            y++;
                        }
                    }
                    z++;
                }
            }

            int old_y = y;
            z=0;
            int k=0;
            for(int j=0; j<size_column; j++){
                y=old_y;
                if (tab[first][j].value > 0) {
                    for (k = 0; k < size_row; k++) {
                        if (tab[second][k].value < 0) {
                            for (int kk = k+1; kk < size_row; kk++) {
                                if (tab[second][k].sibling != nullptr) {
                                    if (tab[second][kk].value != tab[second][k].sibling->value) {
                                        if (tab[second][kk].value == tab[first][j].value) {
                                            matrix[z][y] = 1;
                                            break;
                                        }
                                    } else {
                                        matrix[z][y] = 0;
                                        break;
                                    }
                                } else{
                                    if (tab[second][kk].level < tab[second][k].level){
                                        break;
                                    } else {
                                        if (tab[second][kk].value == tab[first][j].value) {
                                            matrix[z][y] = 1;
                                            break;
                                        } else {
                                            matrix[z][y] = 0;
                                        }
                                    }
                                }
                            }
                            y++;
                        }
                    }
                    z++;
                }
            }

            int j=0;
            for(j=0; j<size_column; j++){
                y=0;
                if (tab[first][j].value < 0) {
                    for (k = 0; k < size_row; k++) {
                        if (tab[second][k].value > 0) {
                            for (int kk = j+1; kk < size_column; kk++) {
                                if (tab[first][j].sibling != nullptr) {
                                    if (tab[first][kk].value != tab[first][j].sibling->value) {
                                        if (tab[first][kk].value == tab[second][k].value) {
                                            matrix[z][y] = 1;
                                            break;
                                        }
                                    } else {
                                        matrix[z][y] = 0;
                                        break;
                                    }
                                } else{
                                    if (tab[first][kk].level < tab[first][j].level){
                                        break;
                                    } else {
                                        if (tab[first][kk].value == tab[second][k].value) {
                                            matrix[z][y] = 1;
                                            break;
                                        } else {
                                            matrix[z][y] = 0;
                                        }
                                    }
                                }
                            }
                            y++;
                        }
                    }
                    z++;
                }
            }

            Label(tab, size_column, max_levels, first);
            Label(tab, size_row, max_levels, second);

            int n_row = node[second];
            int n_col = node[first];

            int nr = n_row;
            int nc = n_col;

            y = sizes[first]+n_row-1;
            z = sizes[second]+n_col-1;

            while(n_col + n_row > 2){
                while(y >= sizes[first]){
                    FillIn(tab, size_row, size_column, matrix, n_col, n_row, sizes, y, z, first, second);
                    y--;
                    n_row--;
                }

                n_row = nr;
                if(n_col>1) {
                    n_col--;
                }
                nc = n_col;
                z = sizes[second]+n_col-1;
                y = sizes[first]+n_row-1;

                while(z>=sizes[second]){
                    FillIn(tab, size_row, size_column, matrix, n_col, n_row, sizes, y, z, first, second);
                    z--;
                    n_col--;
                }

                n_col = nc;
                if(n_row>1) {
                    n_row--;
                }
                nr = n_row;

                z = sizes[second]+n_col -1;
                y = sizes[first]+n_row -1;
            }
            FillIn(tab, size_row, size_column, matrix, n_col, n_row, sizes, y, z, first, second);

            int result = sizes[first] - matrix[sizes[first]][sizes[second]];
            printf("%d\n", result);

            for(int a=0; a<size_column; a++){
                free(matrix[a]);
            }
            free(matrix);
        }
    }

    free(sizes);
    free(node);
    free(max_levels);
    for(int i=0; i<number_of_trees; i++){
        free(tab[i]);
    }
    free(tab);


    return 0;
}