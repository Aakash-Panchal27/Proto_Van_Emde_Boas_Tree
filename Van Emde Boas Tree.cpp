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

  int generate_index(int cluster, int position)
  {
    return cluster * root(universe_size) + position;
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

bool isMember(Van_Emde_Boas* helper, int key)
{
  //if key is greter then universe_size then
  //returns false
  if(key >= helper->universe_size)
    return false;

  //if we reach at base case
  //the just return wheather
  //pointer is nullptr then false
  //else return true
  if(helper->universe_size == 2)
  {
    return helper->clusters[key];
  }
  else
  {
    //recursively goes deep in to the
    //level of VEB tree using its
    //cluster index and its position
    return isMember( helper->clusters[ helper->high(key) ], helper->low(key) );
  }
}

void insert(Van_Emde_Boas* &helper, int key)
{
  //If we reach at base case
  //then assign VEB(1) in place
  //of nullptr
  if(helper->universe_size == 2)
  {
    helper->clusters[key] = new Van_Emde_Boas(1);
  }
  else
  {
      //recursively using index of cluster and its
      //position in cluster
      insert( helper->clusters[ helper->high(key) ], helper->low(key) );

      //also do same recusion in summary VEB
      insert(helper->summary, helper->high(key) );
  }
}

int minimum(Van_Emde_Boas* helper)
{
  if(helper->universe_size == 2)
  {
    if(helper->clusters[0])
    {
      return 0;
    }
    else if(helper->clusters[1])
    {
      return 1;
    }
    return -1;
  }
  else
  {
      int minimum_cluster = minimum(helper->summary);
      int offset;
      if(minimum_cluster == -1)
      {
        return -1;
      }
      else
      {
        offset = minimum( helper->clusters[ minimum_cluster ] );
        return helper->generate_index( minimum_cluster, offset );
      }
  }

}



int maximum(Van_Emde_Boas* helper)
{
  if(helper->universe_size == 2)
  {
    if(helper->clusters[1])
    {
      return 1;
    }
    else if(helper->clusters[0])
    {
      return 0;
    }
    return -1;
  }
  else
  {
      int maximum_cluster = maximum(helper->summary);
      int offset;
      if(maximum_cluster == -1)
      {
        return -1;
      }
      else
      {
        offset = maximum( helper->clusters[ maximum_cluster ] );
        return helper->generate_index( maximum_cluster, offset );
      }
  }

}




int main()
{
  Van_Emde_Boas*hello = new Van_Emde_Boas(4);

  cout << isMember(hello, 3);

  insert(hello, 2);
  insert(hello, 3);

  cout << isMember(hello, 3);

  cout<<"\nminimum: "<<minimum(hello);
  cout<<"\nmaximum: "<<maximum(hello);
}
