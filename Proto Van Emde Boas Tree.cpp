#include<bits/stdc++.h>

using namespace std;

class Proto_Van_Emde_Boas
{
public:

  //total number of keys
  int universe_size;

  //summary
  Proto_Van_Emde_Boas* summary;

  //clusters array of Proto-VEB pointers
  vector< Proto_Van_Emde_Boas* > clusters;

  int root( int u )
  {
    return int( sqrt(u) );
  }

  //returns cluster numbers in which
  //key is present
  int high( int x )
  {
    return x / root( universe_size );
  }

  //returns position of x in cluster
  int low(int x)
  {
    return x % root( universe_size );
  }

  //Gives index form cluster number and position
  int generate_index(int cluster, int position)
  {
    return cluster * root(universe_size) + position;
  }

  //constructor
  Proto_Van_Emde_Boas(int size)
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
      clusters = vector<Proto_Van_Emde_Boas*> (size, nullptr);
    }
    else
    {
      //assiging Proto-VEB(sqrt(u)) to summary
      summary = new Proto_Van_Emde_Boas( root( size ) );

      //creating array of Proto-VEB Tree pointers of size sqrt(u)
      //first all nullptrs are going to assign
      clusters = vector<Proto_Van_Emde_Boas*>( root(size) , nullptr);

      //assigning Proto-VEB(sqrt(u)) to all its clusters
      for(int i = 0 ; i < root(size) ; i++)
      {
        clusters[i] = new Proto_Van_Emde_Boas( root(size) );
      }
    }
  }

};

bool isMember(Proto_Van_Emde_Boas* helper, int key)
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
    return isMember( helper->clusters[ helper->high(key) ],
                                                helper->low(key) );
  }
}

void insert(Proto_Van_Emde_Boas* &helper, int key)
{
  //If we reach at base case
  //then assign Proto-VEB(1) in place
  //of nullptr
  if(helper->universe_size == 2)
  {
    helper->clusters[key] = new Proto_Van_Emde_Boas(1);
  }
  else
  {
      //recursively using index of cluster and its
      //position in cluster
      insert( helper->clusters[ helper->high(key) ],
                                              helper->low(key) );

      //also do same recusion in summary VEB
      insert(helper->summary, helper->high(key) );
  }
}

int minimum(Proto_Van_Emde_Boas* helper)
{
  //base case choses the least key
  //present in the cluster
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
    //no keys present then return -1
    return -1;
  }
  else
  {
      //recursively watches in summary for
      //first 1 present in Proto-VEB so named
      //minimum_cluster
      int minimum_cluster = minimum( helper->summary );
      int offset;

      //if no key is not present in
      //the cluster then returns -1
      if( minimum_cluster == -1 )
      {
        return -1;
      }
      else
      {
        //recursively finds the position of key
        //in the minimum_cluster
        offset = minimum( helper->clusters[ minimum_cluster ] );

        //returns overall index of minimum key
        //see generate_index function for more understading
        return helper->generate_index( minimum_cluster, offset );
      }
  }

}



int maximum(Proto_Van_Emde_Boas* helper)
{
  //returns maximum key present in
  //the cluster
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

    //returns -1 if no keys present in the
    //cluster
    return -1;
  }
  else
  {

      //recursively finds last 1 present
      //in the summary
      int maximum_cluster = maximum(helper->summary);
      int offset;

      //same as minimum
      if(maximum_cluster == -1)
      {
        return -1;
      }
      else
      {
        //same as minimum please refer minimum
        //comments
        offset = maximum( helper->clusters[ maximum_cluster ] );
        return helper->generate_index( maximum_cluster, offset );
      }
  }

}


int successor(Proto_Van_Emde_Boas* helper, int key)
{
  //in base case, returns key greater than
  //our query key in the cluster if present
  //else returns -1
  if(helper->universe_size == 2)
  {
    if(key == 0 && helper->clusters[1])
      return 1;
    else return -1;
  }
  else
  {
    //watches if any key greater than query key is present
    //in the cluster of our key
    int offset = successor(helper->clusters[ helper->high(key) ],
                                            helper->low(key) );

    //if it is present then returns its index
    if(offset != -1)
      return helper->generate_index(helper->high(key), offset);
    else
    {
      //if no successor is present within the cluster then
      //goes to summmary and finds next summary with key present(1)
      //so named successor_cluster
      int successor_cluster = successor(helper->summary,
                                              helper->high(key));

      //if no next 1 in the summary then returns -1
      if(successor_cluster==-1)
        return -1;
      else
      {
        //finds minimum key in the successor_cluster
        offset = minimum( helper->clusters[successor_cluster] );

        //generates its index and returns
        return helper->generate_index( successor_cluster, offset );
      }
    }
  }
}

int predecessor(Proto_Van_Emde_Boas* helper, int key)
{

  //base case wateches smaller key present in
  //the cluster if present else
  //returns -1
  if(helper->universe_size == 2)
  {
    if(key == 1 && helper->clusters[0])
      return 0;
    else return -1;
  }
  else
  {
    //same as successor please refer comments
    //in the successor
    int offset = predecessor(helper->clusters[ helper->high(key) ],
                                                    helper->low(key) );
    if(offset != -1)
      return helper->generate_index(helper->high(key), offset);
    else
    {
      //same as successor please refer comments
      int predecessor_cluster = predecessor(helper->summary,
                                                    helper->high(key));
      if(predecessor_cluster == -1)
        return -1;
      else
      {
        //same as successor please refer comments
        //in the successor
        offset = maximum( helper->clusters[predecessor_cluster] );
        return helper->generate_index( predecessor_cluster, offset );
      }
    }
  }
}

void pveb_delete(Proto_Van_Emde_Boas* &helper, int key)
{
  //base case if key is present then make it nullptr
  if(helper->universe_size == 2)
  {
    if(helper->clusters[key])
    {
    	delete helper->clusters[key];
    	helper->clusters[key] = nullptr;
    }
  }
  else{

    //recursive delete to reach at the base case
	  pveb_delete(helper->clusters[ helper->high(key) ], helper->low(key) );

	  bool isanyinCluster = false;

    //iterate over the cluster of key to check whether
    //any other key is present within that cluster
    //if yes then we should not update summary to 0
    //else update summary to 0
	  for(int i = helper->high(key) * helper->root(helper->universe_size);
	    i < (helper->high(key) + 1) * helper->root(helper->universe_size);
	              i++)

	  {
      //if member is present then break the loop
	    if(isMember(helper->clusters[ helper->high(key) ], i ) )
	    {
	      isanyinCluster = true;
	      break;
	    }
	  }

    //if no member is present then
    //update summary to zero
	  if(isanyinCluster == false)
	  {
	    pveb_delete(helper->summary, helper->high(key) );
	  }
  }
}

int main()
{
  Proto_Van_Emde_Boas*hello = new Proto_Van_Emde_Boas(4);

  cout << isMember(hello, 3);

  insert(hello, 2);
  insert(hello, 3);

  cout << isMember(hello, 3);

  pveb_delete(hello,2);

  cout << isMember(hello, 2);
}
