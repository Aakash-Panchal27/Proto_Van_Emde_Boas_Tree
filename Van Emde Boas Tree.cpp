#include<bits/stdc++.h>
using namespace std;


class Van_Emde_Boas
{
public:

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

bool isMember(Van_Emde_Boas* &helper, int key)
{

  if(key >= helper->universe_size)
    return false;

  if(helper->universe_size == 2)
  {
    return helper->clusters[key];
  }
  else
  return isMember( helper->clusters[ helper->high(key) ], helper->low(key) );
}

int main()
{
  Van_Emde_Boas*hello = new Van_Emde_Boas(4);
  cout << isMember(hello, 4);
}
