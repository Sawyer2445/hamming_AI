/*
 * –асчитывает отклонение двух векторов
 */

#ifndef VEC_NORM
#define VEC_NORM
template<class T>
double vec_norm(const T* vec1, const T* vec0, const size_t size)
{
	double norm = 0; 
	for (auto i = 0; i < size; i++)
	{
		norm += (vec1[i] - vec0[i])*(vec1[i] - vec0[i]);
	}
	return norm;
}
#endif

