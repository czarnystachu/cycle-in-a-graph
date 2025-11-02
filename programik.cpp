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

graph_t wczytaj(int n, int m)
{
	graph_t v;
        v.resize(n+1);

        for(int i = 0; i < m; i++)
        {
                int a, b;
                std::cin >> a >> b;
				v[a].push_back(std::make_tuple(b, false));
				v[b].push_back(std::make_tuple(a, false));
		}
		return v;
}
void wypiszliste(graph_t v)
{
	std::cerr << "Lista: \n";
	std::cerr <<"v.size(): "<< v.size() << '\n';
	for(int j = 1; j < v.size(); j++)
	{
        	std::cerr << j <<":";

        	for(const auto element : v[j])
        	{
				auto tem = std::get <0>(element);
				auto tem2 = std::get <1>(element);
        		std::cerr  << ' ' <<tem <<"("<< tem2 <<")";
        	}
	std::cerr <<'\n' ;
    }

}

bool czy_node_ma_cykl(graph_t & graph, size_t index)
{
	if (index >= graph.size())
	{
		std::cerr <<"index >= graph.size()";
		return 0;
	}
	//std::cout << "node: " << index << std::endl;
	for (size_t i = 1; i < graph[index].size(); ++i)
	{
		if (std::get<1>(graph[index][i]) == true)
			{
				// std::cout << "TAK" << std::endl;
				return 1;
				// continue;
			}

		size_t target_node = std::get<0>(graph[index][i]);
		std::get<1>(graph[index][i]) = true;
		std::cerr <<"test_wypisania\n";
		wypiszliste(graph);
		return czy_node_ma_cykl(graph, target_node);
		// return 0;
	}
	std::cerr <<"brak_cyklu\n";
	return 0;
}

int main()
{
        int a;
        std::cin >>  a;
	while(a--)
	{

		int n,m;
		std::cin >> n >> m;
		auto v  = wczytaj(n, m);

		wypiszliste(v);
		for (int i = 1; i <= n; i++)
		{
			if(czy_node_ma_cykl(v, 1))
			{
				std::cout << "TAK" << std::endl;
			}else
				std::cout << "NIE" << std::endl;

		}
	}

}

