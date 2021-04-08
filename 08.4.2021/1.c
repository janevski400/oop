#include <stdio.h>
#include <string.h>
typedef struct callStruct {
    int den;
    int mesec;
    int godina;
    int vremetraenje;
    char brojPovikuva[10];
    char brojBaran[10];
}Call;

void pecatenjePovici (Call *povici, int n, char *testBroj) {
    int total=0;
    for(int i=0;i<n;i++) {
        if(!strcmp(povici[i].brojPovikuva,testBroj)) {

            if((povici[i].den >= 1) && (povici[i].den<=31)) {

                if((povici[i].mesec >=1) && (povici[i].mesec<=12)) {

                    if((povici[i].godina >= 2019)&&(povici[i].godina <= 2020)) {
                            if(povici[i].den<10) {
                                printf("0%d/",povici[i].den);
                                if(povici[i].mesec<10)
                                        printf("0%d/%d %s %s %d\n", povici[i].mesec, povici[i].godina, povici[i].brojPovikuva, povici[i].brojBaran, povici[i].vremetraenje);
                                else
                                        printf("%d/%d %s %s %d\n", povici[i].mesec, povici[i].godina, povici[i].brojPovikuva, povici[i].brojBaran, povici[i].vremetraenje);
                            }
                            else if(povici[i].mesec<10)
                                printf("%d/0%d/%d %s %s %d\n", povici[i].den, povici[i].mesec, povici[i].godina, povici[i].brojPovikuva, povici[i].brojBaran, povici[i].vremetraenje);
                            else{
                                printf("%d/%d/%d %s %s %d\n", povici[i].den, povici[i].mesec, povici[i].godina, povici[i].brojPovikuva, povici[i].brojBaran, povici[i].vremetraenje);
                            }

                        total += povici[i].vremetraenje;
                    }
                }
            }

        }
    }
    printf("Total: %d sec.\n",total);
}

int main () {
    Call povici[500];
    int n;
    scanf("%d",&n);
    if(n>500)
        return 0;
    else {
        for(int i=0;i<n;i++) {
            scanf("%d/%d/%d %s %s %d", &povici[i].den, &povici[i].mesec, &povici[i].godina, povici[i].brojPovikuva, povici[i].brojBaran, &povici[i].vremetraenje);
        }
        pecatenjePovici(povici,n,"070214011");
    }
    return 0;
}
