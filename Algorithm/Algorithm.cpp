#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
int euclid(int a, int b);

int main() {
    printf("%d",euclid(14, 24));

    return 0;
}

int euclid(int a, int b) {
    if (b == 0) return a;
    return euclid(b, a % b);
}
*/

////////////////1장//////////////////////////
// 독 단지 찾기 / 임의의 독이 든 독 단지 ( 1개만 독 ) / 독이든 단지의 번호

// 가짜 동전 / 가짜 동전이 포함된 동전 더미 ( 1개만 가짜 ) / 가짜 동전의 번호 ( 해결 )
/*
#define max_coin 1024 // 최대 동전 갯수
int cnt = 0;

int check_sum(int coin[], int a, int b);

int main() {
    int coin[max_coin] = { 0 };
    int i = 0;
    srand(time(NULL));

    // coin[rand() % max_coin] = 1;

    coin[524] = 1;

    printf("%d번이 가짜 :  %d번의 확인 끝의 탈출", check_sum(coin, 0, max_coin), cnt);
    return 0;
}

int check_sum(int coin[], int a, int b) {
    if ((b - a) == 1) // 탈출
        if (coin[a])
            return a;
        else
            return b;

    int sum = 0;
    cnt++;

    for (int i = a; i < ( b - (b-a) / 2 ); i++) {
        sum += coin[i];
    }

    printf("%d\n", sum);
    if (sum == 0)
        return check_sum(coin, b - ((b - a) / 2), b);
    else
        return check_sum(coin, a, b - ((b - a) / 2));

    return -1;
}
*/
//가짜 동전 / log3n 의 방법
/*
int check_sum(int coin[], int a, int b);

int main() {
    int coin[max_coin] = { 0 };
    int i = 0;
    srand(time(NULL));

    // coin[rand() % max_coin] = 1;

    coin[524] = 1;

    printf("%d번이 가짜", check_sum(coin, 0, max_coin));
    return 0;
}

int check_sum(int coin[], int a, int b) {
    if ((b - a) == 1) // 탈출
        if (coin[a])
            return a;
        else
            return b;

    int sum = 0;
    int sum_2 = 0;

    
    for (int i = a; i < b - (2 * ((b - a) / 3)); i++) // 0 ~ 333
        sum += coin[i];
    for (int i = b - (2 * ((b - a) / 3)); i < b - ((b - a) / 3); i++) // 333 ~ 666
        sum_2 += coin[i];

    printf("%d %d %d %d\t%d %d\n", a, b - (2 * ((b - a) / 3)), b - ((b - a) / 3), b, sum, sum_2);

    Sleep(1000);
    if (sum > sum_2)
        return check_sum(coin, a, b - (2 * ((b - a) / 3))); 
    else if (sum < sum_2)
        return check_sum(coin, b - (2 * ((b - a) / 3)), b - ((b - a) / 3));
    else
        return check_sum(coin, b - ((b - a) / 3), b);

    return -1;
}
*/

// 미로 구현 / 어떻게 빠져 나올 것 인가 ( 우수의 법칙 / 마크 법칙 )
/*
int make_maze();

int main() {
    int maze[6][6] = { 0 };

    return 0;
}
*/

// 한붓그리기 ( 재귀함수 사용 할 예정 ) / 야호 ( 해결 )
/*
int dfs(int test[][5], int now);
int move = 0;

int main(){
    int test[5][5] = { { 0 } };

    test[0][1] = 1;
    test[0][3] = 1;
    test[1][2] = 1;
    test[1][3] = 1;
    test[1][4] = 1;
    test[2][3] = 1;
    test[3][4] = 1;

    dfs(test, 0);

    return 0;
}

int dfs(int test[][5], int now) {
    if (move != 0)
        for( int i=0; i<5; i++)
            for(int j=0; j<5; j++)
                if(test[i][j] == 1 && now == 0)
                    return -1;

    printf("%d ", now);
    for (int i = 0; i < 5; i++) {
        if (test[now][i] == 1) {
            test[now][i] = 0;
            move++;
            if (dfs(test, i) == -1) test[now][i] = 1, move--;
        }
        else if (test[i][now] == 1) {
            test[i][now] = 0;
            move++;
            if (dfs(test, i) == -1) test[now][i] = 1, move--;
        }

    }
    return 0;
}
*/

// 동전 거스름돈 ( 해결 )
/*
int change(int money, struct change_coin *cc);

struct change_coin {
    int n_coin[4] = { 0 };
};

int main() {
    int money = 8240;
    
    struct change_coin cc = { 0 };


    printf("%d원\n", money);
    change(money, &cc);

    for (int i = 0; i < 4; i++)
        printf("%d ", cc.n_coin[i]);

    return 0;
}

int change(int money, struct change_coin *cc) {
    int coin[] = { 500, 100, 50, 10 };

    for (int i = 0; i < 4; i++) {
        cc->n_coin[i] = money / coin[i]; // 구조체를 통한 출력
        printf("%d원 : %d\n", coin[i], money / coin[i]); // printf를 통한 출력
        money %= coin[i];
    }

    return 0;
}
*/
// 임의 숫자 찾기 ( 해결 )
/*
int A[10] = { 0 };

int rand_A();
int searchK(int K);

int main() {
    srand(time(NULL));

    int ret = -2;
    int K = rand_A();

    printf("\n%d\n", K);
    
    ret = searchK(K);

    if ( ret == K)
        printf("FOund! it's %d!!", K);
    else if ( ret == -2)
        printf("ErroR!!");
    else
        
    return 0;
}

int rand_A() {
    for (int i = 0; i < 10; i++) {
        A[i] = rand() % 100 + 1;
        printf("%d ", A[i]);
    }

    return A[ rand() % 10 ];
}


// Funtion : find K from array A[]
//  return :
//      -1 : if K is not found
//       K : if K is found
int searchK(int K) {
    int ret = 0;

    // 2. K값 순차적 찾기
    for (int i = 1; i < 10; i++)
        if (A[i] == K){
            ret = i;
            break;
        }
    return A[ret];
}
*/
// 최대 숫자 찾기 ( 해결 )
/*
int searchBig();

int main() {
    printf("\nthe big number is %d", searchBig());

    return 0;
}

int searchBig() {
    srand(time(NULL));

    int A[10] = { 0 };

    for (int i = 0; i < 10; i++){
        A[i] = rand() % 100 + 1;
        printf("%d ", A[i]);
    }

    int ret = 0;

    for (int i = 1; i < 10; i++) {
        if (A[ret] < A[i])
            ret = i;
    }
    return A[ret];
}
*/