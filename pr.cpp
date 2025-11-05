#include <iostream>
#include <vector>
#include <set>
#include <tuple>

constexpr auto INDEX = 0u;
constexpr auto VISITED = 1u;
using graph_t = std::vector<std::vector<std::tuple<int, bool>>>;

void dodaj_krawedz(graph_t &v, int a, int b)
{
    v[a].push_back(std::make_tuple(b, false));
    v[b].push_back(std::make_tuple(a, false));
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

std::set<std::tuple<int, int>> visitedEdges;
bool contains(const std::set<std::tuple<int, int>> &heystack, const std::tuple<int, int> &needle)
{
	return (heystack.find(needle) != heystack.cend());
}

void wypiszliste(const graph_t &v)
{
	std::cerr << "Lista: \n";
	// std::cerr << v.size() << '\n';
	for (int j = 1; j < v.size(); j++)
	{
		std::cerr << j << ":";

		for (const auto &element : v[j])
		{
			std::cerr << " " << std::get<INDEX>(element)
					<< " (" << std::boolalpha << contains(visitedEdges, {j, std::get<INDEX>(element)}) << ")";
		}
		std::cerr << '\n';
	}
}


static std::string path;
bool pisz_wezel_rek(const graph_t & graph, size_t current, int droga, int parent)
{
	if (current >= graph.size()) {
		return 0;
	}

	path += std::to_string(current) + " -> ";
	// std::cerr << "droga: " << droga << std::endl;

	auto &node = graph[current];

	for (size_t edgeIndex = 0; edgeIndex < node.size(); ++edgeIndex)
	{
		auto &edge = node[edgeIndex];
		size_t targetNodeIndex = std::get<INDEX>(edge);

		if (targetNodeIndex == parent)
		{
			continue;
		}

		if (contains(visitedEdges, {current, targetNodeIndex}))
		{
			// std::cout << "TAK" << std::endl;
			return (droga > 2) ? true : false;
			// continue;
		}

        // if(std::get<VISITED>(edge) and droga <= 2)
        // {
        //     return 1;
        // }

		visitedEdges.insert({current, targetNodeIndex});
		visitedEdges.insert({targetNodeIndex, current});
		// std::get<VISITED>(edge) = true;

		return pisz_wezel_rek(graph, targetNodeIndex, droga+1, current);
		// return 0;
	}

	return 0;

	// return pisz_wezel_rek(graph, current+1, 0);
}
bool czy_ma_cykl(const graph_t & graph)
{
	for (const auto nodes : graph)
	{
		if (nodes.size() % 2 != 0)
		return 0; 
	}
	return 1;
}

int main()
{
	int a;
	std::cin >>  a;
	while(a--)
	{

		int n,m;
		std::cin >> n >> m;
		auto v  = wczytaj_graf(n, m);

		// wypiszliste(v);

		visitedEdges.clear();
		auto cycled = false;
		for (auto i = 1u; i < v.size() && !cycled; ++i)
		{
			path.clear();
			cycled |= pisz_wezel_rek(v, i, 0, -1);
			// std::cerr << path << " ." << std::endl;
		}

		// wypiszliste(v);

		std::cout << (cycled ? "TAK" : "NIE") << std::endl;
    }

}
