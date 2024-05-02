#include "BaseMaze.h"
#include "RectangularMaze.h"

BaseMaze::BaseMaze(int verticesNumber, int startVertex, int endVertex)
{
	this->verticesNumber = verticesNumber;
	this->startVertex = startVertex;
	this->endVertex = endVertex;
}

// Create a Graph to represent the maze
// It will create a grind with cells (Each cell is closed for now)

void BaseMaze::InitialiseGraph()
{
	edgesList.clear();
	edgesList.resize(verticesNumber);
}

void BaseMaze::GenerateMaze(SpanningtreeAlgorithmBase* algorithm)
{
	auto spanningTreeEdges = algorithm->SpanningTree(verticesNumber, edgesList);

	// Find a solution of a maze based on Graph DFS.
	Solve(spanningTreeEdges);
	RemoveBorders(spanningTreeEdges);
}

void BaseMaze::Solve(const std::vector<std::pair<int, int>>& spanningTreeEdges)
{
	// We will convert 2 vertex numbers into edges, to run the Depth First Search on it.
	// We should create 2 variables for every edge
	// NOTE: There is 2 variables which hold "From->Edge" and "To->Edge"

	Graph spanningTreeGraph(verticesNumber);
	for (int i = 0; i < spanningTreeEdges.size(); i++) {
		const auto& edge = spanningTreeEdges[i];
		int u = edge.first;
		int v = edge.second;

		// Find the edge in edgesList[u] with vertex v
		auto it_u = std::find_if(edgesList[u].begin(), edgesList[u].end(),
			[v](const Edge& e)
			{
				return std::get<0>(e) == v;
			});

		// Find the edge in edgesList[v] with vertex u
		auto it_v = std::find_if(edgesList[v].begin(), edgesList[v].end(),
			[u](const Edge& e)
			{
				return std::get<0>(e) == u;
			});

		// Add the found edges to the spanningTreeGraph
		spanningTreeGraph[u].push_back(*it_u);
		spanningTreeGraph[v].push_back(*it_v);
	}

	// Find path from ENTRY SINLGE point of a maze to the EXIT point.
	// To make sure that there is an exit in the first place !

	DepthFirstSearch dfs;
	auto parent = dfs.Solve(verticesNumber, spanningTreeGraph, startVertex);

	// Now we will return back every vertix into the graph back
	solution = Graph(verticesNumber);

	// Iterate from endVertex to its parent until reaching a self-parent (parent[u] == u)
	for (int u = endVertex; parent[u] != u; u = parent[u])
	{
		// Find the edge in spanningTreeGraph[u] where the first vertex is the parent of u
		const auto& edge = *std::find_if(spanningTreeGraph[u].begin(), spanningTreeGraph[u].end(),
			[u, &parent](const Edge& e) { return std::get<0>(e) == parent[u]; });

		// Add the found edge to the solution for vertex u
		solution[u].push_back(edge);
	}
}

// We will remove any unnecessary walls from the connected path

void BaseMaze::RemoveBorders(const std::vector<std::pair<int, int>>& spanningTreeEdges)
{
	for (const auto& [u, v] : spanningTreeEdges)
	{
		edgesList[u].erase(
			std::find_if(edgesList[u].begin(), edgesList[u].end(),
				[v = v](const Edge& e)
				{
					return std::get<0>(e) == v;
				}));

		edgesList[v].erase(
			std::find_if(edgesList[v].begin(), edgesList[v].end(),
				[u = u](const Edge& e)
				{
					return std::get<0>(e) == u;
				}));
	}
}

void BaseMaze::PrintMazeSVG(const std::string& filename) const
{
	/*std::ofstream svgfile(filename + ".svg");
	if (!svgfile)
	{
		std::cerr << "Error opening " << filename << ".svg for writing.\n";
		std::cerr << "Terminating.";
		exit(1);
	}
	double xmin, ymin, xmax, ymax;
	std::tie(xmin, ymin, xmax, ymax) = GetCoordinateBounds();
	int xresolution = (xmax - xmin + 2) * 30,
		yresolution = (ymax - ymin + 2) * 30;

	svgfile << "<svg width=\"" << xresolution << "\" height=\"" << yresolution
		<< "\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
	svgfile << "<g transform=\"translate(" << (1 - xmin) * 30 << ","
		<< yresolution - (1 - ymin) * 30 << ") scale(1,-1)\">" << std::endl;
	svgfile << "<rect x=\"" << (xmin - 1) * 30 << "\" y=\"" << (ymin - 1) * 30
		<< "\" width=\"" << xresolution << "\" height=\"" << yresolution
		<< "\" fill=\"white\"/>" << std::endl;

	for (int i = 0; i < _verticesNumber; ++i)
	{
		for (const auto& edge : _edgesList[i])
		{
			if (std::get<0>(edge) < i)
			{
				svgfile << std::get<1>(edge)->SVGPrint("black") << "\n";
			}
		}
	}
	svgfile << "</g>" << std::endl;
	svgfile << "</svg>" << std::endl;
	*/
}

void BaseMaze::Draw(sf::RenderWindow& window, sf::Color& color) const
{
	for (int i = 0; i < verticesNumber; ++i)
	{
		for (const auto& edge : edgesList[i])
		{
			std::get<1>(edge)->Draw(window, color);
		}
	}
}