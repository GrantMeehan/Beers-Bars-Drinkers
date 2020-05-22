/*
* Author: Grant Meehan
* Date: 6/1/19
*
* This file, MinPQ.cpp, includes the implementation for the MinPQ class.
* MinPQ is a class which allows you to create a templated minimum priority queue.
*/

template <class T>
MinPQ<T>::MinPQ()
{
  pq = new T[1];
  N = 0;
}

template <class T>
MinPQ<T>::MinPQ(int capacity)
{
  N = 0;
  pq = new T[capacity + 1];
}

template <class T>
bool MinPQ<T>::isEmpty() //determines if PQ is empty
{
  return (N == 0);
}

template <class T>
void MinPQ<T>::insert(T key) { //inserts element into PQ and correctly places element in the PQ
  pq[++N] = key;
  swim(N);
}

template <class T>
T MinPQ<T>::min() //returns min element in PQ
{
  return pq[1];
}

template <class T>
void MinPQ<T>::delMin() //deletes the first element of the PQ (minimum element b/c MinPQ)
{
  exch(1, N--);
  sink(1, N);
  pq[N+1] = T();
}

template <class T>
void MinPQ<T>::swim(int k) //correctly places element in PQ after it has been added to PQ
{
  while (k > 1 && greater(k/2, k)) {
    exch(k, k/2);
    k = k/2;
  }
}

template <class T>
void MinPQ<T>::sink(int k, int N) //correctly places element in PQ after min element is deleted and replaced
{
  while(2*k <= N) {
    int j = 2*k;
    if (j < N && greater(j, j+1))
      j++;
    if (!greater(k,j))
      break;
    exch(k, j);
    k = j;
  }
}

template <class T>
bool MinPQ<T>::greater(int i, int j) //uses EventComparison to compare respective Event elements to determine which is greater
{
  EventComparison ec;
  return ec.compareEvents(pq[i],pq[j]);
}

template <class T>
void MinPQ<T>::exch(int i, int j) //exchanges places of 2 elements in PQ
{
  T temp = pq[i];
  pq[i] = pq[j];
  pq[j] = temp;
}
