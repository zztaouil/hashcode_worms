#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

struct Contributor{
	string	name;
	map<std::string, int>	skills;

	bool	available;

	void	debug(void){
		std::cout << "name: " << name << std::endl;
		map<string, int>::iterator it = skills.begin();
		cout << "skills: " << endl;
		for (; it != skills.end(); it++)
			cout << it->first << " " << it->second << std::endl;
		cout << endl;
	}

	friend bool operator == (Contributor const &lhs, Contributor const &rhs){
		return lhs.name == rhs.name;
	}
};

struct Project{
	string name;
	int		nb_to_complete;
	int		score;
	int		best_before;
	int		nb_roles;
	vector<pair<string, int> >	skills;

	bool	done;

	void	debug(void){
		cout << "name: " << name << endl;
		cout << "nb to complete: " << nb_to_complete << endl;
		cout << "score: " << score << endl;
		cout << "best_before: "  << best_before << endl;
		cout << "skills required:" << endl;
		for(vector<pair<string, int> >::iterator it = skills.begin(); it != skills.end(); it++)
			cout << it->first << " " << it->second << std::endl;
		cout << endl;
	}
};

struct Game{

	void	debug(void){
		for (size_t i = 0; i < contributors.size(); i++){
			contributors[i].debug();
		}
		for (size_t i = 0; i < projects.size(); i++){
			projects[i].debug();
		}
	}

	void	parse(string filename){
		ifstream ifs;
		string	buffer;
		ifs.open(filename);
		int nb_contrib = 0;
		int nb_project = 0;

		if (!ifs.good())
			exit(0);
		getline(ifs, buffer);
		vector<string>	vec = split(buffer, ' ');

		nb_contrib = stoi(vec[0]);
		nb_project = stoi(vec[1]);
		for (int i = 0; i < nb_contrib; i++){
			Contributor cont;
			cont.available = true;
			getline(ifs, buffer);
			vec = split(buffer, ' ');

			cont.name = vec[0];
			int nb_skill = stoi(vec[1]);
			for (int j = 0; j < nb_skill; j++){
				getline(ifs, buffer);
				vec = split(buffer, ' ');
				cont.skills.insert(make_pair(vec[0], stoi(vec[1])));
			}
			contributors.push_back(cont);
		}
		for (int i = 0; i < nb_project; i++){
			Project proj;
			proj.done = false;
			getline(ifs, buffer);
			vec = split(buffer, ' ');

			proj.name = vec[0];
			proj.nb_to_complete = stoi(vec[1]);
			proj.score = stoi(vec[2]);
			proj.best_before = stoi(vec[3]);
			proj.nb_roles = stoi(vec[4]);
		
			for (int j = 0; j < proj.nb_roles; j++){
				getline(ifs, buffer);
				vec = split(buffer, ' ');
				proj.skills.push_back(make_pair(vec[0], stoi(vec[1])));
			}
			projects.push_back(proj);
		}
		ifs.close();
	}


pair<bool,map<string,int>::iterator>		compare_skill(vector<pair<string, int> > &project, map<string, int> contrib){
		
		for (vector<pair<string, int> >::iterator it = project.begin(); it != project.end(); it++)
		{
			map<string, int>::iterator iter_cont = contrib.find(it->first);

			if (iter_cont != contrib.end())
			{
				if (iter_cont->second >= it->second) {
					project.erase(it);
					return make_pair(true, iter_cont);
				}
					
			}
		}
		return make_pair(false, contrib.end());
	}

	int		hamid_masalach(void){
		int ret = 0;
		for (size_t i = 0; i < projects.size(); i++){
			if (projects[i].done) {
				ret++;
			}
				
		}
		return ret;
	}

	void		waldiha(vector<Contributor> &hamid_contib, vector<pair<string, int> > project_skills){
		for (vector<pair<string, int> >::iterator itt = project_skills.begin(); itt != project_skills.end(); itt++)
		{
			for (size_t x = 0 ; x < hamid_contib.size() ; x++) {
				map<string, int>::iterator hamid = hamid_contib[x].skills.find(itt->first);

				if (hamid != hamid_contib[x].skills.end()) {
					
					cout << hamid_contib[x].name;
					hamid_contib.erase(hamid_contib.begin() + x);
					if (itt != project_skills.end() - 1)
						cout << " ";
					break ;
				}
				
			}
		}
	}
	// bool		check_mentority(vector<Contributor> sa9ta, map<string, int> tentazbi) {
	// 	for (size_t i = 0; i < sa9ta.size() ; i++) {
		
	// 	}
	// }
	void		play(void){
		int count = 0;
		// while (hamid_masalach()){
			for (size_t i=0; i < projects.size(); i++){
				vector<Contributor> hamid_contrib;
				// loop contrib
				vector<pair<string, int> > skolz = projects[i].skills;
				// if (projects[i].name == "AndroidTVNextv1") {
					for (size_t j = 0; j < contributors.size(); j++){
						if (contributors[j].available){
								if (compare_skill(skolz, contributors[j].skills).first) {
									hamid_contrib.push_back(contributors[j]);
								}
						}
					}
					// exit(0);
				// }
				
				// for (size_t j = 0 ; j < contributors.size() ; j++) {
				// 	if (check_mentority(hamid_contrib, contributors[j].skills)) {
				// 		hamid_contrib.push_back(contributors[j]);
				// 	}
				// }
				if (static_cast<int>(hamid_contrib.size()) == projects[i].nb_roles) {
					projects[i].done = true;
					count++;
					cout << projects[i].name << endl;
					vector<pair<string, int> > zab = projects[i].skills;
					waldiha(hamid_contrib, zab);
					for (size_t x = 0; x < hamid_contrib.size(); x++){
						pair<bool, map<string, int>::iterator > iteee = compare_skill(projects[i].skills, hamid_contrib[x].skills);	
						if (iteee.first != false){
							vector<Contributor>::iterator hamd = find(contributors.begin(), contributors.end(), hamid_contrib[x]);
							map<string, int>::iterator toto = hamd->skills.find(iteee.second->first);
					
							toto->second++;	
						}
						// if (hamid_contrib[x].name == "MichalZ")
						// 	exit(0);
					}
					projects.erase(projects.begin() + i);
					cout << endl;
				}
			}
			// cout << string(30, '#') <<endl;
			// debug();
			// cout << string(30, '#') <<endl;
			cout << count<< endl;
		}
	// }

	vector<Contributor> contributors;
	vector<Project>		projects;
};

int		main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	
	Game game;
	
	game.parse(av[1]);
	// game.debug();
	game.play();
	
	return 0;
}