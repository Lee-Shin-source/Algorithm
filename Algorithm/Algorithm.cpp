﻿
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

#pragma region 연결 여부만 있을때 그래프

void CreateGraph_1()
{
	struct Vertex
	{
		vector<Vertex*> edges;
	};

	vector<Vertex> v;
	v.resize(6);

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);

	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);

	v[3].edges.push_back(&v[4]);

	v[5].edges.push_back(&v[4]);


	// Q) 0번 -> 3번 정점이 연결되어 있나요?
	bool connected = false;
	for (Vertex* edge : v[0].edges)
	{
		if (edge == &v[3])
		{
			connected = true;
			break;
		}
	}
}
void CreateGraph_2()
{
	struct Vertex
	{

	};

	vector<Vertex> v;
	v.resize(6);

	// 연결된 목록을 따로 관리
	// adjacent[n] -> n번째 정점과 연결된 정점 목록
	vector<vector<int>> adjacent(6);

	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// 정점이 100개
	// - 지하철 노선도 -> 서로 드문 드문 연결 (양옆, 환승역이라면 조금 더 ++)
	// - 페이스북 친구 -> 서로 빽빽하게 연결

	// Q) 0번 -> 3번 정점이 연결되어 있나요?
	bool connected = false;
	for (int edge : adjacent[0])
	{
		if (edge == 3)
		{
			connected = true;
			break;
		}
	}

	//STL
	//vector<int>& adj = adjacent[0];
	//bool connected2 = (std::find(adj.begin(), adj.end(), 3) != adj.end());
}
void CreateGraph_3()
{
	struct Vertex
	{

	};

	vector<Vertex> v;
	v.resize(6);

	// 연결된 목록을 따로 관리
	// 
	// [X] [0] [X] [X] [X] [X]
	// [0] [X] [0] [0] [X] [X]
	// [X] [X] [X] [X] [X] [X]
	// [X] [X] [X] [X] [0] [X]
	// [X] [X] [X] [X] [X] [X]
	// [X] [X] [X] [X] [0] [X]

	// 읽는 방법 : adjacent[from][to]
	// 행렬을 이용한 그래프 표현 (2차원 배열)
	// 메모리 소모가 심하지만, 빠른 접근이 가능하다.
	// (간선이 많은 경우 이점이 있다)
	vector<vector<bool>> adjacent(6, vector<bool>(false));

	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;


	// Q) 0번 -> 3번 정점이 연결되어 있나요?
	bool connected = adjacent[0][3];

}
#pragma endregion
#pragma region 가중치 추가
void CreateGraph_4()
{
	struct Vertex
	{

	};

	vector<Vertex> v;
	v.resize(6);

	// 연결된 목록을 따로 관리
	// 
	// [X] [0] [X] [X] [X] [X]
	// [0] [X] [0] [0] [X] [X]
	// [X] [X] [X] [X] [X] [X]
	// [X] [X] [X] [X] [0] [X]
	// [X] [X] [X] [X] [X] [X]
	// [X] [X] [X] [X] [0] [X]

	vector<vector<int>> adjacent = 
	{
		vector<int> {-1, 15, -1, 35, -1, -1},
		vector<int> {15, -1,  5, 10, -1, -1},
		vector<int> {-1, -1, -1, -1, -1, -1},
		vector<int> {-1, -1, -1, -1,  5, -1},
		vector<int> {-1, -1, -1, -1, -1, -1},
		vector<int> {-1, -1, -1, -1,  5, -1}
	};




	// Q) 0번 -> 3번 정점이 연결되어 있나요?
	bool connected = adjacent[0][3] != -1;

	// Q) 0번 -> 3번 정점의 가중치는 얼마인가요?
	adjacent[0][3];


}
#pragma endregion





