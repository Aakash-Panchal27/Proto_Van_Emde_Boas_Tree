#include<bits/stdc++.h>
using namespace std;


class Van_Emde_Boas
{
  int universe_size;
  Van_Emde_Boas* summary;
  vector<Van_Emde_Boas*> clusters;

  int root( int u )
  {
    return int( sqrt(u) );
  }

  int high( int x )
  {
    return x / root( universe_size );
  }

  int low(int x)
  {
    return x % root( universe_size );
  }

public:
  Van_Emde_Boas(int size)
  {
    universe_size = size;

    //Base case
    if(size <= 2)
    {
      //set summary to nullptr as there is no
      //more summary for size 2
      summary = nullptr;

      //vector of two pointers
      //nullptr in starting
      clusters = vector<Van_Emde_Boas*> (2, nullptr);
    }
    else
    {
      summary = new Van_Emde_Boas( root( size ) );

      clusters = vector<Van_Emde_Boas*>( root(size) );

      for(int i = 0 ; i < root(size) ; i++)
      {
        clusters[i] = new Van_Emde_Boas( root(size) );
      }
    }
  }
};

int main()
{
  Van_Emde_Boas akp(4);
}
