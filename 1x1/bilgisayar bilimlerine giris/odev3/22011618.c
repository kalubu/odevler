#include <stdio.h>
int main(){
    char D[5] = {'a','e','r','k','s'};
    int lenD = 0, lenK = 0, len, puan = 0, i, j, k, l, m, n, x, f, b, c, z, y, s, d;
    lenD = sizeof(D) / sizeof(D[0]);
    char T[50];
    char kelimeler[][6] = {"asker","serak","kars","kase","sera","akse","ark","kes","kas","ser","sek","kar"};
    lenK = sizeof(kelimeler) / sizeof(kelimeler[0]);
    int tekrar[100] = {0};
    printf("Kullanabileceginiz karakterler: ");
    for(z = 0; z < lenD; z++){
        printf("%c ", D[z]);
    }
    printf("\n");
    while (T[0] != '0'){
        c = 0;
        b = 0;
        printf("Tahmininizi giriniz: ");
        scanf("%49s", T);
        len = 0;
        while (T[len] != '\0'){
            len++;
        }
        if (T[0] == '0' && len == 1){
            c = 1;
        }
        if (len < 2 && c == 0){
            printf("Lutfen tahminlerinizi minimum 2 harf olacak sekilde yapiniz.\n");
            c = 1;
        }
        if (c == 0){
            k = 1;
            i = 0;
            while (i < len && k == 1){
                k = 0;
                for (j = 0; j < lenD; j++){
                    if (T[i] == D[j]){
                        k++;
                    }
                }
            i++;
            }
            s = 0;
            y = 0;
            while (s < len - 1 && y == 0){
                d = s + 1;
                y = 0;
                while (d < len && y == 0){
                    if(T[d] == T[s]){
                        y++;
                    }
                d++;
                }
            s++;
            }
            if (k == 0 || y == 1){
                puan = puan - len;
                printf("Hatali harf kullanimi, Puaniniz:%d\n", puan);
                c = 1;
            }
            f= 0;
            l = 0;
            if (c == 0){
                while (l < lenK && b == 0){
                    c = 0;
                    m = 0;
                    n = 0;
                    x = 0;
                    while (kelimeler[l][x] != '\0'){
                        x++;
                    }
                    if (x != len){
                        c = 1;
                        f = 0;
                    }
                    while(T[m] != '\0' && c == 0 && b == 0){
                        if (T[m] == kelimeler[l][m]){
                            m++;
                            n = 1;
                        }
                        else{
                            n = 0;
                            b = 1;
                        }
                    }
                    b = 0;
                    if (n == 1 && c == 0 && tekrar[l] == 0){
                        puan = puan + len;
                        printf("Puaniniz: %d\n", puan);
                        tekrar[l] = 1;
                        n = 0;
                        f = 1;
                        b = 1;
                    }
                l++;
                }
                if (f == 0){
                    puan = puan - len;
                    printf("Puaniniz: %d\n", puan);
                }
            }
        }
    }
    printf("Oyun bitmiştir. Tebrikler! Toplam puaniniz: %d\n", puan);
    return 0;
}