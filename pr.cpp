#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <array>
#include <bitset>

std::bitset <100001> visited; 
using graph_t = std::vector<std::set<size_t>>;

void dodaj_krawedz(graph_t &v, int a, int b)
{
    v[a].insert(b);
    v[b].insert(a);
}

graph_t wczytaj_graf(int n, int m)
{
	graph_t v;
	v.resize(n + 1);

	for (int i = 0; i < m; i++)
	{
		int a, b;
		std::cin >> a >> b;
		dodaj_krawedz(v, a, b);
	}

	return v;
}

void wypiszliste(const graph_t &v)
{
	std::cerr << "Lista: \n";
	for (auto j = 1u; j < v.size(); j++)
	{
		std::cerr << j << ":";
		for (const auto &element : v[j])
		{
			std::cerr << " " << element;
		}
		std::cerr << '\n';
	}
}

bool czy_ma_cykl_bo_parzysty(const graph_t & graph)
{
	if(graph.empty())
	{
		return false;
	}
	
	for (auto i = 1u; i < graph.size(); i++)
	{
		const auto &nodes = graph[i];
		if ((nodes.size() == 0) ||
		    ((nodes.size() % 2) != 0))
		{
			return false;
		}
	}
	return true;
}

bool dfs (const graph_t &graph, size_t current , size_t parent)
{
	auto node = graph[current];
	std::cerr << "current: " <<current<<'\n';
	visited[current] = true;
	for (const auto somsiad : node)
	{
		if(visited[somsiad] == false)
		{
			return dfs (graph, somsiad, current);
		}else if(current != parent)
		{
			return 1;
		}
	} 
}



void print_visited_nodes()
{
    std::cerr << "array:\n";
    for (int i = 0; i < 20; i++)
    {
        std::cerr << std::boolalpha << visited[i] << ' ';

    }
    std::cerr << "\n";
}

static std::string path;

bool DFS(const graph_t & graph, size_t current, int droga, size_t parent)
{
	path += std::to_string(current) + " -> ";   //debagowanie
	
	if (current >= graph.size())
	{
		return 0;
	}

	visited[current] = true;
	auto &node = graph[current];
	
	for (const auto target : node)
	{
		if (target == parent)
		{
			continue;
		}

		if (visited[target] == true)
		{
			return (droga > 2) ? true : false;
		}

		if (DFS(graph, target, droga+1, current))
		{
			return true;
		}
	}
	return 0;
}

int main()
{
// 	int a;
// 	std::cin >> a;
// 	while(a--)
// 	{

// 		int n,m;
// 		std::cin >> n >> m;
// 		auto v  = wczytaj_graf(n, m);
// 		while(n)
// 		{
// 			visited_nodes[n] = 0;
// 			--n;
// 		}
//          wypiszliste(v);

// 		auto cycled = false;
// 		for (auto i = 1u; i < v.size() && !cycled; ++i)
// 		{
// 			path.clear();
// 			cycled |= DFS(v, i, 0, -1);
// 			std::cerr << path << " ." << std::endl;
// 		}
// 		auto even = czy_ma_cykl_bo_parzysty(v);
// 		//std::cerr << even << std::endl;
// 		// wypiszliste(v);
//         //print_visited_nodes();
// 		//std::cerr << visited_nodes <<'\n';
// 		std::cout << ((cycled || even) ? "TAK" : "NIE") << std::endl;
//     }
auto v = wczytaj_graf(3,3);
print_visited_nodes();
wypiszliste(v);
dfs (v, 1, 0);

}