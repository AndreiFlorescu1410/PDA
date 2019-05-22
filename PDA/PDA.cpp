#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
int n;
stack<char> stiva;
class operatie
{
	char litera;
	char elimina_din_stiva, adauga_in_stiva[3];
public:
	char GetLitera() { return litera; }
	char GetElimina() { return elimina_din_stiva; }
	string GetAdauga() { return adauga_in_stiva; }
	friend istream& operator >>(istream&, operatie&);
};

int avanseaza(vector<operatie> a[20][20], int x, char litera)
{
	for(int i=0;i<n;i++)
		for (int j = 0; j < a[x][i].size();j++)
		{
			if (litera == a[x][i][j].GetLitera() && stiva.top() == a[x][i][j].GetElimina())
			{
				stiva.pop();
				string adauga = a[x][i][j].GetAdauga();
				if (adauga[0] != 'l')
				{
					stiva.push(adauga[1]);
					stiva.push(adauga[0]);
				}
				return i;
			}
		}
	return -1;
}
int main()
{
	stiva.push('z');
	int i,x,y,nr;
	string cuvant;
	ifstream f("input.in");
	f >> n >> nr;
	vector<operatie> a[20][20];
	operatie operatie_noua;
	for (i = 1; i <= nr; i++) //citire din fisier
	{
		f >> x >> y >> operatie_noua;
		a[x][y].push_back(operatie_noua);
	}
	f >> cuvant;
	int nod_curent = 0;
	while (cuvant.empty() != 1)
	{
		nod_curent=avanseaza(a, nod_curent, cuvant[0]);
		if (nod_curent == -1)
			break;
		cuvant.erase(cuvant.begin());
	}
	while ((nod_curent = avanseaza(a, nod_curent, 'l')) != -1)
		stiva.push('z');
	if (stiva.top() == 'z')
		cout << "Cuvant acceptat";
	else
		cout << "Cuvant neacceptat";
	return 0;
}

istream& operator>>(istream& i, operatie& operatie)
{
	i >> operatie.litera >> operatie.elimina_din_stiva >> operatie.adauga_in_stiva;
	return i;
}
