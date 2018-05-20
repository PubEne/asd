#include <iostream>
#include <vector>
#include <utility>

//Knight's tour implementation

template<typename T>
constexpr bool operator<(const std::pair<size_t,size_t>& p1,const T& N)
{
    return p1.first < N && p1.second < N;
}
template<typename T>
constexpr bool operator<(const T& N,const std::pair<size_t,size_t>& p1)
{
    return p1.first < N && p1.second < N;
}

template<typename T>
constexpr bool operator>=(const std::pair<size_t,size_t>& p1,const T& N)
{
    return p1.first >= N && p1.second >= N;
}
template<typename T>
constexpr bool operator>=(const T& N,const std::pair<size_t,size_t>& p1)
{
    return p1.first >= N && p1.second >= N;
}

namespace ASD
{
    static constexpr size_t N = 8; //chessboard's size

    constexpr bool canPut(const std::pair<size_t,size_t>& crd,const int sol[N][N])
    {
        return crd >= 0 && crd < N && sol[crd.first][crd.second] == -1;
    } 
    bool solveKnightsTour(const std::pair<size_t,size_t>& p,const size_t& mv, int sol[N][N],const std::vector<std::pair<int,int>>& knightMoves)
    {
        if(mv == N*N)
            return true;
        for(size_t i = 0; i < 8; ++i)
        {
            std::pair<size_t,size_t> next_move = std::make_pair(p.first+knightMoves[i].first,p.second+knightMoves[i].second);
            if(canPut(next_move,sol))
            {
                sol[next_move.first][next_move.second] = mv;
                if(solveKnightsTour(next_move,mv+1,sol,knightMoves))
                    return true;
                sol[next_move.first][next_move.second] = -1;
            }
        }
        return false;
    }
    void print(const int res[N][N])
    {
        for(size_t i = 0; i < N; ++i)
        {
            for(size_t j = 0; j < N; ++j)
                std::cout << res[i][j] << " ";
            std::cout << std::endl;
        }
    }
    bool knightsTourExists()
    {
        int solution[N][N];
        for(size_t i = 0; i < N; ++i)
            for(size_t j = 0; j < N; ++j)
                solution[i][j] = -1;
        solution[0][0] = 0;
        std::vector<std::pair<int,int>> v = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}}; //xy pairs of knight's moves
        if(!solveKnightsTour({0,0},1,solution,v))
            return false;
        print(solution);
        return true;
    }
}

int main()
{
    ASD::knightsTourExists();
}