struct Vertex
{
	// data
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;
vector<bool> visited; // 내가 방문한 목록 (DFS)
vector<bool> discovered; // 발견 여부 (BFS)

void CreateGraph()
{

	vertices.resize(6);
	adjacent = vector<vector<int>>(6);

	// 인접 리스트 방식
	//adjacent[0].push_back(1);
	//adjacent[0].push_back(3);
	//adjacent[1].push_back(0);
	//adjacent[1].push_back(2);
	//adjacent[1].push_back(3);
	//adjacent[3].push_back(4);
	//adjacent[5].push_back(4);

	// 인접 행렬
	adjacent = vector<vector<int>>
	{
		{0, 1, 0, 1, 0, 0},
		{1, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0},
	};

}

// DFS (Depth First Search) 깊이 우선 탐색
#pragma region DFS
// 그래프 전체가 어떤 구조로 되어있는지.
// 그래프의 순환구조가 있는지 알아낼떄 쓸수있음

/// <summary>
/// DFS
/// 우선적으로 현재 방문한 노드에서 내가 방문하지않은 다른 노드가 있으면
/// 그 노드를 우선적으로 이동함
/// </summary>
/// <param name="here"> 현재 시작 지점</param>
void Dfs(int here)
{
	visited[here] = true; // 방문했다

	cout << "Visited : " << here << endl;
	// 인접 리스트 version
	// 모든 인접 정점을 순회한다.
	//for (int i = 0; i < adjacent[here].size(); i++)
	//{
	//	int there = adjacent[here][i];
	//	if (visited[there] == false)
	//		Dfs(there);
	//}

	// 인접 행렬 version
	// 모든 인접 정점을 순회한다.
	for (int there = 0; there < 6; there++)
	{
		if (adjacent[here][there] == 0)
			continue;

		// 아직 방문하지 않은 곳이 있으면 방문한다.
		if (visited[there] == false)
			Dfs(there);

	}
}

/// <summary>
/// 이것의 존재이유 위 코드를 봣을때 5번째 노드는 다른 노드랑 연결되있지는 않은데 
/// 4번 노드를 가르키고있음 그럼 일반적인 위에 Dfs 코드로만으로는 커버가 안됨
/// 그래서 나머지 노드들 중 방문 안한 노드를 전체적으로 순회 할수있게
/// 모든 노드들을 시작점으로 두고 시작해보는것
/// </summary>
void DfsAll()
{
	//visited = vector<bool>(6, false);
	// 시작점에 따라서 결과가 달라수있음
	for (int i = 0; i < 6; i++)
	{
		if (visited[i] == false)
			Dfs(i);
	}
}
#pragma endregion

// BFS (Breadth First Search) 너비 우선 탐색
#pragma region BFS
// 길찾기에 유용함
// Q를 이용한 예약 시스템으로 만듬

void Bfs(int here)
{
	// 누구에 의해 발견 되었는지?
	vector<int> parent(6, -1); // 경로 추적
	// 시작점에서 얼만큼 떨어져 있는지?
	vector<int> distance(6, -1); // 거리

	queue<int> q;
	q.push(here);
	
	discovered[here] = true;

	distance[here] = 0;
	parent[here] = here;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		cout << here << endl;
		
		// 인접 리스트
		//for (int there : adjacent[here])
		//{
		//	if (discovered[there])
		//		continue;

		//	q.push(there);
		//	discovered[there] = true;

		//	parent[there] = here;
		//	distance[there] = distance[here] + 1;
		//}

		// 인접 행렬
		for (int there = 0; there < 6; there++)
		{
			if (adjacent[here][there] == 0)
				continue;

			if (discovered[there])
				continue;

			q.push(there);
			discovered[there] = true;

			parent[there] = here;
			distance[there] = distance[here] + 1;
		}
	}

}

void BfsAll()
{
	for (int i = 0; i < 6; i++)
	{
		if (discovered[i])
			continue;

		Bfs(i);
	}
}
#pragma endregion




int main()
{
	CreateGraph();
	/*visited = vector<bool>(6, false);*/
	discovered = vector<bool>(6, false);
	Bfs(0);
	//BfsAll();

	//Dfs(0);
	//DfsAll();
;}

