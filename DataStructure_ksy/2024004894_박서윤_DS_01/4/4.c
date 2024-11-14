/* 4. 100개 미만의 원소의 개수를 입력받아, 받은 입력 원소 개수 만큼 난수를 생성한다.
생성된 난수에 대하여  선택정렬(selection sort)을 수행하는 프로그램을 작성하시오.
정렬된 난수에서 임의원 원소를 찾기위해 재귀적인 방법을 사용하는  binary search 프로그램을 작성 하시오.
재귀함수 호출시마다 찾는 범위를 left와 right 인덱스 값을 출력하시오.

 [실행순서]
 ① 사용자로부터 난수생성 개수(n)를 입력받는다.
 ② 정수 난수를 n개 발생시켜 1차원 배열에 저장한다.
 ③ 1차원 배열에 대해 선택정렬(selection sort)
을 수행한다. 수행결과를 출력한다.
 ④ 검색을 위해 임의의 정수를 입력받는다.
 ⑤ 입력받은 정수가 배열에 있는지 재귀적인 방법으로 이진탐색(binary search)을  수행하는 프로그램을 작성하시오.*/


#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void selectionSort(int arr[], int n) {
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

int binarySearch(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {

        printf("call binsearch_srcur, left = %d, right = %d\n", left, right);

        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }

    }

    return -1;
}

int main() {
    int n;
    printf("Enter the number of numbers to generate: ");
    scanf_s("%d", &n);

    if (n <= 0 || n >= SIZE) {
        printf("Please enter a lower number.\n");
        return 1;
    }

    int arr[SIZE];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }

    selectionSort(arr, n);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int target;
    printf("Enter the number to search: ");
    scanf_s("%d", &target);

    int result = binarySearch(arr, n, target);



    if (result != -1) {
        printf("The serch numberis present in list[%d].\n", result);
    }
    else {
        printf("The number %d is not present in the array.\n", target);
    }

    return 0;
}