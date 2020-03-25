int length_union(const vector<pair<int, int>> &a) {
    int n = a.size();
    vector<pair<int, bool>> x(n*2);
    for (int i = 0; i < n; i++) {
        x[i*2] = {a[i].first, false};
        x[i*2+1] = {a[i].second, true};
    }

    sort(x.begin(), x.end());

    int result = 0;
    int c = 0;
    for (int i = 0; i < n * 2; i++) {
        if (i > 0 && x[i].first > x[i-1].first && c > 0)
            result += x[i].first - x[i-1].first;
        if (x[i].second)
            c--;
        else
            c++;
    }
    return result;
}

int point_union ( vii v )
{
    int req_time = 0;
    sort ( all ( v ) );
    int lastr = 0;

	for (auto s : v){

		if (s.F <= lastr) {
			req_time += max(0, s.S - lastr);
			lastr = max(s.S, lastr);
		}

		else {
			req_time += s.S - s.F + 1;
			lastr = s.S;
		}
	}

	return req_time;
}
