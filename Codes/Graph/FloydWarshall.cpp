// order of nodes: k->i->j

for( int k = 1; k <= n; ++k ) {
	for( int i = 1; i <= n; ++i ) {
		for( int j = 1; j <= n; ++j ) {
				adjmatrix[i][j] = min( adjmatrix[i][j], adjmatrix[i][k]+adjmatrix[k][j] );
		}
	}
}
