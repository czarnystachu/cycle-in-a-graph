#include <iostream>
#include <vector>
#include <set>
#include <tuple>

using graph_t = std::vector<std::vector<std::tuple<int, bool>>>;

bool bar(std::set <int> set)
{
	for(const auto element : set)
	{
		// bar(v[element])
	}
	return false;
}

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
// void wypiszliste(graph_t v)
// {
// 	std::cout << "Lista: \n";
// 	//std::cerr << v.size() << '\n';
// 	for(int j = 1; j < v.size(); j++)
// 	{
//         	std::cout << j <<":";

//         	for(const auto element : v[j])
//         	{
//         		std::cout <<" "<< element;
//         	}
// 	std::cout <<'\n' ;
//     	}

// }

bool pisz_wezel_rek(graph_t & graph, size_t index, int droga)
{
	if (index >= graph.size()) {
		return 0;
	}

	std::cerr << "node : " << index << std::endl;
	std::cerr << "droga: " << droga << std::endl;
	auto &node = graph[index];
	for (size_t i = 1; i < node.size(); ++i)
	{
		if (std::get<1>(node[i]) and droga > 2)
		{
			// std::cout << "TAK" << std::endl;
			return 1;
			// continue;
		}
        if(std::get<1>(node[i]) and droga <= 2)
        {
            return 1;
        }
		size_t target_node = std::get<0>(graph[index][i]);
		std::get<1>(node[i]) = true;
		return pisz_wezel_rek(graph, target_node, droga+1);
		// return 0;
	}
	return pisz_wezel_rek(graph, index+1, 0);
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
	//}

		if(pisz_wezel_rek(v, 1, 0))
			std::cout << "TAK" << std::endl;
		else
			std::cout << "NIE" << std::endl;
    }

}
