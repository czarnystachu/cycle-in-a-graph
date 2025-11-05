#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <array>
#include <bitset>

std::bitset <100001> visited_nodes; 
using graph_t = std::vector<std::vector<int>>;

void dodaj_krawedz(graph_t &v, int a, int b)
{
    v[a].push_back(b);
    v[b].push_back(a);
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

// std::set<int> visitedEdges;
// bool contains(const std::set<std::tuple<int, int>> &heystack, const std::tuple<int, int> &needle)
// {
// 	return (heystack.find(needle) != heystack.cend());
// }

void wypiszliste(const graph_t &v)
{
	std::cerr << "Lista: \n";
	// std::cerr << v.size() << '\n';
	for (auto j = 1u; j < v.size(); j++)
	{
		std::cerr << j << ":";

		for (const auto &element : v[j])
		{
			std::cerr << " " << element;
			//	<< " (" << std::boolalpha << contains(visitedEdges, {j, std::get<INDEX>(element)}) << ")";
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
	
	for (const auto &nodes : graph)
	{
		if ((nodes.size() == 0) ||
		    ((nodes.size() % 2) != 0))
		{
			return false;
		}
	}
	return true;
}

void print_visited_nodes()
{
    std::cerr << "array:\n";
    for (int i = 0; i < 20; i++)
    {
        std::cerr << std::boolalpha << visited_nodes[i] << ' ';

    }
    std::cerr << "\n";
}

static std::string path;

bool pisz_wezel_rek(const graph_t & graph, size_t current, int droga, size_t parent)
{
	if (current >= graph.size()) {
		return 0;
	}

	path += std::to_string(current) + " -> ";   //debagowanie

	auto &node = graph[current];
	
	for (size_t node_index = 0; node_index < node.size(); ++node_index)
	{
		auto &edge = node[node_index];
		size_t targetNodeIndex = edge;

		if (targetNodeIndex == parent)
		{
			continue;
		}
		if (visited_nodes[current] == true)
		{
			return (droga > 2) ? true : false;
		}

		visited_nodes[current] = true;

		return pisz_wezel_rek(graph, targetNodeIndex, droga+1, current);
	}

	return 0;
}



int main()
{
	int a;
	std::cin >> a;
	while(a--)
	{

		int n,m;
		std::cin >> n >> m;
		auto v  = wczytaj_graf(n, m);
		while(n)
		{
			visited_nodes[n] = 0;
			--n;
		}
        // wypiszliste(v);

		auto cycled = false;
		for (auto i = 1u; i < v.size() && !cycled; ++i)
		{
			path.clear();
			cycled |= pisz_wezel_rek(v, i, 0, -1);
			 //std::cerr << path << " ." << std::endl;
		}
		auto even = czy_ma_cykl_bo_parzysty(v);
		// wypiszliste(v);
        //print_visited_nodes();
		//std::cerr << visited_nodes <<'\n';
		std::cout << ((cycled || even) ? "TAK" : "NIE") << std::endl;
    }

}

