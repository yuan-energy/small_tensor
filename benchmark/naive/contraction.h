


void Order2Contraction(
	const float * a ,
	const float * b ,
	float * c,
	size_t m, 
	size_t n,
	size_t k
){
	for (size_t row = 0; row < m; ++row) {
		for (size_t col = 0; col < k; ++col) {
			c[ row * k + col ] = 0 ; 
			for (int z = 0; z < n; ++z) {
				c[ row * k + col ] += 
					a[ row * k + z ] 
					* 
					b[ z * n + col ] ; 
			}
		}
	}
}

