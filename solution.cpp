//done by varunmaddipati
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")

#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
using namespace __gnu_pbds;
using namespace std;

template<class T> 
using ordered_set = tree<T, null_type,less<T>, rb_tree_tag, tree_order_statistics_node_update> ;
 
template<class key, class value, class cmp = std::less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(k)  returns iterator to kth element starting from 0;
// order_of_key(k) returns count of elements strictly smaller than k;
 
template<class T>
using min_heap = priority_queue<T,vector<T>,greater<T> >; 

/*/--------------------------------IO(Debugging)-----------------------------/*/
template<class T> istream& operator >> (istream &is, vector<T>& V) {
    for(auto &e : V)                                                          
        is >> e;
    return is;
}
template<class T, size_t N> istream& operator >> (istream &is, array<T, N>& V) {
    for(auto &e : V)
        is >> e;
    return is;
}
#ifdef __SIZEOF_INT128__
ostream& operator << (ostream &os, __int128 const& value){
    static char buffer[64];
    int index = 0;
    __uint128_t T = (value < 0) ? (-(value + 1)) + __uint128_t(1) : value;
    if (value < 0) 
        os << '-';
    else if (T == 0)
        return os << '0';
    for(; T > 0; ++index){
        buffer[index] = static_cast<char>('0' + (T % 10));
        T /= 10;
    }    
    while(index > 0)
        os << buffer[--index];
    return os;
}
istream& operator >> (istream& is, __int128& T){
    static char buffer[64];
    is >> buffer;
    size_t len = strlen(buffer), index = 0;
    T = 0; int mul = 1;
    if (buffer[index] == '-')
        ++index, mul *= -1;
    for(; index < len; ++index)
        T = T * 10 + static_cast<int>(buffer[index] - '0');
    T *= mul;    
    return is;
}
#endif
template<typename CharT, typename Traits, typename T>
ostream& _containerprint(std::basic_ostream<CharT, Traits> &out, T const &val) {
    return (out << val << " ");
}
template<typename CharT, typename Traits, typename T1, typename T2>
ostream& _containerprint(std::basic_ostream<CharT, Traits> &out, pair<T1, T2> const &val) {
    return (out << "(" << val.first << "," << val.second << ") ");
}
template<typename CharT, typename Traits, template<typename, typename...> class TT, typename... Args>
ostream& operator << (std::basic_ostream<CharT, Traits> &out, TT<Args...> const &cont) {
    out << "[ ";
    for(auto&& elem : cont) _containerprint(out, elem);
    return (out << "]");
}
template<class L, class R> ostream& operator << (ostream& out, pair<L, R> const &val){
    return (out << "(" << val.first << "," << val.second << ") ");
}
template<typename L, size_t N> ostream& operator << (ostream& out, array<L, N> const &cont){
    out << "[ ";
    for(auto&& elem : cont) _containerprint(out, elem);
    return (out << "]");    
}
template<class T> ostream& operator<<(ostream &out, ordered_set<T> const& S){
    out << "{ ";
    for(const auto& s:S) out << s << " ";
    return (out << "}");
}
template<class L, class R, class chash = std::hash<L> > ostream& operator << (ostream &out, gp_hash_table<L, R, chash> const& M) {
    out << "{ ";
    for(const auto& m: M) out << "(" << m.first << ":" << m.second << ") ";
    return (out << "}");
}
template<class P, class Q = vector<P>, class R = less<P> > ostream& operator << (ostream& out, priority_queue<P, Q, R> const& M){
    static priority_queue<P, Q, R> U;
    U = M;
    out << "{ ";
    while(!U.empty())
        out << U.top() << " ", U.pop();
    return (out << "}");
}
template<class P> ostream& operator << (ostream& out, queue<P> const& M){
    static queue<P> U;
    U = M;
    out << "{ ";
    while(!U.empty())
        out << U.front() << " ", U.pop();
    return (out << "}");
}
#define TRACE
#ifdef TRACE
    #define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template <typename Arg1>
    void __f(const char* name, Arg1&& arg1){
        cerr << name << " : " << arg1 << endl;
    }
    template <typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names + 1, ',');
        cerr.write(names, comma - names) << " : " << arg1<<" | ";
        __f(comma+1, args...);
    }
#else
    #define trace(...) 1
#endif

#define getline_clear cin.ignore()
#define pb push_back

string remove_quotes(string s);

struct database{
	vector<string> titles;
	vector<vector<string>> records;
	
	void add_record (vector<string> current_record) {
		records.pb(current_record);
	}
	void set_title(vector<string> title_record) {
		titles = title_record;
	}
};

database from(string s) {
	database given;
	getline_clear;
	ifstream inFile;
	inFile.open(s);
	bool title = true;
	while(getline(inFile, s)) {
		stringstream req(s);
		
		vector<string> current_record;
		
		while(req.good()) {
			string current; 
			getline(req, current, ',');
			current_record.pb(remove_quotes(current));
		}
		if(title) {
			given.set_title(current_record);
		} else {
			given.add_record(current_record);
		}
		
		title = false;
	}
	return given;
}

database select(database current, vector<string> titles_selected) {
	database result;
	result.set_title(titles_selected);
	
	for(vector<string> record : current.records) {
		vector<string> new_record;
		for(int i=0; i<(int)titles_selected.size(); i++) {
			for(int j=0; j<(int)record.size(); j++) {
				if(current.titles[j]==titles_selected[i]) {
					new_record.pb(record[j]);
				}
			}
		}
		result.add_record(new_record);
	}
	return result;
}

database take(database current, int count) {
	database result;
	result.set_title(current.titles);
	
	for(int i=0; i<min(count, (int)current.records.size()); i++) {
		result.add_record(current.records[i]);
	}
	return result;
}

void print_database(database current) {
	for(string s: current.titles) cout<<s<<" ";
	cout<<"\n";
	for(vector<string> record: current.records) {
		for(string s: record) cout<<s<<" ";
		cout<<"\n";
		//break;
	}
	return;
}

string remove_quotes(string s) {
	if(s[0]=='"') s = s.substr(1, s.length()-1);
	if(s.length()!=0 && s[s.length()-1]=='"') 
		s = s.substr(0, s.length()-1);
	return s;
}

vector<string> splitby(string current, char c) {
	vector<string> result;
	stringstream req(current);
	while(req.good()) {
		string part;
		getline(req, part, c);
		result.pb(part);
	}
	return result;
}

void testCase() {
	//Load the csv file
	
	{
		string query; getline(cin, query);
		
		vector<string> query_parts;
		
		stringstream req(query);
		while(req.good()) {
			string current;
			getline(req, current, ' ');
			query_parts.pb(current);
		}
		
		database current = from(query_parts[1]);
		
		
		for(int i=2; i<(int)query_parts.size(); i+=2) {
			if(query_parts[i]=="SELECT") {
				
				vector<string> titles_selected 
				= splitby(query_parts[i+1], ',');
				
				//trace(titles_selected);
				current = select(current, titles_selected);
				
			} else if(query_parts[i]=="TAKE") {
				current = take(current, stoi(query_parts[i+1]));
			}
		}
		
		print_database(current);
	}
	
	
	
	
	
	
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL);

//#ifndef ONLINE_JUDGE
	//freopen("../country.csv", "r", stdin);
	//freopen("../outp", "w", stdout);
	//freopen("../err", "w", stderr);
//#endif

	int T = 1; 
	//cin >> T;
	for (int t = 1; t <= T; t++) {
		//cout << "Case #" << t << ": ";
		testCase();
	}
}
