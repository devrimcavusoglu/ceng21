#ifndef __the2_h__
#define __the2_h__

template <class T> void print_array(T *arr, int size);
template <class T> T minimum(T *arr, int size);
template <class T> T min(T &a, T &b);
template <class T> void swappp(T &a, T &b, long &swap, long &comparison);
int distance(int a, int b);
void set_dist(int i, int j, double &avg_dist, double &max_dist);
int classical_partition(unsigned short *arr, int size, long &swap, long &comparison, double &avg_dist, double &max_dist);
int hoare_partition(unsigned short *arr, int size, long &swap, long &comparison, double &avg_dist, double &max_dist);
void partition_3way(unsigned short *arr, int &l, int &r, long &swap, long &comparison, int size);
void quickSort(unsigned short* arr, long &swap, double & avg_dist, double & max_dist, bool hoare, int size);
void quickSort3(unsigned short *arr, long &swap, long &comparison, int size);

#endif // __pair_h__
