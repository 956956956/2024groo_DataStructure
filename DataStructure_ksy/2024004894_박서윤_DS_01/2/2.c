/*2. 아래의 메모리의 동적 할당과 해제에 대해, 보다 견고한 할당이 될 수 있도록   매크로를 
사용하여 다시 작성 하여 출력하세요*/

#include <stdio.h>
#include <stdlib.h>

#define ALLOC_CHECK(ptr) \
    if ((ptr) == NULL) { \
        printf("Memory allocation failed\n"); \
        return 1; \
    }


int main()
{
    int i, * pi;
    float f, * pf;

    pi = (int*)malloc(sizeof(int));
    pf = (float*)malloc(sizeof(float));

    /*if (pi == NULL || pf == NULL) {
        printf("fail to load\n");
        return 1;}*/ //이 부분을 매크로로 작성

    *pi = 1024;
    *pf = 3.14f;

    printf("an integer = %d, a float = %f\n", *pi, *pf);

    free(pi);
    free(pf);

    return 0;
}
