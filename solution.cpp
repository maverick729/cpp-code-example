//done by varunmaddipati

#include "bits/stdc++.h"
using namespace std;


//------------------------------------Defines-------------------------------//
#define getline_clear cin.ignore()
#define pb push_back

//-----------------------------Code begins----------------------------------//

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
