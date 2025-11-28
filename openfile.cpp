#include <iostream>
using namespace std;

template <class Type>
int Partition(Type a[], int p, int r)
{
  int i = p, j = r+1 ;
  Type x = a[p];

  while (true)
  {
    while ( a[++i] < x&&i < r )
      ; // 找到≥x的元素
    while (a[--j] > x)
      ; // 找到≤x的元素
    if (i >= j)
      break;
    swap(a[i], a[j]);
  }

  swap(a[p], a[j]); // 基准放到中间 j 位置
  return j;
}

template <class Type>
void QuickSort(Type a[], int p, int r)
{
  if (p < r)
  {
    int q = Partition(a, p, r);
    QuickSort(a, p, q - 1);
    QuickSort(a, q + 1, r);
  }
}

int main()
{
  int a[] = {34, 1, 5, -2, 0, 35, 36, 38};
  int n = sizeof(a) / sizeof(a[0]);

  cout << "原始数组: ";
  for (int i = 0; i < n; i++)
    cout << a[i] << " ";
  cout << endl;

  QuickSort(a, 0, n - 1);

  cout << "排序后数组: ";
  for (int i = 0; i < n; i++)
    cout << a[i] << " ";
  cout << endl;

  return 0;
}
